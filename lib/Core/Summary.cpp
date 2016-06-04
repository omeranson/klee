#include "klee/Summary.h"

Summary::Summary (const klee::ExecutionState & state, const klee::Executor & executor)
        : _state(state), _executor(executor) {}

void Summary::update(llvm::Function & function) {
    _functionName = function->getName().str();
    llvm::Function::const_iterator it;
    for (it = funciton.begin(); it != function.end(); it++) {
        update(*it);
    }
}

void Summary::update(llvm::BasicBlock & basicBlock) {
    llvm::BasicBlock::const_iterator it;
    for (it = basicBlock.begin(); it != basicBlock.end(); it++) {
        update(*it);
    }
}

void Summary::update(llvm::Instruction & instruction) {
// void Executor::executeInstruction(ExecutionState &_state, KInstruction *ki) { ... }
//  llvm::Instruction *i = ki->inst;
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
    switch (i->getOpcode()) {
        case llvm::Instruction::Ret: {
            // Save return value.
            llvm::ReturnInst *ri = llvm::cast<llvm::ReturnInst>(i);
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
            llvm::BranchInst *bi = llvm::cast<llvm::BranchInst>(i);
            updateWithInstruction(bi);
            break;
        }
        case llvm::Instruction::Switch: {
            // Like branch: Save value, but visit every basic block
            llvm::SwitchInst *si = llvm::cast<llvm::SwitchInst>(i);
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
            llvm::InvokeInst *ii = llvm::cast<llvm::InvokeInst>(i);
            updateWithInstruction(ii);
            break;
        }
        case llvm::Instruction::Call: {
            // Summarise and merge
            llvm::CallInst *ci = llvm::cast<llvm::CallInst>(i);
            updateWithInstruction(ci);
            break;
        }
        case llvm::Instruction::PHI: {
            // Assign symbolic value
            // Better summary implementations to check if value is constant or
            // extract constraints
            llvm::PHINode *phi = llvm::cast<llvm::PHINode>(i);
            updateWithInstruction(phi);
            break;
        }
        case llvm::Instruction::Select: {
            // Same as Phi - Assign symbolic value.
            // Possibly improve with better Summary implementations.
            llvm::SelectInst *si = llvm::cast<llvm::SelectInst>(i);
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
            llvm::BinaryOperator *boi = llvm::cast<llvm::BinaryOperator>(i);
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
            llvm::UnaryInstruction *ui = llvm::cast<llvm::UnaryInstruction>(i);
            updateWithInstruction(ui);
            break;
        }

        case llvm::Instruction::ICmp: {
            // Assign symbolic to temporary
            // (Possibly in subclass) if all params are constant, calculate result
            llvm::ICmpInst *ii = llvm::cast<llvm::ICmpInst>(i);
            updateWithInstruction(ii);
            break;
        }

        case llvm::Instruction::FCmp: {
            llvm::FCmpInst *fi = llvm::cast<llvm::FCmpInst>(i);
            updateWithInstruction(fi);
            break;
        }

        case llvm::Instruction::Alloca: {
            // It is important to note this memory address, as it is considered
            // a temporary.
            llvm::AllocaInst *ai = llvm::cast<llvm::AllocaInst>(i);
            updateWithInstruction(ai);
            break;
        }

        case llvm::Instruction::Load: {
            // Set temporary to be symbolic
            // * If both address and value are constant, load constant
            llvm::LoadInst *li = llvm::cast<llvm::LoadInst>(i);
            updateWithInstruction(li);
            break;
        }

        case llvm::Instruction::Store: {
            // Set destination to be symbolic
            // (Currently) Fail (or concretise) if address is not constant
            // * If all params are constant, execute as constant
            llvm::StoreInst *si = llvm::cast<llvm::StoreInst>(i);
            updateWithInstruction(si);
            break;
        }

        case llvm::Instruction::GetElementPtr: {
            // Same as Load/Store
            llvm::GetElementPtrInst *gepi = llvm::cast<llvm::GetElementPtrInst>(i);
            updateWithInstruction(gepi);
            break;
        }

        case llvm::Instruction::InsertValue: {
            llvm::InsertValueInst *ivi = llvm::cast<llvm::InsertValueInst>(i);
            updateWithInstruction(ivi);
            break;
        }

        case llvm::Instruction::ExtractValue: {
            llvm::ExtractValueInst *evi = llvm::cast<llvm::ExtractValueInst>(i);
            updateWithInstruction(evi);
            break;
        }

        case llvm::Instruction::AtomicRMW: {
            llvm::AtomicRMWInst *armwi = llvm::cast<llvm::AtomicRMWInst>(i);
            updateWithInstruction(armwi);
            break;
        }

        case llvm::Instruction::ExtractElement: {
            llvm::ExtractElementInst *eei = llvm::cast<llvm::ExtractElementInst>(i);
            updateWithInstruction(eei);
            break;
        }

        case llvm::Instruction::InsertElement: {
            llvm::InsertElementInst *iei = llvm::cast<llvm::InsertElementInst>(i);
            updateWithInstruction(iei);
            break;
        }

        case llvm::Instruction::ShuffleVector: {
            llvm::ShuffleVectorInst *svi = llvm::cast<llvm::ShuffleVectorInst>(i);
            updateWithInstruction(svi);
            break;
        }

        default: {
            std::string opcodeName = i->getOpcodeName();
            _executor.terminateStateOnExecError(_state, "illegal instruction: " + opcodeName);
            break;
        }
    }
}

