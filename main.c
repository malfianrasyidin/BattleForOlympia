#include <stdio.h>
#include "string.h"
#include "command.h"
#include "point.h"
#include "MatriksMap.h"
#include "unit.h"
#include "stackt.h"
#include "player.h"
#include "queuelist.h"

int main()	{
	int n, NB, NK;
	char cmd[100];
	POINT P;
	MatriksMap M;
	Player CurrPlayer, P1, P2;
	Stack SUndo;
	QueueU Q;
	Queue QP;
	Unit CurrUnit;

	char* exit = "EXIT";
	char* move = "MOVE";
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
	printf("Choose Menu : ");	scanf("%d", &n);
	if (n==1)	{
		printf("Create Map : \n");	
		printf("Row : "); scanf("%d", &NB);
		printf("Column : "); scanf("%d", &NK);
		M = MatGen(NB,NK);
		CreateTurn(&QP, P1, P2);
		InitPlayer(&P1, &P2, NB,NK);
		printf("Your Input : ");
		scanf("%s", cmd);
		printf("%s\n", cmd);
		while (strcmp("EXIT",cmd)==0)	{
			CurrUnit = getUnit(CurrentUnitPos(CurrPlayer),M);
			Q = MakeUnitQueue(UnitList(CurrPlayer));
			printf("Player %d's Turn\n", PlayNumber(CurrPlayer));
			// PrintInfoPlayer(CurrPlayer);
			if (strcmp(move,cmd)==0)	{
				MainMove(&SUndo, CurrentUnitPos(CurrPlayer), &M, &CurrPlayer);
			}
			if (strcmp("UNDO",cmd)==0)	{
				Undo (&SUndo, CurrentUnitPos(CurrPlayer), &M, &CurrPlayer);
			}
			if (strcmp("CHANGE_UNIT",cmd)==0)	{
				ChangeCurrUnit(&Q,M,&CurrPlayer);
			}
			if (strcmp("RECRUIT",cmd)==0){
				RecruitUnit (&CurrPlayer, &UnitList(CurrPlayer), &Q, &M);
			}
			if (strcmp("ATTACK",cmd)==0){
				//Attack
			}
			if (strcmp("MAP",cmd)==0){
				PrintMap(M);
			}
			if (strcmp("INFO",cmd)==0){
				MainInfo(M);
			}
			if (strcmp("END_TURN",cmd)==0)	{
				NextTurn(&QP,&CurrPlayer);
			}
			if (strcmp("SAVE",cmd)==0)	{

			}
			if (strcmp("EXIT",cmd)==0)	{

			}
			printf("Your Input : ");
			scanf("%s", cmd);
		}

	} else if (n==2)	{

	}
	printf("======================================\n");
	printf("=========== GOOD BYE COOPS ===========\n");
	printf("======================================\n");
}
