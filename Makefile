
CCPP    = g++ -std=c++0x
CFLAGS  = -O3 -Wall -pedantic
LDFLAGS = 
INCLUDES = -Iinclude

all: trafficSimulator

trafficSimulator: main.cpp
	$(CCPP) $(CFLAGS) $^ -o $@ $(INCLUDES) $(LDFLAGS)

clean:
	rm -rf trafficSimulator
