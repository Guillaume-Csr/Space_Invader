/*
 * menu.c
 *
 *  Created on: 4 mars 2020
 *      Author: cuisinier
 */
#include "serial.h"
#include <vt100.h>
#include "menu.h"
#include "time.h"


void menu(){
	//float c;
	uint16_t clavier1 = 0;
	vt100_clear_screen();
	while (clavier1 != 0x70){
		clavier1 = serial_get_last_char();
		vt100_move(33, 5);
		serial_puts("---SPACE INVADER---");
		vt100_move(31, 10);
		serial_puts("°-- PRESS P TO START --°");
		vt100_move(33, 16);
		serial_puts("  V   -------> INVADER");
		vt100_move(33, 13);
		serial_puts("¡_|_¡ -------> YOU");

		vt100_move(0, 40);
		serial_puts("gameghost_copyright");
		//for (c = 0; c < 3000000; c++);
		time(3000000);

		vt100_clear_screen();
		vt100_move(33, 5);
		serial_puts("---SPACE INVADER---");

		vt100_move(33, 16);
		serial_puts("  V   -------> INVADER");
		vt100_move(33, 13);
		serial_puts("¡_|_¡ -------> YOU");

		vt100_move(0, 40);
		serial_puts("gameghost_copyright");
		//for (c = 0; c < 3000000; c++);
		time(3000000);
	}
};
