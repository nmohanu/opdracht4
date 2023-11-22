BUILD_DIR=build

.PHONY: always clean

$(BUILD_DIR)/gomoku: $(BUILD_DIR)/main.o $(BUILD_DIR)/board.o
	g++ -o $(BUILD_DIR)/gomoku $(BUILD_DIR)/main.o $(BUILD_DIR)/board.o

$(BUILD_DIR)/main.o: always
	g++ -o $(BUILD_DIR)/main.o -c main.cc

$(BUILD_DIR)/board.o: always
	g++ -o $(BUILD_DIR)/board.o -c board.cc

#
# Always
#
always:
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)/*