void Summary::updateWithInstruction(llvm::Instruction * instruction) {
        std::string opcodeName = instruction->getOpcodeName();
        // _executor.terminateStateOnExecError(_state, "Unhandled instruction summary: " + opcodeName);
        klee_warning_once("Unhandled instruction summary: " + opcodeName);
}

void Summary::updateWithInstruction(llvm::ReturnInst * instruction) {
    const llvm::Function function = instruction->getFunction();
    LLVM_TYPE_Q llvm::Type *returnType = function->getReturnType();
    if (returnType == llvn::Type::getVoidTy(getGlobalContext())) {
        _hasReturnValue = false;
        return;
    }
    Expr::Width width = _executor.getWidthForLLVMType(returnType);
    auto size = Expr::getMinBytesForWidth(width);
    std::string name = _functionName + "_summary";
    const Array *array = _executor.arrayCache.CreateArray(name, size);
    _returnValue = Expr::createTempRead(array, width);
    _hasReturnValue = true;
}

/*
void Summary::updateWithInstruction(llvm::BranchInst * instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::BranchInst");
}

void Summary::updateWithInstruction(llvm::SwitchInst * instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::SwitchInst");
}

void Summary::updateWithInstruction(llvm::InvokeInst * instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::InvokeInst");
}

void Summary::updateWithInstruction(llvm::CallInst * instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::CallInst");
}

void Summary::updateWithInstruction(llvm::PHINode * instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::PHINode");
}

void Summary::updateWithInstruction(llvm::SelectInst * instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::SelectInst");
}

void Summary::updateWithInstruction(llvm::BinaryOperator * instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::BinaryOperator");
}

void Summary::updateWithInstruction(llvm::UnaryInstruction * instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::UnaryInstruction");
}

void Summary::updateWithInstruction(llvm::ICmpInst * instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::ICmpInst");
}

void Summary::updateWithInstruction(llvm::FCmpInst * instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::FCmpInst");
}

void Summary::updateWithInstruction(llvm::AllocaInst * instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::AllocaInst");
}

void Summary::updateWithInstruction(llvm::LoadInst * instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::LoadInst");
}

void Summary::updateWithInstruction(llvm::StoreInst * instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::StoreInst");
}

void Summary::updateWithInstruction(llvm::GetElementPtrInst * instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::GetElementPtrInst");
}

void Summary::updateWithInstruction(llvm::InsertValueInst * instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::InsertValueInst");
}

void Summary::updateWithInstruction(llvm::ExtractValueInst * instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::ExtractValueInst");
}

void Summary::updateWithInstruction(llvm::AtomicRMWInst * instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::AtomicRMWInst");
}

void Summary::updateWithInstruction(llvm::ExtractElementInst * instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::ExtractElementInst");
}

void Summary::updateWithInstruction(llvm::InsertElementInst * instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::InsertElementInst");
}

void Summary::updateWithInstruction(llvm::ShuffleVectorInst * instruction) {
	_executor.terminateStateOnExecError(_state, "Unhandled instruction summary: llvm::ShuffleVectorInst");
}
*/

// TODO(oanson) Make these methods consts
bool Summary::hasReturnValue() const {
    return _hasReturnValue;
}

// The return value
ref<Expr> & Summary::returnValue() {
    return _returnValue;
}

// Modified memory addresses, and their values
std::map<ref<Expr>, ref<Expr> > & Summary::modifiedMemory() {
    return _modifiedMemory;
}

void Summary::debug() {
    std::cerr
    std::stringstream ss;
    ss << "Return value: " << _returnValue;
    ss << "Modified memory: { ";
    std::map<ref<Expr>, ref<Expr> >::iterator it;
    for (it = _modifiedMemory.begin(); it != _modifiedMemory.end(); it++) {
        ss << it->first << ": " << it->second << ", ";
    }
    klee_message("Summary for %s: %s", _functionName.c_str(), oss.str().c_str());
}
