#include "mesinkata.h"
#include "mesinkar.h"
#include <stdio.h>


boolean IsKataSama(Kata K1, Kata K2) {
/*	Mengembalikan true jika K1 = K2; dua kata dikatakan sama jika panjangnya sama dan
	urutan karakter yang menyusun kata juga sama. Sensitif terhadap uppercase dan lowercase
*/
	//KAMUS LOKAL
	int i;
	//ALGORITMA
	if (K1.Length==K2.Length) {
		i=0;
		while ((i<K1.Length) && (K1.TabKata[i]==K2.TabKata[i])) {
			i++;
		}
		if (i==K1.Length) return true;
		else return false;
	}
	else return false;
}

int main() {
	Kata KTitik, KKoma;
	int KReg, KPjg, biaya, i, countKata;
	boolean space, AkhirTelegram;
	
	KTitik.Length= 5;
	KTitik.TabKata[0]= 'T';
	KTitik.TabKata[1]= 'I';
	KTitik.TabKata[2]= 'T';
	KTitik.TabKata[3]= 'I';
	KTitik.TabKata[4]= 'K';
	
	KKoma.Length= 4;
	KKoma.TabKata[0]= 'K';
	KKoma.TabKata[1]= 'O';
	KKoma.TabKata[2]= 'M';
	KKoma.TabKata[3]= 'A';
	
	KReg= 0;
	KPjg= 0;
	countKata = 0;
	
	space= false;
	AkhirTelegram= false;
	
	STARTKATA("pitakar.txt");
	
	if (CC == BLANK) {
		IgnoreBlank();
	}
	if ((CKata.Length == 0) && (CC == MARK)) {
		AkhirTelegram= true;
	}
	while (!AkhirTelegram) {
		countKata+= 1;
		if (IsKataSama(CKata, KTitik)) {
			printf(". ");
			space= false;
		} else if (IsKataSama(CKata, KKoma)) {
			printf(", ");
			space= false;
		} else {
			if (space== true) {
				printf(" ");
			} else {
				space= true;
			}
			for (i= 0; i < CKata.Length; i++) {
				printf("%c", CKata.TabKata[i]);
			}
			if (CKata.Length < 10) {
				KReg+= 1;
			} else if (CKata.Length >= 10) {
				KPjg+= 1;
			}
		}
		CKata.Length = 0;
		ADVKATA();
		IgnoreBlank();
		if (CC == MARK) {
			EndKata= true;
		}
		if (EndKata) {
			AkhirTelegram= true;
		}	
	}
	if (CKata.Length > 0){
		countKata+= 1;
		if (IsKataSama(CKata, KTitik)) {
			printf(". ");
			space= false;
		} else if (IsKataSama(CKata, KKoma)) {
			printf(", ");
			space= false;
		} else {
			if (space== true) {
				printf(" ");
			}
			for (i= 0; i < CKata.Length; i++) {
				printf("%c", CKata.TabKata[i]);
			}
			space= true;
			if (CKata.Length < 10) {
				KReg+= 1;
			} else if (CKata.Length >= 10) {
				KPjg+= 1;
			}
		}
	}		
	if (countKata <= 10) {
		biaya= (KReg * 1000) + (KPjg * 1500);
	} else if (countKata > 10){
		biaya= (((KReg * 1000) + (KPjg * 1500)) * 0.9);
	}
	printf("\n%d\n", KReg);
	printf("%d\n", KPjg);
	printf("%d\n", biaya);
	return 0;
}
