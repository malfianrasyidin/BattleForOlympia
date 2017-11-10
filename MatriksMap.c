#include "MatriksMap.h"
#include <stdio.h>
#include "boolean.h"

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */              
/* *** Konstruktor membentuk MATRIKS *** */
void MakeMATRIKS (int NB, int NK, MatriksMap * M){
/* Membentuk sebuah MATRIKS "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */
	NBrsEff(*M) = NB;
	NKolEff(*M) = NK;
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
/* ********** Assignment  MATRIKS ********** */
void CopyMATRIKS (MatriksMap MIn, MatriksMap * MHsl){
/* Melakukan assignment MHsl  MIn */
	NBrsEff(*MHsl) = NBrsEff(MIn);
	NKolEff(*MHsl) = NKolEff(MIn);
	for(int i = BrsMin ; i <= GetLastIdxBrs(MIn) ; i++){
		for(int j = KolMin ; j <= GetLastIdxKol(MIn) ; j++){
			Elmt(*MHsl,i,j) = Elmt(MIn,i,j);
		}
	}
}
/* ********** KELOMPOK BACA/TULIS ********** */ 
void BacaMATRIKS (MatriksMap * M, int NB, int NK){
/* I.S. IsIdxValid(NB,NK) */ 
/* F.S. M terdefinisi nilai elemen efektifnya, berukuran NB x NK */
/* Proses: Melakukan MakeMATRIKS(M,NB,NK) dan mengisi nilai efektifnya */
/* Selanjutnya membaca nilai elemen per baris dan kolom */
/* Contoh: Jika NB = 3 dan NK = 3, maka contoh cara membaca isi matriks :
1 2 3
4 5 6
8 9 10 
*/
	MakeMATRIKS(NB,NK,&*M);
	for(int i = 1 ; i <= NB ; i++){
		for (int j = 1 ; j <= NK ; j++){
			scanf("%d ", &Elmt(*M,i,j));
		};
	}
}


void TulisMATRIKS (MatriksMap M){
/* I.S. M terdefinisi */
/* F.S. Nilai M(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris 
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris dan per kolom */
/* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/
for(int i = 1 ; i <= GetLastIdxBrs(M) ; i++){
		printf("%d",Elmt(M,i,1));
		for (int j = 2 ; j <= GetLastIdxKol(M) ; j++){
			printf(" %d", Elmt(M,i,j));
		}
		if (i != GetLastIdxBrs(M)){
			printf("\n");
		}
	}
}

/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP MATRIKS ********** */
boolean EQ (MatriksMap M1, MatriksMap M2){
/* Mengirimkan true jika M1 = M2, yaitu NBElmt(M1) = NBElmt(M2) dan */
/* untuk setiap i,j yang merupakan indeks baris dan kolom M1(i,j) = M2(i,j) */
/* Juga merupakan strong EQ karena GetFirstIdxBrs(M1) = GetFirstIdxBrs(M2) 
   dan GetLastIdxKol(M1) = GetLastIdxKol(M2) */
   if (NBrsEff(M1) != NBrsEff(M2)){
	   return(false);
   }
   if (NKolEff(M1) != NKolEff(M2)){
	   return(false);
	}
	else{
		boolean sama = true;
		int i = 0;
		int j = 0;
		while (sama && (i <= NBrsEff(M1))){
			i++;
			while (sama && (j <= NKolEff(M1))){
				j++;
				sama = Elmt(M1,i,j) == Elmt(M2,i,j);
			}
			j = 0;
		}
		return(sama);
	}
}
boolean NEQ (MatriksMap M1, MatriksMap M2){
/* Mengirimkan true jika M1 tidak sama dengan M2 */
	return(!(EQ(M1,M2)));
}
boolean EQSize (MatriksMap M1, MatriksMap M2){
/* Mengirimkan true jika ukuran efektif matriks M1 sama dengan ukuran efektif M2 */
/* yaitu GetBrsEff(M1) = GetNBrsEff (M2) dan GetNKolEff (M1) = GetNKolEff (M2) */
	return((NBrsEff(M1) == NBrsEff(M2)) && (NKolEff(M1) == NKolEff(M2)));
}

/* ********** Operasi lain ********** */
int NBElmt (MatriksMap M){
/* Mengirimkan banyaknya elemen M */
	return(NBrsEff(M) * NKolEff(M));
}

/* ********** KELOMPOK TEST TERHADAP MATRIKS ********** */
boolean IsBujurSangkar (MatriksMap M){
/* Mengirimkan true jika M adalah matriks dg ukuran baris dan kolom sama */
	return(NBrsEff(M) == NKolEff(M));
}

boolean IsSimetri (MatriksMap M){
/* Mengirimkan true jika M adalah matriks simetri : IsBujurSangkar(M) 
   dan untuk setiap elemen M, M(i,j)=M(j,i) */
   if (!(IsBujurSangkar(M))){
	   return(false);
   }
   else{
		boolean sama = true;
		int i = 0;
		int j = 0;
		while (sama && (i <= NBrsEff(M))){
			i++;
			while (sama && (j <= NKolEff(M))){
				j++;
				sama = Elmt(M,i,j) == Elmt(M,j,i);
			}
			j = 0;
		}
		return(sama);
	}
}
boolean IsSatuan (MatriksMap M){
/* Mengirimkan true jika M adalah matriks satuan: IsBujurSangkar(M) dan 
   setiap elemen diagonal M bernilai 1 dan elemen yang bukan diagonal bernilai 0 */ 
	if (!(IsBujurSangkar(M))){
	   return(false);
   }
	else{
		boolean E0 = true;
		int i = 0;
		while (E0 && (i <= NBrsEff(M))){
			i++;
			int j = 1;
			while (E0 && (j <= NKolEff(M))){
				if (i == j){
					E0 = Elmt(M,i,j) == 1;
				}
				else {
					E0 = Elmt(M,i,j) == 0;
				}
				j++;
			}
		}
		return(E0);
   }
}
boolean IsSparse (MatriksMap M){
/* Mengirimkan true jika M adalah matriks sparse: mariks “jarang” dengan definisi: 
   hanya maksimal 5% dari memori matriks yang efektif bukan bernilai 0 */ 
   int count = 0;
   for (int i = GetFirstIdxBrs(M) ; i <= GetLastIdxBrs(M) ; i++){
	   for (int j = GetFirstIdxKol(M) ; j <= GetLastIdxKol(M) ; j++){
		   if (Elmt(M,i,j) != 0){
			   count++;
		   }
	   }
   }
   return(count <= (NBrsEff(M) * NKolEff(M))/20);
}

void Transpose (MatriksMap * M){
/* I.S. M terdefinisi dan IsBujursangkar(M) */
/* F.S. M "di-transpose", yaitu setiap elemen M(i,j) ditukar nilainya dengan elemen M(j,i) */
	MatriksMap K;
	NBrsEff(K) = NBrsEff(*M);
	NKolEff(K) = NKolEff(*M);
	for (int i = BrsMin ; i <= GetLastIdxBrs(*M) ; i++){
		for (int j = KolMin ; j <= GetLastIdxKol(*M) ; j++){
			Elmt(K,i,j) = Elmt(*M,j,i);
		}
	}
	CopyMATRIKS(K,&*M);
}


