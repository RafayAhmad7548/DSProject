CXX = g++

CXXFLAGS = -I./include -I/usr/include/qt6 -I/usr/include/qt6/QtWidgets -I/usr/include/qt6/QtGui -I/usr/include/qt6/QtCore -Wall -std=c++23 -g -fPIC

LDFLAGS = -L/usr/lib -lQt6Widgets -lQt6Gui -lQt6Core

SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)
EXEC = project

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(EXEC) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)