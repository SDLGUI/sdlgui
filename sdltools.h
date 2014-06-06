//----------------------------------------------------------------------------------------------------------------
//
//
//
//
//						�ĵ�����						sdltools.h
//
//						�ĵ��������ڣ�			2014��2��22��
//						�ĵ��������ڣ�			2014��5��02��
//						�ĵ������ߣ�				����
//						�ĵ������ߣ�				����
//						�ĵ���������ϵ��ʽ��Email:twtfcu3@126.com
//																QQ:12880312(twtfcu3@126.com)
//																��վ:http://sdl.my-mx.cn
//
//						��Ȩ˵����
//						1.���ĵ�ʹ���ߵ�Ȩ��
//							a)���ĵ�ʹ���߿�����ʱ���ñ��ĵ����������ļ���
//							b)���ĵ�ʹ���߿�����ʱ�޸ı��ĵ���Ч�������ݣ�
//								�����ܸ��ı��ĵ���//��ͷ����/**/�������κ�ע����䡣
//						2.���ĵ�ʹ���ߵ�����
//							a)ʹ���߲��ø��ı��ĵ����ĵ���
//							b)���ĵ�ʹ������ʹ�ñ��ĵ�ʱ���������ĵ���ʼ��
//								˵�����ĵ���Ȩ�鱾�ĵ����������С�
//							c)���ĵ�ʹ���߸��ı��ĵ���
//								�����ϴ����º���ĵ���http://github.com/sdlgui/sdlgui/
//							d)���ĵ�ʹ���߱��˳е�
//								ʹ�ñ��ĵ�������з�������,
//								���ĵ������߲�Ϊ�����ļ����ݳе��κη������Ρ�
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
	 
	�ı������ 
	 
	 -------------------------------------------- */
