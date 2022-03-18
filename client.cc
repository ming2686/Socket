#include "common.h"

char name[NAMESIZE]="[DEFAULT]";
char msg[BUFSIZE];
//client project!!!!

int main(int argc, char* argv[]){
	WSADATA wsadata;
	SOCKET H_socket;
	SOCKADDR_IN H_addr;
	pthread_t snd_thread, rcv_thread;
	
	char msg[BUFSIZE+1]="Hi I'm yming!!!";
	int strLen;

	//家南 扼捞宏矾府 檬扁拳 
	if(WSAStartup(MAKEWORD(2,2),&wsadata)!=0){
		ErrorHandling("WSAStartup() error!!!");
		return 1;
	} 
	else {
        Sleep(2000);
        printf("WSAStartup completed!\n");
    }
	
	//家南积己 
	H_socket=socket(PF_INET,SOCK_STREAM,0); 
	if(H_socket==INVALID_SOCKET){
		ErrorHandling("socket() error!!!");
		return 1;
	}
	else {
        Sleep(2000);
        printf("Socket has been created!\n");
    }
	
	H_addr.sin_family=AF_INET; //IPv4
	H_addr.sin_addr.s_addr= inet_addr(MY_LOCAL_IP);
	H_addr.sin_port=htons(DEFAULT_PORT);
	
	//connect server
	if(connect(H_socket,(SOCKADDR*)&H_addr,sizeof(H_addr))==SOCKET_ERROR){
		ErrorHandling("connect() error!!!");
		return 1;
	}
	else {
        printf("Connection has been completed!\n");
    }
    
    pthread_create(&snd_thread, NULL, send_msg, (void *)&H_socket);
    pthread_create(&rcv_thread, NULL, recv_msg, (void *)&H_socket);
    pthread_join(snd_thread, NULL);
    pthread_join(rcv_thread, NULL);

	
	//send data
    if (send(H_socket, msg, strlen(msg), 0) < 0) {
        printf("Send failed!!!\n");
        return 1;
    }
    else{
    	while(1){
    		scanf("%s",&msg);
			//fgets(msg, BUFSIZE, stdin);
    		if(strcmp(msg,"exit")==0)
	        {
	            break;
	        }
    		send(H_socket, msg, strlen(msg),0);//价脚
		}
	}

	closesocket(H_socket);//家南 摧扁
	WSACleanup(); //盔加 秦力拳 
	
	return 0;
}

