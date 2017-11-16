#include "MatriksMap.h"
#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "unit.h"
#include "point.h"

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */              

/* *** Konstruktor membentuk MATRIKS *** */
void MakeMATRIKS (int NB, int NK, MatriksMap * M){
/* Membentuk sebuah MATRIKS "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk  */
	NBrsEff(*M) = NB;
	NKolEff(*M) = NK;
	for (int i = 1; i <= NB; i++){
		for (int j = 1; j <=NK ; j++){
			Elmt(*M,i,j).Building = NullBuilding();
			Elmt(*M,i,j).Res = NullUnit();
		}
	}
}


/* *** Selektor "DUNIA MATRIKS" *** */
boolean IsIdxValid (int i, int j){
/* Mengirimkan true jika i, j adalah indeks yang valid untuk matriks apa pun */
	return((( BrsMax >= i) && (KolMax >= j)) && ((BrsMin <= i) && (KolMin <= j)));
}

/* *** Selektor: Untuk sebuah matriks M yang terdefinisi: *** */
indeks GetFirstIdxBrs (MatriksMap M){
/* Mengirimkan indeks baris terkecil M */
	return(BrsMin);
}
indeks GetFirstIdxKol (MatriksMap M){
/* Mengirimkan indeks kolom terkecil M */
	return(KolMin);
}
indeks GetLastIdxBrs (MatriksMap M){
/* Mengirimkan indeks baris terbesar M */
	return(NBrsEff(M));
}
indeks GetLastIdxKol (MatriksMap M){
/* Mengirimkan indeks kolom terbesar M */
	return(NKolEff(M));
}
boolean IsIdxEff (MatriksMap M, indeks i, indeks j){
/* Mengirimkan true jika i, j adalah indeks efektif bagi M */
	return ((IsIdxValid(i,j)) && (( i <= NBrsEff(M)) && (j <= NKolEff(M))));
}
ElType GetElmtDiagonal (MatriksMap M, indeks i){
/* Mengirimkan elemen M(i,i) */
	return(Elmt(M,i,i));
}

////////////////////////////////////////////////////////////////

//FUNGSI NULLITAS
Build NullBuilding(){
//mengembalikan definisi building kosong
	Build B;
	B.Owner = 0;
	B.Tipe = ' ';
	return (B);
}

boolean IsBuildIn (POINT P, MatriksMap M){
//Mengembalikan true jika ada build di titik P.
	return (TipeB(getBuild(P,M)) != ' ');
}

boolean IsUnitIn (POINT P, MatriksMap M){
//Mengembalikan true jika ada unit di titik P.
	return (Tipe(getUnit(P,M)) != ' ');
}


Unit getUnit(POINT P, MatriksMap M){
//Mengembalikan unit yang berada di titik
	return UnitIn(Elmt(M,Absis(P),Ordinat(P)));
}

Build getBuild(POINT P, MatriksMap M)
//Mengembalikan build yang berada di titik P.
{
	return BuildIn(Elmt(M,Absis(P),Ordinat(P)));	
}

char AbbrevUnit(char* Tipe){
//Mengembalikan singkatan dari unit yang akan ditampilkan di peta.
	char X;
	X = Tipe[0];
	return X-32;
}

void PrintMap(MatriksMap M){
/*Memprint Peta M ke Layar*/
	for (int i = 1 ; i <= NBrsEff(M) ; i++){
		printf("*");
		for (int j = 1 ; j <= NKolEff(M) ; j++){
			printf("****");
		}
		printf("\n*");
		for (int j = 1 ; j <= NKolEff(M) ; j++){
			// printf("%s *", &(BuildIn(Elmt(M,i,j))).Tipe[0]);
			printf(" ");
			print_red(AbbrevUnit("tower"));
			printf(" *");
		}
		printf("\n*");
		for (int j = 1 ; j <= NKolEff(M) ; j++){
			printf(" ");
			print_green(AbbrevUnit("archer"));
			printf(" *");
			// printf("%s *", &(UnitIn(Elmt(M,i,j))).KarType[0]);
		}
		printf("\n*");
		for (int j = 1 ; j <= NKolEff(M) ; j++){
			printf(" ");
			print_blue(AbbrevUnit("king"));
			printf(" *");
		}
		printf("\n");
	}
	printf("*");
	for (int j = 1 ; j <= NKolEff(M) ; j++){
			printf("****");
	}
	printf("\n");
}

MatriksMap MatGen(indeks NB, indeks NK){
/*MengGenerate Peta yang baru dengan Random Number */
	int R;
	MatriksMap M;
	MakeMATRIKS(NB,NK, &M);
	//player 1
	BuildIn(Elmt(M,NB-1,KolMin+1)).Tipe = 'T';
	BuildIn(Elmt(M,NB-1,KolMin+1)).Owner = 1;
	POINT K1 = MakePOINT(NB-1,KolMin+1);
	UnitIn(Elmt(M,NB-1,KolMin+1)) = MakeNewUnit(4,1,K1);
	BuildIn(Elmt(M,NB-2,KolMin+1)).Tipe = 'C'; //atas
	BuildIn(Elmt(M,NB-2,KolMin+1)).Owner = 1;
	BuildIn(Elmt(M,NB-1,KolMin)).Tipe = 'C'; //kiri
	BuildIn(Elmt(M,NB-1,KolMin)).Owner = 1;
	BuildIn(Elmt(M,NB-1,KolMin+2)).Tipe = 'C'; //kanan
	BuildIn(Elmt(M,NB-1,KolMin+2)).Owner = 1;
	BuildIn(Elmt(M,NB,KolMin+1)).Tipe = 'C'; //bawah
	BuildIn(Elmt(M,NB,KolMin+1)).Owner = 1;
	//player 2
	BuildIn(Elmt(M,BrsMin+1,NK-1)).Tipe = 'T';
	BuildIn(Elmt(M,BrsMin+1,NK-1)).Owner = 2;
	POINT K2 = MakePOINT(BrsMin+1,NK-1);
	UnitIn(Elmt(M,BrsMin+1,NK-1)) = MakeNewUnit(4,2,K2);
	BuildIn(Elmt(M,BrsMin,NK-1)).Tipe = 'C'; //atas
	BuildIn(Elmt(M,BrsMin,NK-1)).Owner = 2;
	BuildIn(Elmt(M,BrsMin+1,NK-2)).Tipe = 'C'; //kiri
	BuildIn(Elmt(M,BrsMin+1,NK-2)).Owner = 2;
	BuildIn(Elmt(M,BrsMin+1,NK)).Tipe = 'C'; //kanan
	BuildIn(Elmt(M,BrsMin+1,NK-2)).Owner = 2;
	BuildIn(Elmt(M,BrsMin+2,NK-1)).Tipe = 'C'; //bawah
	BuildIn(Elmt(M,BrsMin+2,NK-1)).Owner = 2;
	
	int i,j,k;
	for (k=1; k<=3; k++)	{
		i = rand() % NB;
		j = rand() % NK;
		while (BuildIn(Elmt(M,i,j)).Tipe!=' ')	{
			i = rand() % NB;
			j = rand() % NK;
		}
		BuildIn(Elmt(M,i,j)).Tipe='V';
	}
	return(M);
}

