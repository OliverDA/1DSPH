///
/// \file W.h
/// \date  18.05.2010
/// \author Olli


#ifndef W_H_
#define W_H_

/*! \brief calculates kernel function
 *
 * the kernel used is a cubic spline function with a supoprt of 4h (Monaghan and Lattanzio (1985))
 *  \param deltaX the value of the distance of the two particles in question
 *  \param h the smoothing length (if variable smoothing length: use averaged smoothing length to ensure that interaction is not assymetric)
 *
 *  \return value of kernel function as double
 */
double W(double deltaX, double h);

#endif /* W_H_ */
