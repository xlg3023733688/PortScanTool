#include "PortScanTool.h"

int main(int argc,char* argv[])
{
    if(argc<=4)
    {//输入提示
        inputMessage();
        exit(-1);
    }
    //数据提取
    char* start_ip = argv[1];
    char* end_ip = argv[2];
    char* port_num = argv[4];
    //数据检测
    checkData(start_ip,end_ip,port_num);
    //开始扫描(单线程)
    for(uint32_t i = ntohl(start_ip_addr.s_addr);i<=ntohl(end_ip_addr.s_addr);i++)
    {//遍历各各地址
        scan(i,atoi(port_num));
    }   
    return 0;
}