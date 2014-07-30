# sdlgui class
snippet sdl_class
abbr sdl_class{...}
# alias sdl_class
  typedef class ${1:#:name} : public GUI<$1,${2:#:parent class}>
  {
    public:
      $1(); 
      $1(const char*,int,int,int,int,Uint32); 
      ~$1();
      int init();
      int init(const char*,int,int,int,int,Uint32); 
      int sysevent(SDL_Event*);
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
  int $1::sysevent(SDL_Event* e)
  {
    return $2::sysevent(e);
  }
  int $1::draw()
  {
    return $2::draw();
  }
