#ifndef _STD_INC                   
#define _STD_INC



//#define IPCDELECATOR_OS_WIN

#define IPCDELECATOR_OS_LINUX

#define IPCDELECATOR_MODE_MESSAGEQUE


#include <stdio.h>
#include <string.h>

#ifdef IPCDELECATOR_OS_LINUX
#include <stdlib.h>
#endif

#ifdef IPCDELECATOR_OS_WIN
#include <Windows.h>
#include <tchar.h>
#endif		

#endif
