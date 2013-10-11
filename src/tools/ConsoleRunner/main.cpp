#include <cstdio>
#include <cstdlib>
#include <cstring>

#ifdef _OS_WIN32_
#include <windows.h>
#include <direct.h>
#include <conio.h>
#define wait_key getch

double gettime()
{
    LARGE_INTEGER freq;
    LARGE_INTEGER time;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&time);
    return (double)(time.QuadPart)/(double)(freq.QuadPart);
}

#else
#include <sys/time.h>
#include <unistd.h>
#define wait_key getchar

inline double gettime()
{
    timeval tv;
    gettimeofday(&tv, NULL);
    double time= (double)tv.tv_sec + (double)tv.tv_usec / 1000000;

    return time;
}

#endif

int main(int argc, char *argv[])
{
    if(argc<2)
    {
        printf("Usage: KciConsoleRunner <console program path>\n");
        return 0;
    }

#ifdef _OS_MAC_X_
    system("clear");
#endif
#ifdef _OS_WIN32_
    printf("Please wait...");
#endif

    int l=strlen(argv[1])+2;

    char *program_name=new char[l];
    memset(program_name,0,sizeof(char)*l);
    program_name[0]='\"';
    strcat(program_name,argv[1]);
    strcat(program_name,"\"");

    //get start time

    double exec_time= gettime();
#ifdef _OS_WIN32_
    system("title Cuties Executor - " + program_name);
    system("cls");
#endif

    //run program
    system(program_name);

    //get end time
    exec_time= gettime()-exec_time;

    printf("\n------------------------------------------------------------\n");
    printf("Program execution time : %0.3lf s",exec_time);

    printf("\nPress "

#ifdef _OS_WIN32_
           "any key"
#else
           "ENTER"
#endif
           " to continue.\n");

    wait_key();

    return 0;
}

