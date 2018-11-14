#include "dinamiclibraryexample.h"

DinamicLibraryExample::DinamicLibraryExample()
{
}

extern "C" double  cose()
{
    return 4;
}
