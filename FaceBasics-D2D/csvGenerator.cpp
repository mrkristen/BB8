#include"csvGenerator.h"

using namespace std;

bool csv_handler::createCsv(string name)
{
	bool status = csv.LoadFile("faces.csv");

	if (status == false)
	{
		isExist = false;
		Directory D;
		D.SetDirectory("faces");
		int i = 0;
		int label = 0;


		csv.put_HasColumnNames(false);

		WIN32_FIND_DATAA ffdf;
		CHAR szDirf[MAX_PATH];
		HANDLE hFindf = INVALID_HANDLE_VALUE;


		GetCurrentDirectoryA(MAX_PATH, szDirf);

		strcat(szDirf, "\\*");

		hFindf = FindFirstFileA(szDirf, &ffdf);

		do
		{

			string folder(ffdf.cFileName);

			if ((folder.find('.') != std::string::npos) || (folder.find("..") != std::string::npos))
				continue;


			Directory DF;

			DF.SetDirectory(folder);

			WIN32_FIND_DATAA ffd;
			CHAR szDir[MAX_PATH];
			HANDLE hFind = INVALID_HANDLE_VALUE;

			CHAR clabel[10];
			itoa(label, clabel, 10);
			label++;

			CHAR Buffer[MAX_PATH];
			GetCurrentDirectoryA(MAX_PATH, Buffer);

			strcpy(szDir, Buffer);
			strcat(szDir, "\\*");

			hFind = FindFirstFileA(szDir, &ffd);

			do
			{
				string path(Buffer);
				string brace("\\");
				string file(ffd.cFileName);

				if (file.find(".jpg") != std::string::npos)
				{
					brace += file;
					path += brace;

					csv.SetCell(i, 0, clabel);
					csv.SetCell(i, 1, folder.c_str());
					csv.SetCell(i, 2, path.c_str());


					i++;
				}

			} while (FindNextFileA(hFind, &ffd) != 0);



		} while (FindNextFileA(hFindf, &ffdf) != 0);




		D.End();
		return csv.SaveFile("faces.csv");
	}

	else
	{
		isExist = true;
		return UpdateCsv(name);
	}
}

bool csv_handler::UpdateCsv(string folder)
{
	csv.put_HasColumnNames(false);

	int nrows = csv.get_NumRows();

	string chlabel(csv.getCell(nrows-1, 0));
	int label = atoi(chlabel.c_str()) + 1;

	Directory D;
	D.SetDirectory("faces");

		Directory DF;

		DF.SetDirectory(folder);

		WIN32_FIND_DATAA ffd;
		CHAR szDir[MAX_PATH];
		HANDLE hFind = INVALID_HANDLE_VALUE;

		CHAR clabel[10];
		itoa(label, clabel, 10);
		label++;

		CHAR Buffer[MAX_PATH];
		GetCurrentDirectoryA(MAX_PATH, Buffer);

		strcpy(szDir, Buffer);
		strcat(szDir, "\\*");

		hFind = FindFirstFileA(szDir, &ffd);

		do
		{
			string path(Buffer);
			string brace("\\");
			string file(ffd.cFileName);

			if (file.find(".jpg") != std::string::npos)
			{
				brace += file;
				path += brace;

				csv.SetCell(nrows, 0, clabel);
				csv.SetCell(nrows, 1, folder.c_str());
				csv.SetCell(nrows, 2, path.c_str());


				nrows++;
			}

		} while (FindNextFileA(hFind, &ffd) != 0);


	D.End();
	return csv.SaveFile("faces.csv");
}

std::string csv_handler::findName(int label)
{
	
	bool status = csv.LoadFile("faces.csv");
	csv.put_HasColumnNames(false);

	if (status == false)
	{
		exit(-3);
	}
	else
	{
		for (int i = 0; i < csv.get_NumRows(); i++)
		{
			int clabel = atoi(csv.getCell(i, 0));
			
			if (clabel == label)
				return string (csv.getCell(i, 1));
		}

		return string("*");
	}
}

