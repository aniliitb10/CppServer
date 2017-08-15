#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include "../../../util/util.h"
#include "../../../util/helper.h"

int main(int argc_, char ** argv_)
{
  const int sock = socket(AF_INET, SOCK_STREAM, 0);
  sockaddr_in server, client;
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port = htons(SERVER_PORT);

  bind(sock, (struct sockaddr* ) &server, sizeof(server));
  const unsigned int clientLen = sizeof(client);
  listen(sock, 5);

  char buffer[MAX_CHAR_LEN];
  ssize_t charReceived;

  for (unsigned int index = 0; index < MAX_LOOP_COUNT; ++index)
  {
    std::cout << "Waiting for connection" << std::endl;
    int acceptFd = accept(sock, (struct sockaddr*) &client, (socklen_t*) &clientLen);
    std::cout << "Got connection number: " << (index + 1) << std::endl;

    sendString(acceptFd, OK);
    sendString(acceptFd, SERVER);

    if ((charReceived = read(acceptFd, buffer, MAX_CHAR_LEN)) > 0)
    {
      // sendNormalResponse(acceptFd);
      char* url = strstr(buffer, "HTTP");
      if (url)
      {
        *url = 0;
        url = NULL;
      }
      else
      {
        std::cout << "Error, doesn't look like a valid request!" << std::endl;
      }

      //assuming that it is a GET request
      buffer[3] = '.';
      const std::string filePath (((char*) buffer) + 3);

      std::cout << "requested filePath: " << filePath << std::endl;

      sendFileList(acceptFd, filePath);
    }

    close(acceptFd);
  }
}