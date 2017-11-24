#include <stdio.h>
#include "stringt.h"
#include "command.h"
#include "point.h"
#include "MatriksMap.h"
#include "unit.h"
#include "stackt.h"
#include "player.h"
#include "queuelist.h"
#include "mesininput.h"

int main()	{
	int n, NB, NK;
	char* cmd;
	POINT P;
	MatriksMap M;
	Player CurrPlayer, P1, P2;
	Stack SUndo;
	QueueU Q;
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
		CreateTurn(&QP, P1, P2);
		InitPlayer(&P1, &P2, NB,NK);
		cmd=" ";
		CurrPlayer = P1;
		while (strcmp(cmd,"EXIT")!=0)	{
			PrintMap(M);
			CurrUnit = getUnit(CurrentUnitPos(CurrPlayer),M);
			Q = MakeUnitQueue(UnitList(CurrPlayer));
			printf("Player %d's Turn\n", PlayNumber(CurrPlayer));
			// PrintInfoPlayer(CurrPlayer);
			printf("Your Input : ");
			BACAINPUT();
			PrintMap(M);
			if (CmpInpStr("MOVE",CInput))	{
				MainMove(&SUndo, Locate(CurrUnit), &M, &CurrPlayer);
			}
			if (CmpInpStr("UNDO",CInput))	{
				Undo(&SUndo,&CurrUnit);
			}
			if (CmpInpStr("CHANGE UNIT",CInput))	{
				ChangeCurrUnit(&Q,M,&CurrPlayer);
			}
			if (CmpInpStr("RECRUIT",CInput))	{
				RecruitUnit (CurrPlayer, &UnitList(CurrPlayer), &Q, M);
			}
			if (CmpInpStr("ATTACK",CInput))	{
				//Attack
			}
			if (CmpInpStr("MAP",CInput))	{
				PrintMap(M);
			}
			if (CmpInpStr("INFO",CInput))	{
				MainInfo(M);
			}
			if (CmpInpStr("END TURN",CInput))	{
				NextTurn(&QP,&CurrPlayer);
			}
			if (CmpInpStr("SAVE",CInput))	{

			}
			if (CmpInpStr("EXIT",CInput))	{

			}
		}

	} else if (n==2)	{

	}
	printf("======================================\n");
	printf("=========== GOOD BYE COOPS ===========\n");
	printf("======================================\n");
}
