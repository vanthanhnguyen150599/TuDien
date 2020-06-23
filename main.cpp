#include<iostream>
#include "mylib.h"
#include "ve.h"
#include "cautruc.h"
using namespace std;
int main()
{
	DSTu ds;
	if (!docTu(ds)) cout << "Doc file that bai";
	xuLy(ds);
	luuFile(ds);
}
