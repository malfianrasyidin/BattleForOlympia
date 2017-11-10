#include "matriks.h"
#include <stdio.h>
#include "boolean.h"

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */              
/* *** Konstruktor membentuk MATRIKS *** */
void MakeMATRIKS (int NB, int NK, MATRIKS * M){
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
indeks GetFirstIdxBrs (MATRIKS M){
/* Mengirimkan indeks baris terkecil M */
	return(BrsMin);
}
indeks GetFirstIdxKol (MATRIKS M){
/* Mengirimkan indeks kolom terkecil M */
	return(KolMin);
}
indeks GetLastIdxBrs (MATRIKS M){
/* Mengirimkan indeks baris terbesar M */
	return(NBrsEff(M));
}
indeks GetLastIdxKol (MATRIKS M){
/* Mengirimkan indeks kolom terbesar M */
	return(NKolEff(M));
}
boolean IsIdxEff (MATRIKS M, indeks i, indeks j){
/* Mengirimkan true jika i, j adalah indeks efektif bagi M */
	return ((IsIdxValid(i,j)) && (( i <= NBrsEff(M)) && (j <= NKolEff(M))));
}
ElType GetElmtDiagonal (MATRIKS M, indeks i){
/* Mengirimkan elemen M(i,i) */
	return(Elmt(M,i,i));
}
/* ********** Assignment  MATRIKS ********** */
void CopyMATRIKS (MATRIKS MIn, MATRIKS * MHsl){
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
void BacaMATRIKS (MATRIKS * M, int NB, int NK){
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


void TulisMATRIKS (MATRIKS M){
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

/* ********** KELOMPOK OPERASI ARITMATIKA TERHADAP TYPE ********** */                                  
MATRIKS TambahMATRIKS (MATRIKS M1, MATRIKS M2){
/* Prekondisi : M1  berukuran sama dengan M2 */
/* Mengirim hasil penjumlahan matriks: M1 + M2 */ 
	MATRIKS M;
	MakeMATRIKS(NBrsEff(M1),NKolEff(M1),&M);
	for (int i = 1 ; i <= NBrsEff(M) ; i++){
		for (int j = 1 ; j <= NKolEff(M) ; j++){
			Elmt(M,i,j) = Elmt(M1,i,j) + Elmt(M2,i,j);
		}
	}
	return(M);
}
MATRIKS KurangMATRIKS (MATRIKS M1, MATRIKS M2){
/* Prekondisi : M berukuran sama dengan M */
/* Mengirim hasil pengurangan matriks: salinan M1 – M2 */ 
	MATRIKS M;
	MakeMATRIKS(NBrsEff(M1),NKolEff(M1),&M);
	for (int i = 1 ; i <= NBrsEff(M) ; i++){
		for (int j = 1 ; j <= NKolEff(M) ; j++){
			Elmt(M,i,j) = Elmt(M1,i,j) - Elmt(M2,i,j);
		}
	}
	return(M);
}
MATRIKS KaliMATRIKS (MATRIKS M1, MATRIKS M2){
/* Prekondisi : Ukuran kolom efektif M1 = ukuran baris efektif M2 */
/* Mengirim hasil perkalian matriks: salinan M1 * M2 */
	MATRIKS M;
	ElType temp;
	MakeMATRIKS(NBrsEff(M1),NBrsEff(M2),&M);
	
	for (int i = GetFirstIdxBrs(M) ; i <= GetLastIdxBrs(M) ; i++){
		for(int j = GetFirstIdxKol(M) ; j <= GetLastIdxKol(M) ; j++){
			temp = 0 ;
			for (int z = GetFirstIdxKol(M1) ; z <= GetLastIdxKol(M1) ; z++){
				temp += Elmt(M1,i,z) * Elmt(M2,z,j);
			}
			Elmt(M,i,j) = temp;
		}
	}
	return(M);
}

MATRIKS KaliKons (MATRIKS M, ElType X){
/* Mengirim hasil perkalian setiap elemen M dengan X */
	MATRIKS MC;
	MakeMATRIKS(NBrsEff(M),NKolEff(M),&MC);
	for (int i = 1 ; i <= NBrsEff(MC) ; i++){
		for (int j = 1 ; j <= NKolEff(MC) ; j++){
			Elmt(MC,i,j) = Elmt(M,i,j) *X;
		}
	}
	return(MC);
}

void PKaliKons (MATRIKS * M, ElType K){
/* I.S. M terdefinisi, K terdefinisi */
/* F.S. Mengalikan setiap elemen M dengan K */
	MATRIKS MC;
	CopyMATRIKS(KaliKons(*M,K), &MC);
	CopyMATRIKS(MC,&*M);
}

/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP MATRIKS ********** */
boolean EQ (MATRIKS M1, MATRIKS M2){
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
boolean NEQ (MATRIKS M1, MATRIKS M2){
/* Mengirimkan true jika M1 tidak sama dengan M2 */
	return(!(EQ(M1,M2)));
}
boolean EQSize (MATRIKS M1, MATRIKS M2){
/* Mengirimkan true jika ukuran efektif matriks M1 sama dengan ukuran efektif M2 */
/* yaitu GetBrsEff(M1) = GetNBrsEff (M2) dan GetNKolEff (M1) = GetNKolEff (M2) */
	return((NBrsEff(M1) == NBrsEff(M2)) && (NKolEff(M1) == NKolEff(M2)));
}

/* ********** Operasi lain ********** */
int NBElmt (MATRIKS M){
/* Mengirimkan banyaknya elemen M */
	return(NBrsEff(M) * NKolEff(M));
}

/* ********** KELOMPOK TEST TERHADAP MATRIKS ********** */
boolean IsBujurSangkar (MATRIKS M){
/* Mengirimkan true jika M adalah matriks dg ukuran baris dan kolom sama */
	return(NBrsEff(M) == NKolEff(M));
}
boolean IsSimetri (MATRIKS M){
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
boolean IsSatuan (MATRIKS M){
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
boolean IsSparse (MATRIKS M){
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
MATRIKS Inverse1 (MATRIKS M){
/* Menghasilkan salinan M dengan setiap elemen "di-invers", yaitu dinegasikan (dikalikan -1) */
	return(KaliKons(M,-1));
}
float Determinan (MATRIKS M){
/* Prekondisi: IsBujurSangkar(M) */
/* Menghitung nilai determinan M */
	if (NBrsEff(M) == 1){
		return(Elmt(M,GetFirstIdxBrs(M),GetFirstIdxKol(M)));
	}
	else if (NBrsEff(M) == 2){
		return(Elmt(M,1,1) * Elmt(M,2,2) - Elmt(M,1,2) * Elmt(M,2,1));
	}
	else{
		int x = 1;
		int y = 0;
		float Dtemp = 0;
		MATRIKS MB;
		MakeMATRIKS(NBrsEff(M) -1, NKolEff(M) - 1, &MB);
		for (int z = GetFirstIdxBrs(M) ; z <= GetLastIdxBrs(M) ; z++){
			x = 0;
			y = 0;
			for (int i = GetFirstIdxBrs(M) + 1 ; i <= GetLastIdxBrs(M) ; i++){
				x++;
				for(int j = GetFirstIdxKol(M) ; j <= GetLastIdxKol(M) ; j++){
					if (j != z){
						y++;
						Elmt(MB,x,y) = Elmt(M,i,j);
					}
				}
			}
			if ( z % 2 == 1){
				Dtemp += Elmt(M,GetFirstIdxBrs(M),z) * Determinan(MB);
			}
			else {
				Dtemp -= Elmt(M,GetFirstIdxBrs(M),z) * Determinan(MB);
			}
		}
	return(Dtemp);
	}
}

void PInverse1 (MATRIKS * M){
/* I.S. M terdefinisi */
/* F.S. M di-invers, yaitu setiap elemennya dinegasikan (dikalikan -1) */
	PKaliKons(&*M,-1);
}

void Transpose (MATRIKS * M){
/* I.S. M terdefinisi dan IsBujursangkar(M) */
/* F.S. M "di-transpose", yaitu setiap elemen M(i,j) ditukar nilainya dengan elemen M(j,i) */
	MATRIKS K;
	NBrsEff(K) = NBrsEff(*M);
	NKolEff(K) = NKolEff(*M);
	for (int i = BrsMin ; i <= GetLastIdxBrs(*M) ; i++){
		for (int j = KolMin ; j <= GetLastIdxKol(*M) ; j++){
			Elmt(K,i,j) = Elmt(*M,j,i);
		}
	}
	CopyMATRIKS(K,&*M);
}
