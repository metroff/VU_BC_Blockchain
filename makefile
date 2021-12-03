SRC_DIR := ./include
OBJ_DIR := ./
CPPFLAGS := -O3 -std=c++11 -fopenmp
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

main: $(OBJ_FILES)
	g++ $(CPPFLAGS) main.cpp include/*.cpp -o main $(shell pkg-config --cflags --libs libbitcoin-system)

#-o $@ $^
# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
# 	g++ $(CPPFLAGS) -c $(shell pkg-config --cflags --libs libbitcoin-system) -o $@ $<
clean_all:
	rm $(OBJ_DIR)/*.o main
clean_obj:
	rm $(OBJ_DIR)/*.o
clean:
	rm main