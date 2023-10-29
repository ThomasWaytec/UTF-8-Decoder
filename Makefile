CC = gcc
CFLAGS = 
LDFLAGS = -lm

SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_DIR = obj
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

TARGET = utf8

ifeq ($(OS),Windows_NT)
	CLEAN_CMD = powershell -noprofile rm -force
else
	CLEAN_CMD = rm -f
endif

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $< $(LDFLAGS)

clean:
	$(CLEAN_CMD) $(OBJ_DIR)/*
	$(CLEAN_CMD) $(TARGET)*
