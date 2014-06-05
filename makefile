CFLAG = -I/usr/local/include
name=test.cpp
bin=.
SDLGUI_DIR=./sdlgui
LIBS = -L/usr/local/lib -lSDL2_image -lSDL2_gfx -lSDL2_ttf -lSDL2main -lSDL2
WINLIBS = -L/usr/local/lib -lSDL2_image -lSDL2_image.dll -lSDL2_gfx -lSDL2_draw -lmingw32 -lSDL2_ttf -lSDL2_ttf.dll -lSDL2_mixer -lSDL2_mixer.dll -lSDL2main -lSDL2 -lSDL2.dll 
ALL:
	rm -f $(bin)/$(name).exe 
	make windows 
windows : $(name) $(SDLGUI_DIR)/sdlbase.h $(SDLGUI_DIR)/sdlwindow.h $(SDLGUI_DIR)/sdltools.h $(SDLGUI_DIR)/sdlgui.h
	mkdir -p $(bin)
	g++ -Wall -g $(name) -o $(bin)/$(name).exe $(CFLAG) $(WINLIBS)
	$(bin)/$(name).exe
ubuntu: $(SDLGUI_DIR)/test.cpp $(SDLGUI_DIR)/sdlgui.h $(SDLGUI_DIR)/sdlbase.h $(SDLGUI_DIR)/sdlwindow.h $(SDLGUI_DIR)/sdltools.h
	mkdir -p $(bin)
	g++ -Wall -g $(name) -o $(bin)/$(name).exe $(CFLAG) $(LIBS)
	$(bin)/$(name).exe
