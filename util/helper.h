//
// Created by anil on 15/8/17.
//

#ifndef CPPSERVER_HELPER_H
#define CPPSERVER_HELPER_H

constexpr unsigned short int SERVER_PORT = 1800;
constexpr unsigned short int MAX_CHAR_LEN = 1024;
constexpr unsigned short int MAX_LOOP_COUNT = 100;
constexpr int ERROR_CODE = -1;
constexpr unsigned int uint128 = 128;

static const char* OK = "HTTP/1.0 200 OK\r\n";
static const char* SERVER = "Server: Tiny Web Server\r\n\r\n";
static const char* TINY_WEB = "<html><head><title>Anil's tiny web server</title></head>";
static const char* BODY_OPEN = "<body><p>";
static const char* BODY_CLOSE = "</p></body></html>\r\n";
static const char* WELCOME_MSG = "Welcome to Anil's server";

static const std::string EMPTY_STR = "";

#endif //CPPSERVER_HELPER_H
