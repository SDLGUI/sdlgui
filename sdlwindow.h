//----------------------------------------------------------------------------------------------------------------
//
//
//
//
//						文档名：						sdlwindow.h
//
//						文档创建日期：			2014年2月22日
//						文档更新日期：			2014年6月25日
//						文档创建者：				徐荣
//						文档更新者：				徐荣
//						文档创建者联系方式：Email:twtfcu3@126.com
//																QQ:12880312(twtfcu3@126.com)
//																网站:http://sdl.my-mx.cn
//
//						版权说明：
//						1.本文档使用者的权利
//							a)本文档使用者可以随时利用本文档创建其它文件。
//							b)本文档使用者可以随时修改本文档有效代码内容，
//								但不能更改或添加本文档用//开头及用/**/包含的任何注释语句。
//						2.本文档使用者的义务
//							a)使用者不得更改本文档的文档名
//							b)本文档使用者在使用本文档时请在您的文档开始处
//								说明本文档版权归本文档创建者所有。
//							c)本文档使用者更改本文档后
//								请您上传更新后的文档到http://github.com/sdlgui/sdlgui/
//							d)本文档使用者本人承担
//								使用本文档后的所有法律责任,
//								本文档创建者不为您使用本文件的所有行为容承担任何法律责任。
//
//
//
//
//------------------------------------------------------------------------------------------------------------------
#ifndef __SDLWINDOW_HANDLE__
#define __SDLWINDOW_HANDLE__
#ifdef DLLEXPORT
	#define def_dll __declspec(dllexport)
#else
	#define def_dll
#endif
#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <string.h>
#include <map>
#include <queue>
#include <list>
#include <string>
#include <sstream>
#include "sdlbase.h"
#include "sdlthread.h"
//-----------------------------------------------
using namespace std;
//--------------------------------------------------
class sdl_board;
template<class T,class B> class GUI;
class sdl_ime;
class sdl_frame;
class sdl_widget;
class sdl_clip;
//----------------------------------------------
//
// 					自定义消息常量定义
// 					每个集合为七位数的编码
//          前四位是这类集合的代码
//          后三位是集合子消息的代码
//
//---------------------------------------------
#define __event_macro__(x,y) x##y
//计时器消息集合1000
#define timer_event_macro(y) __event_macro__(1000,y) 
const int sdlgui_event_timer = timer_event_macro(001);
//
//按钮类消息集合1001
#define button_event_macro(y) __event_macro__(1001,y) 
const int sdlgui_button_up= button_event_macro(001);
const int sdlgui_button_down = button_event_macro(002);
const int sdlgui_button_click = button_event_macro(003);
const int sdlgui_button_motion= button_event_macro(004);
const int sdlgui_button_wheel= button_event_macro(005);
//
//IME类消息集合1002
#define ime_event_macro(y) __event_macro__(1002,y) 
/* 输入上屏 */
const int sdlgui_ime_up= ime_event_macro(001);
/* 输入英文 */
const int sdlgui_ime_en= ime_event_macro(002);
/* 中文编码状态 */
const int sdlgui_ime_cn_edit= ime_event_macro(003);
/* 中文上屏状态 */
const int sdlgui_ime_cn_up= ime_event_macro(004);
/* 中文输入不可打印的控制符 */
const int sdlgui_ime_cn_ctrl= ime_event_macro(006);
/* 显示输入法窗口 */
const int sdlgui_ime_show= ime_event_macro(006);
/* 隐藏输入法窗口 */
const int sdlgui_ime_hide= ime_event_macro(007);
//
//文本输入框类消息集合1003
#define edit_event_macro(y) __event_macro__(1003,y) 
/* 文本更新 */
const int sdlgui_edit_change= edit_event_macro(001);
//滚动条类消息集合1004
#define scroll_event_macro(y) __event_macro__(1004,y) 
const int sdlgui_scroll_point= scroll_event_macro(001);
const int sdlgui_scroll_show= scroll_event_macro(002);
const int sdlgui_scroll_hide= scroll_event_macro(003);
//窗口事件类消息集合1005
#define window_event_macro(y) __event_macro__(1005,y) 
/* 消息焦点改变时发送的消息 */
const int sdlgui_window_focus= window_event_macro(001);
/* 鼠标事件集合1006 */
#define mouse_event_macro(y) __event_macro__(1006,y) 
const int sdlgui_mouse_click= mouse_event_macro(001);
const int sdlgui_mouse_db_click= mouse_event_macro(002);
const int sdlgui_mouse_release= mouse_event_macro(003);
const int sdlgui_mouse_motion= mouse_event_macro(004);
const int sdlgui_mouse_wheel= mouse_event_macro(005);

//-------------------------------------
//
//
//             用于继承的专用类
//
//
//-------------------------------------
//用于GUI类的继承与事件处理
//事件处理分为两类，第一类是GUI类自身的系统和用户功能实现。
//第二类是用户调用GUI对象的事件接口。
//GUI类的自身实现分为系统功能和用户功能，系统功能是类成员，用户功能是类静态成员
template <class T,class B>
class GUI : public B
{
	//friend int event_process(void* obj);
	friend class sdl_frame;
	public:
		int(*event_fun)(T*,SDL_Event*);
	public:
		T* This;
	public:
		GUI();
		virtual int event(SDL_Event*);//GUI专用类事件统一调用函数
		int event(int(*)(T*,SDL_Event*));//GU专用类内部事件处理函数（设置用户事件函数接口）
		virtual int sysevent(SDL_Event*e){return 0;};//GUI专用类系统事件处理函数的虚类
		virtual int handle(int handle,SDL_Event*e){return 0;}
		//int handle(int handle,SDL_Event*e){return 0;}
	protected:
		static int sysprocess(T*,SDL_Event*);
		static int userprocess(T*,SDL_Event*);
};
//-------------------------------------
//
//
//             窗口底板类
//
//
//-------------------------------------
typedef class sdl_board : public GUI<sdl_board,sdlsurface>
{
	public:
		friend class sdl_event_manager;
		friend class sdl_frame;
	public:
		sdl_board();
	  sdl_board(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflags);
		~sdl_board();
	  int init(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflags);
		int init();
		int sysevent(SDL_Event*e){return 0;}
	public:
		/* 显示当前窗口 */
		int show();
		/* 隐藏当前窗口 */
		int hide();
		/* 返回当前窗口的显示状态 */
		int is_show();
		/* 设置当前窗口标题 */
		int pos(int,int);
		/* 设置父级窗口对象 */
		sdl_board* parent(sdl_board*);
		/* 返回父级窗口对象 */
		sdl_board* parent();
		/* 返回给定对象是否为当前窗口的子窗口 */
		int is_child(sdl_board*);
		sdl_board* child(int,int);
		/* 添加子级窗口 */
		template<class T>T* add(const char*,int,int,int,int,Uint32);
		template<class T>T* add(T*);
		/* 销毁子级窗口 */
		virtual int destroy(int);
		/* 调整当前窗口Z序 */
		int z_top(sdl_board*,sdl_board*,int);
		/* 初始化时用于绘图窗口的虚函数 */
		virtual int draw(){return 0;}
		/* 重画当前窗口 */
		int redraw();
		/* 返回给定坐标的子窗口对象 */
		//-----------------------------------------------
	public:
		/* 重载委托事件函数处理 */
		int handle(int,SDL_Event*);
		/* 注册事件 */
		virtual int register_event(string);
		/* 连接委托函数 */
		virtual int connect_event(string,sdl_board*,int);
		/* 发送事件信号 */
		int event_signal(string,SDL_Event*);
		/* 鼠标点击事件 */
		virtual int on_click(sdl_board*,void*);
		/* 鼠标双击事件 */
		virtual int on_db_click(sdl_board*,void*);
		/* 鼠标释放事件 */
		virtual int on_release(sdl_board*,void*);
		/* 鼠标移动事件 */
		virtual int on_motion(sdl_board*,void*);
		/* 鼠标中键滚动事件 */
		virtual int on_wheel(sdl_board*,void*);
	protected:
		sdlsurface *_board;
		SDL_Rect  _rect;
		SDL_Rect  _global_rect;
		SDL_Point _pos,_size;
		sdl_board *_parent;
		//sdl_board *_end,*_head;
		//sdl_board *_next,*_last;
		sdltext  *_text_board;
		Uint32		_text_color;
		SDL_Rect  _text_rect;
		int _is_show;
		int _is_destroy;
		map<sdl_board*,int> _board_list;
}*sdl_board_ptr;
//sdl_board** sdl_board::_hit_board_ptr=NULL;
//-------------------------------------
//
//
//            定义事件句柄类型 
//
//
//-------------------------------------
/*
		定义事件句柄类型 
		要求所有事件函数返回整型值，
		调用对象与参数为事件参数
		结构中有两个数据
		sdl_board* object 用于保存对象地址
		int handle 用于保存每个对象指定事件在handle函数中的处理ID
 */
