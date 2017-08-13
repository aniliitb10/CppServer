#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include "../../../util/util.h"

constexpr unsigned short int SERVER_PORT = 1800;
constexpr unsigned short int MAX_CHAR_LEN = 1024;
constexpr unsigned short int MAX_LOOP_COUNT = 100;

int main()
{
  const int sock = socket(AF_INET, SOCK_STREAM, 0);
  sockaddr_in server, client;
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port = htons(SERVER_PORT);

  bind(sock, (struct sockaddr* ) &server, sizeof(server));
  const unsigned int clientLen = sizeof(client);
  listen(sock, 5);

  unsigned char buffer[MAX_CHAR_LEN];
  int charReceived;

  for (unsigned short int index = 0; index < MAX_LOOP_COUNT; ++index)
  {
    std::cout << "Waiting for connection" << std::endl;
    int acceptFd = accept(sock, (struct sockaddr*) &client, (socklen_t*) &clientLen);
    std::cout << "Got connection" << std::endl;
    
    while ((charReceived = read(acceptFd, buffer, MAX_CHAR_LEN)) > 0)
    {
      std::cout << "Received string:\n" << std::string((const char*)buffer, charReceived) << std::endl;
      rot13(buffer, charReceived);
      write(acceptFd, buffer, charReceived);
    }
  }

  return 0;
}