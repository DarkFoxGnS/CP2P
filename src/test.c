#include <stdio.h>
#include <string.h>

#include "cp2p.h"
#include "cp2p_struct.h"

int main(){
	char ip [20];
	char port [20];

	if(cp2p_init()){
		return 0;
	}
	
	printf("Address:");
	cp2p_readLine(ip, sizeof(ip));
	printf("Port:");
	cp2p_readLine(port, sizeof(port));

	cp2p_Sockaddr addr;
	cp2p_getaddrinfo(ip,port,&addr);
	cp2p_printSockaddr(&addr);
	return 0;
}
