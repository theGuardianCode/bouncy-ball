FILES = main.c

all: $(FILES)
	gcc $(FILES) -o bouncy -w -lSDL2
