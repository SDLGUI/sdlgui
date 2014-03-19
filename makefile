CFLAG = -I/usr/local/include
LIBS = -L/usr/local/lib -lSDL2_image -lSDL2_image.dll -lSDl2_gfx -lSDL2_draw -lmingw32 -lSDL2_ttf -lSDL2_ttf.dll -lSDL2main -lSDL2 -lSDL2.dll 
ALL:
	rm *.exe
	make test.exe
test.exe : test.cpp
	g++ -g test.cpp -o test.exe $(CFLAG) $(LIBS)
	./test
