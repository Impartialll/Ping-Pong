TODO:
+ include raylib.h in game.h only
+ Move all structs in game.h
- Move raygui.h into game.h
+ Refactor main_loop to pass the pointers
- Check all the raylib functions for duplicates (BeginDrawing etc)
- Members(var/structs) from start_menu.c must move to game.h
+ ESC should not close the game, but back to main menu
- Refactor Popup window state logic using Enums
- Refactor PopupWelcome members into struct
- Refactor PopIPSettingsmembers into struct
+ Clean commented code
- Fix configure.sh script for WSL
