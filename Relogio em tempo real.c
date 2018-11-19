#include <stdio.h>
#include <windows.h> 
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int main()
{
    time_t rawTime;
    struct tm * relogio;
    char a[100];
		

    while(1)
    {
        system("cls");

        setlocale(LC_ALL, "Portuguese");
        rawTime = time(NULL);
        relogio = localtime(&rawTime);
        strftime(a, 100, "%I:%M:%S", relogio);

		printf("%s\n",a);
        

        
        Sleep(1000);
    }
    return 0;
}
