#ifndef __SDLGUI_TOOLS_HEAD__
#define __SDLGUI_TOOLS_HEAD__
#include "sdlbase.h"
#include "sdlwindow.h"
#include "sdlthread.h"
#include "sdl_event_manager.h"
using namespace std;
//----------------------------------------------------------------
//
//
//					按钮类
//
//
//----------------------------------------------------------------
typedef class sdl_button : public GUI<sdl_button,sdl_widget>
{
	public:
		sdl_button();
		sdl_button(const char*,int,int,int,int,Uint32);
		int init();
		int init(const char*,int,int,int,int,Uint32);
		int sysevent(SDL_Event*);
		int handle(int,SDL_Event*);
		int on_click(sdl_board*,void*);
		int on_release(sdl_board*,void*);
	protected:
		sdl_clip _page;		
}*sdl_button_ptr;
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
	SDL_Rect rt;
	if(sdl_widget::init(ptitle,px,py,pw,ph,pflag))return -1;
	_page.sdlsurface::init(0,pw*4,ph,32,0,0,0,0);
	_page.clip(pw,ph);
	rt.x = 0;
	rt.y = 0;
	rt.w = pw;
	rt.h = ph;
	_page.fill_rect(&rt,0x00ff00);
	rt.x = pw*1;
	_page.fill_rect(&rt,0x0000ff);
	rt.x = pw*2;
	_page.fill_rect(&rt,0xff0000);
	//
	_page.clip(1,1,this,NULL);
	return 0;
}
int sdl_button::sysevent(SDL_Event*e)
{
	switch(e->type)
	{
		default:
			break;
	}
	return sdl_widget::sysevent(e);
}
int sdl_button::handle(int id,SDL_Event* e)
{
	switch(id)
	{
		case sdlgui_mouse_click:
			on_click(this,(void*)e);
		break;
		case sdlgui_mouse_release:
			on_release(this,(void*)e);
		break;
		default:
			return sdl_board::handle(id,e);
		break;
	}
	return 0;
}
int sdl_button::on_click(sdl_board* obj,void* data)
{
	_page.clip(0,0,this,NULL);
	//return 0;
	return sdl_board::on_click(obj,data);
}
int sdl_button::on_release(sdl_board* obj,void* data)
{
	_page.clip(1,1,this,NULL);
	return 0;
	//return sdl_widget::on_release(obj,data);
}
//----------------------------------------------------------------
//
//
//
//					滚动条基类
//
//
//----------------------------------------------------------------
typedef class sdl_scroll : public GUI<sdl_scroll,sdl_widget>
{
	public:
		sdl_scroll();
		sdl_scroll(const char*,int,int,int,int,Uint32);
		virtual ~sdl_scroll();
		int init();
		int init(const char*,int,int,int,int,Uint32);
		int redraw();
		int sysevent(SDL_Event*);
		int handle(int,SDL_Event*);
		int on_timer(sdl_board*,void*);
		int on_motion(sdl_board*,void*);
		int on_release(sdl_board*,void*);
		virtual int on_scroll(sdl_board*,void*);
		float point();
		float point(float,int);
		int scroll(sdl_board*,float,float);
	public:
		/* 滑块表面 */
		sdlsurface bar;
		/* 滑条 */
		//sdlsurface line;
	protected:
		/* 当前滑动点 */
		float _point;
		/* 滑动范围 */
		SDL_Point _scroll_rect;
		/* 滑块坐标 */
		SDL_Rect _bar_rect;
		/* 滑动速度 当前滑动点与上个滑动点的差值*/
		float _speed;
		float _step;
		/* 滚动对象 */
		sdl_board* _scroll_object;
		/* 滚动条计时器 */
		SDL_TimerID _scroll_timer;
}*sdl_scroll_ptr;
sdl_scroll::sdl_scroll()
	:
		GUI<sdl_scroll,sdl_widget>()
{
	init();
}
sdl_scroll::sdl_scroll(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflag)
	:
		GUI<sdl_scroll,sdl_widget>()
{
	init(ptitle,px,py,pw,ph,pflag);
}
sdl_scroll::~sdl_scroll()
{
	if(_scroll_timer)SDL_RemoveTimer(_scroll_timer);
}
int sdl_scroll::init()
{
	if(sdl_widget::init())return -1;
	_point = 0;
	return 0;
}
int sdl_scroll::init(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflag)
{
	if(sdl_widget::init(NULL,px,py,pw,ph,pflag))return -1;
	_scroll_timer = NULL;
	_scroll_object = NULL;
	fill_rect(NULL,0x00ff00);
	register_event("on_scroll");
	connect_event("on_scroll",this,sdlgui_scroll_scroll);
	return 0;
}
float sdl_scroll::point()
{
	return _point;
}
float sdl_scroll::point(float p,int f=0)
{
	//_speed = (f)?p-_point:0;
	//_point = p;
	return p;
}
int sdl_scroll::scroll(sdl_board* obj,float start,float end)
{
	if(obj)_scroll_object = obj;
	_scroll_rect.x = start;
	_scroll_rect.y = end;
	return 0;
}
int sdl_scroll::redraw()
{
	if(sdl_widget::redraw())return -1;
	bar.blit_surface(NULL,_board,&_bar_rect);
	return 0;
}
int sdl_scroll::sysevent(SDL_Event*e)
{
	switch(e->type)
	{
		default:
		break;
	}
	return sdl_widget::sysevent(e);
}
int sdl_scroll::handle(int id,SDL_Event* e)
{
	switch(id)
	{
		case sdlgui_scroll_scroll:
			on_scroll(this,(void*)e);
		break;
	}
	return sdl_board::handle(id,e);
}
int sdl_scroll::on_timer(sdl_board* obj,void* e)
{
	if((_step<=0))
	{
		SDL_RemoveTimer(_scroll_timer);
		_scroll_timer = 0;
	}
	else
	{
		_step-=0.05;
		_speed-=_step*(_speed*0.05);
	}
	event_signal("on_scroll",(SDL_Event*)e);
	return 0;
}
int sdl_scroll::on_motion(sdl_board* obj,void* e)
{
	if(!_scroll_timer && (((SDL_Event*)e)->motion.state==SDL_BUTTON_LMASK))
	{
		_step = 1;
		_scroll_timer = add_timer(100);
	}
	return 0;
}
int sdl_scroll::on_release(sdl_board* obj,void* e)
{
	_step = 1;
}
int sdl_scroll::on_scroll(sdl_board* obj,void* e)
{
	//cout<<"scroll is:"<<this<<endl;
	return 0;
}
//----------------------------------------------
//
//
//				垂直滚动条
//
//
//----------------------------------------------
typedef class sdl_v_scroll : public GUI<sdl_v_scroll,sdl_scroll>
{
	public:
		sdl_v_scroll();
		sdl_v_scroll(const char*,int,int,int,int,Uint32);
		int init();
		int init(const char*,int,int,int,int,Uint32);
		int sysevent(SDL_Event*);
		int handle(int,SDL_Event*);
		//int on_release(sdl_board*,void*);
		int on_motion(sdl_board*,void*);
		int on_timer(sdl_board*,void*);
		float point(float,int);
	protected:
		
}*sdl_v_scroll_ptr;
sdl_v_scroll::sdl_v_scroll()
	:
		GUI<sdl_v_scroll,sdl_scroll>()
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
	if(sdl_scroll::init(ptitle,px,py,pw,ph,pflag))return -1;
	_bar_rect.x = 0;
	_bar_rect.y = 0;
	_bar_rect.w = pw;
	_bar_rect.h = ph*0.3;
	bar.init(0,_bar_rect.w,_bar_rect.h,32,0,0,0,0);
	return 0;
}
float sdl_v_scroll::point(float p,int m=0)
{
	_point = p;
	if(!m)_step = 0;
	if(_point>1)
	{
		_point = 1;
		_step = 0;
	}
	else
	if(_point<0)
	{
		_point = 0;
		_step = 0;
	}
	_bar_rect.y = _rect.h*_point;
	if(_bar_rect.y>_rect.h-_bar_rect.h)
	{
		_bar_rect.y = _rect.h-_bar_rect.h;
	}
	return _point;
}
int sdl_v_scroll::sysevent(SDL_Event*e)
{
	switch(e->type)
	{
		default:
		break;
	}
	return sdl_scroll::sysevent(e);
}
int sdl_v_scroll::handle(int id,SDL_Event* e)
{
	return sdl_scroll::handle(id,e);
}
/* 
		鼠标移动时计算垂直运动速度 
 */
