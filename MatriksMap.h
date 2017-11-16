 /* *********** Definisi TYPE MATRIKS dengan indeks dan elemen integer ********** */
#ifndef MATRIKSMAP_H
#define MATRIKSMAP_H

#include "boolean.h"
#include "unit.h"
#include "point.h"

/* Ukuran minimum dan maksimum baris dan kolom */
#define BrsMin 1
#define BrsMax 100
#define KolMin 1
#define KolMax 100

typedef int indeks; /* indeks baris, kolom */

typedef struct {
	int Owner;
	char Tipe;
} Build;

/* *** Selektor Build *** */
#define OwnerB(B) (B).Owner
#define TipeB(B) (B).Tipe

typedef struct{
	Build Building;
	Unit Res;
} Location;

typedef Location ElType; 

typedef struct { 
	ElType Mem[BrsMax+1][KolMax+1];
  int NBrsEff; /* banyaknya/ukuran baris yg terdefinisi */
	int NKolEff; /* banyaknya/ukuran kolom yg terdefinisi */
} MatriksMap;
/* NBrsEff <= 1 dan NKolEff <= 1 */
/* Indeks matriks yang digunakan: [BrsMin..BrsMax][KolMin..KolMax] */
/* Memori matriks yang dipakai selalu di "ujung kiri atas" */

/* *** Selektor MatriksMap *** */
#define NBrsEff(M) (M).NBrsEff
#define NKolEff(M) (M).NKolEff
#define Elmt(M,i,j) (M).Mem[(i)][(j)]
#define BuildIn(L) (L).Building
#define UnitIn(L) (L).Res



/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */              
/* *** Konstruktor membentuk MATRIKS *** */
void MakeMATRIKS (int NB, int NK, MatriksMap * M); 
/* Membentuk sebuah MATRIKS "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */

/* *** Selektor "DUNIA MATRIKS" *** */
boolean IsIdxInMap (int i, int j);
/* Mengirimkan true jika i, j adalah indeks yang valid untuk matriks apa pun */

/* *** Selektor: Untuk sebuah matriks M yang terdefinisi: *** */
indeks GetFirstIdxBrs (MatriksMap M);
/* Mengirimkan indeks baris terkecil M */
indeks GetFirstIdxKol (MatriksMap M);
/* Mengirimkan indeks kolom terkecil M */
indeks GetLastIdxBrs (MatriksMap M);
/* Mengirimkan indeks baris terbesar M */
indeks GetLastIdxKol (MatriksMap M);
/* Mengirimkan indeks kolom terbesar M */
boolean IsIdxEff (MatriksMap M, indeks i, indeks j);
/* Mengirimkan true jika i, j adalah indeks efektif bagi M */
ElType GetElmtDiagonal (MatriksMap M, indeks i);
/* Mengirimkan elemen M(i,i) */


Build NullBuilding();
//mengembalikan definisi building kosong

boolean IsBuildIn (POINT P, MatriksMap M);
//Mengembalikan true jika ada build di titik P.

boolean IsUnitIn (POINT P, MatriksMap M);
//Mengembalikan true jika ada unit di L dan false jika tidak

Unit getUnit(POINT P, MatriksMap M);
//Mengembalikan unit yang berada di titik P.

Build getBuild(POINT P, MatriksMap M);
//Mengembalikan build yang berada di titik P.

char AbbrevUnit(char* Tipe);
//Mengembalikan singkatan dari unit yang akan ditampilkan di peta.

/* ********** Operasi lain ********** */
void PrintMap(MatriksMap M);
/*Memprint Peta yang terdapat pada Matriks M*/

MatriksMap MatGen(indeks NB, indeks NK);
/*Mengenerate Peta Baru*/

int NBElmt (MatriksMap M);
/* Mengirimkan banyaknya elemen M */


#endif

