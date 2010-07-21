///
/// \file calcDerivatives.cpp
/// \date  18.05.2010
/// \author Olli

#include <vector>
#include<iostream>
#include <math.h>
#include <fstream>
#include<cstring>
#include <sstream>
#include <vector>
#include <iomanip>

#include "parameters.h"
#include "simulation.h"
#include "calcBuddies.h"
#include "W.h"

using namespace std;

void calcDerivatives(simulation& simuCD,parameters& paramCD)
{
	//declaration and initialization of sound speed vector
	vector <double> c(paramCD.np,0);

	//declaration of other variables needed in further calculations (mainly for artificial viscosity)
	double hij=0; //hij=1/2*(hi+hj)
	double cij=0; //cij=1/2*(ci+cj)
	double uij=0; //=ui-uj
	double xij=0; //=xi-xj
	double rhoij=0; //=1/2(rhoi+rhoj)
	double phiij=0; // according to formula monaghan artificial viscosity
	double piij=0; // according to formula monaghan artificial viscosity
	double sumui=0; // auxiliary variable for summing up all u contributions
	double sumuj=0; // auxiliary variable for summing up all u contributions
	double sumei=0; // auxiliary variable for summing up all e contributions
	double sumej=0; // auxiliary variable for summing up all e contributions
	double sumrhoi=0; // auxiliary variable for summing up all rho contributions
	double sumrhoj=0; // auxiliary variable for summing up all rho contributions

	//reset du, de, drho to zero for each timestep
	simuCD.du.assign(paramCD.np,0);
	simuCD.de.assign(paramCD.np,0);
	simuCD.drho.assign(paramCD.np,0);

	//call function that finds nearest neighbors and that calculates kernel value and kernel derivative for each interaction
	calcBuddies(simuCD,paramCD);

	//sum up for rho current step
	  if (paramCD.sumdensity||simuCD.k==1) //either if we are on first step (there we "smooth" density, don't know why this is useful, rho already given from initial condition), or we have chosen to calculate rho in "sum density" manner...
	{
		for (int i=0;i<paramCD.np;i++)//self contribution
		{
			simuCD.rho[i]=simuCD.m[i]*W(0,simuCD.h[i]);
		};

		for (int kay=0; kay<simuCD.niac;kay++)//pair or partner contribution
		{
			int i=simuCD.pairi[kay]; //only to keep following expressions shorter
			int j=simuCD.pairj[kay]; //only to keep following expressions shorter
			simuCD.rho[i]=simuCD.rho[i]+simuCD.m[j]*simuCD.Wij[kay]; //all contributions from  interacting particles in vector pairi
			simuCD.rho[j]=simuCD.rho[j]+simuCD.m[i]*simuCD.Wij[kay]; //all contributions from  interacting particles in vector pairj (Wji=Wij as kernel symmertic to x(~r)=0, no problem here!)
		};
	};


ofstream tx2tFi1le("SmoothedDensityN1");
	if (tx2tFi1le.is_open())
        {
	  for (int d=paramCD.np-1;d>=0;d--)//self contribution
	  {
	    tx2tFi1le <<setprecision (10)<< ::setw( 5 )<<d<< ::setw(25)<<simuCD.rho[d]<<endl;
	
	  }
	tx2tFi1le.close();
	}
		else cout << "Unable to open/create file";


	//calculate pressure and sound speed @ current step
	for(int i=0;i<paramCD.np;i++)
	{
		simuCD.p[i]=(paramCD.gamma-1)*simuCD.rho[i]*simuCD.e[i]; //ideal gas equation of state
		c[i]=sqrt(paramCD.gamma*(paramCD.gamma-1)*simuCD.e[i]); //according to formula for sound speed in ideal gas
	};

	  ofstream t3xtFile;

	//calculate forces at current step
	for (int kay=0; kay <simuCD.niac;kay++)
	{
		int i=simuCD.pairi[kay]; //again: only to keep following expressions shorter
		int j=simuCD.pairj[kay]; //again: only to keep following expressions shorter

		//calculate artificial viscosity, formula(4.66) in Liu book (refers to Monaghan)
		hij=0.5*(simuCD.h[i]+simuCD.h[j]);
		cij=0.5*(c[i]+c[j]);
		uij=simuCD.u[i]-simuCD.u[j];
		xij=simuCD.x[i]-simuCD.x[j];
		rhoij=0.5*(simuCD.rho[i]+simuCD.rho[j]);
		if (uij*xij<0)//that means: whenever in compression (as only then artificial viscosity applies)
		{
			phiij=(hij*uij*xij)/(pow(xij,2)+paramCD.epsilon*pow(hij,2)); //according to formula monaghan artificial viscosity
			piij=(-1*paramCD.alpha*cij*phiij+paramCD.beta*pow(phiij,2))/rhoij; //according to formula monaghan artificial viscosity
		}
		else //if no compression: artificial viscosity is zero
		{
			piij=0;
		};

		//get de/dt du/dt @ current step (according to SPH forulations of equations of fluid dynamics
		sumui=-simuCD.m[j]*(simuCD.p[i]/pow(simuCD.rho[i],2)+simuCD.p[j]/pow(simuCD.rho[j],2)+piij)*simuCD.dWij[kay];
		sumuj=simuCD.m[i]*(simuCD.p[i]/pow(simuCD.rho[i],2)+simuCD.p[j]/pow(simuCD.rho[j],2)+piij)*simuCD.dWij[kay]; //- as dWji =-dWij...
		sumei=0.5*sumui*(simuCD.u[j]-simuCD.u[i]);
		sumej=0.5*sumuj*(simuCD.u[i]-simuCD.u[j]);
		if(~paramCD.sumdensity)
		{
			//get drho/dt @ current step (according to SPH forulations of equations of fluid dynamics
		        //equation (2.18) Monaghan05 (not suitable for larger density ratios)
		         sumrhoi=simuCD.m[j]*(simuCD.u[i]-simuCD.u[j])*simuCD.dWij[kay];
	       	         sumrhoj=-simuCD.m[i]*(simuCD.u[j]-simuCD.u[i])*simuCD.dWij[kay];

		        //equation (2.17) Monaghan05 (better for larger density ratios)
			   // sumrhoi=simuCD.rho[i]*simuCD.m[j]/simuCD.rho[j]*(simuCD.u[i]-simuCD.u[j])*simuCD.dWij[kay];
			   // sumrhoj=-simuCD.rho[j]*simuCD.m[i]/simuCD.rho[i]*(simuCD.u[j]-simuCD.u[i])*simuCD.dWij[kay];

			simuCD.drho[i]=simuCD.drho[i]+sumrhoi;
			simuCD.drho[j]=simuCD.drho[j]+sumrhoj;
		}
		//sum up the contributions from all interactions affecting the particles in question
		simuCD.du[i]=simuCD.du[i]+sumui;
		simuCD.du[j]=simuCD.du[j]+sumuj;
		simuCD.de[i]=simuCD.de[i]+sumei;
		simuCD.de[j]=simuCD.de[j]+sumej;

	
		  t3xtFile.open ("ArtVisN1", fstream::in | fstream::out | fstream::app);

	  
		
		  t3xtFile <<setprecision (6)<< ::setw( 7 )<<i+1<<::setw(7)<<j+1<<::setw( 15 )<<piij<<endl;
//			txtFile << "This is another line.\n";
		
		t3xtFile.close();
		  
	


	};


       	ofstream tx2tFile("DerivativesN1");
	if (tx2tFile.is_open())
        {
	  for (int d=paramCD.np-1;d>=0;d--)//self contribution
	  {
	    tx2tFile <<setprecision (9)<< ::setw( 5 )<<d+1<< ::setw(25)<<simuCD.du[d]<<::setw(25)<<simuCD.de[d]<<endl;
	
	  }
	tx2tFile.close();
	}
		else cout << "Unable to open/create file";
       
 }
