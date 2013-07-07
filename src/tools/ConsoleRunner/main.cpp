#include <cstdio>
#include <cstdlib>
#include <cstring>

#ifdef _OS_WIN32_
#include <windows.h>
#include <conio.h>
#define wait_key getch

double gettime()
{
    LARGE_INTEGER freq;
    LARGE_INTEGER time;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&time);
    return (double)time.QuadPart/(double)freq;
}

#else
#include <sys/time.h>
#define wait_key getchar

double gettime()
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

    char* program_name=new char[strlen(argv[1])+2];
    memset(program_name,0,sizeof(program_name));
    program_name[0]='\"';
    strcat(program_name,argv[1]);
    strcat(program_name,"\"");

    //get start time

    double exec_time= gettime();

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

