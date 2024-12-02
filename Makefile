CXX = g++

CXXFLAGS = -I./include -Wall -std=c++23 -g

SRCS = $(wildcard src/*.cpp)

OBJS = $(SRCS:.cpp=.o)

EXEC = project

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(EXEC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)