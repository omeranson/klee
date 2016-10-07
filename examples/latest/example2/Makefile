KCFLAGS=-I/home/oanson/opt/klee-install/include
CFLAGS=-g
CXXFLAGS=

KLDFLAGS=/home/oanson/projects/klee/Release+Asserts/lib/ofiles/KTest.o -L/home/oanson/projects/klee/Release+Asserts/lib -lkleeRuntest
LDFLAGS=
CXXLDFLAGS=

BASE=figure6
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
