#ifndef DALITZMODEL_RESONANCE_H
#define DALITZMODEL_RESONANCE_H

// STL.
#include <iostream>
#include <string>
#include <complex>

// DalitzModel.
#include "parameter.h"
#include "coefficient.h"
#include "phasespace.h"

namespace DalitzModel {

using complex_t = std::complex<double>;

class Resonance
{
protected:
  Coefficient m_coeff;
  Parameter   m_mass;
  Parameter   m_width;
  Parameter   m_r;
  int         m_l;
  int         m_resoA;
  int         m_resoB;
  int         m_noRes;

  std::string m_name;

  bool        m_helicity = {false};

  double      m_massSq;
public:
  Resonance() = default;
  Resonance(std::string& name, const Coefficient& coeff,
            const int& resoA, const int& resoB,
            const Parameter& mass, const Parameter& width,
            const int& l, const Parameter& r) :
    m_name( name ),
    m_coeff( coeff ),
    m_mass( mass ),
    m_width( width ),
    m_r( r ),
    m_l( l ),
    m_resoA( resoA ),
    m_resoB( resoB )
  {
    m_massSq = m_mass * m_mass;
    m_noRes = 6 - m_resoA - m_resoB;
  }
  Resonance(std::string& name, const double& coeff1, const double& coeff2,
            const int& resoA, const int& resoB,
            const double& mass, const double& width,
            const int& l, const double& r) :
    m_name( name ),
    m_coeff( coeff1 , coeff2 ),
    m_mass( mass ),
    m_width( width ),
    m_r( r ),
    m_l( l ),
    m_resoA( resoA ),
    m_resoB( resoB )
  {
    m_massSq = m_mass * m_mass;
    m_noRes = 6 - m_resoA - m_resoB;
  }
  virtual ~Resonance() {}

  Resonance* cnj_copy() const;
  virtual Resonance* copy() const = 0;

  // Pointer for linked list.
  Resonance* next = {nullptr};

  // Propagator.
  virtual const complex_t propagator(const PhaseSpace& ps, const double& mSqAB) const = 0;

  // Operators.
  friend std::ostream& operator<<(std::ostream& os, const Resonance& reso);
  friend std::istream& operator>>(std::istream& is, Resonance& reso);

  // Getters.
  std::string name()  const { return m_name; }
  Parameter   mass()  const { return m_mass; }
  Parameter   m()     const { return m_mass; }
  double      mSq()   const { return m_massSq; }
  Parameter   width() const { return m_width; }
  Parameter   r()     const { return m_r; }
  int         l()     const { return m_l; }

  const complex_t evaluate(const PhaseSpace& ps, const double& mSq12, const double& mSq13);
  const complex_t evaluate(const PhaseSpace& ps, const double& mSq12, const double& mSq13, const double& mSq23);

  const double M2AB(const double& mSq12, const double& mSq13, const double& mSq23) const;
  const double M2AC(const double& mSq12, const double& mSq13, const double& mSq23) const;
  const double M2BC(const double& mSq12, const double& mSq13, const double& mSq23) const;

