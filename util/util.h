//
// Created by anil on 13/8/17.
//

#ifndef CPPSERVER_UTIL_H
#define CPPSERVER_UTIL_H

#include <iostream>

// rotates the characters of the char array by 13 letters
void rot13(char* str_, unsigned int charLen_);

// sends the char* charArry_ to conFd_
bool sendString(int conFd_, const char* charArray_, ssize_t len_ = 0);

// runs the cmd and stores output in outPut_
void runSystemCmd(const std::string& cmd_, std::string& outPut_);

// send standard/normal response to conFd_
void sendNormalResponse(int conFd_);

// replaces substring match_ of source_ by replacement_
void replaceSubString(std::string& source_, const std::string& match_, const std::string& replacement_);

// sends the list of files to conFd_
void sendFileList(int conFd_, const std::string& path_);

// is it a directory
bool isDir(const std::string& path_);

// is it a regular file
bool isRegFile(const std::string& path_);

// get file's content in a string
void getFileContentInString(const std::string& path_, std::string& content_);

#endif //CPPSERVER_UTIL_H
