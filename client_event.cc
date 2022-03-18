#include "common.h"

void *send_msg(void *arg){
	int socket=*((int *)arg);
	char name_msg[NAMESIZE+BUFSIZE];
	while(1){
		fgets(msg, BUFSIZE, stdin);
		if(!strcmp(msg, "q\n") || !strcmp(msg, "Q\n")) {
            close(socket);
            // exit(0)�� �ƴ� return NULL�� �ϸ� ���� recv_msg �����尡 ����־ �ٷ� ������� �ʴ´�
            exit(0);
        } 
        sprintf(name_msg, "%s %s", name, msg);
        //write(socket, name_msg, strlen(name_msg));
	}
	return NULL;
}

void *recv_msg(void *arg){
	int socket=*((int *)arg);
	char name_msg[NAMESIZE+BUFSIZE];
	int strlen;
	while(1){
		strlen = read(socket, name_msg, sizeof(name_msg)-1);
        if(strlen < 0) {
            return NULL;
        }
        name_msg[strlen] = 0;
        fputs(name_msg, stdout);
	}
	return NULL;	
}

void ErrorHandling(char* message){
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

