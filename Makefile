BUILD_DIR = build
EXECUTABLE = $(BUILD_DIR)/gomoku

SOURCES = main.cpp board.cpp stack.cpp
OBJECTS = $(addprefix $(BUILD_DIR)/, $(SOURCES:.cpp=.o))

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: %.cpp | always
	$(CXX) $(CXXFLAGS) -o $@ -c $<

always:
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean always
