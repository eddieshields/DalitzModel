#ifndef DALITZMODEL_RELBREITWIGNER_H
#define DALITZMODEL_RELBREITWIGNER_H

// DalitzModel.
#include "resonance.h"

namespace DalitzModel {
  namespace LineShape {

using complex_t = std::complex<double>;

class RelBreitWigner : public Resonance
{
public:
  RelBreitWigner() = default;
  RelBreitWigner(std::string& name, const Coefficient& coeff,
            const int& resoA, const int& resoB,
            const Parameter& mass, const Parameter& width,
            const int& l, const Parameter& r) :
    Resonance( name , coeff , resoA , resoB , mass , width , l , r )
  {}
  RelBreitWigner(std::string& name, const double& coeff1, const double& coeff2,
            const int& resoA, const int& resoB,
            const double& mass, const double& width,
            const int& l, const double& r) :
    Resonance( name , coeff1 , coeff2 , resoA , resoB , mass , width , l , r )
  {}
  virtual ~RelBreitWigner() {}

  // Implementation of propagator.
  const complex_t propagator(const PhaseSpace& ps, const double& mSqAB) const;
  
  const double runningWidth(const PhaseSpace& ps, const double& mSqAB) const;

  RelBreitWigner* copy() const;
};

const complex_t RelBreitWigner::propagator(const PhaseSpace& ps, const double& mSqAB) const
{
  complex_t I( 0., 1. );
  return 1. / mSq() - mSqAB - I * m() * runningWidth(ps,mSqAB);
}

const double RelBreitWigner::runningWidth(const PhaseSpace& ps, const double& mSqAB) const
{
  return width()*( rho( ps, mSqAB )/rho( ps, mSq() ) )*std::pow( blattWeisskopf(ps, mSqAB) , 2 );
}

RelBreitWigner* RelBreitWigner::copy() const
{
  return new RelBreitWigner(*this);
}


  } // namespace LineShape
} // namespace DalitzModel

#endif