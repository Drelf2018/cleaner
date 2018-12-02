#include <iostream>
#include <io.h>
#include <string>
using namespace std;
 
 
void dir(string path)
{
	long hFile = 0;
	struct _finddata_t fileInfo;
	string pathName, exdName;
 
 
	if ((hFile = _findfirst(pathName.assign(path).
		append("\\*").c_str(), &fileInfo)) == -1) {
		return;
	}
	do {
		if (fileInfo.attrib&_A_SUBDIR) {
			string fname = string(fileInfo.name);
			if (fname != ".." && fname != ".") {
				dir(path + "\\" + fname);
			} 
		} else {
			cout << path << "\\" << fileInfo.name << endl;
		}
	} while (_findnext(hFile, &fileInfo) == 0);
	_findclose(hFile);
	return;
}
 
 
int main()
{
	string path=".";
	dir(path);
	return 0;
}
