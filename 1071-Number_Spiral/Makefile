export PROBLEM = 1071-HPELITE-TESTE
export CPPFLAGS = -DONLINE_JUDGE -std=c++17 -O2
export OUTPUT = > /dev/null 2>&1
export TEST = ../test/entry01.txt ../test/entry02.txt

all:
	+$(MAKE) -C training
	#+$(MAKE) -C control

clean:
	rm training/*.exe control/*.exe
