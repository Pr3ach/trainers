#define _WIN32_WINNT 0x0501
#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <conio.h>
#include "patchlib/patchlib.h"

/*
 * Battlefield 3 single player original version (origin) 1.6.0.0 trainer
 * bf3.exe sha-1: 743643ad6bb4721919cfc33e8b985d8062dc118d	
 *
 * Pr3acher @__Pr3__ 
 *
 */

int main(int argc, const char *argv[])
{
	// ammo
	int32_t *ammoAddr = 0x011f45e6;

	// health
	void *healthAddr = 0xa71c26;
	uint8_t healthBytes[6] = {0x90,0x90,0x90,0x90,0x90};

	system("title Battlefield 3 single player trainer");
	
	if(!patch_open("bf3.exe",ammoAddr,healthBytes,3))
		err("ammo");
		
	printf("[+] You now have unlimited ammo\n");

	if(!patch_open("bf3.exe",healthAddr,healthBytes,5))
		err("health");

	printf("[+] You're now invincible\n");

	printf("[*] All done, have fun!\n");
	getch();

	return 0;
}

void err(char *str)
{
	printf("[!] Error while applying patch to: %s - Make sure you have admin rights\n",str);
	getch();

	exit(1);
}
