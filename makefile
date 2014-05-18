CFLAG = -I/usr/local/include
LIBS = -L/usr/local/lib -lSDL2_image -lSDL2_gfx -lSDL2_ttf -lSDL2main -lSDL2
WINLIBS = -L/usr/local/lib -lSDL2_image -lSDL2_image.dll -lSDL2_gfx -lSDL2_draw -lmingw32 -lSDL2_ttf -lSDL2_ttf.dll -lSDL2_mixer -lSDL2_mixer.dll -lSDL2main -lSDL2 -lSDL2.dll 
ALL:
	rm exe* 
	make exe
test.exe : test.cpp sdlgui.h sdlbase.h sdlwindow.h sdltools.h
	g++ -g test.cpp sdlbase.h sdlwindow.h sdltools.h -o exe.exe $(CFLAG) $(WINLIBS)
	./exe
UBUNTU : test.cpp sdlgui.h sdlbase.h sdlwindow.h sdltools.h
	g++ -g test.cpp sdlbase.h sdlwindow.h sdltools.h -o exe $(CFLAG) $(LIBS)
	./exe
