#include"Directory.h"

Directory::Directory()
{
	this->saveCurrentDirectory();
}

Directory::~Directory()
{
	this->End();
}
void Directory::saveCurrentDirectory()
{
	dwRet = GetCurrentDirectoryA(BUFSIZE, Buffer);
	if (dwRet == 0)
	{
		exit(0);
	}
	if (dwRet > BUFSIZE)
	{
		exit(0);
	}
}


void Directory::createDirectory(std::string dir)
{
	CreateDirectoryA(dir.c_str(), NULL);
	SetCurrentDirectoryA(dir.c_str());
}

void Directory::End()
{
	SetCurrentDirectoryA(Buffer);
}


void Directory::SetDirectory(std::string Buffer)
{
	SetCurrentDirectoryA(Buffer.c_str());
}
