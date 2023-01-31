
PWD := /home/nabin/Data/.archives/sfml/TicTacToe
SRC_DIR := $(PWD)/src
BUILD_DIR := $(PWD)/build
INCLUDE_DIR := $(PWD)/include
CC := g++
CFLAGS := -lpthread -lglfw -lGL -lsfml-graphics -lsfml-network -lsfml-audio -lsfml-window -lsfml-system -lX11
FILE := /home/nabin/Data/.archives/sfml/TicTacToe/main.cpp

EXECUTABLE := main

SRC_FILES :=  $(wildcard $(SRC_DIR)/*.cpp) 

OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

$(EXECUTABLE):$(FILE) $(OBJ_FILES)
	$(CC) $(FILE) $(OBJ_FILES)  -I$(INCLUDE_DIR) -o $(BUILD_DIR)/$(EXECUTABLE)  $(CFLAGS)


$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CC)  -I$(INCLUDE_DIR) -c $< -o $@  $(CFLAGS)


run:
	$(BUILD_DIR)/$(EXECUTABLE) 
	
clean:
	rm -r $(BUILD_DIR)/


