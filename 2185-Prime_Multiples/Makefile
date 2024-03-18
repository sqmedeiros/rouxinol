export PROBLEM = 2185-HPTHINK-training
export CPPFLAGS = -DONLINE_JUDGE -std=c++17 -O2
export OUTPUT = > /dev/null 2>&1
export TEST = ../test/entry02.txt ../test/entry03.txt

all:
	#+$(MAKE) -C rand
	+$(MAKE) -C training
	#+$(MAKE) -C control

clean:
	rm rand/*.exe training/*.exe control/*.exe
