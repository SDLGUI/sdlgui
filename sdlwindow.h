//----------------------------------------------------------------------------------------------------------------
//
//
//
//
//						文档名：						sdlwindow.h
//
//						文档创建日期：			2014年2月22日
//						文档更新日期：			2014年7月28日
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
#include <vector>
#include <functional>
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
class sdl_timer_node;
class sdl_timer;
class event_signal;
class sdl_board;
template<class T,class B> class GUI;
class sdl_ime;
class sdl_frame;
class sdl_widget;
class sdl_clip;
//--------------------------------------
static sdlgui_debug bug;
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
const int sdlgui_scroll_scroll= scroll_event_macro(004);
//窗口事件类消息集合1005
#define window_event_macro(y) __event_macro__(1005,y) 
/* 消息焦点改变时发送的消息 */
const int sdlgui_window_get_focus= window_event_macro(001);
const int sdlgui_window_kill_focus= window_event_macro(002);
/* 鼠标事件集合1006 */
#define mouse_event_macro(y) __event_macro__(1006,y) 
const int sdlgui_mouse_click= mouse_event_macro(001);
const int sdlgui_mouse_db_click= mouse_event_macro(002);
const int sdlgui_mouse_release= mouse_event_macro(003);
const int sdlgui_mouse_motion= mouse_event_macro(004);
const int sdlgui_mouse_wheel= mouse_event_macro(005);
/* 按键事件集合1007 */
#define key_event_macro(y) __event_macro__(1007,y) 
const int sdlgui_key_down= key_event_macro(001);
const int sdlgui_key_up= key_event_macro(002);

/* 自定义事件ID */
#define sdlgui_custom_event 1008
#define sdlgui_custom_event_macro(x,y) (sdlgui_custom_event+x)*1000+y
//-------------------------------------------------
//
//
//
//
//						用于节点对象事件驱动
//
//
//
//
//-------------------------------------
/* 
	事件驱动类有两个公共接口
	1.
	event_signal::operator()();
	这个接口用于返回一个事件函数对象，使用者可以用这个对象来创建自定义事件处理函数
	事件处理函数格式为int [value](sdl_board&,SDL_Event&){return 0;};
	2.
	event_signal::operator()(sdl_board&,SDL_Event&);
	这个接口用于发送一个事件到全局事件处理序列，SDLGUI会自动即时处理你定义好的事件
	3.
	例子
	假如对象sdl_board test中有一个事件on_click;
	test.on_click()=[](sdl_board& obj,SDL_Event& e)
	{
		std::cout<<"on_click signal"<<std::endl;
		return 0;
	}
	这个表达式就创建了一个事件处理函数，
	当你触发on_click事件时就是调用你定义好的函数，
	向标准输出传一个"on_click"字符串。
	sdl_board test2;
	SDL_Event e;
	test.on_click(test2,e);
	这个表示式就是向SDLGUI发送一个on_click的事件
 */
