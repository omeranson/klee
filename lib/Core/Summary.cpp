#include <sstream>

#include <llvm/IR/Constants.h>
#include <llvm/IR/DataLayout.h>
#include <llvm/IR/LLVMContext.h>

#include "klee/Expr.h"
#include "klee/Summary.h"
#include "klee/klee.h"
#include "klee/Internal/Support/ErrorHandling.h"

static int runcount = 0;

Summary::Summary ()
        : _module(0) {}

void Summary::update(const llvm::Function & function) {
    _function = &function;
    _module = function.getParent();
    // TODO(oanson) No support for vararg
    _arguments.assign(function.arg_size(), 0);
    llvm::Function::const_arg_iterator args_it;
    for (args_it = function.arg_begin(); args_it != function.arg_end(); args_it++) {
	unsigned index = args_it->getArgNo();
	_arguments[index] = klee::ArgumentExpr::create(args_it->getName().str());
    }
    _functionName = function.getName().str();
    llvm::Function::const_iterator it;
    for (it = function.begin(); it != function.end(); it++) {
        update(*it);
    }
    ++runcount;
}

void Summary::update(const llvm::BasicBlock & basicBlock) {
    llvm::BasicBlock::const_iterator it;
    for (it = basicBlock.begin(); it != basicBlock.end(); it++) {
        update(*it);
    }
}

