//screen size: 240x128
//#define UE_TI89
#define SAVE_SCREEN
#include <tigcclib.h>

int _ti89, _ti92plus;

INT_HANDLER oldint5 = NULL;

volatile int mseconds50 = 0;
volatile int seconds = 0;
volatile int resettime = 1;
volatile int stepcounter = 0;
volatile int running = 1;

DEFINE_INT_HANDLER(myint5handler){
	if(resettime){
		mseconds50=resettime=stepcounter=0;
	}else if(running){
		mseconds50++;
		
		mseconds50 = (mseconds50==19)?0:mseconds50;
		//mseconds50 %= 19;

		if(mseconds50%5==0){
			stepcounter++;
			stepcounter = (stepcounter==16)?0:stepcounter;
		}
	}

	ExecuteHandler(oldint5);
}