class event_signal
{
	friend class sdl_frame;
	public:
		event_signal()
		{
		}
		/* 用户创建事件处理函数接口 */
		std::function<int(sdl_board&,SDL_Event&)>& operator()()
		{
			std::function<int(sdl_board&,SDL_Event&)>* t = new std::function<int(sdl_board&,SDL_Event&)>;
			_event_list.push_back(t);
			return *t;
		}
		/* 用于调用事件接口 */
		int operator()(sdl_board& obj,SDL_Event& e)
		{
			/* 临时调整测试 */
			if(!_event_list.empty())
			{
				for(auto p :_event_list)
				{
					(*p)(obj,e);	
				}
			}
			return 0;
			/* 向事件参数尾追加一个对象 */
			_event_called_board.push(&obj);
			/* 向事件参数尾追加一个事件参数 */
			SDL_Event* te = new SDL_Event;
			memcpy((char*)te,(char*)&e,sizeof(SDL_Event));
			_event_called_arg.push(te);
			/* 向全局事件序列追加一个事件 */
			event_signal::_event_queue.push(this);
			return 0;
		}
	protected:
		int call_event()
		{
			if(!_event_list.empty())
			{
				for(auto p :_event_list)
				{
					(*p)(*(_event_called_board.front()),*(_event_called_arg.front()));	
				}
				//* 消除已经调用过的参数 */
				_event_called_board.pop();
				delete _event_called_arg.front();
				_event_called_arg.pop();
			}
			return 0;
		}
	protected:
		/* 
			用于保存当前事件所处理的函数集列表
		 */
		std::vector<std::function<int(sdl_board&,SDL_Event&)>* > _event_list;
		std::queue<sdl_board*> _event_called_board;
		std::queue<SDL_Event*> _event_called_arg;
	protected:
		/* 
			用于处理全局事件序列 
		*/
		static int start()
		{
			if(!_event_queue_thread)
			{
				_event_queue_thread = SDL_CreateThread(event_process,"event_process",NULL);
			}
			return 0;
		}
		static int event_process(void* data)
		{
			event_signal* p=NULL;
			while(1)
			{
				//std::cout<<event_signal::_event_queue.size()<<std::endl;
				if(!event_signal::_event_queue.empty())
				{
					event_signal::_event_queue.front()->call_event();
					event_signal::_event_queue.pop();
				}
				SDL_Delay(1);
			}
			return 0;
		}
	protected:
		static SDL_Thread* _event_queue_thread;
		/* 
			用于保存事件全局序列 
		*/
		static std::queue<event_signal*> _event_queue;
};
std::queue<event_signal*> event_signal::_event_queue;
SDL_Thread* event_signal::_event_queue_thread=NULL;
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
		/* 设置当前窗口坐标 */
		int pos(int,int);
		int pos_x(int);
		int pos_y(int);
		/* 得到当前窗口坐标 */
		SDL_Point pos();
		int pos_x();
		int pos_y();
		/* 设置当前窗口的全局坐标 */
		/* 得到当前窗口的全局坐标 */
		SDL_Point global_pos();
		int global_pos_x();
		int global_pos_y();
		/* 坐标转换 */
		SDL_Point to_global_pos(int,int);
		int to_global_pos_x(int);
		int to_global_pos_y(int);
		SDL_Point to_local_pos(int,int);
		int to_local_pos_x(int);
		int to_local_pos_y(int);
		/* 设置当前底板大小 */
		int size(int,int);
		int width(int);
		int width();
		int height(int);
		int height();
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
		virtual int redraw();
		/* 设置底板标题 */
		int text(const char*);
		/* 给底板加入计时器*/
		SDL_TimerID add_timer(Uint32);
		//Uint32 add_sdl_timer(Uint32);
		sdl_timer_node& add_sdl_timer(Uint32);
		/* 设置底板透明度 */
		int alpha(Uint8);
		/* 设置底板混合模式 */
		int blend(SDL_BlendMode);
		/* 设置底板透明色 */
		int color_key(int,Uint32);
		/* 激活当前窗口 */
		int active();
		/* 是否捕捉当前窗口事件 */
		int capture(int);
		//-----------------------------------------------
	public:
		/* 硬事件 */
		event_signal on_click;
		event_signal on_release;
		event_signal on_motion;
		event_signal on_wheel;
		event_signal on_keydown;
		event_signal on_keyup;
		event_signal on_input;
		/* 软事件 */
		event_signal on_created;
		event_signal on_destroy;
		event_signal on_sizeed;
		event_signal on_timer;
	protected:
		static Uint32 timer_proc(Uint32,void*);
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
		//map<sdl_board*,int> _board_list;
		list<sdl_board*> _board_list;
}*sdl_board_ptr;

//------------------------------------------
//
//
//
//						自定义定时器
//
//
//
//------------------------------------------
class sdl_timer_node 
{
	friend class sdl_timer;
	Uint32 time;	
	clock_t next_time;
	sdl_board* obj;
	public:
	sdl_timer_node()
	{
		next_time = 0;
		obj = NULL;
	}
};
class sdl_timer
{
	public:
	public:
		static int start();
		static sdl_timer_node& push(Uint32,sdl_board*);
	protected:
		static int timer_process(void* data);
	protected:
		static SDL_Thread* _timer_thread;
		static std::vector<sdl_timer_node*> _node_list;

};
SDL_Thread* sdl_timer::_timer_thread = NULL;
std::vector<sdl_timer_node*> sdl_timer::_node_list;

