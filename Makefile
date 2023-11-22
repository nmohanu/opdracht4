BUILD_DIR=build

.PHONY: always clean main.o board.o

$(BUILD_DIR)/gomoku: $(BUILD_DIR)/main.o $(BUILD_DIR)/board.o
	g++ -o $(BUILD_DIR)/gomoku $(BUILD_DIR)/main.o $(BUILD_DIR)/board.o

main.o: $(BUILD_DIR)/main.o always

$(BUILD_DIR)/main.o: main.cpp
	g++ -o $(BUILD_DIR)/main.o -c main.cpp

board.o: $(BUILD_DIR)/board.o always

$(BUILD_DIR)/board.o: board.cpp
	g++ -o $(BUILD_DIR)/board.o -c board.cpp

#
# Always
#
always:
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)/*
