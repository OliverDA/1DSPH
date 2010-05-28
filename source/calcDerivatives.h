///
/// \file calcDerivatives.h
/// \date  18.05.2010
/// \author Olli

#include "simulation.h"
#include "parameters.h"

#ifndef CALCDERIVATIVES_H_
#define CALCDERIVATIVES_H_

/*! \brief calculates derivatives de, du, drho
 *
 * 	...using the SPH formulation of the equations of fluid dynamics
 *\param simuCD  a pointer to the data struct parameters ("call by reference")
 *\param paramCD a pointer to the data struct parameters ("call by reference")
 *
 *  \return nothing (void) as call by reference
 */
void calcDerivatives(simulation& simuCD,parameters& paramCD);

#endif /* CALCDERIVATIVES_H_ */