int sdl_timer::start()
{
	if(!_timer_thread)
	{
		_timer_thread = SDL_CreateThread(sdl_timer::timer_process,"sdl_timer::timer_process",NULL);
	}
	return 0;
}
sdl_timer_node& sdl_timer::push(Uint32 i,sdl_board* obj)
{
	sdl_timer_node* t = new sdl_timer_node;
	t->time = i;
	t->obj = obj;
	sdl_timer::_node_list.push_back(t);
	return *t;
}
int sdl_timer::timer_process(void* data)
{
	SDL_Event e;
	SDL_UserEvent ue;
	vector<sdl_timer_node*>::iterator iter;
	sdl_timer_node* i;
	while(1)
	{
		if(!sdl_timer::_node_list.empty())
		{
			for(iter = sdl_timer::_node_list.begin();iter!=_node_list.end();iter++)
			{
				i = *iter;
				if(i->next_time<clock())
				{
					ue.type = SDL_USEREVENT;
					ue.code = i->time;
					e.type = SDL_USEREVENT;
					e.user = ue;
					i->obj->on_timer(*(i->obj),e);
					if(i->time)
					{
						i->next_time = clock()+i->time;
					}
					else
					{
						delete i;
						sdl_timer::_node_list.erase(iter);					
					}
				}
			}
		}
		SDL_Delay(1);
	}
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
		int clip(int,int,int,sdlsurface*,SDL_Rect*);
		int clip_width();
		int clip_height();
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
		int handle(int,SDL_Event*);
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
		int handle(int,SDL_Event*);
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
		static sdl_board* _active_win;
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
sdl_board* sdl_frame::_active_win= NULL;
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
				sdltext::font_path = "/system/fonts/DroidSansFallback.ttf";
				//_text_board = new sdltext("/system/fonts/DroidSanSansFallback.ttf",16);
			}
		}
		if(_text_board)delete _text_board;
		_text_board = new sdltext(sdltext::font_path.c_str(),16);
		if(_text_board)_text_board->render_utf8_solid(ptitle,_text_color);
		_text_rect.x = (pw-_text_board->clip_rect()->w)/2,_text_rect.y = (ph-_text_board->clip_rect()->h)/2,_text_rect.w = pw,_text_rect.h = ph;
	}
	//
	/* 发送初始化事件 */
	SDL_Event e;
	on_created(*this,e);
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
	return 0;
}
int sdl_board::pos_x(int x)
{
	_rect.x = x;
	return 0;
}
int sdl_board::pos_y(int y)
{
	_rect.y = y;
	return 0;
}
//设置当前窗口坐标
SDL_Point sdl_board::pos()
{
	SDL_Point p = {_rect.x,_rect.y};
	return p;
}
int sdl_board::pos_x()
{
	return _rect.x;
}
int sdl_board::pos_y()
{
	return _rect.y;
}
//得到当前窗口的全局坐标
SDL_Point sdl_board::global_pos()
{
	return to_global_pos(_rect.x,_rect.y);
}
int sdl_board::global_pos_x()
{
	return to_global_pos_x(_rect.x);
}
int sdl_board::global_pos_y()
{
	return to_global_pos_y(_rect.y);
}
//坐标转换
SDL_Point sdl_board::to_global_pos(int x,int y)
{
	SDL_Point p={x+_rect.x,y+_rect.y};
	sdl_board* t = _parent;
	while(t)
	{
		p.x+=t->_rect.x;
		p.y+=t->_rect.y;
		t = t->_parent;
	}
	return p;
}
int sdl_board::to_global_pos_x(int x)
{
	int px=x+_rect.x;
	sdl_board* t = _parent;
	while(t)
	{
		px+=t->_rect.x;
		t = t->_parent;
	}
	return px;
}
int sdl_board::to_global_pos_y(int y)
{
	int py=y+_rect.y;
	sdl_board* t = _parent;
	while(t)
	{
		py+=t->_rect.y;
		t = t->_parent;
	}
	return py;
}
SDL_Point sdl_board::to_local_pos(int x,int y)
{
	SDL_Point p={x-_rect.x,y-_rect.y};
	sdl_board* t = _parent;
	while(t)
	{
		p.x-=t->_rect.x;
		p.y-=t->_rect.y;
		t = t->_parent;
	}
	return p;
}
int sdl_board::to_local_pos_x(int x)
{
	int px=x-_rect.x;
	sdl_board* t = _parent;
	while(t)
	{
		px-=t->_rect.x;
		t = t->_parent;
	}
	return px;
}
int sdl_board::to_local_pos_y(int y)
{
	int py=y-_rect.y;
	sdl_board* t = _parent;
	while(t)
	{
		py-=t->_rect.y;
		t = t->_parent;
	}
	return py;
}
//设置底板大小
int sdl_board::size(int w,int h)
{
	sdlsurface tsur(0,w,h,32,0,0,0,0);
	blit_surface(NULL,&tsur,NULL);
	_rect.w = w;
	_rect.h = h;
	sdlsurface::init(0,w,h,32,0,0,0,0);
	tsur.blit_surface(NULL,this,NULL);
	_board->init(0,w,h,32,0,0,0,0);
	return 0;
}
int sdl_board::width(int w)
{
	return size(w,_rect.h);
}
int sdl_board::width()
{
	return _rect.w;
}
int sdl_board::height(int h)
{
	return size(_rect.w,h);
}
int sdl_board::height()
{
	return _rect.h;
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
	list<sdl_board*>::reverse_iterator node;// = _board_list.rbegin();
	sdl_board* board_node;
	int px,py,gw,gh;
	px = x-_rect.x;
	py = y-_rect.y;
	//find(_board_list.begin(),_board_list.end(),this);
	for(node = _board_list.rbegin();node!=_board_list.rend();node++)
	{
		board_node = *node;
		gw = board_node->_rect.x+board_node->_rect.w;
		gh = board_node->_rect.y+board_node->_rect.h;
		if(board_node->_is_show && !(board_node->_is_destroy) && px>=board_node->_rect.x && px<=gw && py>=board_node->_rect.y && py<=gh)
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
	list<sdl_board*>::iterator node;
	if(!a)return -1;
	_thread_lock.wait();
	/* 如果没有b对象表示直接插入或删除 */
	if(!b)
	{
		/* 大于0表示插入到尾 */
		if(z>0)
		{
			//_board_list.insert(pair<sdl_board*,int>(a,0));
			//_board_list.insert(a);
			_board_list.push_back(a);
		}
		else
		/* 小于0表示插入到头 */
		if(z<0)
		{
			//_board_list.insert(_board_list.begin(),pair<sdl_board*,int>(a,0));
			_board_list.push_front(a);
		}
		/* 为0表示删除 */
		else
		{
			//_board_list.erase(a);
			_board_list.remove(a);
		}
	}
	/* 如果有b对象表示将A对象与B对象进行交换 */
	else
	if(a!=b)	
	{
		if(z>0)
		{
			for(node = _board_list.begin();((*node) != b) && (node!=_board_list.end());node++);
			_board_list.remove(a);
			_board_list.insert(node,a);
		}
		else
		if(z<0)
		{
			for(node = _board_list.begin();((*node) != b) && (node!=_board_list.end());node++);
			_board_list.remove(a);
			_board_list.insert(node,a);
		}
		else
		{

		}
	}
	_thread_lock.post();
	return 0;
}
//---------------------------------------------
//销毁子级窗口参数P表示是否销毁本身
int sdl_board::destroy(int p=1)
{
	list<sdl_board*>::iterator node;
	sdl_board* node_board;
	_is_destroy = p;
	if(_is_destroy && _parent)_parent->z_top(this,NULL,0);
	for(node = _board_list.begin();node!=_board_list.end();node++)
	{
		node_board = *node;
		if(node_board->destroy(1))return -1;		
	}
	return 0;
}
//--------------------------------------------------------
//重绘底板窗口
int sdl_board::redraw()
{
	sdl_board* node_board;
	SDL_Rect prt,srt;
	list<sdl_board*>::iterator node=_board_list.begin();
	/* 如果当前底板不显示或准备销毁则不进行重绘 */
	_thread_lock.wait();
	blit_surface(NULL,_board,NULL);
	if(_text_board)
	{
		_text_board->blit_surface(NULL,_board,&_text_rect);
	}
	while(node!=_board_list.end())
	{
		node_board = *node;
		if(!node_board->_is_destroy)
		{
			if(node_board->_is_show)
			{
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
			}
		}
		node++;
	}
	_thread_lock.post();
	return 0;
}
//-----------------------------------------------
//设置底板标题
int sdl_board::text(const char* ptext)
{
	if(!_text_board)
	{
		_text_board = new sdltext(sdltext::font_path.c_str(),16);
	}
	if(_text_board)
	{
		_text_board->render_utf8_solid(ptext,_text_color);
		_text_rect.x = (_rect.w-_text_board->clip_rect()->w)/2,_text_rect.y = (_rect.h-_text_board->clip_rect()->h)/2,_text_rect.w = _rect.w,_text_rect.h = _rect.h;
		return 0;
	}
	else
	{
		return -1;
	}
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
//----------------------------------------
//给底板加入计时器
SDL_TimerID sdl_board::add_timer(Uint32 timer)
{
	return SDL_AddTimer(timer,sdl_board::timer_proc,(void*)this);
}
sdl_timer_node& sdl_board::add_sdl_timer(Uint32 timer)
{
	return sdl_timer::push(timer,this);
}
//-------------------------------------------------
//窗口计时器公共函数
Uint32 sdl_board::timer_proc(Uint32 interval,void* p)
{
	SDL_Event e;
	SDL_UserEvent ue;
	if(p)
	{
		ue.type = SDL_USEREVENT;
		ue.code = interval;
		ue.data1 = p;
		e.type = SDL_USEREVENT;
		e.user = ue;
		SDL_PushEvent(&e);
		//((sdl_board*)p)->on_timer(*((sdl_board*)p),e);
	}
	return interval;
}
//--------------------------------------------------
//设置底板透明度
int sdl_board::alpha(Uint8 a)
{
	if(_board)
	{
		return _board->surface_alpha_mod(a);
	}
	return -1;
}
//----------------------------------------------
//设置底板混合模式
int sdl_board::blend(SDL_BlendMode b)
{
	if(_board)
	{
		return _board->surface_blend_mode(b);
	}
	return -1;
}
//----------------------------------------------
//设置底板透明色
int sdl_board::color_key(int flag,Uint32 color)
{
	if(_board)
	{
		return _board->color_key(flag,color);
	}
	return -1;
}
//-----------------------------------------------
//激活当前底板
int sdl_board::active()
{
	sdl_board* p = _parent;
	sdl_board* t;
	sdl_board* d = this;
	list<sdl_board*>::reverse_iterator r;
	if(sdl_frame::_active_win == this)return 0;
	while(p)
	{
		t = *(p->_board_list.rbegin());
		p->z_top(d,t,1);
		p = p->_parent;
		d = d->_parent;
	}
	if(sdl_frame::_active_win)
	{
		//sdl_frame::_active_win->event_signal("on_kill_focus",(SDL_Event*)this);
	}
	//event_signal("on_get_focus",(SDL_Event*)sdl_frame::_active_win);
	sdl_frame::_active_win = this;
	return 0;
}
//------------------------------------------------
//是否捕捉当前窗口事件
int sdl_board::capture(int p=1)
{
	/* 
		 P为1表示捕捉窗口，但如果现在已经有窗口被捕捉，则返回-1 
			如果当前捕捉窗口就是本窗口，但更新捕捉窗口时直接返回-1 
			如果要释放捕捉窗口，但本窗口又不是被捕捉的窗口，则返回-1(表示不给本窗口发送信息)
	 */
	if(((sdl_frame::_capture_win==this) && p) || ((sdl_frame::_capture_win!=this) && (!p)))
	{
		return -1;
	}
	if(p)
	{
		sdl_frame::_capture_win = this;
	}
	else
	{
		sdl_frame::_capture_win = NULL;
	}
	return 0;
}
//---------------------------------------------
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
int sdl_clip::clip(int key_color,int ps,int pe,sdlsurface* dst,SDL_Rect *rt = NULL)
{
	if(key_color>=0)
	{
		color_key(1,key_color);
	}
	return clip(ps,pe,dst,rt);
}
int sdl_clip::clip_width()
{
	return _w;
}
int sdl_clip::clip_height()
{
	return _h;
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
	_redraw_thread = NULL;
	//_is_exit = 0;
	_is_redraw = 1;
	return 0;
}
//-------------------------
//窗口框架初始函数
int sdl_frame::init(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflags)
{
	string cur_platform;
	if(sdl_board::init("",0,0,pw,ph,0))return -1;
	//-------------------
	//创建窗口
	_window = new sdlwindow(ptitle,px,py,pw,ph,pflags);
	sdl_frame::_window_list.insert(pair<Uint32,sdl_frame*>(SDL_GetWindowID(_window->window()),this));
	/* 调整窗口 */
	if(_window)
	{
		cur_platform = SDL_GetPlatform();
		/* 取窗口大小 */
		_window->size(&_window_rect.x,&_window_rect.y);
		if(!cur_platform.compare("Android"))
		{
			/* 调整窗口大小 */
			size(_window_rect.x,_window_rect.y);
		}
		else
		{
			_window_rect.x = pw;
			_window_rect.y = ph;
			_screen.surface(_window->get_window_surface()->surface());
		}
	}
	/* 开启消息流子级线程 */
	//_event_thread = SDL_CreateThread(all_event_process,"event_process",(void*)this);
	/* 开启重绘流子级线程 */
	_redraw_thread = SDL_CreateThread(redraw_thread,"redraw_thread",(void*)this);
	/* 激活新窗口 */
	if(sdl_frame::_active_win)
	{
		active();
	}
	else
	{
		sdl_frame::_active_win = this;
	}
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
	return 0;//_window->update_window_surface();
}
//----------------------------------------
//重画函数子线程处理函数
int sdl_frame::redraw_thread(void* data)
{
	clock_t _frame_timer;
	double sleep = 0;
	sdl_frame* f = (sdl_frame*)data;
	if(!f)return -1;
	while(f->_is_redraw)
	{
		_frame_timer = clock();
		//
		f->redraw();
		//
		//f->_window->update_window_surface();
		/* 计算帧频 */
		f->_fps = 1000 / ((clock() - _frame_timer + 0.001));
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
	sdl_board* t;
	int x,y;
	SDL_Event te;
	SDL_UserEvent ue;
	switch(e->type)
	{
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
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
	if(sdl_frame::_capture_win)
	{
		t = sdl_frame::_capture_win;
	}
	else
	{
		t = child(x,y);
	}
	t = (t==0)?(sdl_board*)this : t;
	switch(e->type)
	{
		case SDL_MOUSEBUTTONDOWN:
		case SDL_FINGERDOWN:
			//bug<<"test"<<"..."<<1;
			//bug.out_file("test.txt");
			//t->on_click(*this,*e);
			//if(t != this)
			//cout<<"down:"<<t<<endl;
			{
				//t->event(e);
				//if(e->button.clicks==2)
				{
					//t->event_signal("on_db_click",e);
				}
				//else
				{
					//t->event_signal("on_click",e);
					t->on_click(*t,*e);
				}
			}
		break;
		case SDL_MOUSEBUTTONUP:
		case SDL_FINGERUP:
			//cout<<"up:"<<t<<endl;
			//if(t != this)
			{
				//t->event(e);
				//t->event_signal("on_release",e);
				t->on_release(*t,*e);
			}
		break;
		case SDL_FINGERMOTION:
		case SDL_MOUSEMOTION:
			//if(t != this)
			{
				//t->event(e);
				t->on_motion(*t,*e);
			}
		break;
		case SDL_MOUSEWHEEL:
			//if(t != this)
			{
				//t->event(e);
				//t->event_signal("on_wheel",e);
				t->on_wheel(*t,*e);
			}
		break;
		case SDL_KEYUP:
			if(sdl_frame::_active_win)
			{
				t = sdl_frame::_active_win;
			}
			//t->event(e);
			//t->event_signal("on_key_up",e);
			t->on_keyup(*t,*e);
		break;
		case SDL_TEXTINPUT:
			//ime.input(*e->text.text);
		case SDL_KEYDOWN:
			if(sdl_frame::_active_win)
			{
				t = sdl_frame::_active_win;
			}
			//t->event(e);
			//t->event_signal("on_key_down",e);
			t->on_keydown(*t,*e);
		break;
	}
	return 0;
}
//---------------------------------------------
//重载窗口委托入口函数
int sdl_frame::handle(int id,SDL_Event*e)
{
	return 0;
}
//--------------------------------------------
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
	map<Uint32,sdl_frame*>::iterator _node;
	sdl_frame* _node_window;
	SDL_Event e;
	/* 启动事件序列管理 */
	event_signal::start();
	/* 启动计时器管理 */
	//sdl_timer::start();
	/* 接收事件 */
	while(!sdl_frame::_is_exit)
	{
		if(sdl_frame::_window_list.empty())
		{
			sdl_frame::_is_exit = 1;
		}
		else
		{
			memset((char*)&e,0x00,sizeof(e));
			memset((char*)&sdl_frame::_main_event,0x00,sizeof(sdl_frame::_main_event));
			while(SDL_PollEvent(&sdl_frame::_main_event))
			{
				/* 确定事件窗口 */
				_node = _window_list.find(sdl_frame::_main_event.window.windowID);
				if(_node==_window_list.end())
				{
					_node = _window_list.begin();
				}
				_node_window = (sdl_frame*)(_node->second);
				/* 创建事件 */
				switch(sdl_frame::_main_event.type)
				{
					case SDL_QUIT:
						_node_window->event(&sdl_frame::_main_event);
					break;
					case SDL_WINDOWEVENT:
						_node_window->event(&sdl_frame::_main_event);
					break;
					case SDL_USEREVENT:
						/* 计时器消息分流 */
						//if(sdl_frame::_main_event.user.code == sdlgui_event_timer)
						{
							//((sdl_board*)sdl_frame::_main_event.user.data1)->event(&_main_event);
						}
						//else
						{
							((sdl_board*)sdl_frame::_main_event.user.data1)->on_timer(*(sdl_board*)(sdl_frame::_main_event.user.data1),sdl_frame::_main_event);
							//_node_window->event(&sdl_frame::_main_event);
						}
					break;
					default:
						/* 其它消息分流 */
						_node_window->event_shunt(&sdl_frame::_main_event);
					break;
				}
				//memset((char*)&sdl_frame::_main_event,0x00,sizeof(sdl_frame::_main_event));
				/* 事件线程解锁 */
				//sdl_event_manager::_event_thread_lock.unlock();
			}
			for(_node = _window_list.begin();_node!=_window_list.end();_node++)
			{
				_node_window = (sdl_frame*)_node->second;
				_node_window->_window->update_window_surface();
			}
		}
		SDL_Delay(1);
	}
	//sdl_event_manager::destroy();
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
	if(sdl_board::size(w,h))return -1;
	if(_window->size(&_window_rect.x,&_window_rect.y))return -1;
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
int sdl_widget::handle(int id,SDL_Event* e)
{
	return sdl_board::handle(id,e);
}
int sdl_widget::sysevent(SDL_Event* e)
{
	return sdl_board::sysevent(e);
}
#endif//__SDLWINDOW_HANDLE__