struct sdl_event_handle
{
	sdl_board* object;
	int handle;
};
//-------------------------------------
//
//
//            对象事件委托结构体 
//
//
//-------------------------------------
/* 
	对象事件委托结构体 
	结构中有两个数据
	map<string,sdl_event_handle> _event;
	用于存储对象被委托的事件,string为引索关键词格式为"对象地址_事件处理ID"
	queue<SDL_Event*> _event_queue;
	用于存储被委托对象所产生的事件
 */
class sdl_event_struct
{
	friend class sdl_event_object;
	friend class sdl_event_manager;
	public:
		def_dll sdl_event_struct()
		{
			_event.clear();
		}
		/* 对象事件析构函数 */
		def_dll virtual ~sdl_event_struct();
		/* 
			对象事件注册功能，
			注册时要一个事件函数名的字串与函数名入口地址
		 */
		def_dll int event_register(string,sdl_event_handle);
		/*
			 对象事件注消功能
			 注消时要用到事件函数名的字串
		*/
		def_dll int event_unregister(string);
		/* 
				事件调用累计增量 
		 */
		def_dll int push(SDL_Event*);
		/* 
				事件调用后减量 
		 */
		def_dll int pull();
		/* 
				事件调用计数 
		 */
		def_dll int count();
	protected:
		//事件函数入口列表
		def_dll	map<string,sdl_event_handle> _event;
		//事件参数列表
		def_dll queue<SDL_Event*> _event_queue;
};
def_dll sdl_event_struct::~sdl_event_struct()
{
	map<string,sdl_event_handle>::iterator node;
	for(node = _event.begin();node!=_event.end();node++)
	{
		//delete 
			//(sdl_event_handle)node->first;
	}
	_event.clear();
	while(pull());
}
def_dll int sdl_event_struct::event_register(string event_string,sdl_event_handle event_function)
{
	_event.insert(pair<string,sdl_event_handle>(event_string,event_function));
	return 0;
}
def_dll int sdl_event_struct::event_unregister(string event_string)
{
	_event.erase(event_string);
	return 0;
}
def_dll int sdl_event_struct::push(SDL_Event *e)
{
	SDL_Event* te = new SDL_Event;	
	memcpy((char*)te,(char*)e,sizeof(SDL_Event));
	_event_queue.push(te);
	return _event_queue.size();
}
def_dll int sdl_event_struct::pull()
{
	SDL_Event* t;
	if(_event_queue.size())
	{
		t = _event_queue.front();
		_event_queue.pop();
		delete t;
	}
	return _event_queue.size();
}
def_dll int sdl_event_struct::count()
{
	return _event_queue.size();
}




//-------------------------------------
//
//
//            对象事件项目列表 
//
//
//-------------------------------------
/* 
		对象事件项目列表 
		用于管理每个对象其中一个事件的委托入口调用
		一个参数
		map<string,sdl_event_struct*> _object_event_list;
		用于存储给对象注册进来的的委托事件,string为引索关键词,格式为"对象地址_委托事件字串"
 */
class sdl_event_object
{
	friend class sdl_event_manager;
	public:
		def_dll sdl_event_object();
		/*
			 析构函数
			 删除时清理对象所存储的所有事件 
		 */
		def_dll ~sdl_event_object();
		/* 
			注册一个事件
			参数为事件字串
		 */
		def_dll int event_register(string);
		/* 
			注消一个事件
			参数为事件字串
		 */
		def_dll int event_unregister(string);
		/* 
			事件调用累计一次 
		 */
		def_dll int push();
		/* 
			事件调用一次 
		 */
		def_dll int pull();
		/* 
			事件累计次数 
		 */
		def_dll int count();
	protected:
		def_dll int _event_count;
		def_dll map<string,sdl_event_struct*> _object_event_list;
};
def_dll sdl_event_object::sdl_event_object()
{
	_event_count = 0;
	_object_event_list.clear();
}
def_dll sdl_event_object::~sdl_event_object()
{
	map<string,sdl_event_struct*>::iterator node;
	for(node = _object_event_list.begin();node!=_object_event_list.end();node++)
	{
		delete (sdl_event_struct*)(node->second);
	}
	_object_event_list.clear();
}
def_dll int sdl_event_object::event_register(string event_string)
{
	sdl_event_struct* _event_ingress = new sdl_event_struct;
	_object_event_list.insert(pair<string,sdl_event_struct*>(event_string,_event_ingress));	
	return 0;
}
def_dll int sdl_event_object::event_unregister(string event_string)
{
	map<string,sdl_event_struct*>::iterator node;
	node = _object_event_list.find(event_string);
	delete (sdl_event_struct*)node->second;
	_object_event_list.erase(event_string);	
	return 0;
}
def_dll int sdl_event_object::push()
{
	_event_count++;
	return _event_count;
}
def_dll int sdl_event_object::pull()
{
	_event_count--;
	return _event_count;
}
def_dll int sdl_event_object::count()
{
	return _event_count;
}





//-------------------------------------
//
//
//           事件管理器 
//
//
//-------------------------------------
/* 
			事件管理器(静态类)

			用于调用对象事件
			实现委托功能与事件多线程化

			功能
			1.加入/移除对象
			2、给对象注册/注销事件
			3、给对象事件加入/删除事件委托函数
			4、自行处理对象事件


			一个全局静态操作参数
			map<sdl_board*,sdl_event_object*> _event_list;
			用于存储所有对象的事件结构,sdl_board*为关键词引索，使用的是对象的地址
 */
