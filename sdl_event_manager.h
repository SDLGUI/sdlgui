#ifndef __SDLGUI_EVENT_MANAGER_HEAD__
#define __SDLGUI_EVENT_MANAGER_HEAD__
#ifdef DLLEXPORT
	#define def_dll __declspec(dllexport)
#else
	#define def_dll
#endif

#include <map>
#include <string>
#include <sstream>

class sdl_board;
class sdl_event_struct;
/*
		定义事件句柄类型 
		要求所有事件函数返回整型值，
		调用对象与参数为事件参数
 */
typedef int(sdl_event_struct::*sdl_event_handle)(sdl_board&,void*);

using namespace std;
/* 
	对象事件委托结构体 
 */
class sdl_event_struct
{
	friend class sdl_event_object;
	public:
		def_dll sdl_event_struct()
		{
			_event.clear();
		}
		/* 
			对象事件注册功能，
			注册时要一个事件函数名的字串与函数名入口地址
		 */
		def_dll int event_register(string,sdl_event_handle);
		/*
			 对象事件注消功能
			 注消时要用到事件函数名的字串
		*/
		def_dll int event_unregister(string);
	protected:
		//事件函数入口列表
		def_dll	map<string,sdl_event_handle> _event;
};
def_dll int sdl_event_struct::event_register(string event_string,sdl_event_handle event_function)
{
	_event.insert(pair<string,sdl_event_handle>(event_string,event_function));
	return 0;
}
def_dll int sdl_event_struct::event_unregister(string event_string)
{
	_event.erase(event_string);
	return 0;
}


/* 
		对象事件项目列表 
		用于管理每个对象其中一个事件的托管入口调用
 
 */
class sdl_event_object
{
	friend class sdl_event_manager;
	public:
		def_dll sdl_event_object();
		/* 
			注册一个事件
			参数为事件字串
		 */
		def_dll int event_register(string);
		/* 
			注消一个事件
			参数为事件字串
		 */
		def_dll int event_unregister(string);
		/* 
			事件调用累计一次 
		 */
		def_dll int push();
		/* 
			事件调用一次 
		 */
		def_dll int pull();
		/* 
			事件累计次数 
		 */
		def_dll int count();
	protected:
		def_dll int _event_count;
		def_dll map<string,sdl_event_struct*> _object_event_list;
};
def_dll sdl_event_object::sdl_event_object()
{
	_event_count = 0;
	_object_event_list.clear();
}
def_dll int sdl_event_object::event_register(string event_string)
{
	sdl_event_struct* _event_ingress = new sdl_event_struct;
	_object_event_list.insert(pair<string,sdl_event_struct*>(event_string,_event_ingress));	
	return 0;
}
def_dll int sdl_event_object::event_unregister(string event_string)
{
	_object_event_list.erase(event_string);	
	return 0;
}
def_dll int sdl_event_object::push()
{
	_event_count++;
	return _event_count;
}
def_dll int sdl_event_object::pull()
{
	_event_count--;
	return _event_count;
}
def_dll int sdl_event_object::count()
{
	return _event_count;
}

/* 
			事件管理器

			用于调用对象事件
			实现委托功能与事件多线程化

			功能
			1.加入/移除对象
			2、给对象注册/注销事件
			3、给对象事件加入/删除事件委托函数
			4、自行处理对象事件
 */
