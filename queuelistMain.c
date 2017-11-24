#include "queuelist.h"
#include "point.h"
#include "boolean.h"
#include <stdlib.h>
#include <stdio.h>

int main () {
	QueueU Q;
	infotypeQU P;
	int Choice;

	printf("--This is a driver for ADT Queue List of Points--\n");
	printf("List of commands: \n");
	printf("1. IsEmpty() \n");
	printf("2. IsOneElmt() \n");
	printf("3. NbElmt() \n");
	printf("4. Add Queue \n");
	printf("5. Del Queue \n");
	printf("6. RoundP () \n");
	printf("7. Exit () \n");

	CreateEmptyUQ(&Q);
	printf("Your command: ");
	scanf("%d", &Choice);
	while (Choice != 7){
		if (Choice==1){
			if (IsEmptyUQ(Q)){
				printf("Q is empty\n");
			} else {
				printf("Q is not empty\n");
			}
		} else if (Choice==2){
			if (IsOneElmtUQ(Q) && !IsEmptyUQ(Q)){
				printf("Q has one element\n");
			} else {
				printf("Q doesn't have only one element\n");
			}
		} else if (Choice==3){
			printf("Number of element in Q : %d\n", NbElmtUQ(Q));
		} else if (Choice==4){
			printf("Input a point [X Y]: ");
			BacaPOINT(&P);
			AddQU(&Q,P);
		} else if (Choice==5){
			DelQU(&Q,&P);
			printf("Deleted point is ");
			TulisPOINT(P);
		} else if (Choice==6){
			RoundP(&Q);
			printf("RoundP success\n");
		} else {
			printf("Wrong commands\n");
		}
		printf("Your command: ");
		scanf("%d", &Choice);
	}
	return 0;
}