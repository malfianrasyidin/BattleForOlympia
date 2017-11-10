#include "listsirkuler.h"
#include "boolean.h"
#include <stdlib.h>
#include <stdio.h>


/****************** TEST LIST KOSONG ******************/
boolean IsEmpty (List L){
/* Mengirim true jika list kosong. Lihat definisi di atas. */
	return(First(L) == Nil);
}

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmpty (List *L){
/* I.S. L sembarang             */
/* F.S. Terbentuk list kosong. Lihat definisi di atas. */
	First(*L) = Nil;
}

/****************** Manajemen Memori ******************/
address Alokasi (infotype X){
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
	address P;
	P = (address) malloc(sizeof(ElmtList));
	if (P != Nil){
		Info(P) = X;
		Next(P) = Nil;
		return(P);
	}
	else {
		return(Nil);
	}
}
void Dealokasi (address P){
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
	free(P);
}

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
address Search (List L, infotype X){
/* Mencari apakah ada elemen list dengan Info(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
	if (IsEmpty(L)){
		return(Nil);
	}
	else {
		boolean found = false;
		address P = First(L);
		do {
			found = X == Info(P);
			if (!found){
				P = Next(P);
			}
		} while ((P != First(L)) && (!found));
		if (found){
			return(P);
		}
		else {
			return(Nil);
		}
	}
}

/****************** SELEKTOR TAMBAHAN ***************************/
address getLast(List L){
	if (Next(First(L)) == First(L)){
		return(First(L));
	}
	else{
		address P = First(L);
		while (Next(P) != First(L)){
			P = Next(P);
		}
		return(P);
	}
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirst (List *L, infotype X){
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
	address P = Alokasi(X);
	if (P){
		InsertFirst(&*L,P);
	}
}
void InsVLast (List *L, infotype X){
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
	address P = Alokasi(X);
	if (P){
		InsertLast(&*L,P);
	}
}

/*** PENGHAPUSAN ELEMEN ***/
void DelVFirst (List *L, infotype * X){
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
	address P;
	DelFirst(&*L,&P);
	*X = Info(P);
	Dealokasi(P);
}
void DelVLast (List *L, infotype * X){
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
	address P;
	DelLast(&*L,&P);
	*X = Info(P);
	Dealokasi(P);
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst (List *L, address P){
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
	if (IsEmpty(*L)){
		Next(P) = P;
		First(*L) = P;
	}
	else {
		Next(P) = First(*L);
		address PTemp = getLast(*L);
		First(*L) = P;
		Next(PTemp) = First(*L);
	}
}
void InsertLast (List *L, address P){
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
	if (IsEmpty(*L)){
		First(*L) = P;
		Next(P) = P;
	}
	else {
		Next(P) = First(*L);
		address PLst = getLast(*L);
		Next(PLst) = P;
	}
}
void InsertAfter (List *L, address P, address Prec){
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
	Next(P) = Next(Prec);
	Next(Prec) = P;
}
/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst (List *L, address *P){
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
	*P = First(*L);
	if(Next(*P) == *P){
		First(*L) = Nil;
	}
	else{
		address PTmp = getLast(*L);
		Next(PTmp) = Next(*P);
		First(*L) = Next(*P);
		Next(*P) = *P;
	}
}
void DelLast (List *L, address *P){
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, */
/* jika ada */
	*P = First(*L);
	if (Next(First(*L)) == First(*L)){
		First(*L) = Nil;
	}
	else {
		address Prv = *P;
		*P = Next(*P);
		while (Next(*P) != First(*L)){
			Prv = *P;
			*P = Next(*P);
		}
		Next(Prv) = First(*L);
	}
}

void DelAfter (List *L, address *Pdel, address Prec){
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
	*Pdel = Next(Prec);
	if (*Pdel == First(*L)){
		DelFirst(&*L,&*Pdel);
	}
	else {
		Next(Prec) = Next(*Pdel);
		Next(*Pdel) = *Pdel;
	}
}
void DelP (List *L, infotype X){
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan Info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
	address P = First(*L);
	address Prev = Nil;
	boolean found = false;
	do {
		found = X == Info(P);
		if(!found){
			Prev = P;
			P = Next(P);
		}
	}while ((P != First(*L)) && (!found));
	if ((found) && (P ==  First(*L))){
		DelFirst(&*L,&P);
		Dealokasi(P);
	}
	else if (found){
		DelAfter(&*L, &P, Prev);
		Dealokasi(P);
	}
}
/****************** PROSES SEMUA ELEMEN LIST ******************/
void PrintInfo (List L){
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
	printf("[");
	if (!IsEmpty(L)){
		address P = First(L);
		while (Next(P) != First(L)){
			printf("%d,",Info(P));
			P = Next(P);
		}
		printf("%d",Info(P));
	}
	printf("]");
}
