#ifndef DALITZMODEL_PHASESPACE_H
#define DALITZMODEL_PHASESPACE_H

#include <iostream>
#include <cmath>

namespace DalitzModel {

class PhaseSpace
{
private:
  const double m_mMother;
  const double m_m1;
  const double m_m2;
  const double m_m3;

  const double m_mSqMother = std::pow( m_mMother , 2 );
  const double m_mSq1 = std::pow( m_m1 , 2 );
  const double m_mSq2 = std::pow( m_m2 , 2 );
  const double m_mSq3 = std::pow( m_m3 , 2 );

  const double m_mSqSum = std::pow( m_mMother , 2 ) + std::pow( m_m1 , 2 ) + std::pow( m_m2 , 2 ) + std::pow( m_m3 , 2);

public:
  // Constructor/Destructor.
  PhaseSpace(const double& mMother, const double& m1, const double& m2, const double& m3): 
    m_mMother( mMother ),
    m_m1( m1 ),
    m_m2( m2 ),
    m_m3( m3 )
  {};
  virtual ~PhaseSpace() {};

  // Getters.
  const double m(const int& i) const;
  const double mSq(const int& i) const;

  const double mMother() const { return m_mMother; }
  const double m1() const { return m_m1; }
  const double m2() const { return m_m2; }
  const double m3() const { return m_m3; }

  const double mSqMother() const { return m_mSqMother; }
  const double mSq1() const { return m_mSq1; }
  const double mSq2() const { return m_mSq2; }
  const double mSq3() const { return m_mSq3; }

  const double mSqSum() const { return m_mSqSum; }

  const double mSq12min() const { return std::pow( (m_m1 + m_m2) , 2 ); }
  const double mSq12max() const { return std::pow( (m_mMother - m_m3) , 2 ); }
  const double mSq13min() const { return std::pow( (m_m1 + m_m3) , 2 ); }
  const double mSq13max() const { return std::pow( (m_mMother - m_m2) , 2 ); }
  const double mSq23min() const { return std::pow( (m_m2 + m_m3) , 2 ); }
  const double mSq23max() const { return std::pow( (m_mMother - m_m1) , 2 ); }

  const double mSq13min(const double& mSq12) const;
  const double mSq13max(const double& mSq12) const;
  const double mSq23min(const double& mSq12) const;
  const double mSq23max(const double& mSq12) const;

  const bool contains(const double& mSq12, const double& mSq13) const;
  const bool contains(const double& mSq12, const double& mSq13, const double& mSq23) const;

  const double kallen(const double& x, const double& y, const double& z) const;
};

const double PhaseSpace::m(const int& i) const
{
  if ( i == 0 ) return m_mMother;
  if ( i == 1 ) return m_m1;
  if ( i == 2 ) return m_m2;
  if ( i == 3 ) return m_m3;
  return 0.;
}

const double PhaseSpace::mSq(const int& i) const
{
  if ( i == 0 ) return m_mSqMother;
  if ( i == 1 ) return m_mSq1;
  if ( i == 2 ) return m_mSq2;
  if ( i == 3 ) return m_mSq3;
  return 0.;
}

const double PhaseSpace::mSq13min(const double& mSq12 ) const
{
  double first  = std::pow( m_mSqMother + m_mSq1 - m_mSq2 - m_mSq3, 2 );
  double second = std::sqrt( kallen( mSq12, m_mSq1     , m_mSq2 ) );
  double third  = std::sqrt( kallen( mSq12, m_mSqMother, m_mSq3 ) );

  return ( first - std::pow( second + third, 2 ) ) / ( 4. * mSq12 );
}


const double PhaseSpace::mSq13max(const double& mSq12 ) const
{
  double first  = std::pow( m_mSqMother + m_mSq1 - m_mSq2 - m_mSq3, 2 );
  double second = std::sqrt( kallen( mSq12, m_mSq1     , m_mSq2 ) );
  double third  = std::sqrt( kallen( mSq12, m_mSqMother, m_mSq3 ) );

  return ( first - std::pow( second - third, 2 ) ) / ( 4. * mSq12 );
}

const double PhaseSpace::mSq23min( const double& mSq12 ) const
{
  double first  = std::pow( m_mSqMother - m_mSq1 + m_mSq2 - m_mSq3, 2 );
  double second = std::sqrt( kallen( mSq12, m_mSq1     , m_mSq2 ) );
  double third  = std::sqrt( kallen( mSq12, m_mSqMother, m_mSq3 ) );

  return ( first - std::pow( second + third, 2 ) ) / ( 4. * mSq12 );
}

const double PhaseSpace::mSq23max( const double& mSq12 ) const
{
  double first  = std::pow( m_mSqMother - m_mSq1 + m_mSq2 - m_mSq3, 2 );
  double second = std::sqrt( kallen( mSq12, m_mSq1     , m_mSq2 ) );
  double third  = std::sqrt( kallen( mSq12, m_mSqMother, m_mSq3 ) );

  return ( first - std::pow( second - third, 2 ) ) / ( 4. * mSq12 );
}

const bool PhaseSpace::contains( const double& mSq12, const double& mSq13 ) const
{
  const double& mSq23 = m_mSqSum - mSq12 - mSq13;

  return ( ( mSq13 > mSq13min( mSq12 ) ) && ( mSq13 < mSq13max( mSq12 ) ) &&
         ( mSq23 > mSq23min( mSq12 ) ) && ( mSq23 < mSq23max( mSq12 ) ) );
}

const bool PhaseSpace::contains(const double& mSq12, const double& mSq13, const double& mSq23) const
{
    if ( ( mSq12min()      < mSq12 && mSq12 < mSq12max() ) 
      && ( mSq13min(mSq12) < mSq13 && mSq13 < mSq13max(mSq12) ) 
      && ( mSq23min(mSq12) < mSq23 && mSq23 < mSq23max(mSq12) ) ) return true;
    return false;
}

const double PhaseSpace::kallen( const double& x, const double& y, const double& z ) const
{
  double result = 0.;
  result += std::pow( x, 2 );
  result += std::pow( y, 2 );
  result += std::pow( z, 2 );
  result -= 2. * x * y;
  result -= 2. * x * z;
  result -= 2. * y * z;

  return result;
}

} // DalitzModel

#endif