#ifndef DALITZMODEL_AMPLITUDE_H
#define DALITZMODEL_AMPLITUDE_H

// STL.
#include <iostream>
#include <vector>
#include <memory>

// DalitzModel.
#include "resonance.h"
#include "phasespace.h"

namespace DalitzModel {

using complex_t = std::complex<double>;

class Amplitude
{
private:
  std::vector<Resonance*> m_resonances;
  std::vector<Resonance*> m_cnjresonances;

  PhaseSpace m_ps;
public:
  Amplitude() = default;
  Amplitude(PhaseSpace& ps) :
    m_ps( ps )
  {}
  virtual ~Amplitude() {}

  void setPhaseSpace(PhaseSpace& ps);
  void addResonance(Resonance* reso);

  const int size() const { return m_resonances.size(); }
  PhaseSpace& phasespace() { return m_ps; }
  PhaseSpace& ps()         { return m_ps; }

  // Operators.
  friend std::ostream& operator<<(std::ostream& os, const Amplitude& amp);

  const complex_t Adir  (const double& mSq12, const double& mSq13) const ;
  const complex_t Adir  (const double& mSq12, const double& mSq13, const double& mSq23) const;
  const complex_t Abar  (const double& mSq12, const double& mSq13) const ;
  const complex_t Abar  (const double& mSq12, const double& mSq13, const double& mSq23) const;

  const double    AdirSq(const double& mSq12, const double& mSq13) const;
  const double    AdirSq(const double& mSq12, const double& mSq13, const double& mSq23) const;
  const double    AbarSq(const double& mSq12, const double& mSq13) const;
  const double    AbarSq(const double& mSq12, const double& mSq13, const double& mSq23) const;

  const complex_t A1    (const double& mSq12, const double& mSq13) const ;
  const complex_t A1    (const double& mSq12, const double& mSq13, const double& mSq23) const;
  const complex_t A2    (const double& mSq12, const double& mSq13) const ;
  const complex_t A2    (const double& mSq12, const double& mSq13, const double& mSq23) const;

  const double    A1Sq  (const double& mSq12, const double& mSq13) const;
  const double    A1Sq  (const double& mSq12, const double& mSq13, const double& mSq23) const;
  const double    A2Sq  (const double& mSq12, const double& mSq13) const;
  const double    A2Sq  (const double& mSq12, const double& mSq13, const double& mSq23) const;

