//
// Created by anil on 15/8/17.
//

#include "util.h"
#include "helper.h"
#include <cstring>
#include <unistd.h>
#include <array>
#include <sstream>
#include <regex>
#include <fstream>

void rot13(char* str_, unsigned int charLen_)
{
  int charInt;
  for (unsigned int index = 0; index < charLen_; ++index)
  {
    if (str_[index] >= 'A' && str_[index] <= 'Z')
    {
      charInt = str_[index] - 'A';
      charInt += 13;
      charInt %= 26;
      str_[index] = 'A' + charInt;
    }
    else if (str_[index] >= 'a' && str_[index] <= 'z')
    {
      charInt = str_[index] - 'a';
      charInt += 13;
      charInt %= 26;
      str_[index] = 'a' + charInt;
    }
    // else leave it as it was
  }
}

bool sendString(int conFd_, const char* charArray_, ssize_t len_)
{
  ssize_t totalBytesToSend = ((len_ == 0) ? strlen(charArray_) : len_);
  ssize_t sentBytes = 0;

  while (totalBytesToSend > 0)
  {
    sentBytes = write(conFd_, charArray_, totalBytesToSend);

    if (sentBytes == ERROR_CODE)
    {
      return false;
    }

    totalBytesToSend -= sentBytes;
    charArray_ += sentBytes;
  }

  return true;
}

void replaceSubString(std::string& source_, const std::string& match_, const std::string& replacement_)
{
  size_t pos = 0;
  while ((pos = source_.find(match_, pos)) != std::string::npos)
  {
    source_.replace(pos, match_.length(), replacement_);
    pos += replacement_.length();
  }
}

void sendNormalResponse(int conFd_)
{
  sendString(conFd_, TINY_WEB);
  sendString(conFd_, BODY_OPEN);
  sendString(conFd_, WELCOME_MSG);
  sendString(conFd_, BODY_CLOSE);
}

void runSystemCmd(const std::string& cmd_, std::string& outPut_)
{
  std::ostringstream os;
  std::array<char, uint128> buffer;
  FILE* pipe = popen(cmd_.data(), "r");
  if (!pipe) throw std::runtime_error("popen() failed!");

  while (!feof(pipe))
  {
    if (fgets(buffer.data(), uint128, pipe) != nullptr)
    {
      os << buffer.data();
    }
  }
  outPut_ = os.str();
}

void tokenize(const std::string& str_, const std::regex& token_, std::string& updatedStr_)
{
  // <a href=".">Link to this folder</a>
  std::ostringstream os;
  std::sregex_token_iterator itr (str_.cbegin(), str_.cend(), token_, -1);
  std::sregex_token_iterator itrEnd;

  for (; itr != itrEnd; ++itr)
  {
    os << "<br><a href=\"./" << *itr <<  "\">" << *itr << "</a></br>";
  }
  updatedStr_ = os.str();
}

void getFileContentInString(const std::string& path_, std::string& content_)
{
  std::ifstream file(path_);

  if (file.good())
  {
    file.seekg(0, file.end);
    size_t fileLength = static_cast<size_t>(file.tellg());
    content_.resize(fileLength);
    file.seekg(0); //important to reset to start here
    file.read(&content_[0], fileLength);
  }
  else
  {
    std::cout << "There was some problem in opening the file: " << path_ << std::endl;
  }

  file.close();
}

void sendFileList(int conFd_, const std::string& path_)
{
  std::string content;
  if (isDir(path_))
  {
    runSystemCmd(std::string("cd " + path_ + " && ls -1"), content);  
  }
  else if(isRegFile(path_))
  {
    getFileContentInString(path_, content);
  }
  else
  {
    std::cout << "Neither a dir nor a regular file at " << path_ << std::endl;
  }

  std::string formattedStr;
  tokenize(content, std::regex("\n"), formattedStr);

  sendString(conFd_, TINY_WEB);
  sendString(conFd_, BODY_OPEN);
  sendString(conFd_, formattedStr.data());
  sendString(conFd_, BODY_CLOSE);
}

bool isDir(const std::string& path_)
{
  std::string out;
  runSystemCmd("file " + path_, out);
  std::cout << out << std::endl;
  return (out.find(": directory") != std::string::npos);
}

bool isRegFile(const std::string& path_)
{
  std::string out;
  runSystemCmd("file " + path_, out);
  std::cout << out << std::endl;
  return (out.find(": ASCII text") != std::string::npos);
}