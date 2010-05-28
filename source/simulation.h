///
/// \file simulation.h
/// \date  18.05.2010
/// \author Olli



//includes c++ vector
#include <vector>

using namespace std;


//to avoid multiple inclusions
#ifndef SIMULATION_H_
#define SIMULATION_H_

///
/// \brief defines a data structure containing all variables which are used during simulation
///
/// vectors are used to store variables which have to be computed for each particle (one vector component represents one particle)
struct simulation
{
vector <double> x;  ///< positions (of particles)
vector <double> u;  ///<velocity (of particles)
vector <double> du; ///<derivative of velocity
vector <double> rho;  ///<density
vector <double> drho;  ///<derivative of density
vector <double> p; ///<pressure
vector <double> e;  ///<internal energy
vector <double> de; ///<derivative of internal energy
vector <double> m;  ///<mass
vector <double> h;  ///<smoothing length
vector <double> Wij; ///<vector representing the value of the kernel function for each interaction pair
vector <double> dWij;  ///<vector representing the derivative of the kernel function for each interaction pair
vector <int> count; ///<vector counting the number of interactions for each particle (for every particle one vector component) (sum of all entries in count must be the double of niac ( as each interaction has 2 contributors)
vector <int> pairi; ///<vector where each component contains number of one interaction partner
vector <int> pairj; ///<vector where each component contains number of other interaction partner

int k;  ///<current time step
int niac;  ///<total number of interactions (for all particles together)

};

#endif /* SIMULATION_H_ */
