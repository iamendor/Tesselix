#include "debugmalloc.h"
#include "util.h"
#include <stdbool.h>
#include <math.h>

bool equal(double a, double b){
    double const eps = pow(10, -10);
    return fabs(a-b) < eps;
}