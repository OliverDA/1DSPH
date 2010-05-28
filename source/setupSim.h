///
/// \file setupSim.h
/// \date  18.05.2010
/// \author Olli


#ifndef SETUPSIM_H_
#define SETUPSIM_H_

/*! \brief sets up initial conditions for simulation
 *  \param paramSUS a pointer to the data struct parameters ("call by reference")
 *  \param simuSUS  a pointer to the data struct parameters ("call by reference")
 *
 *  \return nothing (void) as call by reference
 */
void setupSim (parameters& paramSUS, simulation& simuSUS);

#endif /* SETUPSIM_H_ */