void Summary::update(const llvm::Instruction & instruction) {
// void Executor::executeInstruction(ExecutionState &_state, KInstruction *ki) { ... }
//  llvm::Instruction *instruction = ki->inst;
    // ...
    // If store or set (or phi):
    //  If value is constant: ( Possibly in second pass )
    //      summary[value_name] <- constant value
    //  elif value is closed set of constants: ( Possibly in second pass )
    //      summary[value_name] <- {set of options}
    //  else (First pass)
    //      summary[value_name] <- symbolic value of store size
    // Else:
    //  (Almost) Simulate expression.
    //  branch: ignore (although maintain entry values for phi later)
    //  ...
    //
    //
    // Phase one:
    //  Every set, or store, is symbolic.
    //  If attempt to store to a symbolic address: Fail (So that we'll know and fix it)
    //  Branch operations are ignored (all BB are traversed in order they appear in function)
    // Phase two:
    //  Constant expressions remain constant.
    //  Rest is as in phase one
    // Phase three:
    //  Chaotic iteration (branch handling)
    //  Rest is as in phase two
    // Phase four:
    //  If possible, simulate expression.
    //  Rest as in phase three
    switch (instruction.getOpcode()) {
        case llvm::Instruction::Ret: {
            // Save return value.
            const llvm::ReturnInst &ri = llvm::cast<llvm::ReturnInst>(instruction);
            updateWithInstruction(ri);
            break;
        }
        // Unwind is handled by the default: Fail!
        // case llvm::Instruction::Unwind:
        case llvm::Instruction::Br: {
            // If unconditional, ignore
            // If conditional, save condition result.
            //  If condition result constant: (Probably not do this in simplest)
            //      Continue to only reachable basic block
            const llvm::BranchInst &bi = llvm::cast<llvm::BranchInst>(instruction);
            updateWithInstruction(bi);
            break;
        }
        case llvm::Instruction::Switch: {
            // Like branch: Save value, but visit every basic block
            const llvm::SwitchInst &si = llvm::cast<llvm::SwitchInst>(instruction);
            updateWithInstruction(si);
            break;
        }
        case llvm::Instruction::Unreachable: {
            // Fail or ignore?
            // Currently ignore. Uncomment next line to fail
            //_executor.terminateStateOnExecError(_state, "reached \"unreachable\" instruction");
            break;
        }
        case llvm::Instruction::Invoke: {
            // Summarise and merge
            const llvm::InvokeInst &ii = llvm::cast<llvm::InvokeInst>(instruction);
            updateWithInstruction(ii);
            break;
        }
        case llvm::Instruction::Call: {
            // Summarise and merge
            const llvm::CallInst &ci = llvm::cast<llvm::CallInst>(instruction);
            updateWithInstruction(ci);
            break;
        }
        case llvm::Instruction::PHI: {
            // Assign symbolic value
            // Better summary implementations to check if value is constant or
            // extract constraints
            const llvm::PHINode &phi = llvm::cast<llvm::PHINode>(instruction);
            updateWithInstruction(phi);
            break;
        }
        case llvm::Instruction::Select: {
            // Same as Phi - Assign symbolic value.
            // Possibly improve with better Summary implementations.
            const llvm::SelectInst &si = llvm::cast<llvm::SelectInst>(instruction);
            updateWithInstruction(si);
            break;
        }
        case llvm::Instruction::VAArg: {
            // Fail or ignore? (Klee fails)
            // For now, ignore. Uncomment next line to fail:
            //_executor.terminateStateOnExecError(_state, "unexpected VAArg instruction");
            break;
        }
        // All arithmetic / logical operands will be treated similarly:
        // Assign symbolic
        // If both parameters are constant, assign constant (But possibly in subclass)
        case llvm::Instruction::Add:
        case llvm::Instruction::Sub:
        case llvm::Instruction::Mul:
        case llvm::Instruction::UDiv:
        case llvm::Instruction::SDiv:
        case llvm::Instruction::URem:
        case llvm::Instruction::SRem:
        case llvm::Instruction::And:
        case llvm::Instruction::Or:
        case llvm::Instruction::Xor:
        case llvm::Instruction::Shl:
        case llvm::Instruction::LShr:
        case llvm::Instruction::AShr:
        case llvm::Instruction::FAdd:
        case llvm::Instruction::FSub:
        case llvm::Instruction::FMul:
        case llvm::Instruction::FDiv:
        case llvm::Instruction::FRem: {
            const llvm::BinaryOperator &boi = llvm::cast<llvm::BinaryOperator>(instruction);
            updateWithInstruction(boi);
            break;
        }

        // Conversion
        // Same treatment to all: symbolic -> symbolic. * Constant -> Constant.
        case llvm::Instruction::Trunc:
        case llvm::Instruction::ZExt:
        case llvm::Instruction::SExt:
        case llvm::Instruction::IntToPtr:
        case llvm::Instruction::PtrToInt:
        case llvm::Instruction::BitCast:
        case llvm::Instruction::FPTrunc:
        case llvm::Instruction::FPExt:
        case llvm::Instruction::FPToUI:
        case llvm::Instruction::FPToSI:
        case llvm::Instruction::UIToFP:
        case llvm::Instruction::SIToFP: {
            const llvm::UnaryInstruction &ui = llvm::cast<llvm::UnaryInstruction>(instruction);
            updateWithInstruction(ui);
            break;
        }

        case llvm::Instruction::ICmp: {
            // Assign symbolic to temporary
            // (Possibly in subclass) if all params are constant, calculate result
            const llvm::ICmpInst &ii = llvm::cast<llvm::ICmpInst>(instruction);
            updateWithInstruction(ii);
            break;
        }

        case llvm::Instruction::FCmp: {
            const llvm::FCmpInst &fi = llvm::cast<llvm::FCmpInst>(instruction);
            updateWithInstruction(fi);
            break;
        }

        case llvm::Instruction::Alloca: {
            // It is important to note this memory address, as it is considered
            // a temporary.
            const llvm::AllocaInst &ai = llvm::cast<llvm::AllocaInst>(instruction);
            updateWithInstruction(ai);
            break;
        }

        case llvm::Instruction::Load: {
            // Set temporary to be symbolic
            // * If both address and value are constant, load constant
            const llvm::LoadInst &li = llvm::cast<llvm::LoadInst>(instruction);
            updateWithInstruction(li);
            break;
        }

        case llvm::Instruction::Store: {
            // Set destination to be symbolic
            // (Currently) Fail (or concretise) if address is not constant
            // * If all params are constant, execute as constant
            const llvm::StoreInst &si = llvm::cast<llvm::StoreInst>(instruction);
            updateWithInstruction(si);
            break;
        }

        case llvm::Instruction::GetElementPtr: {
            // Same as Load/Store
            const llvm::GetElementPtrInst &gepi = llvm::cast<llvm::GetElementPtrInst>(instruction);
            updateWithInstruction(gepi);
            break;
        }

        case llvm::Instruction::InsertValue: {
            const llvm::InsertValueInst &ivi = llvm::cast<llvm::InsertValueInst>(instruction);
            updateWithInstruction(ivi);
            break;
        }

        case llvm::Instruction::ExtractValue: {
            const llvm::ExtractValueInst &evi = llvm::cast<llvm::ExtractValueInst>(instruction);
            updateWithInstruction(evi);
            break;
        }

        case llvm::Instruction::AtomicRMW: {
            const llvm::AtomicRMWInst &armwi = llvm::cast<llvm::AtomicRMWInst>(instruction);
            updateWithInstruction(armwi);
            break;
        }

        case llvm::Instruction::ExtractElement: {
            const llvm::ExtractElementInst &eei = llvm::cast<llvm::ExtractElementInst>(instruction);
            updateWithInstruction(eei);
            break;
        }

        case llvm::Instruction::InsertElement: {
            const llvm::InsertElementInst &iei = llvm::cast<llvm::InsertElementInst>(instruction);
            updateWithInstruction(iei);
            break;
        }

        case llvm::Instruction::ShuffleVector: {
            const llvm::ShuffleVectorInst &svi = llvm::cast<llvm::ShuffleVectorInst>(instruction);
            updateWithInstruction(svi);
            break;
        }

        default: {
            const std::string & opcodeName = instruction.getOpcodeName();
	    klee::klee_warning("illegal instruction in summary: %s", opcodeName.c_str());
            break;
        }
    }
}

