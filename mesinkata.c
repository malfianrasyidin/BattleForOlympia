#include "mesinkata.h"
#include "mesinkar.h"
#include "boolean.h"
#include <stdio.h>

/* State Mesin Kata */
boolean EndKata;
Kata CKata;

void IgnoreBlank()
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang 
   F.S. : CC ≠ BLANK atau CC = MARK */
{	/* ALGORITMA */
	while (((CC == BLANK) || (CC == ENTER)) && (CC != MARK)) {
		ADV();
	}
}

void STARTKATA(char filename[])
/* I.S. : CC sembarang 
   F.S. : EndKata = true, dan CC = MARK; 
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */
{	START(filename);
	IgnoreBlank();
	EndKata = (CC == MARK);
	if (!EndKata) {
	SalinKata();
	}
}

void ADVKATA()
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi 
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi, 
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.		  
   Proses : Akuisisi kata menggunakan procedure SalinKata */
{	IgnoreBlank();
	EndKata = (CC == MARK);
	if (!EndKata) {
	SalinKata();
	}
}

void SalinKata()
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi; 
          CC = BLANK atau CC = MARK; 
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
{	/* KAMUS LOKAL */
	int i;
	/*ALGORITMA */
	i = 0;
	while ((CC != MARK) && (CC != BLANK) && (CC != ENTER) && (i <= NMax)) {
		CKata.TabKata[i] = CC;
		i = i + 1;
		ADV();
	}
	CKata.TabKata[i] = '\0';
	CKata.Length = i;
	IgnoreBlank();
}
