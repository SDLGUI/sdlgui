//----------------------------------------------------------------------------------------------------------------
//
//
//
//
//						文档名：						sdltools.h
//
//						文档创建日期：			2014年2月22日
//						文档更新日期：			2014年5月02日
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
//								但不能更改本文档用//开头及用/**/包含的任何注释语句。
//						2.本文档使用者的义务
//							a)使用者不得更改本文档的文档名
//							b)本文档使用者在使用本文档时请在您的文档开始处
//								说明本文档版权归本文档创建者所有。
//							c)本文档使用者更改本文档后
//								请您上传更新后的文档到http://github.com/sdlgui/sdlgui/
//							d)本文档使用者本人承担
//								使用本文档后的所有法律责任,
//								本文档创建者不为您的文件内容承担任何法律责任。
//
//
//
//
//------------------------------------------------------------------------------------------------------------------
#ifndef __SDLGUI_TOOLS_HANDLE__
#define __SDLGUI_TOOLS_HANDLE__
#include "sdlbase.h"
#include "sdlwindow.h"
#include <iostream>
#include <ctime>
#include <string.h>

using namespace std;

class sdl_edit;
class sdl_scroll;
class sdl_view_plane;
class sdl_view;

/* --------------------------------------------
	 
	文本输入框 
	 
	 -------------------------------------------- */
typedef class sdl_edit : public GUI<sdl_edit,sdl_widget>
{
	public:
		sdl_edit();
		int init();
		int init(const char*,int,int,int,int,Uint32);
		int sysevent(SDL_Event*);
		/* 追加文本 */
		int push(const char*);
		/* 删除文本最后一个字 */
		int kill();
		/* 清除文本内容 */
		int clear();
		/* 返回文本内容长度 */
		int length();
	protected:
		int _count;
}*sdl_edit_ptr;
sdl_edit::sdl_edit()
:
GUI<sdl_edit,sdl_widget>()
{

}
int sdl_edit::init()
{
	if(sdl_widget::init())return -1;
	return 0;
}
int sdl_edit::init(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflags)
{
	if(sdl_widget::init(ptitle,px,py,pw,ph,pflags))return -1;
	fill_rect(NULL,0xffffff);
	push(ptitle);
	return 0;
}
int sdl_edit::sysevent(SDL_Event* e)
{
	//return 0;
	switch(e->type)
	{
		case SDL_USEREVENT:
			switch(e->user.code)
			{
				case sdlgui_ime_cn_up:
				case sdlgui_ime_en:
					push((char*)(e->user.data1));
				break;
				case sdlgui_ime_cn_ctrl:
					switch(*(int*)(e->user.data1))
					{
						case SDLK_BACKSPACE:
							kill();
						break;
					}
				break;
			}
		break;
	}
	return 0;
}
int sdl_edit::push(const char* p = NULL)
{
	if(p==NULL)return 0;
	_count += strlen(p);
	char* t = new char[_count];
	memset(t,0x00,_count);
	//return 0;
	t = strcat(t,text());
	strcpy(t,text());
	t = strcat(t,p);
	//text(t);
	//text("123456");
	delete t;
	return 0;
}
int sdl_edit::kill()
{
	if(!_count)return 0;
	char* t = new char[_count];
	memset(t,0x00,_count);
	memcpy(t,text(),_count-1);
	text(t);
	delete t;
	_count --;
	return 0;
}


