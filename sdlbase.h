//----------------------------------------------------------------------------------------------------------------
//
//
//
//
//						�ĵ�����						sdlbase.h
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
#ifndef __sdlbase_head__
#define __sdlbase_head__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#ifndef __ANDROID_OS__
#include <SDL2/SDL2_rotozoom.h>
#endif //__ANDROID_OS__
#include <SDL2/SDL_ttf.h>
#include <cmath>
#include <iostream>
#include "sdlthread.h"
using namespace std;
/////////////////////////////////////////////////
class sdlsurface;
class sdltext;
class sdltexture;
class sdlrenderer;
class sdlwidnow;
///////////////////////////////////////////////////////////////////////
//
//						SDL���������������ķ�װ
//
///////////////////////////////////////////////////////////////////////
typedef class sdlsurface
{
	public:
		sdlsurface();
		sdlsurface(SDL_Surface*);
		sdlsurface(Uint32,int,int,int,Uint32,Uint32,Uint32,Uint32);
		virtual ~sdlsurface();
		int init();
		int init(SDL_Surface*);
		int init(Uint32,int,int,int,Uint32,Uint32,Uint32,Uint32);
	protected:
		SDL_Surface *_surface;
		SDL_Rect _surface_rect;
		/* �߳��� */
		sdl_semaphore _thread_lock;
	public:
		///-------------------------------------
		sdlrenderer* create_software_renderer();
		SDL_Surface* surface();
		int surface(SDL_Surface*);
		int create_rgb_surface(Uint32,int,int,int,Uint32,Uint32,Uint32,Uint32);
		int fill_rect(const SDL_Rect* rect,Uint32 color);
		int load_bmp(const char* file);
		int blit_scaled(const SDL_Rect*,sdlsurface*,SDL_Rect*);
		int blit_surface(const SDL_Rect*,sdlsurface*,SDL_Rect*);
		int free_surface();
		int surface_blend_mode(SDL_BlendMode);
		int surface_color_mod(Uint8,Uint8,Uint8);
		int set_surface_palette(SDL_Palette*);
		int save_BMP(const char*);
		sdlsurface* convert_surface(SDL_PixelFormat* fmt,Uint32 flags);
		SDL_Rect* clip_rect();
		int pixel(int,int);
		int pixel(int,int,Uint32);
		/* ��һ������ֱ�� */
		int line(int,int,int,int,Uint32);
		/* �������һ������ */
		int rectangle(int,int,int,int,Uint32,int);
		/* �������һ����Բ */
		int circle(int,int,int,Uint32,int);
		/* �������һ����Բ */
		int ellipse(int,int,int,int,Uint32,int);
		/* ��ת���� */
		int rotate(float);
		//
		int must_lock();
		int lock_surface();
		int unlock_surface();
		int surface_alpha_mod(Uint8);
		Uint8 surface_alpha_mod();
		int color_key(int,Uint32);
		Uint32 color_key();
		Uint32 map_rgb(Uint8,Uint8,Uint8);
		Uint32 map_rgba(Uint8,Uint8,Uint8,Uint8);
		//---------------------------------------
		//SDL_image.h
		int img_load(const char*);
#ifndef __ANDROID_OS__
		//-----------------------------------------
		//SDL2_rotozoom.h
		int rotozoom_surface(double,double,int);	
		int rotozoom_surface_xy(double,double,double,int);
		SDL_Point rotozoom_surface_size(int,int,double,double,int*,int*);
		SDL_Point rotozoom_surface_size_xy(int,int,double,double,double,int*,int*);
		int zoom_surface(double,double,int);
		SDL_Point zoom_surface_size(int,int,double,double,int*,int*);
		int shrink_surface(int,int);
		int rotate_surface_90degrees(int);
#endif// __ANDROID_OS__
}*sdlsurface_ptr;
//----------------------------------------------------
//
//
//               �ı���Ⱦ��
//
//
//--------------------------------------------
typedef class sdltext : public sdlsurface
{
	public:
		sdltext();
		sdltext(const char*,int);
		~sdltext();
		int init();
		int text(const char*);
		/* 
		 ���õ�ǰ�ı�,
		 ����(�ı������壬�����С)
		*/
		int text(const char*,const char*,int);
		char* text();
		int font(const char*,int);
		int close_font();
		//--------------------------------------
		int font_style();	
		int font_style(int);	
		int font_outline();
		int font_outline(int);
		int font_hinting();
		int font_hinting(int);
		int font_kerning();
		int font_kerning(int);
		int font_height();
		int font_ascent();
		int font_descent();
		int font_line_skip();
		long font_faces();
		int font_face_is_fixed_width();
		char* font_face_family_name();
		char* font_face_style_name();
		int glyph_is_provided(Uint16);
		int glyph_metrics(Uint16,int*,int*,int*,int*,int*);
		int size_text(char*,int*,int*);
		int size_utf8(const char*,int*,int*);
		int size_unicode(const Uint16*,int*,int*);
		//
		int render_text_solid(const char*,Uint32);
		int render_utf8_solid(const char*,Uint32);
		int render_unicode_solid(const Uint16*,Uint32);
		int render_glyph_solid(const Uint16,Uint32);
		//
		int render_text_shaded(const char*,Uint32,Uint32);
		int render_utf8_shaded(const char*,Uint32,Uint32);
		int render_unicode_shaded(const Uint16*,Uint32,Uint32);
		int render_glyph_shaded(const Uint16,Uint32,Uint32);
		//
		int render_text_blended(const char*,Uint32);
		int render_utf8_blended(const char*,Uint32);
		int render_unicode_blended(const Uint16*,Uint32);
		int render_glyph_blended(const Uint16,Uint32);
		//--------------------------------------
	public:
		static string font_path;
	protected:
		TTF_Font* _font;
		char* _text;
	protected:
		static int is_init;
}*sdltext_ptr;
int sdltext::is_init = 0;
string sdltext::font_path="";
//--------------------------------------------
//
///
//              ����������
//
//
//
//---------------------------------------------

class sdltexture
{
	public:
		sdltexture();
		sdltexture(SDL_Texture*);
		~sdltexture();
		int texture(SDL_Texture*);
		SDL_Texture* texture();
	protected:
		SDL_Texture* _texture;
	public:
		Uint8 texture_alpha_mod();
		SDL_BlendMode texture_blend_mode();
		int destroy();
};

