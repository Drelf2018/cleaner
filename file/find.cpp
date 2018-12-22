#include <io.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <map>
using namespace std;

map<string,string> mp;

void getFiles(string path, vector<string>& files)
{
    //文件句柄  
    long   hFile = 0;
    //文件信息  
    struct _finddata_t fileinfo;
    string p;
    if ((hFile = _findfirst(p.assign(path).append("/*").c_str(), &fileinfo)) != -1)
    {
        do
        {
            //如果是目录,迭代之  ,但我不需要 
            //如果不是,加入列表  
            if ((fileinfo.attrib &  _A_SUBDIR))
            {
                /*if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                    getFiles(p.assign(path).append("/").append(fileinfo.name), files);*/
            }
            else
            {
                files.push_back(p.assign(path).append("/").append(fileinfo.name));
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}

void init()
{
	int pos=0;
	string reader,pots,path;
	string::iterator it;
	ifstream fin("clean.inf");
	while(getline(fin,reader))
	{
		//mp[reader.ad()]=...
		pots=path=reader;
		
		/*it=pots.begin();
		while(reader[pos++]!='[');
		pots.erase(it+0,it+pos);
		while(reader[pos++]!='[');
		
		pos=0;*/
	}
}

int main()
{
	vector<string> files;
	getFiles(".",files);
	int size = files.size();
    for (int i = 0; i < size; i++)
    {
        cout<<files[i] << endl;
    }
    //mp["hehe"]="hehe2";
    //cout<<(mp["hehe"]=="")<<endl;
	return 0;
}
