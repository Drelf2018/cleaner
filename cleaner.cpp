#include <io.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <map>
#include <windows.h>
#include <time.h>
#include <cstdio>
using namespace std;

map<string,string> mp;

void getFiles(string path, vector<string>& files)
{
    long   hFile = 0;//文件句柄  
    struct _finddata_t fileinfo;//文件信息  
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

string getPos(string fname)
{//返回后缀名 
    int pos=fname.length()-1; //文件名长度 
    while(pos!=-1&&fname[pos]!='.'&&fname[pos]!='/')pos--;//找'.'或者'/' 
    if(pos==-1)return "";//没找到 
    string last=fname.substr(pos,fname.length());
    return last;//找到了 
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
		//cout<<reader.substr(s,t-s+1)<<" "<<reader.substr(pos,len-pos+1)<<endl;
		mp[reader.substr(s,t-s+1)]=reader.substr(pos,len-pos+1);
	}
}

string getTime()
{
	char tmp[64];
	string r;
	time_t t = time(0); 
	strftime(tmp,sizeof(tmp),"%Y-%m-%d",localtime(&t) );
	r=tmp;
	return r; 
}

void move(string file)
{
	int len=0,i=1,j=2;
	string path=".";
	cout<<"["<<file<<"]>>>["<<mp[getPos(file)]<<"]"<<endl;
	if(mp[getPos(file)]!="")
	{
		path.append(mp[getPos(file)]);
		len=path.length();//***
		while(i<len&&j<len)
		{
			while(path[j]!='/')j++;
			if(path.substr(i+1,j-i-1)=="AutoTime")
				path.replace(i+1,j-i-1,getTime()),j=path.find("/",j);
			//cout<<path.substr(i+1,j-i-1)<<endl;
			i=j++; 
		}
		cout<<"here"<<endl;
		cout<<path<<endl;
		while(CreateDirectory(path.c_str(),NULL));
	}
    /*move ad mp[ad];*/
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
        move(files[i]);
    }
	return 0;
}
