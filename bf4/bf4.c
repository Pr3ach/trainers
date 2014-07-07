#define _WIN32_WINNT 0x0501
#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <conio.h>
#include "patchlib/patchlib.h"

/*
 * Battlefield 4 single player original version (origin) x64 v1.2.0.2 trainer
 * Pr3acher @__Pr3__ 
 *
 * Note: You need to adjust the 'make.bat' file; more precisely, change gcc_x64 to your x64 verson of gcc, same for windres
 *
 */

int main(int argc, const char *argv[])
{
	//  ammo quantity
	int32_t *ammoAddr = 0x1409425f9;
	uint8_t ammoBytes[7] = {0x90,0x90,0x90,0x90,0x90,0x90};

	// health
	void *healthAddr = 0x140f0db57;

	system("title Battlefield 4 trainer");
	
	if(!patch_open("bf4.exe",ammoAddr,ammoBytes,6))
		err("ammo");
		
	printf("[+] You now have unlimmited ammo\n");

	if(!patch_open("bf4.exe",healthAddr,ammoBytes,5)) // re-using patch for ammo since we simply nop here too ...
		err("health");

	printf("[+] You're now invincible\n");

	printf("[*] All done, enjoy!\n");
	getch();

	return 0;
}

void err(char *str)
{
	printf("[!] Error while applying patch to: %s - Make sure you have admin rights\n",str);
	getch();

	exit(1);
}