  // Methods.
  double kallen              (const double& x, const double& y, const double& z) const;
  double q                   (const PhaseSpace& ps, const double& mSqAB) const;
  double p                   (const PhaseSpace& ps, const double& mSqAB) const;
  double rho                 (const PhaseSpace& ps, const double& mSqAB) const;
  double zemach              (const PhaseSpace& ps, const double& mSqAB, const double& mSqAC, const double& mSqBC) const;
  double helicity            (const PhaseSpace& ps, const double& mSqAB, const double& mSqAC, const double& mSqBC) const;
  double blattWeisskopfPrime (const PhaseSpace& ps, const double& mSqAB) const;
  double blattWeisskopfPrimeP(const PhaseSpace& ps, const double& mSqAB) const;
  double blattWeisskopf      (const PhaseSpace& ps, const double& mSqAB) const;
  double angular             (const PhaseSpace& ps, const double& mSqAB, const double& mSqAC, const double& mSqBC) const;

};

Resonance* Resonance::cnj_copy() const
{
  Resonance* reso = this->copy();
  if ( this->m_resoA == 2 ) {
    reso->m_resoA = this->m_resoB;
    reso->m_resoB = this->m_resoA;
  }  else {
    int noRes = 6 - this->m_resoA - this->m_resoB;
    reso->m_resoA = this->m_resoA;
    reso->m_resoB = noRes;
  }
  reso->m_name = this->m_name + "_cnj";
  return reso;
}

// I/O operators.
std::ostream& operator<<(std::ostream& os, const Resonance& reso)
{
  os << reso.m_name;
  os << ": coeff = " << reso.m_coeff;
  os << ", resoA = " << reso.m_resoA;
  os << ", resoB = " << reso.m_resoB;
  os << ", mass = "  << reso.m_mass;
  os << ", width = " << reso.m_width;
  os << ", l = "     << reso.m_l;
  os << ", rBW = "   << reso.m_r;

  return os;
}

std::istream& operator>>(std::istream& is, Resonance& reso)
{
  // Input of the form "c1 c2 resoA resoB mass width l rBW".
  double c1, c2;
  is >> c1 >> c2
     >> reso.m_resoA
     >> reso.m_resoB
     >> reso.m_mass
     >> reso.m_width
     >> reso.m_l
     >> reso.m_r;
  reso.m_coeff = Coefficient(c1,c2);
}

const complex_t Resonance::evaluate(const PhaseSpace& ps, const double& mSq12, const double& mSq13, const double& mSq23)
{
  if ( !ps.contains(mSq12, mSq13) ) return 0.;
  double mSqAB = M2AB(mSq12, mSq13, mSq23);
  double mSqAC = M2AC(mSq12, mSq13, mSq23);
  double mSqBC = M2BC(mSq12, mSq13, mSq23);
  return m_coeff*propagator(ps, mSqAB)*angular(ps, mSqAB, mSqAC, mSqBC);
}

const complex_t Resonance::evaluate(const PhaseSpace& ps, const double& mSq12, const double& mSq13)
{
  double mSq23 = ps.mSqSum() - mSq12 - mSq13;
  return evaluate(ps, mSq12, mSq13, mSq23);
}

const double Resonance::M2AB(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  if ( m_noRes == 3 ) return mSq12;
  if ( m_noRes == 2 ) return mSq13;
  if ( m_noRes == 1 ) return mSq23;
  return 0.;
}

const double Resonance::M2AC(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  if ( m_resoB == 3 ) return mSq12;
  if ( m_resoB == 2 ) return mSq13;
  if ( m_resoB == 1 ) return mSq23;
  return 0.;
}

const double Resonance::M2BC(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  if ( m_resoA == 3 ) return mSq12;
  if ( m_resoA == 2 ) return mSq13;
  if ( m_resoA == 1 ) return mSq23;
  return 0.;
}

inline double Resonance::kallen(const double& x, const double& y, const double& z) const
{
  return std::pow( x , 2 ) + std::pow( y , 2 ) + std::pow( z , 2) - 2*x*y - 2*x*z - 2*y*z;
}

double Resonance::p(const PhaseSpace& ps, const double& mSqAB) const
{
  return std::sqrt( kallen( mSqAB, ps.mSq( m_resoA ), ps.mSq( m_resoB ) ) )/( 2*std::sqrt(mSqAB) );
}

double Resonance::q(const PhaseSpace& ps, const double& mSqAB) const
{
  return std::sqrt( kallen( mSqAB, ps.mSqMother(), ps.mSq( m_noRes ) ) )/( 2*std::sqrt(mSqAB) );
}

double Resonance::rho(const PhaseSpace& ps, const double& mSqAB) const
{
  return std::sqrt( kallen( mSqAB, ps.mSq( m_resoA ), ps.mSq( m_resoB ) ) )/mSqAB;
}

inline double Resonance::zemach(const PhaseSpace& ps, const double& mSqAB, const double& mSqAC, const double& mSqBC) const
{
  if ( m_l == 0 ) return 1;

  double diffSqMC = ps.mSqMother() - ps.mSq( m_noRes );
  double diffSqAB = ps.mSq(  m_resoA ) - ps.mSq(  m_resoB );
  double zemach1 = mSqAC - mSqBC - (diffSqMC*diffSqAB)/mSqAB;

  if ( m_l == 1 ) return zemach1;

  double sumSqMC = ps.mSqMother() + ps.mSq( m_noRes );
  double sumSqAB = ps.mSq(  m_resoA ) + ps.mSq(  m_resoB );
  double first  = mSqAB - 2*sumSqMC + std::pow( diffSqMC , 2 )/mSqAB;
  double second = mSqAB - 2*sumSqAB + std::pow( diffSqAB , 2 )/mSqAB;
        
  if ( m_l == 2 ) return std::pow( zemach1 , 2 ) - (first*second)/3;

  return 0.;
}

inline double Resonance::helicity(const PhaseSpace& ps, const double& mSqAB, const double& mSqAC, const double& mSqBC) const
{
  if ( m_l == 0 ) return 1.;

  const double& diffSqMC = ps.mSqMother() - ps.mSq( m_noRes );
  const double& diffSqAB = ps.mSq(  m_resoA ) - ps.mSq(  m_resoB );
  const double& hel1  = mSqAC - mSqBC - diffSqMC * diffSqAB / mSq();

  if ( m_l == 1 ) return hel1;

  const double& sumSqMC = ps.mSqMother()   + ps.mSq( m_noRes );
  const double& sumSqAB = ps.mSq(  m_resoA ) + ps.mSq(  m_resoB );
  double first  = mSqAB - 2. * sumSqMC + std::pow( diffSqMC, 2 ) / mSq();
  double second = mSqAB - 2. * sumSqAB + std::pow( diffSqAB, 2 ) / mSq();

  if ( m_l == 2 ) return std::pow( hel1, 2 ) - first * second / 3.;

  return 0.;
}

inline double Resonance::blattWeisskopfPrime(const PhaseSpace& ps, const double& mSqAB) const
{
  if ( m_l == 0 ) return 1.;

  double q0 = q( ps, mSq() );
  double qm = q( ps, mSqAB );
  double rq0Sq = std::pow( r()*q0 , 2 );
  double rqmSq = std::pow( r()*qm , 2 );

  if ( m_l == 1 ) return std::sqrt( ( 1 + rq0Sq )/( 1 + rqmSq ) );
  if ( m_l == 2 ) return std::sqrt( ( 9 + 3*rq0Sq + std::pow( rq0Sq , 2 ) )/( 9 + 3*rqmSq + std::pow( rqmSq , 2 ) ) );
  return 0.;
}

inline double Resonance::blattWeisskopfPrimeP(const PhaseSpace& ps, const double& mSqAB) const
{
  if ( m_l == 0 ) return 1.;

  double p0 = p( ps, mSq() );
  double pm = p( ps, mSqAB );
  double rp0Sq = std::pow( r()*p0 , 2 );
  double rpmSq = std::pow( r()*pm , 2 );

  if ( m_l == 1 ) return std::sqrt( ( 1 + rp0Sq )/( 1 + rpmSq ) );
  if ( m_l == 2 ) return std::sqrt( ( 9 + 3*rp0Sq + std::pow( rp0Sq , 2 ) )/( 9 + 3*rpmSq + std::pow( rpmSq , 2 ) ) );
  return 0.;
}

double Resonance::blattWeisskopf(const PhaseSpace& ps, const double& mSqAB) const 
{
  if ( m_l == 0 ) return 1.;

  double q0 = q( ps, mSq() );
  double qm = q( ps, mSqAB );
  return std::pow( qm/q0 , m_l )*blattWeisskopfPrime(ps, mSqAB);
}

double Resonance::angular(const PhaseSpace& ps, const double& mSqAB, const double& mSqAC, const double& mSqBC) const
{
  if ( m_helicity ) return helicity(ps, mSqAB, mSqAC, mSqBC)*blattWeisskopfPrimeP(ps, mSqAB)*blattWeisskopfPrime(ps, mSqAB);
  return zemach(ps, mSqAB, mSqAC, mSqBC)*blattWeisskopfPrimeP(ps, mSqAB)*blattWeisskopfPrime(ps, mSqAB);
}

}

#endif