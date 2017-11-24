/* File: jam_driver.c */
/* Tanggal: 31 Agustus 2017 */
/* Driver ADT JAM */

#include "jam.h"
#include <stdio.h>

int main () {
	JAM J, J1, J2;
	long S;
	TANGGAL D;
	printf("KELOMPOK BACA/TULIS\n");
	printf("Masukkan Jam yang salah :\n");
	BacaJAM(&J);
	printf("Jam yang Anda tulis adalah :\n");
	TulisJAM(J);
	printf("\nKELOMPOK KONVERSI TERHADAP TYPE\n");
	printf("Konversi Jam ke Detik\n");
	printf("Masukkan Jam :\n");
	BacaJAM(&J);
	printf("Jika dikonversi ke detik menjadi %d detik\n", JAMToDetik(J));
	printf("Masukkan Detik :\n");
	scanf("%d", &S);
	printf("Jika dikonversi ke jam menjadi ");
	TulisJAM(DetikToJAM(S));
	printf("\nKELOMPOK OPERASI TERHADAP TYPE\n");
	printf("Masukkan Jam 1 :\n");
	BacaJAM(&J1);
	printf("Masukkan Jam 2 :\n");
	BacaJAM(&J2);
	printf("Apakah Jam 1 = Jam 2? ");
	if (JEQ(J1, J2)) {
		printf("Ya!\n");
	}
	else {
		printf("Tidak!\n");
	}
	printf("Apakah Jam 1 != Jam 2? ");
	if (JNEQ(J1, J2)) {
		printf("Ya!\n");
	}
	else {
		printf("Tidak!\n");
	}
	printf("Apakah Jam 1 < Jam 2? ");
	if (JLT(J1, J2)) {
		printf("Ya!\n");
	}
	else {
		printf("Tidak!\n");
	}
	printf("Apakah Jam 1 > Jam 2? ");
	if (JGT(J1, J2)) {
		printf("Ya!\n");
	}
	else {
		printf("Tidak!\n");
	}
	printf("Operator Aritmatika JAM\n");
	printf("Masukkan Jam :\n");
	BacaJAM(&J);
	printf("Masukkan Detik :\n");
	scanf("%d", &S);
	printf("Satu detik setelah ini adalah ");
	TulisJAM( NextDetik(J));
	printf("\n%d detik setelah ini adalah ", S);
	TulisJAM( NextNDetik(J, S));
	printf("\nSatu detik sebelum ini adalah ");
	TulisJAM( PrevDetik(J));
	printf("\n%d detik sebelum ini adalah ", S);
	TulisJAM( PrevNDetik(J, S));
	printf("\nKelompok Operator Aritmatika\n");
	printf("Masukkan Jam Awal :\n");
	BacaJAM(&J1);
	printf("Masukkan Jam Akhir :\n");
	BacaJAM(&J2);
	printf("Durasinya adalah %d detik\n", Durasi(J1, J2));
	printf("Mengecek waktu saat ini\n");
	GetCurrentTime(&J, &D);
	TulisTANGGAL(D);
	printf(" ");
	TulisJAM(J);
	printf("\n");

	return 0;	
}