void Summary::updateWithInstruction(const llvm::Instruction & instruction) {
        std::string opcodeName = instruction.getOpcodeName();
	klee::klee_warning("Unhandled instruction summary: %s", opcodeName.c_str());
}

const llvm::Function & getFunction(const llvm::Instruction & instruction) {
	const llvm::BasicBlock * basicBlock = instruction.getParent();
	return *(basicBlock->getParent());
}

void Summary::updateWithInstruction(const llvm::ReturnInst & instruction) {
    llvm::Value * returnValue = instruction.getReturnValue();
    if (!returnValue) {
        _hasReturnValue = false;
        return;
    }
    if (_hasReturnValue) {
	LLVM_TYPE_Q llvm::Type *type = returnValue->getType();
        _returnValue = createSymbolicExpr(type, "return_value");
	return;
    }
    _returnValue = evaluate(*returnValue);
    _hasReturnValue = true;
}

/*
void Summary::updateWithInstruction(const llvm::BranchInst & instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::BranchInst");
}

void Summary::updateWithInstruction(const llvm::SwitchInst & instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::SwitchInst");
}

void Summary::updateWithInstruction(const llvm::InvokeInst & instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::InvokeInst");
}

void Summary::updateWithInstruction(const llvm::CallInst & instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::CallInst");
}

void Summary::updateWithInstruction(const llvm::PHINode & instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::PHINode");
}

void Summary::updateWithInstruction(const llvm::SelectInst & instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::SelectInst");
}

void Summary::updateWithInstruction(const llvm::BinaryOperator & instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::BinaryOperator");
}

void Summary::updateWithInstruction(const llvm::UnaryInstruction & instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::UnaryInstruction");
}

void Summary::updateWithInstruction(const llvm::ICmpInst & instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::ICmpInst");
}

void Summary::updateWithInstruction(const llvm::FCmpInst & instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::FCmpInst");
}

void Summary::updateWithInstruction(const llvm::AllocaInst & instruction) {
	// Create symbolic of allocated size. Value set to its address
    LLVM_TYPE_Q llvm::Type *type = instruction.getAllocatedType();
    klee::Expr::Width width = _executor.getWidthForLLVMType(type);
    if (instruction.isArrayAllocation()) {
      const llvm::Value count = instruction.getArraySize();
      if (isConstant(count)) {
	      ref<Expr> count = evaluate(count);
      } else {
	      return;
      }
      count = Expr::createZExtToPointerWidth(count);
      size = MulExpr::create(size, count);
    }
    executeAlloc(state, size, true, ki);
}


void Summary::updateWithInstruction(const llvm::LoadInst & instruction) {
	// Read data from state. Override with data from _modifiedMemory
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::LoadInst");
}

*/
void Summary::updateStore(
		const llvm::Value & baseValue, const llvm::Value & valueValue,
		std::map<klee::ref<klee::Expr>, klee::ref<klee::Expr> > & memmap) {
	klee::ref<klee::Expr> baseExpr = evaluate(baseValue);
	klee::ref<klee::Expr> valueExpr = evaluate(valueValue);
	std::map<klee::ref<klee::Expr>, klee::ref<klee::Expr> >::iterator it = memmap.find(baseExpr);
	if (it == memmap.end()) {
		memmap.insert(
			std::pair<klee::ref<klee::Expr>, klee::ref<klee::Expr> >(
				baseExpr, valueExpr));
		return;
	}
	if (it->second == valueExpr) {
		return;
	}
	LLVM_TYPE_Q llvm::Type * type = valueValue.getType();
	std::stringstream ss;
	ss << valueExpr;
	memmap[baseExpr] = createSymbolicExpr(type, ss.str().c_str());
}

