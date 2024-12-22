CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -lcurl -lcjson

SRC = src/main.c src/display.c src/http.c src/json_parser.c src/utility.c
OBJ = $(SRC:.c=.o)
TARGET = sky_scanner

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o  $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
