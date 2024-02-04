CC = g++
FLAGS = -std=c++17 -Wall -Wextra -pedantic
TARGET = main
SRC = $(shell find . -name "*.cpp")
SFML = -lsfml-graphics -lsfml-window -lsfml-system

$(TARGET): $(SRC)
	$(CC) $(FLAGS) -o $(TARGET) $(SRC) $(SFML)