class sdl_event_manager
{
	public:
		/* 
			加入事件对象 参数为对象地址
		 */
		def_dll static int push(sdl_board*);
		/* 
			移除事件对象 参数为对象地址
		 */
		def_dll static int pull(sdl_board*);
		/* 
		 加入对象事件，参数为对象地址，事件字串 
		 */
		def_dll static int push(sdl_board*,string);
		/* 
			移除对象事件，参数为对象地址，事件字串 
		 */
		def_dll static int pull(sdl_board*,string);
		/* 
			加入对象事件委托入口函数
			参数为对象地址，事件字串，委托入口函数地址
		 */
		def_dll static int push(sdl_board*,string,sdl_board*,sdl_event_handle);
		/* 
			移除对象事件委托入口函数
			参数为对象地址，事件字串，委托入口函数地址
		 */
		def_dll static int pull(sdl_board*,string,sdl_board*,sdl_event_handle);
	protected:
		def_dll static map<sdl_board*,sdl_event_object*> _event_list;		
};
def_dll map<sdl_board*,sdl_event_object*> sdl_event_manager::_event_list;
def_dll int sdl_event_manager::push(sdl_board* obj)
{
	sdl_event_object *obj_event_list = new sdl_event_object;
	sdl_event_manager::_event_list.insert(pair<sdl_board*,sdl_event_object*>(obj,obj_event_list));
	return 0;
}
def_dll int sdl_event_manager::pull(sdl_board* obj)
{
	sdl_event_manager::_event_list.erase(obj);
	return 0;
}
def_dll int sdl_event_manager::push(sdl_board* obj,string event_string)
{
	map<sdl_board*,sdl_event_object*>::iterator event_iter;
	sdl_event_object* event; 
	/* 先找到对象列表中的对象事件列表的引索 */
	event_iter = sdl_event_manager::_event_list.find(obj);
	if(event_iter == sdl_event_manager::_event_list.end())
	{
		return -1;
	}
	/* 再注册事件到对象事件列表 */
	//cout<<"event_register start"<<endl;
	event = (sdl_event_object*)(event_iter->second);
	//cout<<"event_register stop"<<endl;
	/* 使用对象事件列表自身注册功能 */
	return event->event_register(event_string);
}
def_dll int sdl_event_manager::pull(sdl_board* obj,string event_string)
{
	map<sdl_board*,sdl_event_object*>::iterator event_iter;
	sdl_event_object* event; 
	/* 先找到对象列表中的对象事件列表的引索 */
	event_iter = sdl_event_manager::_event_list.find(obj);
	if(event_iter == sdl_event_manager::_event_list.end())
	{
		return -1;
	}
	/* 再注册事件到对象事件列表 */
	event = (sdl_event_object*)event_iter->second;
	/* 使用对象事件列表自身注册功能 */
	return event->event_unregister(event_string);
}
def_dll int sdl_event_manager::push(sdl_board* connect_object,string event_string,sdl_board* event_object,sdl_event_handle event_hendle)
{
	stringstream event_object_string;
	map<sdl_board*,sdl_event_object*>::iterator event_iter;
	map<string,sdl_event_struct*>::iterator event_struct_iter;
	sdl_event_object* event; 
	sdl_event_struct* event_struct; 
	/* 先找到对象列表中的对象事件列表的引索 */
	event_iter = sdl_event_manager::_event_list.find(connect_object);
	if(event_iter == sdl_event_manager::_event_list.end())
	{
		return -1;
	}
	/* 再读取注册事件对象的事件列表 */
	event = (sdl_event_object*)event_iter->second;
	/* 
		 然后找到对象事件列表中的事件(委托)结构
			没有找到返回-1 
	 */
	event_struct_iter = event->_object_event_list.find(event_string);
	if(event_struct_iter == event->_object_event_list.end())
	{
		return -1;
	}
	/* 使用对象事件列表自身注册功能 */
	event_object_string<<event_object<<"_"<<event_hendle;
	event_struct = (sdl_event_struct*)event_struct_iter->second;

	return event_struct->event_register(event_object_string.str(),event_hendle);
}
def_dll int sdl_event_manager::pull(sdl_board* connect_object,string event_string,sdl_board* event_object,sdl_event_handle event_hendle)
{
	stringstream event_object_string;
	map<sdl_board*,sdl_event_object*>::iterator event_iter;
	map<string,sdl_event_struct*>::iterator event_struct_iter;
	sdl_event_object* event; 
	sdl_event_struct* event_struct; 
	/* 先找到对象列表中的对象事件列表的引索 */
	event_iter = sdl_event_manager::_event_list.find(connect_object);
	if(event_iter == sdl_event_manager::_event_list.end())
	{
		return -1;
	}
	/* 再读取注册事件对象的事件列表 */
	event = (sdl_event_object*)event_iter->second;
	/* 
		 然后找到对象事件列表中的事件(委托)结构
			没有找到返回-1 
	 */
	event_struct_iter = event->_object_event_list.find(event_string);
	if(event_struct_iter == event->_object_event_list.end())
	{
		return -1;
	}
	/* 使用对象事件列表自身注册功能 */
	event_object_string<<event_object<<"_"<<event_hendle;
	event_struct = (sdl_event_struct*)event_struct_iter->second;

	return event_struct->event_unregister(event_object_string.str());
}
#endif //__SDLGUI_EVENT_MANAGER_HEAD__
