#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string>
using namespace std;
#define MAX_BACKLOG 128
int main(){
    //create socket
    string host_ip="127.0.0.1";
    int welcomfd=socket(AF_INET,SOCK_STREAM,0);
    // bind socket
    sockaddr_in addr{};
    addr.sin_family=AF_INET;
    addr.sin_port=htons(12000);
    inet_pton(AF_INET,host_ip.c_str(),&addr.sin_addr);
    //listen
    bind(welcomfd,(sockaddr*)&addr,sizeof(addr));
    listen(welcomfd,MAX_BACKLOG);
    cout<<"listening port 12000......"<<endl;
    //accept
    while(true){
        sockaddr_in client_addr{};
        socklen_t len=sizeof(client_addr);
        int confd=accept(welcomfd,(sockaddr*)&client_addr,&len);
        char buffer[2048];
        ssize_t total=0;
        while(true){
            ssize_t n=recv(confd,buffer+total,sizeof(buffer)-total,0);
            if(n>0) total+=n;
            else if(n==0) break;
            else{
                exit(1);
            }
        }
        cout<<"recieved"<<endl;
        cout.write(buffer,total);
        cout<<endl;
        cout<<"begin send"<<endl;
        ssize_t sendn=0;
        while(sendn<total){
            ssize_t m=send(confd,buffer+sendn,total-sendn,0);
            if(m>0) sendn+=m;
            if(m<=0) break;
        }
        if(sendn!=total) break;
        close(confd);
    }
    close(welcomfd);
    return 0;
}