  // Individual resonances.
  const complex_t Adir  (std::string name, const double& mSq12, const double& mSq13) const ;
  const complex_t Adir  (std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const;
  const complex_t Abar  (std::string name, const double& mSq12, const double& mSq13) const ;
  const complex_t Abar  (std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const;

  const double    AdirSq(std::string name, const double& mSq12, const double& mSq13) const;
  const double    AdirSq(std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const;
  const double    AbarSq(std::string name, const double& mSq12, const double& mSq13) const;
  const double    AbarSq(std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const;

  const complex_t A1    (std::string name, const double& mSq12, const double& mSq13) const ;
  const complex_t A1    (std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const;
  const complex_t A2    (std::string name, const double& mSq12, const double& mSq13) const ;
  const complex_t A2    (std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const;

  const double    A1Sq  (std::string name, const double& mSq12, const double& mSq13) const;
  const double    A1Sq  (std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const;
  const double    A2Sq  (std::string name, const double& mSq12, const double& mSq13) const;
  const double    A2Sq  (std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const;
};

void Amplitude::setPhaseSpace(PhaseSpace& ps)
{
  m_ps = ps;
}

void Amplitude::addResonance(Resonance* reso)
{
  m_resonances.push_back( std::move( reso ) );

  // Make conjugate copy of the resonance.
  Resonance* resoCnj = m_resonances[m_resonances.size()-1]->cnj_copy();
  m_cnjresonances.push_back( std::move( resoCnj ) );
}

std::ostream& operator<<(std::ostream& os, const Amplitude& amp)
{
  std::string out = "Resonances = \n";
  os << out;
  for (int i = 0; i < amp.size(); i++) {
    os << *amp.m_resonances[i] << "\n";
  }
  return os;
}

const complex_t Amplitude::Adir(const double& mSq12, const double& mSq13) const
{
  complex_t A(0.,0.);
  for (int i = 0; i < size(); i++) {
    A += m_resonances[i]->evaluate( m_ps , mSq12 , mSq13 );
  }
  return A;
}

const complex_t Amplitude::Adir(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  complex_t A(0.,0.);
  for (int i = 0; i < size(); i++) {
    A += m_resonances[i]->evaluate( m_ps , mSq12 , mSq13 , mSq23 );
  }
  return A;
}

const complex_t Amplitude::Abar(const double& mSq12, const double& mSq13) const
{
  complex_t A(0.,0.);
  for (int i = 0; i < size(); i++) {
    A += m_cnjresonances[i]->evaluate( m_ps , mSq12 , mSq13 );
  }
  return A;
}

const complex_t Amplitude::Abar(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  complex_t A(0.,0.);
  for (int i = 0; i < size(); i++) {
    A += m_cnjresonances[i]->evaluate( m_ps , mSq12 , mSq13 , mSq23 );
  }
  return A;
}

const double Amplitude::AdirSq(const double& mSq12, const double& mSq13) const
{
  return std::norm( Adir( mSq12, mSq13 ) );
}

const double Amplitude::AdirSq(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return std::norm( Adir( mSq12, mSq13 , mSq23 ) );
}

const double Amplitude::AbarSq(const double& mSq12, const double& mSq13) const
{
  return std::norm( Abar( mSq12, mSq13 ) );
}

const double Amplitude::AbarSq(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return std::norm( Abar( mSq12, mSq13, mSq23 ) );
}

const complex_t Amplitude::A1(const double& mSq12, const double& mSq13) const
{
  return ( Adir( mSq12 , mSq13 ) + Abar( mSq12 , mSq13 ) ) / 2.;
}

const complex_t Amplitude::A1(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return ( Adir( mSq12 , mSq13 , mSq23 ) + Abar( mSq12 , mSq13 , mSq23 ) ) / 2.;
}

const complex_t Amplitude::A2(const double& mSq12, const double& mSq13) const
{
  return ( Adir( mSq12 , mSq13 ) - Abar( mSq12 , mSq13 ) ) / 2.;
}


const complex_t Amplitude::A2(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return ( Adir( mSq12 , mSq13 , mSq23 ) - Abar( mSq12 , mSq13 , mSq23 ) ) / 2.;
}

const double Amplitude::A1Sq(const double& mSq12, const double& mSq13) const
{
  return std::norm( A1( mSq12 , mSq13 ) );
}

const double Amplitude::A1Sq(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return std::norm( A1( mSq12 , mSq13 , mSq23 ) );
}

const double Amplitude::A2Sq(const double& mSq12, const double& mSq13) const
{
  return std::norm( A2( mSq12 , mSq13 ) );
}

const double Amplitude::A2Sq(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return std::norm( A2( mSq12 , mSq13 , mSq23 ) );
}

// Individual resonances.
const complex_t Amplitude::Adir(std::string name, const double& mSq12, const double& mSq13) const
{
  complex_t A(0.,0.);
  for (int i = 0; i < size(); i++) {
    if ( m_resonances[i]->name() != name ) continue;
    A += m_resonances[i]->evaluate( m_ps , mSq12 , mSq13 );
  }
  return A;
}

const complex_t Amplitude::Adir(std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const
{
  complex_t A(0.,0.);
  for (int i = 0; i < size(); i++) {
    if ( m_resonances[i]->name() != name ) continue;
    A += m_resonances[i]->evaluate( m_ps , mSq12 , mSq13 , mSq23 );
  }
  return A;
}

const complex_t Amplitude::Abar(std::string name, const double& mSq12, const double& mSq13) const
{
  complex_t A(0.,0.);
  for (int i = 0; i < size(); i++) {
    if ( m_resonances[i]->name()+"_cnj" != name ) continue;
    A += m_cnjresonances[i]->evaluate( m_ps , mSq12 , mSq13 );
  }
  return A;
}

const complex_t Amplitude::Abar(std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const
{
  complex_t A(0.,0.);
  for (int i = 0; i < size(); i++) {
    if ( m_resonances[i]->name()+"_cnj" != name ) continue;
    A += m_cnjresonances[i]->evaluate( m_ps , mSq12 , mSq13 , mSq23 );
  }
  return A;
}

const double Amplitude::AdirSq(std::string name, const double& mSq12, const double& mSq13) const
{
  return std::norm( Adir( name, mSq12, mSq13 ) );
}

const double Amplitude::AdirSq(std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return std::norm( Adir( name, mSq12, mSq13 , mSq23 ) );
}

const double Amplitude::AbarSq(std::string name, const double& mSq12, const double& mSq13) const
{
  return std::norm( Abar( name, mSq12, mSq13 ) );
}

const double Amplitude::AbarSq(std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return std::norm( Abar( name, mSq12, mSq13, mSq23 ) );
}

const complex_t Amplitude::A1(std::string name, const double& mSq12, const double& mSq13) const
{
  return ( Adir( name, mSq12 , mSq13 ) + Abar( name, mSq12 , mSq13 ) ) / 2.;
}

const complex_t Amplitude::A1(std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return ( Adir( name, mSq12 , mSq13 , mSq23 ) + Abar( name, mSq12 , mSq13 , mSq23 ) ) / 2.;
}

const complex_t Amplitude::A2(std::string name, const double& mSq12, const double& mSq13) const
{
  return ( Adir( name, mSq12 , mSq13 ) - Abar( name, mSq12 , mSq13 ) ) / 2.;
}


const complex_t Amplitude::A2(std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return ( Adir( name, mSq12 , mSq13 , mSq23 ) - Abar( name, mSq12 , mSq13 , mSq23 ) ) / 2.;
}

const double Amplitude::A1Sq(std::string name, const double& mSq12, const double& mSq13) const
{
  return std::norm( A1( name, mSq12 , mSq13 ) );
}

const double Amplitude::A1Sq(std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return std::norm( A1( name, mSq12 , mSq13 , mSq23 ) );
}

const double Amplitude::A2Sq(std::string name, const double& mSq12, const double& mSq13) const
{
  return std::norm( A2( name, mSq12 , mSq13 ) );
}

const double Amplitude::A2Sq(std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return std::norm( A2( name, mSq12 , mSq13 , mSq23 ) );
}

} // namespace DalitzModel

#endif