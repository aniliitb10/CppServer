#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include "../../../util/util.h"
#include "../../../util/helper.h"

int main(int argc_, char ** argv_)
{
  sockaddr_in server{}, client{};
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port = htons(SERVER_PORT);

  const int sock = socket(AF_INET, SOCK_STREAM, 0);
  bind(sock, (struct sockaddr* ) &server, sizeof(server));
  const unsigned int clientLen = sizeof(client);

  if (listen(sock, MAX_REQ_TO_LISTEN) == ERROR_CODE)
  {
    std::cerr << "There was some problem in listening on socket" << std::endl;
    return ERROR_CODE;
  }

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
      char* url = strstr(buffer, "HTTP");
      if (static_cast<bool>(url))
      {
        *url = 0;
        url = nullptr;
      }
      else
      {
        std::cerr << "Error, doesn't look like a valid request!" << std::endl;
        continue;
      }

      // assuming that it is a GET request
      buffer[3] = '.';
      const std::string filePath (((char*) buffer) + 3);

      sendContent(acceptFd, trimString(filePath));
    }

    close(acceptFd);
  }
}