/*----------------------------------------------------------

				滚动条


------------------------------------------------------------ */
typedef class sdl_scroll : public GUI<sdl_scroll,sdl_widget>
{
	public:
		/* 空白构造函数 */
		sdl_scroll();
		/* 带参构造函数 */
		sdl_scroll(const char*,int,int,int,int,Uint32);
		/* 空白初始化函数 */
		virtual int init();
		/* 带参构造函数 */
		virtual int init(const char*,int,int,int,int,Uint32);
		/* 滚动函数 */
		virtual float scroll(float);
		/* 设置滚动初始速度 */
		virtual int scroll(int);
		/*  */
		virtual float scroll();
		/* 返回滚动点的值 */
		virtual float point();
		/* 设置滚动点的值 */
		virtual int point(float);
		/* 发送滚动点事件 */
		virtual int scroll_event(sdl_board*);
		/* 向上滚动一格 */
		int up();
		/* 向下滚动一格 */
		int down();
		/* 返回滚动对象最高点 */
		int top();
		/* 返回滚动对象最低点 */
		int bottom();
		/* 设置滚动窗口,并设置好滚动对象的滚动高低点*/
		virtual int scroll(sdl_board*,int,int);
		/* 系统事件 */
		virtual int sysevent(SDL_Event*);
		/* 显示窗口
			参数为0时表示自动显示,为1时表示永远显示 
		 */
		int show(int);
		/* 更新滚动条 */
		int update();
	public:
		/* 滚动条背景 */
		sdlsurface bg;
		sdlsurface bar;
		/* 滚动条滑块 */
	protected:
		/* 滚动点的值 */
		float _scroll_point;
		/* 滚动窗口 */
		sdl_board* _scroll_board;
		/* 滚动设时器 */
		SDL_TimerID _scroll_timer;
		/* 滚动初始步长 */
		float _scroll_step;
		/* 滚动速度 */
		float _scroll_speed;
		/* 滚动步长系数 */
		float _scroll_step_sx;
		/* 滚动对像最高点和最低点 */
		SDL_Point _scroll_object_rect;
		/* 是否自动显示 */
		int _scroll_auto_show;
		/* 窗口滚动开始时间 */
		clock_t _scroll_start_time;
		/* 窗口滚动开始坐标 */
		float _scroll_start_y;
		/* 滚动滑块区域 */
		SDL_Rect _scroll_bar_rect;
		/* 是否滚动 */
		int _scroll_is_change;
}*sdl_scroll_ptr;
sdl_scroll::sdl_scroll()
:
GUI<sdl_scroll,sdl_widget>()
{
	init();
}
sdl_scroll::sdl_scroll(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflags)
:
GUI<sdl_scroll,sdl_widget>()
{
	init(ptitle,px,py,pw,ph,pflags);
}
int sdl_scroll::init()
{
	if(sdl_widget::init())return -1;
	return 0;
}
int sdl_scroll::init(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflags)
{
	int x,y;
	if(sdl_widget::init(ptitle,px,py,pw,ph,pflags))return -1;
	_scroll_point = 0;
	_scroll_board = NULL;
	_scroll_timer = 0;
	_scroll_auto_show = 1;
	_scroll_start_time = 0;
	_scroll_start_y = 0;
	_scroll_step = 0;
	_scroll_speed = 0;
	_scroll_step_sx = 0;
	_scroll_is_change = 0;
	//
	bar.init(1,_scroll_bar_rect.w,_scroll_bar_rect.h,32,0,0,0,0);
	bar.fill_rect(NULL,0xffff00);
	if(_scroll_bar_rect.h>15)
	{
		y = (_scroll_bar_rect.h-10)/2;
		x = (_scroll_bar_rect.w*0.2);
		//
		bar.line(x,y,_scroll_bar_rect.w-x,y,0xffffff);
		bar.line(x,y+1,_scroll_bar_rect.w-x,y+1,0xffffff);
		//
		bar.line(x,y+4,_scroll_bar_rect.w-x,y+4,0xffffff);
		bar.line(x,y+5,_scroll_bar_rect.w-x,y+5,0xffffff);
		//
		bar.line(x,y+8,_scroll_bar_rect.w-x,y+8,0xffffff);
		bar.line(x,y+9,_scroll_bar_rect.w-x,y+9,0xffffff);
		//
	}
	//
	bg.init(1,pw,ph,32,0,0,0,0);
	bg.fill_rect(NULL,0x0000ff);
	//
	update();
	return 0;
}
float sdl_scroll::scroll(float ps)
{
	return ps;
}
int sdl_scroll::scroll(int pstep)
{
	//更新滚动步长
	_scroll_step = pstep;
	//更新滚动步长系数
	_scroll_step_sx = 1.0;
	//如果没有计时器或消除了计时器,则加入计时器
	if(!_scroll_timer)_scroll_timer = add_timer(100);
	//
	return 0;
}
float sdl_scroll::scroll()
{
	return _scroll_point;
}
float sdl_scroll::point()
{
	return _scroll_point;
}
int sdl_scroll::point(float p)
{
	return update();
}
int sdl_scroll::scroll(sdl_board* b,int pt,int pb)
{
	if(!b)return -1;
	/* 滚动条控制窗口 */
	_scroll_board = b;
	/* 滚动条最高点 */
	_scroll_object_rect.x = pt;
	/* 滚动条最低点 */
	_scroll_object_rect.y = pb;
	return 0;
}
int sdl_scroll::top()
{
	return _scroll_object_rect.x;
}
int sdl_scroll::bottom()
{
	return _scroll_object_rect.y;
}
int sdl_scroll::show(int pcmd=0)
{
	return 0;
}
int sdl_scroll::update()
{
	bg.blit_surface(NULL,this,NULL);
	bar.blit_surface(NULL,this,&_scroll_bar_rect);
	return 0;
}
int sdl_scroll::scroll_event(sdl_board* obj)
{
	SDL_UserEvent ue;
	SDL_Event te;
	float p[2];
	if(!obj)return -1;
	//计算滚动窗口坐标
	p[1] = (_scroll_object_rect.y - _scroll_object_rect.x)*_scroll_point + _scroll_object_rect.x;
	p[0] = _scroll_point;
	//向指定窗口或父级窗口发送消息
	ue.type = SDL_USEREVENT;
	ue.code = sdlgui_scroll_point;
	ue.data1 = (void*)this;
	ue.data2 = (void*)p;
	//------------------------------
	te.type = SDL_USEREVENT;
	te.user = ue;
	//---------------------------------
	obj->event(&te);
	return 0;
}
int sdl_scroll::sysevent(SDL_Event* e)
{
	//SDL_UserEvent ue;
	//SDL_Event te;
	//int p;
	switch(e->type)
	{
		case SDL_MOUSEBUTTONDOWN:
		case SDL_FINGERDOWN:
			capture();
			if(!_scroll_is_change)
			{
				_scroll_start_time = clock();
				_scroll_is_change = 1;
			}
		break;
		case SDL_MOUSEBUTTONUP:
			_scroll_is_change = 0;
			scroll(int(_scroll_step*20));
			capture(0);
		break;
		case SDL_FINGERUP:
			_scroll_is_change = 0;
			//开始滚动事件
			scroll(int(_scroll_step*200));
			capture(0);
		break;
		case SDL_MOUSEMOTION:
			if(_scroll_is_change)
			{
				point(_scroll_point);
				//发送消息
				if(_scroll_board)
				{
					scroll_event(_scroll_board);
				}
				else
				if(parent())
				{
					scroll_event(parent());
				}
			}
		break;
		case SDL_KEYDOWN:
		break;
		case SDL_KEYUP:
		break;
		case SDL_USEREVENT:
		   switch(e->user.code)
			 {
				  case sdlgui_event_timer:
						//
						if((_scroll_step_sx<=0.0 )|| (_scroll_point <= 0.0)|| (_scroll_point>=1.0))
						{
							SDL_RemoveTimer(_scroll_timer);
							_scroll_timer = 0;
						}
						//发送消息
						if(_scroll_board)
						{
							scroll_event(_scroll_board);
						}
						else
						if(parent())
						{
							scroll_event(parent());
						}
					break;
			 }
		break;
	}
	return sdl_widget::sysevent(e);
}

