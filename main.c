#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int main() {
    vector vectorA = setVector(2, 3, 0, 0);
    rotateVector(&vectorA, 0.5f);
    return 0;
}