//--------------------------------------------
//
///
//              ��Ⱦ������
//
//
//
//---------------------------------------------
class sdlrenderer
{
	public:
		sdlrenderer();
		sdlrenderer(SDL_Renderer*);
		~sdlrenderer();
	protected:
		SDL_Renderer *_renderer;
	public:	
		sdltexture* create_texture_from_surface(sdlsurface*);
		sdltexture* create_texture(Uint32,int,int,int);
		int copy(sdltexture*,const SDL_Rect*,const SDL_Rect*);
		int clear();
		int present();
		int fill_rect(const SDL_Rect*);
		int set_render_draw_color(Uint8,Uint8,Uint8,Uint8);
		sdltexture* render_target();
		int render_target(sdltexture*);
		int draw_line(int,int,int,int);
		int draw_point(int,int);
		int destroy();
};
//-----------------------------------------
//
//
//             ����������
//
//------------------------------------------
class sdlwindow
{
	public:
		sdlwindow();//���ڹ��캯��
		sdlwindow(SDL_Window* win);
		sdlwindow(const char*,int,int,int,int,Uint32);//�������ں���
		virtual ~sdlwindow();//������������
	protected:
		SDL_Window *_window;//�������������
	public:
		int window(const char*,int,int,int,int,Uint32);//�������ں���
		int window(sdlwindow*);//���ݴ���ָ��
		SDL_Window* window();//���ش���ָ��
		int destroy();//���ٴ���
		////
		sdlrenderer* create_renderer(int,Uint32);//����������Ⱦ���� 
		///
		sdlsurface* get_window_surface();//�õ����ڱ���
		//
		int update_window_surface();//���´��ڱ���
		//
		int pos(int,int);//���´���λ��
		//
		int size(int*,int*);//ȡ���ڴ�С
		int size(int,int);//���´��ڴ�С
		//
		int show();//��ʾ����
		//
		int hide();//���ش���
};
//-------------------------------------------
//
//
//
//
//
//                    ��ʵ��
//
//
//
//
//-------------------------------------------
sdlsurface::sdlsurface()
{
	_surface = NULL;
	_thread_lock.init(1);
	init();
}
sdlsurface::sdlsurface(SDL_Surface* sur)
{
	_surface = NULL;
	init(sur);
}
sdlsurface::sdlsurface(Uint32 flags,int width,int height,int depth,Uint32 Rmask,Uint32 Gmask,Uint32 Bmask,Uint32 Amask)
{
	_surface = NULL;
	init(flags,width,height,depth,Rmask,Gmask,Bmask,Amask);
}
SDL_Surface* sdlsurface::surface()
{
	return _surface;
}
sdlsurface::~sdlsurface()
{
	if(_surface)
	{
		//_thread_lock.wait();
		free_surface();
		//SDL_FreeSurface(_surface);
		//_thread_lock.post();
	}
	_thread_lock.destroy();
}
int sdlsurface::surface(SDL_Surface* surface)
{
	int i=-1;
	if(surface)
	{
		_thread_lock.wait();
		if(_surface)free_surface();
		_surface = surface;
		i = 0;
		_thread_lock.post();
	}
	return i;
}
int sdlsurface::init()
{
	if(_surface)free_surface();
	return 0;
}
int sdlsurface::init(SDL_Surface* sur)
{
	int i=-1;
	if(sur)
	{
		_thread_lock.wait();
		if(_surface)free_surface();
		_surface = sur;		
		i = 0;
		_thread_lock.post();
	}
	return i;
}
int sdlsurface::init(Uint32 flags,int width,int height,int depth,Uint32 Rmask,Uint32 Gmask,Uint32 Bmask,Uint32 Amask)
{
	//_thread_lock.wait();
	if(_surface)free_surface();
	create_rgb_surface(flags,width,height,depth,Rmask,Gmask,Bmask,Amask);
	//cout<<"surface unlock"<<endl;
	//_thread_lock.post();
	return 0;
}
int sdlsurface::create_rgb_surface(Uint32 flags,int width,int height,int depth,Uint32 Rmask,Uint32 Gmask,Uint32 Bmask,Uint32 Amask)
{
	_thread_lock.wait();
	if(_surface)free_surface();
	_surface = SDL_CreateRGBSurface(flags,width,height,depth,Rmask,Gmask,Bmask,Amask);
	_thread_lock.post();
	if(_surface)return 0;
	return -1;
}
int sdlsurface::fill_rect(const SDL_Rect* rect,Uint32 color)
{
	int i;
	//_thread_lock.wait();
	i = 	SDL_FillRect(_surface,rect,color);
	//_thread_lock.post();
	return i;
}
int sdlsurface::load_bmp(const char* file)
{
	_thread_lock.wait();
	if(_surface)free_surface();
	_surface = SDL_LoadBMP(file);
	//_surface = SDL_CreateRGBSurfaceFrom(t->pixels,t->w,t->h,t->format->BitsPerPixel,t->pitch,t->format->Rmask,t->format->Gmask,t->format->Bmask,t->format->Amask);
	_thread_lock.post();
	if(_surface)return 0;
	return -1;
}
///////////////////////////////////////////
//λ�鴫�䷽������һ������Ϊλ��Դ�Ĵ��䷶Χ���ڶ�������ΪĿ��λ�飬����������ΪĿ�괫�䷶Χ���ɹ�����0
int sdlsurface::blit_surface(const SDL_Rect* srcrect,sdlsurface* dst,SDL_Rect* dstrect)
{
	int i=-1;
	if(dst)
	{
		//_thread_lock.wait();
		i = SDL_BlitSurface(_surface,srcrect,dst->surface(),dstrect);
		//_thread_lock.post();
	}
	return i;
}
//-------------------------------------------------
//�ͷ����õ�surface
int sdlsurface::free_surface()
{
	/* �������û�з���ֵ */
	//_thread_lock.wait();
	SDL_FreeSurface(_surface);
	_surface = NULL;
	//_thread_lock.post();
	return 0;
}
//���ñ�����ģʽ
int sdlsurface::surface_blend_mode(SDL_BlendMode mode)
{
	int i;
	_thread_lock.wait();
	i = SDL_SetSurfaceBlendMode(_surface,mode);
	_thread_lock.post();
	return i; 
}
//-------------------------------------------------
//���ñ���ɫ��ģʽ
int sdlsurface::surface_color_mod(Uint8 r,Uint8 g,Uint8 b)
{
	int i;
	_thread_lock.wait();
	i = SDL_SetSurfaceColorMod(_surface,r,g,b);
	_thread_lock.post();
	return i;
}
//--------------------------------------------------
//���ñ���ALPHAģʽ
int sdlsurface::surface_alpha_mod(Uint8 a)
{
	int i;
	_thread_lock.wait();
	i =	SDL_SetSurfaceAlphaMod(_surface,a);
	_thread_lock.post();
	return i;
}
//--------------------------------------------------
//�õ�����ALPHAģʽ
Uint8 sdlsurface::surface_alpha_mod()
{
	Uint8 a;
	_thread_lock.wait();
	SDL_GetSurfaceAlphaMod(_surface,&a);
	_thread_lock.post();
	return a;
}
//--------------------------------------
//���ñ����ɫ��
int sdlsurface::set_surface_palette(SDL_Palette* palette)
{
	int i;
	_thread_lock.wait();
	i = SDL_SetSurfacePalette(_surface,palette);
	_thread_lock.post();
	return i;
}
//-------------------------------------------
//��������BMPλͼ��ʽд������ļ���
int sdlsurface::save_BMP(const char* file)
{
	int i;
	_thread_lock.wait();
	i = SDL_SaveBMP(_surface,file);
	_thread_lock.post();
	return i;
}
//----------------------------------------------
//���������Ŵ��䵽Ŀ��λ�顣
int sdlsurface::blit_scaled(const SDL_Rect* srcrect,sdlsurface* dst,SDL_Rect* dstrect)
{
	int i=-1;
	if(dst)
	{
		//_thread_lock.wait();
		i = SDL_BlitScaled(_surface,srcrect,dst->surface(),dstrect);
		//_thread_lock.post();
	}
	return i;
}
//------------------------------------------------
//������ת����ָ����ʽ���������µı���ָ��
sdlsurface* sdlsurface::convert_surface(SDL_PixelFormat* fmt,Uint32 flags = 0)
{
	sdlsurface* tsur;
	_thread_lock.wait();
	tsur = new sdlsurface(SDL_ConvertSurface(_surface,fmt,flags));
	_thread_lock.post();
	return  tsur;
}
//----------------------------------------------
//�õ��������
SDL_Rect* sdlsurface::clip_rect()
{
	_thread_lock.wait();
	memset((char*)&_surface_rect,0x00,sizeof(SDL_Rect));
	SDL_GetClipRect(_surface,&_surface_rect);
	_thread_lock.post();
	return &_surface_rect;
}
//------------------------------------------------------
//
//
//
//
//
//
//------------------------------------------------------
sdltext::sdltext()
:
sdlsurface()
{
	_font = NULL;
	init();
}
/* 
	ʹ��ָ����������ֺ�������һ���ı�������� 
 */
