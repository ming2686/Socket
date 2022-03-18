#include "common.h"
int g_client_socket[CLNT_MAX]; //client는 10명
int g_client_count=0;
pthread_mutex_t g_mutex;//뮤텍스 설정 

int main(int argc, char** argv) {
	WSADATA wsadata;
	SOCKET server_socket, client_socket;
	SOCKADDR_IN server_addr, client_addr;
	pthread_t t_thread;
	
	int size_client_addr;
	char msg[BUFSIZE+1]; //데이터를 받아올 변수 
	int retval;
		
	pthread_mutex_init(&g_mutex, NULL);

	//소켓 라이브러리 초기화
	if(WSAStartup(MAKEWORD(2,2),&wsadata)!=0){
		ErrorHandling("WSAStartup() error!!!");
		return -1;
	}
	else{
		Sleep(2000);
		printf("WSAStartup completed!!\n");
	}
	
	//소켓생성 
	server_socket=socket(PF_INET,SOCK_STREAM,0); 
	if(server_socket==INVALID_SOCKET){
		ErrorHandling("socket() error!!!");
		return -1;
	}
	else{
		Sleep(2000);
		printf("Socket has been created!\n");
	}

	server_addr.sin_family=AF_INET; //IPv4
	server_addr.sin_port=htons(DEFAULT_PORT);
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	
	//IP주소와 포트번호 할당, 소켓이랑 서버의 정보를 묶어줌
	if(bind(server_socket,(SOCKADDR*)&server_addr,sizeof(server_addr))==SOCKET_ERROR){
		ErrorHandling("bind() error!!!");
		return -1;
	}
	else {
		Sleep(2000);
		printf("Bind done!\n");
	}
	
	//listen 함수를 통해 서버소켓 완성, 어떤 컴퓨터로부터 요청이 와도 수락할 수 있게 대기상태 
	if(listen(server_socket,CLNT_MAX)==SOCKET_ERROR){
		ErrorHandling("listen() error!!!");
		return -1;
	}
	else {
		Sleep(2000);
		printf("Waiting for incoming connections...\n");
	}
	
	while(1){
		size_client_addr=sizeof(client_addr);
		//클라이언트의 견결요청을 수락하기 위해 accept함수 호출
		client_socket=accept(server_socket,(SOCKADDR*)&client_addr,&size_client_addr);
		if(client_socket==INVALID_SOCKET){
			ErrorHandling("accept() error!!!");
			return -1; 
		}
	
		pthread_mutex_lock(&g_mutex);
		g_client_socket[g_client_count++]=client_socket;
		pthread_mutex_unlock(&g_mutex);
		//쓰레드생성 
		pthread_create(&t_thread, NULL, handle_client, (void *)client_socket);
		pthread_detach(t_thread);
		printf("Connected client IP : %s\n",inet_ntoa(client_addr.sin_addr));
	}
	/*
	if((retval = recv(client_socket, msg, BUFSIZE, 0)) == SOCKET_ERROR){
		printf("recv() fail!!!");
		return -1;
	}
	else{ //client에서 받아온 문자열출력 
		while(1){
			retval = recv(client_socket, msg, BUFSIZE, 0);
			if(retval==-1){
				printf("client[%d] close\n",client_socket);
				send_all_client(msg,client_socket);
				break;
			}
		}
		msg[retval]='\0';
		puts(msg);
	}
	*/
	closesocket(client_socket);
	closesocket(server_socket);
	
	//프로그램을 종료하기 전에 초기화한 소켓 라이브러리 해제
	WSACleanup(); 
	
	printf("서버를 종료합니다.\n");
		
	return 0;
}


