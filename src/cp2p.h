#include <stdio.h>
#include <string.h>

#include "cp2p_struct.h"

int cp2p_init();
int cp2p_pton(char * address, cp2p_Sockaddr * sockaddr);
int cp2p_ntop(cp2p_Sockaddr * sockaddr, char * address);
int cp2p_getaddrinfo(char * ip, char * port, cp2p_Sockaddr * sockaddr);
unsigned short cp2p_ntohs(short netshort);

void cp2p_printCompileInfo(){
	printf("Compile info:\n");
	printf("\tCompiled at %s\n",COMPILE_TIME);
	printf("\ton branch %s\n",GIT_BRANCH);
	printf("\twith hash \"%s\"\n",GIT_HASH);
}

void cp2p_printSockaddr(cp2p_Sockaddr * sockaddr){
	printf(
			"cp2p_Sockaddr(%p): %u.%u.%u.%u:%u\n",
			sockaddr,
			(sockaddr->data+2)[0],
			(sockaddr->data+2)[1],
			(sockaddr->data+2)[2],
			(sockaddr->data+2)[3],
			cp2p_ntohs(*(unsigned short*)sockaddr->data)
			);
}

void cp2p_flushInBuffer(FILE * file){
	unsigned char c;
	while ((c = getc(file)) != EOF && c != '\n');
}

void cp2p_readLine(char * line,int size){
	fgets(line,size,stdin);
	int length = strlen(line);
	if (length > 0 && line[length-1] == '\n'){
		line[length-1] = 0;
	}else{
		cp2p_flushInBuffer(stdin);
	}
}

#ifdef _WIN32
#include "win_cp2p.h"
#endif

#ifdef __linux__
#include "lin_cp2p.h"
#endif