void Summary::updateWithInstruction(const llvm::StoreInst & instruction) {
	// update _modifiedMemory with new value.
	// What to do when store is symbolic (i.e. base address is symbolic)?
	// 	Havoc? (Fairly bad)
	// 	Error? (Worse)
	// 	Ignore? (Worst)
	//	Currently, just have the symbolic address as key in _modifiedMemory
	const llvm::Value * baseValue = instruction.getPointerOperand();
	const llvm::Value * valueValue = instruction.getValueOperand();
	if (llvm::isa<llvm::AllocaInst>(*baseValue)) {
		updateStore(*baseValue, *valueValue, _stackMemory);
	} else {
		updateStore(*baseValue, *valueValue, _modifiedMemory);
	}
}
/*
void Summary::updateWithInstruction(const llvm::GetElementPtrInst & instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::GetElementPtrInst");
}

void Summary::updateWithInstruction(const llvm::InsertValueInst & instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::InsertValueInst");
}

void Summary::updateWithInstruction(const llvm::ExtractValueInst & instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::ExtractValueInst");
}

void Summary::updateWithInstruction(const llvm::AtomicRMWInst & instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::AtomicRMWInst");
}

void Summary::updateWithInstruction(const llvm::ExtractElementInst & instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::ExtractElementInst");
}

void Summary::updateWithInstruction(const llvm::InsertElementInst & instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::InsertElementInst");
}

void Summary::updateWithInstruction(const llvm::ShuffleVectorInst & instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::ShuffleVectorInst");
}
*/

