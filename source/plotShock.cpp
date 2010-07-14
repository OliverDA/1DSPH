///
/// \file plotShock.cpp
/// \date  18.05.2010
/// \author Olli

//updates the diagramm by adding new values
// perhaps I will not directly plot to a diagram but instead write the results into a file, which can then be post procssed...

#include <iostream>
#include <fstream>
#include<cstring>
#include <sstream>
#include <iomanip>



#include "simulation.h"

using namespace std;

void plotShock(simulation& simuPS)
{
	//some variables needed to construct the output file name (with ongoing numbers)
	string file;
	string firstPart = "../outdata/dataStep";
	string fileEnding = ".txt";
	stringstream number;


	//reads number of timesteps into stringstream

	  number << setw(6) << setfill('0') << simuPS.k;

	//composes filename
	file = firstPart+number.str()+fileEnding;
	cout<<file<<endl;

	//cast the std..string to a char string (normal c string)which is needed as filename
	char *filename = const_cast<char *>(file.c_str());
	cout<<filename<<endl;

	ofstream txtFile(filename);
	if (txtFile.is_open())
	{
		for(int i=0;i<(int)simuPS.x.size();i++)
		{
		  txtFile <<setprecision (10)<< ::setw( 20 )<<simuPS.x[i]<<::setw(5)<<0.0<<::setw( 20 )<<simuPS.rho[i]<<::setw( 20 )<<simuPS.p[i]<<::setw( 20 )<<simuPS.u[i]<<::setw( 20 )<<simuPS.e[i]<<endl;
//			txtFile << "This is another line.\n";
		}
		txtFile.close();
	}
		else cout << "Unable to open/create file";

}
