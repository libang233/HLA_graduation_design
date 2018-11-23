#ifndef SOCKETCONFIG_H_
#define SOCKETCONFIG_H_

#include <stdio.h>
#include <tchar.h>
#include<WINSOCK2.H>
#include "windows.h"

#include<string>

#include<iostream>
#include<cstring>
using namespace std;
#pragma comment(lib, "ws2_32.lib")


extern SOCKET socketSclient;

void socketInit();

void socketClose();

#endif // SOCKETCONFIG_H_