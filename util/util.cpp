//
// Created by anil on 15/8/17.
//

#include "util.h"
#include "helper.h"
#include <cstring>
#include <array>
#include <sstream>
#include <regex>
#include <fstream>

bool sendString(int conFd_, const char *charArray_, size_t len_)
{
  size_t totalBytesToSend = ((len_ == 0) ? strlen(charArray_) : len_);
  long int sentBytes = 0;

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

void runSystemCmd(const std::string& cmd_, std::string& outPut_)
{
  std::ostringstream os;
  std::array<char, uint128> buffer{};
  FILE* pipe = popen(cmd_.data(), "r");
  if (!static_cast<bool>(pipe)) throw std::runtime_error("popen() failed!");

  while (!static_cast<bool>(feof(pipe)))
  {
    if (fgets(buffer.data(), uint128, pipe) != nullptr)
    {
      os << buffer.data();
    }
  }
  outPut_.append(os.str());
}

void assignLinks(const std::string &str_, const std::regex &token_, std::string &updatedStr_,
                 const std::string &relativePath_)
{
  std::ostringstream os;
  std::sregex_token_iterator itr (str_.cbegin(), str_.cend(), token_, -1);
  std::sregex_token_iterator itrEnd;

  for (; itr != itrEnd; ++itr)
  {
    std::string tmpStr = *itr;
    replaceSubString(tmpStr, THIS_DIR, EMPTY_STR);
    os << "<br><a href=\"" << tmpStr << "\">" << tmpStr << "</a></br>";
  }
  updatedStr_ = os.str();
}

void getFileContentInString(const std::string& path_, std::string& content_)
{
  std::ifstream file(trimString(path_), std::ios::in);
  if (file.good())
  {
    file.seekg(0, file.end);
    auto fileLength = static_cast<size_t>(file.tellg());
    content_.resize(fileLength);
    file.seekg(0); //important to reset to start here
    file.read(&content_[0], fileLength);
  }
  else
  {
    std::cerr << "Couldn't not open the file: " << path_ << std::endl;
  }

  file.close();
}

void sendContent(int conFd_, const std::string &path_)
{
  std::string content;

  if (isDir(path_))
  {
    std::string tmpContent;
    runSystemCmd(std::string("cd " + path_ + " && ls -d1 */ && cd ../"), tmpContent);
    runSystemCmd(std::string("cd " + path_ + " && find . -maxdepth 1 -type f && cd ../"), tmpContent);
    assignLinks(tmpContent, std::regex("\n"), content, path_);
  }
  else if(isRegFile(path_))
  {
    getFileContentInString(path_, content);
  }
  else
  {
    std::cerr << "Neither a dir nor a regular file at " << path_ << std::endl;
    sendMsg(conFd_, ERROR_MSG);
    return;
  }

  sendMsg(conFd_, content.data());
}

bool isDir(const std::string& path_)
{
  std::string out;
  runSystemCmd("file " + path_, out);
  return (out.find(": directory") != std::string::npos);
}

bool isRegFile(const std::string& path_)
{
  std::string out;
  runSystemCmd("file " + path_, out);
  return (out.find("ASCII text") != std::string::npos);
}

std::string trimString(const std::string &str_)
{
  size_t firstMatch = str_.find_first_not_of(WHITE_SPACE);
  if (firstMatch == std::string::npos)
  {
    return EMPTY_STR;
  }

  size_t lastMatch = str_.find_last_not_of(WHITE_SPACE);
  return str_.substr(firstMatch, (lastMatch-firstMatch+1));
}

void sendMsg(int fd_, const char *msg_)
{
  sendString(fd_, TINY_WEB);
  sendString(fd_, BODY_OPEN);
  sendString(fd_, msg_);
  sendString(fd_, BODY_CLOSE);
}