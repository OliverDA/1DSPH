///
/// \file W.cpp
/// \date  18.05.2010
/// \author Olli


#include <math.h>

//kernel funktion W is cubic B-spline with support of 4h
double W(double deltaX, double h)
{
	//to be more efficient, all "constant" variables could be declared (only once and not every time the function is called) in parameters structure
	double W_;
	double alphaD=1/h; //coefficient for cubic spline kernel in 1D (see Liu eq(3.6), page 64)
	double r =fabs(deltaX);	//r: distance between the particles
	double R= r/h; //nondimensional distance
	if(R>2)//support of 4h, everything beyond is zero
	{
		W_=0;
	}
	else if(R<1)
	{
		W_=(double)2/3-pow(R,2)+0.5*pow(R,3); //attention: the "^"symbol does NOT mean "exponent"!!!
	}
	else
	{
		W_=(double)1/6*pow((2-R),3);
	};
	W_=W_*alphaD;
	return W_;
}
