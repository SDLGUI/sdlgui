//----------------------------------------------------------------------------------------------------------------
//
//
//
//
//						文档名：						sdlwindow.h
//
//						文档创建日期：			2014年2月22日
//						文档更新日期：			2014年5月25日
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
#include "sdlbase.h"
#include <SDL2/SDL_thread.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <string.h>
//-----------------------------------------------
using namespace std;
//--------------------------------------------------
class timer_node;
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

//-------------------------------------------------------------
//
//
//							消息事件结构
//
//
//
//-------------------------------------------------------------
typedef class sdlgui_event_struct
{
	public:
		sdlgui_event_struct();
		sdlgui_event_struct(SDL_Event*,SDL_UserEvent*);
		/* 事件对象储存器 */
		SDL_Event event;
		SDL_UserEvent user_event;
		/* 列表节点 */
	//protected:
		sdlgui_event_struct *next,*last;
}*sdlgui_event_struct_ptr;
sdlgui_event_struct::sdlgui_event_struct()
{
	memset((char*)&event,0x00,sizeof(SDL_Event));
	memset((char*)&user_event,0x00,sizeof(SDL_UserEvent));
	next = NULL;
	last = NULL;
}
sdlgui_event_struct::sdlgui_event_struct(SDL_Event* e,SDL_UserEvent* ue = NULL)
{
	sdlgui_event_struct();
	if(e)memcpy((char*)&event,(char*)e,sizeof(SDL_Event));
	if(ue)memcpy((char*)&user_event,(char*)ue,sizeof(SDL_UserEvent));
}
//---------------------------------------------
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
		sdlgui_event_struct_ptr event();//GUI专用类读取事件函数
	//protected:
		sdlgui_event_struct_ptr _head_event,_end_event;
	protected:
		int event_process();
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
		
	public:
		/* 激活当前窗口 */
		int active();
		/* 显示当前窗口 */
		int show();
		/* 隐藏当前窗口 */
		int hide();
		/* 返回当前窗口的显示状态 */
		int is_show();
		/* 设置当前窗口标题 */
		int text(const char*);
		/* 
			 设置当前窗口标题,
			 参数(标题文本，标题字体，字体大小，文本颜色，渲染范围)
		 */
		int text(const char*,const char*,int,Uint32,SDL_Rect*);
		/* 返回当前窗口标题 */
		const char* text();
		/* 本地坐标 */
		int pos(int,int);
		int pos_x(int);
		int pos_x();
		int pos_y(int);
		int pos_y();
		int pos(SDL_Point);
		SDL_Point pos();
		/* 全局坐标 */
		SDL_Point global_pos();
		int global_pos(int,int);
		int global_pos_x(int);
		int global_pos_x();
		int global_pos_y(int);
		int global_pos_y();
		/* 坐标转换 */
		int target_pos_x(sdl_board*,int);
		int target_pos_y(sdl_board*,int);
		SDL_Point target_pos(sdl_board*,int,int);
		/*  窗口大小 */
		int size(int,int);
		int size(SDL_Point);
		SDL_Point size();
		SDL_Rect* rect();
		int width();
		int width(int);
		int height();
		int height(int);
		/* 设置父级窗口对象 */
		sdl_board* parent(sdl_board*);
		/* 返回父级窗口对象 */
		sdl_board* parent();
		/* 返回给定对象是否为当前窗口的子窗口 */
		int is_child(sdl_board*);
		/* 添加子级窗口 */
		template<class T>T* add(const char*,int,int,int,int,Uint32);
		template<class T>T* add(T*);
		/* 调整当前窗口Z序 */
		int z_top(sdl_board*,sdl_board*,int);
		/* 消毁当前窗口数据 */
		int destroy(int);
		//int redraw_hit();
		int redraw_hit(sdl_board*);
		//int redraw_hit(SDL_Rect*,sdl_board*);
		/* 初始化时用于绘图窗口的虚函数 */
		virtual int draw(){return 0;}
		/* 重画当前窗口 */
		int redraw();
		/* 返回给定坐标的子窗口对象 */
		sdl_board* hit_board(int,int);
		//virtual int event(SDL_Event* e){return 0;}
		//-----------------------------------------------
		/* 设置窗口透明色 */
		int color_key(int,Uint32);
		/* 设置窗口透明度 */
		int alpha(Uint8);
		/* 设置窗口混合模式 */
		int blend(SDL_BlendMode);
		int hit_rect(SDL_Rect*);
		//------------------------------------------------
		//timer_node* add_timer(int);
		/* 添加窗口计时器 */
		SDL_TimerID add_timer(int);
		/* 捕捉鼠标 */
		int capture(int);
	public:
		/* 计时器全局回调函数 */
		static Uint32 timer_callback(Uint32,void*); 
	public:
		/* 当前刷新帧数累计 */
		static int _frame_count;
		/* 全局探板数组 */
		//static sdl_board** _hit_board_ptr;
	protected:
		sdlsurface *_board;
		sdlsurface *_hit_board;
		sdl_board** _hit_board_ptr;
		sdltext *_text_board;
		SDL_Rect  _rect;
		SDL_Rect  _hit_rect;
		SDL_Point _pos,_size;
		char* _text;
		/* 文本颜色 */
		Uint32 _text_color;
		/* 文本渲染范围 */
		SDL_Rect _text_rect;
		sdl_board *_parent;
		sdl_board *_end,*_head;
		sdl_board *_next,*_last;
		int _is_show;
		int _is_destroy;
		//sdlrenderer* _renderer;
		//sdltexture* _texture;
}*sdl_board_ptr;
/* 初始全局变量 */
int sdl_board::_frame_count = 0;
//sdl_board** sdl_board::_hit_board_ptr=NULL;
//------------------------------------
//
//
// 						输入类
//
//
//
//------------------------------------
typedef class sdl_ime : public GUI<sdl_ime,sdl_board>
{
	public:
		sdl_ime();
		int init(const char*,int,int,int,int,Uint32);
		/* 输入法系统事件 */
		int sysevent(SDL_Event*);
		/* 返回当前输入法输入状态 */
		int state();
		/* 设置输入法的码表 */
		int input_method(const char*);
		/* 解析按键 */
		int input(char);
		/* 设置输入法状态为英文状态 */
		int input_en_method();
		/* 设置输入法状态为中文状态 */
		int input_cn_method();
		/* 返回当前文字 */
		const char* word();
	protected:
		/* 内部初始化 */
		int init();
		/* 根据码表解析当前编码 */
		int parse();
		/* 初始化当前编码 */
		int init_buffer();
		/* 显示编码对应的词组 */
		int show_list();
	protected:
		/* 当前输入的UTF8文字 */
		char* _cur_word;
		/*当前输入法的输入状态*/
		int _state;
		/* 输入法的码表文件路径 */
		char* _input_method_file_path;
		fstream _input_method_file;
		/* 当前编辑状态下的按键字符顺序 */
		char _word_buf[100];
		/* 存储当前编码所对应的10个词组 */
		char _word_group[10][100];
		/* 当前编辑状态下按键顺序引索 */
		int _word_buf_index;
		/* 存储当前编码所对应的10个词组引索 */
		int _word_group_index;
		/* 输入法宽度 */
		int ime_width;
}*sdl_ime_ptr;
//------------------------------------
sdl_ime::sdl_ime()
:
GUI<sdl_ime,sdl_board>()
{
	init();
}
int sdl_ime::init()
{
	if(sdl_board::init())return -1;
	//
	_cur_word = NULL;
	_input_method_file_path = NULL;
	_state = sdlgui_ime_en;
	memset(_word_buf,0x00,sizeof(char)*100);
	_word_buf_index = 0;
	_word_group_index = 0;
	ime_width = 0;
	//
	return 0;
}
int sdl_ime::init(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflag)
{
	init();
	if(sdl_board::init(ptitle,px,py,pw,ph,pflag))return -1;
	ime_width = pw;
	return 0;
}
int sdl_ime::state()
{
	return _state;
}
int sdl_ime::input_method(const char* pfile)
{
	if(!pfile)return -1;
	if(_input_method_file_path)
	{
		delete _input_method_file_path;
	}
	_input_method_file_path = new char[strlen(pfile)+1];
	memset(_input_method_file_path,0x00,sizeof(char)*strlen(pfile)+1);
	memcpy(_input_method_file_path,pfile,sizeof(char)*strlen(pfile)+1);
	return input_cn_method();
}
int sdl_ime::input_en_method()
{
	_state = sdlgui_ime_en;
	return 0;
}
int sdl_ime::input_cn_method()
{
	_state = sdlgui_ime_cn_up;
	return 0;
}
int sdl_ime::input(char ch)
{
	//return 0;
	SDL_UserEvent ue;
	SDL_Event e;
	//return 0;
	if(isalpha(ch) && (_state != sdlgui_ime_en)) _state = sdlgui_ime_cn_edit;
	switch (_state)
	{
		case sdlgui_ime_en:
			if(_parent)
			{
				_word_buf_index++;
				memset(_word_buf,0x00,_word_buf_index);
				_word_buf_index = 0;
				_word_buf[0] = ch;
				ue.type = SDL_USEREVENT;
				ue.code = sdlgui_ime_en;
				ue.data1 = (void*)_word_buf;
				e.type = SDL_USEREVENT;
				e.user = ue;
				//cout<<ue.data1<<endl;
				_parent->event(&e);
			}
		break;
		case sdlgui_ime_cn_edit:
			ue.code = sdlgui_ime_cn_up;
			switch(ch)
			{
				default:
					/* 如果输入的字母则解析编码 */
					if(isalpha(ch))
					{
						_word_buf[_word_buf_index] = ch;
						_word_buf_index++;
						parse();
					}
					else
					/* 如果输入的数字则选择编码对应的词语 */
					if(isdigit(ch))
					{
						memset(_word_buf,0x0,sizeof(char)*_word_buf_index);
						_word_buf_index = 0;
						_cur_word=_word_group[ch-SDLK_0];
						if(_parent)
						{
							ue.type = SDL_USEREVENT;
							ue.data1 = (void*)word();
							e.type = SDL_USEREVENT;
							e.user = ue;
							_parent->event(&e);
						}
						_state = sdlgui_ime_cn_up;
						init_buffer();
					}
				break;
				/* 如果输入的是空格则选择编码对应的第一个词语 */
				case SDLK_SPACE:
					memset(_word_buf,0x0,sizeof(char)*_word_buf_index);
					_word_buf_index = 0;
					_cur_word=_word_group[1];
					if(_parent)
					{
						ue.type = SDL_USEREVENT;
						ue.data1 = (void*)word();
						e.type = SDL_USEREVENT;
						e.user = ue;
						_parent->event(&e);
					}
					_state = sdlgui_ime_cn_up;
					init_buffer();
				break;
			}
		break;
		case sdlgui_ime_cn_up:
			/* 如果指定的输入窗口则发送消息 */
			if(_parent)
			{
				ue.type = SDL_USEREVENT;
				/* 处理可打印字符 */
				if(isprint(ch))
				{
					memset(_word_buf,0x0,100);
					/* 如果输入的数字 */
					if(isdigit(ch))
					{
						sprintf(_word_buf,"%c",ch);
					}
					else
					/* 如果输入的标点符号 */
					if(ispunct(ch))
					{
						switch(ch)		
						{
							case '.':
								sprintf(_word_buf,"。");
							break;
							case ',':
								sprintf(_word_buf,"，");
							break;
							case ';':
								sprintf(_word_buf,"；");
							break;
							case ':':
								sprintf(_word_buf,"：");
							break;
							case '\'':
								sprintf(_word_buf,"‘");
							break;
							case '"':
								sprintf(_word_buf,"”");
							break;
							case '<':
								sprintf(_word_buf,"《");
							break;
							case '>':
								sprintf(_word_buf,"》");
							break;
							case '[':
								sprintf(_word_buf,"【");
							break;
							case ']':
								sprintf(_word_buf,"】");
							break;
							case '!':
								sprintf(_word_buf,"！");
							break;
							case '`':
								sprintf(_word_buf,"`");
							break; 
							case '~':
								sprintf(_word_buf,"~");
							break; 
						}
					}
					ue.code = sdlgui_ime_cn_up;
					ue.data1 = (void*)_word_buf;
				}
				/* 处理不可打印的字符 */
				else
				{
					ue.code = sdlgui_ime_cn_ctrl;
					ue.data1 = (void*)(int)ch;
				}
				e.type = SDL_USEREVENT;
				e.user = ue;
				_parent->event(&e);
			}
		break;
	}
	//return 0;
	show_list();
	return 0;
}
int sdl_ime::parse()
{
	//int a,*b;
	//memset(_word_group,0x0,sizeof(_word_group));
	memset(_word_group,0x0,1000);
	memcpy(_word_group[0],_word_buf,100);
	if(!_word_buf_index)return 0;
	char *_tc;
	char _tbuf[1000];
	//int _file_pt = 0;
	int _is_parse = 1;
	if(!_input_method_file_path)return -1;
	_input_method_file.open(_input_method_file_path,ios::in);
	memset(_tbuf,0x0,1000);
	while(_is_parse)
	{
		if(strstr(_tbuf,_word_buf)!=_tbuf)
		{
			_tc = NULL;
			memset(_tbuf,0x0,1000);
			_input_method_file.getline(_tbuf,1000);
			_tc = strtok(_tbuf," ");
			//--
			_is_parse = !_input_method_file.eof();
		}
		else
		{
			_word_group_index = 0;
			while(_tc!=NULL)
			{
				_tc = strtok(NULL," ");
				if(_tc)
				{
					memcpy(_word_group[_word_group_index+1],_tc,100);
					_word_group_index++;
					if(_word_group_index >= 1000)break;
				}
			}
			_is_parse = 0;
		}
	}
	_input_method_file.close();
	return 0;
}
int sdl_ime::show_list()
{
	char _word_list[1000] = {0};
	int i=0;
	int j=0;
	for(i=0;i<_word_group_index;i++)
	{
		sprintf(_word_list+j,"[%d]%s",i,_word_group[i]);
		j+=strlen(_word_group[i])+3;
	}
	//cout<<_word_list<<endl;
	text(_word_list);
	return 0;
}
const char* sdl_ime::word()
{
	if(_cur_word)return _cur_word;
	return NULL;
}
int sdl_ime::init_buffer()
{
	//if(_cur_word)delete _cur_word;
	//_word_list = NULL;
	//_cur_word = NULL;
	memset(_word_buf,0x00,sizeof(_word_buf));
	_word_buf_index = 0;
	memset(_word_group,0x00,sizeof(_word_group));
	_word_group_index=0;
	return 0;
}
int sdl_ime::sysevent(SDL_Event* e)
{
	//cout<<e<<endl;
	//return 0;
	switch (e->type)
	{
		case SDL_MOUSEBUTTONUP:
			//cout<<_state<<endl;
			if(_state == sdlgui_ime_en)
			{
				size(ime_width,0);				
				_state = sdlgui_ime_cn_up;
			}
			else
			{
				size(_rect.h,0);
				_state = sdlgui_ime_en;
			}
			/* 这里引起错误，要调试 */
			init_buffer();
		break;
		case SDL_KEYUP:
			//cout<<(e->key.keysym.sym)<<endl;
			input(e->key.keysym.sym);
		break;
	}
	//return 0;
	return sdl_board::sysevent(e);
}
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
		virtual int sysevent(SDL_Event*);
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
		int run();
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
	public:
		sdl_ime ime;
		sdlsurface backgroup;
	protected:
		static sdl_board* _capture_win;
	protected:
		static int call_redraw(void*);
		static int all_event_process(void*);
	protected:
		sdl_board* _active_win;
		sdlwindow* _window;
		sdl_board _screen;
		SDL_Event _main_event;
		double _fps;
		SDL_Point _window_rect;
		/* 消息处理循环变量 */
		int _is_exit;
		/* 处理消息流的子级线程 */
		SDL_Thread* _event_thread;
}*sdl_frame_ptr;
sdl_board* sdl_frame::_capture_win = NULL;
//-------------------------------------------------------
//
//
//                   剪辑类
//
//
//-------------------------------------------------------
typedef class sdl_clip : public sdlsurface
{
	public:
		sdl_clip();
		sdl_clip(sdlsurface*,int,int);
		~sdl_clip();
		//用给定的剪辑宽度和高度进行裁剪。
		int clip(int,int);
		int init();
		int init(sdlsurface*,int,int);
		int init(Uint32,int,int,int,Uint32,Uint32,Uint32,Uint32);
		int row();
		int column();
		int read(int,int);
		int read();
		int write();
		int write(int,int);
		virtual sdlsurface* operator()(int,int);
		virtual sdlsurface* operator[](SDL_Point);
	protected:
		inline SDL_Rect clip_rect(int,int);
	protected:
		sdlsurface* _clip_surface;
		//sdlsurface** _sub_surface;
		SDL_Rect _clip_rect;
		int _width,_height;
		SDL_Point _sub_size;
}*sdl_clip_ptr;
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
	//为每个对象创建事件列表的头节点
	/* 关系与下面的缓冲关系一样 */
	_head_event = new sdlgui_event_struct;
	_head_event->next = _head_event;
	_head_event->last = _head_event; 
	/* 
	//为每个对象创建事件缓冲列表头节点
	让缓冲节点的第一个节点的上下指向设置为第一个节点
	尾节点的头节点永远存在且为空白消息,仅
	供检测列表使用
	 */
	_end_event = new sdlgui_event_struct;
	_end_event->last = _end_event; 
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
	//向对象事件列表末端追加一个事件
	//在末端申请一个事件节点
	_end_event->last->next = new sdlgui_event_struct(e,NULL);
	//更新新节点的上下指向
	_end_event->last = _end_event->last->next;
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
//GUI继承专用类事件处理线程
template<class T,class B>
int GUI<T,B>::event_process()
{
	sdlgui_event_struct* cur_event = NULL;
		//取出当前事件节点
		cur_event = event();
		if(cur_event)
		{
			//调整事件处理函数来处理事件
			userprocess(This,&cur_event->event);
			sysprocess(This,&cur_event->event);
			delete cur_event;
		}
		SDL_Delay(1);
	return 0;
}
//-----------------------------------------------
//GUI继承专用类读取事件列表中的有效节点
template<class T,class B>
sdlgui_event_struct_ptr GUI<T,B>::event()
{
	sdlgui_event_struct* cur_event = NULL;
	//return NULL;
	//如果事件列表头节点的前后指向节点不同则表示缓存的事件还有处理数据
	/* 
	如果事件列表头节点的向后指向存在，
	表示列表还有数据处理
	 */
	if(_head_event->next)
	{
		//cout<<this<<endl;
		//1.取出当前事件节点
		cur_event = _head_event->next;
		//2.让头节点的下个节点指向已处理事件节点的下个节点。
		_head_event->next = _head_event->next->next;
		//_head_event->next->last = _head_event;
	}
	//return 0;
	//如果事件列表头节点的向后指向为空表示缓存的事件已处理完成
	if(!_head_event->next)
	{
		/* 
			 如果尾节点的上个节点与下个节点指向不同节点，
			 表示有新加入的事件节点 
			 则把尾节点移动到头节点当中 
		 */
		if(_end_event->last != _end_event->next)
		{
			//将缓存事件放到处理列表当中
			_head_event->next = _end_event->next;
			//将缓存事件列表清空
			//_end_event->next = NULL;
			//_end_event->last= _end_event;
			//_end_event->next = _end_event->last;
		}
	}
	return cur_event;
	//return (cur_event == _head_event->last || cur_event == NULL)?NULL:cur_event;
}

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
	//cout<<"sdl_board::~sdl_board()"<<text()<<endl;
	/* 释放缓冲表面 */
	if(_board)delete _board;
	if(_hit_board)delete _hit_board;
	if(_hit_board_ptr)delete _hit_board_ptr;
	/*释放文本*/
	if(_text)delete _text;
	/* 释放文本表面 */
	if(_text_board)delete _text_board;
}
//底板初始函数
int sdl_board::init(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflags)
{
	if(sdlsurface::init(0,pw,ph,32,0,0,0,0))return -1;
	//-------------
	_rect.x = px;
	_rect.y = py;
	_rect.w = pw;
	_rect.h = ph;
	//--------------
	//if(_board)delete _board;
	_board = new sdlsurface(0,pw,ph,32,0,0,0,0);
	//----------------
	_hit_rect.w = 0;
	_hit_rect.h = 0;
	_hit_board = new sdlsurface(0,pw,ph,32,0,0,0,0);
	_hit_board->fill_rect(NULL,*(Uint32*)this);
	_hit_board->color_key(SDL_TRUE,0);
	_hit_board->surface_blend_mode(SDL_BLENDMODE_BLEND);
	/* 初始自身探板对象 */
	redraw_hit(NULL);
	//-----------------
	if(ptitle)
	{
		_text_rect.x = 0;
		_text_rect.y = 0;
		if(_text_board)delete _text_board;
		#if defined (WIN32)
		_text_board = new sdltext("c:/windows/fonts/simkai.ttf",16);
		#elif defined (LINUX) 
		_text_board = new sdltext("/usr/share/fonts/truetype/wqy/wqy-zenhei.ttc",16);
		#elif defined (__ANDROID_OS__)
		_text_board = new sdltext("/system/fonts/DroidSanSansFallback.ttf",16);
		#endif
		_text_board->render_utf8_solid(ptitle,_text_color);
	}
	//
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
	_text = NULL;
	_text_color = 0;
	_parent = NULL;
	_end = NULL;
	_head = NULL;
	_next = NULL;
	_last = NULL;
	_board = NULL;
	_text_board = NULL;
	_hit_board_ptr = NULL;
	return 0;
}
//--------------------------------------
//设置窗口底板标题
int sdl_board::text(const char* ptext)
{
	if(_text_board)
	{
		_text_board->text(ptext);
		return _text_board->render_utf8_solid(ptext,_text_color);
	}
	return -1;
}
//-----------------------------------------------
// 设置当前窗口标题,
// 参数(标题文本，标题字体，字体大小，文本颜色，渲染范围)
int sdl_board::text(const char* ptext,const char* pfont,int psize=16,Uint32 pcolor=0x000000,SDL_Rect* prect=NULL)
{
	if(!_text_board)_text_board = new sdltext(pfont,psize);
	if(_text_board)
	{
		_text_board->text(ptext,pfont,psize);
		if(prect)memcpy((char*)&_text_rect,prect,sizeof(SDL_Rect));
		return _text_board->render_utf8_solid(ptext,pcolor);
	}
	return -1;
}
//---------------------------------------
//取得窗口底板标题
const char* sdl_board::text()
{
	if(_text_board)
	return _text_board->text();
	return "";
}
//--------------------------------------
//设置窗口底板位置
int sdl_board::pos(int x,int y)
{
	_rect.x = x;
	_rect.y = y;
	return 0;
}
int sdl_board::pos(SDL_Point pt)
{
	_rect.x = pt.x;
	_rect.y = pt.y;
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
//---------------------------------------------
/* 
	获取窗口底板全局位置
	不断与父级当前坐标合并，至到没有父级
 */
SDL_Point sdl_board::global_pos()
{
	SDL_Point pt = {_rect.x,_rect.y};
	sdl_board* t =parent();
	while(t)
	{
		pt.x += t->_rect.x;
		pt.y += t->_rect.y;
		t=t->parent();
	}
	return pt;
}
//-----------------------------------------------
//设置窗口底板全局位置
int sdl_board::global_pos(int x,int y)
{
	int tx,ty;
	tx = x;
	ty = y;
	sdl_board* t = parent();
	while(t)
	{
		tx-=t->_rect.x;
		ty-=t->_rect.y;
		t = t->parent();
	}
	_rect.x = tx;
	_rect.y = ty;
	return 0;
}
//-----------------------------------------
//设置窗口底板全局X坐标
int sdl_board::global_pos_x(int x)
{
	int tx;
	tx = x;
	sdl_board* t = parent();
	while(t)
	{
		tx-=t->_rect.x;
		t = t->parent();
	}
	_rect.x = tx;
	return 0;
}
//-----------------------------------------
//设置窗口底板全局Y坐标
int sdl_board::global_pos_y(int y)
{
	int ty;
	ty = y;
	sdl_board* t = parent();
	while(t)
	{
		ty-=t->_rect.y;
		t = t->parent();
	}
	_rect.y = ty;
	return 0;
}
//-----------------------------------------
//获取窗口底板全局X坐标
int sdl_board::global_pos_x()
{
	int tx;
	tx = _rect.x;
	sdl_board* t = parent();
	while(t)
	{
		tx+=t->_rect.x;
		t = t->parent();
	}
	return tx;
}
//-----------------------------------------
//获取窗口底板全局Y坐标
int sdl_board::global_pos_y()
{
	int ty;
	ty = _rect.y;
	sdl_board* t = parent();
	while(t)
	{
		ty+=t->_rect.y;
		t = t->parent();
	}
	return ty;
}
//-------------------------------------------
//坐标转换
int sdl_board::target_pos_x(sdl_board* obj,int px)
{
	if(!obj)return -1;
	int x = global_pos_x();
	int tx = obj->global_pos_x(); 
	return (x-tx+px);
}
int sdl_board::target_pos_y(sdl_board* obj,int py)
{
	if(!obj)return -1;
	int y = global_pos_y();
	int ty = obj->global_pos_y(); 
	return (y-ty+py);
}
SDL_Point sdl_board::target_pos(sdl_board* obj,int px,int py)
{
	SDL_Point pt1 = global_pos();
	if(!obj)
	{
		pt1.x = 0;
		pt1.y = 0;
		return pt1;
	}
	SDL_Point pt2 = obj->global_pos();
	pt1.x = pt2.x-pt1.x+px;
	pt1.y = pt2.y-pt1.y+py;
	return pt1;
}
//--------------------------------------
//取得窗口底板位置
SDL_Point sdl_board::pos()
{
	SDL_Point pt={_rect.x,_rect.y};
	return pt;
}
int sdl_board::pos_x()
{
	return _rect.x;
}
int sdl_board::pos_y()
{
	return _rect.y;
}
//--------------------------------------
//设置窗口底板大小
int sdl_board::size(int w,int h)
{
	if(w>0)_rect.w = w;
	if(h>0)_rect.h = h;
	/* 申请一个临时表面 */
	sdlsurface *t = new sdlsurface(0,w,h,32,0,0,0,0);
	blit_surface(NULL,t,NULL);
	sdlsurface::init(t->surface());
	return _board->init(0,w,h,32,0,0,0,0);
}
//--------------------------------------
//设置窗口底板大小
int sdl_board::size(SDL_Point s)
{
	return size(s.x,s.y);
}
//--------------------------------------
//得到窗口底板大小
SDL_Point sdl_board::size()
{
	SDL_Point s = {_rect.w,_rect.h};
	return s;
}
//-------------------------------------
//得到窗口矩形区域
SDL_Rect* sdl_board::rect()
{
	return &_rect;
}
//-------------------------------------------
//设置窗口宽度
int sdl_board::width(int pw)
{
	_rect.w = pw;
	return 0;
}
//------------------------------------------
//得到窗口宽度
int sdl_board::width(){return _rect.w;} 
//--------------------------------------------
//设置窗口高度
int sdl_board::height(int ph)
{
	_rect.h = ph;
	return 0;
}
//-----------------------------------------
//得到窗口高度
int sdl_board::height(){return _rect.h;}
//------------------------------------------
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
//-------------------------------------
//添加子内部窗口底板
template<class T>T* sdl_board::add(const char* title,int px,int py,int pw,int ph,Uint32 pflags)
{
	T* t = dynamic_cast<T*>(new T);
	t->init(title,px,py,pw,ph,pflags);
	t->_parent = this;
	z_top(t,NULL,0);
	return t;
}
//---------------------------------------------------
//添加外部子窗口底板
template<class T>T* sdl_board::add(T* obj)
{
	if(obj)
	{
		obj->_parent = this;
		//cout<<"obj:"<<obj<<" obj->_parent:"<<obj->_parent<<":"<<this<<endl;
		z_top(obj,NULL,0);
		return obj;
	}
	return NULL;
}
//-----------------------------------------
//调整子窗口Z序
/* 
		子窗口Z序的最顶层窗口（即列表尾节点）的NEXT应为NULL 
 */
int sdl_board::z_top(sdl_board* a,sdl_board *b,int z=0)
{
	sdl_board* temp;
	//如果源窗口a不存在则返回错误
	if(a==NULL)return -1;
	//如果目标窗口b不存在则按Z序调整窗口顺序
	if(b==NULL)
	{
		switch(z)
		{
			//如果Z序为0则调整为顶序
			case 0:
				//如果没有头节点子窗口则直接设置
				if(_head==NULL)
				{
					a->_next = NULL;
					_head = a;
					_head->_last = a;
				}
				//如果已有子窗口节点
				else
				{
					//cout<<a<<endl;
					//如果节点为链表尾则直接返回
					if(a == _head->_last)return 0;
					//先把A节点脱离出来。
					if(a->_last)a->_last->_next = a->_next;	
					if(a->_next)a->_next->_last = a->_last;	
					//再把A节点放到链表尾
					_head->_last->_next = a;
					//更新A节点链表数据
					a->_last = _head->_last;
					a->_next = NULL;
					//如果调整的节点是头节点，则更新头节点到下一个节点
					if(a == _head)_head = _head->_next;
					//更新链表尾数据
					_head->_last = a;
				}
			break;
			//如果Z序指定数据则移动指针
			defalut:
				if(z>0)
				{

				}
				else
				{

				}
			break;
		}
	}
	//如果窗口B存在，则移动指定的两个子窗口Z序
	else
	{
		if(z>0)
		{

		}
		else
		if(z<0)
		{

		}
		else
		{
			//窗口B与窗口A相同表示脱离指定子窗口节点
			if(a==b)
			{
			/* 
				如果子窗口没有下个窗口
				   表示子窗口为末尾节点，
				   则分析当前子窗口是否为第一个子窗口
				    如果当前子窗口为第一个子窗口
				      则将父级窗口子节点初始化为NULL
				    否则如果当前子窗口不是第一个子窗口
				     则更新子窗口列表末尾指向
				如果当前子窗口有下个窗口
				  则分析当前子窗口是否为第一个子窗口
				    如果当前子窗口是第一个子窗口
				      则更新你父级窗口子节点的指向
				    否则如果当前子窗口不是第一个子窗口
				      则直接脱离当前子窗口
			 */
				//cout<<a->text()<<endl;
				if(a==_head)
				{
					_head = _head->_next;
					if(_head)
					{
						_head->_last = _head->_last->_next;
					}
				}
				else
				if(a==_head->_last)
				{
					_head->_last = _head->_last->_last;
					_head->_last->_next = NULL;
				}
				else
				{
					a->_next->_last = a->_last;
					a->_last->_next= a->_next;
				}
			}
			else
			{

			}
		}
	}
	return 0;
}
//--------------------------------------------------------
//消毁窗口
int sdl_board::destroy(int p=1)
{
	sdl_board* t = _head;
	_is_destroy = p;
	while(t)
	{
		t->destroy(1);
		t = t->_next;
	}
	return 0;
}
//-----------------------------------------------
//重绘窗口探板
int sdl_board::redraw_hit(sdl_board* child = NULL)
{
	SDL_Rect lrt;
	int x,y;
	/* 如果子对象存在表示复制到父级探板 */
	if(child)
	{
		memcpy(&lrt,child->rect(),sizeof(SDL_Rect));
		//lrt.x = 0;
		//lrt.y = 0;
		for(y = (lrt.y>0)?lrt.y:0;y<(lrt.h+lrt.y) && y<_rect.h;y++)
		{
			for(x=(lrt.x>0)?lrt.x:0;x<(lrt.w+lrt.x) && x<_rect.w;x++)
			{
				_hit_board_ptr[x+y*_rect.w] = child->_hit_board_ptr[(x-child->_rect.x)+(y-child->_rect.y)*child->_rect.w];
			}
		}
		return 0;
	}
	/* 如果探板大小与窗口大小不一致表示要创建探板 */
	if((_hit_rect.w-_rect.w) || (_hit_rect.h-_rect.h))
	{
		if(_hit_board_ptr)delete _hit_board_ptr;
		_hit_rect.w = _rect.w;
		_hit_rect.h = _rect.h;
		_hit_board_ptr = new sdl_board*[_hit_rect.w*_hit_rect.h];

	}
	/* 如果没有子级表示更新自身探板 */
	memcpy(&lrt,&_rect,sizeof(SDL_Rect));
	lrt.x = 0;
	lrt.y = 0;
	for(y = (lrt.y>0)?lrt.y:0;y<(lrt.h+lrt.y) && y<_rect.h;y++)
	{
		for(x=(lrt.x>0)?lrt.x:0;x<(lrt.w+lrt.x) && x<_rect.w;x++)
		{
			_hit_board_ptr[x+y*_rect.w] = this;
		}
	}
	return 0;
}
//-----------------------------------
//返回探板中指定坐标的窗口值
sdl_board* sdl_board::hit_board(int px,int py)
{
	if(_hit_board_ptr)
	{
		return _hit_board_ptr[px+py*_rect.w];
	}
	return NULL;
}
//-------------------------
//重绘底板窗口
int sdl_board::redraw()
{
	//if(_is_show == 0)return 0;
	sdl_board* temp = _head;
	sdl_board* del_board = NULL;
	SDL_Rect trc1,trc2;
	//------------------
	//如果不消毁，则处理窗口
	if(!_is_destroy)
	{
		//如果显示则绘画窗口
		if(_is_show)
		{
			blit_surface(NULL,_board,NULL);
			/* 处理窗口标签文本 */
			if(_text_board)
			{
				_text_board->blit_surface(NULL,_board,&_text_rect);
			}
			/* 重绘新探板 */
			redraw_hit();
			//处理子窗口
			while(temp)
			{
				del_board = temp;
				if(!temp->redraw())
				{
						/* 将子窗口绘制到父窗口上 */
						trc1.x = temp->rect()->x;	
						trc1.y = temp->rect()->y;	
						trc1.w = temp->rect()->w;	
						trc1.h = temp->rect()->h;	
						trc2.x = 0;
						trc2.y = 0;
						trc2.w = temp->rect()->w;
						trc2.h = temp->rect()->h;
						if(trc1.x<0)
						{
							trc1.w+=trc1.x;
							trc1.x = 0;
							trc2.x = temp->rect()->x*-1;
						}
						if(trc1.y<0)
						{
							trc1.h+=trc1.y;
							trc1.y = 0;
							trc2.y = temp->rect()->y*-1;
						}
						temp->_board->blit_surface(&trc2,_board,&trc1);
						/* 将子窗口探板绘制到父窗口上 */
						redraw_hit(temp);
						temp = temp->_next;
				}
				else
				{
					del_board = temp;
					temp = temp->_next;
					if(del_board->_parent && !del_board->_parent->z_top(del_board,del_board,0))
					{
						delete del_board;
					}
				}
			}
		}
		else
		{
			/* 不显示窗口返回0 */
			return 0;
		}
	}
	//如果消毁，则移除子级窗口节点并返回-1
	else
	if(_is_destroy)
	{
		while(temp)		
		{
			del_board = temp;
			//如果当前节点有子窗口，则跳到子窗口
			temp->destroy();
			//如果重绘函数返回-1，表示已删除子节点
			if(temp->redraw())
			{
				temp = temp->_next;
				if(del_board->_parent && !del_board->_parent->z_top(del_board,del_board,0))
				{
					delete del_board;
				}
			}
		}
		return -1;
	}
	return 0;
}
//------------------------------------
//激活底板窗口
int sdl_board::active()
{
	sdl_board* t = this;
	while(t->_parent)
	{
		t = t->_parent;
	}
	((sdl_frame*)t)->_active_win = this;
	//cout<<t<<":"<<this<<endl;
	return 0;
}
//------------------------------------------------
//捕捉鼠标
int sdl_board::capture(int p =1)
{
	if(p && !sdl_frame::_capture_win)
	{
		sdl_frame::_capture_win = this;
		return 0;
	}
	else
	if(!p)
	{
		if(!sdl_frame::_capture_win || sdl_frame::_capture_win == this)
		{
			sdl_frame::_capture_win = NULL;
			return 0;
		}
	}
	return -1;
}
//--------------------------------------------
//设置关键色
int sdl_board::color_key(int t,Uint32 color)
{
	return _board->color_key(t,color);
	//return sdlsurface::color_key(t,color);
}
//-----------------------------------------------
//设置透明度
int sdl_board::alpha(Uint8 p_alpha)
{
	return _board->surface_alpha_mod(p_alpha);
}
//-----------------------------------------------
//设置混合模式
int sdl_board::blend(SDL_BlendMode p_blend)
{
	return _board->surface_blend_mode(p_blend);
}
//-----------------------------------------------
//设置探板范围
int sdl_board::hit_rect(SDL_Rect *rt)
{
	return 0;
}
//---------------------------------------------
//添加一个计时器
//timer_node* sdl_board::add_timer(int t)
SDL_TimerID sdl_board::add_timer(int t)
{
	//return timer_node::add_timer(this,t);
	return SDL_AddTimer(t,sdl_board::timer_callback,(void*)this);
}
Uint32 sdl_board::timer_callback(Uint32 interval,void* p)
{
	//sdl_board* t = (sdl_board*)p;
	SDL_UserEvent userevent;
	SDL_Event e;
	//-----------------
	userevent.type = SDL_USEREVENT;
	userevent.code = sdlgui_event_timer;
	userevent.data1 = p;
	userevent.data2 = (void*)interval;
	//----------------
	e.type = SDL_USEREVENT;
	e.user = userevent;
	//-----------------
	SDL_PushEvent(&e);	
	//t->event(&e);
	//------------------
	return interval;
}
//---------------------------------------------
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
	if(_window)
	{
		delete _window;
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
	_active_win = this;
	_is_exit = 0;
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
	/* 创建渲染器 */
	if(_window)
	{
		/* 取窗口大小 */
		_window->size(&_window_rect.x,&_window_rect.y);
		_screen.init(ptitle,px,py,_window_rect.x,_window_rect.y,pflags);
		size(_window_rect.x,_window_rect.y);
		//_rect.h = _window_rect.y;
		//_rect.w = _window_rect.y;
	}
	_screen._surface = _window->get_window_surface()->surface();
	//创建输入法,默认隐藏
	ime.init("",0,ph-30,pw,30,1);
	ime.fill_rect(NULL,0x0000ff);
	ime.hide();
	/* 开启消息流子级线程 */
	//_event_thread = SDL_CreateThread(all_event_process,"event_process",(void*)this);
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
	sdl_board::_frame_count = 0;
	sdl_board::redraw();
	if(ime.is_show())
	{
		ime.redraw();
		ime._board->blit_surface(NULL,_board,ime.rect());
		//cout<<ime.rect()->w<<endl;
		ime.redraw_hit();
		redraw_hit(&ime);
		//ime._hit_board->blit_surface(NULL,_hit_board,ime.rect());
	}
	_board->blit_surface(NULL,&_screen,NULL);
	//_window->update_window_surface();
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
	t = hit_board(x,y);
	t = (t==0)?(sdl_board*)this : t;
	switch(e->type)
	{
		case SDL_MOUSEBUTTONDOWN:
		case SDL_FINGERDOWN:
			if(sdl_frame::_capture_win)
			{
				sdl_frame::_capture_win->event(e);
			}
			else
			{
				if(t!=_active_win)
				{
					/* 先给失去焦点的窗口发送失去焦点消息 */
					ue.type = SDL_USEREVENT;
					ue.code = sdlgui_window_focus;
					ue.data1 = (void*)0;
					ue.data2 = (void*)t;
					te.type = SDL_USEREVENT;
					te.user = ue;
					if(_active_win)_active_win->event(&te);
					/* 然后给得到焦点的窗口发送得到焦点消息 */
					ue.data1= (void*)1;
					ue.data2 = (void*)_active_win;
					te.type = SDL_USEREVENT;
					te.user = ue;
					t->event(&te);
					/* 再更新焦点状态 */
					t->active();
				}
				/* 最后发送当前消息 */
				t->event(e);
			}
			//if(t != this)t->event(e);
		break;
		case SDL_MOUSEBUTTONUP:
		case SDL_FINGERUP:
		case SDL_FINGERMOTION:
		case SDL_MOUSEMOTION:
		case SDL_MOUSEWHEEL:
			//if(t != this)t->event(e);
			if(sdl_frame::_capture_win)
			{
				sdl_frame::_capture_win->event(e);
			}
			else
			{
				t->event(e);
			}
		break;
		case SDL_KEYUP:
			//
			//if(_active_win != this)
			{
				if(ime.is_show())
				{
					ime.parent(_active_win);
					ime.event(e);
				}
				else
				{
					_active_win->event(e);
				}
			}
		break;
		case SDL_TEXTINPUT:
			//ime.input(*e->text.text);
		case SDL_KEYDOWN:
			//if(_active_win != this)_active_win->event(e);
			_active_win->event(e);
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
					_screen._surface = _window->get_window_surface()->surface();
				break;
				default:
					cout<<"Window Event"<<endl;
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
	clock_t _frame_timer;
	double sleep = 0;
	//sdltexture* tex=NULL;
	while(!_is_exit)
	{
		_frame_timer = clock();
		while(SDL_PollEvent(&_main_event))
		{
			switch(_main_event.type)
			{
				case SDL_QUIT:
					event(&_main_event);
				break;
				case SDL_WINDOWEVENT:
					event(&_main_event);
				break;
				case SDL_USEREVENT:
					/* 计时器消息分流 */
					if(_main_event.user.code == sdlgui_event_timer)
					{
							((sdl_board*)_main_event.user.data1)->event(&_main_event);
					}
					else
					{
						event(&_main_event);
					}
				break;
				default:
					/* 其它消息分流 */
					event_shunt(&_main_event);
				break;
			}
		}
		redraw();
		//
		/* 刷新屏幕 */
		_window->update_window_surface();
		/* 计算帧频 */
		_fps = 1000 / ((clock() - _frame_timer + 0.001));
		sleep = 1000/60-1000/_fps;
		sleep = (sleep>0)?sleep:0;
		SDL_Delay((sleep<(1000/60))?sleep:(1000/60));
	}
	return 0;
}
//------------------------------------------------
//窗口框架调用重画函数的全局函数
int sdl_frame::call_redraw(void* obj)
{
	sdl_frame* _this = (sdl_frame*)obj;
	while(SDL_PollEvent(&(_this->_main_event)))
	{
		//clock_t _frame_timer;
		switch(_this->_main_event.type)
		{
			case SDL_QUIT:
				exit(0);
			break;
			case 0:
			break;
			default:
				_this->event(&(_this->_main_event));
			break;
		}
		SDL_Delay(1);
	}
	return 0;  
}
//------------------------------------------------
//窗口消息流事件处理函数
int sdl_frame::all_event_process(void* obj)
{
	sdl_board* This = (sdl_board*)obj;
	sdl_board* temp = This;
	/* 退出出前一直处理消息流 */
	return 0;
	while(1)
	{
		/* 每次都从主窗口消息开始处理 */
		temp = This;
		while(temp)
		{
			/* 处理每个节点的消息流 */
			//temp->event_process();
			/* 
				 以下操作为消息节点的跳转 
					1.如果没有下个节点则跳转到上级 
					2.如果有子级则跳转到子级
			 */
			if(temp->_head)
			{
				temp = temp->_head;
			}
			else
			if(temp->_next)
			{
				temp = temp->_next;
			}
			else
			{
				temp = temp->_parent;
			}
		}
	}
}
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
	_screen._surface = _window->get_window_surface()->surface();
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
//------------------------------------------------------------------
//
//
//
//---------------------------------------------------------------------
sdl_clip::sdl_clip()
:
sdlsurface()
{
	init();
}
sdl_clip::sdl_clip(sdlsurface* clip,int w,int h)
:
sdlsurface()
{
	init(clip,w,h);	
}
sdl_clip::~sdl_clip()
{
	delete _clip_surface;	
}
int sdl_clip::init()
{
	_clip_surface = NULL;
	if(sdlsurface::init())return -1;
	return 0;
}
int sdl_clip::init(sdlsurface* pclip,int w,int h)
{
	init();
	if(pclip == NULL)return -1;
	//更新操作对象
	_clip_surface = pclip;
	_surface = pclip->surface();	
	//初始化剪辑
	return clip(w,h);
}
int sdl_clip::init(Uint32 pflags,int pw,int ph,int pdepth,Uint32 Rmask,Uint32 Gmask,Uint32 Bmask,Uint32 Amask)
{
	return	sdlsurface::init(pflags,pw,ph,pdepth,Rmask,Gmask,Bmask,Amask); 
}
//用于初始化表面剪辑
//w和h分别表示每个剪辑的宽度和高度
//这个函数会自动计算把表面分成了几个剪辑
int sdl_clip::clip(int w,int h)
{
	//return 0;
	int x,y;
	//SDL_Rect tclip;
	//先得取当前表面的宽度和高度
	int src_w = sdlsurface::clip_rect()->w;
	int src_h = sdlsurface::clip_rect()->h;
	//更新每个剪辑的高度和宽度
	_clip_rect.w = w;
	_clip_rect.h = h;
	//计算这个表面可以剪辑的行与列
	_clip_rect.x = int(src_w/_clip_rect.w+0.9);
	_clip_rect.y = int(src_h/_clip_rect.h+0.9);
	//更新剪辑数组
	if(_clip_surface)delete[] _clip_surface;
	_clip_surface = new sdlsurface[row()*column()];
	//更新每个剪辑表面
	for(y=0;y<row();y++)
	{
		for(x=0;x<column();x++)
		{
			//初始子剪辑
			_clip_surface[x+y*column()].init(0,_clip_rect.w,_clip_rect.h,32,0,0,0,0);
			//更新子剪辑表面
			read(x,y);
		}
	}
	return 0;
}
/* 读取所有剪辑 */
int sdl_clip::read()
{
	int x,y;
	for(y=0;y<column();y++)
	{
		for(x=0;x<row();x++)
		{
			read(x,y);
		}
	}
	return 0;
}
int sdl_clip::read(int x,int y)
{
	//取得指定的剪辑引索
	int tx = (x>column())?column():x;
	int ty = (y>row())?row():y;
	//取得指定剪辑的坐标
	SDL_Rect rt = clip_rect(tx,ty);
	//更新指定剪辑表面
	blit_surface(&rt,operator()(x,y),NULL);
	return 0;
}
int sdl_clip::row()
{
	return _clip_rect.y;
	return _width;
}
int sdl_clip::column()
{
	return _clip_rect.x;
	return _height;
}
int sdl_clip::write()
{
	int i,j;
	for(i=0;i<row();i++)
	{
		for(j=0;j<column();j++)
		{
			write(j,i);
		}
	}
	return 0;
}
int sdl_clip::write(int x,int y)
{
	sdlsurface* t = operator()(x,y);
	SDL_Rect rt = clip_rect(x,y);
	if(t)t->blit_surface(NULL,this,&rt);
	return  0;
}
//取得指定引索的剪辑对象
sdlsurface* sdl_clip::operator()(int x,int y)
{
	if((x+y*column()) >= row()*column())return NULL;
	if(_clip_surface)return &_clip_surface[y*column()+x];
	return NULL;
}
sdlsurface* sdl_clip::operator[](SDL_Point pt)
{
	return operator()(pt.x,pt.y);
}
//取得指定引索的剪辑范围
SDL_Rect sdl_clip::clip_rect(int x,int y)
{
	SDL_Rect rt;
	rt.x = ((x>=column())?column()-1:x)*_clip_rect.w;
	rt.y = ((y>=column())?row()-1:y)*_clip_rect.h;
	rt.w = _clip_rect.w;
	rt.h = _clip_rect.h;
	return rt;
}
//-----------------------------------------------------------------------------
//
//
//
//
//
//                           基础工具集
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
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
//
//
//  								Button 类
//
//---------------------------------------------------------------------------------------------------------
typedef class sdl_button : public GUI<sdl_button,sdl_widget>
{
	public:
		sdl_button();
		sdl_button(const char*,int,int,int,int,Uint32);
		virtual ~sdl_button();
		int init();
		int init(const char*,int,int,int,int,Uint32);
		int sysevent(SDL_Event*);
		/* 失去焦点页面 */
		sdlsurface* killfocus_page();
		/* 释放鼠标页面 */
		sdlsurface* release_page();
		/* 按下鼠标页面 */
		sdlsurface* press_page();
		/* 更新页面 */
		int update_page();
		int clip(sdlsurface*);
		int clip(const char*);
	protected:
		/* 内部初始化表面 */
		int draw();
	protected:
		sdlsurface _button_frame;
		sdl_clip _button_clip;
}*sdl_button_ptr;
//---------------------------------------------------
//
//
//
//----------------------------------------------------
//
sdl_button::sdl_button()
:
GUI<sdl_button,sdl_widget>()
{
	init();
}
sdl_button::sdl_button(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflag)
:
GUI<sdl_button,sdl_widget>()
{
	init(ptitle,px,py,pw,ph,pflag);
}
sdl_button::~sdl_button()
{

}
int sdl_button::init()
{
	if(sdl_widget::init())return -1;
	return 0;
}
int sdl_button::init(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflag)
{
	string text_str(SDL_GetPlatform());
	if(sdl_widget::init("",px,py,pw,ph,pflag))return -1;
	if(!text_str.compare("Windows"))
	{
		text(ptitle,"c:/windows/fonts/simkai.ttf",16,0);
	}
	else
	if(!text_str.compare("Linux"))
	{
		text(ptitle,"/usr/share/fonts/truetype/wqy/wqy-zenhei.ttc",16);
	}
	else
	if(!text_str.compare("Android"))
	{
		text(ptitle,"/system/fonts/DroidSanSansFallback.ttf",16);
	}
	/* 设置按钮文本渲染范围 */
	_text_rect.x = (_rect.w-_text_board->clip_rect()->w)/2;
	_text_rect.y = (_rect.h-_text_board->clip_rect()->h)/2;
	//
	_button_clip.init(0,pw*4,ph,32,0,0,0,0);
	_button_clip.clip(pw,ph);
	//-------------------------------------------
	//_button_clip(0,0)->fill_rect(NULL,0xff0000);
	//_button_clip(1,0)->fill_rect(NULL,0x00ff00);
	//_button_clip(2,0)->fill_rect(NULL,0x0000ff);
	//_button_clip(3,0)->fill_rect(NULL,0xffff00);
	//_button_clip.write();
	draw();
	_button_clip(0,0)->blit_surface(NULL,this,NULL);
	return 0;
}
int sdl_button::clip(sdlsurface* sur)
{
	if(!sur)return -1;
	//sur->blit_surface(_button_clip.clip_rect(),&_button_clip,NULL);
	sur->blit_surface(sur->clip_rect(),&_button_clip,NULL);
	_button_clip.read();
	_button_clip(0,0)->blit_surface(NULL,this,NULL);
	return 0;
}
int sdl_button::clip(const char* path)
{
	if(!path)return 0;
	_button_clip.img_load(path);
	_button_clip.read();
	_button_clip(0,0)->blit_surface(NULL,this,NULL);
	return 0;
}
sdlsurface* sdl_button::killfocus_page()
{
	return _button_clip(0,0);
}
sdlsurface* sdl_button::release_page()
{
	return _button_clip(1,0);
}
sdlsurface* sdl_button::press_page()
{
	return _button_clip(2,0);
}
int sdl_button::update_page()
{
	return _button_clip.write();

}
int sdl_button::draw()
{
	sdlsurface* tsur;
	int x,y;
	Uint32 color;
	y = _rect.w;
	y = ((y>_rect.h)?_rect.h:y)/2.0+0.5;
	/* 画离开页面 */
	tsur = _button_clip(0,0);
	for(x=0;x<y;x++)
	{
		color = 0xfff000 | ((2*x-1)*8);
		tsur->rectangle(x,x,_rect.w-x,_rect.h-x-1,color);
	}
	/* 画释放页面 */
	tsur = _button_clip(1,0);
	for(x=0;x<y;x++)
	{
		color = 0xffff00 | ((2*x-1)*8);
		tsur->rectangle(x,x,_rect.w-x,_rect.h-x-1,color);
	}
	/* 画点击页面 */
	tsur = _button_clip(2,0);
	for(x=0;x<y;x++)
	{
		color = 0xff0f00 | ((2*x-1)*8);
		tsur->rectangle(x,x,_rect.w-x,_rect.h-x-1,color);
	}
	/* 更新按钮表面 */
	_button_clip.write();
	//
	return 0;
}
int sdl_button::sysevent(SDL_Event* e)
{
	static int is_down = 0;
	SDL_Event _event;
	SDL_UserEvent _ue;
	_ue.type = SDL_USEREVENT;
	_ue.data1= this;
	switch(e->type)
	{
		case SDL_USEREVENT:
			switch(e->user.code)
			{
				case sdlgui_window_focus:
					if(*(int*)e->user.data1)
					{
						_button_clip(1,0)->blit_surface(NULL,this,NULL);
					}
				break;
			}
		break;
		case SDL_MOUSEBUTTONUP:
			if(is_down)
			{
				_ue.type = SDL_USEREVENT;
				_ue.code= sdlgui_button_click;
				_ue.data1 = this;
				_event.type = SDL_USEREVENT;
				_event.user = _ue;
				parent()->event(&_event);
			}
			_button_clip(1,0)->blit_surface(NULL,this,NULL);
			is_down = 0;
			capture(0);
		break;
		case SDL_MOUSEBUTTONDOWN:
			is_down = 1;
			_button_clip(2,0)->blit_surface(NULL,this,NULL);
			capture();
			//---------
		break;
		case SDL_KEYUP:
			_event.type = SDL_MOUSEBUTTONUP;
			event(&_event);
		break;
		case SDL_KEYDOWN:
			_event.type = SDL_MOUSEBUTTONDOWN;
			event(&_event);
		break;
	}
	return sdl_widget::sysevent(e);
}
#endif//__SDLWINDOW_HANDLE__
