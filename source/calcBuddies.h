///
/// \file calcBuddies.h
/// \date  18.05.2010
/// \author Olli

#ifndef CALCBUDDIES_H_
#define CALCBUDDIES_H_

/*! \brief calculates neighbors (which are located within the support domain) for each particle
 *  \param simuCB  a pointer to the data struct parameters ("call by reference")
 *  \param paramCB a pointer to the data struct parameters ("call by reference")
 *
 *
 *  \return nothing (void) as call by reference
 */
void calcBuddies(simulation& simuCB,parameters& paramCB);

#endif /* CALCBUDDIES_H_ */

