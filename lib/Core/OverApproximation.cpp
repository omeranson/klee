//===-- OverApproximation.cpp -*****---------------------------------------===//
//
//                     The KLEE Symbolic Virtual Machine
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include <llvm/ADT/StringExtras.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/LLVMContext.h>

#include <klee/Internal/Module/KInstruction.h>
#include <klee/Internal/Support/ErrorHandling.h>
#include <klee/Internal/Support/OverApproximation.h>
#include <klee/ExecutionState.h>
#include <klee/Expr.h>
#include "Executor.h"
#include "Memory.h"

void klee::OverApproximation::readConfiguration(const std::string & confFile) {
  try {
    config = YAML::LoadFile(confFile);
  } catch (YAML::BadFile & e) {
    klee_warning("Failed to load file %s: %s", confFile.c_str(), e.what());
    config = YAML::Node();
  }
}

klee::OverApproximation & klee::OverApproximation::getInstance() {
  static klee::OverApproximation * instance = NULL;
  if (!instance) {
    instance = new klee::OverApproximation();
    instance->readConfiguration("over-approximation.yaml");
  }
  return *instance;
}

bool klee::OverApproximation::isOverApproximated(const llvm::Function * f) const {
  std::string functionName = f->getName().str();
  return (!!config[functionName]);
}

void klee::OverApproximation::overApproximate(Executor & executor,
                                              ExecutionState & state,
                                              KInstruction *target,
                                              llvm::Function *f,
                                              std::vector<ref<Expr> > &arguments) {
  static unsigned id = 0;
  std::string functionName = f->getName().str();
  YAML::Node functionConfig = config[functionName];
  YAML::Node writableMemoryArgs = functionConfig["writable_memory_arguments"];

  std::vector<ExecutionState*> states;
  std::vector<ExecutionState*> next_states;
  states.push_back(&state);
  ref<Expr> retval;
  std::string s;
  llvm::raw_string_ostream rso(s);
  rso << f->getName() << "/retval/" << llvm::utostr(++id);
  llvm::StringRef name = rso.str();
  createSymbolicReturnValue(executor, target->inst, name, retval);
  executor.bindLocal(target, state, retval);
  // TODO Remove
  state.addConstraint(SleExpr::create(retval, ConstantExpr::create(1024, retval->getWidth())));

  if (!writableMemoryArgs) {
    return;
  }

  for (YAML::const_iterator it = writableMemoryArgs.begin();
      it != writableMemoryArgs.end(); ++it) {
    int idx = it->as<int>();
    std::string s;
    llvm::raw_string_ostream rso(s);
    rso << f->getName() << "/arg:" << llvm::utostr(idx) << "/" << llvm::utostr(id);
    llvm::StringRef name = rso.str();
    havocStatesReachableMemory(executor, states, name, arguments[idx], next_states);
    // executor.updateStates(&state);
    states = next_states;
    next_states.clear();
  }
}

bool klee::OverApproximation::createSymbolicReturnValue(Executor & executor, const llvm::Instruction * caller, llvm::StringRef & name, ref<Expr> & result) {
  LLVM_TYPE_Q llvm::Type *type = caller->getType();
  if (type == llvm::Type::getVoidTy(llvm::getGlobalContext())) {
  	return false;
  }
  Expr::Width width = executor.getWidthForLLVMType(type);
  executor.createSymbolicValue(width, name, result);
  return true;
}

void klee::OverApproximation::havocReachableMemory(Executor & executor,
                                                   ExecutionState & state,
                                                   llvm::StringRef & name,
                                                   ref<Expr> address,
                                                   std::vector<ExecutionState*> &next_states) {
  Executor::ExactResolutionList rl;
  if (!executor.resolveExact(state, address, rl, name, true)) {
    // Lookup failed
    klee_warning("havocReachableMemory: Lookup failed post-test. State destroyed");
    return;
  }
  if (rl.empty()) {
    // Lookup failed
    klee_warning("havocReachableMemory: Lookup failed post-test");
    return;
  }
  Executor::ExactResolutionList::iterator it = rl.begin();
  Executor::ExactResolutionList::iterator ie = rl.end();
  for (; it != ie; ++it) {
    const MemoryObject *mo = it->first.first;
    const ObjectState *os = it->first.second;
    ExecutionState *s = it->second;
    next_states.push_back(s);
    ObjectState *wos = s->addressSpace.getWriteable(mo, os);
    // TODO(oanson) This possibly can be optimised
    // TODO(oanson) write from address, not from 0
    mo->setName(name);
    const Array *array = executor.arrayCache.CreateArray(name, mo->size);
    UpdateList ul(array, 0);
    for (unsigned offset = 0; offset < mo->size; offset++) {
      ref<Expr> offsetExpr = ConstantExpr::create(offset, Expr::Int32);
      ref<Expr> value = ReadExpr::create(ul, offsetExpr);
      wos->write(offset, value);
    }
    s->addSymbolic(mo, array);
  }
}

void klee::OverApproximation::havocStatesReachableMemory(Executor & executor,
                                                        std::vector<ExecutionState *> &states,
                                                        llvm::StringRef & name,
                                                        ref<Expr> argument,
                                                        std::vector<ExecutionState*> &next_states) {
  for (std::vector<ExecutionState*>::iterator vit = states.begin(),
                                              vie = states.end();
      vit != vie; vit++) {
    havocReachableMemory(executor, **vit, name, argument, next_states);
  }
}
