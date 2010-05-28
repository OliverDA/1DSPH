///
/// \file dW.h
/// \date  18.05.2010
/// \author Olli

#ifndef DW_H_
#define DW_H_

/*! \brief calculates kernel derivative
 *  \param deltaX the value of the distance of the two particles in question
 *  \param h the smoothing length (if variable smoothing length: use averaged smoothing length to ensure that interaction is not assymetric)
 *
 *  \return value of kernel derivative as double
 */
double dW(double deltaX, double h);

#endif /* DW_H_ */
