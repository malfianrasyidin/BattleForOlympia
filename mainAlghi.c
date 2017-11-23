#include "command.h"
#include "point.h"
#include "MatriksMap.h"
#include "unit.h"
#include <stdio.h>
#include "stackt.h"
#include "string.h"
#include "player.h"



int main()	{
	int n, NB, NK;
	char* cmd;
	MatriksMap M;
	Player CurrPlayer;
	Stack SUndo;
	Queue Q;
	Queue QP;
	Unit CurrUnit;
	printf("=====================================\n");
	printf("=== WELCOME TO BATTLE FOR OLYMPIA ===\n");
	printf("=====================================\n");
	printf("\n");
	printf("by : \n");
	printf("1. Mochamad Alghifari\n");
	printf("2. Rifqi Rifaldi Utomo\n");
	printf("3. M. Rafli Al Khadafi\n");
	printf("4. M. Alfian Rasyidin\n");
	printf("5. M. Aufa Helfiandri\n");
	printf("\n");
	printf("\n");
	printf("MENU : \n");
	printf("1. START\n");
	printf("2. LOAD\n");
	printf("3. EXIT\n");
	printf("Choose Menu : \n");	scanf("%d", &n);
	if (n==1)	{
		printf("Create Map : \n");	
		printf("Row : "); scanf("%d", &NB);
		printf("Column : "); scanf("%d", &NK);
		M = MatGen(NB,NK);
		//InitPlayer(&InfoHead(QP), &InfoTail(QP), NB,NK);
		cmd=" ";
		while (strcmp(cmd,"EXIT")!=0)	{
			CurrUnit = getUnit(CurrentUnitPos(CurrPlayer),M);
			Q = MakeUnitQueue(UnitList(CurrPlayer));
			printf("Player %d's Turn\n", PlayNumber(CurrPlayer));
			//PrintInfoPlayer(CurrPlayer);
			PrintInfoUnit(CurrUnit);
			printf("Your Input : "); scanf("%s", cmd);
			if (strcmp(cmd,"MOVE"))	{
				MainMove(&SUndo, &CurrUnit, &M);
			}
			if (strcmp(cmd,"UNDO"))	{
				Undo(&SUndo,&CurrUnit);
			}
			if (strcmp(cmd,"CHANGE_UNIT"))	{
				//Q = MakeUnitQueue(UnitList(P));
				//ChangeCurrUnit(&Q,M,&P);
			}
			if (strcmp(cmd,"RECRUIT"))	{
				//RecruitUnit (P, UnitList(P), &Q, M);
			}
			if (strcmp(cmd,"ATTACK"))	{
				//Attack
			}
			if (strcmp(cmd,"MAP"))	{
				PrintMap(M);
			}
			if (strcmp(cmd,"INFO"))	{
				MainInfo(M);
			}
			if (strcmp(cmd,"END_TURN"))	{
				NextTurn(&QP,&CurrPlayer);
			}
			if (strcmp(cmd,"SAVE"))	{

			}
			if (strcmp(cmd,"EXIT"))	{

			}
		}

	} else if (n==2)	{

	}
	printf("======================================\n");
	printf("=========== GOOD BYE COOPS ===========\n");
	printf("======================================\n");
}