#include <sstream>

#include "llvm/IR/LLVMContext.h"

#include "klee/Expr.h"
#include "klee/Summary.h"
#include "klee/klee.h"
#include "klee/Internal/Support/ErrorHandling.h"

Summary::Summary (const klee::ExecutionState & state, const klee::Executor & executor)
        : _state(state), _executor(executor) {}

void Summary::update(const llvm::Function & function) {
    _functionName = function.getName().str();
    llvm::Function::const_iterator it;
    for (it = function.begin(); it != function.end(); it++) {
        update(*it);
    }
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
    const llvm::Function & function = getFunction(instruction);
    LLVM_TYPE_Q llvm::Type *returnType = function.getReturnType();
    if (returnType == llvm::Type::getVoidTy(llvm::getGlobalContext())) {
        _hasReturnValue = false;
        return;
    }
    klee::Expr::Width width = _executor.getWidthForLLVMType(returnType);
    size_t size = klee::Expr::getMinBytesForWidth(width);
    std::string name = _functionName + "_summary";
    const klee::Array *array = arrayCache.CreateArray(name, size);
    _returnValue = klee::Expr::createTempRead(array, width);
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

void Summary::updateWithInstruction(const llvm::StoreInst & instruction) {
	// update _modifiedMemory with new value.
	// What to do when store is symbolic?
	// 	Havoc? (Fairly bad)
	// 	Error? (Worse)
	// 	Ignore? (Worst)
	//
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::StoreInst");
}

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

// TODO(oanson) Make these methods consts
bool Summary::hasReturnValue() const {
    return _hasReturnValue;
}

// The return value
klee::ref<klee::Expr> & Summary::returnValue() {
    return _returnValue;
}

// Modified memory addresses, and their values
std::map<klee::ref<klee::Expr>, klee::ref<klee::Expr> > & Summary::modifiedMemory() {
    return _modifiedMemory;
}

void Summary::debug() const {
    std::stringstream ss;
    if (hasReturnValue()) {
	    ss << "Return value: ";
	    ss << *_returnValue;
    } else {
	    ss << "No return value.";
    }
    ss << "  Modified memory: { ";
    std::map<klee::ref<klee::Expr>, klee::ref<klee::Expr> >::const_iterator it;
    for (it = _modifiedMemory.begin(); it != _modifiedMemory.end(); it++) {
        ss << *(it->first) << ": ";
	ss << *(it->second) << ", ";
    }
    ss << "}";
    klee::klee_message("Summary for %s: %s", _functionName.c_str(), ss.str().c_str());
}
