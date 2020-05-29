#ifndef _CAUTRUC_H // 1 man hinh dai 210, rong 52
#define _CAUTRUC_H

#include<iostream>
#include<fstream>
#include<string>
#include "mylib.h"
#include "ve.h"
using namespace std;

//========================== STRUCT NGHIA =======================
struct nghiaTu
{
	string nghia = "";
	nghiaTu *next = NULL;
};
// ======================== DANH SACH NGHIA =====================
struct listNghia
{
	nghiaTu *First = NULL;
};
// ========================== STRUCT TU =========================
struct tuNgu
{
	string word = "";
	string tuLoai = "";
	listNghia nghia;
	string *viDu[5] = {NULL};
};
// ====================== DANH SACH LIEN KET KEP ===================
struct lienKetTu
{
	tuNgu tu;
	lienKetTu *next = NULL;
	lienKetTu *pre = NULL;
};
// ========================= MANG BAM  ==============================
struct DSTu
{
	lienKetTu *danhSachTu[26] = {NULL};
//	lienKetTu *danhSachCuoi[26] = {NULL};
};



// ======================= HAM BAM ==================================
int hashtable(string tu)
{
	return tu[0] - 97; // (int) 'a' = 97 (int)'z' = 122
}
// ========================= THEM NGHIA ===============================
void themNghia(tuNgu &word, string nghia)
{
	if (word.nghia.First == NULL) // Them dau
	{
		word.nghia.First = new nghiaTu;
		word.nghia.First->nghia = nghia;
		word.nghia.First->next = NULL;
	}
	else // Them cuoi 
	{
		nghiaTu *p;
		for (p = word.nghia.First; p->next != NULL; p = p->next);
		p->next = new nghiaTu; // Tao con tro moi o duoi
		p = p->next; // Tro den duoi
		p->nghia = nghia; // Gan
		p->next = NULL;
	}
}
// =========================== LAY NGHIA ================================
void layNghia(tuNgu &word, string nghia)// 
{
	string temp;
	for (int i = 0; i < nghia.length(); i++)
	{
		if (nghia[i] != ',') temp = temp + nghia[i];
		else
		{
			themNghia(word,temp);
			temp = "";
		}
	}
//	cout << temp;
	themNghia(word,temp);
}
// =========================  THEM VI DU =================================
bool themVD(tuNgu &word, string VD)
{
	if (word.viDu[4] != NULL) return 0; // Da du VD
	for (int i = 0; i < 5; i++)
	{
		if (word.viDu[i] == NULL)
		{
			word.viDu[i] = new string;
			*(word.viDu[i]) = VD;
			return 1;
		}
	} 
}
// ========================= LAY VD ==================================
void layVD(tuNgu &word,string VD)
{
	string temp;
	for (int i = 0; i < VD.length(); i++)
	{
		if (VD[i] != ',') temp = temp + VD[i];
		else // tach nghia
		{
			themVD(word,temp);
			temp = "";
		}
	}
	themVD(word,temp);
}
// ============================ SO SANH TU ============================
int soSanhTu(string a, string b) // tra ve 1 a sau b, tra ve 0 a = b, tra ve -1 a truoc b
{
	if (a.length() < b.length()) // do dai cua a < do dai cua b // a = six, b = sixty
	{
		for (int i = 0; i < a.length(); i++)
		{
			if (a[i] == b[i]) continue;
			if (a[i] > b[i]) return 1;
			return -1;
		}
		return -1;
	}
	for (int i = 0; i < b.length(); i++) // do dai cua a >= do dai cua b
	{
		if (a[i] == b[i]) continue;
		if (a[i] > b[i]) return 1;
		return -1;
	}
	if (a.length() == b.length()) return 0; //(six-six)
	return 1; // (sixty - six)
}
// ========================= THEM TU =================================
bool themTu(DSTu &ds, tuNgu word)
{
	int vitri = hashtable(word.word); // vi tri o ham bam
	if (ds.danhSachTu[vitri] == NULL) // Them dau hash thu vitri+1
	{
		ds.danhSachTu[vitri] = new lienKetTu;
		ds.danhSachTu[vitri]->tu = word;
		ds.danhSachTu[vitri]->next = NULL;
		ds.danhSachTu[vitri]->pre = NULL;
		return 1;
	}
	lienKetTu *p;
	for (p = ds.danhSachTu[vitri]; p != NULL; p = p->next)
	{
		if (soSanhTu(p->tu.word,word.word) == 0) return 0; // Tu nay da ton tai
		if (soSanhTu(p->tu.word,word.word) == 1) // Tim tu nam sau word
		{
			if (p->pre == NULL) // Them dau p = head
			{
				lienKetTu *q = new lienKetTu;
				q->next = ds.danhSachTu[vitri];
				ds.danhSachTu[vitri]->pre = q;
				q->pre = NULL;
				q->tu = word;
				ds.danhSachTu[vitri] = q;
				return 1;
			}
			// Them giua
			{
				lienKetTu *q = new lienKetTu;
				q->pre = p->pre;
				p->pre = q;
				q->next = p;
				q->pre->next = q;
				q->tu = word;
				return 1;
			}
			
		}
		if (p->next == NULL)// Them cuoi
		{
			p->next = new lienKetTu;
			p->next->pre = p;
			p = p->next;
			p->next = NULL;
			p->tu = word;
			return 1;
		}
//		{
//			lienKetTu *q = new lienKetTu;
//			q->next = p->next;
//			p->next = q;
//			p->next->pre = p;
//			q->next->pre = q;
//			p->tu = word;
//			return 1;
//		}
	}
} 
// ======================== DOC TU =====================================
bool docTu(DSTu &ds)
{
	string word;
	string tuLoai;
	string nghia;
	string VD;
	
	ifstream infile;
	infile.open("input.txt",ios_base::in);
	if (infile.fail()) return 0;
	while (!infile.eof())
	{
		tuNgu temp;// data cua tu
		getline(infile,word,';');
		getline(infile,tuLoai,';');
		getline(infile,nghia,';');
		getline(infile,VD,';');
		infile.ignore();
		
		{
			temp.word = word;
			temp.tuLoai = tuLoai;
			layNghia(temp,nghia);
			layVD(temp,VD);
			themTu(ds,temp);
		}
//		cout << word << " ";
//		cout << temp.nghia.First->nghia << endl;
//		cout << *(temp.viDu[0]) << endl;
	}
//	for (int i = 0; i < 26; i++)
//	for (lienKetTu *p = ds.danhSachTu[0]; p != NULL; p = p->next) cout << p->tu.word << endl;
	
	return 1;
}
// ======================== TU TIEP THEO ===========================
lienKetTu *nextWord(lienKetTu *word,DSTu &ds)
{
//	lienKetTu *temp = word
	int vitri = hashtable(word->tu.word);
	while (1)
	{
		if (word == NULL || word->next == NULL)
		{
			if (vitri < 25)
			{
				word = ds.danhSachTu[vitri+1];
				vitri++;
				
				if (word != NULL){return word;}
				continue;
			}
			return NULL;
		}
		if (word->next != NULL) return (word->next);
	}
}
// ========================= TU TRUOC DO ======================
lienKetTu *preWord(lienKetTu *word, DSTu &ds)
{
	int vitri = hashtable(word->tu.word);
	while (1)
	{
		
		if (word == NULL || word->pre == NULL)
		{
			if (vitri > 0)
			{
				if (ds.danhSachTu[vitri-1] != NULL)
				{
					for (word = ds.danhSachTu[vitri-1]; word->next != NULL; word = word->next);
					vitri--;
					return word;
				}
				vitri--;
				continue;
			}
			return NULL;	
		}
		if (word->pre != NULL) return word->pre;
	}
}
// ====================== TU DAU TIEN ========================
lienKetTu *firstWord(DSTu &ds)
{
	for (int i = 0; i < 26; i++) // tim hashtable
	{
		if (ds.danhSachTu[i] != NULL) return ds.danhSachTu[i];
	}
	return NULL;
}
// ==================== TIM KIEM TU ======================
bool isMatch(string word, string search) // search = six, word = sixty
{
	if (word.length() < search.length()) return 0;
	for (int i = 0; i < search.length(); i++) // search <= word (lenght)
	{
		if (word[i] != search[i]) return 0;
	}
	return 1;//(sixty, six)
}
// =============================== SHOW VD ============================
void showVD(lienKetTu *word)
{
	string VD;
	string temp;
	string x;
	for (int i = 0; i < 5; i++)
	{
		if (word->tu.viDu[i] == NULL) break;
		gotoxy(3,wherey()+2);
		cout << "Vi du " << i+1 << ": ";
		gotoxy(2,wherey()+1);
		VD = *(word->tu.viDu[i]);
		temp = "";
		x = "";
		for (int j = 0; j < word->tu.viDu[i]->length(); j++)
		{
			if (VD[j] != ' ')
			{
				x = x + VD[j];
				continue;
			}
			if(temp.length() + x.length() + 1 < 56)
			{
				temp = temp + ' ' + x;
				x = "";
			}
			else
			{
				cout  << temp;
				temp = "";
				temp = x;
				x = "";
				gotoxy(4,wherey()+1);
			}
		}
		if(temp.length() + x.length() + 1 < 56) // vet mang
		{
			temp = temp + ' ' + x;
			cout << temp;
		}
		else
		{
			cout << temp;
			gotoxy(4,wherey()+1);
			cout << x;
		}
	}
	
}
// ============================== XEM TU ===============================
void showWord(lienKetTu *word)
{
	anConTro();
	changeColor(15);
	veKhungShow(30,60);
	gotoxy(2,5);
	cout << word->tu.word;
	gotoxy(2,7);
	cout << "Tu loai: " << word->tu.tuLoai;
	gotoxy(2,9);
	cout << "Nghia: " << word->tu.nghia.First->nghia;
	for (nghiaTu *p = word->tu.nghia.First->next; p != NULL; p = p->next)
	{
		cout << ", " << p->nghia;
	}
//	gotoxy(2,11);
/*	cout << "Vi du: ";
	for (int i = 0; i < 5; i++)
	{
		if (word->tu.viDu[i] == NULL) break;
		gotoxy(2,12+i);
		cout << *word->tu.viDu[i];
	} */
	showVD(word);
}
// ========================== XOA TU ===================================
void deleteWord(lienKetTu *word, DSTu &ds)
{
	if (word->pre == NULL) // xoa dau
	{
		int vitri = hashtable(word->tu.word);
		ds.danhSachTu[vitri] = ds.danhSachTu[vitri]->next;
		if (ds.danhSachTu[vitri != NULL])ds.danhSachTu[vitri]->pre = NULL;
		delete word;
		return;
	}
	if (word->next == NULL) // xoa cuoi
	{
		word->pre->next = NULL;
		delete word;
		return;
	}
	
	word->pre->next = word->next;
	word->next->pre = word->pre;
	delete word;
}
// ===================== NHAP THONG TIN TU ===================
lienKetTu *nhapThongTinTu(DSTu &ds)
{
	changeColor(15);
	system("cls");
	veKhungShow(30,60);
	lienKetTu *res = NULL;
	char c;
	bool kytu;
	int cur = 0;
	string tu;
	string tuloai;
	string nghia;
	string *VD[5] = {NULL};
	hienConTro();
	gotoxy(2,5);
	cout << "Nhap tu: "; // tu : 11,5
	gotoxy(2,7);
	cout << "Nhap tu loai: "; // 16,7
	gotoxy(2,9);
	cout << "Nhap nghia: "; // 14,9
	gotoxy(26,26);
	cout << "LUU TU";
	for (int i = 0; i < 5; i++)
	{
		gotoxy(2,11+2*i);
		cout << "Vi du " << i+1 << ": "; // 11,11 + 2*i
	}
	gotoxy(11,5);
	pressKey(c,kytu);
	while(c != 27)
	{
		if (c == 72 && !kytu) // UP
		{
			if (cur > 0)
			{
				cur--;
				switch(cur)
				{
					case 0:
						{
							gotoxy(11+tu.length(),5);
							break;
						}
					case 1:
						{
							gotoxy(16+tuloai.length(),7);
							break;
						}
					case 2:
						{
							gotoxy(14+nghia.length(),9);
							break;
						}		
				}
				if (cur >= 3 && cur <= 7)
				{
					if (cur == 7)
					{
						anConTro();
						gotoxy(26,26);
						changeColor(15);
						cout << "LUU TU";
						hienConTro();
					}
					if (VD[cur-3] != NULL)
					{
						if (VD[cur-3]->length() < 46)
						{
							gotoxy(11+VD[cur-3]->length(),11+2*(cur-3));
									
						}
						else
						{
							gotoxy(58,11+2*(cur-3));
						}
					}
					else gotoxy(11,11+2*(cur-3));
				}	
			}
		}
		if (c == 80 && !kytu) // DOWN
		{
			if (cur < 8)
			{
				cur++;
				switch(cur)
				{
					case 8:
						{
							gotoxy(26,26);
							changeColor(192);
							cout << "LUU TU";
							anConTro();
							break;
						}
					case 1:
						{
							gotoxy(16+tuloai.length(),7);
							break;
						}
					case 2:
						{
							gotoxy(14+nghia.length(),9);
							break;
						}
				} 
				if (cur >= 3 && cur <= 7)
				{
					if (VD[cur-3] != NULL)
					{
						if (VD[cur-3]->length() < 46)
						{
							gotoxy(11+VD[cur-3]->length(),11+2*(cur-3));
							break;
						}
						else
						{
							gotoxy(58,11+2*(cur-3));
							break;
						}
					}
					else gotoxy(11,11+2*(cur-3));
				}
			}
		}
		
		pressKey(c,kytu);
	}
	return res;
}
// ===================== XU LY ================================
void xuLy(DSTu &ds)
{
//	fullscreen();
	veKhung(30,60);
	int cur = 0;
	lienKetTu *mang[26] = {NULL};
	if (firstWord(ds) == NULL) cout << "Chua co tu nao trong tu dien";
	else // Khoi tao mang
	{
		mang[0] = firstWord(ds);
		changeColor(192);
		gotoxy(1,3);
		cout << mang[0]->tu.word;
		changeColor(15);
		for (int i = 1; i < 26; i++)
		{
			if (mang[i-1] == NULL)
			{
				mang[i] = NULL;
				continue;
			} 
			mang[i] = nextWord(mang[i-1],ds);
			gotoxy(1,i+3);
			if (mang[i] != NULL) 
			{
				cout << mang[i]->tu.word;
			}
		}
	}
	char c;
	bool kytu;
	string search;
	int dem = 0; // dung cho search box
	gotoxy(search.length()+1,1);
	hienConTro();
	pressKey(c,kytu);
	while (c != 27) // Khong nhan Esc
	{
		if (c == 72 && !kytu) // Up
		{
			anConTro();
			if (cur > 0)
			{
				changeColor(15);
				gotoxy(1,cur+3);
				cout << mang[cur]->tu.word;
				cur--;
				changeColor(192);
				gotoxy(1,cur+3);
				cout << mang[cur]->tu.word;
			}
			else // cur = 0
			{
				if (preWord(mang[cur],ds) != NULL && search.empty()) //khong co search
				{
					changeColor(15);
					for (int i = 25; i > 0; i--)
					{
						mang[i] = mang[i-1];
						gotoxy(1,i+3);
						cout << mang[i]->tu.word << "          ";
					}
					mang[cur] = preWord(mang[cur],ds); // cur = 0
					gotoxy(1,cur+3);// clean
					cout << "               ";
					changeColor(192);
					gotoxy(1,3);
					cout << mang[cur]->tu.word;
					changeColor(15);
				}
				else
				{
					if (!search.empty())
					{
						if (isMatch(preWord(mang[cur],ds)->tu.word,search))
						{
							changeColor(15);
							for (int i = 25; i > 0; i--)
							{
								mang[i] = mang[i-1];
								gotoxy(1,i+3);
								cout << mang[i]->tu.word << "         ";
							}
							mang[cur] = preWord(mang[cur],ds);
							gotoxy(1,cur+3);
							cout << "                ";
							changeColor(192);
							gotoxy(1,cur+3);
							cout << mang[cur]->tu.word;
						}
					}
				}
			}
		}
		if (c == 80 && !kytu) // Down
		{
			anConTro();
			if (cur < 25 && nextWord(mang[cur],ds) != NULL && search.empty())
			{
				
				changeColor(15);
				gotoxy(1,cur+3);
				cout << mang[cur]->tu.word;
				cur++;
				changeColor(192);
				gotoxy(1,cur+3);
				cout << mang[cur]->tu.word;
			}
			else // cur = 25 hoac mang[cur+1] = NULL (bieen duoi)
			{
				if (nextWord(mang[cur],ds) != NULL && search.empty()) // khong search box
				{
					changeColor(15);
					for (int i = 0; i < 25; i++)
					{
						mang[i] = mang[i+1];
						gotoxy(1,i+3);
						cout << mang[i]->tu.word << "       ";
					}
					mang[cur] = nextWord(mang[cur],ds);
					gotoxy(1,cur+3);// clean
					cout << "               ";
					changeColor(192);
					gotoxy(1,cur+3);
					cout << mang[cur]->tu.word;
					changeColor(15);
				}
				if (!search.empty()) // co search box
				{
					if (cur < 25)
					{
						if (mang[cur+1] != NULL)
						{
							changeColor(15);
							gotoxy(1,cur+3);
							cout << mang[cur]->tu.word;
							cur++;
							changeColor(192);
							gotoxy(1,cur+3);
							cout << mang[cur]->tu.word;
						}
					}
					else
					{
						if (isMatch(nextWord(mang[cur],ds)->tu.word,search))
						{
							changeColor(15);
							for (int i = 0; i < 25; i++)
							{
								mang[i] = mang[i+1];
								gotoxy(1,i+3);
								cout << mang[i]->tu.word << "         ";
							}
							mang[cur] = nextWord(mang[cur],ds);
							gotoxy(1,cur+3);
							cout << "                ";
							changeColor(192);
							gotoxy(1,cur+3);
							cout << mang[cur]->tu.word;
						}
					}
				}
			}
		}
		if ((c >= 97 && c <= 122) && kytu) // a->z
		{
			changeColor(15);
			gotoxy(1+search.length(),1);
			cout << c;
			search = search + c;
			if (!search.empty()) // cap nhat list
			{
				bool check = 0;
				int vitri = hashtable(search);
				dem = 0;
				for (lienKetTu *p = ds.danhSachTu[vitri]; p != NULL; p = p->next) // nap tu
				{
					anConTro();
					if (isMatch(p->tu.word,search) && dem < 26)
					{
						check = 1;
						mang[dem] = p;
						changeColor(15);
						gotoxy(1,dem+3);
						cout << mang[dem]->tu.word << "        ";
						dem++;
						continue;
					}
					if (check) break;// 
				}
				for (int i = dem; i < 26; i++)
				{
					changeColor(15);
					mang[i] = NULL;
					gotoxy(1,i+3);
					cout << "                        ";
				}
				if (mang[0] != NULL)
				{
					changeColor(192);
					gotoxy(1,3);
					cout << mang[0]->tu.word;
					cur = 0; // Cap nhat vi tri
				}
			}
		}
		if (c == 8) // backspace
		{
			if (!search.empty())
			{
				changeColor(15);
				gotoxy(search.length(),1);
				cout << " ";
				search = search.erase(search.length()-1);
				if (search.empty()) // khoi tao lai
				{
					cur = 0;
					mang[0] = firstWord(ds);
					changeColor(15);
					gotoxy(1,3);
					cout << "                 ";
					changeColor(192);
					gotoxy(1,3);
					cout << mang[0]->tu.word;
					changeColor(15);
					for (int i = 1; i < 26; i++)
					{
						if (mang[i-1] == NULL)
						{
							mang[i] = NULL;
							continue;
						} 
						mang[i] = nextWord(mang[i-1],ds);
						gotoxy(1,i+3);
						if (mang[i] != NULL) cout << mang[i]->tu.word << "       ";
					}
				}
				else // cap nhat list
				{
					bool check = 0;
					int vitri = hashtable(search);
					dem = 0;
					for (lienKetTu *p = ds.danhSachTu[vitri]; p != NULL; p = p->next) // nap tu
					{
						anConTro();
						if (isMatch(p->tu.word,search) && dem < 26)
						{
							check = 1;
							mang[dem] = p;
							changeColor(15);
							gotoxy(1,dem+3);
							cout << mang[dem]->tu.word << "        ";
							dem++;
							continue;
						}
						if (check) break;
					}
					for (int i = dem; i < 26; i++)
					{
						changeColor(15);
						mang[i] = NULL;
						gotoxy(1,i+3);
						cout << "                        ";
					}
					if (mang[0] != NULL)
					{
						changeColor(192);
						gotoxy(1,3);
						cout << mang[0]->tu.word;
						cur = 0; // Cap nhat vi tri
					}
				}
			}
		}
		if (c == 13) //Enter
		{
			if (mang[cur] != NULL)
			{
				changeColor(15);
				system("cls");
				showWord(mang[cur]);
				gotoxy(0,31);
				system("pause");
				system("cls");
				// Khoi tao lai mang
				veKhung(30,60);
				anConTro();
				changeColor(15);
				if (!search.empty()) // In lai search box
				{
					gotoxy(1,1);
					cout << search;
				}
				for (int i = 0; i < 26; i++)
				{
					if  (mang[i] != NULL )
					{
						gotoxy(1,i+3);
						cout << mang[i]->tu.word;
					}
				}
				changeColor(192);
				gotoxy(1,cur+3);
				cout << mang[cur]->tu.word;
				changeColor(15); 
			}
		}
		if (c == 83 && !kytu) // DELETE
		{
			anConTro();
			changeColor(15);
			system("cls");
			gotoxy(0,30);
			cout << "Ban co muon xoa tu " << mang[cur]->tu.word << "? " << endl << "Nhan Y den XAC NHAN hoac nhan phim bat ky de thoat";
			pressKey(c,kytu);
			if (c == 121 && kytu)
			{
				deleteWord(mang[cur],ds);
				changeColor(15);
				system("cls");
				// Khoi tao lai
				veKhung(30,60);
				cur = 0;
				if (firstWord(ds) != NULL)
				{
					mang[0] = firstWord(ds);
					changeColor(192);
					gotoxy(1,3);
					cout << mang[0]->tu.word;
					changeColor(15);
					for (int i = 1; i < 26; i++)
					{
						if (mang[i-1] == NULL)
						{
							mang[i] = NULL;
							continue;
						} 
						mang[i] = nextWord(mang[i-1],ds);
						gotoxy(1,i+3);
						if (mang[i] != NULL) cout << mang[i]->tu.word;
					}
				}
				else
				{
					gotoxy(0,31);
					cout << "Tu dien trong";
				}
			}
			else
			{
				anConTro();
				changeColor(15);
				system("cls");
				veKhung(30,60);
				for (int i = 0; i < 26; i++)
				{
					if (mang[i] == NULL) break;
					gotoxy(1,i+3);
					cout << mang[i]->tu.word;
				}
				gotoxy(1,cur+3);
				changeColor(192);
				cout << mang[cur]->tu.word;
				changeColor(15);
				gotoxy(1,1); // phuc hoi search box
				cout << search;
			}
		}
		if (c == 61 && !kytu) // F3
		{
			nhapThongTinTu(ds);
			
		}
		gotoxy(search.length()+1,1);
		hienConTro();
		pressKey(c,kytu);
	} 
	
}

#endif