//---------------------------------------------------------------
//
//
//
//
//						水平滚动条类
//
//
//
//
//
//
//----------------------------------------------------------------
typedef class sdl_v_scroll : public GUI<sdl_v_scroll,sdl_scroll>
{
	public:
		// 空白构造函数 //
		sdl_v_scroll();
		// 带参构造函数 //
		sdl_v_scroll(const char*,int,int,int,int,Uint32);
		// 空白初始化函数 //
		int init();
		// 带参初始化函数 //
		int init(const char*,int,int,int,int,Uint32);
		// 系统事件处理函数 //
		int sysevent(SDL_Event*);
	public:
		// 最左点 //
		int left();
		// 最右点 //
		int right();
		/* 设置滚动初始速度 */
		int scroll(int);
		int scroll(sdl_board*,int,int);
		/* 设置滚动点的值 */
		int point(float);
}*sdl_v_scroll_ptr;
sdl_v_scroll::sdl_v_scroll()
{
	init();
}
sdl_v_scroll::sdl_v_scroll(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflag)
:
GUI<sdl_v_scroll,sdl_scroll>()
{
	init(ptitle,px,py,pw,ph,pflag);
}
int sdl_v_scroll::init()
{
	if(sdl_scroll::init())return -1;
	return 0;
}
int sdl_v_scroll::init(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflag)
{
	_scroll_object_rect.x = 0;
	_scroll_object_rect.y = pw;
	_scroll_bar_rect.x = 0;
	_scroll_bar_rect.y = 0;
	_scroll_bar_rect.w = pw*0.1;
	_scroll_bar_rect.h = ph;
	if(sdl_scroll::init(ptitle,px,py,pw,ph,pflag))return -1;
	return 0;
}
int sdl_v_scroll::sysevent(SDL_Event* e)
{
	switch(e->type)
	{
		case SDL_MOUSEBUTTONDOWN:
			_scroll_start_y = e->button.x;
		break;
		case SDL_FINGERDOWN:
			_scroll_start_y = e->tfinger.x;
		break;
		case SDL_MOUSEBUTTONUP:
			//_scroll_step = (e->button.x - _scroll_start_y);
		  _scroll_step = (e->button.x - _scroll_start_y)/(clock()-_scroll_start_time+0.0001)*1;
		break;
		case SDL_FINGERUP:
			//_scroll_step = (e->tfinger.x*50 - _scroll_start_y);
		  _scroll_step = (e->tfinger.x - _scroll_start_y)/(clock()-_scroll_start_time+0.0001)*500;
		break;
		case SDL_MOUSEMOTION:
			if(_scroll_is_change)
			{
				_scroll_point = (((float)(e->button.x-global_pos_x()))/(float)_rect.w);
			}
		break;
		case SDL_FINGERMOTION:
			if(_scroll_is_change)
			{
				//_scroll_point = (((float)(e->tfinger.x-global_pos_x()))/(float)_rect.w);
			}
		break;
		case SDL_USEREVENT:
			switch(e->user.code)
			{
				case sdlgui_event_timer:
					//如果步长系数不为0，并且滑动点不为1则滑动窗口
					_scroll_step_sx -= 0.002;
					if(_scroll_step_sx<0)_scroll_step_sx = 0;
					_scroll_point += _scroll_speed*_scroll_step_sx;
					//更新滚动滑块
					point(_scroll_point);
				break;
			}
		break;
	}
	return sdl_scroll::sysevent(e);
}
int sdl_v_scroll::left()
{
	return _scroll_object_rect.x;
}
int sdl_v_scroll::right()
{
	return _scroll_object_rect.y;
}
int sdl_v_scroll::scroll(int pstep)
{
	//更新滚动步长速度
	_scroll_speed = (float)pstep/_rect.w*1.0;
	return sdl_scroll::scroll(pstep);
}
int sdl_v_scroll::scroll(sdl_board* o,int x,int y)
{
	return sdl_scroll::scroll(o,x,y);
}

