#!/bin/bash

ulimit -c unlimited
#ulimit -m 524288

timeout 2h klee -use-LATEST-algorithm -output-dir=klee-out-LATEST ./parse-http-request-line.bc

timeout 2h klee -output-dir=klee-out-VANILA ./parse-http-request-line.bc

