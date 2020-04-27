#ifndef _VE_H // 1 man hinh dai 210, rong 52
#define _VE_H

#include<iostream>
#include "mylib.h"
using namespace std;

void veKhung(int dai, int rong)
{
	char traitren = 201;
	char phaitren = 187;
	char traiduoi = 200;
	char phaiduoi = 188;
	char ngang = 205;
	char doc = 186;
	char doctrai = 185;
	char docphai = 204;
	for (int i = 0; i < dai; i++)
	{
		for (int j = 0; j < rong; j++)
		{
			if (i == 0)
			{
				if (j == 0)
				{
					cout << traitren;
					continue;
				}
				if (j == rong - 1)
				{
					cout << phaitren;
					continue;
				}
				cout << ngang;
				continue;
			}
			if (i == 2)
			{
				if (j == 0)
				{
					cout << docphai;
					continue;
				}
				if (j == rong - 1)
				{
					cout << doctrai;
					continue;
				}
				cout << ngang;
				continue;
			}
			if (i == dai - 1)
			{
				if (j == 0)
				{
					cout << traiduoi;
					continue;
				}
				if (j == rong - 1)
				{
					cout << phaiduoi;
					continue;
				}
				cout << ngang;
				continue;
			}
			if (j == 0 || j == rong - 1)
			{
				cout << doc;
				continue;
			}
			cout << " ";
		}
		gotoxy(wherex()-rong,wherey()+1);
	}
}
// ========================== KHUNG SHOW TU ===========================
void veKhungShow(int dai, int rong)
{
	char traitren = 201;
	char phaitren = 187;
	char traiduoi = 200;
	char phaiduoi = 188;
	char ngang = 205;
	char doc = 186;
	char doctrai = 185;
	char docphai = 204;
	gotoxy(0,0);
	for (int i = 0; i < dai; i++)
	{
		for (int j = 0; j < rong; j++)
		{
			if (i == 0)
			{
				if (j == 0)
				{
					cout << traitren;
					continue;
				}
				if (j == rong - 1)
				{
					cout << phaitren;
					continue;
				}
				cout << ngang;
				continue;
			}
/*			if (i == 2)
			{
				if (j == 0)
				{
					cout << docphai;
					continue;
				}
				if (j == rong - 1)
				{
					cout << doctrai;
					continue;
				}
				cout << ngang;
				continue;
			} */
			if (i == dai - 1)
			{
				if (j == 0)
				{
					cout << traiduoi;
					continue;
				}
				if (j == rong - 1)
				{
					cout << phaiduoi;
					continue;
				}
				cout << ngang;
				continue;
			}
			if (j == 0 || j == rong - 1)
			{
				cout << doc;
				continue;
			}
			cout << " ";
		}
		gotoxy(wherex()-rong,wherey()+1);
	}
}

#endif