sdltext::sdltext(const char* pfont,int psize)
:
sdlsurface()
{
	_font = NULL;
	init();
	font(pfont,psize);
}
sdltext::~sdltext()
{
	delete[] _text;
	font(NULL,0);
	sdlsurface::free_surface();
}
int sdltext::init()
{
	if(!sdltext::is_init)
	{
		sdltext::is_init = 1;
		TTF_Init();
	}
	if(_font)TTF_CloseFont(_font);
	if(sdlsurface::init())return -1;
	return 0;
}
int sdltext::text(const char* ptext)
{
	if(_text)delete[] _text;
	int len = strlen(ptext)+1;
	_text = new char[len];
	memset(_text,0x00,len);
	strcpy(_text,ptext);
	//---------------------------------
	return 0;
}
int sdltext::text(const char* ptext,const char* pfont,int psize)
{
	if(text(ptext))return -1;
	if(font(pfont,psize))return -1;
	return 0;
}
char* sdltext::text()
{
	if(_text) return _text;
	return NULL;
}
int sdltext::font(const char* font_path,int font_size=16)
{
	if(_font)
	{
		TTF_CloseFont(_font);
		_font = NULL;
	}
	if(!font_path)return -1;
	_font = TTF_OpenFont(font_path,font_size);
	if(!_font)return -1;
	return 0;
}
int sdltext::font_style()	
{
	if(!_font)return -1;
	return TTF_GetFontStyle(_font);
}
int sdltext::font_style(int pstyle)	
{
	if(!_font)return -1;
	TTF_SetFontStyle(_font,pstyle);
	return 0;
}
int sdltext::font_outline()
{
	if(!_font)return -1;
	return TTF_GetFontOutline(_font);
}
int sdltext::font_outline(int poutline)
{
	if(!_font)return -1;
	TTF_SetFontOutline(_font,poutline);
	return 0;
}
int sdltext::font_hinting()
{
	if(!_font)return -1;
	return TTF_GetFontHinting(_font);
}
int sdltext::font_hinting(int phinting)
{
	if(!_font)return -1;
	TTF_SetFontHinting(_font,phinting);
	return 0;
}
int sdltext::font_kerning()
{
	if(!_font)return -1;
	return TTF_GetFontKerning(_font);
}
int sdltext::font_kerning(int pkerning)
{
	if(!_font)return -1;
	TTF_SetFontKerning(_font,pkerning);
	return 0; 
}
int sdltext::font_height()
{
	if(!_font)return -1;
	return TTF_FontHeight(_font);
}
int sdltext::font_ascent()
{
	if(!_font)return -1;
	return TTF_FontAscent(_font);
}
int sdltext::font_descent()
{
	if(!_font)return -1;
	return TTF_FontDescent(_font);
}
int sdltext::font_line_skip()
{
	if(!_font)return -1;
	return TTF_FontLineSkip(_font);
}
long sdltext::font_faces()
{
	if(!_font)return -1;
	return TTF_FontFaces(_font);
}
int sdltext::font_face_is_fixed_width()
{
	if(!_font)return -1;
	return TTF_FontFaceIsFixedWidth(_font);
}
char* sdltext::font_face_family_name()
{
	if(!_font)return NULL;
	return TTF_FontFaceFamilyName(_font);
}
char* sdltext::font_face_style_name()
{
	if(!_font)return NULL;
	return TTF_FontFaceStyleName(_font);
}
int sdltext::glyph_is_provided(Uint16 ch)
{
	if(!_font)return -1;
	return TTF_GlyphIsProvided(_font,ch);
}
int sdltext::glyph_metrics(Uint16 ch,int* minx,int* maxx,int* miny,int* maxy,int* advance)
{
	if(!_font)return -1;
	return TTF_GlyphMetrics(_font,ch,minx,maxx,miny,maxy,advance);
}
int sdltext::size_text(char* ptext,int* pw,int* ph)
{
	if(!_font)return -1;
	return TTF_SizeText(_font,ptext,pw,ph);
}
int sdltext::size_utf8(const char* ptext,int* pw,int* ph)
{
	if(!_font)return -1;
	return TTF_SizeUTF8(_font,ptext,pw,ph);
}
int sdltext::size_unicode(const Uint16* ptext,int* pw,int* ph)
{
	if(!_font)return -1;
	return TTF_SizeUNICODE(_font,ptext,pw,ph);
}
int sdltext::render_text_solid(const char* ptext,Uint32 pcolor)
{
	SDL_Color c = {(Uint8)((pcolor & 0xff0000)>>16),(Uint8)((pcolor & 0x00ff00)>>8),(Uint8)(pcolor & 0x0000ff)};
	//SDL_Color tc = {0,255,255};
	if(!_font)return -1;
	free_surface();
	_surface = TTF_RenderText_Solid(_font,ptext,c);
	if(!_surface)return -1;
	return 0;
}
int sdltext::render_utf8_solid(const char* ptext,Uint32 pcolor)
{
	//cout<<"sdltext::"<<ptext<<endl;
	SDL_Color c = {(Uint8)((pcolor & 0xff0000)>>16),(Uint8)((pcolor & 0x00ff00)>>8),(Uint8)(pcolor & 0x0000ff)};
	if(!_font)return -1;
	free_surface();
	_surface = TTF_RenderUTF8_Solid(_font,ptext,c);
	text(ptext);
	if(!_surface)return -1;
	return 0;
}
int sdltext::render_unicode_solid(const Uint16* ptext,Uint32 pcolor)
{
	SDL_Color c = {(Uint8)((pcolor & 0xff0000)>>16),(Uint8)((pcolor & 0x00ff00)>>8),(Uint8)(pcolor & 0x0000ff)};
	if(!_font)return -1;
	free_surface();
	_surface = TTF_RenderUNICODE_Solid(_font,ptext,c);
	if(!_surface)return -1;
	return 0;
}
int sdltext::render_glyph_solid(const Uint16 ptext,Uint32 pcolor)
{
	SDL_Color c = {(Uint8)((pcolor & 0xff0000)>>16),(Uint8)((pcolor & 0x00ff00))>>8,(Uint8)(pcolor & 0x0000ff)};
	if(!_font)return -1;
	free_surface();
	_surface = TTF_RenderGlyph_Solid(_font,ptext,c);
	if(!_surface)return -1;
	return 0;
}
int sdltext::render_text_shaded(const char* ptext,Uint32 pcolor,Uint32 pcolor1)
{
	SDL_Color c = {(Uint8)((pcolor & 0xff0000)>>16),(Uint8)((pcolor & 0x00ff00)>>8),(Uint8)(pcolor & 0x0000ff)};
	SDL_Color c1 = {(Uint8)((pcolor1 & 0xff0000)>>16),(Uint8)((pcolor1 & 0x00ff00)>>8),(Uint8)(pcolor1 & 0x0000ff)};
	if(!_font)return -1;
	free_surface();
	_surface = TTF_RenderText_Shaded(_font,ptext,c,c1);
	if(!_surface)return -1;
	return 0;
}
int sdltext::render_utf8_shaded(const char* ptext,Uint32 pcolor,Uint32 pcolor1)
{
	SDL_Color c = {(Uint8)((pcolor & 0xff0000)>>16),(Uint8)((pcolor & 0x00ff00)>>8),(Uint8)(pcolor & 0x0000ff)};
	SDL_Color c1 = {(Uint8)((pcolor1 & 0xff0000)>>16),(Uint8)((pcolor1 & 0x00ff00)>>8),(Uint8)(pcolor1 & 0x0000ff)};
	if(!_font)return -1;
	free_surface();
	_surface = TTF_RenderUTF8_Shaded(_font,ptext,c,c1);
	if(!_surface)return -1;
	return 0;
}
int sdltext::render_unicode_shaded(const Uint16* ptext,Uint32 pcolor,Uint32 pcolor1)
{
	SDL_Color c = {(Uint8)((pcolor & 0xff0000)>>16),(Uint8)((pcolor & 0x00ff00)>>8),(Uint8)(pcolor & 0x0000ff)};
	SDL_Color c1 = {(Uint8)((pcolor1 & 0xff0000)>>16),(Uint8)((pcolor1 & 0x00ff00)>>8),(Uint8)(pcolor1 & 0x0000ff)};
	if(!_font)return -1;
	free_surface();
	_surface = TTF_RenderUNICODE_Shaded(_font,ptext,c,c1);
	if(!_surface)return -1;
	return 0;
}
int sdltext::render_glyph_shaded(const Uint16 ptext,Uint32 pcolor,Uint32 pcolor1)
{
	SDL_Color c = {(Uint8)((pcolor & 0xff0000)>>16),(Uint8)((pcolor & 0x00ff00)>>8),(Uint8)(pcolor & 0x0000ff)};
	SDL_Color c1 = {(Uint8)((pcolor1 & 0xff0000)>>16),(Uint8)((pcolor1 & 0x00ff00)>>8),(Uint8)(pcolor1 & 0x0000ff)};
	if(!_font)return -1;
	free_surface();
	_surface = TTF_RenderGlyph_Shaded(_font,ptext,c,c1);
	if(!_surface)return -1;
	return 0;
}
int sdltext::render_text_blended(const char* ptext,Uint32 pcolor)
{
	SDL_Color c = {(Uint8)((pcolor & 0xff0000)>>16),(Uint8)((pcolor & 0x00ff00)>>8),(Uint8)(pcolor & 0x0000ff)};
	if(!_font)return -1;
	free_surface();
	_surface = TTF_RenderText_Blended(_font,ptext,c);
	if(!_surface)return -1;
	return 0;
}
int sdltext::render_utf8_blended(const char* ptext,Uint32 pcolor)
{
	SDL_Color c = {(Uint8)((pcolor & 0xff0000)>>16),(Uint8)((pcolor & 0x00ff00)>>8),(Uint8)(pcolor & 0x0000ff)};
	if(!_font)return -1;
	free_surface();
	_surface = TTF_RenderUTF8_Blended(_font,ptext,c);
	if(!_surface)return -1;
	return 0;
}
int sdltext::render_unicode_blended(const Uint16* ptext,Uint32 pcolor)
{
	SDL_Color c = {(Uint8)((pcolor & 0xff0000)>>16),(Uint8)((pcolor & 0x00ff00)>>8),(Uint8)(pcolor & 0x0000ff)};
	if(!_font)return -1;
	free_surface();
	_surface = TTF_RenderUNICODE_Blended(_font,ptext,c);
	if(!_surface)return -1;
	return 0;
}
int sdltext::render_glyph_blended(const Uint16 ptext,Uint32 pcolor)
{
	SDL_Color c = {(Uint8)((pcolor & 0xff0000)>>16),(Uint8)((pcolor & 0x00ff00)>>8),(Uint8)(pcolor & 0x0000ff)};
	if(!_font)return -1;
	free_surface();
	_surface = TTF_RenderGlyph_Blended(_font,ptext,c);
	if(!_surface)return -1;
	return 0;
}
//------------------------------------------------------
//
//
//
//
//
//
//
//
//------------------------------------------------
//�ɱ��洴��һ����Ⱦ��
sdlrenderer* sdlsurface::create_software_renderer()
{
	_thread_lock.wait();
	sdlrenderer* tren;
	tren= new sdlrenderer(SDL_CreateSoftwareRenderer(_surface));
	_thread_lock.post();
	return tren;
}
//-----------------------------------------
//�õ�ָ�����������ֵ
int sdlsurface::pixel(int x,int y)
{
	if(_surface==NULL)return -1;
	_thread_lock.wait();
	int bpp = _surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)_surface->pixels + y * _surface->pitch + x * bpp;
	_thread_lock.post();
	switch(bpp)
	{
		case 1:return *p;
		case 2:return *(Uint16*)p;
		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)return p[0]<<16|p[1]<<8|p[2];
			return p[0]|p[1]<<8|p[2]<<16;
		break;
		case 4:
			return *(Uint32*)p;
		break;
		default:return 0;
	}
}
//-----------------------------------------
//����ָ�����������ֵ
int sdlsurface::pixel(int x,int y,Uint32 v)
{
	if(_surface == NULL)return -1;
	_thread_lock.wait();
	int bpp = _surface->format->BytesPerPixel;
	Uint8 *p = (Uint8*)_surface->pixels+y*_surface->pitch+x*bpp;
	switch(bpp)
	{
			case 1:
				*p = v;
			break;
			case 2:
				*(Uint16*)p=v;
			break;
			case 3:
				if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
				{
					p[0] = (v>>16)&0xff;
					p[1] = (v>>8)&0xff;
					p[2] = v&0xff;
				}
				else
				{
					p[0]=v&0xff;
					p[1]=(v>>8)&0xff;
					p[2]=(v>>16)&0xff;
				}
			break;
			case 4:
				*(Uint32*)p=v;
			break;
	}
	_thread_lock.post();
	return 0;
}
//----------------------------------------------------------
//�������һ������
int sdlsurface::rectangle(int x0,int y0,int x1,int y1,Uint32 color,int pm=0)
{
	SDL_Rect rt;
	if(pm)
	{
		rt.x = x0;
		rt.y = y0;
		rt.w = x1;
		rt.h = y1;
		return fill_rect(&rt,color);
	}
	else
	{
		/* ������ˮƽ�� */
		line(x0,y0,x1,y0,color);
		line(x0,y1,x1,y1,color);
		/* ��������ֱ�� */
		line(x0,y0,x0,y1,color);
		line(x1,y0,x1,y1,color);
		return 0;
	}
}
/* 
	 ���ߺ��� 
	��ȷ���ǻ�ˮƽ�ߣ���ֱ�ߣ���������ֱ�� 
	����������ѡ���߷�ʽ��ʼ����
	������
 */
