#include "klee/Internal/System/KernelSimulator.h"

#include <syscall.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <netinet/in.h>

#include <llvm/Support/raw_ostream.h>

#include "klee/Internal/Support/Debug.h"
#include "klee/Internal/Support/ErrorHandling.h"
#include "../Core/Executor.h"
#include "../Core/Memory.h"
#include "../Core/SpecialFunctionHandler.h"

namespace klee {

KernelSimulator::KernelSimulator() {
  fileDescriptors.push_back(FileDescriptor());
  fileDescriptors.push_back(FileDescriptor());
  fileDescriptors.push_back(FileDescriptor());

  FileDescriptor & stdin = fileDescriptors[0];
  stdin.FDTType = FDT_file;
  stdin.flags = O_RDONLY;

  FileDescriptor & stdout = fileDescriptors[1];
  stdout.FDTType = FDT_file;
  stdout.flags = O_WRONLY;

  FileDescriptor & stderr = fileDescriptors[2];
  stderr.FDTType = FDT_file;
  stderr.flags = O_WRONLY;
}

bool KernelSimulator::exprToInt(ref<Expr> expr, int & result) {
  if (!isa<ConstantExpr>(expr)) {
    return false;
  }
  result = cast<ConstantExpr>(expr)->getSExtValue();
  return true;
}

bool KernelSimulator::exprToUInt64(ref<Expr> expr, uint64_t & result) {
  if (!isa<ConstantExpr>(expr)) {
    return false;
  }
  result = cast<ConstantExpr>(expr)->getZExtValue();
  return true;
}

bool KernelSimulator::simpleReadUniquePointer(Executor & executor, ExecutionState &state,
    ref<Expr> expr, Expr::Width width, ref<Expr> & result) {
  ObjectPair op;
  ref<Expr> addressExpr = executor.toUnique(state, expr);
  ref<ConstantExpr> address = cast<ConstantExpr>(addressExpr);
  if (!state.addressSpace.resolveOne(address, op)) {
    klee_warning("exprToPointer: Multiple resolutions");
    Executor::ExactResolutionList rl;
    executor.resolveExact(state, address, rl, "syscall_getsockname_size");
    if (rl.begin() == rl.end()) {
      klee_warning("exprToPointer: Actually, NO resolutions");
    }
    for (Executor::ExactResolutionList::iterator it = rl.begin(),
           ie = rl.end(); it != ie; ++it) {
      const MemoryObject *mo = it->first.first;
      const ObjectState *os = it->first.second;
      ref<Expr> value = os->read(mo->getOffsetExpr(address), width);
      std::string s;
      llvm::raw_string_ostream rso(s);
      rso << "A resolution result: " << value;
      klee_warning("	%s", rso.str().c_str());
    }
    abort();
    return false;
  }
  bool res __attribute__ ((unused));

  const MemoryObject *mo = op.first;
  const ObjectState *os = op.second;
  ref<Expr> value = os->read(mo->getOffsetExpr(address), width);
  result = executor.toUnique(state, expr);
  return true;
}

bool KernelSimulator::readDataAtAddress(Executor & executor, ExecutionState & state,
    ref<Expr> addressExpr, char * buf, uint64_t size) {
  ObjectPair op;
  addressExpr = executor.toUnique(state, addressExpr);
  ref<ConstantExpr> address = cast<ConstantExpr>(addressExpr);
  if (!state.addressSpace.resolveOne(address, op)) {
    klee_warning("exprToPointer: Multiple resolutions");
    return false;
  }
  const ObjectState *os = op.second;

  for (unsigned idx = 0; idx < size; idx++) {
    ref<Expr> cur = os->read8(idx);
    cur = executor.toUnique(state, cur);
    if (!isa<ConstantExpr>(cur)) {
      klee_warning("hit symbolic char while reading concrete string");
      return false;
    }
    buf[idx] = cast<ConstantExpr>(cur)->getZExtValue(8);
  }
  return true;
}

ref<Expr> KernelSimulator::constantInt(int result) {
	return ConstantExpr::create(result, Expr::Int64);
}

ref<Expr> KernelSimulator::constantInt32(int result) {
	return ConstantExpr::create(result, Expr::Int32);
}

ref<Expr> KernelSimulator::constantChar(char result) {
	return ConstantExpr::create(result, Expr::Int8);
}

void KernelSimulator::syscall(Executor & executor, ExecutionState & state, KInstruction * target, std::vector<ref<Expr> > &arguments) {
  // Assert arguments[0] is constant expression
  // switch/case over arguments[0]
  // do the magic
  // return
  // default: Fail!
  assert(arguments.size()>0 &&
         "invalid number of arguments to syscall");
  uint64_t op_z;
  if (!exprToUInt64(arguments[0], op_z)) {
    executor.terminateStateOnError(state,
           "syscall called with non-constant operation",
           Executor::User);
    return;
  }
  switch (op_z) {
  #define KLEE_SYSCALL_CALL_FAILURES(name, ncodes, ...) \
  case SYS_##name:\
    forkAndFail(executor, state, target, ncodes, ##__VA_ARGS__); \
    return name(executor, state, target, arguments);
  #define KLEE_SYSCALL_CALL(name) \
  case SYS_##name:\
    return name(executor, state, target, arguments);
  #define KLEE_SYSCALL_NOP(name) \
  case SYS_##name:\
    executor.bindLocal(target, state, constantInt(0)); \
    return;
  KLEE_SYSCALL_CALL_FAILURES(socket, 0, 0)
  KLEE_SYSCALL_CALL_FAILURES(bind, 0, 0)
  KLEE_SYSCALL_CALL_FAILURES(connect, 0, 0)
  KLEE_SYSCALL_CALL_FAILURES(open, 0, 0)
  KLEE_SYSCALL_CALL_FAILURES(ioctl, 0, 0)
  KLEE_SYSCALL_CALL_FAILURES(fcntl, 0, 0)
  KLEE_SYSCALL_CALL_FAILURES(close, 0, 0)
  KLEE_SYSCALL_CALL_FAILURES(fstat, 0, 0)
  KLEE_SYSCALL_CALL_FAILURES(mmap, 0, 0)
  KLEE_SYSCALL_CALL_FAILURES(getsockname, 0, 0)
  KLEE_SYSCALL_CALL_FAILURES(getcwd, 0, 0)
  KLEE_SYSCALL_CALL_FAILURES(getuid, 0, 0)
  KLEE_SYSCALL_CALL_FAILURES(getpid, 0, 0)
  KLEE_SYSCALL_CALL_FAILURES(write, 0, 0)
  KLEE_SYSCALL_CALL_FAILURES(writev, 0, 0)
  KLEE_SYSCALL_CALL_FAILURES(prlimit64, 0, 0)
  KLEE_SYSCALL_CALL_FAILURES(getrlimit, 0, 0)
  KLEE_SYSCALL_CALL_FAILURES(setrlimit, 0, 0)
  KLEE_SYSCALL_CALL(setsid) // TODO(oanson) Also fork and return correct errors, but setsid is not interesting enough currently
  KLEE_SYSCALL_CALL(exit)
  KLEE_SYSCALL_NOP(rt_sigaction)
  KLEE_SYSCALL_NOP(rt_sigprocmask)
  #undef KLEE_SYSCALL_CALL
  default: {
    std::string s;
    llvm::raw_string_ostream rso(s);
    rso << "syscall called with unsupported operation: " << op_z;
    const char * message = rso.str().c_str();
    klee_warning("%s", message);

    executor.terminateStateOnError(state, message, Executor::User);
    return;
  }
  }
}

int KernelSimulator::nextFreeFileDescriptor() {
  for (unsigned idx = 0; idx < fileDescriptors.size(); idx++) {
    if (fileDescriptors[idx].FDTType == FDT_uninitialised) {
      return idx;
    }
  }
  int result = fileDescriptors.size();
  fileDescriptors.push_back(FileDescriptor());
  return result;
}

void KernelSimulator::vForkAndFail(Executor & executor, ExecutionState & state, KInstruction * target, int ncodes, va_list codes) {
  static unsigned id = 0;
  ref<Expr> result;
  executor.createSymbolicValue(64, "syscall failures" + llvm::utostr(++id), result);
  executor.bindLocal(target, state, result);
  ref<Expr> assumptions = EqExpr::create(constantInt(-ENOSYS), result);
  for (int idx = 0; idx < ncodes; idx++) {
    int code = va_arg(codes, int);
    assumptions = OrExpr::create(result, 
		    EqExpr::create(constantInt(code), result));
  }
  state.addConstraint(assumptions);
}

void KernelSimulator::forkAndFail(Executor & executor, ExecutionState & state, KInstruction * target, int ncodes, ...) {
  va_list codes;
  va_start ( codes, ncodes );
  vForkAndFail(executor, state, target, ncodes, codes);
  va_end(codes);
}

void KernelSimulator::socket(Executor & executor, ExecutionState & state, KInstruction * target, std::vector<ref<Expr> > &arguments) {
  int fdidx = nextFreeFileDescriptor();
  FileDescriptor & fd = fileDescriptors[fdidx];
  fd.FDTType = FDT_socket;
  if (!exprToInt(arguments[1], fd.domain)) {
    klee_warning("socket called with non-constant domain");
    executor.terminateStateOnError(state,
        "socket called with non-constant domain",
        Executor::User);
    return;
  }
  if (!exprToInt(arguments[2], fd.type)) {
    klee_warning("socket called with non-constant type");
    executor.terminateStateOnError(state,
        "socket called with non-constant type",
        Executor::User);
    return;
  }
  if (!exprToInt(arguments[3], fd.protocol)) {
    klee_warning("socket called with non-constant protocol");
    executor.terminateStateOnError(state,
        "socket called with non-constant protocol",
        Executor::User);
    return;
  }
  executor.bindLocal(target, state, constantInt(fdidx));
}

void KernelSimulator::bind(Executor & executor, ExecutionState & state, KInstruction * target, std::vector<ref<Expr> > &arguments) {
  uint64_t sockfd;
  if (!exprToUInt64(arguments[1], sockfd)) {
    const char * message = "bind called with non-constant socket";
    klee_warning(message);
    executor.terminateStateOnError(state, message, Executor::User);
    return;
  }
  if (sockfd >= fileDescriptors.size()) {
    const char * message = "bind on non-existant file-descriptor";
    klee_warning(message);
    executor.terminateStateOnError(state, message, Executor::User);
    return;
  }
  FileDescriptor & fd = fileDescriptors[sockfd];
  if (fd.FDTType != FDT_socket) {
    const char * message = "bind on non-socket file descriptor";
    klee_warning(message);
    executor.terminateStateOnError(state, message, Executor::User);
    return;
  }
  // TODO check other arguments?
  executor.bindLocal(target, state, constantInt(0));
}

void KernelSimulator::ioctl(Executor & executor, ExecutionState & state, KInstruction * target, std::vector<ref<Expr> > &arguments) {
  uint64_t sockfd;
  if (!exprToUInt64(arguments[1], sockfd)) {
    const char * message = "ioctl called with non-constant socket";
    klee_warning(message);
    executor.terminateStateOnError(state, message, Executor::User);
    return;
  }
  if (sockfd >= fileDescriptors.size()) {
    const char * message = "ioctl on non-existant file-descriptor";
    klee_warning(message);
    executor.terminateStateOnError(state, message, Executor::User);
    return;
  }
  FileDescriptor & fd = fileDescriptors[sockfd];
  if (fd.FDTType != FDT_socket) {
    const char * message = "ioctl on non-socket file descriptor";
    klee_warning(message);
    executor.terminateStateOnError(state, message, Executor::User);
    return;
  }
  // TODO check other arguments?
  executor.bindLocal(target, state, constantInt(0));
}

void KernelSimulator::fcntl(Executor & executor, ExecutionState & state, KInstruction * target, std::vector<ref<Expr> > &arguments) {
  uint64_t sockfd;
  if (!exprToUInt64(arguments[1], sockfd)) {
    const char * message = "fcntl called with non-constant socket";
    klee_warning(message);
    executor.terminateStateOnError(state, message, Executor::User);
    return;
  }
  if (sockfd >= fileDescriptors.size()) {
    const char * message = "fcntl on non-existant file-descriptor";
    klee_warning(message);
    executor.terminateStateOnError(state, message, Executor::User);
    return;
  }
  FileDescriptor & fd = fileDescriptors[sockfd];
  if (fd.FDTType != FDT_socket) {
    const char * message = "fcntl on non-socket file descriptor";
    klee_warning(message);
    executor.terminateStateOnError(state, message, Executor::User);
    return;
  }
  // TODO check other arguments?
  executor.bindLocal(target, state, constantInt(0));
}

void KernelSimulator::connect(Executor & executor, ExecutionState & state, KInstruction * target, std::vector<ref<Expr> > &arguments) {
  uint64_t sockfd;
  if (!exprToUInt64(arguments[1], sockfd)) {
    const char * message = "connect called with non-constant socket";
    klee_warning(message);
    executor.terminateStateOnError(state, message, Executor::User);
    return;
  }
  if (sockfd >= fileDescriptors.size()) {
    const char * message = "connect on non-existant file-descriptor";
    klee_warning(message);
    executor.terminateStateOnError(state, message, Executor::User);
    return;
  }
  FileDescriptor & fd = fileDescriptors[sockfd];
  if (fd.FDTType != FDT_socket) {
    const char * message = "connect on non-socket file descriptor";
    klee_warning(message);
    executor.terminateStateOnError(state, message, Executor::User);
    return;
  }
  // TODO check other arguments?
  executor.bindLocal(target, state, constantInt(0));
}

void KernelSimulator::open(Executor & executor, ExecutionState & state, KInstruction * target, std::vector<ref<Expr> > &arguments) {
  int fdidx = nextFreeFileDescriptor();
  FileDescriptor & fd = fileDescriptors[fdidx];
  fd.FDTType = FDT_file;
  if (!exprToInt(arguments[2], fd.flags)) {
    const char * message = "open called with non-constant flags";
    klee_warning(message);
    executor.terminateStateOnError(state, message, Executor::User);
    return;
  }
  executor.bindLocal(target, state, constantInt(fdidx));
}

void KernelSimulator::close(Executor & executor, ExecutionState & state, KInstruction * target, std::vector<ref<Expr> > &arguments) {
  uint64_t sockfd;
  if (!exprToUInt64(arguments[1], sockfd)) {
    const char * message = "close called with non-constant file-descriptor";
    klee_warning(message);
    executor.terminateStateOnError(state, message, Executor::User);
    return;
  }
  if (sockfd >= fileDescriptors.size()) {
    const char * message = "close on non-existant file-descriptor";
    klee_warning(message);
    executor.terminateStateOnError(state, message, Executor::User);
    return;
  }
  FileDescriptor & fd = fileDescriptors[sockfd];
  fd.FDTType = FDT_uninitialised;
  executor.bindLocal(target, state, constantInt(0));
}

void KernelSimulator::fstat(Executor & executor, ExecutionState & state, KInstruction * target, std::vector<ref<Expr> > &arguments) {
  uint64_t sockfd;
  if (!exprToUInt64(arguments[1], sockfd)) {
    const char * message = "fstat called with non-constant file-descriptor";
    klee_warning(message);
    executor.terminateStateOnError(state, message, Executor::User);
    return;
  }
  if (sockfd >= fileDescriptors.size()) {
    const char * message = "fstat on non-existant file-descriptor";
    klee_warning(message);
    executor.terminateStateOnError(state, message, Executor::User);
    return;
  }
  FileDescriptor & fd = fileDescriptors[sockfd];
  if (fd.FDTType != FDT_file) {
    const char * message = "fstat on non-file file-descriptor";
    klee_warning(message);
    executor.terminateStateOnError(state, message, Executor::User);
    return;
  }
  std::vector<ref<Expr> > make_symbolic_args;
  make_symbolic_args.push_back(arguments[2]);
  make_symbolic_args.push_back(ConstantExpr::create(sizeof(struct stat), Expr::Int64));
  executor.specialFunctionHandler->handleMakeNamedSymbolic(state, make_symbolic_args, "fstat");
  executor.bindLocal(target, state, constantInt(0));
}

void KernelSimulator::mmap(Executor & executor, ExecutionState & state, KInstruction * target, std::vector<ref<Expr> > &arguments) {
    const char * message = "mmap unsupported";
    klee_warning(message);
    executor.terminateStateOnError(state, message, Executor::User);
    return;
}

void KernelSimulator::getsockname(Executor & executor, ExecutionState & state, KInstruction * target, std::vector<ref<Expr> > &arguments) {
  uint64_t sockfd;
  if (!exprToUInt64(arguments[1], sockfd)) {
    const char * message = "getsockname called with non-constant socket";
    klee_warning(message);
    executor.terminateStateOnError(state, message, Executor::User);
    return;
  }
  if (sockfd >= fileDescriptors.size()) {
    const char * message = "getsockname on non-existant file-descriptor";
    klee_warning(message);
    executor.terminateStateOnError(state, message, Executor::User);
    return;
  }
  FileDescriptor & fd = fileDescriptors[sockfd];
  if (fd.FDTType != FDT_socket) {
    const char * message = "getsockname on non-socket file descriptor";
    klee_warning(message);
    executor.terminateStateOnError(state, message, Executor::User);
    return;
  }
  std::vector<ref<Expr> > make_symbolic_args;
  make_symbolic_args.push_back(arguments[2]);
  make_symbolic_args.push_back(0);

  ref<Expr> address = arguments[3];

  Executor::ExactResolutionList rl;
  executor.resolveExact(state, address, rl, "syscall_getsockname_size");
  for (Executor::ExactResolutionList::iterator it = rl.begin(),
         ie = rl.end(); it != ie; ++it) {
    const MemoryObject *mo = it->first.first;
    const ObjectState *os = it->first.second;
    ExecutionState *s = it->second;
    // Calculate the size
    int size = mo->size;
    int offset;
    if (!exprToInt(mo->getOffsetExpr(address), offset)) {
      const char * message = "getsockname with non-constant size of addrlen";
      klee_warning(message);
      executor.terminateStateOnError(state, message, Executor::User);
      return;
    }
    int bytes = size - offset;
    bytes = bytes > 8 ? 8 : bytes;
    Expr::Width type = bytes*8;
    make_symbolic_args[1] = os->read(offset, type);
    executor.specialFunctionHandler->handleMakeNamedSymbolic(*s, make_symbolic_args, "getsockname");
    //executor.specialFunctionHandler->handleMakeNamedSymbolic(s, make_address_symbolic_args, "getsockname::size");
    mo->setName("getsockname#size");
    executor.executeMakeSymbolic(*s, mo, "getsockname#size");
    executor.bindLocal(target, *s, constantInt(0));
    // TODO Also make the returned size symbolic
  }
}

void KernelSimulator::getcwd(Executor & executor, ExecutionState & state, KInstruction * target, std::vector<ref<Expr> > &arguments) {
  // TODO(oanson) Shouldn't getcwd always return the same thing?
  static unsigned id = 0;
  // Create array of size MAXPATH (cached)
  // copy from it at most <size> to <address>
  // Assume for now that size is constant
  ref<Expr> address = arguments[1];
  uint64_t size;
  if (!exprToUInt64(arguments[2], size)) {
    const char * message = "getcwd called with non-constant size";
    klee_warning(message);
    executor.terminateStateOnError(state, message, Executor::User);
    return;
  }
  Executor::ExactResolutionList rl;
  executor.resolveExact(state, address, rl, "getcwd_destination_buffer");
  for (Executor::ExactResolutionList::iterator it = rl.begin(),
                                               ie = rl.end(); it != ie; ++it) {
    const Array *array = executor.arrayCache.CreateArray("syscall::getcwd/" + llvm::utostr(++id), size);
    UpdateList ul(array, 0);
    const MemoryObject *mo = it->first.first;
    const ObjectState *os = it->first.second;
    ExecutionState *s = it->second;
    ObjectState *wos = s->addressSpace.getWriteable(mo, os);
    // TODO(oanson) This definitely can be optimised
    for (unsigned offset = 0; offset < size; offset++) {
      ref<Expr> value = ReadExpr::create(ul, constantInt32(offset));
      wos->write(offset, value);
    }
    mo->setName("getcwd");
    s->addSymbolic(mo, array);
    executor.bindLocal(target, *s, constantInt(0));
  }
}

void KernelSimulator::getuid(Executor & executor, ExecutionState & state, KInstruction * target, std::vector<ref<Expr> > &arguments) {
  ref<Expr> result;
  executor.createSymbolicValue(64, "getuid", result);
  executor.bindLocal(target, state, result);
}

void KernelSimulator::getpid(Executor & executor, ExecutionState & state, KInstruction * target, std::vector<ref<Expr> > &arguments) {
  ref<Expr> result;
  executor.createSymbolicValue(64, "getpid", result);
  executor.bindLocal(target, state, result);
}

void KernelSimulator::write(Executor & executor, ExecutionState & state, KInstruction * target, std::vector<ref<Expr> > &arguments) {
  uint64_t sockfd;
  if (!exprToUInt64(arguments[1], sockfd)) {
    const char * message = "write called with non-constant socket";
    klee_warning(message);
    executor.terminateStateOnError(state, message, Executor::User);
    return;
  }
  if (sockfd >= fileDescriptors.size()) {
    const char * message = "write on non-existant file-descriptor";
    klee_warning(message);
    executor.terminateStateOnError(state, message, Executor::User);
    return;
  }
  FileDescriptor & fd = fileDescriptors[sockfd];
  if (fd.FDTType == FDT_uninitialised) {
    const char * message = "write on uninitialised file descriptor";
    klee_warning(message);
    executor.terminateStateOnError(state, message, Executor::User);
    return;
  }
  // Printing to stdout and stderr if requested. XXX This is buggy and insecure
  uint64_t size;
  if (!exprToUInt64(arguments[3], size)) {
    const char * message = "write called with non-constant size";
    klee_warning(message);
    executor.terminateStateOnError(state, message, Executor::User);
    return;
  }
  if ((sockfd == 1) || (sockfd == 2)) {
    char * buf = (char*)alloca(size);
    if (!readDataAtAddress(executor, state, arguments[2], buf, size)) {
      const char * message = "write failed to get buffer";
      klee_warning(message);
      executor.terminateStateOnError(state, message, Executor::User);
      return;
    }
    int written = ::write(sockfd, buf, size);
    executor.bindLocal(target, state, constantInt(written));
    return;
  }
  executor.bindLocal(target, state, constantInt(size));
  return; // TODO(oanson) should be randomly less than size too

}

void KernelSimulator::writev(Executor & executor, ExecutionState & state, KInstruction * target, std::vector<ref<Expr> > &arguments) {
  uint64_t sockfd;
  if (!exprToUInt64(arguments[1], sockfd)) {
    const char * message = "writev called with non-constant socket";
    klee_warning(message);
    executor.terminateStateOnError(state, message, Executor::User);
    return;
  }
  if (sockfd >= fileDescriptors.size()) {
    const char * message = "writev on non-existant file-descriptor";
    klee_warning(message);
    executor.terminateStateOnError(state, message, Executor::User);
    return;
  }
  FileDescriptor & fd = fileDescriptors[sockfd];
  if (fd.FDTType == FDT_uninitialised) {
    const char * message = "writev on uninitialised file descriptor";
    klee_warning(message);
    executor.terminateStateOnError(state, message, Executor::User);
    return;
  }
  uint64_t iovcnt;
  if (!exprToUInt64(arguments[2], iovcnt)) {
    const char * message = "writev called with non-constant iovcnt";
    klee_warning(message);
    executor.terminateStateOnError(state, message, Executor::User);
    return;
  }

  int written = 0;
  // Printing to stdout and stderr if requested. XXX This is buggy and insecure
  if ((sockfd == 1) || (sockfd == 2)) {
    ref<Expr> iov;
    if (!simpleReadUniquePointer(executor, state, arguments[2], Context::get().getPointerWidth(), iov)) {
      const char * message = "writev failed to get iov";
      klee_warning(message);
      executor.terminateStateOnError(state, message, Executor::User);
      return;
    }
    for (unsigned index = 0; index < iovcnt; index++) {
      // get len
      ref<Expr> lenPtr = AddExpr::create(iov, constantInt(Context::get().getPointerWidth()));
      ref<Expr> len;
      if (!simpleReadUniquePointer(executor, state, lenPtr, 64, len)) {
        const char * message = "writev failed to get iov len";
        klee_warning(message);
        executor.terminateStateOnError(state, message, Executor::User);
        return;
      }
      uint64_t len_u64;
      if (!exprToUInt64(len, len_u64)) {
        const char * message = "writev failed to get iov len (2)";
        klee_warning(message);
        executor.terminateStateOnError(state, message, Executor::User);
        return;
      }
      // read it
      char * buf = (char*)alloca(len_u64);
      if (!readDataAtAddress(executor, state, iov, buf, len_u64)) {
        const char * message = "writev failed to get iov data";
        klee_warning(message);
        executor.terminateStateOnError(state, message, Executor::User);
        return;
      }
      // write it
      written += ::write(sockfd, buf, len_u64);
      // get next address
      iov = AddExpr::create(iov, constantInt(sizeof(struct iovec)));
    }
  }
  executor.bindLocal(target, state, constantInt(written));
}

void KernelSimulator::prlimit64(Executor & executor, ExecutionState & state, KInstruction * target, std::vector<ref<Expr> > &arguments) {
// In this special case, we return concrete data regarding what KLEE allows. (maybe)
// Params: pid, resource, new (IN), old (OUT),
// pid must be 0 or this pid
// then, if old is given, call getrlimit(resource, old)
// 	if new is given, call setrlimit(resource, new)
// return
  uint64_t pid;
  if (!exprToUInt64(arguments[1], pid)) {
    const char * message = "prlimit64 failed to get pid";
    klee_warning(message);
    executor.terminateStateOnError(state, message, Executor::User);
    return;
  }
  if (pid != 0) /*|| (solve(EqExpr::create(pid, getpid())))*/ {
    executor.bindLocal(target, state, constantInt(-1));
    return; // TODO(oanson) and bind the correct error (call ForkAndFail)
  }
  uint64_t resource;
  if (!exprToUInt64(arguments[2], resource)) {
    const char * message = "prlimit64 failed to get resource";
    klee_warning(message);
    executor.terminateStateOnError(state, message, Executor::User);
    return;
  }
  if (_getrlimit(executor, state, resource, arguments[4]) == -1) {
    return;
  }
  if (_setrlimit(executor, state, resource, arguments[3]) == -1) {
    return;
  }
  executor.bindLocal(target, state, constantInt(0));
}

void KernelSimulator::getrlimit(Executor & executor, ExecutionState & state, KInstruction * target, std::vector<ref<Expr> > &arguments) {
  uint64_t resource;
  if (!exprToUInt64(arguments[1], resource)) {
    const char * message = "getrlimit failed to get resource";
    klee_warning(message);
    executor.terminateStateOnError(state, message, Executor::User);
    return;
  }
  _getrlimit(executor, state, resource, arguments[2]);
  executor.bindLocal(target, state, constantInt(0));
}

void KernelSimulator::setrlimit(Executor & executor, ExecutionState & state, KInstruction * target, std::vector<ref<Expr> > &arguments) {
  uint64_t resource;
  if (!exprToUInt64(arguments[1], resource)) {
    const char * message = "setrlimit failed to get resource";
    klee_warning(message);
    executor.terminateStateOnError(state, message, Executor::User);
    return;
  }
  _setrlimit(executor, state, resource, arguments[2]);
  executor.bindLocal(target, state, constantInt(0));
}

int KernelSimulator::_getrlimit(Executor & executor, ExecutionState & state,
		uint64_t resource, ref<Expr> pointer) {
  rlim_t soft = RLIM_INFINITY;
  rlim_t hard = RLIM_INFINITY;
  if (resource == RLIMIT_NOFILE) {
    // Special handling.
    soft = 1024;
    hard = 1024;
  }

  Executor::ExactResolutionList rl;
  executor.resolveExact(state, pointer, rl, "getrlimit");
  for (Executor::ExactResolutionList::iterator it = rl.begin(),
                                               ie = rl.end(); it != ie; ++it) {

    const MemoryObject *mo = it->first.first;
    const ObjectState *os = it->first.second;
    ExecutionState *s = it->second;
    ObjectState *wos = s->addressSpace.getWriteable(mo, os);
    wos->write(0, constantInt(soft));
    wos->write(sizeof(rlim_t), constantInt(hard));
  }
  return 0;
}

int KernelSimulator::_setrlimit(Executor & executor, ExecutionState & state, uint64_t resource, ref<Expr> pointer) {
  // Do nothing
  return 0;
}

void KernelSimulator::exit(Executor & executor, ExecutionState & state, KInstruction * target, std::vector<ref<Expr> > &arguments) {
  executor.terminateStateOnExit(state);
}

void KernelSimulator::setsid(Executor & executor, ExecutionState & state, KInstruction * target, std::vector<ref<Expr> > &arguments) {
  ref<Expr> result;
  executor.createSymbolicValue(64, "setsid", result);
  executor.bindLocal(target, state, result);
}
}
