#pragma once

#include "stdafx.h"
#include <strsafe.h>
#include "resource.h"

#include <time.h> 

#include"FaceBasics.h"
#include"Audio.h"

class Application:virtual public CFaceBasics, virtual public CAudioBasics
{
private:
	HWND &m_appHWnd;

public:
	Application();

    int Run(HINSTANCE hInstance, int nCmdShow);
	static LRESULT CALLBACK  MessageRouter(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK       DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

};
