///
/// \file dW.cpp
/// \date  18.05.2010
/// \author Olli

#include <math.h>

//derivation of kernel function
double dW(double deltaX, double h)
{
	double d_W;
	double alphaD=1/h; //coefficient for cubic spline kernel in 1D (see Liu eq(3.6), page 64)
	double r =fabs(deltaX);	//r: distance between the particles
	double R= r/h; //nondimensional distance
	if(R>2)//support of 4h, everything beyond is zero
	{
		d_W=0;
	}
	else if(R<1)
	{
		d_W=-2*R+1.5*pow(R,2);
	}
	else
	{
		d_W=-((double)1)/2*pow((2-R),2);
	};

	d_W=d_W*alphaD*deltaX/r/h; //deltaX/r for the sign (-->*(+/-1) )!!!, h because of d/dr=d/dR*dR/dr (dR/dr=1/h)
	return d_W;
}
