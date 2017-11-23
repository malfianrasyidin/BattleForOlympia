#include "listdpUnit.h"
#include "stdio.h"
#include "stdlib.h"
#include "unit.h"
#include "MatriksMap.h"

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsEmpty (List L)
/* Mengirim true jika list kosong. Lihat definisi di atas. */
{
	return ((First(L)==Nil)&&(Last(L)==Nil));
}

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmpty (List *L)
/* I.S. L sembarang  */
/* F.S. Terbentuk list kosong. Lihat definisi di atas. */
{
	First(*L)=Nil;
	Last(*L)=Nil;
}

/****************** Manajemen Memori ******************/
address Alokasi (infotype X)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil. */
/* Misalnya: menghasilkan P, maka Info(P)=X, Next(P)=Nil, Prev(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil. */
{
	address p;
	p = (address) malloc (sizeof(ElmtList));
	if (p) {
		Info(p)=X;
		Next(p)=Nil;
		Prev(p)=Nil;
	} else {
		p = Nil;
	}
	return p;
}
void Dealokasi (address P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
{
	free(P);
}

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
address Search (List L, infotype X)
/* Mencari apakah ada elemen list dengan Info(P)=X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
{
	if (IsEmpty(L)) {
		return Nil;
	} else {
		address P = First(L);
		while ((Next(P)!=Nil) && (!CmpUnit(Info(P),X))) {
			P=Next(P);
		}
		if (!CmpUnit(Info(P),X)) {
			return Nil;
		} else {
			return P;
		}
	}
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirst (List *L, infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
	address P = Alokasi(X);
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
	address P = Alokasi(X);
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
	address P;
	DelFirst (L,&P);
	*X = Info(P);
	Dealokasi(P);
}
void DelVLast (List *L, infotype *X)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
{
	address P;
	DelLast (L,&P);
	*X = Info(P);
	Dealokasi(P);
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst (List *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
{
	if (IsEmpty(*L)) {
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
void InsertLast (List *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
{
	if (IsEmpty(*L)) {
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
void InsertAfter (List *L, address P, address Prec)
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
void InsertBefore (List *L, address P, address Succ)
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
void DelFirst (List *L, address *P)
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
void DelLast (List *L, address *P)
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
/* F.S. Jika ada elemen list beraddress P, dengan Info(P)=X  */
/* maka P dihapus dari list dan didealokasi */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
{
	if (!IsEmpty(*L)) {
		address P,Q;
		infotype Y;
		boolean stop = false;
		while (!stop) {
			if (CmpUnit(Info(First(*L)),X)) {
				DelVFirst(L,&Y);
				stop = IsEmpty(*L);
			} else {
				stop = true;
			}
		}
		if (!IsEmpty(*L)) {
			P = First(*L);
			while (Next(P)!=Nil) {
				if (CmpUnit(Info(Next(P)),X)) {
					DelAfter(L,&Q,P);
					Dealokasi(Q);
				} else {
					P = Next(P);
				}
			}
		}
	}
}
void DelAfter (List *L, address *Pdel, address Prec)
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

void DelBefore (List *L, address *Pdel, address Succ)
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

/****************** PROSES SEMUA ELEMEN LIST ******************/
void PrintListUnit (List L)
/* I.S. List mungkin kosong */
/* F.S. 
== List of Units ==
1. King (2,1) | Health 20
2. Swordsman (3,5) | Health 20
*/
{
	printf("== List Of Unit ==");
	address p = First(L);
	int i=1;
	while (p!=Nil) {
		printf("%d. ",i);
		printf("Unit: %s (%d,%d) | ", Tipe(Info(p)), Absis(Locate(Info(p))), Ordinat(Locate(Info(p))));
		printf("Health: %d | ", HP(Info(p)));
		if (Next(p)!=Nil) {printf("\n");}
		p = Next(p);
	}
}

List EnemyCanBeAttacked(Unit U, MatriksMap M){
//Mengembalikan List enemy yg bisa di attack.	
	boolean Top, Bottom, Right, Left;
	POINT PTop,PBottom, PRight, PLeft;
	List L;
	CreateEmpty(&L);
	PTop = NextY(Locate(U));
	PRight = NextX(Locate(U));
	PLeft = PlusDelta(Locate(U), -1, 0);
	PBottom = PlusDelta(Locate(U), 0, -1);
	Top = IsUnitIn(PTop,M) && IsEnemy(U,getUnit(PTop,M));
	if (Top)	InsVFirst(&L,getUnit(PTop,M));	
	Bottom = IsUnitIn(PBottom,M) && IsEnemy(U,getUnit(PBottom,M));
	if (Bottom)	InsVFirst(&L,getUnit(PBottom,M));
	Right = IsUnitIn(PRight,M) && IsEnemy(U,getUnit(PRight,M));
	if (Right)	InsVFirst(&L,getUnit(PRight,M));
	Left = IsUnitIn(PLeft,M) && IsEnemy(U,getUnit(PLeft,M));
	if (Left)	InsVFirst(&L,getUnit(PLeft,M));
	return (L);
}