export PROBLEM = 1667-HPTHINK-rand
export CPPFLAGS = -DONLINE_JUDGE -std=c++17 -O2
export OUTPUT = > /dev/null 2>&1
export TEST = ../test/entry06.txt ../test/entry07.txt ../test/entry08.txt ../test/entry09.txt ../test/entry10.txt ../test/entry12.txt

all:
	+$(MAKE) -C all
	#+$(MAKE) -C training
	#+$(MAKE) -C control

clean:
	rm all/*.exe training/*.exe control/*.exe
