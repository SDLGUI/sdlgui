#include <SDL2/SDL.h>
#include "sdlthread.h"
#ifdef __SDLGUI_THREAD_HEAD__
//--------------------------------------------------
//
//
//
//
//
//
//
//
//--------------------------------------------------
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
//-----------------------------------------------------------------
//
//
//
//
//
//					互斥体对象实现
//
//
//
///
//-----------------------------------------------------------------
def_dll sdl_mutex::sdl_mutex()
{
	_mutex = NULL;
	create();
}
def_dll sdl_mutex::~sdl_mutex()
{
	destroy();
}
def_dll int sdl_mutex::create()
{
	destroy();
	_mutex = SDL_CreateMutex();
	if(_mutex)return 0;
	return -1;
}
def_dll int sdl_mutex::destroy()
{
	if(_mutex)
	{
		SDL_DestroyMutex(_mutex);
		_mutex = NULL;
	}
	return 0;
}
def_dll int sdl_mutex::lock()
{
	return SDL_LockMutex(_mutex);
}
def_dll int sdl_mutex::unlock()
{
	return SDL_UnlockMutex(_mutex);
}
def_dll int sdl_mutex::try_lock()
{
	return SDL_TryLockMutex(_mutex);
}
//----------------------------------------------------------
//
//
//
//
//			条件变量
//
//
//
//------------------------------------------------------------
def_dll sdl_condition::sdl_condition()
{
	_condition = NULL;
	create();
}
def_dll sdl_condition::~sdl_condition()
{
	destroy();
}
def_dll int sdl_condition::create()
{
	destroy();
	_condition = SDL_CreateCond();
	if(_condition)return 0;
	return -1;
}
def_dll int sdl_condition::destroy()
{
	if(_condition)
	{
		SDL_DestroyCond(_condition);
		return 0;
	}
	return -1;
}
def_dll int sdl_condition::wait(sdl_mutex* p)
{
	if(p)
	{
		return SDL_CondWait(_condition,p->_mutex);
	}
	return -1;
}
def_dll int sdl_condition::wait(sdl_mutex& p)
{
	return SDL_CondWait(_condition,p._mutex);
}
def_dll int sdl_condition::wait_timeout(sdl_mutex* p,Uint32 t)
{
	if(p)
	{
		return SDL_CondWaitTimeout(_condition,p->_mutex,t);
	}
	return -1;
}
def_dll int sdl_condition::wait_timeout(sdl_mutex& p,Uint32 t)
{
	return SDL_CondWaitTimeout(_condition,p._mutex,t);
}
def_dll int sdl_condition::signal()
{
	return SDL_CondSignal(_condition);
}
def_dll int sdl_condition::broadcast()
{
	return SDL_CondBroadcast(_condition);
}
#endif //__SDLGUI_THREAD_HEAD__
