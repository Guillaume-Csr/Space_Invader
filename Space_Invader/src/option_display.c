/*
 * option_display.c
 *
 *  Created on: 10 mars 2020
 *      Author: cuisinier
 */
#include "serial.h"
#include <vt100.h>
#include "option_display.h"
#include "time.h"

uint8_t nb_vie = 0;
float mc;


struct Point{
		uint8_t x, y;
	};
char ti_1[1] = "V";
char ti_2[1] = "V";
char ti_3[1] = "V";


void vie(int nb_mort, int reset_vie){
	vt100_clear_screen();
	vt100_move(0,2);
	serial_puts("--------------------------------------------------------------------------------");
	if (nb_mort == 0 || reset_vie == 1){
		nb_vie = 3;
		vt100_move(0,0);
		serial_puts("vie restantes : nb_vie");
	}
	else {
		nb_vie = nb_vie - nb_mort;
		if (nb_vie == 0) {
			game_over();
		}
	}

}

void game_over(){
	vt100_clear_screen();
	vt100_move(40, 12);
	serial_puts("GAME OVER !");
	time(300000);
	vt100_clear_screen();
	for(mc=12;mc<23;mc++){
		vt100_move(40,mc);
		serial_puts("GAME OVER !");
		time(20000);
		vt100_clear_screen();
	}

}

void player(uint8_t xp){
	vt100_move(xp, 24);
	serial_puts("¡_|_¡");
}

void invader(uint8_t xi,uint8_t yi,uint8_t xm,uint8_t ym){

	// definition des coordonnées
	struct Point c1={5,4}; //v1={x,y}
	struct Point c2={35,4};
	struct Point c3={65,4};

	// attribution des pointeur vers les structure de coordonnées
	struct Point *c12=&c1;
	struct Point *c22=&c2;
	struct Point *c32=&c3;

	// destruction des vaisseaux si coordonnées missile = coordonnées vaisseaux
	if (c12->x+xi == xm && c12->y+yi == ym){

		ti_1[0] = ' ';

	}
	else if (c22->x+xi == xm && c22->y+yi == ym){

		ti_2[0] = ' ';

	}
	else if (c32->x+xi == xm && c32->y+yi == ym){

		ti_3[0] = ' ';

	}

	// affichage vaisseaux
	vt100_move(c12->x+xi,c12->y+yi);
	serial_puts(ti_1);

	vt100_move(c22->x+xi,c22->y+yi);
	serial_puts(ti_2);

	vt100_move(c32->x+xi,c32->y+yi);
	serial_puts(ti_3);
/*
	if (dead != 1){
		vt100_move(xi,yi);
		serial_puts("V");
	}
	else {
		vt100_move(xi,yi);
		serial_putchar(' ');
	}

	struct Point  tab_i[3];

	tab_i[0].x=5;
	tab_i[0].y=4;

	tab_i[1].x=40;
	tab_i[1].y=4;

	tab_i[2].x=75;
	tab_i[2].y=4;

	*/

}




