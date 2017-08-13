//
// Created by anil on 13/8/17.
//

#include "util.h"

void rot13(unsigned char* str_, unsigned int charLen_)
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