int sdl_v_scroll::point(float p)
{
	int pt;
	_scroll_point = p;
	if(_scroll_point>1)
	{
		_scroll_point = 1;
	}
	else
	if(_scroll_point<0)
	{
		_scroll_point = 0;
	}
	//更新滚动滑块
	pt = (_rect.w-bar.clip_rect()->w)*_scroll_point;
	_scroll_bar_rect.x = pt;
	//
	return sdl_scroll::point(pt);
}
//-------------------------------------------------------------------------------
//
//
//
//
//
//
//						垂直滚动条类
//
//
//
//
//
//
//---------------------------------------------------------------------------------
typedef class sdl_h_scroll : public GUI<sdl_h_scroll,sdl_scroll>
{
	public:
		/* 空白构造函数 */
		sdl_h_scroll();
		/* 带参构造函数 */
		sdl_h_scroll(const char*,int,int,int,int,Uint32);
		/* 空白初始函数 */
		int init();
		/* 带参初始函数 */
		int init(const char*,int,int,int,int,Uint32);
		/* 系统事件处理函数 */
		int sysevent(SDL_Event*);
	public:
		/* 最顶点 */
		int top();
		/* 最底点 */
		int bottom();
		/* 设置滚动初始速度 */
		int scroll(int);
		/* 设置滚动对象及范围 */
		int scroll(sdl_board*,int,int);
		/* 设置滚动点的值 */
		int point(float);
}*sdl_h_scroll_ptr;
sdl_h_scroll::sdl_h_scroll()
{
	init();
}
sdl_h_scroll::sdl_h_scroll(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflag)
{
	init(ptitle,px,py,pw,ph,pflag);
}
int sdl_h_scroll::init()
{
	if(sdl_scroll::init())return -1;
	return 0;
}
int sdl_h_scroll::init(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflag)
{
	_scroll_object_rect.x = 0;
	_scroll_object_rect.y = ph;
	_scroll_bar_rect.x = 0;
	_scroll_bar_rect.y = 0;
	_scroll_bar_rect.w = pw;
	_scroll_bar_rect.h = ph*0.1;
	if(sdl_scroll::init(ptitle,px,py,pw,ph,pflag))return -1;
	return 0;
}
int sdl_h_scroll::sysevent(SDL_Event* e)
{
	switch(e->type)
	{
		case SDL_MOUSEBUTTONDOWN:
			_scroll_start_y = e->button.y;
		break;
		case SDL_FINGERDOWN:
			_scroll_start_y = e->tfinger.y;
		break;
		case SDL_MOUSEBUTTONUP:
		  _scroll_step = (e->button.y - _scroll_start_y)/(clock()-_scroll_start_time+0.0001)*1;
		break;
		case SDL_FINGERUP:
			_scroll_step = (e->tfinger.y - _scroll_start_y)/(clock()-_scroll_start_time+0.0001)*500;
		break;
		case SDL_MOUSEMOTION:
			if(_scroll_is_change)
			{
				_scroll_point = (((float)(e->button.y-global_pos_y()))/(float)_rect.h);
			}
		break;
		case SDL_USEREVENT:
			switch(e->user.code)
			{
				case sdlgui_event_timer:
					//如果步长系数不为0，并且滑动点不为1则滑动窗口
					_scroll_step_sx -= 0.02;
					if(_scroll_step_sx<0)_scroll_step_sx = 0;
					_scroll_point += _scroll_speed*_scroll_step_sx;
					//更新滚动滑块
					point(_scroll_point);
				break;
			}
		break;
	}
	return sdl_scroll::sysevent(e);
}
int sdl_h_scroll::top()
{
	return 0;
}
int sdl_h_scroll::bottom()
{
	return 0;
}
int sdl_h_scroll::scroll(int pstep)
{
	//更新滚动步长速度
	_scroll_speed = (float)pstep/_rect.h*1.0;
	return sdl_scroll::scroll(pstep);

}
int sdl_h_scroll::scroll(sdl_board* o,int a,int b)
{
	return sdl_scroll::scroll(o,a,b);
}
int sdl_h_scroll::point(float p)
{
	int pt;
	_scroll_point = p;
	if(_scroll_point>1)
	{
		_scroll_point = 1;
	}
	else
	if(_scroll_point<0)
	{
		_scroll_point = 0;
	}
	//更新滚动滑块
	pt = (_rect.h-bar.clip_rect()->h)*_scroll_point;
	_scroll_bar_rect.y = pt;
	//
	return sdl_scroll::point(pt);
}
//---------------------------------------------------------------
//
//
//
//									sdl_view类
//
//
//
//
//---------------------------------------------------------------
typedef class sdl_view_plane : public GUI<sdl_view_plane,sdl_widget>
{
	public:
		/* 视图子窗口面板空白构造函数 */
		sdl_view_plane();
		/* 视图子窗口面板带参构造函数 */
		sdl_view_plane(const char*,int,int,int,int,Uint32);
		/* 视图子窗口面板空白初始化函数 */
		int init();
		/* 视图子窗口面板带参初始化函数 */
		int init(const char*,int,int,int,int,Uint32);
		/* 视图子窗口面板系统事件处理函数 */
		int sysevent(SDL_Event*);
		/* 视图子窗口滚动控制对象 */
		int scroll_bar(sdl_v_scroll*,sdl_h_scroll*);
	protected:
		int _is_down;
		int _spte;
		sdl_v_scroll* _vertical;
		sdl_h_scroll* _horizontal;
}*sdl_view_plane_ptr;
sdl_view_plane::sdl_view_plane()
:
GUI<sdl_view_plane,sdl_widget>()
{
	init();
}
sdl_view_plane::sdl_view_plane(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflag)
:
GUI<sdl_view_plane,sdl_widget>()
{
	init(ptitle,px,py,pw,ph,pflag);
}
int sdl_view_plane::init()
{
	if(sdl_widget::init())return -1;
	return 0;
}
int sdl_view_plane::init(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflag)
{
	if(sdl_widget::init(ptitle,px,py,pw,ph,pflag))return -1;
	return 0;
}
int sdl_view_plane::scroll_bar(sdl_v_scroll* v,sdl_h_scroll* h)
{
	_vertical = v;
	_horizontal = h;
	return 0;
}
int sdl_view_plane::sysevent(SDL_Event* e)
{
	float pt;
	switch(e->type)
	{
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEMOTION:
		case SDL_FINGERUP:
		case SDL_FINGERDOWN:
		case SDL_FINGERMOTION:
			if(parent())parent()->event(e);
		break;
		case SDL_USEREVENT:
			switch(e->user.code)
			{
				case sdlgui_scroll_point:
					pt = (((float*)(e->user.data2))[1]);
					if(e->user.data1 == _vertical)
					{
						pos_x(pt);
					}
					else
					if(e->user.data1 == _horizontal)
					{
						pos_y(pt);
					}
				break;
			}
		break;
	}
	return 0;
}
typedef class sdl_view : public GUI<sdl_view,sdl_widget>
{
	public:
		/* 视图类的空白构造函数 */
		sdl_view();
		/* 视图类的带参构造函数 */
		sdl_view(const char*,int,int,int,int,Uint32);
		/* 视图类的空白构造函数 */
		int init();
		/* 视图类的带参初始化函数 */
		int init(const char*,int,int,int,int,Uint32);
		/* 系统事件处理函数 */
		int sysevent(SDL_Event*);
		/* 设置视图滚动参数 */
		int scroll(Uint32,SDL_Rect*);
	protected:
		/* 视图面板的系统函数 */
	public:
		sdl_view_plane view;
	protected:
		/* 垂直滚动条 */
		sdl_v_scroll* _vertical;
		/* 水平滚动条 */
		sdl_h_scroll* _horizontal;
		/* 滚动方式*/
		Uint32 _scroll_type;
		/* 鼠标坐标 */
		SDL_Point _mouse_pt;
		/* 鼠标拖动时间 */
		int _mouse_drag_time;
}*sdl_view_ptr;
sdl_view::sdl_view()
:
GUI<sdl_view,sdl_widget>()
{
	init();
}
sdl_view::sdl_view(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflag)
:
GUI<sdl_view,sdl_widget>()
{
	init(ptitle,px,py,pw,ph,pflag);
}
int sdl_view::init()
{
	if(sdl_widget::init())return -1;
	return 0;
}
int sdl_view::init(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflag)
{
	if(sdl_widget::init(ptitle,px,py,pw,ph,pflag))return -1;
	_vertical = NULL;
	_horizontal = NULL;
	_scroll_type = 1;
	view.init("",0,0,pw,ph,1);
	add(&view);
	return 0;
}
int sdl_view::sysevent(SDL_Event*e)
{
	float scroll_step;
	switch(e->type)
	{
		case SDL_MOUSEBUTTONDOWN:
			SDL_GetMouseState(&_mouse_pt.x,&_mouse_pt.y);
			_mouse_drag_time = clock();
		break;
		case SDL_MOUSEMOTION:
			if(_vertical)
			{
				if(e->motion.state)
				{
					_vertical->point((float)(e->motion.x-global_pos_x())/_vertical->width());
					_vertical->scroll_event(&view);
				}
			}
			if(_horizontal)
			{
				if(e->motion.state)
				{
					_horizontal->point((float)(e->motion.y-global_pos_y())/_horizontal->height());
					_horizontal->scroll_event(&view);
				}
			}
		break;
		case SDL_MOUSEBUTTONUP:
			if(_vertical)
			{
				scroll_step = (e->button.x - _mouse_pt.x)/(clock()-_mouse_drag_time+0.0001)*1;
				_vertical->scroll(scroll_step*200);
				_vertical->scroll_event(&view);
			}
			if(_horizontal)
			{
				scroll_step = (e->button.y - _mouse_pt.y)/(clock()-_mouse_drag_time+0.0001)*1;
				_horizontal->scroll(scroll_step*200);
				_horizontal->scroll_event(&view);
			}
		break;
		case SDL_USEREVENT:
			switch(e->user.code)
			{
				case sdlgui_event_timer:
				break;
				case sdlgui_scroll_point:
					if((sdl_scroll*)(e->user.data1) == _vertical)
					{
						
					}
					else
					if((sdl_scroll*)(e->user.data1) == _horizontal)
					{

					}
				break;
			}
		break;
	}
	return 0;
}
/* 
	pflag使用位标签1与2组合,
	1表示垂直滚动,
	2表示水平滚动，
	1|2表示水平与垂直滚动
	rt参数表示滚动范围
	x与w一组表示水平范围
	y与h一级表示垂直范围
 */
