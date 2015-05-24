// networkproject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "Read_File.h"
#include "windows.h"
#include "conio.h"
using namespace std;
void main()
{
	int x;
	system("color 1b");
	cout<<"                                 Wellcom To AMI\n\n\n\n\n\n\n\n\n";
	cout<<"                               Please Wait Second\n\n\n";
	for(int i=0;i<5;i++)
	{
		Sleep(1000);
		cout<<i<<"\t";
	}
	Read_File myread;
	myread.getFileCount();
	x=myread.count;
	myread.RadingFile1(x);
	for(int i=5;i<10;i++)
	{
		Sleep(1000);
		cout<<i<<"\t";
	}
	Sleep(1000);
    system("color 5f");
	system("cls");
	cout<<"                                Wellcom To AMI\n\n\n\n\n\n\n\n\n";
	cout<<"                                Program Finish\n";
	cin.get();
}


