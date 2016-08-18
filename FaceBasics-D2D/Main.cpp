#include"Application.h"



int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	if (SUCCEEDED(hr))
	{
		{
			Application app;
			app.Run(hInstance, nCmdShow);
		}

		CoUninitialize();
	}

	return EXIT_SUCCESS;

}