typedef class sdl_edit : public GUI<sdl_edit,sdl_widget>
{
	public:
		sdl_edit();
		int init();
		int init(const char*,int,int,int,int,Uint32);
		int sysevent(SDL_Event*);
		/* ׷���ı� */
		int push(const char*);
		/* ɾ���ı����һ���� */
		int kill();
		/* ����ı����� */
		int clear();
		/* �����ı����ݳ��� */
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

				������


------------------------------------------------------------ */
typedef class sdl_scroll : public GUI<sdl_scroll,sdl_widget>
{
	public:
		/* �հ׹��캯�� */
		sdl_scroll();
		/* ���ι��캯�� */
		sdl_scroll(const char*,int,int,int,int,Uint32);
		/* �հ׳�ʼ������ */
		virtual int init();
		/* ���ι��캯�� */
		virtual int init(const char*,int,int,int,int,Uint32);
		/* �������� */
		virtual float scroll(float);
		/* ���ù�����ʼ�ٶ� */
		virtual int scroll(int);
		/*  */
		virtual float scroll();
		/* ���ع������ֵ */
		virtual float point();
		/* ���ù������ֵ */
		virtual int point(float);
		/* ���͹������¼� */
		virtual int scroll_event(sdl_board*);
		/* ���Ϲ���һ�� */
		int up();
		/* ���¹���һ�� */
		int down();
		/* ���ع���������ߵ� */
		int top();
		/* ���ع���������͵� */
		int bottom();
		/* ���ù�������,�����úù�������Ĺ����ߵ͵�*/
		virtual int scroll(sdl_board*,int,int);
		/* ϵͳ�¼� */
		virtual int sysevent(SDL_Event*);
		/* ��ʾ����
			����Ϊ0ʱ��ʾ�Զ���ʾ,Ϊ1ʱ��ʾ��Զ��ʾ 
		 */
		int show(int);
		/* ���¹����� */
		int update();
	public:
		/* ���������� */
		sdlsurface bg;
		sdlsurface bar;
		/* ���������� */
	protected:
		/* �������ֵ */
		float _scroll_point;
		/* �������� */
		sdl_board* _scroll_board;
		/* ������ʱ�� */
		SDL_TimerID _scroll_timer;
		/* ������ʼ���� */
		float _scroll_step;
		/* �����ٶ� */
		float _scroll_speed;
		/* ��������ϵ�� */
		float _scroll_step_sx;
		/* ����������ߵ����͵� */
		SDL_Point _scroll_object_rect;
		/* �Ƿ��Զ���ʾ */
		int _scroll_auto_show;
		/* ���ڹ�����ʼʱ�� */
		clock_t _scroll_start_time;
		/* ���ڹ�����ʼ���� */
		float _scroll_start_y;
		/* ������������ */
		SDL_Rect _scroll_bar_rect;
		/* �Ƿ���� */
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
	//���¹�������
	_scroll_step = pstep;
	//���¹�������ϵ��
	_scroll_step_sx = 1.0;
	//���û�м�ʱ���������˼�ʱ��,������ʱ��
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
	/* ���������ƴ��� */
	_scroll_board = b;
	/* ��������ߵ� */
	_scroll_object_rect.x = pt;
	/* ��������͵� */
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
	//���������������
	p[1] = (_scroll_object_rect.y - _scroll_object_rect.x)*_scroll_point + _scroll_object_rect.x;
	p[0] = _scroll_point;
	//��ָ�����ڻ򸸼����ڷ�����Ϣ
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
			//��ʼ�����¼�
			scroll(int(_scroll_step*200));
			capture(0);
		break;
		case SDL_MOUSEMOTION:
			if(_scroll_is_change)
			{
				point(_scroll_point);
				//������Ϣ
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
						//������Ϣ
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
//						ˮƽ��������
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
		// �հ׹��캯�� //
		sdl_v_scroll();
		// ���ι��캯�� //
		sdl_v_scroll(const char*,int,int,int,int,Uint32);
		// �հ׳�ʼ������ //
		int init();
		// ���γ�ʼ������ //
		int init(const char*,int,int,int,int,Uint32);
		// ϵͳ�¼������� //
		int sysevent(SDL_Event*);
	public:
		// ����� //
		int left();
		// ���ҵ� //
		int right();
		/* ���ù�����ʼ�ٶ� */
		int scroll(int);
		int scroll(sdl_board*,int,int);
		/* ���ù������ֵ */
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
					//�������ϵ����Ϊ0�����һ����㲻Ϊ1�򻬶�����
					_scroll_step_sx -= 0.002;
					if(_scroll_step_sx<0)_scroll_step_sx = 0;
					_scroll_point += _scroll_speed*_scroll_step_sx;
					//���¹�������
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
	//���¹��������ٶ�
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
	//���¹�������
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
//						��ֱ��������
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
		/* �հ׹��캯�� */
		sdl_h_scroll();
		/* ���ι��캯�� */
		sdl_h_scroll(const char*,int,int,int,int,Uint32);
		/* �հ׳�ʼ���� */
		int init();
		/* ���γ�ʼ���� */
		int init(const char*,int,int,int,int,Uint32);
		/* ϵͳ�¼������� */
		int sysevent(SDL_Event*);
	public:
		/* ��� */
		int top();
		/* ��׵� */
		int bottom();
		/* ���ù�����ʼ�ٶ� */
		int scroll(int);
		/* ���ù������󼰷�Χ */
		int scroll(sdl_board*,int,int);
		/* ���ù������ֵ */
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
					//�������ϵ����Ϊ0�����һ����㲻Ϊ1�򻬶�����
					_scroll_step_sx -= 0.02;
					if(_scroll_step_sx<0)_scroll_step_sx = 0;
					_scroll_point += _scroll_speed*_scroll_step_sx;
					//���¹�������
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
	//���¹��������ٶ�
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
	//���¹�������
	pt = (_rect.h-bar.clip_rect()->h)*_scroll_point;
	_scroll_bar_rect.y = pt;
	//
	return sdl_scroll::point(pt);
}
//---------------------------------------------------------------
//
//
//
//									sdl_view��
//
//
//
//
//---------------------------------------------------------------
typedef class sdl_view_plane : public GUI<sdl_view_plane,sdl_widget>
{
	public:
		/* ��ͼ�Ӵ������հ׹��캯�� */
		sdl_view_plane();
		/* ��ͼ�Ӵ��������ι��캯�� */
		sdl_view_plane(const char*,int,int,int,int,Uint32);
		/* ��ͼ�Ӵ������հ׳�ʼ������ */
		int init();
		/* ��ͼ�Ӵ��������γ�ʼ������ */
		int init(const char*,int,int,int,int,Uint32);
		/* ��ͼ�Ӵ������ϵͳ�¼������� */
		int sysevent(SDL_Event*);
		/* ��ͼ�Ӵ��ڹ������ƶ��� */
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
		/* ��ͼ��Ŀհ׹��캯�� */
		sdl_view();
		/* ��ͼ��Ĵ��ι��캯�� */
		sdl_view(const char*,int,int,int,int,Uint32);
		/* ��ͼ��Ŀհ׹��캯�� */
		int init();
		/* ��ͼ��Ĵ��γ�ʼ������ */
		int init(const char*,int,int,int,int,Uint32);
		/* ϵͳ�¼������� */
		int sysevent(SDL_Event*);
		/* ������ͼ�������� */
		int scroll(Uint32,SDL_Rect*);
	protected:
		/* ��ͼ����ϵͳ���� */
	public:
		sdl_view_plane view;
	protected:
		/* ��ֱ������ */
		sdl_v_scroll* _vertical;
		/* ˮƽ������ */
		sdl_h_scroll* _horizontal;
		/* ������ʽ*/
		Uint32 _scroll_type;
		/* ������� */
		SDL_Point _mouse_pt;
		/* ����϶�ʱ�� */
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
	pflagʹ��λ��ǩ1��2���,
	1��ʾ��ֱ����,
	2��ʾˮƽ������
	1|2��ʾˮƽ�봹ֱ����
	rt������ʾ������Χ
	x��wһ���ʾˮƽ��Χ
	y��hһ����ʾ��ֱ��Χ
 */
int sdl_view::scroll(Uint32 pflag,SDL_Rect* rt=NULL)
{
	_scroll_type = pflag;
	if(_scroll_type&1)
	{
		//ˮƽ������
		if(!_vertical)
		{
			_vertical = add<sdl_v_scroll>("",0,_rect.h-30,_rect.w,30,1);
			_vertical->fill_rect(NULL,0xff00ff);
			_vertical->update();
		}
		//����ı������Χ
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
		//��ֱ������
		if(!_horizontal)
		{
			_horizontal= add<sdl_h_scroll>("",_rect.w - 30,0,30,_rect.h,1);
			_horizontal->fill_rect(NULL,0xff00ff);
			_horizontal->update();
		}
		//����ı������Χ
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
//							�б���
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
		/* ��ͼ������Χ */
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
	/* ���ù�����ʽ */
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
					/* ���ʧȥ���㣬�����Ƿ��Ӽ����ڻ�ȡ���� */
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
			 ���ش����������ú���
			 ����ͬ�����»���������� 
		 */
		int pos(int,int);
		int pos_x(int);
		int pos_y(int);
	public:
		/* 
			������Ƴ��б���Ŀ
			����Ŀ����ΪNULLʱ��ʾ�Ƴ���N����Ŀ
			����Ŀ�������ʱ��ʾ�ڵ�N��������Ŀ
		 */
		template<class T>T* item(int,T*);
		/* 
			���ص�N����Ŀ����ָ�룬ʧ��ʱ����NULL
		 */
		template<class T>T* item(int);
		/* 
			�����б�
			����ʱҪ���������½�һ�����б�����Ĵ���
			����Ϊ����ʱ��ʼ����
			�ɹ�ʱ����0��ʧ��ʱ����-1
		*/
		int pull(int);
		/* 
			�����б� 
			����ʱ����Ŀ�������ڹر�
			�ɹ�ʱ����0��ʧ��ʱ����-1
		 */
		int push();
		/* 
			ѡ���N��,�ɹ�ʱ�����ϴ�ѡ���ID��ʧ��ʱ����-1 
		 */
		int select(int);
	protected:
		/* ��Ŀ���� */
		int _item_count;
		/* ��ǰѡ����ĿID */
		int _current_item_id;
		/* ��Ŀ������峤�� */
		int _item_plane_length;
		/* ��Ŀ�������ָ�� */
		sdl_listbox_plane* _item_plane;
		/* ��Ŀ������ťָ�� */
		sdl_button* _list_button;
		/* ��Ŀ�б�״̬ */
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
	/* ������Ŀ������� */
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
					 �������б���ı�ʱ 
					 �����Ƿ��б�������ȡ�� 
					*/
					if(!(int)(e->user.data1))
					{
						/* ��ȡ��ȡ����Ķ��� */
						tobj = (sdl_board*)(e->user.data2);
						/* 
							 �����������ǻ������򻬶������Ӽ����� 
							 �������ݣ�����رջ������ 
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
	/* ���ָ�����Ȳ�Ϊ0�����»������ڳ��� */
	if(plength)
	{
		_item_plane_length = plength;
		if(_item_plane)_item_plane->height(_item_plane_length);
	}
	/* �������������岻���ڸ���,��������뵽�������� */
	if(_item_plane && !_item_plane->parent())
	{
		parent()->add<sdl_listbox_plane>(_item_plane);
	}
	/* �������������,����ʾ��� */
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
