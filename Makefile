BUILD_DIR=build

.PHONY: always clean main.o board.o stack.o

$(BUILD_DIR)/gomoku: main.o board.o stack.o
	g++ -o $(BUILD_DIR)/gomoku $(BUILD_DIR)/main.o $(BUILD_DIR)/board.o $(BUILD_DIR)/stack.o

main.o: $(BUILD_DIR)/main.o always

$(BUILD_DIR)/main.o: main.cpp
	g++ -o $(BUILD_DIR)/main.o -c main.cpp

board.o: $(BUILD_DIR)/board.o always

$(BUILD_DIR)/board.o: board.cpp
	g++ -o $(BUILD_DIR)/board.o -c board.cpp

stack.o: $(BUILD_DIR)/stack.o always

$(BUILD_DIR)/stack.o: stack.cpp
	g++ -o $(BUILD_DIR)/stack.o -c stack.cpp

#
# Always
#
always:
	mkdir -p $(BUILD_DIR)

clean: