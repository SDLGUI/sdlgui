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
#include <string.h>

using namespace std;

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
					//cout<<e->user.data1<<endl;
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
	cout<<"sdl_edit printf:"<<t<<endl;
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
		int init();
		/* 带参构造函数 */
		int init(const char*,int,int,int,int,Uint32);
		/* 滚动函数 */
		float scroll(float);
		/* 返回滚动点的值 */
		float scroll();
		/* 设置滚动窗口 */
		int scroll(sdl_board*);
		/* 系统事件 */
		int sysevent(SDL_Event*);
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
	if(sdl_widget::init(ptitle,px,py,pw,ph,pflags))return -1;
	return 0;
}
float sdl_scroll::scroll(float ps)
{
	SDL_Event e;
	SDL_UserEvent ue;
	if(_scroll_board)
	{
		//_scroll_board->event(NULL);
	}
	return ps;
}
float sdl_scroll::scroll()
{
	return _scroll_point;
}
int sdl_scroll::scroll(sdl_board* b)
{
	if(!b)return -1;
	_scroll_board = b;
	return 0;
}
int sdl_scroll::sysevent(SDL_Event* e)
{
	switch(e->type)
	{
		case SDL_MOUSEBUTTONDOWN:
		break;
		case SDL_MOUSEBUTTONUP:
		break;
		case SDL_MOUSEMOTION:
		break;
		case SDL_KEYDOWN:
		break;
		case SDL_KEYUP:
		break;
	}
	return sdl_widget::sysevent(e);
}
#endif// __SDLGUI_TOOLS_HANDLE__
