export PROBLEM = 1635-HPTHINK-slow-time
export CPPFLAGS = -DONLINE_JUDGE -std=c++17 -O2
export OUTPUT = > /dev/null 2>&1
export TEST = ../test/entry04.txt ../test/entry05.txt ../test/entry08.txt ../test/entry11.txt ../test/entry12.txt

all:
	+$(MAKE) -C all 
	#+$(MAKE) -C training
	#+$(MAKE) -C control

clean:
	rm all/*.exe training/*.exe control/*.exe