class sdl_event_manager
{
	friend class sdl_frame;
	public:
		/* 
			加入事件对象 参数为对象地址
		 */
		def_dll static int push(sdl_board*);
		/* 
			移除事件对象 参数为对象地址
		 */
		def_dll static int pull(sdl_board*);
		/* 
		 加入对象事件，参数为对象地址，事件字串 
		 */
		def_dll static int push(sdl_board*,string);
		/* 
			移除对象事件，参数为对象地址，事件字串 
		 */
		def_dll static int pull(sdl_board*,string);
		/* 
			加入对象事件委托入口函数
			参数为对象地址，事件字串，委托对象，委托入口函数处理ID
		 */
		def_dll static int push(sdl_board*,string,sdl_board*,int);
		/* 
			移除对象事件委托入口函数
			参数为对象地址，事件字串，委托入口函数地址
		 */
		def_dll static int pull(sdl_board*,string,sdl_board*,int);
		/* 
			对象事件调用 
		 */
		def_dll static int call_event(sdl_board*,string,SDL_Event*);
		/* 
			多线程管理事件列表 
		 */
		def_dll static int start();
		/* 
			退出时的销毁函数 
		 */
		def_dll static int destroy();
	protected:
		def_dll static int run(void*);
	protected:
		def_dll static map<sdl_board*,sdl_event_object*> _event_list;		
		def_dll static SDL_Thread* _event_process_thread;
		def_dll static sdl_condition _event_process_thread_cond;
		def_dll static sdl_condition _event_created_thread_cond;
		def_dll static sdl_mutex _event_thread_lock;
		def_dll static int _event_thread_is_lock;
		def_dll static int _event_thread_is_run;
};
def_dll map<sdl_board*,sdl_event_object*> sdl_event_manager::_event_list;
def_dll SDL_Thread* sdl_event_manager::_event_process_thread = NULL;
def_dll sdl_condition sdl_event_manager::_event_process_thread_cond;
def_dll sdl_condition sdl_event_manager::_event_created_thread_cond;
def_dll sdl_mutex sdl_event_manager::_event_thread_lock;
def_dll int sdl_event_manager::_event_thread_is_lock=0;
def_dll int sdl_event_manager::_event_thread_is_run = 1;
////////////////////////////////////////////////////
//
//
//
//
//
////////////////////////////////////////////////////
def_dll int sdl_event_manager::push(sdl_board* obj)
{
	sdl_event_object *obj_event_list = new sdl_event_object;
	sdl_event_manager::_event_list.insert(pair<sdl_board*,sdl_event_object*>(obj,obj_event_list));
	return 0;
}
def_dll int sdl_event_manager::pull(sdl_board* obj)
{
	sdl_event_manager::_event_list.erase(obj);
	return 0;
}
def_dll int sdl_event_manager::push(sdl_board* obj,string event_string)
{
	map<sdl_board*,sdl_event_object*>::iterator event_iter;
	sdl_event_object* event; 
	/* 先找到对象列表中的对象事件列表的引索 */
	event_iter = sdl_event_manager::_event_list.find(obj);
	if(event_iter == sdl_event_manager::_event_list.end())
	{
		return -1;
	}
	/* 再注册事件到对象事件列表 */
	//cout<<"event_register start"<<endl;
	event = (sdl_event_object*)(event_iter->second);
	//cout<<"event_register stop"<<endl;
	/* 使用对象事件列表自身注册功能 */
	return event->event_register(event_string);
}
def_dll int sdl_event_manager::pull(sdl_board* obj,string event_string)
{
	map<sdl_board*,sdl_event_object*>::iterator event_iter;
	sdl_event_object* event; 
	/* 先找到对象列表中的对象事件列表的引索 */
	event_iter = sdl_event_manager::_event_list.find(obj);
	if(event_iter == sdl_event_manager::_event_list.end())
	{
		return -1;
	}
	/* 再注册事件到对象事件列表 */
	event = (sdl_event_object*)event_iter->second;
	/* 使用对象事件列表自身注册功能 */
	return event->event_unregister(event_string);
}
def_dll int sdl_event_manager::push(sdl_board* connect_object,string event_string,sdl_board* event_object,int event_handle)
{
	stringstream event_object_string;
	map<sdl_board*,sdl_event_object*>::iterator event_iter;
	map<string,sdl_event_struct*>::iterator event_struct_iter;
	sdl_event_object* event; 
	sdl_event_struct* event_struct; 
	sdl_event_handle _handle;
	_handle.object = event_object;
	_handle.handle = event_handle;
	/* 先找到对象列表中的对象事件列表的引索 */
	event_iter = sdl_event_manager::_event_list.find(connect_object);
	/* 如果对象列表没有找到返回-1 */
	if(event_iter == sdl_event_manager::_event_list.end())
	{
		return -1;
	}
	/* 再读取注册事件对象的事件列表 */
	event = (sdl_event_object*)event_iter->second;
	/* 
		 然后找到对象事件列表中的事件(委托)结构
			没有找到返回-1 
	 */
	event_struct_iter = event->_object_event_list.find(event_string);
	if(event_struct_iter == event->_object_event_list.end())
	{
		return -1;
	}
	/* 使用对象事件列表自身注册功能 */
	event_object_string.clear();
	event_object_string<<event_object<<"_"<<_handle.handle;
	event_struct = (sdl_event_struct*)event_struct_iter->second;

	return event_struct->event_register(event_object_string.str(),_handle);
}
def_dll int sdl_event_manager::pull(sdl_board* connect_object,string event_string,sdl_board* event_object,int event_hendle)
{
	stringstream event_object_string;
	map<sdl_board*,sdl_event_object*>::iterator event_iter;
	map<string,sdl_event_struct*>::iterator event_struct_iter;
	sdl_event_object* event; 
	sdl_event_struct* event_struct; 
	/* 先找到对象列表中的对象事件列表的引索 */
	event_iter = sdl_event_manager::_event_list.find(connect_object);
	if(event_iter == sdl_event_manager::_event_list.end())
	{
		return -1;
	}
	/* 再读取注册事件对象的事件列表 */
	event = (sdl_event_object*)event_iter->second;
	/* 
		 然后找到对象事件列表中的事件(委托)结构
			没有找到返回-1 
	 */
	event_struct_iter = event->_object_event_list.find(event_string);
	if(event_struct_iter == event->_object_event_list.end())
	{
		return -1;
	}
	/* 使用对象事件列表自身注册功能 */
	event_object_string<<event_object<<"_"<<event_hendle;
	event_struct = (sdl_event_struct*)event_struct_iter->second;

	return event_struct->event_unregister(event_object_string.str());
}
def_dll int sdl_event_manager::call_event(sdl_board* event_object,string event_string,SDL_Event* e)
{
	stringstream event_object_string;
	map<sdl_board*,sdl_event_object*>::iterator event_iter;
	map<string,sdl_event_struct*>::iterator event_struct_iter;
	sdl_event_object* event; 
	sdl_event_struct* event_struct; 
	/* 先找到对象列表中的对象事件列表的引索 */
	event_iter = sdl_event_manager::_event_list.find(event_object);
	if(event_iter == sdl_event_manager::_event_list.end())
	{
		return -1;
	}
	/* 再读取注册事件对象的事件列表 */
	event = (sdl_event_object*)event_iter->second;
	/* 
		 然后找到对象事件列表中的事件(委托)结构
			没有找到返回-1 
	 */
	event_struct_iter = event->_object_event_list.find(event_string);
	if(event_struct_iter == event->_object_event_list.end())
	{
		return -1;
	}
	/* 使用对象事件列表累计 */
	event_struct = (sdl_event_struct*)event_struct_iter->second;
	return event_struct->push(e);
}
def_dll int sdl_event_manager::start()
{
	sdl_event_manager::_event_process_thread = SDL_CreateThread(sdl_event_manager::run,"sdl_event_manager::run",NULL);
}
def_dll int sdl_event_manager::run(void* p)
{
	stringstream event_object_string;
	map<sdl_board*,sdl_event_object*>::iterator event_iter;
	map<string,sdl_event_struct*>::iterator event_struct_iter;
	map<string,sdl_event_handle>::iterator event_struct_handle_iter;
	sdl_event_object* event; 
	sdl_event_struct* event_struct; 
	sdl_event_handle event_struct_handle;
	sdl_board* event_object;
	while(sdl_event_manager::_event_thread_is_run)
	{
		/* 引索所有的托管函数地址 */
		/* 先找到对象列表中的对象事件列表的引索 */
		//event_iter = sdl_event_manager::_event_list.begin();
		for(event_iter = sdl_event_manager::_event_list.begin();event_iter!=sdl_event_manager::_event_list.end();event_iter++)
		{
			event_object = (sdl_board*)(event_iter->first);
			/* 
				 如果当前对象要销毁则锁定事件处理线程 
				 然后删除当前窗口节点 
			 */
			if(event_object->_is_destroy)
			{
				/* 删除对象节点时是否要删除事件列表中所有调用该对象的委托事件 */
				//cout<<event_object<<":"<<event_object->_is_destroy<<endl;
				sdl_event_manager::_event_list.erase(event_object);				
				//delete event_object;
			}
			else
			{
				/* 否则再读取注册事件对象的事件列表 */
				event = (sdl_event_object*)event_iter->second;
				/* 
					然后找到对象事件列表中的事件(委托)结构
				*/
				for(event_struct_iter = event->_object_event_list.begin();event_struct_iter!=event->_object_event_list.end();event_struct_iter++)
				{
					/* 使用对象事件列表累计 */
					event_struct = (sdl_event_struct*)event_struct_iter->second;
					if(event_struct->count())
					{
						//cout<<clock()<<endl;
						for(event_struct_handle_iter = event_struct->_event.begin();event_struct_handle_iter!=event_struct->_event.end();event_struct_handle_iter++)
						{
							/* 调用托管的事件函数 */
							event_struct_handle = (sdl_event_handle)event_struct_handle_iter->second;
							if(event_struct_handle.object)
							{
								//cout<<"event start"<<event_struct_handle.object<<endl;
								//event_struct_handle.object;
								if(sdl_event_manager::_event_list.find(event_struct_handle.object)!=sdl_event_manager::_event_list.end())
								event_struct_handle.object->handle(event_struct_handle.handle,(SDL_Event*)(event_struct->_event_queue.front()));
								//cout<<"event stop"<<clock()<<endl;
							}
						}
						event_struct->pull();
					}
				}
			}
		}
		SDL_Delay(1);
	}
	return 0;
}
def_dll int sdl_event_manager::destroy()
{
	int _thread_state;
	map<sdl_board*,sdl_event_object*>::iterator node;
	sdl_event_manager::_event_thread_is_run = 0;
	SDL_WaitThread(sdl_event_manager::_event_process_thread,&_thread_state);
	for(node = sdl_event_manager::_event_list.begin();node!=sdl_event_manager::_event_list.end();node++)
	{
		delete (sdl_event_object*)node->second;
	}
	sdl_event_manager::_event_list.clear();
	return 0;
}
//------------------------------------------
//
//
//					剪辑类
//
//
//------------------------------------------
typedef class sdl_clip : public sdlsurface
{
	public:
		sdl_clip();
		sdl_clip(int,int,string);
		int init();
		int init(int,int,string);
		int clip(int,int);
		int clip(int,int,sdlsurface*,SDL_Rect*);
		//int blit_surface(int,int,sdlsurface*,SDL_Rect*);
		//int blit_scael(int,int,sdlsurface*,SDL_Rect*);
	protected:
		int _w,_h;
		int _sur_w,_sur_h;
		int _row,_column;
}*sdl_clip_ptr;
//------------------------------------
//
//           工具类
//
//
//------------------------------------
typedef class sdl_widget : public GUI<sdl_widget,sdl_board>
{
	public:
		sdl_widget();
		sdl_widget(const char*,int,int,int,int,Uint32);
		~sdl_widget();
		int init();
		int init(const char*,int,int,int,int,Uint32);
		int sysevent(SDL_Event*);
}*sdl_widget_ptr;
//-------------------------------------
//
//
//             窗口框架类
//
//-------------------------------------
typedef class sdl_frame : public GUI<sdl_frame,sdl_board>
{
	public:
		friend class sdl_board;
	public:
		sdl_frame();
		sdl_frame(const char*,int,int,int,int,Uint32);
		~sdl_frame();
		int init();
		int init(const char*,int,int,int,int,Uint32);
		int redraw();
		virtual int sysevent(SDL_Event*);
		int destroy(int);
		sdlwindow* frame();
		//------------------------------------------------
		int pos(int,int);
		int size(int,int);
		int size(int*,int*);
		int show();
		int hide();
		//------------------------------------
		double fps();
	protected:
		/* 事件分流 */
		int event_shunt(SDL_Event*);
	protected:
		/* 渲染多线程函数 */
		static int redraw_thread(void*);
	public:
		//sdl_ime ime;
		static int run();
		static SDL_Event _main_event;
		/* 消息处理循环变量 */
		static int _is_exit;
	protected:
		static sdl_board* _capture_win;
		static map<Uint32,sdl_frame*> _window_list;
	protected:
		sdlwindow* _window;
		sdlsurface _screen;
		double _fps;
		SDL_Point _window_rect;
		/* 顶级窗口渲染循环 */
		int _is_redraw;
		/* 处理消息流的子级线程 */
		SDL_Thread* _event_thread;
		/* 处理重绘流的子级线程 */
		SDL_Thread* _redraw_thread;
}*sdl_frame_ptr;
sdl_board* sdl_frame::_capture_win = NULL;
map<Uint32,sdl_frame*> sdl_frame::_window_list;
SDL_Event sdl_frame::_main_event;
int sdl_frame::_is_exit=0;
//--------------------------------------------------
//
//
//
//
//
//
//
//
//
//
//
//
//---------------------------------------------------
//---------------------------------------------
/* 
	主要是处理消息分流而设计的类,
	它的构造函数首先会申请两个事件节点,
	第一个节点为首节点，第二个节点为尾节点,
	首节点的向上指向节点永远是指向尾节点的,
	如果首尾节点相邻，则表示本窗口的,
	所有事件处理完毕，将合并新的缓冲事件,
 */
