#include <winsock2.h>
#include <ws2def.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <stdio.h>

#include "cp2p_struct.h"

int cp2p_init(){
	WSADATA wsaData;
	int result = WSAStartup(MAKEWORD(2,2),&wsaData);
	if(result){
		printf("Windows Socket API init failed!\n");
		printf("Error ID:%d\n",WSAGetLastError());
		return 1;
	}
	return 0;
}

int cp2p_pton(char * address, cp2p_Sockaddr * sockaddr){
	int a = sizeof(cp2p_Sockaddr);
	if (WSAStringToAddressA(address,AF_INET,NULL,(LPSOCKADDR)sockaddr,&a)){
		printf("Address conversion failed.\n");
		printf("Error ID:%d\n",WSAGetLastError());
		return 1;
	}
	return 0;
}

int cp2p_ntop(cp2p_Sockaddr * sockaddr, char * address){
	printf("Not implemented yet!\n");
	return 0;
}

int cp2p_getaddrinfo(char * address, char * port, cp2p_Sockaddr * sockaddr){
	struct addrinfo hints = {0},* res;
	if(getaddrinfo(address, port, &hints, &res)){
		printf("Get Addr Info failed.\n");
		printf("Error ID:%d\n",WSAGetLastError());
		return 1;
	}
	
	for(struct addrinfo * ptr=res; ptr != NULL ;ptr=ptr->ai_next){
		sockaddr->family = ptr->ai_addr->sa_family;
		memcpy(sockaddr->data, ptr->ai_addr->sa_data,14);
	}
	
	freeaddrinfo(res);

	return 0;
}

unsigned short cp2p_ntohs(short netshort){
	return ntohs(netshort);
}
