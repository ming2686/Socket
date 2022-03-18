#include "common.h"
int g_client_socket[CLNT_MAX]; //client�� 10��
int g_client_count=0;
pthread_mutex_t g_mutex;//���ؽ� ���� 

int main(int argc, char** argv) {
	WSADATA wsadata;
	SOCKET server_socket, client_socket;
	SOCKADDR_IN server_addr, client_addr;
	pthread_t t_thread;
	
	int size_client_addr;
	char msg[BUFSIZE+1]; //�����͸� �޾ƿ� ���� 
	int retval;
		
	pthread_mutex_init(&g_mutex, NULL);

	//���� ���̺귯�� �ʱ�ȭ
	if(WSAStartup(MAKEWORD(2,2),&wsadata)!=0){
		ErrorHandling("WSAStartup() error!!!");
		return -1;
	}
	else{
		Sleep(2000);
		printf("WSAStartup completed!!\n");
	}
	
	//���ϻ��� 
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
	
	//IP�ּҿ� ��Ʈ��ȣ �Ҵ�, �����̶� ������ ������ ������
	if(bind(server_socket,(SOCKADDR*)&server_addr,sizeof(server_addr))==SOCKET_ERROR){
		ErrorHandling("bind() error!!!");
		return -1;
	}
	else {
		Sleep(2000);
		printf("Bind done!\n");
	}
	
	//listen �Լ��� ���� �������� �ϼ�, � ��ǻ�ͷκ��� ��û�� �͵� ������ �� �ְ� ������ 
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
		//Ŭ���̾�Ʈ�� �߰��û�� �����ϱ� ���� accept�Լ� ȣ��
		client_socket=accept(server_socket,(SOCKADDR*)&client_addr,&size_client_addr);
		if(client_socket==INVALID_SOCKET){
			ErrorHandling("accept() error!!!");
			return -1; 
		}
	
		pthread_mutex_lock(&g_mutex);
		g_client_socket[g_client_count++]=client_socket;
		pthread_mutex_unlock(&g_mutex);
		//��������� 
		pthread_create(&t_thread, NULL, handle_client, (void *)client_socket);
		pthread_detach(t_thread);
		printf("Connected client IP : %s\n",inet_ntoa(client_addr.sin_addr));
	}
	/*
	if((retval = recv(client_socket, msg, BUFSIZE, 0)) == SOCKET_ERROR){
		printf("recv() fail!!!");
		return -1;
	}
	else{ //client���� �޾ƿ� ���ڿ���� 
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
	
	//���α׷��� �����ϱ� ���� �ʱ�ȭ�� ���� ���̺귯�� ����
	WSACleanup(); 
	
	printf("������ �����մϴ�.\n");
		
	return 0;
}


