///
/// \file calcBuddies.cpp
/// \date  18.05.2010
/// \author Olli

#include<iostream>
#include<vector>
#include<math.h> //for fabs-function (absolute value for floating/double numbers)
#include <fstream>
#include<cstring>
#include <sstream>
#include <iomanip>

#include <stdio.h>
#include <stdlib.h>

#include "simulation.h"
#include "parameters.h"
#include "W.h"
#include "dW.h"

using namespace std;

void calcBuddies(simulation& simuCB,parameters& paramCB)
{
	//initialize some variables (for an explanation of the variables see "simulation.h" headerfile which defines the data structure)(they have to be reset every time the function is called)
	simuCB.niac=0;
	simuCB.count.assign(paramCB.np,0);
	simuCB.pairi.assign(paramCB.max_interactions,0);
	simuCB.pairj.assign(paramCB.max_interactions,0);
	simuCB.Wij.assign(paramCB.max_interactions,0);
	simuCB.dWij.assign(paramCB.max_interactions,0);

	// now one has to check for each couple of particles if they are within their mutual support domain
	//here it is done the following way: the smoothing length (~support length) is averaged between two particles.
	//then it is tested if the distance between those two particles is such that they are within the averaged smoothing length
	//the smoothing length is averaged to ensure a symmetrical interaction (even if two particles have different smoothing (~suport) lengths, which can be the case if calculation is done with variable smoothing length)

	for(int i=0;i<paramCB.np-1;i++)//loop over all particles but the last (this one does not have a right hand neighbor)
	{
		for(int j=i+1;j<paramCB.np;j++)  //loop over all particles but the first (this one does not have a left hand neighbor)
		{
			//testing if they are within their support domain, if yes -->interaction
			if(fabs(simuCB.x[i]-simuCB.x[j])<(paramCB.fac*0.5*(simuCB.h[i]+simuCB.h[j])))
			{
				simuCB.niac=simuCB.niac+1; //increase number of total interactions
				simuCB.pairi[simuCB.niac-1]=i; //save the particles number (0-599) in this vector (!!! vector starts with 0!!!)
				simuCB.pairj[simuCB.niac-1]=j; //save the other particles number (0-599) in this vector (the same components (with number niac)  of each vector represent an interaction pair)
				simuCB.count[i]=simuCB.count[i]+1; //increase the number of interactions for particle i
				simuCB.count[j]=simuCB.count[j]+1; //increase the number of interactions for particle j
				simuCB.Wij[simuCB.niac-1]=W(simuCB.x[i]-simuCB.x[j],0.5*(simuCB.h[i]+simuCB.h[j])); //calculate W for interaction pair niac( input values: distance between particles and (averaged) smoothing length
				simuCB.dWij[simuCB.niac-1]=dW(simuCB.x[i]-simuCB.x[j],0.5*(simuCB.h[i]+simuCB.h[j])); //same for derivative of smoothing function

				//abort program when maximum interaction number is achieved!! (to avoid overflow)
				if(simuCB.niac==paramCB.max_interactions)
				{
					cout<<"more interactions than allowed";
					exit(1);
				};
			};
		};
	};

	ofstream txtFile("BuddiesN1");
	if (txtFile.is_open())
	{
	  for(int i=simuCB.niac-1;i>=0;i--)
		{
		  txtFile <<setprecision (9)<< ::setw( 7 )<<	simuCB.pairi[i]+1<<::setw(6)<<simuCB.pairj[i]+1<<::setw(17)<<fabs(simuCB.x[simuCB.pairi[i]]-simuCB.x[simuCB.pairj[i]])<<::setw( 17 )<<simuCB.Wij[i]<<::setw( 17 )<<simuCB.dWij[i]<<endl;
//			txtFile << "This is another line.\n";
		}
		txtFile.close();
	}
		else cout << "Unable to open/create file";

}
