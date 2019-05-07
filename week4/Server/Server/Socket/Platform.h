#ifndef PLATFORM_H
#define PLATFORM_H

#pragma comment(lib,"ws2_32.lib")
#include "winsock2.h"
#include "Ws2tcpip.h"
extern WSADATA g_wsadata;
#define CloseSocket closesocket
#define GetSocketError WSAGetLastError
#define StartSocketLib WSAStartup( MAKEWORD( 2, 2 ), &g_wsadata );
#define CloseSocketLib WSACleanup();

#ifndef socklen_t
typedef int socklen_t;

#endif

#endif
#pragma once