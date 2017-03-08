//===-- OverApproximation.h -------------------------------------*- C++ -*-===//
//
//                     The KLEE Symbolic Virtual Machine
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
// Class to handle over approximation of given functions. Includes reading and
// parsing the configuration, as well as executing the over-approximation i.e.
// branching to possible Requires clause and havocking writable memory.
//===----------------------------------------------------------------------===//
#ifndef OVER_APPROXIMATION_H
#define OVER_APPROXIMATION_H

#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

#include <klee/util/Ref.h>

namespace llvm {
  class Function;
  class Instruction;
  class StringRef;
}

namespace klee {

class Executor;
class ExecutionState;
class Expr;
class KInstruction;

class OverApproximation {
protected:
  YAML::Node config;

  void readConfiguration(const std::string & confFile);
  OverApproximation() {}; // Singleton
  virtual ~OverApproximation() {}; // Singleton
public:
  static OverApproximation & getInstance();
  bool isOverApproximated(const llvm::Function * f) const;
  void overApproximate(Executor & executor, ExecutionState & state,
                       KInstruction *target, llvm::Function * f, std::vector<ref<Expr> > &arguments);
protected:
  bool createSymbolicReturnValue(Executor & executor,
                                 const llvm::Instruction * caller,
                                 llvm::StringRef & name,
                                 ref<Expr> & result);

  void havocReachableMemory(Executor & executor, ExecutionState & state,
                            llvm::StringRef & name, ref<Expr> address,
                            std::vector<ExecutionState*> &next_states);

  void havocStatesReachableMemory(Executor & executor,
                                  std::vector<ExecutionState *> &states,
                                  llvm::StringRef & name, ref<Expr> argument,
                                  std::vector<ExecutionState*> &next_states);
}; // class OverApproximation

} // namespace klee

#endif // OVER_APPROXIMATION_H
