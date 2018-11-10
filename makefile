src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)
CC = g++
LDFLAGS = -std=c++11 -g
OFLAGS = -std=c++11 -g

all : jarra

test : jarra
	python tests.py

jarra: $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)


%.o: %.cpp
	$(CC) -o $@ -c $< $(OFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) jarra