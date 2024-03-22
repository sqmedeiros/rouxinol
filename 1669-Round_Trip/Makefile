export PROBLEM = 1669-HPTHINK-rand
export CPPFLAGS = -DONLINE_JUDGE -std=c++17 -O2
export OUTPUT = > /dev/null 2>&1
export TEST = ../test/entry06.txt ../test/entry07.txt ../test/entry08.txt ../test/entry09.txt ../test/entry10.txt ../test/entry16.txt

all:
	+$(MAKE) -C rand
	#+$(MAKE) -C training
	#+$(MAKE) -C control

clean:
	rm rand/*.exe training/*.exe control/*.exe
