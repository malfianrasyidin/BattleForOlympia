#include "mesininput.h"
#include "mesinkarT.h"
#include "boolean.h"



int main(){
	BACAINPUT();
	for(int i = 0; i <= CInput.Length; i++){ 
		printf("%c",CInput.TabInput[i]);
	}
	if(CmpInpStr("BACA",CInput)){
		printf("BENAR");
	}
	else{
		printf("VALAK");
	}
}
