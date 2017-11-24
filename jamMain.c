/* File: jam_driver.c */
/* Tanggal: 31 Agustus 2017 */
/* Driver ADT JAM */

#include "jam.h"
#include <stdio.h>

int main () {
	JAM J, J1, J2;
	long S;
	TANGGAL D;
	printf("--This is a driver for ADT Jam--\n");
	printf("KELOMPOK BACA/TULIS\n");
	printf("Masukkan Jam yang salah [Jam Menit Detik]: ");
	BacaJAM(&J);
	printf("Jam yang Anda tulis adalah : ");
	TulisJAM(J);
	printf("\nKELOMPOK KONVERSI TERHADAP TYPE\n");
	printf("Konversi Jam ke Detik");
	printf("Masukkan Jam [Jam Menit Detik] : ");
	BacaJAM(&J);
	printf("Jika dikonversi ke detik menjadi %ld detik\n", JAMToDetik(J));
	printf("Masukkan Detik : ");
	scanf("%ld", &S);
	printf("Jika dikonversi ke jam menjadi ");
	TulisJAM(DetikToJAM(S));
	printf("\nKELOMPOK OPERASI TERHADAP TYPE\n");
	printf("Masukkan Jam 1 [Jam Menit Detik]: ");
	BacaJAM(&J1);
	printf("Masukkan Jam 2 [Jam Menit Detik]: ");
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
	printf("Masukkan Jam [Jam Menit Detik]: ");
	BacaJAM(&J);
	printf("Masukkan Detik :");
	scanf("%ld", &S);
	printf("Satu detik setelah ini adalah ");
	TulisJAM( NextDetik(J));
	printf("\n%ld detik setelah ini adalah ", S);
	TulisJAM( NextNDetik(J, S));
	printf("\nSatu detik sebelum ini adalah ");
	TulisJAM( PrevDetik(J));
	printf("\n%ld detik sebelum ini adalah ", S);
	TulisJAM( PrevNDetik(J, S));
	printf("\nKelompok Operator Aritmatika\n");
	printf("Masukkan Jam Awal [Jam Menit Detik]: ");
	BacaJAM(&J1);
	printf("Masukkan Jam Akhir : ");
	BacaJAM(&J2);
	printf("Durasinya adalah %ld detik\n", Durasi(J1, J2));
	GetCurrentTime(&J, &D);
	printf("Tanggal saat ini adalah ");
	TulisTANGGAL(D);
	printf("\n");
	printf("Waktu saat ini adalah ");
	TulisJAM(J);
	printf("\n");

	return 0;	
}