klee::ref<klee::Expr> Summary::evaluate(const llvm::Value & value) {
	if (llvm::isa<llvm::Instruction>(value)) {
	    const llvm::Instruction & instruction = llvm::cast<llvm::Instruction>(value);
	    switch (instruction.getOpcode()) {
		case llvm::Instruction::Ret: {
		    // Save return value.
		    const llvm::ReturnInst &ri = llvm::cast<llvm::ReturnInst>(instruction);
		    return _evaluate(ri);
		}
		// Unwind is handled by the default: Fail!
		// case llvm::Instruction::Unwind:
		case llvm::Instruction::Br: {
		    // If unconditional, ignore
		    // If conditional, save condition result.
		    //  If condition result constant: (Probably not do this in simplest)
		    //      Continue to only reachable basic block
		    const llvm::BranchInst &bi = llvm::cast<llvm::BranchInst>(instruction);
		    return _evaluate(bi);
		}
		case llvm::Instruction::Switch: {
		    // Like branch: Save value, but visit every basic block
		    const llvm::SwitchInst &si = llvm::cast<llvm::SwitchInst>(instruction);
		    return _evaluate(si);
		}
		case llvm::Instruction::Unreachable: {
		    // Fail or ignore?
		    // Currently ignore. Uncomment next line to fail
		    //_executor.terminateStateOnExecError(_state, "reached \"unreachable\" instruction");
		    break;
		}
		case llvm::Instruction::Invoke: {
		    // Summarise and merge
		    const llvm::InvokeInst &ii = llvm::cast<llvm::InvokeInst>(instruction);
		    return _evaluate(ii);
		}
		case llvm::Instruction::Call: {
		    // Summarise and merge
		    const llvm::CallInst &ci = llvm::cast<llvm::CallInst>(instruction);
		    return _evaluate(ci);
		}
		case llvm::Instruction::PHI: {
		    // Assign symbolic value
		    // Better summary implementations to check if value is constant or
		    // extract constraints
		    const llvm::PHINode &phi = llvm::cast<llvm::PHINode>(instruction);
		    return _evaluate(phi);
		}
		case llvm::Instruction::Select: {
		    // Same as Phi - Assign symbolic value.
		    // Possibly improve with better Summary implementations.
		    const llvm::SelectInst &si = llvm::cast<llvm::SelectInst>(instruction);
		    return _evaluate(si);
		}
		case llvm::Instruction::VAArg: {
		    // Fail or ignore? (Klee fails)
		    // For now, ignore. Uncomment next line to fail:
		    //_executor.terminateStateOnExecError(_state, "unexpected VAArg instruction");
		    break;
		}
		// All arithmetic / logical operands will be treated similarly:
		// Assign symbolic
		// If both parameters are constant, assign constant (But possibly in subclass)
		case llvm::Instruction::Add:
		case llvm::Instruction::Sub:
		case llvm::Instruction::Mul:
		case llvm::Instruction::UDiv:
		case llvm::Instruction::SDiv:
		case llvm::Instruction::URem:
		case llvm::Instruction::SRem:
		case llvm::Instruction::And:
		case llvm::Instruction::Or:
		case llvm::Instruction::Xor:
		case llvm::Instruction::Shl:
		case llvm::Instruction::LShr:
		case llvm::Instruction::AShr:
		case llvm::Instruction::FAdd:
		case llvm::Instruction::FSub:
		case llvm::Instruction::FMul:
		case llvm::Instruction::FDiv:
		case llvm::Instruction::FRem: {
		    const llvm::BinaryOperator &boi = llvm::cast<llvm::BinaryOperator>(instruction);
		    return _evaluate(boi);
		}

		// Conversion
		// Same treatment to all: symbolic -> symbolic. * Constant -> Constant.
		case llvm::Instruction::Trunc:
		case llvm::Instruction::ZExt:
		case llvm::Instruction::SExt:
		case llvm::Instruction::IntToPtr:
		case llvm::Instruction::PtrToInt:
		case llvm::Instruction::BitCast:
		case llvm::Instruction::FPTrunc:
		case llvm::Instruction::FPExt:
		case llvm::Instruction::FPToUI:
		case llvm::Instruction::FPToSI:
		case llvm::Instruction::UIToFP:
		case llvm::Instruction::SIToFP: {
		    const llvm::UnaryInstruction &ui = llvm::cast<llvm::UnaryInstruction>(instruction);
		    return _evaluate(ui);
		}

		case llvm::Instruction::ICmp: {
		    // Assign symbolic to temporary
		    // (Possibly in subclass) if all params are constant, calculate result
		    const llvm::ICmpInst &ii = llvm::cast<llvm::ICmpInst>(instruction);
		    return _evaluate(ii);
		}

		case llvm::Instruction::FCmp: {
		    const llvm::FCmpInst &fi = llvm::cast<llvm::FCmpInst>(instruction);
		    return _evaluate(fi);
		}

		case llvm::Instruction::Alloca: {
		    // It is important to note this memory address, as it is considered
		    // a temporary.
		    const llvm::AllocaInst &ai = llvm::cast<llvm::AllocaInst>(instruction);
		    return _evaluate(ai);
		}

		case llvm::Instruction::Load: {
		    // Set temporary to be symbolic
		    // * If both address and value are constant, load constant
		    const llvm::LoadInst &li = llvm::cast<llvm::LoadInst>(instruction);
		    return _evaluate(li);
		}

		case llvm::Instruction::Store: {
		    // Set destination to be symbolic
		    // (Currently) Fail (or concretise) if address is not constant
		    // * If all params are constant, execute as constant
		    const llvm::StoreInst &si = llvm::cast<llvm::StoreInst>(instruction);
		    return _evaluate(si);
		}

		case llvm::Instruction::GetElementPtr: {
		    // Same as Load/Store
		    const llvm::GetElementPtrInst &gepi = llvm::cast<llvm::GetElementPtrInst>(instruction);
		    return _evaluate(gepi);
		}

		case llvm::Instruction::InsertValue: {
		    const llvm::InsertValueInst &ivi = llvm::cast<llvm::InsertValueInst>(instruction);
		    return _evaluate(ivi);
		}

		case llvm::Instruction::ExtractValue: {
		    const llvm::ExtractValueInst &evi = llvm::cast<llvm::ExtractValueInst>(instruction);
		    return _evaluate(evi);
		}

		case llvm::Instruction::AtomicRMW: {
		    const llvm::AtomicRMWInst &armwi = llvm::cast<llvm::AtomicRMWInst>(instruction);
		    return _evaluate(armwi);
		}

		case llvm::Instruction::ExtractElement: {
		    const llvm::ExtractElementInst &eei = llvm::cast<llvm::ExtractElementInst>(instruction);
		    return _evaluate(eei);
		}

		case llvm::Instruction::InsertElement: {
		    const llvm::InsertElementInst &iei = llvm::cast<llvm::InsertElementInst>(instruction);
		    return _evaluate(iei);
		}

		case llvm::Instruction::ShuffleVector: {
		    const llvm::ShuffleVectorInst &svi = llvm::cast<llvm::ShuffleVectorInst>(instruction);
		    return _evaluate(svi);
		}

		default: {
		    const std::string & opcodeName = instruction.getOpcodeName();
		    klee::klee_warning("illegal instruction in summary: %s", opcodeName.c_str());
		    break;
		}
	    }
	} else if (llvm::isa<llvm::Constant>(value)) {
		if (llvm::isa<llvm::ConstantInt>(value)) {
			const llvm::ConstantInt & constant = llvm::cast<llvm::ConstantInt>(value);
			return klee::ConstantExpr::alloc(constant.getValue());
		} else if (llvm::isa<llvm::ConstantFP>(value)) {
			const llvm::ConstantFP & constant = llvm::cast<llvm::ConstantFP>(value);
			return klee::ConstantExpr::alloc(constant.getValueAPF());
		} else if (llvm::isa<llvm::GlobalValue>(value)) {
			const llvm::GlobalValue & globalValue = llvm::cast<llvm::GlobalValue>(value);
			return _evaluate(globalValue);
		}
	} else if (llvm::isa<llvm::Argument>(value)) {
		const llvm::Argument & argument = llvm::cast<llvm::Argument>(value);
		return _evaluate(argument);
	} else {
		return _evaluate(value);
	}
	assert(0 && "Unhandled case!");
}

