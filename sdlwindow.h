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
#include "gui.h"
#include "sdlboard.h"
#include "sdl_event_manager.h"
#include <SDL2/SDL_thread.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <string.h>
//-----------------------------------------------
using namespace std;
//--------------------------------------------------
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
					//ue.data1 = (void*)(int)ch;
					ue.data1 = (void*)ch;
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
	protected:
		static sdl_board* _capture_win;
	protected:
		static int call_redraw(void*);
		static int all_event_process(void*);
	protected:
		sdl_board* _active_win;
		sdlwindow* _window;
		//sdl_board _screen;
		sdlsurface _screen;
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
		//_screen.init(ptitle,px,py,_window_rect.x,_window_rect.y,pflags);
		size(_window_rect.x,_window_rect.y);
		//_rect.h = _window_rect.y;
		//_rect.w = _window_rect.y;
	}
	_screen.surface(_window->get_window_surface()->surface());
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
					cout<<t<<endl;
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
					_screen.surface(_window->get_window_surface()->surface());
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
			SDL_Delay(1);
		}
		SDL_Delay(1);
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
	delete[] _clip_surface;	
}
int sdl_clip::init()
{
	_clip_surface = NULL;
	if(sdlsurface::init())return -1;
	return 0;
}
int sdl_clip::init(sdlsurface* pclip,int w,int h)
{
	SDL_Rect* rt;
	init();
	if(pclip == NULL)return -1;
	//更新操作对象
	rt = pclip->clip_rect();
	sdlsurface::init(0,rt->w,rt->h,32,0,0,0,0);
	pclip->blit_surface(NULL,this,NULL);
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
	if(sdl_widget::init(ptitle,px,py,pw,ph,pflag))return -1;
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
						//_button_clip(1,0)->blit_surface(NULL,this,NULL);
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
			capture(1);
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
