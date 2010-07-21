///
/// \file marchTime.cpp
/// \date  18.05.2010
/// \author Olli

//function that conducts numerical integration using leap frog scheme
//calls function . "calcDerivatives.cpp" and (if printstep condition is satisfied) "plotShock.cpp"

#include <iostream>  //for output on screen
#include <vector>
#include <stdlib.h> ///for exit command
#include<iomanip>
#include <fstream>

#include "calcDerivatives.h"
#include "parameters.h"
#include "simulation.h"
#include "plotShock.h"


using namespace std; //replaces prefix "std::" for each command


void marchTime (parameters& paramMT, simulation& simuMT)
{
	//define intermediate variables and initialize them to zero (needed for leap frog integration)
	vector <double> em1(paramMT.np,0),um1(paramMT.np,0),rhom1(paramMT.np,0);

	//control output
	cout<<endl<<"number of time steps"<<paramMT.nt<<endl;

	//for-loop for time integration using leap frog scheme
	for (int k=1;k<=paramMT.nt;k++)
	{
		//control output
		cout<<endl<<"Advancing timestep, current timestep k="<<k<<endl;

		//write current time step in corresponding simulation variable
		simuMT.k=k;

		//use current derivatives to take to next half step , only if not first time step!
		if(k!=1)//if not first time step
		{
			//save current values (which are @intermediate time step) in the intermediate variables
			em1=simuMT.e;
			um1=simuMT.u;
			if(!paramMT.sumdensity)//if we do not use the sumdensity approach (i.e we also have to integrate rho)...
			{
				// ... we also save the current value of rho
				rhom1=simuMT.rho;

				//and calculate the new rho (advance by half a time step)
				for(int i=0;i<(int)simuMT.x.size();i++)
					simuMT.rho[i]=simuMT.rho[i]+0.5*paramMT.dt*simuMT.drho[i];
			}

			//now we also calculate u,e at the full timestep
			for(int i=0;i<(int)simuMT.x.size();i++)
			{
				simuMT.e[i]=simuMT.e[i]+0.5*paramMT.dt*simuMT.de[i];
				simuMT.u[i]=simuMT.u[i]+0.5*paramMT.dt*simuMT.du[i];
				//just in case that e becomes negative (due to negative kernel/derivative contribution) which is not physical: replace negative values by "0"
				if(simuMT.e[i]<0)
				{
					simuMT.e[i]=0;
				}
			}
		}

ofstream tFile("updateHalfUeN2");
	if (tFile.is_open())
        {
	  for(int i=(int)simuMT.x.size()-1;i>=0;i--) {
	  
	  tFile <<setprecision(9)<< ::setw( 5 )<<i+1<<::setw(16)<<simuMT.x[i]+2<< ::setw(16)<<simuMT.u[i]<<::setw(15)<<0<<::setw(15)<<simuMT.e[i]<<endl;
	
	  }
	tFile.close();
	}
		else cout << "Unable to open/create file";



		// we call here (remember: u,e, are at full timestep (either calculated above or (if first timestep)=initial values) the calcDerivatives function to get new derivatives
		calcDerivatives(simuMT,paramMT);

		if(k==1)//if first time step
		{
			if(!paramMT.sumdensity)//if we do not use the sumdensity approach, we must calculate the density solving the diff eq (-->integrating time step)
			{
				for(int i=0;i<(int)simuMT.x.size();i++)
				{
					simuMT.rho[i]=simuMT.rho[i]+0.5*paramMT.dt*simuMT.drho[i];
				};
			}

			//calculate u,e at intermediate timestep (dt/2)
			for(int i=0;i<(int)simuMT.x.size();i++)
			{
				simuMT.e[i]=simuMT.e[i]+0.5*paramMT.dt*simuMT.de[i];
				simuMT.u[i]=simuMT.u[i]+0.5*paramMT.dt*simuMT.du[i];
				//just in case that e becomes negative (due to negative kernel derivative contribution) which is not physical: replace negative values by "0"
				if(simuMT.e[i]<0)
				{
					simuMT.e[i]=0;
				};
				//now advance the particles a full step (with the velocity at 1/2 step)
				simuMT.x[i]=simuMT.x[i]+paramMT.dt*simuMT.u[i];
			};
		}
		else  //if not the first step: use standard leap
		{
			if(!paramMT.sumdensity)//if we dnoot use the sumdensity approach, we must calculate the desnity solving the diff eq (-->integrating time step)
			{
				for(int i=0;i<(int)simuMT.x.size();i++)
				{
					simuMT.rho[i]=rhom1[i]+paramMT.dt*simuMT.drho[i];
				};
			};
			for(int i=0;i<(int)simuMT.x.size();i++)
			{//calculate new e, u, always at intermediate time step (as um1,em1 are calculated at dt/2 (see above) and now we advance a full step)
				simuMT.e[i]=em1[i]+paramMT.dt*simuMT.de[i];
				simuMT.u[i]=um1[i]+paramMT.dt*simuMT.du[i];
				//again: just in case that e becomes negative (due to negative kernel derivative contribution) which is not physical: replace negative values by "0"
				if(simuMT.e[i]<0)
				{
					simuMT.e[i]=0;
				}
				//advance particles now (always a full step) with velocity at 1/2 step
				simuMT.x[i]=simuMT.x[i]+paramMT.dt*simuMT.u[i];
			};
		};

		if(k%paramMT.printstep==0)//if k multiple of printstep-->print results
		{
			//write the date into a file...
			plotShock(simuMT);
		};

		//check if simulation unstable: criterion: check maximum velocity of all particles at each timestep and stop simulation if max exceeds a certain limit!
		//first determine the maximum velocity in the u-vector
		double max=simuMT.u[0];
		for (int i=0; i<(int)simuMT.u.size(); i++)
		{
			if (simuMT.u[i]>max)
			{
				max = simuMT.u[i];
			};
		};
		//then test the criterion
		if (max>paramMT.maxU)
		{
			cout<<endl<<"simulation unstable";
			exit(1);//quit program, alternative: return 0
		};

	};
}