int sdl_v_scroll::on_motion(sdl_board* obj,void* data)
{
	int y;
	if((((SDL_Event*)data)->motion.state==SDL_BUTTON_LMASK))
	{
		y = ((SDL_Event*)data)->motion.yrel;
		_speed = y;
	}
	return sdl_scroll::on_motion(obj,data);
}
int sdl_v_scroll::on_timer(sdl_board* obj,void* data)
{
	if(sdl_scroll::on_timer(obj,data))return -1;
	float s = _speed/(_rect.h-_bar_rect.h);
	_point+=s;
	point(_point,1);
	/* 如果指定了滚动对象，则调整对象位置 */
	if(_scroll_object)	
	{
		_scroll_object->pos_y(_scroll_rect.y+(_scroll_rect.y-_scroll_rect.x)*_point);
	}
	return 0;
}
//-------------------------------------------------
//
//
//			水平滚动条
//
//
//-------------------------------------------------
typedef class sdl_h_scroll : public GUI<sdl_h_scroll,sdl_scroll>
{
	public:
		sdl_h_scroll();
		sdl_h_scroll(const char*,int,int,int,int,Uint32);
		int init();
		int init(const char*,int,int,int,int,Uint32);
		int sysevent(SDL_Event*);
		int handle(int,SDL_Event*);
		int on_motion(sdl_board*,void*);
		int on_timer(sdl_board*,void*);
		float point(float,int);
	protected:
		
}*sdl_h_scroll_ptr;
sdl_h_scroll::sdl_h_scroll()
	:
		GUI<sdl_h_scroll,sdl_scroll>()
{
	init();
}
sdl_h_scroll::sdl_h_scroll(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflag)
	:
		GUI<sdl_h_scroll,sdl_scroll>()
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
	if(sdl_scroll::init(ptitle,px,py,pw,ph,pflag))return -1;
	_bar_rect.x = 0;
	_bar_rect.y = 0;
	_bar_rect.w = pw*0.3;
	_bar_rect.h = ph;
	bar.init(0,_bar_rect.w,_bar_rect.h,32,0,0,0,0);
	bar.fill_rect(NULL,0xff0000);
	return 0;
}
int sdl_h_scroll::sysevent(SDL_Event*e)
{
	switch(e->type)
	{
		default:
		break;
	}
	return sdl_scroll::sysevent(e);
}
int sdl_h_scroll::handle(int id,SDL_Event* e)
{
	return sdl_scroll::handle(id,e);
}
int sdl_h_scroll::on_motion(sdl_board* obj,void* data)
{
	int x;
	if((((SDL_Event*)data)->motion.state==SDL_BUTTON_LMASK))
	{
		x = ((SDL_Event*)data)->motion.xrel;
		_speed = x;
	}
	return sdl_scroll::on_motion(obj,data);
}
int sdl_h_scroll::on_timer(sdl_board* obj,void* data)
{
	if(sdl_scroll::on_timer(obj,data))return -1;
	float s = _speed/(_rect.w-_bar_rect.w);
	_point+=s;
	point(_point,1);
	/* 如果指定了滚动对象，则调整对象位置 */
	if(_scroll_object)	
	{
		_scroll_object->pos_y(_scroll_rect.y+(_scroll_rect.y-_scroll_rect.x)*_point);
	}
	return 0;
}
float sdl_h_scroll::point(float p,int m=0)
{
	_point = p;
	if(!m)_step = 0;
	if(_point>1)
	{
		_point = 1;
	}
	else
	if(_point<0)
	{
		_point = 0;
	}
	_bar_rect.x = _rect.w*_point;
	if(_bar_rect.x>_rect.w-_bar_rect.w)
	{
		_bar_rect.x = _rect.w-_bar_rect.w;
	}
	return _point;
}
#endif// __SDLGUI_TOOLS_HEAD__
