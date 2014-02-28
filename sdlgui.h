//----------------------------------------------------------------------------------------------------------------
//
//
//
//
//						文档名：						sdlgui.h
//
//						文档创建日期：			2014年2月22日
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
#ifndef __SDLGUI_HANDLE__
#define __SDLGUI_HANDLE__
//----------------------------------------------
//
// 					自定义消息常量定义
// 					每个集合为七位数的编码
//          前四位是这类集合的代码
//          后三位是集合子消息的代码
//
//---------------------------------------------
/*
#define __event_macro__(x,y) x##y
//计时器消息集合1000
#define timer_event_macro(y) __event_macro__(1000,y) 
const int sdlgui_event_timer = timer_event_macro(001);
//
//按钮类消息集合1001
#define button_event_macro(y) __event_macro__(1001,y) 
const int sdlgui_button_up= button_event_macro(001);
const int sdlgui_button_down = button_event_macro(002);
const int sdlgui_button_click = button_event_macro(003);
//
//IME类消息集合1002
#define ime_event_macro(y) __event_macro__(1002,y) 
const int sdlgui_ime_up= ime_event_macro(001);
*/
//--------------------------------------------------------
//
//
//
//
//
//--------------------------------------------------------
#include "sdlbase.h"
#include "sdlwindow.h"
#include "sdltools.h"
#endif// __SDLGUI_HANDLE__

