/*
*   文件名称：socket_server.cpp
*   创 建 者：bailiyang
*   创建日期：2018年08月31日
*/

#include <iostream>
#include <errno.h>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
  int listenfd = socket(AF_INET, SOCK_STREAM, 0); 
  if (listenfd < 0)
    printf("socket fail with errno %d\n", errno);
  
  struct sockaddr_in addr;
  bzero(&addr, sizeof(sockaddr_in));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  addr.sin_port = htons(8888);

  if (bind(listenfd, (sockaddr *)&addr, sizeof(struct sockaddr)) < 0)
    printf("bind fail with errno %d\n", errno);
  
  listen(listenfd, 10);
  fork();
  printf("%d server start\n", getpid());
  for(;;)
  {
    struct sockaddr_in conn_addr;
    socklen_t addr_len = sizeof(sockaddr);
    printf("%d start accept\n", getpid());
    int connfd = accept(listenfd, (sockaddr *)&conn_addr, &addr_len);
    printf("%d accept over\n", getpid());
    if (connfd < 0)
    {
      printf("accept connect fail, with errno %d\n", errno);
      continue;
    }

    std::string conn_addr_str = inet_ntoa(conn_addr.sin_addr);
    printf("recv connect from fd %d, and ip %s\n", connfd, conn_addr_str.c_str());

    char buff[256] = "Hello World";
    if (write(connfd, buff, strlen(buff)) < 0)
      printf("write fail with errno %d\n", errno);
    close(connfd);
  }

  return 0;
}
