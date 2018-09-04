/*
*   文件名称：socket_test.cpp
*   创 建 者：bailiyang
*   创建日期：2018年08月31日
*/

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
  int socketfd = socket(AF_INET, SOCK_STREAM, 0); 
  if (socketfd < 0)
    printf("socket fail with errno %d\n", errno);
  
  struct sockaddr_in addr;
  bzero(&addr, sizeof(sockaddr_in));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8888);
  if (inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) < 0)
    printf("inet_pton fail with errno %d\n", errno);
  if (connect(socketfd, (sockaddr *)&addr, sizeof(sockaddr)) < 0)
    printf("connect fail with errno %d\n", errno);

  printf("connect success\n");
  
  char buff[256];
  while(read(socketfd, buff, sizeof(buff)) > 0)
  {
    printf("recv str %s\n", buff);
  }
  
  close(socketfd);

  return 0;
}