int sdl_view::scroll(Uint32 pflag,SDL_Rect* rt=NULL)
{
	_scroll_type = pflag;
	if(_scroll_type&1)
	{
		//水平滚动条
		if(!_vertical)
		{
			_vertical = add<sdl_v_scroll>("",0,_rect.h-30,_rect.w,30,1);
			_vertical->fill_rect(NULL,0xff00ff);
			_vertical->update();
		}
		//如果改变滚动范围
		if(rt)
		{
			_vertical->scroll(&view,rt->w,rt->x);
		}
		else
		{
			_vertical->scroll(&view,0,-_rect.w);
		}
	}
	else
	if(_vertical)
	{
		_vertical->destroy();
	}
	if(_scroll_type&2)
	{
		//垂直滚动条
		if(!_horizontal)
		{
			_horizontal= add<sdl_h_scroll>("",_rect.w - 30,0,30,_rect.h,1);
			_horizontal->fill_rect(NULL,0xff00ff);
			_horizontal->update();
		}
		//如果改变滚动范围
		if(rt)
		{
			_horizontal->scroll(&view,rt->h,rt->y);
		}
		else
		{
			_horizontal->scroll(&view,0,-_rect.h);
		}
	}
	else
	if(_horizontal)
	{
		_horizontal->destroy();
	}
	view.scroll_bar((_vertical)?_vertical:NULL,(_horizontal)?_horizontal:NULL);
	return 0;
}
//--------------------------------------------------------------
//
//
//
//
//							列表类
//
//
//
//
//
//-------------------------------------------------------------
typedef class sdl_listbox_plane : public GUI<sdl_listbox_plane,sdl_view>
{
	public:
		sdl_listbox_plane();
		sdl_listbox_plane(const char*,int,int,int,int,Uint32);
		int init();
		int init(const char*,int,int,int,int,Uint32);
		int sysevent(SDL_Event*);
	protected:
		/* 视图滚动范围 */
		SDL_Rect _view_scroll_rect;
}* sdl_listbox_plane_ptr;
sdl_listbox_plane::sdl_listbox_plane()
:
GUI<sdl_listbox_plane,sdl_view>()
{
	init();
}
sdl_listbox_plane::sdl_listbox_plane(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflag)
:
GUI<sdl_listbox_plane,sdl_view>()
{
	init(ptitle,px,py,pw,ph,pflag);
}
int sdl_listbox_plane::init()
{
	if(sdl_view::init())return -1;
	return 0;
}
int sdl_listbox_plane::init(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflag)
{
	if(sdl_view::init(ptitle,px,py,pw,ph,pflag))return -1;
	view.fill_rect(NULL,0xffffff);
	/* 设置滚动方式 */
	_view_scroll_rect.x = 0;
	_view_scroll_rect.w = 0;
	_view_scroll_rect.y = 0;
	_view_scroll_rect.h = 0;
	scroll(1,&_view_scroll_rect);
	return 0;
}
int sdl_listbox_plane::sysevent(SDL_Event* e)
{
	switch(e->type)
	{
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEMOTION:
		case SDL_FINGERDOWN:
		case SDL_FINGERUP:
		case SDL_FINGERMOTION:
			if(parent())parent()->event(e);
		break;
		case SDL_USEREVENT:
			switch(e->user.code)
			{
				case sdlgui_window_focus:
					/* 如果失去焦点，分析是否被子级窗口获取焦点 */
					if(!(int)(e->user.data1))
					{
						if(!is_child((sdl_board*)(e->user.data2)))
						{
							hide();
						}
					}
				break;
			}
		break;
	}
	return sdl_view::sysevent(e);
}
//------------------------------------------------------
typedef class sdl_listbox : public GUI<sdl_listbox,sdl_widget>
{
	public:
		sdl_listbox();
		sdl_listbox(const char*,int,int,int,int,Uint32);
		int init();
		int init(const char*,int,int,int,int,Uint32);
		int sysevent(SDL_Event*);
		/* 
			 重载窗口坐标设置函数
			 用于同步更新滑动面板坐标 
		 */
		int pos(int,int);
		int pos_x(int);
		int pos_y(int);
	public:
		/* 
			加入或移除列表项目
			当项目对象为NULL时表示移除第N个项目
			当项目对象存在时表示在第N个加入项目
		 */
		template<class T>T* item(int,T*);
		/* 
			返回第N个项目对象指针，失败时返回NULL
		 */
		template<class T>T* item(int);
		/* 
			拉开列表
			拉开时要父级窗口新建一个供列表项滑动的窗口
			参数为拉开时初始长度
			成功时返回0，失败时返回-1
		*/
		int pull(int);
		/* 
			推入列表 
			推入时把项目滑动窗口关闭
			成功时返回0，失败时返回-1
		 */
		int push();
		/* 
			选择第N项,成功时返回上次选择的ID，失败时返回-1 
		 */
		int select(int);
	protected:
		/* 项目个数 */
		int _item_count;
		/* 当前选中项目ID */
		int _current_item_id;
		/* 项目滑动面板长度 */
		int _item_plane_length;
		/* 项目滑动面板指针 */
		sdl_listbox_plane* _item_plane;
		/* 项目下拉按钮指针 */
		sdl_button* _list_button;
		/* 项目列表状态 */
		int _list_status;
}*sdl_listbox_ptr;
sdl_listbox::sdl_listbox()
:
GUI<sdl_listbox,sdl_widget>()
{
	init();
}
sdl_listbox::sdl_listbox(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflag)
:
GUI<sdl_listbox,sdl_widget>()
{
	init();
	init(ptitle,px,py,pw,ph,pflag);
}
int sdl_listbox::init()
{
	if(sdl_widget::init())return -1;
	_item_plane = NULL;
	_list_button = NULL;
	_current_item_id = 0;
	_item_plane_length = 90;
	_list_status = 0;
	return 0;
}
int sdl_listbox::init(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflag)
{
	SDL_Rect rt;
	if(sdl_widget::init(ptitle,px,py,pw,ph,pflag))return -1;
	/* 创建项目滑动面板 */
	_item_plane = new sdl_listbox_plane("",px,py+ph,pw,_item_plane_length,1);
	rt.y = -ph;
	rt.h = 0;
	_item_plane->scroll(2,&rt);
	_item_plane->fill_rect(NULL,0x0f00fa);
	return 0;
}
int sdl_listbox::pos(int px,int py)
{
	if(_item_plane)_item_plane->pos(px,py+_rect.h);
	return sdl_widget::pos(px,py);
}
int sdl_listbox::pos_x(int px)
{
	if(_item_plane)_item_plane->pos_x(px);
	return sdl_widget::pos_x(px);
}
int sdl_listbox::pos_y(int py)
{
	if(_item_plane)_item_plane->pos_y(py);
	return sdl_widget::pos_y(py);
}
int sdl_listbox::sysevent(SDL_Event* e)
{
	sdl_board* tobj;
	switch(e->type)
	{
		case SDL_MOUSEBUTTONDOWN:
			pull(0);
		break;
		case SDL_USEREVENT:
			switch(e->user.code)
			{
				case sdlgui_window_focus:
					/* 
					 当下拉列表焦点改变时 
					 分析是否被列表滑动面板获取了 
					*/
					if(!(int)(e->user.data1))
					{
						/* 先取获取焦点的对象 */
						tobj = (sdl_board*)(e->user.data2);
						/* 
							 如果焦点对象是滑动面板或滑动面板的子级窗口 
							 则处理数据，否则关闭滑动面板 
						 */
						if((tobj == _item_plane) || (_item_plane->is_child(tobj)))
						{
						}
						else
						{
							_item_plane->hide();
						}
					}
				break;
			}
		break;
	}
	return sdl_widget::sysevent(e);
}
template<class T>
T* sdl_listbox::item(int pid,T* pitem)
{
	if(pitem)
	{
		_item_plane->view.add<T>(pitem);
		return pitem;
	}
	return NULL;
}
template <class T>
T* sdl_listbox::item(int pid)
{

}
int sdl_listbox::pull(int plength=0)
{
	/* 如果指定长度不为0，更新滑动窗口长度 */
	if(plength)
	{
		_item_plane_length = plength;
		if(_item_plane)_item_plane->height(_item_plane_length);
	}
	/* 否则如果滑动面板不存在父级,则把面板加入到父级窗口 */
	if(_item_plane && !_item_plane->parent())
	{
		parent()->add<sdl_listbox_plane>(_item_plane);
	}
	/* 如果滑动面板存在,则显示面板 */
	if(_item_plane)
	{
		_item_plane->show();
	}
	return 0;
}
int sdl_listbox::push()
{
	return 0;
}
int sdl_listbox::select(int pid)
{
	return 0;
}

#endif// __SDLGUI_TOOLS_HANDLE__
