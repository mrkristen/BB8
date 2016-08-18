#pragma once


#include <iostream>
#include <Windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>

#include <CkCsv.h>
#include"Directory.h"

class csv_handler
{
	CkCsv csv;
	bool UpdateCsv(std::string name);
	
public:
	static bool isExist;
	bool createCsv(std::string name);
	std::string findName(int label);

};