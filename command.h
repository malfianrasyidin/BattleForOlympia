#include <stdio.h>
#include "point.h"
#include "MatriksMap.h"
#include "unit.h"
#include "player.h"
#include "stackt.h"
#include "queuelist.h"


boolean PointInMap (POINT P, MatriksMap M);
/* I.S Sembarang
 * F.S Return true jika P terdefinisi di M dan 
 * 	   false jika P tidak terdefinisi di M
 */

boolean IsDiagonal(POINT PU, POINT P);

boolean IsStraight(POINT PU, POINT P);

boolean isNembus (POINT PU,POINT PA, Player Enemy);

boolean IsMoveValid(POINT PU, POINT P, MatriksMap M, Player Enemy);
/* I.S Unit bukan unit Null, M Terdefinisi
 * F.S True jika Movement ke P Valid, False jika tidak */

void History(Stack *S, POINT P);
//Prekondisi : Sudah di cek command yang dibolehkan untuk menyimpan stack history

void PossibleMove (POINT PIn, MatriksMap M, MatriksMap *MOut, int *cnt, Player Enemy);
//Mengembalikan matriks disertakan tempat2 yang mungkin di move

void MainMove(Stack *S, POINT PIn, MatriksMap *M, Player *Play, Player Enemy);
//MainMove

void Undo (Stack *S, POINT P1, MatriksMap *M, Player *Play);
//Mengembalikan current unit ke posisi sebelumya dan menambah movement points jika ada.

// CHANGE & RECRUIT UNIT
QueueU MakeUnitQueue (List L);
/*Mengembaikan Queue yang berisi semua unit pada L */

void NextUnit(QueueU *Q, POINT *U, MatriksMap M);
//I.S Q terdefinisi
//F.S Mengembalikan Unit yang akan digunakan setelahnya

POINT SearchUnit(QueueU Q, int x);
//I.S Q terdefinisi, tidak mungkin kosong
//F.S Mengembalikan Unit yang berada di urutan X pada Queue

void ChangeCurrUnit(QueueU *Q, MatriksMap M, Player *P);
//I.S Q terdefinisi, U sembarang.
//F.S Mengganti Current Unit yang diapakai player dengan unit selanjutnya pada Queue,  

List UnitCanBeChanged1(Player P);

void UnitCanBeChanged2(List *L, Player P, MatriksMap M, Player Enemy,int* jml);

void ChangeUNIT(Player *P, MatriksMap M);

void NextUNIT(Player *P, MatriksMap M, Player Enemy, int pil, int* jml);


void AddUnit (List *L, QueueU *Q, Unit U);
//I.S L dan U terdefinisi
//F.S Mengembalikan L dan Q yang sudah ditambah elemennya dengan unit U.

void InfoRecruit(int *N);

int EmptyTower(Player P, MatriksMap M);

void RecruitUnit (Player *P, List *L, QueueU *Q, MatriksMap *M);
//I.S Unit UR unit yang merecruit, L dan Q terdefinisi
//F.S Mengembalikan Pesan kesalahan jika UR bukan King atau L dan Q yang sudah terisi Unit Baru jika True

/* ############################## */
/* ########### INFO ############# */
/* ############################## */
void PrintInfoCell (POINT P, MatriksMap M);
//F.S : Ngeprint info cell (building & unit)

void MainInfo(MatriksMap M);
//main info