BASE=$(patsubst %.c,%,$(wildcard *.c))
KCFLAGS=-I../../../include
#CFLAGS=-g -fpic -Wall -Werror
CFLAGS=-g -fpic -Wall
CXXFLAGS=

KLDFLAGS=-L/home/oanson/projects/klee/Release+Asserts/lib
LDFLAGS=
CXXLDFLAGS=


CC=musl-clang
CXX=musl-clang++
LD=musl-clang

OBJS=$(foreach f,${BASE},${f}.o)
BC_OBJS=$(foreach f,${BASE},.${f}.o.bc)
ALL=autostubs.so.bc

all: ${ALL}

%.o: %.c
	${CC} -c ${KCFLAGS} ${CFLAGS} $^ -o $@

%.o: %.cpp
	${CXX} -c ${KCFLAGS} ${CXXFLAGS} ${CFLAGS} $^ -o $@

autostubs.so: ${OBJS}
	${LD} -shared -o $@ ${OBJS}

%.bc: %
	extract-bc $^

%.ll: %.bc
	llvm-dis $^ > $@

clean:
	rm -f ${ALL} autostubs.so ${OBJS} ${BC_OBJS}
