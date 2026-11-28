#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string>
using namespace std;
int main(){
    string host="127.0.0.1";
    int fd=socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in hostaddr{};
    hostaddr.sin_family=AF_INET;
    hostaddr,sin_port=htons(12000);
    inet_pton(AF_INET,host.c_str(),&hostaddr);
    connect(fd,(sockaddr*)&hostaddr,sizeof(hostaddr));
    string mess="HELLO";
    ssize_t sendn=0;
    while(sendn<mess.len()){
        ssize_t m=send(fd,mess.c_str()+sendn,mess.len()-sendn,0);
        if(m<=0) break;
        sendn+=m;
    }
    if(sendn!=mess.len()){
        exit(1);
    }
    char buffer[2048];
    ssize_t total=0;
    while(true){
        ssize_t n=recv(fd,buffer+total,sizeof(buffer)-total,0);
        if(n>0) total+=n;
        else if(n==0) break;
        else exit(1);
    }
    cout.write(buffer,total);
    cout<<endl;
    return 0;
}