///
/// \file marchTime.h
/// \date  18.05.2010
/// \author Olli

#ifndef MARCHTIME_H_
#define MARCHTIME_H_


/*! \brief time stepping function (for integration)
 *
 * 	numerical integration is done using the leap frog scheme
 *  \param paramMT a pointer to the data struct parameters ("call by reference")
 *  \param simumT  a pointer to the data struct parameters ("call by reference")
 *
 *  \return nothing (void) as call by reference
 */
void marchTime (parameters& paramMT, simulation& simuMT);

#endif /* MARCHTIME_H_ */
