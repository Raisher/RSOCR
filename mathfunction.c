#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "mathfunction.h"

double random(double a, double b)
{
	return (b-a) * ((double) rand()/RAND_MAX) + a;
}

double sigmoid_f(double a)
{
	return 1.0 / (1.0*exp(-a));
}

int maths_between(int in, Uint16 l, Uint16 r)
{
	if (in > r)
		in=r;
	if (in<l)
		in=l;
	return in;
}

double dsig_f(double b)
{
	return sigmoid_f(b) * (1.0 - sigmoid_f(b));
}

