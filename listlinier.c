#include "listlinier.h"
#include "boolean.h"
#include <stdlib.h>
#include <stdio.h>


/****************** TEST LIST KOSONG ******************/
boolean IsEmpty (List L){
/* Mengirim true jika list kosong */
	return(First(L) == Nil);
}

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmpty (List *L){
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
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
void Dealokasi (address *P){
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
	free(*P);
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
		while ((P != Nil) && (!found)){
			found = Info(P) == X;
			if (!found){
				P = Next(P);
			}
		}
		if(!found){
			return(Nil);
		}
		else {
			return(P);
		}
	}
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirst (List *L, infotype X){
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
	address P = Alokasi(X);
	if (P != Nil){
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
void DelVFirst (List *L, infotype *X){
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
	address P;
	DelFirst(&*L,&P);
	*X = Info(P);
	Dealokasi(&P);
}

void DelVLast (List *L, infotype *X){
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
	address P;
	DelLast(&*L,&P);
	*X = Info(P);
	Dealokasi(&P);
}

/****************** SELEKTOR TAMBAHAN ****************************/

address getLast(List L){
	address P = First(L);
	while (Next(P)){
		P = Next(P);
	}
	return(P);
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst (List *L, address P){
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
	if (IsEmpty(*L)){
		Next(P) = Nil;
	}
	else {
		Next(P) = First(*L);
	}
	First(*L) = P;
}
void InsertAfter (List *L, address P, address Prec){
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
	Next(P) =  Next(Prec);
	Next(Prec) = P;
}
void InsertLast (List *L, address P){
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
	if (IsEmpty(*L)){
		InsertFirst(&*L,P);
	}
	else {
		address Ptemp = getLast(*L);
		Next(Ptemp) = P;
	}
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst (List *L, address *P){
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
	*P = First(*L);
	if (IsEmpty(*L)){
		First(*L) = Nil;
	}
	else {
		First(*L) = Next(*P);
	}
	Next(*P) = Nil;
}
void DelP (List *L, infotype X){
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan Info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
	boolean found = false;
	address P = First(*L);
	address Prec = Nil;
	while ((P != Nil) && (!found)){
		found = Info(P) == X;
		if (!found){
			Prec = P;
			P = Next(P);
		}
	}
	if(found){
		if (P == First(*L)){
			DelFirst(&*L,&P);
		}
		else if (Next(P) == Nil){
			DelLast(&*L,&P);
		}
		else {
			DelAfter(&*L,&P,Prec);
		}
	}
}
void DelLast (List *L, address *P){
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, */
/* jika ada */
	if (Next(First(*L))){
		*P = First(*L);
		address Prec;
		while (Next(*P)){
			Prec = *P;
			*P = Next(*P);
		}
		Next(Prec) = Nil;
	}
	else {
		DelFirst(&*L,&*P);
	}
}

void DelAfter (List *L, address *Pdel, address Prec){
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
	*Pdel = Next(Prec);
	Next(Prec) = Next(*Pdel);
	Next(*Pdel) = Nil;
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
void PrintInfo (List L){
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
	address P = First(L);
	printf("[");
	if (!IsEmpty(L)){
		while(P){
			printf("%d",Info(P));
			if (Next(P) != Nil){
				printf(",");
			}
			P = Next(P);
		}
	}
	printf("]");
}

int NbElmt (List L){
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
	address P = First(L);
	int count = 0;
	while(P){
		count++;
		P = Next(P);
	}
	return(count);
}

/*** Prekondisi untuk Max/Min/rata-rata : List tidak kosong ***/
infotype Max (List L){
	address P = Next(First(L));
	infotype Mx = Info(First(L));
	while(P){
		if (Mx < Info(P)){
			Mx = Info(P);
		}
		P = Next(P);
	}
	return(Mx);
}
/****************** PROSES TERHADAP LIST ******************/
void Konkat1 (List *L1, List *L2, List *L3){
/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 kosong, L3 adalah hasil konkatenasi L1 & L2 */
/* Konkatenasi dua buah list : L1 dan L2    */
/* menghasilkan L3 yang baru (dengan elemen list L1 dan L2) */
/* dan L1 serta L2 menjadi list kosong.*/
/* Tidak ada alokasi/dealokasi pada prosedur ini */
	if(!IsEmpty(*L1)){
		*L3 = *L1;
		address P = getLast(*L3);
		Next(P) = First(*L2);
	}
	else {
		*L3 = *L2;
	}
	CreateEmpty(&*L1);
	CreateEmpty(&*L2);
}
