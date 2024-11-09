PROJECT_NAME:=raygui_research
SRC:=main.c screen_logo.c screen_title.c screen_options.c screen_gameplay.c screen_ending.c
CC:=clang
CFLAGS:=-Wall -lm

$(PROJECT_NAME):
	$(CC) $(CFLAGS) $(shell pkg-config --libs --cflags raylib) $(SRC) -o $(PROJECT_NAME)

.PHONY: start
start: clear $(PROJECT_NAME)
	XDG_RUNTIME_DIR=/run/user/$$UID ./$(PROJECT_NAME)

.PHOMY: clear
clear:
	rm -vf $(PROJECT_NAME)
