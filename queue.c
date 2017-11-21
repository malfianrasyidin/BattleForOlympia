/* File : queue.c */
/*
NIM				: 135161098
Nama			: Rifqi Rifaldi Utomo
Tanggal			: 28 September 2017
Topik praktikum	: Array Statik Eksplisit
Deskripsi		: 
 Realisasi ADT Queue dengan representasi array secara eksplisit dan alokasi dinamik
 Model Implementasi Versi III dengan circular buffer */

#include "boolean.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

/* ********* Prototype ********* */
boolean IsEmpty (Queue Q)
/* Mengirim true jika Q kosong: lihat definisi di atas */
{	/* ALGORTIMA */
	return ((Head(Q) == Nil) && (Tail(Q) == Nil));
}

boolean IsFull (Queue Q)
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */
{	/* ALGORTIMA */
	return ((Head(Q) == (Tail(Q) + 1)) || ((Head(Q) == 1) && (Tail(Q) == MaxEl(Q))));
}

int NBElmt (Queue Q)
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */
{	/* ALGORTIMA */
	if (IsEmpty(Q)) {
		return 0;
	}
	else if (Tail(Q) > Head(Q)) {
		return (Tail(Q) - Head(Q) + 1);
	}
	else {
		return (MaxEl(Q) - Head (Q) + 1 + Tail(Q));
	}
}


/* *** Kreator *** */
void CreateEmpty (Queue * Q, int Max)
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */
{	/* ALGORTIMA */
	(* Q).T = (infotype *) malloc ((Max + 1) * sizeof(infotype));
	if ((*Q).T != NULL) {
		MaxEl(*Q) = Max;
		Head(*Q) = Nil;
		Tail(*Q) = Nil;
	}
	else {
	MaxEl(*Q) = 0;
	}
}


/* *** Destruktor *** */
void DeAlokasi(Queue * Q)
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */
{	/* ALGORTIMA */
    MaxEl(* Q) = 0;
    free((* Q).T);
}


/* *** Primitif Add/Delete *** */
void Add (Queue * Q, infotype X)
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */
{	/* ALGORTIMA */
	if (IsEmpty(* Q)) {
		Head(* Q) = 1;
		Tail(* Q) = 1;
	}
	else if (Tail(* Q) == MaxEl(* Q)) {
		Tail(* Q) = 1;
	}
	else {
		Tail(* Q) = Tail(* Q) + 1;
	}
	InfoTail(* Q) = X;
}

void Del (Queue * Q, infotype * X)
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer; 
        Q mungkin kosong */
{	/* ALGORTIMA */
	(* X) = InfoHead(* Q);
	if (NBElmt(* Q) == 1) {
		Head(* Q) = 0;
		Tail(* Q) = 0;
	}
	else if (Head(* Q) == MaxEl(* Q)) {
		Head(* Q) = 1;
	}
	else {
		++Head(* Q);
	}
}

void CreateTurn (Queue * Q) {
	/* Membuat turn dengan urutan 1 dan 2 */
	/* ALGORITMA */
	CreateEmpty(Q, 2);
	Add(Q, 1);
	Add(Q, 2);
}

void NextTurn (Queue * Q) {
	/* Mengubah head -> tail dan tail -> head */
	infotype X;
	/* ALGORITMA */
	Del(Q, &X);
	Add(Q. &X);
}

int CurrentTurn (Queue Q) {
	/* Mengambilkan turn saat ini */
	return InfoTail(Q);
}