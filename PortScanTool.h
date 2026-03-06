#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

//参数声明
extern struct in_addr start_ip_addr,end_ip_addr;//存放ip地址，便于转换

//函数声明
void wrongMessage(const char* s);
void inputMessage();
void checkData(const char* start_ip,const char* end_ip,const char* port_num);
void scan(uint32_t ip,int port);
void portExists(struct sockaddr_in* object);
void portUnexists(struct sockaddr_in* object);
int createSock(uint32_t ip,int port);
bool linkHost(int listen_fd,struct sockaddr_in* object);
struct sockaddr_in* initObject(uint32_t ip,int port);
void destroyObject(struct sockaddr_in* object);
