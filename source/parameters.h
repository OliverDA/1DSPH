///
/// \file parameters.h
/// \date  18.05.2010
/// \author Olli


//to avoid multiple inclusions (which would lead to an compiler error)
#ifndef PARAMETERS_H_
#define PARAMETERS_H_

///
/// \brief defines an own data structure containing all parameters (geomerty, fluid properties, ...)
///
/// as values do not change during simulation they are declared "static constant" (otherwise an assignment of a value in the headerfile is not accepted)
///values for parameters which are not assigned in the headerfile are computed in the setupSimulation function
struct parameters
{
	//flags
	static const bool constspacing = false; ///<if true: uses const. (initial) spacing defined below (otherwise: constant mass, and (initial) spacing adapted according to rho)
	static const bool sumdensity = true; ///<if true, sums density instead of integrating eq.

	//geometry and mass
	static const double xmin = -1.00;///<domain left border
	static const double xmax = 1.00; ///<domain right border
	static const double mass = 0.001875; ///<(const.) mass of a single particle (in case of "const mass" calculation
	static const double h = 0.015; ///<smoothing length, make sure smaller (according to matlab comment!?!) than dxl, dxr
	static const double fac = 2; ///<factor used for calculating the influence of particles (=1/2 of support length which is here 4h)


	//
	//variables for particle spacings
	//a) based on constant mass:
	double dxl; ///<declaration of left hand side particle spacing variable
	double dxr; ///<declaration of right hand side particle spacing variable

	//b) constant spacing
	static const double dx = 0.005;///<dx for option "constant spacing"

	//left and right quantities of density, velocity, and pressure
	static const double rhol =  1.0;///<initial value for left hand density
	static const double rhor =  0.125;///<initial value for right hand density
	static const double ul   =  0.0;///<initial value for left hand velocity
	static const double ur   =  0.0;///<initial value for right hand velocity
	static const double pl   =  1.0;///<initial value for left hand pressure
	static const double pr   =  0.1;///<initial value for right hand pressure

	//other parameters
	int np; ///<number of particles
	static const int nt = 80; ///< number of time steps
	static const double dt = 0.0025; //</time step, lower time step if unstable, CFL is not obvious
	static const int max_interactions = 10000; ///< number of maximum interactions list (=number of max interactions per time step)
	static const double gamma = 1.4; ///< gas constant for "air"
	static const double epsilon = 0.1; ///<parameter for Monaghan artificial viscosity
	static const double alpha = 1.0;  ///<parameter for Monaghan artificial viscosity
	static const double beta = 2.0;  ///<parameter for Monaghan artificial viscosity
	static const int printstep = 1; ///< every "printstep"th step's results are written in (a separate) output data file
	static const double maxU=10000; ///<value for velocity not to be exceeded (program abort criterion)

};
#endif /* PARAMETERS_H_ */
