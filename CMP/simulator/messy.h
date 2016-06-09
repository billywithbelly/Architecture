#ifndef MESSY_H
#define MESSY_H

#include "objects.h"
#include "environment.h"
#include "library.h"
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>

void setArgument (char* memorySize, char* pageSize, char* cacheSize, 
    char* blockSize, char* n, int sort)
{
    switch (sort){
        //I
        case 0:
            IMemoryData.MemorySize = atoi (memorySize);
    }
}

#endif
