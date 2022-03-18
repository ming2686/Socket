#ifndef _common_h
#define _common_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <pthread.h>
#include <unistd.h>
#define DEFAULT_PORT 9090
#define MY_LOCAL_IP "192.168.0.53"

#define BUFSIZE 512
#define CLNT_MAX 10

extern int g_client_socket[CLNT_MAX]; //client´Â 10¸í
extern int g_client_count;
extern pthread_mutex_t g_mutex;

void *handle_client(void* arg);
void send_msg(char *msg, int len);

void ErrorHandling(char* message);

#endif
