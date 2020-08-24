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

void _main(void){
	int leave_program = 0;
	ClrScr();
	running=0;
	resettime=1;

	oldint5 = GetIntVec(AUTO_INT_5);
	SetIntVec(AUtO_INT_5, myint5handler);

	printf_xy(0, 0, "[ESC] end");
	printf_xy(0, 10, "[ENTER] run/stop");
	printf_xy(0, 20, "[CLEAR] reset");

	while(!leave_program){
		if(!(mseconds50%5)){
			printf(50, 50, "%02d", stepcounter);
		}

		if(kbhit()){
			int input = ngetchx();

			switch(input){
				case KEY_ESC:
					leave_program = 1;
					break;
				case KEY_ENTER:
					running = !running;
					break;
				case KEY_CLEAR:
					resettime = 1;
					break;
			}
		}
	}

	CLrScr();
	printf_xy(50, 50, "EAT");
	printf_xy(50, 60, "SHIT");
	printf_xy(50, 70, "INC");

	int k = ngetchx();

	SetIntVec(AUTO_INT_5, oldint5);

	GKeyFlush();
}
