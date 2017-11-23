#ifndef PLAYER__H
#define PLAYER__H

#include "boolean.h"
#include "listdpUnit.h"
#include "unit.h"
#include "point.h"


#define Nol 0
#define StartingGold 100
/* Konstanta untuk mendefinisikan address tak terdefinisi */

typedef struct tPlayer *addrQ;
typedef struct tPlayer {
    int PlayerNumber;
    POINT CurrUnitPos;
    int Gold;
    int Income;
    int UpKeep;
    List ListOfUnits;
    List ListOfVillages;
    POINT CastlePointer;
    POINT TowersPointer[4];
} Player;

typedef addrQ infotypeQ;

#define PlayNumber(P)       (P).PlayerNumber
#define PGold(P) 			(P).Gold
#define CurrentUnitPos(P)	(P).CurrUnitPos
#define PIncome(P)			(P).Income
#define PUpKeep(P)			(P).UpKeep
#define UnitList(P)			(P).ListOfUnits
#define VillageList(P)		(P).ListOfVillages
#define PlayerCastle(P)		(P).CastlePointer
#define TabTower(P)			(P).TowersPointer
#define PlayerTower(P,i) 	(P).TowersPointer[i-1]

/* Definisi elemen dan address */

typedef int addressQ;   /* indeks tabel */
/* Contoh deklarasi variabel bertype Queue : */
/* Versi I : tabel dinamik, Head dan Tail eksplisit, ukuran disimpan */
typedef struct { infotypeQ * T;   /* tabel penyimpan elemen */
                 addressQ HEAD;  /* alamat penghapusan */
                 addressQ TAIL;  /* alamat penambahan */
                 int MaxEl;     /* Max elemen queue */
               } Queue;
/* Definisi Queue kosong: HEAD=Nil; TAIL=Nil. */
/* Catatan implementasi: T[0] tidak pernah dipakai */

/* ********* AKSES (Selektor) ********* */
/* Jika Q adalah Queue, maka akses elemen : */
#define Head(Q) (Q).HEAD
#define Tail(Q) (Q).TAIL
#define InfoHead(Q) (Q).T[(Q).HEAD]
#define InfoTail(Q) (Q).T[(Q).TAIL]
#define MaxEl(Q) (Q).MaxEl

void InitPlayer (Player *P1, Player *P2, int NB, int NK);
//Membuat player pada kondisi awal

void AttackU (Unit U1, Unit U2);
//Membuat Unit 1 Menyerang Unit 2 dengan tipe Attack 1



/*** QUEUE PLAYER ***/

/* ********* Prototype ********* */
boolean IsQEmpty (Queue Q);
/* Mengirim true jika Q kosong: lihat definisi di atas */
boolean IsQFull (Queue Q);
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */
int NBElmtQ (Queue Q);
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */

/* *** Kreator *** */
void CreateEmptyQ (Queue * Q, int Max);
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */

/* *** Destruktor *** */
void DeAlokasiQ(Queue * Q);
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */

/* *** Primitif Add/Delete *** */
void AddQ (Queue * Q, infotypeQ X);
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */
void DelQ (Queue * Q, infotypeQ * X);
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer; 
        Q mungkin kosong */

/* *** Fungsi Tambahan Untuk Battle for Olympia ** */

void CreateTurn(Queue * Q, Player P1, Player P2);
/* I.S. sembarang */
/* F.S. Queue dengan alokasi 2 memory, dengan angka 1 yang merepresentasikan
		P1 pada Head dan angka 2 yang merepresentasikan P2 pada Tail */
void NextTurn(Queue * Q, Player * CurrentPlayer);
/* I.S. Q terdefinisi 2 elemen dengan A sebagai head dan B sebagai Tail */
/* F.S. A dihapus (selesai turn) sehingga B menjadi head (turn saat ini)
		dan A sebagai tail (turn berikutnya) */
infotypeQ CurrentTurn (Queue Q);
/* I.S. Q terdefinisi dengan elemen head A (turn saat ini) dan elemen tail B
		(turn berikutnya) */
/* F.S. mengembalikan A (turn saat ini)*/

#endif