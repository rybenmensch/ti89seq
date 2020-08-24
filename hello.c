
#include <tigcclib.h>
#define SPRITE_HEIGHT 7
/*
	screen size: 240x128
	0100 0001	0x41
	0010 0010 0x22
	0001 0100 0x14
	0000 1000	0x08
	0001 0100	0x14
	0010 0010	0x22
	0100 0001	0x41
	Left:	338
	Right:344
	Up:		337
	Down:	340
*/
struct cursor{
	int x_counter;
	int y_counter;
	int x;
	int y;
	int drawn;
	const unsigned char cursorspr[7];
};

struct bars{
	int barspr;
	int y[16];
};

void randbars(struct bars *);
void clearbars(struct bars *);

void drawcursor(struct cursor *);

void _main(void){
	unsigned char cursorspr[] = {
		0x41,0x22,0x14,0x08,0x14,0x22,0x41
	};
	
	struct cursor cursor = {0,64,0,0,0,
	{0x41,0x22,0x14,0x08,0x14,0x22,0x41},};
	struct cursor *p_cursor = &cursor;
	
	struct bars bartest = {0x7FFF, {0}};
	struct bars *p_bars = &bartest;
	
	ClrScr();
	randomize();
	
	int c_x, c_y;
	c_x=0;
	c_y=64;
	
	int key;
	
	randbars(p_bars);
	drawcursor(p_cursor);
	//Sprite8(c_x, p_bars->y[0], SPRITE_HEIGHT, cursorspr, LCD_MEM, SPRT_XOR);

	while((key=ngetchx()) != KEY_ESC){
		
		if(key == 338){ //left
			/*
			Sprite8(c_x, c_y, SPRITE_HEIGHT, cursorspr, LCD_MEM, SPRT_XOR);
			c_x -= 15;
			Sprite8(c_x, c_y, SPRITE_HEIGHT, cursorspr, LCD_MEM, SPRT_XOR);
			*/
			drawcursor(p_cursor);
		}else if(key == 344){ //right
			Sprite8(c_x, c_y, SPRITE_HEIGHT, cursorspr, LCD_MEM, SPRT_XOR);
			c_x += 15;
			Sprite8(c_x, c_y, SPRITE_HEIGHT, cursorspr, LCD_MEM, SPRT_XOR);
		}else if(key == 337){ //up
			Sprite8(c_x, c_y, SPRITE_HEIGHT, cursorspr, LCD_MEM, SPRT_XOR);
			c_y -= 16;
			Sprite8(c_x, c_y, SPRITE_HEIGHT, cursorspr, LCD_MEM, SPRT_XOR);
		}else if(key== 340){ //down
			Sprite8(c_x, c_y, SPRITE_HEIGHT, cursorspr, LCD_MEM, SPRT_XOR);
			c_y += 16;
			Sprite8(c_x, c_y, SPRITE_HEIGHT, cursorspr, LCD_MEM, SPRT_XOR);
		}else{
			clearbars(p_bars);
			randbars(p_bars);
		}
	}
	
	/*ClrScr();
	printf("%d\n", c_y);
	ngetchx();
	*/
}

void randbars(struct bars *bar){
	int i;
	randomize();
	
	for(i=0;i<16;i++){
		bar->y[i] = random(16)*8;
		Sprite16(i*15, bar->y[i], 1, &(bar->barspr), LCD_MEM, SPRT_XOR);
	}
}

void clearbars(struct bars *bar){
	int i;
	for(i=0;i<16;i++){
		Sprite16(i*15, bar->y[i], 1, &(bar->barspr), LCD_MEM, SPRT_XOR);
	}
}

void updatecursor(struct cursor *cursor){
	
}

void drawcursor(struct cursor *cursor){
	int xcount = cursor->x_counter;
	int ycount = cursor->y_counter;
	cursor->x = (xcount*15) + 6;
	cursor->y = (ycount*15) + 3;
	
	if(cursor->drawn){
		Sprite8(cursor->x, cursor->y, SPRITE_HEIGHT, cursor->cursorspr, LCD_MEM, SPRT_XOR);
		Sprite8(cursor->x, cursor->y, SPRITE_HEIGHT, cursor->cursorspr, LCD_MEM, SPRT_XOR);
	}else{
		cursor->drawn=1;;
	}
}