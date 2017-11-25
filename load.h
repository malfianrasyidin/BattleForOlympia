#ifndef LOAD__H
#define LOAD__H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mesinkar.h"
#include "mesinkata.h"
#include "boolean.h"
#include "load.h"
#include "command.h"
#include "MatriksMap.h"
#include "unit.h"
#include "point.h"
#include"listdpUnit.h"
#include "player.h"
#include "jam.h"


void kataToString (Kata CKata, char *str);
/* I.S. CKata terdefinisi, str sembarang */
/* F.S. str terdefinisi dengan isi dari CKata.TabKata */

void kataToChar (Kata CKata, char *chr);
/* I.S. CKata terdefinisi, str sembarang */
/* F.S. str terdefinisi dengan isi dari CKata.TabKata */

void kataToInt (Kata CKata, int *bil);
/* I.S. CKata terdefinisi, str sembarang */
/* F.S. str terdefinisi dengan isi dari CKata.TabKata */

/*** MEMBACA FILE EKSTERNAL ***/
void ReadTime(TANGGAL *T, JAM *J);
/* I.S. T dan J sembarang, CKata ada di kata pertama*/
/* F.S. Tanggal T dan Jam J terdefinisi */

void ReadPoint (POINT *P);
/* I.S. P sembarang, CKata ada di kata pertama*/
/* F.S. Point P terdefinisi */

void ReadUnit (Unit *U);
/* I.S. U sembarang, CKata ada di kata pertama*/
/* F.S. Unit U terdefinisi */

void ReadBuild(Build *B);
/* I.S. B sembarang, CKata ada di kata pertama*/
/* F.S. Build B terdefinisi */

void ReadLocation(Location *L);
/* I.S. L sembarang, CKata ada di kata pertama*/
/* F.S. Location L terdefinisi */

void ReadListOfPoint(List *L);
/* I.S. B sembarang, CKata ada di kata pertama*/
/* F.S. Build B terdefinisi */

void ReadPlayer(Player *P);
/* I.S. P sembarang, CKata ada di kata pertama*/
/* F.S. Player P terdefinisi */

void ReadUndo(Stack *S);
/* I.S. S sembarang, CKata ada di kata pertama*/
/* F.S. Stack S terdefinisi */

void ReadTurn(Queue *Q);
/* I.S. Q sembarang, CKata ada di kata pertama*/
/* F.S. Queue Q terdefinisi */

void Load(MatriksMap *MatMap, Player *Player1, Player *Player2, Queue *Turn);
/* Melakukan load file */
/* I.S. file pitakar.txt berisi hasil save, semua parameter tidak terdefinisi*/
/* F.S. mendefinisikan semua parameter */

#endif