///
/// \file setupSim.cpp
/// \date  18.05.2010
/// \author Olli

// call by reference chosen as two return values in c not possible (other possibility: define a data structure containing both, here too complicated))
#include <iostream>
#include <vector>

#include "parameters.h"
#include "simulation.h"


using namespace std;

void setupSim (parameters& paramSUS, simulation& simuSUS)//attention: call by reference: changes to local variables xxxSUS affect global variables (params, simus) in main function
{
	//calculate left and right particle spacings based on constant mass
  double dxl, dxr, xmin, xmax;
    //some local copies needed
        xmin=paramSUS.xmin;
        xmax=paramSUS.xmax;
	paramSUS.dxl=paramSUS.mass/paramSUS.rhol;
	dxl=paramSUS.dxl;  //probably just as abbreviation

	paramSUS.dxr=paramSUS.mass/paramSUS.rhor;
	dxr=paramSUS.dxr;  //probably just as abbreviation

	// parameters for constant particle spacing
	double dx=paramSUS.dx;  //probably just as abbreviation

	//particle locations

	vector<double> xl,xr,x;//declare empty vectors for left,right and the entire domain (not initialize them as they have to be empty (otherwise the assignment x.begin()messes up..)

	//for constant spacing:
	if (paramSUS.constspacing)
	{
		//calculate left hand spacing
		for(double i=0;i>xmin;i=i-dx)//loop starting at "0" backwards to ensure that there is in any case a particle at this position
			xl.insert(xl.begin(),i);
		xl.insert(xl.begin(),xmin);//inserts xmin, condition in for loop compares "double" values, no "equal" possible
		//calculate right hand spacing
		for(double i=0;i<paramSUS.xmax;i=i+dx)//loop starting at "0" to ensure that there is in any case a particle at this position

			xr.insert(xr.end(),i);
		xr.insert(xr.end(),xmax);//inserts xmax, condition in for loop compares "double" values, no "equal" possible
	}
	else //if not constant spacing
	{	//in this case: positionning a particle at xmin/xmax is not implemented!

		//calculate left hand spacing
		for(double i=0;i>xmin;i=i-dxl)//loop starting at "0" backwards to ensure that there is in any case a particle at this position
			xl.insert(xl.begin(),i);

		//calculate right hand spacing
		for(double i=0;i<xmax;i=i+dxr)//loop starting at "0" to ensure that there is in any case a particle at this position
			xr.insert(xr.end(),i);
	};

	///merging the two vectors
       	//x.reserve(xl.size() + xr.size()); //reserves size for x (
       	x.insert(x.end(), xl.begin(), xl.end()-1); //insert the first vector (leaving out "0")
       	x.insert(x.end(), xr.begin(), xr.end()); //insert the second.


//now one can determine the number of particles
	paramSUS.np=x.size();

//finally initial conditions for simulation can be set up
	  simuSUS.x=x; //affect positions to simulation data structure
	//initialization of "intermediate" vectors, size must be included as otherwise assignment "vect[i]=x does NOT work!!!
	vector<double> uleft(xl.size()),uright(xr.size()),rholeft(xl.size()),rhoright(xr.size()),pleft(xl.size()),pright(xr.size()),eleft(xl.size()),eright(xr.size()), mleft(xl.size()),mright(xr.size()),hleft(xl.size()),hright(xr.size());
	//initialize left hand side
	for (int i=0;i<(int)xl.size();i++)
	{
		uleft[i]=paramSUS.ul;
		rholeft[i]=paramSUS.rhol;
		pleft[i]=paramSUS.pl;
		eleft[i]=pleft[i]/(paramSUS.gamma-1)/rholeft[i];   // ideal gas equation of state
		mleft[i]=paramSUS.mass;
		hleft[i]=paramSUS.h;
	};

	//initialize right hand side
	for (int i=0;i<(int)xr.size();i++)
	{
	   	uright[i]=paramSUS.ur;
	   	rhoright[i]=paramSUS.rhor;
	   	pright[i]=paramSUS.pr;
	   	eright[i]=pright[i]/(paramSUS.gamma-1)/rhoright[i];  // ideal gas equation of state
	   	mright[i]=paramSUS.mass;
	   	hright[i]=paramSUS.h;
   };

	//merging the two sides
	simuSUS.u.insert(simuSUS.u.end(), uleft.begin(), uleft.end()-1); //insert the first vector
	simuSUS.u.insert(simuSUS.u.end(), uright.begin(), uright.end()); //insert the second
	simuSUS.rho.insert(simuSUS.rho.end(), rholeft.begin(), rholeft.end()-1); //insert the first vector
	simuSUS.rho.insert(simuSUS.rho.end(), rhoright.begin(), rhoright.end()); //insert the second
	simuSUS.p.insert(simuSUS.p.end(), pleft.begin(), pleft.end()-1); //insert the first vector
	simuSUS.p.insert(simuSUS.p.end(), pright.begin(), pright.end()); //insert the second
	simuSUS.e.insert(simuSUS.e.end(), eleft.begin(), eleft.end()-1); //insert the first vector
	simuSUS.e.insert(simuSUS.e.end(), eright.begin(), eright.end()); //insert the second
	simuSUS.m.insert(simuSUS.m.end(), mleft.begin(), mleft.end()-1); //insert the first vector
	simuSUS.m.insert(simuSUS.m.end(), mright.begin(), mright.end()); //insert the second
	simuSUS.h.insert(simuSUS.h.end(), hleft.begin(), hleft.end()-1); //insert the first vector
	simuSUS.h.insert(simuSUS.h.end(), hright.begin(), hright.end()); //insert the second
	//initialize current time step variable
	simuSUS.k=0;

	//if constant spacing is chosen and value dx given: mass results of rho and dx (and not mass&rho->dx), if mass was given as well: too few degrees of freedom!
	//Remark: in this case the mass vector calculated above is overwritten (more elegant solution: take mass calculation from above and put it into else...but needs extra loops...)
	if (paramSUS.constspacing)
	{
		//calculate left hand side mass
		for (int i=0;i<(int)xl.size();i++)
			{
				mleft[i]=paramSUS.rhol*paramSUS.dx;
			};
		//calculate right hand side mass
		for (int i=0;i<(int)xr.size();i++)
			{
				mright[i]=paramSUS.rhor*paramSUS.dx;
			};
		//merge vectors
		simuSUS.m.clear();
		simuSUS.m.insert(simuSUS.m.end(), mleft.begin(), mleft.end()); //insert the first vector
		simuSUS.m.insert(simuSUS.m.end(), mright.begin(), mright.end()); //insert the second
	};

	//initialize all derivatives vectors with zeros
	simuSUS.du.assign((int)simuSUS.x.size(),0);
	simuSUS.de.assign((int)simuSUS.x.size(),0);
	simuSUS.drho.assign((int)simuSUS.x.size(),0);
}

