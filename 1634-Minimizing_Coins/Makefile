export PROBLEM = 1634-HPTHINK-training
export CPPFLAGS = -DONLINE_JUDGE -std=c++17 -O2
export OUTPUT = > /dev/null 2>&1
export TEST = ../test/entry04.txt ../test/entry05.txt ../test/entry08.txt ../test/entry09.txt ../test/entry11.txt

all:
	#+$(MAKE) -C rand
	+$(MAKE) -C training
	#+$(MAKE) -C control

clean:
	rm rand/*.exe training/*.exe control/*.exe
