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
  std::vector<std::unique_ptr<Resonance>> m_resonances;
  std::vector<std::unique_ptr<Resonance>> m_cnjresonances;

  PhaseSpace m_ps;
public:
  Amplitude() = default;
  Amplitude(PhaseSpace& ps) :
    m_ps( ps )
  {}
  virtual ~Amplitude() {}

  void addResonance(Resonance* reso);
  void addResonance(std::unique_ptr<Resonance>& reso);

  const int size() const { return m_resonances.size(); }

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
};

void Amplitude::addResonance(std::unique_ptr<Resonance>& reso)
{
  m_resonances.push_back( std::move( reso ) );

  // Make conjugate copy of the resonance.
  std::unique_ptr<Resonance> resoCnj = std::unique_ptr<Resonance>(m_resonances[m_resonances.size()-1]->cnj_copy());
  m_cnjresonances.push_back( std::move( resoCnj ) );
}

void Amplitude::addResonance(Resonance* reso)
{
  std::unique_ptr<Resonance> unique_reso = std::unique_ptr<Resonance>(reso);
  addResonance( unique_reso );
}

std::ostream& operator<<(std::ostream& os, const Amplitude& amp)
{
  std::string out = "Resonances = ";
  for (int i = 0; i < amp.size(); i++) {
    out += amp.m_resonances[i]->name() + ", ";
  }
  out.replace(out.size()-2,2,"");
  os << out;
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

} // namespace DalitzModel

#endif