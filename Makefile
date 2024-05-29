SRC_DIR=src
BUILD_DIR=build

.PHONY: build

build: $(SRC_DIR)/main.cpp
	g++ $(SRC_DIR)/*.cpp -o terasm.exe