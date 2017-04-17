BASE=test_getrandom
KCFLAGS=-I/home/oanson/opt/klee-install/include
CFLAGS=-g
CXXFLAGS=

KLDFLAGS=-L/home/oanson/projects/klee/Release+Asserts/lib
LDFLAGS=
CXXLDFLAGS=

OBJS=${BASE}.o

CC=musl-clang
CXX=musl-clang++
LD=musl-clang

ALL=${BASE} ${BASE}.bc ${BASE}.ll

all: ${ALL}

${BASE}: ${OBJS}
	${LD} ${KLDFLAGS} ${CXXLDFLAGS} ${LDFLAGS} $^ -o $@

%.o: %.c
	${CC} -c ${KCFLAGS} ${CFLAGS} $^ -o $@

%.o: %.cpp
	${CXX} -c ${KCFLAGS} ${CXXFLAGS} ${CFLAGS} $^ -o $@

%.bc: %
	extract-bc $^

%.ll: %.bc
	llvm-dis $^ > $@

clean:
	rm -f ${ALL}