//GUI继承专用类构造函数
template<class T,class B>
GUI<T,B>::GUI():B()
{
	//This = dynamic_cast<T*>(this);
	This = (T*)(this);
	event_fun = NULL;
}
//----------------------------------------
//GUI继承专用类对象事件设置函数
template<class T,class B>
int GUI<T,B>::event(int(*f)(T*,SDL_Event*))
{
	if(f)
	{
		event_fun = f; 
		return 0;
	}
	return -1;
}
//------------------------------------
//GUI继承专用类事件调用函数
template<class T,class B>
int GUI<T,B>::event(SDL_Event* e)
{
	userprocess(This,e);
	sysprocess(This,e);
	return 0;
}
//--------------------------------------
//GUI继承专用类系统事件设置函数
template<class T,class B>
int GUI<T,B>::sysprocess(T* obj,SDL_Event* e)
{
	T* _this = ((GUI<T,B>*)obj)->This;
	if(_this!=NULL)return _this->sysevent(e);
	return -1;
}
//--------------------------------------
//GUI继承专用类用户事件设置函数
template<class T,class B>
int GUI<T,B>::userprocess(T* obj,SDL_Event* e)
{
	//return 0;
	T* _this = ((GUI<T,B>*)obj)->This;
	if(_this!=NULL && _this->event_fun!=NULL)
	{
		return (*(_this->event_fun))(_this,e);
	}
	return -1;
}
//-----------------------------------------------

