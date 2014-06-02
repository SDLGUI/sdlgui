CFLAG = -I/usr/local/include
name=test.cpp
bin=.
SDLGUI_DIR=./sdlgui
LIBS = -L/usr/local/lib -lSDL2_image -lSDL2_gfx -lSDL2_ttf -lSDL2main -lSDL2
WINLIBS = -L/usr/local/lib -lSDL2_image -lSDL2_image.dll -lSDL2_gfx -lSDL2_draw -lmingw32 -lSDL2_ttf -lSDL2_ttf.dll -lSDL2_mixer -lSDL2_mixer.dll -lSDL2main -lSDL2 -lSDL2.dll 
ALL:
	rm -f $(bin)/$(name).exe 
	make $(bin)/$(name).exe
$(bin)/$(name).exe : $(name) $(SDLGUI_DIR)/sdlbase.h $(SDLGUI_DIR)/sdlwindow.h $(SDLGUI_DIR)/sdltools.h $(SDLGUI_DIR)/sdlgui.h
	mkdir -p $(bin)
	g++ -g $(name) -o $(bin)/$(name).exe $(CFLAG) $(WINLIBS)
	$(bin)/$(name).exe
UBUNTU : test.cpp sdlgui.h sdlbase.h sdlwindow.h sdltools.h
	g++ -g test.cpp sdlbase.h sdlwindow.h sdltools.h -o exe $(CFLAG) $(LIBS)
	./exe
