#include <stdio.h>
#include "command.h"
#include "point.h"
#include "MatriksMap.h"
#include "unit.h"
#include "stackt.h"
#include "player.h"
#include "queuelist.h"
#include <string.h>
#include "save.h"
#include "load.h"

int main()	{
	//Initialize
	int n, NB, NK;
	char command[100];
	MatriksMap M;
	Player P1, P2;
	Player* CurrPlayer;
	Player* CurrEnemy;
	Stack SUndo;
	QueueU Q;
	Queue QP;
	Unit CurrUnit;
	//Welcoming Party
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
	printf("MENU : \n");
	printf("1. START\n");
	printf("2. LOAD\n");
	printf("3. EXIT\n");
	//Input menu
	printf("Choose Menu : ");	scanf("%d", &n);
	if (n != 3) {
		if (n==1)	{
			printf("\n== Create Map ==\n");	
			printf("Row : "); scanf("%d", &NB);
			printf("Column : "); scanf("%d", &NK);
			//Generate Map
			M = MatGen(NB,NK);
			//Create Queue of Player
			CreateTurn(&QP);
			//Initialize player
			InitPlayer(&P1, &P2, NB,NK);
			CurrPlayer = &P1;
			CurrEnemy = &P2;
		} else if (n==2)	{
			Load(&M, &P1, &P2, &QP);
			if (InfoHead(QP) == PlayNumber(P1)) {
				CurrPlayer = &P1;
				CurrEnemy = &P2;
			} else {
				CurrPlayer = &P2;
				CurrEnemy = &P1;
			}
		} 
		//Initialize command
		command[0]='\0';
		while (strcmp(command,"EXIT")!=0)	{
			//Initialize Current Unit
			CurrUnit = getUnit(CurrentUnitPos(*CurrPlayer),M);
			//Make Queue of Unit of Player
			Q = MakeUnitQueue(UnitList(*CurrPlayer));
			printf("\nPlayer %d's Turn\n", PlayNumber(*CurrPlayer));
			PrintInfoPlayer(*CurrPlayer);
			PrintInfoUnit(CurrUnit);
			//Input Command
			printf("Your Input : "); scanf("%s", command);
			if (strcmp(command,"MOVE")==0)	{
				MainMove(&SUndo, CurrentUnitPos(*CurrPlayer), &M, CurrPlayer);
			}
			if (strcmp(command,"UNDO")==0)	{
				Undo (&SUndo, CurrentUnitPos(*CurrPlayer), &M, CurrPlayer);
			}
			if (strcmp(command,"CHANGE_UNIT")==0)	{
				ChangeCurrUnit(&Q,M,CurrPlayer);
			}
			if (strcmp(command,"RECRUIT")==0)	{
				RecruitUnit (CurrPlayer, &UnitList(*CurrPlayer), &Q, &M);
			}
			if (strcmp(command,"ATTACK")==0)	{
				Attack (&M, CurrPlayer, CurrEnemy, &SUndo);
			}
			if (strcmp(command,"MAP")==0)	{
				PrintMap(M);
			}
			if (strcmp(command,"INFO")==0)	{
				MainInfo(M);
			}
			if (strcmp(command,"END_TURN")==0)	{
				NextTurn (&M, &QP, P1, P2, CurrPlayer, CurrEnemy, &SUndo);
			}
			if (strcmp(command,"SAVE")==0)	{
				Save(M, P1, P2, QP);
			}
			if (strcmp(command,"LOAD")==0)	{
				MainInfo(M);
			}
			if (strcmp(command,"EXIT")==0)	{
				break;
			}
			command[0]='\0';
		}
	}
	printf("\n======================================\n");
	printf("=========== GOOD BYE COOPS ===========\n");
	printf("======================================\n");
}