//------------------------------------------
//
//
//
//
//---------------------------------------------
//-------------------------------------
//底板空白构造函数
sdl_board::sdl_board()
:
GUI<sdl_board,sdlsurface>()
{
	init();
}
//-------------------------------------------
//底板带参构造函数
//---------------------------------------
sdl_board::sdl_board(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflags)
:
GUI<sdl_board,sdlsurface>()
{
	init();
	init(ptitle,px,py,pw,ph,pflags);
}
//-----------------------------------------------
//底板析构函数
sdl_board::~sdl_board()
{
	/* 释放缓冲表面 */
	if(_board)delete _board;
	/* 释放文本表面 */
	if(_text_board)delete _text_board;
	/* 释放子窗口节点 */
	//destroy(1);
}
//底板初始函数
int sdl_board::init(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflags)
{
	//cout<<"init board start"<<endl;
	string cur_platform;
	if(sdlsurface::init(0,pw,ph,32,0,0,0,0))return -1;
	//-------------
	_rect.x = px;
	_rect.y = py;
	_rect.w = pw;
	_rect.h = ph;
	_global_rect.x = 0;
	_global_rect.y = 0;
	//--------------
	if(_board)delete _board;
	_board = new sdlsurface(0,pw,ph,32,0,0,0,0);
	//----------------
	//-----------------
	if(ptitle)
	{
		cur_platform = SDL_GetPlatform();
		if(!sdltext::font_path.length())
		{
			if(!cur_platform.compare("Windows"))
			{
				sdltext::font_path = "c:/windows/fonts/simkai.ttf";
			//_text_board = new sdltext("c:/windows/fonts/simkai.ttf",16);
			}
			else
			if(!cur_platform.compare("Linux"))
			{
				sdltext::font_path = "/usr/share/font/truetype/wqy/wqy-zenhei.ttc";
				//_text_board = new sdltext("/usr/share/fonts/truetype/wqy/wqy-zenhei.ttc",16);
			}
			else
			if(!cur_platform.compare("Android"))
			{
				sdltext::font_path = "/system/fonts/DroidSanSansFallback.ttf";
				//_text_board = new sdltext("/system/fonts/DroidSanSansFallback.ttf",16);
			}
		}
		if(_text_board)delete _text_board;
		_text_board = new sdltext(sdltext::font_path.c_str(),16);
		if(_text_board)_text_board->render_utf8_solid(ptitle,_text_color);
		_text_rect.x = (pw-_text_board->clip_rect()->w)/2,_text_rect.y = (ph-_text_board->clip_rect()->h)/2,_text_rect.w = pw,_text_rect.h = ph;
	}
	//
	/* 注册委托函数 */
	sdl_event_manager::push(this);
	register_event("on_click");
	connect_event("on_click",this,sdlgui_mouse_click);
	register_event("on_db_click");
	connect_event("on_db_click",this,sdlgui_mouse_db_click);
	register_event("on_release");
	connect_event("on_release",this,sdlgui_mouse_release);
	register_event("on_motion");
	connect_event("on_motion",this,sdlgui_mouse_motion);
	register_event("on_wheel");
	connect_event("on_wheel",this,sdlgui_mouse_wheel);
	return 0;
}
//------------------------------------------
//底板初始空函数
int sdl_board::init()
{
	if(sdlsurface::init())return -1;
	memset((char*)&_pos,0x00,sizeof(SDL_Point));
	memset((char*)&_size,0x00,sizeof(SDL_Point));
	memset((char*)&_rect,0x00,sizeof(SDL_Rect));
	_is_show = 1;
	_is_destroy = 0;
	_parent = NULL;
	//_end = NULL;
	//_head = NULL;
	//_next = NULL;
	//_last = NULL;
	_board = NULL;
	_text_board= NULL;
	_text_color = 0x000000;
	/* 初始子窗口节点列表 */
	_board_list.clear();
	return 0;
}
//--------------------------------------
//设置窗口底板位置
int sdl_board::pos(int x,int y)
{
	_rect.x = x;
	_rect.y = y;
	if(_parent)
	{
		_global_rect.x = _parent->_global_rect.x+_rect.x;
		_global_rect.y = _parent->_global_rect.y+_rect.y;
	}
	else
	{
		_global_rect.x = 0;
		_global_rect.y = 0;
	}
	return 0;
}
//设置父级窗口
sdl_board* sdl_board::parent(sdl_board* parent)
{
	_parent = parent;
	return _parent;
}
//------------------------------------------
//返回父级窗口
sdl_board* sdl_board::parent()
{
	return _parent;
}
//-------------------------------------------------
/* 
	 返回给定对象是否为当前窗口的子窗口 
	 如果是子级窗口返回0,否则返回-1 
 */
