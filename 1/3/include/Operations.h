#include <stdbool.h>
#include "Status.h"

bool cmp(long double , long double , long double );
Status getAllSollutions(long double, long double*, long double (*)[6], int*);
Status isMultiple(long double, long double, bool*);
Status isTriangle(long double, long double, long double, long double, bool*);