klee::ref<klee::Expr> Summary::_evaluate(const llvm::Value & value) {
    std::map<const llvm::Value*, klee::ref<klee::Expr> >::iterator it = _values.find(&value);
    if (it != _values.end()) {
    	return it->second;
    }
    LLVM_TYPE_Q llvm::Type *type = value.getType();
    std::string name;
    if (value.hasName()) {
    	name = value.getName().str();
    } else {
    	name = "<unnamed>";
    }
    klee::ref<klee::Expr> result = createSymbolicExpr(type, name);
    _values[&value] = result;
    return result;
}

klee::ref<klee::Expr> Summary::_evaluate(const llvm::Argument & argument) {
	unsigned index = argument.getArgNo();
	return _arguments[index];
}

klee::ref<klee::Expr> Summary::_evaluate(const llvm::GlobalValue & globalValue) {
// TODO This causes the load to fail.
	std::map<const llvm::GlobalValue *, klee::ref<klee::Expr> >::const_iterator it = _globals.find(&globalValue);
	if (it != _globals.end()) {
		return it->second;
	}
	klee::ref<klee::Expr> value = klee::ArgumentExpr::create(globalValue.getName().str());
	_globals[&globalValue] = value;
	return value;
}

klee::ref<klee::Expr> Summary::_evaluate(const llvm::LoadInst & instruction) {
	const llvm::Value * pointerValue = instruction.getPointerOperand();
	klee::ref<klee::Expr> pointerExpr = evaluate(*pointerValue);
	std::map<klee::ref<klee::Expr>, klee::ref<klee::Expr> >::const_iterator it = _modifiedMemory.find(pointerExpr);
	if (it != _modifiedMemory.end()) {
		return it->second;
	}
	it = _stackMemory.find(pointerExpr);
	if (it != _stackMemory.end()) {
		return it->second;
	}
	const llvm::Value & value = instruction;
	return _evaluate(value);
}

