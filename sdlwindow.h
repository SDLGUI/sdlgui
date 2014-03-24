//----------------------------------------------------------------------------------------------------------------
//
//
//
//
//						文档名：						sdlwindow.h
//
//						文档创建日期：			2014年2月22日
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
	public:
		int(*event_fun)(T*,SDL_Event*);
	public:
		T* This;
	public:
		GUI();
		virtual int event(SDL_Event*);//GUI专用类事件统一调用函数
		int event(int(*)(T*,SDL_Event*));//GU专用类内部事件处理函数（设置用户事件函数接口）
		virtual int sysevent(SDL_Event*e){};//GUI专用类系统事件处理函数的虚类
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
		int active();
		int show();
		int hide();
		int is_show();
		int text(const char*);
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
		/*  */
		int size(int,int);
		int size(SDL_Point);
		SDL_Point size();
		SDL_Rect* rect();
		sdl_board* parent();
		sdl_board* parent(sdl_board*);
		template<class T>T* add(const char*,int,int,int,int,Uint32);
		template<class T>T* add(T*);
		int z_top(sdl_board*,sdl_board*,int);
		int destroy();
		//int redraw_hit();
		int redraw_hit(sdl_board*);
		//int redraw_hit(SDL_Rect*,sdl_board*);
		int redraw();
		sdl_board* hit_board(int,int);
		//virtual int event(SDL_Event* e){return 0;}
		//-----------------------------------------------
		int color_key(int,Uint32);
		int alpha(Uint8);
		int blend(SDL_BlendMode);
		int hit_rect(SDL_Rect*);
		//------------------------------------------------
		//timer_node* add_timer(int);
		SDL_TimerID add_timer(int);
	public:
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
		SDL_Rect  *_hit_rect;
		SDL_Point _pos,_size;
		char* _text;
		sdl_board *_parent;
		sdl_board *_end,*_head;
		sdl_board *_next,*_last;
		int _is_show;
		int _is_destroy;
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
		int _word_group_index = 0;
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
	//
	return 0;
}
int sdl_ime::init(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflag)
{
	init();
	if(sdl_board::init(ptitle,px,py,pw,ph,pflag))return -1;
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
	SDL_UserEvent ue;
	SDL_Event e;
	if(isalpha(ch) && (_state != sdlgui_ime_en)) _state = sdlgui_ime_cn_edit;
	switch (_state)
	{
		case sdlgui_ime_en:
			if(_parent)_parent->event(&e);			
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
					ue.data1 = (void*)ch;
				}
				e.type = SDL_USEREVENT;
				e.user = ue;
				_parent->event(&e);
			}
		break;
	}
	show_list();
	return 0;
}
int sdl_ime::parse()
{
	int a,*b;
	//memset(_word_group,0x0,sizeof(_word_group));
	memset(_word_group,0x0,1000);
	memcpy(_word_group[0],_word_buf,100);
	if(!_word_buf_index)return 0;
	char *_tc;
	char _tbuf[1000];
	int _file_pt = 0;
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
}
int sdl_ime::show_list()
{
	char _word_list[1000] = {0};
	int i=0;
	int j=0;
	for(i;i<_word_group_index;i++)
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
	if(_cur_word)delete _cur_word;
	//_word_list = NULL;
	_cur_word = NULL;
	memset(_word_buf,0x00,sizeof(_word_buf));
	_word_buf_index = 0;
	memset(_word_group,0x00,sizeof(_word_group));
	_word_group_index=0;
	return 0;
}
int sdl_ime::sysevent(SDL_Event* e)
{
	return 0;
	switch (e->type)
	{
		case SDL_MOUSEBUTTONUP:
			//cout<<_state<<endl;
			if(_state == sdlgui_ime_en)
			{
				_state = sdlgui_ime_cn_up;
			}
			else
			{
				_state = sdlgui_ime_en;
			}
			/* 这里引起错误，要调试 */
			//init_buffer();
		break;
		case SDL_KEYUP:
			input(e->key.keysym.sym);
		break;
	}
	return 0;
	//return sdl_board::sysevent(e);
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
		int show();
		int hide();
		//------------------------------------
		double fps();
	public:
		sdl_ime ime;
		sdlsurface backgroup;
	protected:
		sdl_board* _active_win;
		static int call_redraw(void*);
		sdlwindow* _window;
		sdl_board _screen;
		SDL_Event _main_event;
		double _fps;
}*sdl_frame_ptr;
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
		int init();
		int init(sdlsurface*,int,int);
		int row();
		int column();
		int write();
		int write(int,int);
		virtual sdlsurface* operator()(int,int);
	protected:
		inline SDL_Rect clip_rect(int,int);
	protected:
		sdlsurface* _clip_surface;
		sdlsurface** _sub_surface;
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
	return sysprocess(This,e);
	//sysevent(e);
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
	init(ptitle,px,py,pw,ph,pflags);
}
//-----------------------------------------------
//底板析构函数
sdl_board::~sdl_board()
{
	//return 0;
	//destroy();
	if(_board)delete _board;
	if(_hit_board)delete _hit_board;
	if(_text)delete _text;
}
//底板初始函数
int sdl_board::init(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflags)
{
	if(init())return -1;
	if(sdlsurface::init(0,pw,ph,32,0,0,0,0))return -1;
	//-------------
	_rect.x = px;
	_rect.y = py;
	_rect.w = pw;
	_rect.h = ph;
	//--------------
	_board = new sdlsurface(0,pw,ph,32,0,0,0,0);
	//----------------
	_hit_board_ptr = new sdl_board*[pw*ph];
	_hit_board = new sdlsurface(0,pw,ph,32,0,0,0,0);
	_hit_board->fill_rect(NULL,(Uint32)this);
	_hit_board->color_key(SDL_TRUE,0);
	_hit_board->surface_blend_mode(SDL_BLENDMODE_BLEND);
	_hit_rect = NULL;
	redraw_hit(NULL);
	//-----------------
	if(ptitle)
	{
		_text_board = new sdltext("c:/windows/fonts/simkai.ttf",16);
		_text_board->render_utf8_solid(ptitle,0);
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
	_is_show = 1;
	_is_destroy = 0;
	_text = NULL;
	_parent = NULL;
	_end = NULL;
	_head = NULL;
	_next = NULL;
	_last = NULL;
	_board = NULL;
	_text_board = NULL;
	return 0;
}
//--------------------------------------
//设置窗口底板标题
int sdl_board::text(const char* ptext)
{
	int len;
	if(_text_board)
	{
		_text_board->text(ptext);
		return _text_board->render_utf8_solid(ptext,0);
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
//获取窗口底板全局位置
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
	return 0;
}
//--------------------------------------
//设置窗口底板大小
int sdl_board::size(SDL_Point s)
{
	if(s.x>0)_rect.w = s.x;
	if(s.y>0)_rect.h = s.y;
	return 0;
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
		//cout<<this<<endl;
		obj->_parent = this;
		z_top(obj,NULL,0);
		return obj;
	}
	return NULL;
}
//-----------------------------------------
//调整子窗口Z序
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
			
		}
	}
	return 0;
}
//--------------------------------------------------------
//消毁窗口
int sdl_board::destroy()
{
	sdl_board* t = _head;
	_is_destroy = 1;
	while(t)
	{
		t->destroy();
		t = t->_next;
	}
	return 0;
	//--------------------------------------------
	//以下无效
	if(parent())
	{
		if(parent()->_head == this)
		{
			_next->_last = parent()->_head->_last;
			parent()->_head = _next;
		}
		else
		if(parent()->_head->_last == this)
		{
			parent()->_head->_last = this->_last;	
		}
		else
		{

		}
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
	if(_is_show == 0)return 0;
	sdl_board* temp = _head;
	sdl_board* del_board = NULL;
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
				_text_board->blit_surface(NULL,_board,NULL);
			}
			/* 重绘新探板 */
			redraw_hit();
			_hit_board->fill_rect(NULL,(int)this);
		}
	}
	//处理子窗口
	while(temp)
	{
		del_board = temp;
		//子窗口不消毁则显示
		if(!temp->_is_destroy)
		{
			if(temp->_is_show)
			{
				/* 重绘子窗口 */
				temp->redraw();
				/* 将子窗口绘制到父窗口上 */
				temp->_board->blit_surface(NULL,_board,temp->rect());
				/* 将子窗口探板绘制到父窗口上 */
				redraw_hit(temp);
				//memmove((_hit_board_ptr+_rect.w*temp->_rect.y+temp->_rect.x),(temp->_hit_board_ptr),temp->_rect.w*temp->_rect.h);
				temp->_hit_board->blit_surface(NULL,_hit_board,temp->rect());
			}
			temp = temp->_next;
		}
		//子窗口消毁则退出链表
		else
		{
				temp = temp->_next;
				if(del_board->parent())
				{
					if(del_board->parent()->_head == del_board)
					{

					}
					else
					if(del_board->parent()->_head->_last == del_board)
					{
						del_board->parent()->_head->_last = del_board->_last;
						del_board->_last->_next = NULL;
					}
					else
					{

					}
					//delete del_board;
					//cout<<this<<endl;
				}
		}
		//SDL_Delay(1);
	}
	//------------------------------
	//处理探板范围
	if(_hit_rect)
	{
		_hit_board->fill_rect(_hit_rect,0x000000);
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
	_hit_rect = rt;
	//Uint32 _key_color = (Uint32)this + 1;
	//
	//return _board->surface_blend_mode(p_blend);
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
	_active_win = this;
}
//-------------------------
//窗口框架初始函数
int sdl_frame::init(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflags)
{
	init();
	if(sdl_board::init("",px,py,pw,ph,0))return -1;
	/* 设置窗口位置 */
	_rect.x = 0;
	_rect.y = 0;
	//-------------------
	//创建窗口
	_screen.init(ptitle,px,py,pw,ph,pflags);
	_window = new sdlwindow(ptitle,px,py,pw,ph,pflags);
	_screen._surface = _window->get_window_surface()->surface();
	//创建输入法
	ime.init("",0,ph-30,pw,30,1);
	ime.fill_rect(NULL,0x0000ff);
	/* 初始化背景 */
	//if(backgroup.init(0,pw,ph,32,0,0,0,0))return -1;
	//backgroup.fill_rect(NULL,0x000000);
	/* 申请探板对象 */
	//if(sdl_board::_hit_board_ptr)
	{
		/* 先清除以前的探板对象 */
		//delete sdl_board::_hit_board_ptr;
	}
	/* 申请新的探板对象 */
	//sdl_board::_hit_board_ptr = new sdl_board*[pw,ph];
	//memset((char*)sdl_board::_hit_board_ptr,0x00,sizeof(sdl_board)*px*py);
	//add<sdl_ime>(&ime);
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
		ime.redraw_hit();
		ime._hit_board->blit_surface(NULL,_hit_board,ime.rect());
	}
	_board->blit_surface(NULL,&_screen,NULL);
	_window->update_window_surface();
	return 0;
}
//-------------------------------------
//返回当前FPS
double sdl_frame::fps()
{
	return _fps;
}
//-------------------------
//重载窗口的系统事件处理函数。
//用于消息事件分流
int sdl_frame::sysevent(SDL_Event* e)
{
	static sdl_board* t;
	static int x,y;
	SDL_GetMouseState(&x,&y);
	t = (sdl_board*)_hit_board->pixel(x,y);
	t = hit_board(x,y);
	//cout<<hit_board(x,y)<<":"<<t<<endl;
	//t = hit_board(x,y);
	t = (t==0)?(sdl_board*)this : t;
	switch(e->type)
	{
		case SDL_MOUSEBUTTONDOWN:
			t->active();
			if(t != this)t->event(e);
		break;
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEMOTION:
		case SDL_MOUSEWHEEL:
			if(t != this)t->event(e);
		break;
		case SDL_KEYUP:
			//
			if(_active_win != this)
			{
				if(ime.is_show())
				{
					ime.parent(_active_win);
				}
				else
				{
					_active_win->event(e);
				}
			}
			//ime.event(e);
			ime.input(e->key.keysym.sym);
		break;
		case SDL_TEXTINPUT:
			//ime.input(*e->text.text);
		case SDL_KEYDOWN:
			if(_active_win != this)_active_win->event(e);
		break;
	}
	return sdl_board::sysevent(e);
}
//-------------------------------------------
//窗口框架运行函数
int sdl_frame::run()
{
	static SDL_Thread *thread;
	while(1)
	{
		SDL_PollEvent(&_main_event);
		thread = SDL_CreateThread(sdl_frame::call_redraw,"call_redraw",(void*)this);
		SDL_WaitThread(thread,NULL);
		SDL_Delay(1);
	}
	return 0;
}
//------------------------------------------------
//窗口框架调用重画函数的全局函数
int sdl_frame::call_redraw(void* obj)
{
	sdl_frame* _this = (sdl_frame*)obj;
	//while(1)
	{
		static clock_t _frame_timer;
		_frame_timer = clock();
		_this->redraw();
		switch(_this->_main_event.type)
		{
			case SDL_QUIT:
				exit(0);
			break;
			case SDL_USEREVENT:
				switch(_this->_main_event.user.code)
				{
					case sdlgui_event_timer:
						if(_this->_main_event.user.data1 == obj)
						{
							_this->event(&_this->_main_event);
						}
						else
						{
							((sdl_board*)_this->_main_event.user.data1)->event(&_this->_main_event);
						}
					break;
				}
			break;
			default:
				_this->event(&(_this->_main_event));
			break;
		}

		//cout<<clock()-_frame_timer<<endl;
		_this->_fps = 1 / ((clock() - _frame_timer)/1000.0+0.0001);
		memset((char*)&_this->_main_event,0x00,sizeof(SDL_Event));
	}
	return 0;  
}
//------------------------------------------
//更新窗口位置
int sdl_frame::pos(int x,int y)
{
	return _window->pos(x,y);
}
//----------------------------------------------
//更新窗口大小
int sdl_frame::size(int w,int h)
{
	return _window->size(w,h);
}
//----------------------------------------------
//显示窗口
int sdl_frame::show()
{
	return _window->show();
}
//----------------------------------------------
//显示窗口
int sdl_frame::hide()
{
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
int sdl_clip::init()
{
	if(sdlsurface::init())return -1;
	return 0;
}
int sdl_clip::init(sdlsurface* clip,int w,int h)
{
	init();
	int i,j;
	SDL_Rect* src_clip,tclip;
	if(clip == NULL)return -1;
	//create_rgb_surface(0,100,100,32,0,0,0,0);
	_clip_surface = clip;
	_surface = clip->surface();	
	//----------------------------------------
	src_clip = sdlsurface::clip_rect();
	_sub_size.x = w;
	_sub_size.y = h;
	_width = src_clip->w%_sub_size.x;
	_width = int(src_clip->w/_sub_size.x) + ((_width)?1:0);
	_height= src_clip->h%_sub_size.y;
	_height= int(src_clip->h/_sub_size.y) + ((_height)?1:0);
	//_clip_surface = clip;
	sdlsurface **temp = new sdlsurface*[_width*_height];
	_sub_surface= new sdlsurface*[_width*_height];
	{
		for(i = 0;i<_height;i++)
		{
			for(j = 0;j<_width;j++)
			{
				
				//cout<<i<<":"<<j<<endl;
				//continue;
				//if(_sub_surface[i*_width+j])	delete _sub_surface[i*_width+j];
				temp[i*_width+j] = new sdlsurface(0,w,h,32,0,0,0,0);
				//_sub_surface[i*_width+j] = new sdlsurface(0,w,h,32,0,0,0,0);
				tclip = clip_rect(i,j);	
				//blit_surface(&tclip,_sub_surface[i*_width+j],NULL);
				blit_surface(&tclip,temp[i*_width+j],NULL);
			}
		}
		if(_sub_surface)delete _sub_surface;
		_sub_surface = temp;
	}
	return  0;
}
int sdl_clip::row()
{
	return _width;
}
int sdl_clip::column()
{
	return _height;
}
int sdl_clip::write()
{
	int i,j;
	for(i=0;i<_height;i++)
	{
		for(j=0;j<_width;j++)
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
sdlsurface* sdl_clip::operator()(int x,int y)
{
	if(x*y >= _width*_height)return NULL;
	if(_sub_surface)return _sub_surface[y*_width+x];
	return NULL;
}
SDL_Rect sdl_clip::clip_rect(int x,int y)
{
	SDL_Rect rt;
	rt.x = ((x>column())?column():x)*_sub_size.x;
	rt.y = ((y>column())?row():y)*_sub_size.y;
	rt.w = _sub_size.x;
	rt.h = _sub_size.y;
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
		int init();
		int init(const char*,int,int,int,int,Uint32);
		int sysevent(SDL_Event*);
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
int sdl_button::init()
{
	if(sdl_widget::init())return -1;
	return 0;
}
int sdl_button::init(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflag)
{
	if(sdl_widget::init(ptitle,px,py,pw,ph,pflag))return -1;
	_button_frame.init(0,pw*4,ph,32,0,0,0,0);
	_button_clip.init(&_button_frame,pw,ph);
	//-------------------------------------------
	_button_clip(0,0)->fill_rect(NULL,0x00ff00);
	_button_clip(1,0)->fill_rect(NULL,0xff0000);
	_button_clip(2,0)->fill_rect(NULL,0x0000ff);
	_button_clip(3,0)->fill_rect(NULL,0xffff00);
	_button_clip.write();
	_button_clip(0,0)->blit_surface(NULL,this,NULL);
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
			_button_clip(0,0)->blit_surface(NULL,this,NULL);
			is_down = 0;
		break;
		case SDL_MOUSEBUTTONDOWN:
			is_down = 1;
			_button_clip(1,0)->blit_surface(NULL,this,NULL);
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