int sdl_board::is_child(sdl_board* obj)
{
	sdl_board* t = obj;
	//如果指定窗口与指定窗口的父级窗口都存在则处理数据
	while(t && t->parent())
	{
		//如果指定窗口的父级窗口与当前窗口相等,返回0
		if(t->parent() == this)return 1;
		//向父级窗口跳转
		t = t->parent();
	}
	//如果一直没有返回表示指定窗口不是当前窗口的子级,则返回-1
	return 0;
}
sdl_board* sdl_board::child(int x,int y)
{
	//map<sdl_board*,int>::iterator node;
	map<sdl_board*,int>::reverse_iterator node = _board_list.rbegin();
	sdl_board* board_node;
	int px,py,gw,gh;
	px = x-_rect.x;
	py = y-_rect.y;
	for(node = _board_list.rbegin();node!=_board_list.rend();node++)
	{
		board_node=(sdl_board*)node->first;
		gw = board_node->_rect.x+board_node->_rect.w;
		gh = board_node->_rect.y+board_node->_rect.h;
		if(px>=board_node->_rect.x && px<=gw && py>=board_node->_rect.y && py<=gh)
		{
			return board_node->child(px,py);
		}
	}
	return this;
}
//-------------------------------------
//添加子内部窗口底板
template<class T>T* sdl_board::add(const char* title,int px,int py,int pw,int ph,Uint32 pflags)
{
	T* t = dynamic_cast<T*>(new T);
	t->init(title,px,py,pw,ph,pflags);
	t->_parent = this;
	t->_global_rect.x = _global_rect.x+px;
	t->_global_rect.y = _global_rect.y+py;
	z_top(t,NULL,1);
	return t;
}
//---------------------------------------------------
//添加外部子窗口底板
template<class T>T* sdl_board::add(T* obj)
{
	if(obj)
	{
		obj->_parent = this;
		z_top(obj,NULL,1);
		return obj;
	}
	return NULL;
}
//-----------------------------------------
//调整子窗口Z序
/* 
		子窗口Z序的最顶层窗口（即列表尾节点）的NEXT应为NULL 
		如果b为空
			如果z为0表示删除a节点
			否则如果z>0表示插入头节点
			否则如果z<0表示插入尾节点
		否则
			如果z为0表示交换a和b的位置
			否则如果z>0表示a移动到b的后面
			否则如果z<0表示a移动到b的前面
 */
