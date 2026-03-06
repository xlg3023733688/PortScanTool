#include "PortScanTool.h"

//参数定义
struct in_addr start_ip_addr,end_ip_addr;

//函数定义
void wrongMessage(const char* s)
{
    std::cout<<s<<"错误!\n";
    exit(-1);
}

void inputMessage()
{//输入提示
    //./main start_ip end_ip -p port_num
    std::cout<<"输入提示:./main start_ip end_ip -p port_num\n";
}

void checkData(const char* start_ip,const char* end_ip,const char* port_num)
{//数据检测
    //端口是否合格
    int port_begin = 1,port_end = 65535,port=atoi(port_num);
    if(port < port_begin || port > port_end) 
    {
        std::cout<<"扫描的端口号不合格(port:1~65535)!"<<std::endl;
        exit(-1);
    }
    //ip地址是否合格
    int ret1 = inet_pton(AF_INET,start_ip,&start_ip_addr);
    int ret2 = inet_pton(AF_INET,end_ip,&end_ip_addr);
    if(ret1==0||ret2==0)
    {//格式错误
        std::cout<<"输入的ip地址格式错误!\n";
        exit(-1);
    }
    else if(ret1==-1||ret2==-1)
    {//参数错误
        std::cout<<"inet_pton参数错误!\n";
        exit(-1);
    }
    //转换成整形
    uint32_t s = ntohl(start_ip_addr.s_addr);
    uint32_t e = ntohl(end_ip_addr.s_addr);
    if(e<s)
    {
        std::cout<<"输入ip地址顺序不对(低地址~高地址)!\n";
        exit(-1);
    }
    std::cout<<"参数合法,正在进入下一步!\n";
}

int createSock(uint32_t ip,int port)
{
    int listen_fd  = socket(AF_INET,SOCK_STREAM,0);
    if(listen_fd==-1)
    {
        wrongMessage("socket");
    }
    return listen_fd;
}

struct sockaddr_in* initObject(uint32_t ip,int port)
{
    struct sockaddr_in* object = new struct sockaddr_in;
    object->sin_port=htons(port);
    object->sin_family=AF_INET;
    object->sin_addr.s_addr=htonl(ip);
    return object;
}

void destroyObject(struct sockaddr_in* object)
{
    delete object;
}

bool linkHost(int listen_fd,struct sockaddr_in* object)
{//连接主机
    if(connect(listen_fd,(struct sockaddr*)object,sizeof(*object))==-1)
    {
        return false;
    }
    //连接成功
    return true;
}

void portExists(struct sockaddr_in* object)
{//端口存在
    std::cout<<"ip:"<<inet_ntoa(object->sin_addr)<<"的"<<ntohs(object->sin_port)<<"号端口存在服务!\n";
}

void portUnexists(struct sockaddr_in* object)
{//端口不存在
    std::cout<<"ip:"<<inet_ntoa(object->sin_addr)<<"的"<<ntohs(object->sin_port)<<"号端口不存在服务!\n";
}

void scan(uint32_t ip,int port)
{//扫描
    int listen_fd = createSock(ip,port);//套接字
    struct sockaddr_in* object = initObject(ip,port);//目标主机信息
    //开始扫描
    if(linkHost(listen_fd,object))
    {
        portExists(object);
    }
    else
    {
        portUnexists(object);
    }
    destroyObject(object);//清理内存
}