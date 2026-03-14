#pragma once

typedef struct{
	short family;
	union{
		unsigned char data[14];

		struct {
			short port;
			unsigned char ip1;
			unsigned char ip2;
			unsigned char ip3;
			unsigned char ip4;
		};
	};
}cp2p_Sockaddr;
