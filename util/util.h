//
// Created by anil on 13/8/17.
//

#pragma once

#include <iostream>
#include <unistd.h>

// sends the char* charArry_ to conFd_
bool sendString(int conFd_, const char *charArray_, size_t len_ = 0);

// runs the cmd and stores output in outPut_
// this should not be needed once the compiler starts supporting std::filesystem
void runSystemCmd(const std::string& cmd_, std::string& outPut_);

// replaces all substrings match_ of source_ by replacement_
void replaceSubString(std::string& source_, const std::string& match_, const std::string& replacement_);

// sends the list of files to conFd_
void sendContent(int conFd_, const std::string &path_);

// is it a directory
bool isDir(const std::string& path_);

// is it a regular file
bool isRegFile(const std::string& path_);

// get file's content in a string
void getFileContentInString(const std::string& path_, std::string& content_);

std::string trimString(const std::string &str_);

// send msg_ to fd_
void sendMsg(int fd_, const char *msg_);
