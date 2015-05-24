#pragma once
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <vector>
using namespace std;


class Read_File
{
public:
	int count;
	Read_File()
	{
		count=0;
	}

	int getFileCount()
	{
		ifstream file("Read.txt");
		string str;
		while (getline(file, str))
			count++;
		return count;
	}

	vector<string> split(char* str, char splitChar)
	{
		vector<string> strings;
		int i=0;
		while(str[i]!=NULL)
		{
			int j=0;
			string splitStr = "";
			for(j=0;str[i+j]!=splitChar && str[i+j]!=NULL;j++)
			{
				splitStr+=str[i+j];
			}
			strings.push_back(splitStr);
			i+=j+(str[i+j]==splitChar?1:0);
		}
		return strings;
	}

	////khandan az file amade
	int** RadingFile1(int n)
	{
		vector<vector<string>> s;

		ifstream file("out.tr");
		char str[100];//=new char[100];
		for(int i=0;!file.eof();i++)
		{
			file.getline(str, 100);
			vector<string> strings = split(str,' ');
			s.push_back(strings);
		}

/////////////////////////////////////////////
			//stringstream ss(str);
			//string token;
			//j=0;
			//while (getline(ss,token, ' '))
			//{
			////s[i][j++]=atoi(token.c_str());
			//	s[i][j++]=(token.c_str());
			//}
			//i++;
///////////////////////////////////////////
		

		////using ofstream to output strings to a text file
		ofstream myfile;
		myfile.open ("myTest.txt");
		if (myfile.is_open())
		{
			
			 myfile << "Event,Time,Fromnode,Tonode,Pkttype,PktSize,.....,Flags,Fid,Srcaddr,Dstaddr,Seqnum,Pktid\n";
			for(int i=0;i<s.size();i++)
			{ 
				if(s[i][0]=="r" && s[i][4]=="cbr" && s[i][2]=="1" && s[i][3]=="2")
				{
				for(int j=0;j<s[i].size();j++)	
				{
					myfile << s[i][j]<<",";
				}
				myfile  <<"\n";
				}

				else if(file.eof())
					i++;
			}
			myfile.close();
		}
		else cout << "Can't open file";

		return 0;	

	}
};

/////////////////////////////////////////
		//int main () {
		//
		//	//using ofstream to output strings to a text file
		//   ofstream myfile ("myTest.txt");
		//
		//   if (myfile.is_open())
		//   {
		//   	myfile << "This is a test.\n";
		//   	myfile << "I am learning C++.\n";
		//   	myfile.close();
		//   }
		//   else cout << "Can't open file";
		//
		//   return 0;
		//}
		//return s;
///////////////////////////////////////