int sdlsurface::line(int x0,int y0,int x1,int y1,Uint32 color)
{
	if(_surface == NULL)return -1;
	//ȡ���������
	int bpp = _surface->format->BytesPerPixel;
	//����С����
	int tx0 = x0;
	int ty0 = y0;
	int tx1 = x1;
	int ty1 = y1;
	if(tx0>tx1)
	{
		tx0 += tx1;
		tx1 =  tx0-tx1;
		tx0 -= tx1;
		//
		ty0 += ty1;
		ty1 =  ty0-ty1;
		ty0 -= ty1;
	}
	/* ȡ�����������׵�ַ */
	Uint8 *p = (Uint8*)_surface->pixels+ty0*_surface->pitch+tx0*bpp;
	//
	float x_off=tx1-tx0;
	float y_off=ty1-ty0;
	int x,y;
	//float xy_s;
	/* ����ߵ��յ㳬���˱��������ȡ��Ч���� */
	x_off -= (tx1>=_surface->pitch)?x_off-_surface->pitch : 0;
	x_off = (tx1<=0)?0:x_off;
	y_off -= (ty1>=_surface->h)?ty1-_surface->h:0;
	y_off = (ty1<=0)?0:y_off;
	//
	//ѡ���ʽ
	//if(must_lock())lock_surface();
	switch(bpp)
	{
		/* ��ɫ */
		case 1:
			/* �����ˮƽ�� */
			if(!y_off)
			{
				memset((Uint32*)p,color,x_off*bpp);
			}
		break;
		/* 16ɫ */
		case 2:
		break;
		/*  */
		case 3:
		break;
		/* 32λ */
		case 4:
			/* �����ˮƽ�� */
			if(!y_off)
			{
				for(x=0;x<x_off;x++)
				{
					*(Uint32*)(p+x*bpp) = color;
				}
			}
			else
			/* �������ֱ�� */
			if(!x_off)
			{
				for(y=0;y<y_off;y++)
				{
					*(Uint32*)(p+y*_surface->pitch) = color;
				}
			}
			/* ������б�� */
			else
			{
				for(x = 0;x<x_off;x++)
				{
					//if(!x_off)cout<<y_off<<endl;
					y = x/(x_off/y_off);	
					*(Uint32*)(p+x*bpp+y*_surface->pitch) = color;
				}
			}
		break;
	}
	//if(must_lock())unlock_surface();
	return 0;
}
//------------------------------------------------------------
//��һ��Բ,pm=0��ʾ�����,pm=1��ʾ���
int sdlsurface::circle(int px,int py,int pr,Uint32 color,int pm =0)
{
	if(_surface == NULL)return -1;
	//����뾶С��3���ʾ�޷����ƣ�ֱ���˳�
	if(pr<3)return -1;
	//ȡ���������
	int bpp = _surface->format->BytesPerPixel;
	int i = 0;
	//�µ�����
	float tx,ty,tx1,ty1;
	float pj = 0;
	switch(bpp)
	{
		/* ��ɫ */
		case 1:
		break;
		/* 16ɫ */
		case 2:
		break;
		/*  */
		case 3:
		break;
		/* 32λ */
		case 4:
			for(i=0;i<=pr;i++)
			{
				pj = 3.1415926/180*i;
				ty = i;
				tx = pr*sin(acos(ty/pr));
				//tx = sin(pj)*pr;
				//ty = cos(pj)*pr;
				if(pm)
				{
					//����ڶ������ټ����һ����
					line(px-tx,py-ty,px+tx,py-ty,color);
					//������������ټ����������
					line(px-tx,py+ty,px+tx,py+ty,color);
				}
				else
				{
					//�����һ������������
					tx1 = px+tx;
					ty1 = py-ty;
					pixel(tx1,ty1,color);
					//����ڶ������������
					tx1 = px-tx;
					ty1 = py-ty;
					pixel(tx1,ty1,color);
					//������������������
					tx1 = px-tx;
					ty1 = py+ty;
					pixel(tx1,ty1,color);
					//������������������
					tx1 = px+tx;
					ty1 = py+ty;
					pixel(tx1,ty1,color);
				}
			}
		break;
	}
	return 0;
}
//---------------------------------------------------------------
//��һ����Բ��pm=0��ʾ����䣬pm=1��ʾ���
int sdlsurface::ellipse(int px,int py,int pr0,int pr1,Uint32 color,int pm=0)
{
	int x,y;
	float d1,d2;
	x = 0;
	y = pr1;
	d1 = pr1*pr1 + pr0*pr0*(-pr1+0.5);
	if(pm)
	{
		line(x+px,y+py,-x+px,y+py,color);
		line(x+px,-y+py,-x+px,-y+py,color);
	}
	else
	{
		pixel(x+px,y+py,color);
		pixel(-x+px,-y+py,color);
		pixel(-x+px,y+py,color);
		pixel(x+px,-y+py,color);
	}
	while(pr1*pr1*(x+1)<pr0*pr0*(y-0.5))
	{
		if(d1<=0)
		{
			d1+=pr1*pr1*(2*x+3);
			x++;
		}
		else
		{
			d1+=pr1*pr1*(2*x+3)+pr0*pr0*(-2*y+2);
			x++;
			y--;
		}
		//draw
		if(pm)
		{
			line(x+px,y+py,-x+px,y+py,color);
			line(x+px,-y+py,-x+px,-y+py,color);
		}
		else
		{
			pixel(x+px,y+py,color);
			pixel(-x+px,-y+py,color);
			pixel(-x+px,y+py,color);
			pixel(x+px,-y+py,color);
		}
	}
	d2 = pr1*pr1*(x+0.5)*(x+0.5)+pr0*pr0*(y-1)*(y-1)-pr0*pr0*pr1*pr1;
	while(y>0)
	{
		if(d2<=0)
		{
			d2+=pr1*pr1*(2*x+2)+pr0*pr0*(-2*y+3);
			x++;
			y--;
		}
		else
		{
			d2+=pr0*pr0*(-2*y+3);
			y--;
		}
		//draw
		if(pm)
		{
			line(x+px,y+py,-x+px,y+py,color);
			line(x+px,-y+py,-x+px,-y+py,color);
		}
		else
		{
			pixel(x+px,y+py,color);
			pixel(-x+px,-y+py,color);
			pixel(-x+px,y+py,color);
			pixel(x+px,-y+py,color);
		}
	}
	return 0;
}
//---------------------------------------------
//��ת����
int sdlsurface::rotate(float j)
{
	float x,y;
	float a,b,c;
	//float r;
	float op_x,op_y;
	float change_pixel_angle;
	float p0x,p0y;
	float p1x,p1y;
	//float p2x,p2y;
	float row,column;
	float row_off,column_off;
	/* ȡ��ͼ��߿�*/
	row = clip_rect()->h;
	column = clip_rect()->w;
	//
	sdlsurface tsur(0,column,row,32,0,0,0,0);
	//memcpy((char*)&tsur,(char*)this,sizeof(sdlsurface));
	tsur.fill_rect(NULL,0x000000);
	/* ����������� */
	op_x = column/2;
	op_y = row/2;
	/* ���p0���� */
	p0x = op_x;
	p0y = row;
	for(row_off=0;row_off<row;row_off++)
	{
		for(column_off = 0;column_off<column;column_off++)
		{
			/* ����p1���� */
			p1x = column_off;
			p1y = row_off;
			//cout<<p1x<<":"<<p1y<<endl;
			/* ��������α߳� */
			a = sqrt((p1x-op_x)*(p1x-op_x)+(p1y-op_y)*(p1y-op_y));
			c = sqrt((p1x-p0x)*(p1x-p0x)+(p1y-p0y)*(p1y-p0y));
			b = op_y;
			/* ���Ҫת���������ĽǶ� */
			change_pixel_angle = acos((a*a+b*b-c*c)/(2*a*b))*180/3.1415926;
			//cout<<"col:"<<column_off<<"-row:"<<row_off<<":"<<change_pixel_angle<<endl;
			/* �����ת��ĽǶ� */
			if(p1x>p0x)
			{
				change_pixel_angle -= j;
			}
			else
			{
				change_pixel_angle += j;
			}
			//change_pixel_angle = (change_pixel_angle>359)?0:change_pixel_angle;
			/* �����ת��c�ĳ��� */
			c = sqrt(a*a+b*b-cos(change_pixel_angle/180*3.1415926)*2*a*b);
			/* ���BC�н� */
			change_pixel_angle = acos((b*b+c*c-a*a)/(2*b*c));//*180/3.1415926;
			/* �����ת������������ */
			if(p1x>p0x)
			{
				x = p0x + sin(change_pixel_angle)*c;
			}
			else
			{
				x = p0x - sin(change_pixel_angle)*c;
			}
			y = p0y - cos(change_pixel_angle)*c;
			/* ��ʼ�������� */
			if(x<0 || x>column || y<0 || y>row)
			{
				//cout<<x<<":"<<y<<endl;
			}
			else
			{
				tsur.pixel(column_off,row_off,pixel(x,y));
				//cout<<"x:"<<x<<"--y:"<<y<<"--"<<sdlsurface::pixel(x,y)<<endl;
			}
		}
	}
	/* ���µ����� */
	tsur.blit_scaled(NULL,this,NULL);
	return 0;
}
//-------------------------------------t--------------
//����һ��ͼƬ��ҪSDL_img��֧��
int sdlsurface::img_load(const char* pfile)
{
	if(pfile == NULL)return -1;
	_thread_lock.wait();
	if(_surface)
	{
		SDL_FreeSurface(_surface);
		_surface = NULL;
	}
	_surface = IMG_Load(pfile);
	_thread_lock.post();
	if(_surface)return 0;
	return -1;
}
//--------------------------------------------
//��������״̬
int sdlsurface::must_lock()
{
	return SDL_MUSTLOCK(_surface);
}
//------------------------------------------------------
//��������
int sdlsurface::lock_surface()
{
	int i;
	_thread_lock.wait();
	i = SDL_LockSurface(_surface);
	_thread_lock.post();
	return 0;
}
//-----------------------------------------------
//��������
int sdlsurface::unlock_surface()
{
	_thread_lock.wait();
	SDL_UnlockSurface(_surface);
	_thread_lock.post();
	return 0;
}
//-------------------------------------------------
//���ñ���ALPHAģʽ�Ĺؼ�ɫ
int sdlsurface::color_key(int flag,Uint32 key)
{
	int i;
	_thread_lock.wait();
	i= SDL_SetColorKey(_surface,flag,key);
	_thread_lock.post();
	return i;
}
//-------------------------------------------------
//�õ�ALPHAģʽ�Ĺؼ�ɫ
Uint32 sdlsurface::color_key()
{
	Uint32 key;
	_thread_lock.wait();
	SDL_GetColorKey(_surface,&key);
	_thread_lock.post();
	return key;
}
//-------------------------------------------------
//
Uint32 sdlsurface::map_rgb(Uint8 r,Uint8 g,Uint8 b)
{
	Uint32 i;
	_thread_lock.wait();
	i= SDL_MapRGB(_surface->format,r,g,b);
	_thread_lock.post();
	return i;
}
//-------------------------------------------------
//
Uint32 sdlsurface::map_rgba(Uint8 r,Uint8 g,Uint8 b,Uint8 a)
{
	Uint32 i;
	_thread_lock.wait();
	i = SDL_MapRGBA(_surface->format,r,g,b,a);
	_thread_lock.post();
	return  i;
}
#ifndef __ANDROID_OS__
//-----------------------------------------------------
//��ת���ű���
int sdlsurface::rotozoom_surface(double angle,double zoom,int smooth)
{
	SDL_Surface* t = rotozoomSurface(_surface,angle,zoom,smooth);
	if(t)
	{
		//_surface->free
		free_surface();
		_surface = t;
		return 0;
	}
	return -1;
}
//-----------------------------------------------------
//��ת����(X,Y)����
int sdlsurface::rotozoom_surface_xy(double angle,double zoomx,double zoomy,int smooth)
{
	SDL_Surface* t = rotozoomSurfaceXY(_surface,angle,zoomx,zoomy,smooth);
	if(t)
	{
		free_surface();
		_surface = t;
		return 0;
	}
	return -1;
}
//-----------------------------------------------------
//��ת���ű����Ĵ�С
SDL_Point sdlsurface::rotozoom_surface_size(int width,int height,double angle,double zoom,int *dstwidth = NULL,int *dstheight = NULL)
{
	SDL_Point pt = {0,0};	
	rotozoomSurfaceSize(width,height,angle,zoom,&pt.x,&pt.y);	
	return pt;
}
//-----------------------------------------------------
//��ת����(X,Y)�����Ĵ�С
SDL_Point sdlsurface::rotozoom_surface_size_xy(int width,int height,double angle,double zoomx,double zoomy,int *dstwidth = NULL,int *dstheight = NULL)
{
	SDL_Point pt = {0,0};	
	rotozoomSurfaceSizeXY(width,height,angle,zoomx,zoomy,&pt.x,&pt.y);	
	return pt;
}
//-----------------------------------------------------
//���ű����Ĵ�С
int sdlsurface::zoom_surface(double zoomx,double zoomy,int smooth)
{
	SDL_Surface* t = zoomSurface(_surface,zoomx,zoomy,smooth);
	if(t)
	{
		free_surface();
		_surface = t;
		return 0;
	}
	return -1;
}
//-----------------------------------------------------
//����(X,Y)�����Ĵ�С
SDL_Point sdlsurface::zoom_surface_size(int width,int height,double zoomx,double zoomy,int* dstwidth = NULL,int* dstheight = NULL)
{
	SDL_Point pt = {0,0};
	zoomSurfaceSize(width,height,zoomx,zoomy,&pt.x,&pt.y);
	return pt;	
}
//-----------------------------------------------------
//��������
int sdlsurface::shrink_surface(int factorx,int factory)
{
	SDL_Surface* t = shrinkSurface(_surface,factorx,factory);
	if(t)
	{
		free_surface();
		_surface = t;
		return 0;
	}
	return  -1;
}
//-------------------------------------------------------
//90����ת����
int sdlsurface::rotate_surface_90degrees(int numClockwiseTurns)
{
	SDL_Surface* t = rotateSurface90Degrees(_surface,numClockwiseTurns);
	if(t)
	{
		free_surface();
		_surface = t;
		return 0;
	}
	return -1;
}
#endif //__ANDROID_OS__
///////////////////////////////////////////////////////////////////////////
//
//
// 								������
//
//
/////////////////////////////////////////////////////////////////////////
sdltexture::sdltexture()
{
	_texture = NULL;
}
sdltexture::sdltexture(SDL_Texture* tex)
{
	if(tex)
	{
		if(_texture)destroy();
		_texture = tex;
	}
}
sdltexture::~sdltexture()
{
	if(_texture)
	{
		destroy();
	}
}
int sdltexture::texture(SDL_Texture* tex)
{
	if(_texture)destroy();
	_texture = tex;
	return 0;
}
SDL_Texture* sdltexture::texture()
{
	return _texture;
}
Uint8 sdltexture::texture_alpha_mod()
{
	Uint8 talpha;
	SDL_GetTextureAlphaMod(_texture,&talpha);
	return talpha;
}
SDL_BlendMode sdltexture::texture_blend_mode()
{
	SDL_BlendMode tmode;
	SDL_GetTextureBlendMode(_texture,&tmode);
	return tmode;
}
//--------------------------------------------
//����һ������
int sdltexture::destroy()
{
	SDL_DestroyTexture(_texture);
	_texture = NULL;
	return 0;
}
/////////////////////////////////////////////////////////////////////////
//
// 					��Ⱦ��
//
//
//////////////////////////////////////////////////////////////////////////
sdlrenderer::sdlrenderer()
{
	_renderer = NULL;
}
sdlrenderer::sdlrenderer(SDL_Renderer* ren)
{
	if(ren)
	{
		if(_renderer)destroy();
		_renderer = ren;
	}
}
sdlrenderer::~sdlrenderer()
{
	if(_renderer)
	{
		destroy();
	}
}
sdltexture* sdlrenderer::create_texture_from_surface(sdlsurface* surface)
{
	if(surface)
	{
		return new sdltexture(SDL_CreateTextureFromSurface(_renderer,surface->surface()));
	}
	return NULL;
	SDL_Texture* tex;
	tex = SDL_CreateTextureFromSurface(_renderer,surface->surface());
	sdltexture* t_tex = new sdltexture(tex);
	return t_tex;
}
sdltexture* sdlrenderer::create_texture(Uint32 format,int access,int w,int h)
{
	return new sdltexture(SDL_CreateTexture(_renderer,format,access,w,h));
}
int sdlrenderer::clear()
{
	return SDL_RenderClear(_renderer);
}
int sdlrenderer::copy(sdltexture* tex,const SDL_Rect* srcrect = NULL,const SDL_Rect*dstrect = NULL)
{
	if(tex) return SDL_RenderCopy(_renderer,tex->texture(),srcrect,dstrect); return -1;
} 
int sdlrenderer::present()
{
	SDL_RenderPresent(_renderer); 
	return 0; 
}
int sdlrenderer::fill_rect(const SDL_Rect* rect)
{
	return SDL_RenderFillRect(_renderer,rect);
} 
int sdlrenderer::set_render_draw_color(Uint8 r,Uint8 g,Uint8 b,Uint8 a)
{
	return SDL_SetRenderDrawColor(_renderer,r,g,b,a);
}
//------------------------------------------
//�õ���Ⱦ����Ŀ������
sdltexture* sdlrenderer::render_target()
{
	return new sdltexture(SDL_GetRenderTarget(_renderer));
}
int sdlrenderer::render_target(sdltexture* t)
{
	if(!t)return -1;
	return SDL_SetRenderTarget(_renderer,t->texture());
}
//-------------------------------------------
//����Ⱦ���ϻ���
int sdlrenderer::draw_line(int x1,int y1,int x2,int y2)
{
	return SDL_RenderDrawLine(_renderer,x1,y1,x2,y2);
}
//----------------------------------------------
//����Ⱦ���ϻ���
int sdlrenderer::draw_point(int x,int y)
{
	return SDL_RenderDrawPoint(_renderer,x,y);
}
int sdlrenderer::destroy()
{
	SDL_DestroyRenderer(_renderer);
	_renderer = NULL;
	return 0;
}
//////////////////////////////////////////////////////////////////////
//
// 								������
//
//
/////////////////////////////////////////////////////////////
sdlwindow::sdlwindow()
{
	_window = NULL;
}
sdlwindow::sdlwindow(SDL_Window* win)
{
	if(win)
	{
		if(_window)destroy();
		_window = win;
	}
}
sdlwindow::~sdlwindow()
{
	if(_window)destroy();
}
sdlwindow::sdlwindow(const char* title,int px,int py,int pw,int ph,Uint32 flags)
{
	window(title,px,py,pw,ph,flags);
}
int sdlwindow::window(const char* title,int px,int py,int pw,int ph,Uint32 flags)
{
	if(_window)destroy();
	_window = SDL_CreateWindow(title,px,py,pw,ph,flags);
	if(_window==NULL)return -1;
	return 0;
}
int sdlwindow::window(sdlwindow* pwindow)
{
	if(pwindow==NULL)return -1;
	if(_window)destroy();
	_window = pwindow->_window;
	if(_window==NULL)return -1;
	return 0;
}
SDL_Window* sdlwindow::window()
{
	return _window;
}
int sdlwindow::destroy()
{
	SDL_DestroyWindow(_window);
	_window = NULL;
	return 0;
}
sdlrenderer* sdlwindow::create_renderer(int index,Uint32 flags)
{
	SDL_Renderer* ren = SDL_CreateRenderer(_window,index,flags);
	return new sdlrenderer(ren);
}
//-----------------------------------
//�õ����ڱ���
sdlsurface* sdlwindow::get_window_surface()
{
	return new sdlsurface(SDL_GetWindowSurface(_window));
}
//------------------------------------
//���´��ڱ���
int sdlwindow::update_window_surface()
{
	return SDL_UpdateWindowSurface(_window);
}
//------------------------------------------
//���´���λ��
int sdlwindow::pos(int x,int y)
{
	SDL_SetWindowPosition(_window,x,y);
	return 0;
}
//----------------------------------------------
//���´��ڴ�С
int sdlwindow::size(int w,int h)
{
	SDL_SetWindowSize(_window,w,h);
	return 0;
}
int sdlwindow::size(int *w,int *h)
{
	SDL_GetWindowSize(_window,w,h);	
	return 0;
}
//----------------------------------------------------
//��ʾ����
int sdlwindow::show()
{
	SDL_ShowWindow(_window);
	return 0;
}
//----------------------------------------------------------
//���ش���
int sdlwindow::hide()
{
	SDL_HideWindow(_window);
	return 0;
}
#endif //__sdlbase_head__
