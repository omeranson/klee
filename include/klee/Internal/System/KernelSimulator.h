//===-- KernelSimulator.h ---------------------------------------*- C++ -*-===//
//
//                     The KLEE Symbolic Virtual Machine
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Class to simulate kernel functions. Specifically a class to simulate system
// calls and store their state (which is usually stored in kernel)
//
//===----------------------------------------------------------------------===//

#ifndef KERNEL_SIMULATOR_H
#define KERNEL_SIMULATOR_H

#include <fcntl.h>
#include <stdint.h>
#include <stdarg.h>
#include <unistd.h>
#include <vector>

#include <klee/Expr.h>

namespace klee {
  class Expr;
  class ExecutionState;
  class Executor;
  struct KInstruction;
  template<typename T> class ref;

  typedef enum {
    FDT_uninitialised  = 0,
    FDT_socket,
    FDT_file
  } FileDescriptorType;

  struct FileDescriptor {
    // TODO TBD
    FileDescriptorType FDTType;
    // TODO Allow to be symbolic
    int domain; // socket
    int type; // socket
    int protocol; // socket

    int flags; // open
    // int mode; // open (not needed)
  };

  class KernelSimulator {
  public: // TODO(oanson) make private
    std::vector<FileDescriptor> fileDescriptors;

    KernelSimulator();
    int nextFreeFileDescriptor();
    bool exprToInt(ref<Expr> expr, int & result);
    bool exprToUInt64(ref<Expr> expr, uint64_t & result);
    ref<Expr> constantInt(int result);
    ref<Expr> constantInt32(int result);
    ref<Expr> constantChar(char result);
    bool readDataAtAddress(Executor & executor, ExecutionState & state, ref<Expr> addressExpr, char * buf, uint64_t size);
    bool simpleReadUniquePointer(Executor & executor, ExecutionState &state, ref<Expr> expr, Expr::Width width, ref<Expr> & result);

    int _getrlimit(Executor & executor, ExecutionState & state, uint64_t resource, ref<Expr> pointer);
    int _setrlimit(Executor & executor, ExecutionState & state, uint64_t resource, ref<Expr> pointer);

    void forkAndFail(Executor & executor, ExecutionState & state, KInstruction * target, int ncodes, ...);
    void vForkAndFail(Executor & executor, ExecutionState & state, KInstruction * target, int ncodes, va_list codes);
  public:
  
    void syscall(Executor & executor, ExecutionState & state, KInstruction * target, std::vector<ref<Expr> > &arguments);
    #define KLEE_SYSCALL_FUNCTION(name) void name(Executor & executor, ExecutionState & state, KInstruction * target, std::vector<ref<Expr> > &arguments)
    KLEE_SYSCALL_FUNCTION(socket);
    KLEE_SYSCALL_FUNCTION(bind);
    KLEE_SYSCALL_FUNCTION(connect);
    KLEE_SYSCALL_FUNCTION(open);
    KLEE_SYSCALL_FUNCTION(ioctl);
    KLEE_SYSCALL_FUNCTION(fcntl);
    KLEE_SYSCALL_FUNCTION(close);
    KLEE_SYSCALL_FUNCTION(fstat);
    KLEE_SYSCALL_FUNCTION(mmap);
    KLEE_SYSCALL_FUNCTION(getsockname);
    KLEE_SYSCALL_FUNCTION(getcwd);
    KLEE_SYSCALL_FUNCTION(getuid);
    KLEE_SYSCALL_FUNCTION(getpid);
    KLEE_SYSCALL_FUNCTION(write);
    KLEE_SYSCALL_FUNCTION(writev);
    KLEE_SYSCALL_FUNCTION(prlimit64);
    KLEE_SYSCALL_FUNCTION(getrlimit);
    KLEE_SYSCALL_FUNCTION(setrlimit);
    KLEE_SYSCALL_FUNCTION(exit);
    KLEE_SYSCALL_FUNCTION(setsid);
    #undef KLEE_SYSCALL_FUNCTION

  };

}
#endif // KERNEL_SIMULATOR_H
