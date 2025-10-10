CC = gcc
CFLAGS = `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs`
SRC = ./gui/GUI.c
OUT = front

$(OUT): $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(LDFLAGS) -o $(OUT)
	@echo "Compiled GUI successfully."

clean:
	rm -f $(OUT)
