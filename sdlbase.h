//----------------------------------------------------------------------------------------------------------------
//
//
//
//
//						文档名：						sdlbase.h
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
using namespace std;
/////////////////////////////////////////////////
class sdlsurface;
class sdltext;
class sdltexture;
class sdlrenderer;
class sdlwidnow;
///////////////////////////////////////////////////////////////////////
//
//						SDL表面对象操作函数的封装
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
		/* 画一条任意直线 */
		int line(int,int,int,int,Uint32);
		/* 画或填充一个矩形 */
		int rectangle(int,int,int,int,Uint32,int);
		/* 画或填充一个正圆 */
		int circle(int,int,int,Uint32,int);
		/* 画或填充一个椭圆 */
		int ellipse(int,int,int,int,Uint32,int);
		/* 旋转表面 */
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
//               文本渲染类
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
		 设置当前文本,
		 参数(文本，字体，字体大小)
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
	protected:
		TTF_Font* _font;
		char* _text;
	protected:
		static int is_init;
}*sdltext_ptr;
int sdltext::is_init = 0;
//--------------------------------------------
//
///
//              纹理类申明
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
//              渲染类申明
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
//             窗口类申明
//
//------------------------------------------
class sdlwindow
{
	public:
		sdlwindow();//窗口构造函数
		sdlwindow(SDL_Window* win);
		sdlwindow(const char*,int,int,int,int,Uint32);//创建窗口函数
		virtual ~sdlwindow();//窗口析构函数
	protected:
		SDL_Window *_window;//窗口类主体变量
	public:
		int window(const char*,int,int,int,int,Uint32);//创建窗口函数
		int window(sdlwindow*);//传递窗口指针
		SDL_Window* window();//返回窗口指针
		int destroy();//消毁窗口
		////
		sdlrenderer* create_renderer(int,Uint32);//创建窗口渲染对象 
		///
		sdlsurface* get_window_surface();//得到窗口表面
		//
		int update_window_surface();//更新窗口表面
		//
		int pos(int,int);//更新窗口位置
		//
		int size(int*,int*);//取窗口大小
		int size(int,int);//更新窗口大小
		//
		int show();//显示窗口
		//
		int hide();//隐藏窗口
};
//-------------------------------------------
//
//
//
//
//
//                    类实现
//
//
//
//
//-------------------------------------------
sdlsurface::sdlsurface()
{
	_surface = NULL;
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
		free_surface();
	}
}
int sdlsurface::surface(SDL_Surface* surface)
{
	if(surface)
	{
		if(_surface)free_surface();
		_surface = surface;
		return 0;
	}
	return -1;
}
int sdlsurface::init()
{
	if(_surface)free_surface();
	return 0;
}
int sdlsurface::init(SDL_Surface* sur)
{
	if(sur)
	{
		if(_surface)free_surface();
		_surface = sur;		
		return 0;
	}
	return -1;
}
int sdlsurface::init(Uint32 flags,int width,int height,int depth,Uint32 Rmask,Uint32 Gmask,Uint32 Bmask,Uint32 Amask)
{
	if(_surface)free_surface();
	create_rgb_surface(flags,width,height,depth,Rmask,Gmask,Bmask,Amask);
	return 0;
}
int sdlsurface::create_rgb_surface(Uint32 flags,int width,int height,int depth,Uint32 Rmask,Uint32 Gmask,Uint32 Bmask,Uint32 Amask)
{
	if(_surface)free_surface();
	//_surface = NULL;
	_surface = SDL_CreateRGBSurface(flags,width,height,depth,Rmask,Gmask,Bmask,Amask);
	if(_surface)return 0;
	return -1;
}
int sdlsurface::fill_rect(const SDL_Rect* rect,Uint32 color)
{
	return SDL_FillRect(_surface,rect,color);
}
int sdlsurface::load_bmp(const char* file)
{
	if(_surface)free_surface();
	_surface = SDL_LoadBMP(file);
	//_surface = SDL_CreateRGBSurfaceFrom(t->pixels,t->w,t->h,t->format->BitsPerPixel,t->pitch,t->format->Rmask,t->format->Gmask,t->format->Bmask,t->format->Amask);
	if(_surface)return 0;
	return -1;
}
///////////////////////////////////////////
//位块传输方法，第一个参数为位块源的传输范围，第二个参数为目标位块，第三个参数为目标传输范围。成功返回0
int sdlsurface::blit_surface(const SDL_Rect* srcrect,sdlsurface* dst,SDL_Rect* dstrect)
{
	if(dst)
	{
		return SDL_BlitSurface(_surface,srcrect,dst->surface(),dstrect);
	}
	return -1;
}
//-------------------------------------------------
//释放无用的surface
int sdlsurface::free_surface()
{
	/* 这个函数没有返回值 */
	SDL_FreeSurface(_surface);
	_surface = NULL;
	return 0;
}
//设置表面混合模式
int sdlsurface::surface_blend_mode(SDL_BlendMode mode)
{
	return SDL_SetSurfaceBlendMode(_surface,mode);
}
//-------------------------------------------------
//设置表面色彩模式
int sdlsurface::surface_color_mod(Uint8 r,Uint8 g,Uint8 b)
{
	return SDL_SetSurfaceColorMod(_surface,r,g,b);
}
//--------------------------------------------------
//设置表面ALPHA模式
int sdlsurface::surface_alpha_mod(Uint8 a)
{
	return SDL_SetSurfaceAlphaMod(_surface,a);
}
//--------------------------------------------------
//得到表面ALPHA模式
Uint8 sdlsurface::surface_alpha_mod()
{
	Uint8 a;
	SDL_GetSurfaceAlphaMod(_surface,&a);
	return a;
}
//--------------------------------------
//设置表面调色盘
int sdlsurface::set_surface_palette(SDL_Palette* palette)
{
	return SDL_SetSurfacePalette(_surface,palette);
}
//-------------------------------------------
//将表面以BMP位图格式写入磁盘文件。
int sdlsurface::save_BMP(const char* file)
{
	return SDL_SaveBMP(_surface,file);
}
//----------------------------------------------
//将表面缩放传输到目标位块。
int sdlsurface::blit_scaled(const SDL_Rect* srcrect,sdlsurface* dst,SDL_Rect* dstrect)
{
	if(dst)
	return SDL_BlitScaled(_surface,srcrect,dst->surface(),dstrect);
	return -1;
}
//------------------------------------------------
//将表面转换成指定格式，并返回新的表面指针
sdlsurface* sdlsurface::convert_surface(SDL_PixelFormat* fmt,Uint32 flags = 0)
{
	return new sdlsurface(SDL_ConvertSurface(_surface,fmt,flags));
}
//----------------------------------------------
//得到表面剪辑
SDL_Rect* sdlsurface::clip_rect()
{
	memset((char*)&_surface_rect,0x00,sizeof(SDL_Rect));
	SDL_GetClipRect(_surface,&_surface_rect);
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
	使用指定的字体和字号来构造一个文本表面对象 
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
	SDL_Color c = {(Uint8)((pcolor & 0xff0000)>>16),(Uint8)((pcolor & 0x00ff00)>>8),(Uint8)(pcolor & 0x0000ff)};
	if(!_font)return -1;
	free_surface();
	_surface = TTF_RenderUTF8_Solid(_font,ptext,c);
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
//由表面创建一个渲染器
sdlrenderer* sdlsurface::create_software_renderer()
{
	return new sdlrenderer(SDL_CreateSoftwareRenderer(_surface));
}
//-----------------------------------------
//得到指定坐标的像素值
int sdlsurface::pixel(int x,int y)
{
	if(_surface==NULL)return -1;
	int bpp = _surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)_surface->pixels + y * _surface->pitch + x * bpp;
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
//设置指定坐标的像素值
int sdlsurface::pixel(int x,int y,Uint32 v)
{
	if(_surface == NULL)return -1;
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
	return 0;
}
//----------------------------------------------------------
//画或填充一个矩形
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
		/* 画两条水平线 */
		line(x0,y0,x1,y0,color);
		line(x0,y1,x1,y1,color);
		/* 画两条垂直线 */
		line(x0,y0,x0,y1,color);
		line(x1,y0,x1,y1,color);
		return 0;
	}
}
/* 
	 画线函数 
	先确定是画水平线，垂直线，还是任意直线 
	再锁定表面选择画线方式开始画线
	最后解锁
 */
