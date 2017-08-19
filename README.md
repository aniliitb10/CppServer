# CppServer
A simple server in C++.

This server just lists the content of current directory.
In the displayed list:
1) If clicked on a regualr file, it displays the file.
2) If clicked on a directory, it displays its content.

It is hardcoded to listen on port 1800 (helper.h) but if it doesn't listen on port 1800, please run:

lsof -i
  
or
  
lsof -i | grep CppServer

to get the port number it is listening on.
