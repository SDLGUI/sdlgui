#include <SDL2/SDL.h>
#include "sdlthread.h"
#ifdef __SDLGUI_THREAD_HEAD__
def_dll sdl_semaphore::sdl_semaphore()
{
	init();
}
def_dll sdl_semaphore::sdl_semaphore(int d)
{
	init(d);
}
def_dll sdl_semaphore::~sdl_semaphore()
{
	destroy();
}
def_dll int sdl_semaphore::init()
{
	_semaphore = NULL;
}
def_dll int sdl_semaphore::init(int d)
{
	destroy();
	_semaphore = SDL_CreateSemaphore(d);
	if(_semaphore)return 0;
	return -1;
}
def_dll int sdl_semaphore::destroy()
{
	if(_semaphore)
	{
		SDL_DestroySemaphore(_semaphore);
		_semaphore = NULL;
		return 0;
	}
	return -1;
}
def_dll int sdl_semaphore::wait()
{
	return SDL_SemWait(_semaphore);
}
def_dll int sdl_semaphore::post()
{
	return SDL_SemPost(_semaphore);
}
def_dll Uint32 sdl_semaphore::value()
{
	return SDL_SemValue(_semaphore);
}
def_dll int sdl_semaphore::try_wait()
{
	return SDL_SemTryWait(_semaphore);
}
def_dll int sdl_semaphore::wait_timeout(Uint32 ms)
{
	return SDL_SemWaitTimeout(_semaphore,ms);
}
#endif //__SDLGUI_THREAD_HEAD__
