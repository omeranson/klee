#export PATH=$HOME/opt/klee-env/bin:$HOME/projects/klee/Release+Asserts/bin:$HOME/opt/llvm-install/bin:$PATH
export PATH=$HOME/opt/klee-env/bin:$HOME/projects/klee_summarisation/Release+Asserts/bin:$HOME/opt/llvm-install/bin:$PATH
export LD_LIBRARY_PATH=$HOME/opt/klee-env/lib:$LD_LIBRARY_PATH
export LLVM_COMPILER=clang
export LLVM_COMPILER_PATH=/usr/bin
export CC=musl-clang
export CXX=musl-clang++
unset COMPILE_STD_LIBC
