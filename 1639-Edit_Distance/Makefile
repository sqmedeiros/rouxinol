export PROBLEM = 1639-HPTHINK-training
export CPPFLAGS = -DONLINE_JUDGE -std=c++17 -O2
export OUTPUT = > /dev/null 2>&1
export TEST = ../test/entry06.txt ../test/entry07.txt ../test/entry08.txt ../test/entry09.txt ../test/entry10.txt ../test/entry11.txt ../test/entry15.txt

all:
	#+$(MAKE) -C rand
	+$(MAKE) -C training
	#+$(MAKE) -C control

clean:
	rm rand/*.exe fast/*.exe control/*.exe
