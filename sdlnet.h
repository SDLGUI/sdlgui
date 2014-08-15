#ifndef __SDL_NET_H__
#define __SDL_NET_H__
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <sstream>
class sdlnet_udp_socket
{
	public:
		sdlnet_udp_socket()
		{

		}
		int open(string address,Uint16 port,int channel)
		{
			if(SDLNet_ResolveHost(&_ip_address,address.c_str(),port)==-1)return -1;
			_udp_socket = SDLNet_UDP_Open(port);
			if(_udp_socket==NULL)return -1;
			_channel = SDLNet_UDP_Bind(_udp_socket,channel,&_ip_address);
			packet.channel = _channel;
			packet.address = _ip_address;
			return _channel;
		}
		int bind(int channel,IPaddress& ip)
		{
			return SDLNet_UDP_Bind(_udp_socket,channel,&ip);
		}
		IPaddress* get_peer_address(int channel)
		{
			return SDLNet_UDP_GetPeerAddress(_udp_socket,channel);
		}
		int send(UDPpacket* _packet)
		{
			return SDLNet_UDP_Send(_udp_socket,_channel,_packet);
		}
		template<typename T>
		int send(T data,int len)
		{
			packet.data = (Uint8*)data;
			packet.len = len;
			return SDLNet_UDP_Send(_udp_socket,_channel,&packet);
		}
		int sendV(UDPpacket** packet,int npackets)
		{
			return SDLNet_UDP_SendV(_udp_socket,packet,npackets);
		}
		int recv(UDPpacket& packet)
		{
			return SDLNet_UDP_Recv(_udp_socket,&packet);
		}
		int recvV(UDPpacket** packet)
		{
			return SDLNet_UDP_RecvV(_udp_socket,packet);
		}
	public:
		UDPpacket packet;
	protected:
		UDPsocket _udp_socket;
		IPaddress _ip_address;
		int _channel;
};
class sdlnet_tcp_socket
{
	public:
		sdlnet_tcp_socket()
		{

		}
};
class sdlnet
{
	public:
		union
		{
			sdlnet_udp_socket udp;
			sdlnet_tcp_socket tcp;
		};
	public:
		sdlnet()
		{

		}
		static const char* number_to_address(Uint32 n)
		{
			if(!n)return NULL;
			string ip_str;
			string num = sdlnet::number_to_hex(n);
			stringstream ss;
			int i;
			switch(SDL_BYTEORDER)
			{
				case SDL_BIG_ENDIAN:
					for(i=0;i<6;i+=2)
					{
						ss<<sdlnet::number_to_dec(num.substr(i,2).c_str())<<".";
					}
				break;
				case SDL_LIL_ENDIAN:
					for(i=6;i>=0;i-=2)
					{
						ss<<sdlnet::number_to_dec(num.substr(i,2).c_str())<<".";
					}
				break;
			}
			ip_str = ss.str();
			ip_str.erase(ip_str.length()-1);
			return ip_str.c_str();
		}
		static const int resolve_host(IPaddress* address,const char* host,Uint16 port)
		{
			return SDLNet_ResolveHost(address,host,port);
		}
		static const char* resolve_ip(IPaddress* address)
		{
			return SDLNet_ResolveIP(address);
		}
		static const char* localhost_ip(Uint32& num_ip)
		{
			IPaddress _localhost_ip;
			SDLNet_ResolveHost(&_localhost_ip,NULL,0);
			SDLNet_ResolveHost(&_localhost_ip,SDLNet_ResolveIP(&_localhost_ip),0);
			num_ip = _localhost_ip.host;
			return number_to_address(_localhost_ip.host);
		}
	//protected:
		static int to_dec(char n)
		{
			if(n>='0'&&n<='9')
			{
				return n-48;
			}
			else
			if(n>='A'&&n<='F')
			{
				return n-55;
			}
			else
			if(n>='a'&&n<='f')
			{
				return n-87;
			}
			return -1;
		}
		static int number_to_dec(const char* n)
		{
			int num=0;
			while(*n)
			{
				num*=16;
				num+=to_dec(*n);
				n++;
			}
			return num;
		}
		static char to_hex(int n)
		{
			if(n>=0 && n<=9)
			{
				return n+48;
			}
			else
			if(n>=10 && n<=15)
			{
				return n+55;
			}
			return 0;
		}
		static char* number_to_hex(Uint32 n)
		{
			char *hex = new char[100];
			if(!n)
			{
				hex[0]='0';
				hex[1]=0;
				return hex;
			}
			int index=0;
			int c;
			while(n)
			{
				hex[index]=to_hex(n%16);
				index++;
				n/=16;
			}
			if(index%8)
			{
				hex[index++]='0';
				hex[index]=0x00;
			}
			for(n=0;n<index/2;n++)
			{
				c = hex[n];
				hex[n] = hex[index-n-1];
				hex[index-n-1] = c;
			}
			return hex;
		}
};
#endif
