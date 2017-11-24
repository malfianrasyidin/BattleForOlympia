#include "listdpUnit.h"
#include <stdio.h>
#include <stdlib.h>
#include "unit.h"
#include "point.h"
#include "MatriksMap.h"

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsEmptyList (List L)
/* Mengirim true jika list kosong. Lihat definisi di atas. */
{
	return ((First(L)==Nil)&&(Last(L)==Nil));
}

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmptyList (List *L)
/* I.S. L sembarang  */
/* F.S. Terbentuk list kosong. Lihat definisi di atas. */
{
	First(*L)=Nil;
	Last(*L)=Nil;
}

/****************** Manajemen Memori ******************/
addressList Alokasi (infotype X)
/* Mengirimkan addressList hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addressList tidak nil. */
/* Misalnya: menghasilkan P, maka Info(P)=X, Next(P)=Nil, Prev(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil. */
{
	addressList p;
	p = (addressList) malloc (sizeof(ElmtList));
	if (p) {
		Info(p)=X;
		Next(p)=Nil;
		Prev(p)=Nil;
	} else {
		p = Nil;
	}
	return p;
}
void Dealokasi (addressList P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addressList P */
{
	free(P);
}

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
addressList Search (List L, infotype X)
/* Mencari apakah ada elemen list dengan Info(P)=X */
/* Jika ada, mengirimkan addressList elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
{
	if (IsEmptyList(L)) {
		return Nil;
	} else {
		addressList P = First(L);
		while ((Next(P)!=Nil) && (!EQ(Info(P),X))) {
			P=Next(P);
		}
		if (!EQ(Info(P),X)) {
			return Nil;
		} else {
			return P;
		}
	}
}

int NbElmtList (List L)
{
	int count;	
	if (IsEmptyList(L)) {
		count = 0;
	} else {
		addressList P = First(L);
		while (P != Nil) {
			count++;
		}
		P = Next(P);
	}
	return count;
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirst (List *L, infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
	addressList P = Alokasi(X);
	if (P!=Nil) {
		InsertFirst(L,P);
	}
}
void InsVLast (List *L, infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
	addressList P = Alokasi(X);
	if (P!=Nil) {
		InsertLast(L,P);
	}
}

/*** PENGHAPUSAN ELEMEN ***/
void DelVFirst (List *L, infotype *X)
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
{
	addressList P;
	DelFirst (L,&P);
	*X = Info(P);
	Dealokasi(P);
}
void DelVLast (List *L, infotype *X)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
{
	addressList P;
	DelLast (L,&P);
	*X = Info(P);
	Dealokasi(P);
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst (List *L, addressList P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-addressList P sebagai elemen pertama */
{
	if (IsEmptyList(*L)) {
		First(*L) = P;
		Last(*L) = P;
		Next(First(*L))=Nil;
		Prev(Last(*L))=Nil;
	} else {
		Prev(First(*L))=P;
		Next(P)=First(*L);
		Prev(P)=Nil;
		First(*L)=P;
	}
}
void InsertLast (List *L, addressList P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
{
	if (IsEmptyList(*L)) {
		First(*L) = P;
		Last(*L) = P;
		Next(First(*L))=Nil;
		Prev(Last(*L))=Nil;
	} else {
		Next(Last(*L))=P;
		Prev(P)=Last(*L);
		Next(P)=Nil;
		Last(*L)=P;
	}
}
void InsertAfter (List *L, addressList P, addressList Prec)
/* I.S. Prec pastilah elemen list; P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
{
	Next(P)=Next(Prec);
	Prev(P)=Prec;
	Next(Prec)=P;
	if (Next(P)!=Nil) {
		Prev(Next(P))=P;
	} else {
		Last(*L)=P;
	}
}
void InsertBefore (List *L, addressList P, addressList Succ)
/* I.S. Succ pastilah elemen list; P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sebelum elemen beralamat Succ */
{
	Prev(P)=Prev(Succ);
	Next(P)=Succ;
	Prev(Succ)=P;
	if (Prev(P)!=Nil) {
		Next(Prev(P))=P;
	} else {
		First(*L)=P;
	}
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst (List *L, addressList *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
{
	*P = First(*L);
	if (First(*L) == Last(*L)) {
		First(*L) = Nil;
		Last(*L) = Nil;
	} else {
		First(*L) = Next(First(*L));
		Prev(First(*L)) = Nil;
	}
	Next(*P) = Nil;
	Prev(*P) = Nil;
}
void DelLast (List *L, addressList *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, jika ada */
{
	*P = Last(*L);
	if (First(*L) == Last(*L)) {
		First(*L) = Nil;
		Last(*L) = Nil;
	} else {
		Last(*L) = Prev(Last(*L));
		Next(Last(*L)) = Nil;
	}
	Next(*P) = Nil;
	Prev(*P) = Nil;
}
void DelP (List *L, infotype X)
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddressList P, dengan Info(P)=X  */
/* maka P dihapus dari list dan didealokasi */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
{
	if (!IsEmptyList(*L)) {
		addressList P,Q;
		infotype Y;
		boolean stop = false;
		while (!stop) {
			if (EQ(Info(First(*L)),X)) {
				DelVFirst(L,&Y);
				stop = IsEmptyList(*L);
			} else {
				stop = true;
			}
		}
		if (!IsEmptyList(*L)) {
			P = First(*L);
			while (Next(P)!=Nil) {
				if (EQ(Info(Next(P)),X)) {
					DelAfter(L,&Q,P);
					Dealokasi(Q);
				} else {
					P = Next(P);
				}
			}
		}
	}
}
void DelAfter (List *L, addressList *Pdel, addressList Prec)
/* I.S. List tidak kosong. Prec adalah anggota list. */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
{
	*Pdel=Next(Prec);
	if (*Pdel!=Nil) {
		Next(Prec) = Next(Next(Prec));
		if (Next(Prec)==Nil) {
			Last(*L)=Prec;
		} else {
			Prev(Next(Prec))=Prec;
		}
		Next(*Pdel)=Nil;
		Prev(*Pdel)=Nil;
	}
}

void DelBefore (List *L, addressList *Pdel, addressList Succ)
/* I.S. List tidak kosong. Succ adalah anggota list. */
/* F.S. Menghapus Prev(Succ): */
/*      Pdel adalah alamat elemen list yang dihapus  */
{
	*Pdel=Prev(Succ);
	if (*Pdel!=Nil) {
		Prev(Succ) = Prev(Prev(Succ));
		if (Prev(Succ)==Nil) {
			First(*L)=Succ;
		} else {
			Next(Prev(Succ))=Succ;
		}
		Next(*Pdel)=Nil;
		Prev(*Pdel)=Nil;
	}	
}