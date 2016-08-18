#pragma once


#include <windows.h> 
#include <stdio.h>
#include <tchar.h>
#include<iostream>

#define BUFSIZE MAX_PATH

class Directory
{
	CHAR Buffer[MAX_PATH];
	DWORD dwRet;

public:
	void saveCurrentDirectory();
	void createDirectory(std::string dir);
	void SetDirectory(std::string Buffer);
	void End();
	Directory();
	~Directory();
};
