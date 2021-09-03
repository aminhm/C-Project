/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

int connect_to_server(int argc,char ** argv);