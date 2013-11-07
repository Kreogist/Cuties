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

    int l=1;
    for(int i=1; i<argc; i++)
    {
        l+=strlen(argv[i]);
    }

#ifdef _OS_WIN32_
    char *title=new char[l+100];
    title[0]='\0';
    strcat(title, "title Cuites Executor - ");
    strcat(title, argv[1]);
    system(title);
    printf("Please wait...");
#endif

    char *programName=new char[l];
    memset(programName,0,sizeof(char)*l);
    programName[0]='\"';
    strcat(programName,argv[1]);
    for(int i=2; i<argc; i++)
    {
        strcat(programName," ");
        strcat(programName,argv[i]);
    }
    strcat(programName,"\"");

    //get start time
    double execTime= gettime();

#ifdef _OS_WIN32_
    system("cls");
#endif

    //run program
    system(programName);

    //get end time
    execTime= gettime()-execTime;

    printf("\n------------------------------------------------------------\n");
    printf("Program execution time : %0.3lf s",execTime);

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

