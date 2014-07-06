#include <windows.h>
#include "color.h"

HANDLE hStdOut=NULL;

void setColor(int color)
{
    if(hStdOut==NULL)
        hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hStdOut,FOREGROUND_INTENSITY | color);

	return;
}
