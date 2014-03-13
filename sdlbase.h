//----------------------------------------------------------------------------------------------------------------
//
//
//
//
//						�ĵ�����						sdlbase.h
//
//						�ĵ��������ڣ�			2014��2��22��
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
#include <SDL2/SDL2_rotozoom.h>
#include <SDL2/SDL_ttf.h>
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
//
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
		int init();
		int text(const char*);
		char* text();
		int font(const char*,int);
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
		int copy(sdltexture*,const SDL_Rect*,const SDL_Rect*);
		int clear();
		int present();
		int fill_rect(const SDL_Rect*);
		int set_render_draw_color(Uint8,Uint8,Uint8,Uint8);
		sdltexture* render_target();
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
	//_surface = NULL;
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
	if(_surface)return 0;
	return -1;
}
///////////////////////////////////////////
//λ�鴫�䷽������һ������Ϊλ��Դ�Ĵ��䷶Χ���ڶ�������ΪĿ��λ�飬����������ΪĿ�괫�䷶Χ���ɹ�����0
int sdlsurface::blit_surface(const SDL_Rect* srcrect,sdlsurface* dst,SDL_Rect* dstrect)
{
	if(dst)
	{
		return SDL_BlitSurface(_surface,srcrect,dst->surface(),dstrect);
	}
	return -1;
}
//-------------------------------------------------
//�ͷ����õ�surface
int sdlsurface::free_surface()
{
	SDL_FreeSurface(_surface);
	//if(_surface)delete _surface;
	_surface = NULL;
	return 0;
}
//���ñ�����ģʽ
int sdlsurface::surface_blend_mode(SDL_BlendMode mode)
{
	return SDL_SetSurfaceBlendMode(_surface,mode);
}
//-------------------------------------------------
//���ñ���ɫ��ģʽ
int sdlsurface::surface_color_mod(Uint8 r,Uint8 g,Uint8 b)
{
	return SDL_SetSurfaceColorMod(_surface,r,g,b);
}
//--------------------------------------------------
//���ñ���ALPHAģʽ
int sdlsurface::surface_alpha_mod(Uint8 a)
{
	return SDL_SetSurfaceAlphaMod(_surface,a);
}
//--------------------------------------------------
//�õ�����ALPHAģʽ
Uint8 sdlsurface::surface_alpha_mod()
{
	Uint8 a;
	SDL_GetSurfaceAlphaMod(_surface,&a);
	return a;
}
//--------------------------------------
//���ñ����ɫ��
int sdlsurface::set_surface_palette(SDL_Palette* palette)
{
	return SDL_SetSurfacePalette(_surface,palette);
}
//-------------------------------------------
//��������BMPλͼ��ʽд������ļ���
int sdlsurface::save_BMP(const char* file)
{
	return SDL_SaveBMP(_surface,file);
}
//----------------------------------------------
//���������Ŵ��䵽Ŀ��λ�顣
int sdlsurface::blit_scaled(const SDL_Rect* srcrect,sdlsurface* dst,SDL_Rect* dstrect)
{
	if(dst)
	return SDL_BlitScaled(_surface,srcrect,dst->surface(),dstrect);
	return -1;
}
//------------------------------------------------
//������ת����ָ����ʽ���������µı���ָ��
sdlsurface* sdlsurface::convert_surface(SDL_PixelFormat* fmt,Uint32 flags = 0)
{
	return new sdlsurface(SDL_ConvertSurface(_surface,fmt,flags));
}
//----------------------------------------------
//�õ��������
SDL_Rect* sdlsurface::clip_rect()
{
	SDL_Rect* trect = new SDL_Rect;
	memset((char*)trect,0x00,sizeof(SDL_Rect));
	SDL_GetClipRect(_surface,trect);
	return trect;
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
sdltext::sdltext(const char* ptext,int psize)
:
sdlsurface()
{
	_font = NULL;
	init();
	font(ptext,psize);
}
int sdltext::init()
{
	if(!sdltext::is_init)
	{
		sdltext:is_init = 1;
		TTF_Init();
	}
	if(_font)TTF_CloseFont(_font);
	if(sdlsurface::init())return -1;
	return 0;
}
int sdltext::text(const char* ptext)
{
	//cout<<ptext<<endl;
	if(_text)delete _text;
	int len = strlen(ptext)+1;
	_text = new char[len];
	memset(_text,0x00,len);
	strcpy(_text,ptext);
	//---------------------------------
	return 0;
}
char* sdltext::text()
{
	if(_text) return _text;
	return "";
}
int sdltext::font(const char* font_path,int font_size)
{
	if(_font)	TTF_CloseFont(_font);
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
	SDL_Color c = {(pcolor & 0xff0000)>>16,(pcolor & 0x00ff00)>>8,pcolor & 0x0000ff};
	SDL_Color tc = {0,255,255};
	if(!_font)return -1;
	free_surface();
	_surface = TTF_RenderText_Solid(_font,ptext,c);
	if(!_surface)return -1;
	return 0;
}
int sdltext::render_utf8_solid(const char* ptext,Uint32 pcolor)
{
	SDL_Color c = {(pcolor & 0xff0000)>>16,(pcolor & 0x00ff00)>>8,pcolor & 0x0000ff};
	if(!_font)return -1;
	free_surface();
	_surface = TTF_RenderUTF8_Solid(_font,ptext,c);
	if(!_surface)return -1;
	return 0;
}
int sdltext::render_unicode_solid(const Uint16* ptext,Uint32 pcolor)
{
	SDL_Color c = {(pcolor & 0xff0000)>>16,(pcolor & 0x00ff00)>>8,pcolor & 0x0000ff};
	if(!_font)return -1;
	free_surface();
	_surface = TTF_RenderUNICODE_Solid(_font,ptext,c);
	if(!_surface)return -1;
	return 0;
}
int sdltext::render_glyph_solid(const Uint16 ptext,Uint32 pcolor)
{
	SDL_Color c = {(pcolor & 0xff0000)>>16,(pcolor & 0x00ff00)>>8,pcolor & 0x0000ff};
	if(!_font)return -1;
	free_surface();
	_surface = TTF_RenderGlyph_Solid(_font,ptext,c);
	if(!_surface)return -1;
	return 0;
}
int sdltext::render_text_shaded(const char* ptext,Uint32 pcolor,Uint32 pcolor1)
{
	SDL_Color c = {(pcolor & 0xff0000)>>16,(pcolor & 0x00ff00)>>8,pcolor & 0x0000ff};
	SDL_Color c1 = {(pcolor1 & 0xff0000)>>16,(pcolor1 & 0x00ff00)>>8,pcolor1 & 0x0000ff};
	if(!_font)return -1;
	free_surface();
	_surface = TTF_RenderText_Shaded(_font,ptext,c,c1);
	if(!_surface)return -1;
	return 0;
}
int sdltext::render_utf8_shaded(const char* ptext,Uint32 pcolor,Uint32 pcolor1)
{
	SDL_Color c = {(pcolor & 0xff0000)>>16,(pcolor & 0x00ff00)>>8,pcolor & 0x0000ff};
	SDL_Color c1 = {(pcolor1 & 0xff0000)>>16,(pcolor1 & 0x00ff00)>>8,pcolor1 & 0x0000ff};
	if(!_font)return -1;
	free_surface();
	_surface = TTF_RenderUTF8_Shaded(_font,ptext,c,c1);
	if(!_surface)return -1;
	return 0;
}
int sdltext::render_unicode_shaded(const Uint16* ptext,Uint32 pcolor,Uint32 pcolor1)
{
	SDL_Color c = {(pcolor & 0xff0000)>>16,(pcolor & 0x00ff00)>>8,pcolor & 0x0000ff};
	SDL_Color c1 = {(pcolor1 & 0xff0000)>>16,(pcolor1 & 0x00ff00)>>8,pcolor1 & 0x0000ff};
	if(!_font)return -1;
	free_surface();
	_surface = TTF_RenderUNICODE_Shaded(_font,ptext,c,c1);
	if(!_surface)return -1;
	return 0;
}
int sdltext::render_glyph_shaded(const Uint16 ptext,Uint32 pcolor,Uint32 pcolor1)
{
	SDL_Color c = {(pcolor & 0xff0000)>>16,(pcolor & 0x00ff00)>>8,pcolor & 0x0000ff};
	SDL_Color c1 = {(pcolor1 & 0xff0000)>>16,(pcolor1 & 0x00ff00)>>8,pcolor1 & 0x0000ff};
	if(!_font)return -1;
	free_surface();
	_surface = TTF_RenderGlyph_Shaded(_font,ptext,c,c1);
	if(!_surface)return -1;
	return 0;
}
int sdltext::render_text_blended(const char* ptext,Uint32 pcolor)
{
	SDL_Color c = {(pcolor & 0xff0000)>>16,(pcolor & 0x00ff00)>>8,pcolor & 0x0000ff};
	if(!_font)return -1;
	free_surface();
	_surface = TTF_RenderText_Blended(_font,ptext,c);
	if(!_surface)return -1;
	return 0;
}
int sdltext::render_utf8_blended(const char* ptext,Uint32 pcolor)
{
	SDL_Color c = {(pcolor & 0xff0000)>>16,(pcolor & 0x00ff00)>>8,pcolor & 0x0000ff};
	if(!_font)return -1;
	free_surface();
	_surface = TTF_RenderUTF8_Blended(_font,ptext,c);
	if(!_surface)return -1;
	return 0;
}
int sdltext::render_unicode_blended(const Uint16* ptext,Uint32 pcolor)
{
	SDL_Color c = {(pcolor & 0xff0000)>>16,(pcolor & 0x00ff00)>>8,pcolor & 0x0000ff};
	if(!_font)return -1;
	free_surface();
	_surface = TTF_RenderUNICODE_Blended(_font,ptext,c);
	if(!_surface)return -1;
	return 0;
}
int sdltext::render_glyph_blended(const Uint16 ptext,Uint32 pcolor)
{
	SDL_Color c = {(pcolor & 0xff0000)>>16,(pcolor & 0x00ff00)>>8,pcolor & 0x0000ff};
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
	return new sdlrenderer(SDL_CreateSoftwareRenderer(_surface));
}
//-----------------------------------------
//�õ�ָ�����������ֵ
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
//����ָ�����������ֵ
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
//-------------------------------------t--------------
//����һ��ͼƬ��ҪSDL_img��֧��
int sdlsurface::img_load(const char* pfile)
{
	if(pfile == NULL)return -1;
	//if(_surface)SDL_FreeSurface(_surface);
	_surface = IMG_Load(pfile);
	return 0;
}
//------------------------------------------------------
//��������
int sdlsurface::lock_surface()
{
	SDL_LockSurface(_surface);
	return 0;
}
//-----------------------------------------------
//��������
int sdlsurface::unlock_surface()
{
	SDL_UnlockSurface(_surface);
	return 0;
}
//-------------------------------------------------
//���ñ���ALPHAģʽ�Ĺؼ�ɫ
int sdlsurface::color_key(int flag,Uint32 key)
{
	return SDL_SetColorKey(_surface,flag,key);
}
//-------------------------------------------------
//�õ�ALPHAģʽ�Ĺؼ�ɫ
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
		if(_texture)delete _texture;
		_texture = tex;
	}
}
sdltexture::~sdltexture()
{
	if(_texture)
	{
		destroy();
		delete _texture;
	}
}
int sdltexture::texture(SDL_Texture* tex)
{
	if(_texture)delete _texture;
	_texture = tex;
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
		if(_renderer)delete _renderer;
		_renderer = ren;
	}
}
sdlrenderer::~sdlrenderer()
{
	if(_renderer)
	{
		destroy();
		delete _renderer;
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
		if(_window)delete _window;
		_window = win;
	}
}
sdlwindow::~sdlwindow()
{
	if(_window)delete _window;
}
sdlwindow::sdlwindow(const char* title,int px,int py,int pw,int ph,Uint32 flags)
{
	window(title,px,py,pw,ph,flags);
}
int sdlwindow::window(const char* title,int px,int py,int pw,int ph,Uint32 flags)
{
	if(_window)delete _window;
	_window = SDL_CreateWindow(title,px,py,pw,ph,flags);
	if(_window==NULL)return -1;
	return 0;
}
int sdlwindow::window(sdlwindow* pwindow)
{
	if(pwindow==NULL)return -1;
	if(_window)delete _window;
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
