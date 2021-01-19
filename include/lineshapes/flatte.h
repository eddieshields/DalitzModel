#ifndef DALITZMODEL_FLATTE_H
#define DALITZMODEL_FLATTE_H

// DalitzModel.
#include "resonance.h"

namespace DalitzModel {
  namespace LineShape {

using complex_t = std::complex<double>;

class Flatte : public Resonance
{
private:
  Parameter m_g1;
  Parameter m_g2;
  Parameter m_m11;
  Parameter m_m12;
  Parameter m_m21;
  Parameter m_m22;

  double m_g1Sq;
  double m_g2Sq;
  double m_m11Sq;
  double m_m12Sq;
  double m_m21Sq;
  double m_m22Sq;
public:
  Flatte() = default;
  Flatte(std::string& name, const Coefficient& coeff,
            const int& resoA, const int& resoB,
            const Parameter& mass, const Parameter& width,
            const int& l, const Parameter& r,
            const Parameter& g1, const Parameter& g2,
            const Parameter& m11, const Parameter& m12, const Parameter& m21, const Parameter& m22) :
    Resonance( name , coeff , resoA , resoB , mass , width , l , r ),
    m_g1( g1 ),
    m_g2( g2 ),
    m_m11( m11 ),
    m_m12( m12 ),
    m_m21( m21 ),
    m_m22( m22 )
  {
    m_g1Sq  = m_g1 * m_g1;
    m_g2Sq  = m_g2 * m_g2;
    m_m11Sq = m_m11 * m_m11;
    m_m12Sq = m_m12 * m_m12;
    m_m21Sq = m_m21 * m_m21;
    m_m22Sq = m_m22 * m_m22;
  }
  Flatte(std::string& name, const double& coeff1, const double& coeff2,
            const int& resoA, const int& resoB,
            const double& mass, const double& width,
            const int& l, const double& r,
            const double& g1, const double& g2,
            const double& m11, const double& m12, const double& m21, const double& m22) :
    Resonance( name , coeff1 , coeff2 , resoA , resoB , mass , width , l , r ),
    m_g1( g1 ),
    m_g2( g2 ),
    m_m11( m11 ),
    m_m12( m12 ),
    m_m21( m21 ),
    m_m22( m22 )
  {
    m_g1Sq  = m_g1 * m_g1;
    m_g2Sq  = m_g2 * m_g2;
    m_m11Sq = m_m11 * m_m11;
    m_m12Sq = m_m12 * m_m12;
    m_m21Sq = m_m21 * m_m21;
    m_m22Sq = m_m22 * m_m22;
  }
  virtual ~Flatte() {}

  const complex_t propagator(const PhaseSpace& ps, const double& mSqAB) const;

  const double rho1(const PhaseSpace& ps, const double& mSqAB) const;
  const double rho2(const PhaseSpace& ps, const double& mSqAB) const;

  Flatte* copy() const;

  Parameter g1()  { return m_g1; }
  Parameter g2()  { return m_g2; }
  Parameter m11() { return m_m11; }
  Parameter m12() { return m_m12; }
  Parameter m21() { return m_m21; }
  Parameter m22() { return m_m22; }

  double g1Sq()   { return m_g1Sq; }
  double g2Sq()   { return m_g2Sq; }
  double m11Sq()  { return m_m11Sq; }
  double m12Sq()  { return m_m12Sq; }
  double m21Sq()  { return m_m21Sq; }
  double m22Sq()  { return m_m22Sq; }
};

const complex_t Flatte::propagator(const PhaseSpace& ps, const double& mSqAB) const
{
  const complex_t I(0.,1.);
  return m_g1 / ( mSq() - mSqAB - I*(rho1(ps,mSqAB)*m_g1Sq + rho2(ps,mSqAB)*m_g2Sq ) );
}

const double Flatte::rho1(const PhaseSpace& ps, const double& mSqAB) const
{
  return std::sqrt( kallen( mSqAB, m_m11Sq , m_m12Sq ) )/mSqAB;
}

const double Flatte::rho2(const PhaseSpace& ps, const double& mSqAB) const
{
  return std::sqrt( kallen( mSqAB, m_m21Sq, m_m22Sq ) )/mSqAB;
}

Flatte* Flatte::copy() const
{
  return new Flatte(*this);
}

  } // namespace LineShape
} // namespace DalitzModel

#endif