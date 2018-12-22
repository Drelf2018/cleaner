#include <io.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <map>
#include <windows.h>
using namespace std;

map<string,string> mp;

void getFiles(string path, vector<string>& files)
{
    long   hFile = 0;//�ļ����  
    struct _finddata_t fileinfo;//�ļ���Ϣ  
    string p;
    if ((hFile = _findfirst(p.assign(path).append("/*").c_str(), &fileinfo)) != -1)
    {
        do
        {
            //�����Ŀ¼,����֮  ,���Ҳ���Ҫ 
            //�������,�����б�  
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

string getPos(string fname)
{//���غ�׺�� 
    int pos=fname.length()-1; //�ļ������� 
    while(pos!=-1&&fname[pos]!='.'&&fname[pos]!='/')pos--;//��'.'����'/' 
    if(pos==-1)return "";//û�ҵ� 
    string last=fname.substr(pos,fname.length());
    return last;//�ҵ��� 
}

void init()
{
	int pos,s,t,len;
	string reader,pots,path;
	ifstream fin("clean.inf");
	while(getline(fin,reader))
	{
		pos=s=t=0;
		len=reader.length()-1;
		while(pos<=len&&reader[pos++]!='[');s=pos;
		while(pos<=len&&reader[pos++]!=']');t=pos-2;
		//cout<<reader.substr(s,t)<<" "<<reader.substr(pos,len)<<endl;
		mp[reader.substr(s,t)]=reader.substr(pos,len);
	}
}

int main()
{
	system("color 8E");
	init();
	vector<string> files;
	getFiles("./file",files);
	int size = files.size();
    for (int i = 0; i < size; i++)
    {
        cout<<"["<<files[i]<<"]>>>["<<mp[getPos(files[i])]<<"]"<<endl;
        /*move ad mp[ad];*/
    }
	return 0;
}
