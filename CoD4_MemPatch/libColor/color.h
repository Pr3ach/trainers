#ifndef colour
#define colour

    //Color taken by SetConsoleTextAttribute()

#define Green FOREGROUND_GREEN
#define White FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN
#define Red FOREGROUND_RED
#define Blue FOREGROUND_BLUE

void setColor(int color);

#endif
