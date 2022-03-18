#ifndef _common_h
#define _common_h
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <pthread.h>
#include <unistd.h>
#define DEFAULT_PORT 9090
#define MY_LOCAL_IP "192.168.0.53"
#define BUFSIZE 512
#define NAMESIZE 20

void *send_msg(void *arg);
void *recv_msg(void *arg);

extern char name[NAMESIZE];
extern char msg[BUFSIZE];

void ErrorHandling(char* message);

#endif