int sdlsurface::line(int x0,int y0,int x1,int y1,Uint32 color)
{
	if(_surface == NULL)return -1;
	//取出像素深度
	int bpp = _surface->format->BytesPerPixel;
	//计算小坐标
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
	/* 取出像素数据首地址 */
	Uint8 *p = (Uint8*)_surface->pixels+ty0*_surface->pitch+tx0*bpp;
	//
	float x_off=tx1-tx0;
	float y_off=ty1-ty0;
	int x,y;
	//float xy_s;
	/* 如果线的终点超过了表面宽度则截取有效长度 */
	x_off -= (tx1>=_surface->pitch)?x_off-_surface->pitch : 0;
	x_off = (tx1<=0)?0:x_off;
	y_off -= (ty1>=_surface->h)?ty1-_surface->h:0;
	y_off = (ty1<=0)?0:y_off;
	//
	//选择格式
	//if(must_lock())lock_surface();
	switch(bpp)
	{
		/* 单色 */
		case 1:
			/* 如果画水平线 */
			if(!y_off)
			{
				memset((Uint32*)p,color,x_off*bpp);
			}
		break;
		/* 16色 */
		case 2:
		break;
		/*  */
		case 3:
		break;
		/* 32位 */
		case 4:
			/* 如果画水平线 */
			if(!y_off)
			{
				for(x=0;x<x_off;x++)
				{
					*(Uint32*)(p+x*bpp) = color;
				}
			}
			else
			/* 如果画垂直线 */
			if(!x_off)
			{
				for(y=0;y<y_off;y++)
				{
					*(Uint32*)(p+y*_surface->pitch) = color;
				}
			}
			/* 画任意斜线 */
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
//画一个圆,pm=0表示不填充,pm=1表示填充
int sdlsurface::circle(int px,int py,int pr,Uint32 color,int pm =0)
{
	if(_surface == NULL)return -1;
	//如果半径小于3则表示无法绘制，直接退出
	if(pr<3)return -1;
	//取出像素深度
	int bpp = _surface->format->BytesPerPixel;
	int i = 0;
	//新点坐标
	float tx,ty,tx1,ty1;
	float pj=0;
	switch(bpp)
	{
		/* 单色 */
		case 1:
		break;
		/* 16色 */
		case 2:
		break;
		/*  */
		case 3:
		break;
		/* 32位 */
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
					//计算第二项限再计算第一项限
					line(px-tx,py-ty,px+tx,py-ty,color);
					//计算第三项限再计算第四项限
					line(px-tx,py+ty,px+tx,py+ty,color);
				}
				else
				{
					//计算第一项限起点的坐标
					tx1 = px+tx;
					ty1 = py-ty;
					pixel(tx1,ty1,color);
					//计算第二项限起点坐标
					tx1 = px-tx;
					ty1 = py-ty;
					pixel(tx1,ty1,color);
					//计算第三项限起点坐标
					tx1 = px-tx;
					ty1 = py+ty;
					pixel(tx1,ty1,color);
					//计算第四项限起点坐标
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
//画一个椭圆，pm=0表示不填充，pm=1表示填充
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
//旋转表面
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
	/* 取出图像高宽*/
	row = clip_rect()->h;
	column = clip_rect()->w;
	//
	sdlsurface tsur(0,column,row,32,0,0,0,0);
	//memcpy((char*)&tsur,(char*)this,sizeof(sdlsurface));
	tsur.fill_rect(NULL,0x000000);
	/* 算出中心坐标 */
	op_x = column/2;
	op_y = row/2;
	/* 算出p0坐标 */
	p0x = op_x;
	p0y = row;
	for(row_off=0;row_off<row;row_off++)
	{
		for(column_off = 0;column_off<column;column_off++)
		{
			/* 更新p1坐标 */
			p1x = column_off;
			p1y = row_off;
			//cout<<p1x<<":"<<p1y<<endl;
			/* 算出三角形边长 */
			a = sqrt((p1x-op_x)*(p1x-op_x)+(p1y-op_y)*(p1y-op_y));
			c = sqrt((p1x-p0x)*(p1x-p0x)+(p1y-p0y)*(p1y-p0y));
			b = op_y;
			/* 算出要转换到这个点的角度 */
			change_pixel_angle = acos((a*a+b*b-c*c)/(2*a*b))*180/3.1415926;
			//cout<<"col:"<<column_off<<"-row:"<<row_off<<":"<<change_pixel_angle<<endl;
			/* 算出旋转后的角度 */
			if(p1x>p0x)
			{
				change_pixel_angle -= j;
			}
			else
			{
				change_pixel_angle += j;
			}
			//change_pixel_angle = (change_pixel_angle>359)?0:change_pixel_angle;
			/* 算出旋转后c的长度 */
			c = sqrt(a*a+b*b-cos(change_pixel_angle/180*3.1415926)*2*a*b);
			/* 算出BC夹角 */
			change_pixel_angle = acos((b*b+c*c-a*a)/(2*b*c));//*180/3.1415926;
			/* 算出旋转后这个点的坐标 */
			if(p1x>p0x)
			{
				x = p0x + sin(change_pixel_angle)*c;
			}
			else
			{
				x = p0x - sin(change_pixel_angle)*c;
			}
			y = p0y - cos(change_pixel_angle)*c;
			/* 开始复制像素 */
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
	/* 更新到表面 */
	tsur.blit_scaled(NULL,this,NULL);
	return 0;
}
//-------------------------------------t--------------
//加载一个图片，要SDL_img的支持
int sdlsurface::img_load(const char* pfile)
{
	if(pfile == NULL)return -1;
	if(_surface)
	{
		SDL_FreeSurface(_surface);
		_surface = NULL;
	}
	_surface = IMG_Load(pfile);
	if(_surface)return 0;
	return -1;
}
//--------------------------------------------
//表面锁定状态
int sdlsurface::must_lock()
{
	return SDL_MUSTLOCK(_surface);
}
//------------------------------------------------------
//锁定表面
int sdlsurface::lock_surface()
{
	SDL_LockSurface(_surface);
	return 0;
}
//-----------------------------------------------
//解锁表面
int sdlsurface::unlock_surface()
{
	SDL_UnlockSurface(_surface);
	return 0;
}
//-------------------------------------------------
//设置表面ALPHA模式的关键色
int sdlsurface::color_key(int flag,Uint32 key)
{
	return SDL_SetColorKey(_surface,flag,key);
}
//-------------------------------------------------
//得到ALPHA模式的关键色
Uint32 sdlsurface::color_key()
{
	Uint32 key;
	SDL_GetColorKey(_surface,&key);
	return key;
}
//-------------------------------------------------
//
Uint32 sdlsurface::map_rgb(Uint8 r,Uint8 g,Uint8 b)
{
	return SDL_MapRGB(_surface->format,r,g,b);
}
//-------------------------------------------------
//
Uint32 sdlsurface::map_rgba(Uint8 r,Uint8 g,Uint8 b,Uint8 a)
{
	return SDL_MapRGBA(_surface->format,r,g,b,a);
}
#ifndef __ANDROID_OS__
//-----------------------------------------------------
//旋转缩放表面
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
//旋转缩放(X,Y)表面
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
//旋转缩放表面后的大小
SDL_Point sdlsurface::rotozoom_surface_size(int width,int height,double angle,double zoom,int *dstwidth = NULL,int *dstheight = NULL)
{
	SDL_Point pt = {0,0};	
	rotozoomSurfaceSize(width,height,angle,zoom,&pt.x,&pt.y);	
	return pt;
}
//-----------------------------------------------------
//旋转缩放(X,Y)表面后的大小
SDL_Point sdlsurface::rotozoom_surface_size_xy(int width,int height,double angle,double zoomx,double zoomy,int *dstwidth = NULL,int *dstheight = NULL)
{
	SDL_Point pt = {0,0};	
	rotozoomSurfaceSizeXY(width,height,angle,zoomx,zoomy,&pt.x,&pt.y);	
	return pt;
}
//-----------------------------------------------------
//缩放表面后的大小
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
//缩放(X,Y)表面后的大小
SDL_Point sdlsurface::zoom_surface_size(int width,int height,double zoomx,double zoomy,int* dstwidth = NULL,int* dstheight = NULL)
{
	SDL_Point pt = {0,0};
	zoomSurfaceSize(width,height,zoomx,zoomy,&pt.x,&pt.y);
	return pt;	
}
//-----------------------------------------------------
//收缩表面
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
//90度旋转表面
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
// 								纹理类
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
//消毁一个纹理
int sdltexture::destroy()
{
	SDL_DestroyTexture(_texture);
	_texture = NULL;
	return 0;
}
/////////////////////////////////////////////////////////////////////////
//
// 					渲染类
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
//得到渲染器的目标纹理
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
//在渲染器上画线
int sdlrenderer::draw_line(int x1,int y1,int x2,int y2)
{
	return SDL_RenderDrawLine(_renderer,x1,y1,x2,y2);
}
//----------------------------------------------
//在渲染器上画点
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
// 								窗口类
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
//得到窗口表面
sdlsurface* sdlwindow::get_window_surface()
{
	return new sdlsurface(SDL_GetWindowSurface(_window));
}
//------------------------------------
//更新窗口表面
int sdlwindow::update_window_surface()
{
	return SDL_UpdateWindowSurface(_window);
}
//------------------------------------------
//更新窗口位置
int sdlwindow::pos(int x,int y)
{
	SDL_SetWindowPosition(_window,x,y);
	return 0;
}
//----------------------------------------------
//更新窗口大小
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
//显示窗口
int sdlwindow::show()
{
	SDL_ShowWindow(_window);
	return 0;
}
//----------------------------------------------------------
//隐藏窗口
int sdlwindow::hide()
{
	SDL_HideWindow(_window);
	return 0;
}
#endif //__sdlbase_head__
