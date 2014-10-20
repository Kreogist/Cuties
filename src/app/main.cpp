#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <Python.h>

int main(int argc, char **argv)
{
    wchar_t *programName=new wchar_t[strlen(argv[0])+1];
    mbstowcs(programName,argv[0],strlen(argv[0]));
    Py_SetProgramName(programName);

    Py_Initialize();

    if(!Py_IsInitialized())
    {
        puts("Can not initialize python");
        return -1;
    }

    FILE *pyMain=fopen("main.py","rw");
    if(pyMain==NULL)
    {
        puts("main.py not find!");
        return -1;
    }

    PyRun_SimpleFile(pyMain,"main.py");

    Py_Finalize();

    delete[] programName;

    return 0;
}
