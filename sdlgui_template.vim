# sdlgui class
snippet sdl_class
abbr sdl_class{...}
# alias sdl_class
  typedef class ${1:#:name} : public GUI<$1,${2:#:parent class}>
  {
    public:
      $1(); 
      $1(const char*,int,int,int,int,Uint32); 
      virtual ~$1();
      int init();
      int init(const char*,int,int,int,int,Uint32); 
      int draw();
    public:
      ${0}
    protected:
  }*$1_ptr;
  $1::$1()
  :
  GUI<$1,$2>()
  {
    init();
  }
  $1::$1(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflags)
  :
  GUI<$1,$2>()
  {
    init(ptitle,px,py,pw,ph,pflags);
  }
	$1::~$1()
	{

	}
  int $1::init()
  {
    if($2::init())return -1;
    return 0;
  }
  int $1::init(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflags)
  {
    if($2::init(ptitle,px,py,pw,ph,pflags))return -1;
    return 0;
  }
  int $1::draw()
  {
    return $2::draw();
  }

#sdl_add_widget
snippet sdl_add_widget
abbr obj.add<sdl_widget>(...)
	${1:#:object} add<${2:sdl_widget}>("${3:#:title}",${4:#:rect},${5:1});

#sdl_event
snippet sdl_event
abbr obj.on_event()=...
${1}${2:.}${3:on_click()}=[${4:&}](sdl_board& obj,SDL_Event& e)
{
	return 0;
};
