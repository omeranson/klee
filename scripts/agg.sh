#!/bin/bash

FILTER=$1
shift
PROGRAMMES=$*

# To remove injected lines after __user_main (klee-vanilla)
# find -name run.istats -exec sed -i -e '/^fn=__user_main$/{n;N;N;N;N;N;N;N;N;N;N;d}' {} \;
# To rename main -> __user_main (klee-sesyscalls)
# find -name run.istats -exec sed -i 's/^fn=main$/fn=__user_main/' {} \;
for i in $PROGRAMMES; do
	#FILE1="coreutils-8.27/src/klee/$i/klee-out-0/run.istats"
	#FILE2="coreutils-8.27/src/klee-vanilla/$i/klee-out-0/run.istats"
	#FILE1="inetutils-1.9.4-orig2/klee/$i/klee-out-0/run.istats"
	#FILE2="inetutils-1.9.4-orig2/klee-vanilla-old/$i/klee-out-0/run.istats"
	#FILE1="ntp/klee/$i/klee-out-0/run.istats"
	#FILE2="ntp/klee-vanilla/$i/klee-out-0/run.istats"
	#FILE1="dnsmasq/klee/$i/klee-out-0/run.istats"
	#FILE2="dnsmasq/klee-vanilla/$i/klee-out-0/run.istats"
	#FILE1="dhcp/klee/$i/klee-out-0/run.istats"
	#FILE2="dhcp/klee-vanilla/$i/klee-out-0/run.istats"
	FILE1="bind/klee/$i/klee-out-0/run.istats"
	FILE2="bind/klee-vanilla/$i/klee-out-0/run.istats"
	echo -n "$i "
	./agg-files.pl $FILTER $FILE1 $FILE2
done

