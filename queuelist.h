/* File : queuelist.h */
/* Representasi queue dengan list berkait dengan first (HEAD) dan last (TAIL) */
#ifndef _QUEUELIST_H
#define _QUEUELIST_H
#include "boolean.h"
#include "point.h"
#include <stdlib.h>

/* Konstanta */
#define Nil NULL

/* Deklarasi infotype */
typedef POINT infotypeQU;

/* Queue dengan representasi berkait dengan pointer */
typedef struct tElmtQueueU * addressQU;
typedef struct tElmtQueueU { 
	infotypeQU Info;
	addressQU Next; 
} ElmtQueue; 

/* Type queue dengan ciri HEAD dan TAIL : */
typedef struct { 
	addressQU HEAD;  /* alamat penghapusan */
	addressQU TAIL;  /* alamat penambahan */
} QueueU;

/* Selektor */
#define Head(Q) (Q).HEAD
#define Tail(Q) (Q).TAIL
#define InfoHeadQU(Q) (Q).HEAD->Info
#define InfoTailQU(Q) (Q).TAIL->Info
#define NextQU(P) (P)->Next
#define InfoQU(P) (P)->Info

/* Prototype manajemen memori */
void AlokasiU (addressQU *P, infotypeQU X);
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka Info(P)=X dan 
        Next(P)=Nil */
/*      P=Nil jika alokasi gagal */
void DealokasiU (addressQU  P);
/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */
boolean IsEmptyUQ (QueueU Q);
/* Mengirim true jika Q kosong: HEAD(Q)=Nil and TAIL(Q)=Nil */
boolean IsOneElmtUQ(QueueU Q);
/* Mengirim True jika Q hanya memiliki 1 elemen*/
int NbElmtUQ(QueueU Q);
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong */
/*** Kreator ***/
void CreateEmptyUQ(QueueU * Q);
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk */
/*** Primitif Add/Delete ***/
void AddQU (QueueU * Q, infotypeQU X);
/* Proses: Mengalokasi X dan menambahkan X pada bagian TAIL dari Q
   jika alokasi berhasil; jika alokasi gagal Q tetap */
/* Pada dasarnya adalah proses insert last */
/* I.S. Q mungkin kosong */
/* F.S. X menjadi TAIL, TAIL "maju" */
void DelQU(QueueU * Q, infotypeQU * X);
/* Proses: Menghapus X pada bagian HEAD dari Q dan mendealokasi
   elemen HEAD */
/* Pada dasarnya operasi delete first */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "mundur" */
void RoundP(QueueU *Q);
/*Proses : Memindahkan Nilai Tail Queue ke Head Queue dan Head Queue ke 
  Elemen setelahnya. */

#endif
