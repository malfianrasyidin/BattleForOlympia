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

void Help(){
	printf("These are the available commands:\n");
	printf("> MOVE\n");
	printf("This command will let you move to your desired position.\n");
	printf("> UNDO\n");
	printf("In case you change your mind, you can undo your action. \nBut, be mind that you only can use it if you previously only have done these commands: > MOVE, > MAP, > INFO.\n");
	printf("> CHANGE_UNIT\n");
	printf("CHANGE_UNIT command lets you switch your current player.\n");
	printf("> NEXT_UNIT\n");
	printf("It eases you to change the unit which is available to move \n");
	printf("> RECRUIT\n");
	printf("You can use this command to recruit new players! Make sure you have enough gold to buy it.\n");
	printf("> ATTACK\n");
	printf("Protect your kingdom! Be the last kingdom left to win the game.\n");
	printf("> MAP\n");
	printf("Avoid getting lost! Make sure you know the maps of this island.\n");
	printf("> INFO\n");
	printf("Look up important informations that you might be considered.\n");
	printf("> END_TURN\n");
	printf("Give the next player chance to play.\n");
	printf("> SAVE\n");
	printf("Get some breaks, save your progress by using this command.\n");
	printf("> LOAD\n");
	printf("Get the previously saved game.\n");
	printf("> HELP\n");
	printf("In case you forget, use this to show all informations you need.\n");
	printf("> EXIT\n");
	printf("Leave the game.\n");
}

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
	int next;
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
			while (NB<8 || NK<8)	{
				printf("Map minimum size is 8x8\n");
				printf("Row : "); scanf("%d", &NB);
				printf("Column : "); scanf("%d", &NK);
			}
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
		Help();
		//Input Command
		printf("Your Input : "); scanf("%s", command);
		//Initialize Current Unit
		CurrUnit = getUnit(CurrentUnitPos(*CurrPlayer),M);
		//Make Queue of Unit of Player
		Q = MakeUnitQueue(UnitList(*CurrPlayer));
		printf("\nPlayer %d's Turn\n", PlayNumber(*CurrPlayer));
		PrintInfoPlayer(*CurrPlayer,M);
		PrintInfoUnit(CurrUnit);
		printf("\n");
		int jml=0;
		List LNEXT;
		CreateEmptyList(&LNEXT);
		UnitCanBeChanged2(&LNEXT, *CurrPlayer, M,*CurrEnemy,&jml);
		if (Search(LNEXT, CurrentUnitPos(*CurrPlayer))!=Nil)	{
			next=2; 
		} else next=1;
		while (strcmp(command,"EXIT")!=0)	{
			if (strcmp(command,"MOVE")==0)	{
				MainMove(&SUndo, CurrentUnitPos(*CurrPlayer), &M, CurrPlayer,*CurrEnemy);
			}
			if (strcmp(command,"UNDO")==0)	{
				Undo (&SUndo, CurrentUnitPos(*CurrPlayer), &M, CurrPlayer);
			}
			if (strcmp(command,"CHANGE_UNIT")==0)	{
				CreateEmpty(&SUndo);
				ChangeUNIT(CurrPlayer, M);
			}
			if (strcmp(command,"NEXT_UNIT")==0)	{
				CreateEmpty(&SUndo);
				NextUNIT(CurrPlayer,M,*CurrEnemy,next,&jml);
				next++;
			}
			if (strcmp(command,"RECRUIT")==0)	{
				CreateEmpty(&SUndo);
				RecruitUnit (CurrPlayer, &UnitList(*CurrPlayer), &Q, &M);
			}
			if (strcmp(command,"ATTACK")==0)	{
				CreateEmpty(&SUndo);
				Attack (&M, CurrPlayer, CurrEnemy, &SUndo);
			}
			if (strcmp(command,"MAP")==0)	{
				PrintMap(M);
			}
			if (strcmp(command,"INFO")==0)	{
				MainInfo(M);
			}
			if (strcmp(command,"END_TURN")==0)	{
				UnitCanBeChanged2(&LNEXT, *CurrPlayer, M,*CurrEnemy,&jml);
				if (Search(LNEXT, CurrentUnitPos(*CurrPlayer))!=Nil)	{
					next=2; 
				} else next=1;
				CreateEmpty(&SUndo);
				NextTurn (&M, &QP, CurrPlayer, CurrEnemy, &SUndo);
			}
			if (strcmp(command,"SAVE")==0)	{
				CreateEmpty(&SUndo);
				Save(M, P1, P2, QP);
			}
			if (strcmp(command,"LOAD")==0)	{
				CreateEmpty(&SUndo);
				MainInfo(M);
			}
			if (strcmp(command,"HELP")==0) {
				Help();
			}
			//Initialize Current Unit
			CurrUnit = getUnit(CurrentUnitPos(*CurrPlayer),M);
			//Make Queue of Unit of Player
			Q = MakeUnitQueue(UnitList(*CurrPlayer));
			printf("\nPlayer %d's Turn\n", PlayNumber(*CurrPlayer));
			PrintInfoPlayer(*CurrPlayer,M);
			PrintInfoUnit(CurrUnit);
			printf("\n");
			command[0]='\0';
			
			//Input Command
			printf("Your Input : "); scanf("%s", command);
		}
	}
	printf("\n======================================\n");
	printf("=========== GOOD BYE COOPS ===========\n");
	printf("======================================\n");
}