int sdl_board::z_top(sdl_board* a,sdl_board *b,int z=1)
{
	map<sdl_board*,int>::iterator node;
	if(!a)return -1;
	_thread_lock.wait();
	/* 如果没有b对象表示直接插入或删除 */
	if(!b)
	{
		/* 大于0表示插入到尾 */
		if(z>0)
		{
			_board_list.insert(pair<sdl_board*,int>(a,0));
		}
		else
		/* 小于0表示插入到头 */
		if(z<0)
		{
			_board_list.insert(_board_list.begin(),pair<sdl_board*,int>(a,0));
		}
		/* 为0表示删除 */
		else
		{
			_board_list.erase(a);
		}
	}
	else
	{
		if(z>0)
		{
			node = _board_list.find(b)++;
			_board_list.erase(a);
			_board_list.insert(node,pair<sdl_board*,int>(a,0));
		}
		else
		if(z<0)
		{
			node = _board_list.find(b)++;
			_board_list.erase(a);
			_board_list.insert(node,pair<sdl_board*,int>(a,0));
		}
		else
		{
			node = _board_list.find(a);
			_board_list.erase(a);
			_board_list.insert(_board_list.find(b),pair<sdl_board*,int>(a,0));
			_board_list.erase(b);
			_board_list.insert(node,pair<sdl_board*,int>(b,0));
		}
	}
	_thread_lock.post();
	return 0;
}
//---------------------------------------------
//销毁子级窗口参数P表示是否销毁本身
int sdl_board::destroy(int p=1)
{
	map<sdl_board*,int>::iterator node;
	sdl_board* node_board;
	_is_destroy = p;
	if(_is_destroy && _parent)_parent->z_top(this,NULL,0);
	//cout<<"start destor is "<<this<<endl;
	for(node = _board_list.begin();node!=_board_list.end();node++)
	{
		node_board = (sdl_board*)node->first;
		if(node_board->destroy(1))return -1;		
	}
	//cout<<"stop destor is "<<this<<endl;
	return 0;
}
//--------------------------------------------------------
//重绘底板窗口
int sdl_board::redraw()
{
	sdl_board* node_board;
	SDL_Rect prt,srt;
	map<sdl_board*,int>::iterator node = _board_list.begin();
	//map<sdl_board*,int>::reverse_iterator node = _board_list.rbegin();
	blit_surface(NULL,_board,NULL);
	_text_board->blit_surface(NULL,_board,&_text_rect);
	//_thread_lock.wait();
	//cout<<"start redraw "<<this<<endl;
	while(node!=_board_list.end())
	{
		//cout<<node->first<<endl;
		node_board = (sdl_board*)node->first;
		node_board->redraw();
		/* 调整画到父级窗口的绘画范围 */
		if(node_board->_rect.x>0)
		{
			srt.x = 0;
			prt.x = node_board->_rect.x;
			if(node_board->_rect.x+node_board->_rect.w > _rect.w)
			{
				prt.w = _rect.w-node_board->_rect.x;
				srt.w = _rect.w-node_board->_rect.x;
			}
			else
			{
				prt.w = node_board->_rect.w;
				srt.w = node_board->_rect.w;
			}
		}
		else
		{
			prt.x = 0;
			prt.w = node_board->_rect.w+node_board->_rect.x;
			srt.x = node_board->_rect.x*-1;
			srt.w = node_board->_rect.w+node_board->_rect.x;
		}
		if(node_board->_rect.y>0)
		{
			srt.y = 0;
			prt.y = node_board->_rect.y;
			if(node_board->_rect.y+node_board->_rect.h > _rect.h)
			{
				prt.h = _rect.h-node_board->_rect.y;
				srt.h = _rect.h-node_board->_rect.y;
			}
			else
			{
				prt.h = node_board->_rect.h;
				srt.h = node_board->_rect.h;
			}
		}
		else
		{
			prt.y = 0;
			prt.h = node_board->_rect.h+node_board->_rect.y;
			srt.y = node_board->_rect.y*-1;
			srt.h = node_board->_rect.h+node_board->_rect.y;
		}
		node_board->_board->blit_surface(&srt,_board,&prt);
		node++;
	}
	//cout<<"stop redraw "<<this<<endl;
	//_thread_lock.post();
	return 0;
}
//显示一个底板窗口
int sdl_board::show()
{
	_is_show = 1;
	return 0;
}
//---------------------------------------------
//隐藏一个底板窗口
int sdl_board::hide()
{
	_is_show = 0;
	return 0;
}
//---------------------------------------------
//一个底板窗口的显示状态
int sdl_board::is_show()
{
	return _is_show;
}
//---------------------------------------------
//底板窗口委托事件处理
int sdl_board::handle(int id,SDL_Event* e)
{
	switch(id)
	{
		case sdlgui_mouse_click:
			on_click(This,(void*)e);
		break;
		case sdlgui_mouse_motion:
			on_motion(This,(void*)e);
		break;
		case sdlgui_mouse_wheel:
			on_wheel(This,(void*)e);
		break;
		case sdlgui_mouse_db_click:
			on_db_click(This,(void*)e);
		break;
		case sdlgui_mouse_release:
			on_release(This,(void*)e);
		break;
		default:
			cout<<"other events"<<endl;
		break;
	}
	return 0;
}
//----------------------------------------------
//底板窗口注册事件函数
int sdl_board::register_event(string event_string)
{
	return sdl_event_manager::push(this,event_string);
}
//----------------------------------------------
//底板窗口连接委托事件函数
int sdl_board::connect_event(string event_string,sdl_board* event_object,int event_handle)
{
	return sdl_event_manager::push(This,event_string,event_object,event_handle);
}
//----------------------------------------------
//给底板窗口发送信号
int sdl_board::event_signal(string event_string,SDL_Event*e)
{
	return sdl_event_manager::call_event(This,event_string,e);
}
//---------------------------------------------
//底板窗口鼠标点击事件委托函数
int sdl_board::on_click(sdl_board* obj,void* data)
{
	//cout<<"click mouse on board is:"<<this<<endl;
	return 0;
}
//---------------------------------------------
//底板窗口鼠标释放事件委托函数
int sdl_board::on_release(sdl_board* obj,void* data)
{
	//cout<<"release mouse on board is:"<<this<<endl;
	return 0;
}
//---------------------------------------------
//底板窗口鼠标双击事件委托函数
int sdl_board::on_db_click(sdl_board* obj,void* data)
{
	//cout<<"db_click mouse on board is:"<<this<<endl;
	return 0;
}
//---------------------------------------------
//底板窗口鼠标移动事件委托函数
int sdl_board::on_motion(sdl_board* obj,void* data)
{
	//cout<<"motion board is:"<<this<<endl;
	return 0;
}
//-------------------------------------------------
// 鼠标中键滚动事件 
int sdl_board::on_wheel(sdl_board* obj,void* data)
{
	//cout<<"mouse wheel is"<<this<<endl;
	return 0;
}
//------------------------------------------------
//
//
//
//
//
//
//
//
//------------------------------------------------
sdl_clip::sdl_clip()
{
	init();
}
sdl_clip::sdl_clip(int pw,int ph,string f)
{
	init(pw,ph,f);
}
int sdl_clip::init()
{
	return 0;
}
int sdl_clip::init(int pw,int ph,string f)
{
	init();
	if(img_load(f.c_str()))return -1;
	clip(pw,ph);
	return 0;
}
int sdl_clip::clip(int pw,int ph)
{
	_w = pw;
	_h = ph;
	_sur_w = clip_rect()->w;
	_sur_h = clip_rect()->h;
	//
	_column = _sur_w/_w;
	if(_sur_w%_w)
	{
		_column += 1;
	}
	_row = _sur_h / _h;
	if(_sur_h % _h)
	{
		_row += 1;
	}
	return 0;
}
int sdl_clip::clip(int ps,int pe,sdlsurface* dst,SDL_Rect *rt = NULL)
{
	SDL_Rect srt={(ps%_column)*_w,(ps/_column)*_h,(pe%_column-ps%_column+1)*_w,((ps-pe)/_column+1)*_h};
	//cout<<srt.x<<":"<<srt.y<<"-"<<srt.w<<":"<<srt.h<<endl;
	if(!dst)return -1;
	if(rt)
	{
		return blit_scaled(&srt,dst,rt);		
	}
	else
	{
		return blit_surface(&srt,dst,NULL);
	}
	return -1;
}
//-------------------------------------------
//
//
//
//
//
//
//--------------------------------------
//窗口框架空白构造函数
sdl_frame::sdl_frame()
:
GUI<sdl_frame,sdl_board>()
{
	init();
}
//--------------------------------------
//窗口框架带参构造函数
sdl_frame::sdl_frame(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflags)
:
GUI<sdl_frame,sdl_board>()
{
	init();
	init(ptitle,px,py,pw,ph,pflags);	
}
//--------------------------------------
//框架析构函数
sdl_frame::~sdl_frame()
{
	int _thread_state;
	if(_window)
	{
		delete _window;
	}
	if(_redraw_thread)
	{
		_is_redraw = 0;
		SDL_WaitThread(_redraw_thread,&_thread_state);
		_redraw_thread = NULL;
	}
}
//-------------------------
//
int sdl_frame::init()
{
	if(sdl_board::init())return -1;
	_window = NULL;
	//_renderer = NULL;
	_event_thread = NULL;
	//_is_exit = 0;
	_is_redraw = 1;
	return 0;
}
//-------------------------
//窗口框架初始函数
int sdl_frame::init(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflags)
{
	if(sdl_board::init("",px,py,pw,ph,0))return -1;
	/* 设置窗口位置 */
	_rect.x = 0;
	_rect.y = 0;
	//-------------------
	//创建窗口
	_window = new sdlwindow(ptitle,px,py,pw,ph,pflags);
	sdl_frame::_window_list.insert(pair<Uint32,sdl_frame*>(SDL_GetWindowID(_window->window()),this));
	/* 创建渲染器 */
	if(_window)
	{
		/* 取窗口大小 */
		_window->size(&_window_rect.x,&_window_rect.y);
		//_screen.init(ptitle,px,py,_window_rect.x,_window_rect.y,pflags);
		size(_window_rect.x,_window_rect.y);
		//_rect.h = _window_rect.y;
		//_rect.w = _window_rect.y;
	}
	_screen.surface(_window->get_window_surface()->surface());
	/* 开启消息流子级线程 */
	//_event_thread = SDL_CreateThread(all_event_process,"event_process",(void*)this);
	/* 开启重绘流子级线程 */
	_redraw_thread = SDL_CreateThread(redraw_thread,"redraw_thread",(void*)this);
	return 0;
}
//-----------------------------------
//返回窗口框架的窗口对象。
sdlwindow* sdl_frame::frame()
{
	return _window;
}
//-----------------
//重载底板类的重画函数
//用于把_board对象显示到窗口框架
int sdl_frame::redraw()
{
	/* 更新窗口 */
	sdl_board::redraw();
	/* 将窗口传输到屏幕 */
	_board->blit_surface(NULL,&_screen,NULL);
	/* 刷新屏幕 */
	return _window->update_window_surface();
}
//----------------------------------------
//重画函数子线程处理函数
int sdl_frame::redraw_thread(void* data)
{
	clock_t _frame_timer;
	double sleep = 0;
	sdl_frame* f = (sdl_frame*)data;
	while(f->_is_redraw)
	{
		//cout<<f<<endl;
		_frame_timer = clock();
		//
		f->redraw();
		//
		//f->_window->update_window_surface();
		/* 计算帧频 */
		f->_fps = 1000 / ((clock() - _frame_timer + 0.001));
		//cout<<f->_fps<<endl;
		sleep = 1000/60-1000/f->_fps;
		sleep = (sleep>0)?sleep:0;
		SDL_Delay((sleep<(1000/60))?sleep:(1000/60));
	}
	return 0;
}
//-------------------------------------------
//销毁顶级窗口
int sdl_frame::destroy(int p=1)
{
	int _thread_state;
	_is_redraw = 0;
	SDL_WaitThread(_redraw_thread,&_thread_state);
	_redraw_thread = NULL;
	_window->destroy();
	sdl_frame::_window_list.erase(SDL_GetWindowID(_window->window()));
	return 0;
}
//-------------------------------------
//返回当前FPS
double sdl_frame::fps()
{
	return _fps;
}
//-------------------------
//用于消息事件分流
int sdl_frame::event_shunt(SDL_Event* e)
{
	static sdl_board* t;
	static int x,y;
	SDL_Event te;
	SDL_UserEvent ue;
	switch(e->type)
	{
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEMOTION:
		case SDL_MOUSEWHEEL:
			SDL_GetMouseState(&x,&y);
		break;
		case SDL_FINGERUP:
		case SDL_FINGERDOWN:
		case SDL_FINGERMOTION:
			x = e->tfinger.x * _window_rect.x;
			y = e->tfinger.y * _window_rect.y;
		break;
	}
	t = child(x,y);
	t = (t==0)?(sdl_board*)this : t;
	switch(e->type)
	{
		case SDL_MOUSEBUTTONDOWN:
		case SDL_FINGERDOWN:
			//if(sdl_frame::_capture_win)
			{
				//sdl_frame::_capture_win->event(e);
				//sdl_frame::_capture_win->event_signal("on_click");
			}
			//
			if(t != this)
			{
				t->event(e);
				//if(e->button.clicks==2)
				{
					//t->event_signal("on_db_click",e);
				}
				//else
				{
					t->event_signal("on_click",e);
				}
			}
		break;
		case SDL_MOUSEBUTTONUP:
		case SDL_FINGERUP:
			if(t != this)
			{
				t->event(e);
				t->event_signal("on_release",e);
			}
		break;
		case SDL_FINGERMOTION:
		case SDL_MOUSEMOTION:
			if(t != this)
			{
				t->event(e);
				t->event_signal("on_motion",e);
			}
		break;
		case SDL_MOUSEWHEEL:
			//if(t != this)t->event(e);
			//if(sdl_frame::_capture_win)
			{
				//sdl_frame::_capture_win->event(e);
				//sdl_frame::_capture_win->event_signal("on_click");
			}
			//else
			{
				t->event(e);
				t->event_signal("on_wheel",e);
			}
		break;
		case SDL_KEYUP:
		break;
		case SDL_TEXTINPUT:
			//ime.input(*e->text.text);
		case SDL_KEYDOWN:
			//if(_active_win != this)_active_win->event(e);
			//_active_win->event(e);
		break;
	}
	return 0;
}
//重载窗口的系统事件处理函数。
int sdl_frame::sysevent(SDL_Event* e)
{
	switch(e->type)
	{
		case SDL_WINDOWEVENT:
			switch(e->window.event)
			{
				/* 屏幕重显窗口时，分配新的窗口表面 */
				/* 窗口大小调整时，分配新的窗口表面 */
				case SDL_WINDOWEVENT_RESIZED:
				case SDL_WINDOWEVENT_RESTORED:
					_screen.surface(_window->get_window_surface()->surface());
				break;
				case SDL_WINDOWEVENT_CLOSE:
					destroy();
				break;
				default:
					//cout<<"Window Event"<<endl;
				break;
			}
		break;
		case SDL_QUIT:
			_is_exit = 1;
		break;
	}
	return sdl_board::sysevent(e);
}
//-------------------------------------------
//窗口框架运行函数
int sdl_frame::run()
{
	//sdltexture* tex=NULL;
	map<Uint32,sdl_frame*>::iterator _node;
	sdl_frame* _node_window;
	//cout<<"window destroy start"<<endl;
	while(!sdl_frame::_is_exit)
	{
		//cout<<_is_exit<<endl;
		if(sdl_frame::_window_list.empty())
		{
			sdl_frame::_is_exit = 1;
			//return 0;
			break;
		}
		else
		{
			while(SDL_PollEvent(&sdl_frame::_main_event))
			{
				/* 如果事件处理线程没有锁定则锁定后创建事件 */
				//sdl_event_manager::_event_thread_lock.lock();
				if(!sdl_event_manager::_event_thread_is_lock)
				{
					//sdl_event_manager::_event_process_thread_cond.wait(sdl_event_manager::_event_thread_lock);
					sdl_event_manager::_event_thread_is_lock = 1;
				}
				/* 确定事件窗口 */
				_node = _window_list.find(sdl_frame::_main_event.window.windowID);
				_node_window = (sdl_frame*)_node->second;
				//if(!_node_window)return -1;
				if(!_node_window)
				{
					sdl_frame::_is_exit = 1;
					//return 0;
					break;
				}
				/* 创建事件 */
				switch(sdl_frame::_main_event.type)
				{
					case SDL_QUIT:
						//cout<<_node_window<<endl;
						_node_window->event(&_main_event);
					break;
					case SDL_WINDOWEVENT:
						//event(&_main_event);
						_node_window->event(&sdl_frame::_main_event);
					break;
					case SDL_USEREVENT:
						/* 计时器消息分流 */
						if(sdl_frame::_main_event.user.code == sdlgui_event_timer)
						{
							((sdl_board*)sdl_frame::_main_event.user.data1)->event(&_main_event);
						}
						else
						{
							//event(&_main_event);
							_node_window->event(&sdl_frame::_main_event);
						}
					break;
					default:
						/* 其它消息分流 */
						//event_shunt(&_main_event);
						_node_window->event_shunt(&sdl_frame::_main_event);
					break;
				}
				/* 事件线程解锁 */
				sdl_event_manager::_event_thread_lock.unlock();
			}
			SDL_Delay(1);
		}
	}
	//cout<<"window destroy stop"<<endl;
	sdl_event_manager::destroy();
	return 0;
}
//------------------------------------------------
//------------------------------------------
//更新窗口位置
int sdl_frame::pos(int x,int y)
{
	if(!_window)return -1;
	return _window->pos(x,y);
}
//----------------------------------------------
//更新窗口大小
int sdl_frame::size(int w,int h)
{
	if(!_window)return -1;
	if(_window->size(w,h))return -1;
	//if(sdl_board::size(w,h))return -1;
	_screen.surface(_window->get_window_surface()->surface());
	return 0;
}
int sdl_frame::size(int* w,int* h)
{
	if(!_window)return -1;
	return _window->size(w,h);
}
//----------------------------------------------
//显示窗口
int sdl_frame::show()
{
	if(!_window)return -1;
	return _window->show();
}
//----------------------------------------------
//显示窗口
int sdl_frame::hide()
{
	if(!_window)return -1;
	return _window->hide();
}
//---------------------------------------------------------------
//
//
//
//
//---------------------------------------------------------------
//窗口工具构造函数
sdl_widget::sdl_widget()
:
GUI<sdl_widget,sdl_board>()
{
	init();
}
sdl_widget::sdl_widget(const char* title,int px,int py,int pw,int ph,Uint32 pflags)
:
GUI<sdl_widget,sdl_board>()
{
	init(title,px,py,pw,ph,pflags);
}
//---------------------------------------------------------
//窗口工具析构函数
sdl_widget::~sdl_widget()
{
	//cout<<this<<endl;
}
int sdl_widget::init()
{
	if(sdl_board::init())return -1;
	return 0;
}
int sdl_widget::init(const char* title,int px,int py,int pw,int ph,Uint32 pflags)
{
	if(sdl_board::init(title,px,py,pw,ph,pflags))return -1;
	return 0;
}
int sdl_widget::sysevent(SDL_Event* e)
{
	return sdl_board::sysevent(e);
}
#endif//__SDLWINDOW_HANDLE__
