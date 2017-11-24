#include "queuelist.h"
#include "boolean.h"
#include <stdlib.h>


void AlokasiU (addressQU *P, infotypeQU X){
/* I.S. Sembarang */
/* F.S. Alamat P diAlokasiQL, jika berhasil maka Info(P)=X dan 
        Next(P)=Nil */
/*      P=Nil jika AlokasiQL gagal */
	*P = (addressQU) malloc(sizeof(ElmtQueue));
	if (*P != Nil){
		InfoQU(*P) = X;
		NextQU(*P) = *P;
	}
	else {
		*P = Nil;
	}
}
void DeAlokasiU (addressQU  P){
/* I.S. P adalah hasil AlokasiQL, P != Nil */
/* F.S. Alamat P dideAlokasiQL, dikembalikan ke sistem */
	free(P);
}
boolean IsEmptyUQ (QueueU Q){
/* Mengirim true jika Q kosong: HEAD(Q)=Nil and TAIL(Q)=Nil */
	return(Head(Q) == Nil);
}

boolean IsOneElmtUQ(QueueU Q){
/* Mengirim True jika Q hanya memiliki 1 elemen*/
	return(Head(Q) == Tail(Q));
}

int NbElmtUQ(QueueU Q){
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong */
	addressQU P = Head(Q);
	if (!P){
		return(0);
	}
	else{
		int count = 1;
		P = NextQU(P);
		while(P != Head(Q)){
			count++;
			P = NextQU(P);
		}
	return(count);
	}
}
/*** Kreator ***/
void CreateEmptyUQ(QueueU * Q){
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk */
	Head(*Q) = Nil;
	Tail(*Q) = Nil;
}
/*** Primitif AddQLQL/Delete ***/
void AddQU (QueueU * Q, infotypeQU X){
/* Proses: MengAlokasiQL X dan menambahkan X pada bagian TAIL dari Q
   jika AlokasiQLQL berhasil; jika AlokasiQL gagal Q tetap */
/* Pada dasarnya adalah proses insert last */
/* I.S. Q mungkin kosong */
/* F.S. X menjadi TAIL, TAIL "maju" */
	addressQU P;
	AlokasiU(&P,X);
	if(IsEmptyUQ(*Q)){
		Head(*Q) = P;
		Tail(*Q) = P;
	}
	else {
		NextQU(Tail(*Q)) = P;
		NextQU(P) = Head(*Q);
		Tail(*Q) = P;
	}
}
void DelQU(QueueU * Q, infotypeQU * X){
/* Proses: Menghapus X pada bagian HEAD dari Q dan mendeAlokasiQL
   elemen HEAD */
/* Pada dasarnya operasi delete first */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "mundur" */
	addressQU P = Head(*Q);
	if (Head(*Q) == Tail(*Q)){
		Head(*Q) = Nil;
		Tail(*Q) = Nil;
	}
	else {
		Head(*Q) = NextQU(P);
		NextQU(Tail(*Q)) = Head(*Q);
		NextQU(P) = P;
	}
	*X = InfoQU(P);
	DeAlokasiU(P);
}
void RoundP(QueueU *Q){
	/*Proses : Memindahkan Nilai Tail Queue ke Head Queue dan Head Queue ke 
	  Elemen setelahnya. */
	Tail(*Q) =  Head(*Q);
	Head(*Q) =  NextQU(Head(*Q));
}
