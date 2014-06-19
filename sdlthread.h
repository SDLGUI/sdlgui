#ifndef __SDLGUI_THREAD_HEAD__
#define __SDLGUI_THREAD_HEAD__
#include <SDL2/SDL.h>
//如果导入动态库则定义头
#ifdef DLLEXPORT
#define def_dll __declspec(dllexport)
#else
#define def_dll
#endif
//---------------------------------------------------
//
//
//				信号对象
//
//
//
//---------------------------------------------------
class sdl_semaphore
{
	public:
		def_dll sdl_semaphore();
		def_dll sdl_semaphore(int);
		def_dll virtual ~sdl_semaphore();
		/**
		 * @brief 初始化一个信号对象
		 *
		 * @return 
		 */
		def_dll int init();
		def_dll int init(int);
		/**
		 * @brief 创建一个信号对象
		 *
		 * @return 
		 */
		def_dll int create(int);
	
		/**
		 * @brief 消毁信号对象
		 *
		 * @return 
		 */
		def_dll int destroy();
		/**
		 * @brief 等待信号
		 *
		 * @return 
		 */
		def_dll int wait();
		/**
		 * @brief 释放信号
		 *
		 * @return 
		 */
		def_dll int post();
		/**
		 * @brief 信号值
		 *
		 * @return 
		 */
		def_dll Uint32 value();
		/**
		 * @brief 当前信号正在等待 
		 *
		 * @return 
		 */
		def_dll int try_wait();
		/**
		 * @brief 等待信号超时
		 *
		 * @param int
		 *
		 * @return 
		 */
		def_dll int wait_timeout(Uint32);
	protected:
		SDL_sem* _semaphore;
};
#endif//__SDLGUI_THREAD_HEAD__
