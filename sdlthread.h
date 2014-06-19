#ifndef __SDLGUI_THREAD_HEAD__
#define __SDLGUI_THREAD_HEAD__
#include <SDL2/SDL.h>
//如果导入动态库则定义头
#ifdef DLLEXPORT
#define def_dll __declspec(dllexport)
#else
#define def_dll
#endif
//class sdl_semaphore
//class sdl_mutex
//class sdl_condition
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
//---------------------------------------------------
//
//
//
//				互斥体
//
//
//---------------------------------------------------
class sdl_mutex
{
	friend class sdl_condition;
	public:
		def_dll sdl_mutex();
		def_dll virtual ~sdl_mutex();
		/**
		 * @brief 创建一个互斥体
		 *
		 * @return 
		 */
		def_dll int create();
		/**
		 * @brief 消毁一个互斥体
		 *
		 * @return 
		 */
		def_dll int destroy();
		/**
		 * @brief 锁定一个互斥体
		 *
		 * @return 
		 */
		def_dll int lock();
		/**
		 * @brief 偿试着锁定一个互斥体
		 *
		 * @return 
		 */
		def_dll int try_lock();
		/**
		 * @brief 解锁一个互斥体
		 *
		 * @return 
		 */
		def_dll int unlock();
	protected:
		SDL_mutex* _mutex;
};
//---------------------------------------------------
//
//
//
//				条件变量
//
//
//
//
//----------------------------------------------------
class sdl_condition
{
	public:
		def_dll sdl_condition();
		def_dll virtual ~sdl_condition();
		/**
		 * @brief 创建一个条件变量对象
		 *
		 * @return 
		 */
		def_dll int create();
		/**
		 * @brief 消毁一个条件变量对象
		 *
		 * @return 
		 */
		def_dll int destroy();
		/**
		 * @brief 等待一个条件变量的信号
		 *
		 * @return 
		 */
		def_dll int wait(sdl_mutex*);
		def_dll int wait(sdl_mutex&);
		/**
		 * @brief 在指定时间内等待一个条件变量的信号
		 *
		 * @return 
		 */
		def_dll int wait_timeout(sdl_mutex*,Uint32);
		def_dll int wait_timeout(sdl_mutex&,Uint32);
		/**
		 * @brief 激动一个条件变量，让一个条件等待
		 *
		 * @return 
		 */
		def_dll int signal();
		/**
		 * @brief 激活所有等待线程
		 *
		 * @return 
		 */
		def_dll int broadcast();
	protected:
		SDL_cond* _condition;
};
#endif//__SDLGUI_THREAD_HEAD__
