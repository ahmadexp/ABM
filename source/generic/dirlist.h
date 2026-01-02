const int maxdirentrys = 500;
class direntry{
	public:
		char filename[256];
		bool folder;
		int extrainfoint;
		direntry(char* filename2);};
direntry::direntry(char* filename2){
	sprintf(filename,"%s",filename2);
	folder=0;
	extrainfoint=0;}
direntry *direntrys[maxdirentrys];
int n_direntrys = 0;

void deletedirentry(int number){
	delete direntrys[number];
	direntrys[number]=NULL;
	if(number<n_direntrys-1)for(int a=number;a<n_direntrys;a++)direntrys[a]=direntrys[a+1];
	direntrys[n_direntrys-1]=NULL;
	n_direntrys=n_direntrys-1;
}

#ifdef _WIN32
#include <windows.h>
#else
#include <dirent.h>
#include <sys/stat.h>
#endif
#ifndef MAX_PATH
#define MAX_PATH 256
#endif

void dirlist(char* directory){
	while(n_direntrys)deletedirentry(0);
	
	std::string path = directory;
	// Handle Windows-style wildcard paths e.g. "foo/*" -> "foo"
	size_t wildcard = path.find('*');
	if (wildcard != std::string::npos) {
		size_t slash = path.rfind('/');
		if (slash != std::string::npos) path = path.substr(0, slash);
		else path = ".";
	}
	// Fallback check if it ends in slash (pure dir)
	
#ifdef _WIN32
	WIN32_FIND_DATAA findData;
	std::string searchPath = path + "\\*";
	HANDLE hFind = FindFirstFileA(searchPath.c_str(), &findData);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0) continue;
			
			direntrys[n_direntrys] = new direntry(findData.cFileName);
			if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) direntrys[n_direntrys]->folder = 1;
			n_direntrys++;
		} while (FindNextFileA(hFind, &findData) && n_direntrys < maxdirentrys);
		FindClose(hFind);
	}
#else
	DIR *d = opendir(path.c_str());
	if (d) {
		struct dirent *dir;
		while ((dir = readdir(d)) != NULL) {
			if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) continue;
			
			direntrys[n_direntrys] = new direntry(dir->d_name);
			if (dir->d_type == DT_DIR) direntrys[n_direntrys]->folder = 1;
			n_direntrys++;
			if(n_direntrys >= maxdirentrys) break;
		}
		closedir(d);
	}
#endif
}
