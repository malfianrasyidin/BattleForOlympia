/* DRIVER LIST DP UNIT */

#include "listdpUnit.h"
#include <stdio.h>

void PrintPoint (POINT P) {
	printf("(%d,%d)", Absis(P), Ordinat(P));
}

void PrintListOfPoint (List L) {
	addressList P = First(L);
	printf("[ ");
	while (P != Nil) {
		PrintPoint(Info(P));
		printf(" ");
		P = Next(P);
	}
	printf("]\n");
}

int main () {
	List L;
	infotype X;
	int a, b, c;
	printf("/Membuat Empty List/\n");
	CreateEmptyList(&L);
	PrintListOfPoint(L);
	printf("/Menambah Elemen List/\n");
	printf("InsVFirst. Format masukan: <X> <Y>\n");
	printf("Masukan akan diterima hingga pengguna memasukkan -999 -999\n");
	scanf("%d %d", &a, &b);
	while ((a != -999) || (b != -999)) {
		Absis(X) = a;
		Ordinat(X) = b;
		InsVFirst(&L, X);
		PrintListOfPoint(L);
		scanf("%d %d", &a, &b);
	}
	printf("InsVLast. Format masukan: <X> <Y>\n");
	printf("Masukan akan diterima hingga pengguna memasukkan -999 -999\n");
	scanf("%d %d", &a, &b);
	while ((a != -999) || (b != -999)) {
		Absis(X) = a;
		Ordinat(X) = b;
		InsVLast(&L, X);
		PrintListOfPoint(L);
		scanf("%d %d", &a, &b);
	}
	printf("/Menghapus Elemen List/\n");
	printf("DelVFirst. Format masukan: 0\n");
	printf("Masukan selain 0 akan dianggap berhenti\n");
	scanf("%d", &a);
	while (a == 0 && !IsEmptyList(L)) {
		DelVFirst(&L, &X);
		PrintPoint(X);
		printf("\n");
		PrintListOfPoint(L);
		scanf("%d", &a);
	}
	printf("DelVFirst. Format masukan: 0\n");
	printf("Masukan selain 0 akan dianggap berhenti\n");
	scanf("%d", &a);
	while (a == 0 && !IsEmptyList(L)) {
		DelVFirst(&L, &X);
		PrintPoint(X);
		printf("\n");
		PrintListOfPoint(L);
		scanf("%d", &a);
	}
	printf("NbElmtList = %d\n", NbElmtList(L));
	printf("Search\n");
	printf("Masukan infotype X\n");
	scanf("%d %d", &a, &b);
		Absis(X) = a;
		Ordinat(X) = b;
	printf("DelP. Format masukan: <X> <Y>\n");
	printf("Masukan akan diterima hingga pengguna memasukkan -999 -999\n");
	scanf("%d %d", &a, &b);
	while ((a != -999) || (b != -999)) {
		Absis(X) = a;
		Ordinat(X) = b;
		DelP(&L, X);
		PrintListOfPoint(L);
		scanf("%d %d", &a, &b);
	}
}