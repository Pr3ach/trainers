#define _WIN32_WINNT 0x0501
#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <conio.h>
#include "patchlib/patchlib.h"

/*
 * assassins's creed 4: black flag SP helper; prevents items quantity from decreasing
 * Pr3acher @__Pr3__ 
 *
*/

int main(int argc, const char *argv[])
{
	// patch setQuantity() game function, which handles most items like money, secondary ammo,or mortar 
	int16_t *setQuantityAddr = 0x01081891;
	uint8_t setQuantityBytes[3] = {0x90,0x90};

	int16_t *cargo_addr = 0x0107577e;
	uint8_t cargo_bytes[3] = {0x90,0x90};

	system("title AC4BF SP helper");

	if(!patch_open("ac4bfsp.exe",setQuantityAddr,setQuantityBytes,2))
		err("setQuantity function");

	printf("[+] Most items will now be constant\n");
	
	if(!patch_open("ac4bfsp.exe",cargo_addr,cargo_bytes,2))
		err("cargo");

	printf("[+] Cargo will now be constant\n");

	getch();

	return 0;
}

void err(char *str)
{
	printf("[!] Error while applying patch to: %s - Make sure you have admin rights\n",str);
	getch();

	exit(1);
}
