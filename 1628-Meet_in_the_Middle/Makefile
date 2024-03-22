export PROBLEM = 1628-HPTHINK-rand
export CPPFLAGS = -DONLINE_JUDGE -std=c++17 -O2
export OUTPUT = > /dev/null 2>&1
export TEST = ../test/entry08.txt ../test/entry22.txt ../test/entry23.txt ../test/entry24.txt ../test/entry27.txt ../test/entry28.txt ../test/entry30.txt ../test/entry31.txt ../test/entry32.txt ../test/entry33.txt ../test/entry34.txt ../test/entry35.txt ../test/entry36.txt ../test/entry37.txt ../test/entry38.txt ../test/entry39.txt ../test/entry40.txt

all:
	+$(MAKE) -C rand
	#+$(MAKE) -C training
	#+$(MAKE) -C control

clean:
	rm rand/*.exe training/*.exe control/*.exe
