#include "dinamiclibraryexample.h"
#include <cstdio>

DinamicLibraryExample::DinamicLibraryExample()
{
    puts("this is a dynamic library");
}

double  cos( double * n)
{
	return 4;
}
