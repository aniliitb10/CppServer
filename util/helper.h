//
// Created by anil on 15/8/17.
//

#pragma once

constexpr unsigned short int SERVER_PORT = 1800;
constexpr unsigned short int MAX_CHAR_LEN = 1024;
constexpr unsigned short int MAX_LOOP_COUNT = 100;
constexpr int ERROR_CODE = -1;
constexpr unsigned int uint128 = 128;
constexpr int int1024 = 1024;
constexpr unsigned int MAX_REQ_TO_LISTEN = 5;

static const char* OK = "HTTP/1.0 200 OK\r\n";
static const char* SERVER = "Server: Tiny Web Server\r\n\r\n";
static const char* TINY_WEB = "<html><head><title>Anil's tiny web server</title></head>";
static const char* BODY_OPEN = "<body><p>";
static const char* BODY_CLOSE = "</p></body></html>\r\n";
static const char* WELCOME_MSG = "Welcome to Anil's server";
static const char* ERROR_MSG = "404: Either file not found or format is not supported.";

static const std::string EMPTY_STR = "";
static const std::string THIS_DIR = "./";
static const std::string F_SLASH = "/";
static const std::string WHITE_SPACE = " ";
static const std::string DOT_STR = ".";
