/* File: mesinkata.h */
/* NIM				: 13516098
   Nama				: Rifqi Rifaldi Utomo
   Tanggal			: 23 September 2017
   Topik praktikum	: Mesin Kata Versi 1
   Deskripsi		: Mesin Kata Versi 1
 */

#include "mesininput.h"
#include "mesinkarT.h"
#include "boolean.h"
#include <stdio.h>

/* State Mesin Kata */
boolean EndInput;
Input CInput;

void EmbraceBlank()
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang 
   F.S. : CC ≠ BLANK atau CC = MARK */
{	/* ALGORITMA */
	while ((CCI == BLANK) || (CCI != MARK)) {
		ADVIN();
	}
}

void BACAINPUT()
/* I.S. : CC sembarang 
   F.S. : EndInput = true, dan CC = MARK; 
          atau EndInput = false, CInput adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */
{	STARTIN();
	EmbraceBlank();
	EndInput = (CCI == MARK);
	if (!EndInput) {
	SalinInput();
	}
}

void ADVINPUT()
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi 
   F.S. : CInput adalah kata terakhir yang sudah diakuisisi, 
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndInput = true.		  
   Proses : Akuisisi kata menggunakan procedure SalinKata */
{	EmbraceBlank();
	EndInput = (CCI == MARK);
	if (!EndInput) {
	SalinInput();
	}
}

void SalinInput()
/* Mengakuisisi kata, menyimpan dalam CInput
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CInput berisi kata yang sudah diakuisisi; 
          CC = BLANK atau CC = MARK; 
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
{	/* KAMUS LOKAL */
	int i;
	/*ALGORITMA */
	i = 0;
	while ((CCI != MARK) && (CCI != BLANK) && (CCI != ENTER) && (i <= NMax)) {
		CInput.TabInput[i] = CCI;
		i = i + 1;
		ADVIN();
	}
	CInput.TabInput[i] = '\0';
	CInput.Length = i;
	EmbraceBlank();
}


boolean CmpInpStr(char Str[], Input II){
	int i = 0;
	boolean sama = true;
	char CStr;
	while((sama) && (CStr) && (i < CInput.Length)){
		CStr = Str[i];
		sama = CInput.TabInput[i] == CStr;
		i++;
	}
	printf("%c",CStr);
	if (i != CInput.Length ){
		return(false);
	}
	else{
		return(sama);
	}
}
