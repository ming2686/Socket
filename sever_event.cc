#include "common.h"

void *handle_client(void* arg){ //client 관리 
	int client_socket = *((int*)arg);
	int strlen=0;
	char msg[BUFSIZE];
	int i=0;
	
	while(strlen=recv(client_socket, msg, BUFSIZE, 0)!=0)
		send_msg(msg,strlen);
	
	pthread_mutex_lock(&g_mutex);
	for(i=0;i<g_client_count;i++){
		if(client_socket==g_client_socket[i]){
			while(++i<g_client_count){
				g_client_socket[i-1]=g_client_socket[i];
			}
			break;
		}
	}
	g_client_count--;
	pthread_mutex_unlock(&g_mutex);
	close(client_socket);
	return NULL;
}

void send_msg(char *msg, int len){ //문자를 받는 함수 
	int i=0;
	pthread_mutex_lock(&g_mutex);
    for(i=0; i<g_client_count; i++) {
        write(g_client_socket[i], msg, len);
    }
    pthread_mutex_unlock(&g_mutex);
}

void ErrorHandling(char* message){
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}


