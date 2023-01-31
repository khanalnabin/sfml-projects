
SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include
CC := g++
CFLAGS := -lsfml-system -lsfml-window -lsfml-graphics 

EXECUTABLE := main

SOURCES :=  $(wildcard $(SRC_DIR)/*.cpp) 

OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

OBJ_FILES := $(OBJECTS)

build:$(EXECUTABLE)

run: 
	$(BUILD_DIR)/$(EXECUTABLE) 

$(EXECUTABLE):$(OBJECTS)
	$(CC) $(OBJECTS)  -I$(INCLUDE_DIR) -o $(BUILD_DIR)/$(EXECUTABLE)  $(CFLAGS)

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CC)  -I$(INCLUDE_DIR) -c $< -o $@  $(CFLAGS)


clean:
	rm -r $(BUILD_DIR)/*