klee::ref<klee::Expr> Summary::createSymbolicExpr(LLVM_TYPE_Q llvm::Type * type, const std::string & name) const {
    llvm::DataLayout dataLayout(_module);
    klee::Expr::Width width = dataLayout.getTypeSizeInBits(type);
    return klee::PureSymbolicExpr::create(name, width);
}

// TODO(oanson) Make these methods consts
bool Summary::hasReturnValue() const {
    return _hasReturnValue;
}

std::vector<klee::ref<klee::Expr> > & Summary::arguments() {
    return _arguments;
}

const std::map<const llvm::GlobalValue *, klee::ref<klee::Expr> > & Summary::globals() const {
	return _globals;
}

// The return value
klee::ref<klee::Expr> & Summary::returnValue() {
    return _returnValue;
}

// Modified memory addresses, and their values
std::map<klee::ref<klee::Expr>, klee::ref<klee::Expr> > & Summary::modifiedMemory() {
    return _modifiedMemory;
}

const llvm::Function & Summary::function() const {
	return *_function;
}

/*
void Summary::execute(klee::ExecutionState& state) {
    ExprEvaluator ee;
    std::map<ref<Expr>, ref<Expr> >::iterator it;
    for (it = _modifiedMemory.begin(); it != _modifiedMemory.end(); it++) {
        ref<Expr> & base = ee.visit(it->first);
        ref<Expr> & value = ee.visit(it->second);
        state.constraints.addConstraint(klee::EqExpr::create());
    }
}
*/

void Summary::print(std::ostream& ss) const {
    ss << "Arguments: { ";
    for (unsigned idx = 0; idx < _arguments.size(); idx++) {
        ss << idx << ": " << *(_arguments[idx]) << ", ";
    }
    ss << "}";

    if (hasReturnValue()) {
	    ss << "  Return value: ";
	    ss << *_returnValue;
    } else {
	    ss << "  No return value.";
    }
    ss << "  Modified memory: { ";
    std::map<klee::ref<klee::Expr>, klee::ref<klee::Expr> >::const_iterator it;
    for (it = _modifiedMemory.begin(); it != _modifiedMemory.end(); it++) {
        ss << *(it->first) << ": ";
	ss << *(it->second) << ", ";
    }
    ss << "}";
    ss << "  Stack memory: { ";
    for (it = _stackMemory.begin(); it != _stackMemory.end(); it++) {
        ss << *(it->first) << ": ";
	ss << *(it->second) << ", ";
    }
    ss << "}";
    ss << "  globals: { ";
    std::map<const llvm::GlobalValue *, klee::ref<klee::Expr> >::const_iterator globals_it;
    for (globals_it = _globals.begin(); globals_it != _globals.end(); globals_it++) {
	std::string buffer;
	llvm::raw_string_ostream rso(buffer);
	rso << (globals_it->first->getName().str()) << ": " << *(globals_it->second) << ", ";
	ss << rso.str();
    }
    ss << "}";
}

void Summary::debug() const {
    std::stringstream ss;
    ss << *this;
    klee::klee_message("Summary for %s: %s", _functionName.c_str(), ss.str().c_str());
}

/** SummaryExecution **/

SummaryExecution::SummaryExecution(Summary & summary) : summary(summary) {}
const std::map<klee::ref<klee::ArgumentExpr>, klee::ref<klee::Expr> > & SummaryExecution::arguments() const {
	return _arguments;
}

const std::map<klee::ref<klee::PureSymbolicExpr>, klee::ref<klee::Expr> > & SummaryExecution::symbolics() const {
	return _symbolics;
}

void SummaryExecution::map(klee::ref<klee::ArgumentExpr> &key, klee::ref<klee::Expr> & value) {
	_arguments.insert(std::make_pair(key, value));
}

void SummaryExecution::map(klee::ref<klee::PureSymbolicExpr> &key, klee::ref<klee::Expr> & value) {
	_symbolics.insert(std::make_pair(key, value));
}
