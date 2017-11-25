/* DRIVER LIST DP UNIT */

#include "listdpUnit.h"
#include <stdio.h>

void PrintPoint (POINT P) {
	printf("(%d,%d)", Absis(P), Ordinat(P));
}

void PrintListOfPoint (List L) {
	addressList P = First(L);
	printf("[ ")
	while (P != Nil) {
		PrintPoint(Info(P));
		printf(" ");
	}
}

int main () {
	List L;
	infotype X;
	int a, b;
	printf("/Menambah Elemen List/\n")
	printf("InsVFirst. Format masukan: <X> <Y>\n")
	printf("Masukan akan diterima hingga pengguna memasukkan -999 -999\n")
	scanf("%d %d\n", &a, &b);
	while ((a !== -999) || (b != -999)) {
		Absis(X) = a;
		Ordinat(X) = b;
	}
	
}