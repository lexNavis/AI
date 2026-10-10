CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -g
TARGET   := app
SRCS     := main.cpp search/DFS.cpp search/BFS.cpp tree/Tree.cpp search/AStar.cpp tree/TreeGenerator.cpp game/Minimax.cpp game/AlphaBeta.cpp experiments/Experiment.cpp
HEADERS  := $(wildcard tree/*.h search/*.h)

all: $(TARGET)

$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean