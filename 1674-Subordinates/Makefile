export PROBLEM = 1674-HPTHINK-rand
export CPPFLAGS = -DONLINE_JUDGE -std=c++17 -O2
export OUTPUT = > /dev/null 2>&1
export TEST = ../test/entry04.txt ../test/entry05.txt ../test/entry06.txt ../test/entry10.txt ../test/entry12.txt

all:
	+$(MAKE) -C rand
	#+$(MAKE) -C training
	#+$(MAKE) -C control

clean:
	rm rand/*.exe training/*.exe control/*.exe
