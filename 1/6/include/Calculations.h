#include "../include/Status.h"

long double fa(long double x, long double eps);

long double fb(long double x, long double eps);

long double fc(long double x, long double eps);

long double fd(long double x, long double eps);

Status calc(long double (* f)(long double, long double), 
            long double eps, long double a, long double b, long double *out);