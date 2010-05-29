///
/// \file main.cpp
/// \date  18.05.2010
/// \author Olli


/*****the following section contains no comments related to the code****************************************
 *****it only contains doxygen (documentation generator) information for front page building*******
 */

/*! \mainpage 1D Smoothed-particle hydrodynamics (SPH) code
 *
 * \section intro_sec Introduction
 *
 * this is a basic version of an 1D compressible SPH code which simulates (using the default settings) the following Shock Tube Situation:
  \verbatim
				left hand side			right hand side

  dimensions			[-1;0]				[0;1]
  rho				1.0				0.125
  p				1.0				0.1
  u				0.0				0.0
 \endverbatim
 * the Simulation computes 80 time steps, each one of 0.0025 (80*0.0025=0.2)
 *
 * \section install_sec Installation
 * Check the source code from github
 * \verbatim
git clone git://github.com/olliinurlaub/1DSPH \endverbatim
 *

 * \section com Compile
 * go to source folder and type
 * \verbatim 
make all
\endverbatim
 * \section sim Runnig simulations
 * still in source folder:
 * \verbatim
 ./1DSPH \endverbatim
 * \section vis Visuzalization
 *
 *a) go into outdata folder and run gnuplot
 * \verbatim
gnuplot
\endverbatim
 *
 *b) load the gnuplotscript using the following command
 * \verbatim
load 'plotScript2.p' \endverbatim
*/
/*************************************END DOXYGEN SECTION***************************/

/***********************************BEGIN CODE MAIN-FUNCTION************************/





//includes headerfiles for all functions (and data structures) used directly within main function
#include "parameters.h"
#include "simulation.h"
#include "setupSim.h"
#include "marchTime.h"


using namespace std;

/*!  int main ()
 *  \brief the main function
 *
 *  where first the initial condition setup function is called and then the time stepping function is executed
 *
 *  \return 0.
 */

int main ()
{


parameters param;  // creates an instance of the parameters data structure
simulation sims;   //creates an instance of the simulation data structure

//
// sets up initial Conditions for Simulation
setupSim(param, sims);



//execute time stepping function
marchTime(param, sims);

return 0;
}

