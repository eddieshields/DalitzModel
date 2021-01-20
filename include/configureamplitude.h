#ifndef DALITZMODEL_CONFIGUREAMPLITUDE_H
#define DALITZMODEL_CONFIGUREAMPLITUDE_H

// DalitzModel.
#include "relbreitwigner.h"
#include "flatte.h"
#include "coefficient.h"
#include "parameter.h"
#include "amplitude.h"
#include "configfile.h"
#include "msgservice.h"

namespace DalitzModel {

class ConfigureAmplitude
{
private:
  ConfigFile m_config;
  Amplitude  m_amp;

  void build_model_from_file();
  void build_phasespace_from_file();
  void build_resonance_from_file(std::string name);
public:
  ConfigureAmplitude() = default;
  ConfigureAmplitude(const std::string cfgfile) :
    m_config( cfgfile )
  {}
  virtual ~ConfigureAmplitude() {}

  // Operators.
  friend std::ostream& operator<<(std::ostream& os, const ConfigureAmplitude& cfgamp);
  friend std::istream& operator>>(std::istream& is, ConfigureAmplitude& cfgamp);

  void appendRBW(std::string name);
  void appendFlatte(std::string name);

  Amplitude operator()() { build_model_from_file(); return m_amp; }
};

void ConfigureAmplitude::build_model_from_file()
{
  DEBUG("Building model");
  build_phasespace_from_file();
  std::stringstream resos( m_config.get("resos") );
  std::string res;
  while ( resos >> res ) {
    build_resonance_from_file( res );
  }
  return;
}

void ConfigureAmplitude::build_phasespace_from_file()
{
  DEBUG("Building PhaseSpace");
  double mM = m_config.get<double>("mMoth");
  double m1 = m_config.get<double>("m1");
  double m2 = m_config.get<double>("m2");
  double m3 = m_config.get<double>("m3");
  PhaseSpace ps(mM,m1,m2,m3);
  m_amp.setPhaseSpace( ps );
}

void ConfigureAmplitude::build_resonance_from_file(std::string name)
{
  DEBUG("Building Resonances");
  std::stringstream res( m_config.get(name) );
  std::string type;
  res >> type;

  if ( type == "RBW" ) {
    appendRBW( name );
  } else if ( type == "CC" ) {
    appendFlatte( name );
  } else {
    WARNING("Unrecognised type " << type);
  }
  return;
}

void ConfigureAmplitude::appendRBW(std::string name)
{
  DEBUG(m_config.get(name));
  std::stringstream res( m_config.get(name) );

  int resoA, resoB, l;
  // Parameters.
  std::string type, mass, width, radius, coeff1, coeff2;
  res >> type >> resoA >> resoB >> l
      >> mass >> width >> radius
      >> coeff1 >> coeff2;

  Parameter m     = m_config.get<Parameter>(mass);
  Parameter w     = m_config.get<Parameter>(width);
  Parameter r     = m_config.get<Parameter>(radius);
  Parameter c1    = m_config.get<Parameter>(coeff1);
  Parameter c2    = m_config.get<Parameter>(coeff2);

  Coefficient c( c1 , c2 );

  LineShape::RelBreitWigner* comp = new LineShape::RelBreitWigner(name,c,resoA,resoB,m,w,l,r);
  m_amp.addResonance( comp );
}

void ConfigureAmplitude::appendFlatte(std::string name)
{
  std::stringstream res( m_config.get(name) );

  int resoA, resoB, l;
  // Parameters.
  std::string type, mass, width, radius, coeff1, coeff2, gam1name, gam2name, m1name, m2name;
  res >> type >> resoA >> resoB >> l
      >> mass >> width >> radius
      >> coeff1 >> coeff2
      >> gam1name >> gam2name >> m1name >> m2name;

  Parameter m     = m_config.get<Parameter>(mass);
  Parameter w     = m_config.get<Parameter>(width);
  Parameter r     = m_config.get<Parameter>(radius);
  Parameter c1    = m_config.get<Parameter>(coeff1);
  Parameter c2    = m_config.get<Parameter>(coeff2);
  Parameter gam1  = m_config.get<Parameter>(gam1name);
  Parameter gam2  = m_config.get<Parameter>(gam2name);
  Parameter m02a  = m_config.get<Parameter>(m1name);
  Parameter m02b  = m_config.get<Parameter>(m2name);

  Coefficient c( c1 , c2 );

  LineShape::Flatte* comp = new LineShape::Flatte(name,c,resoA,resoB,m,w,l,r,gam1,gam2,m02a,m02b);
  m_amp.addResonance(comp);
}

// I/O operators.
std::ostream& operator<<(std::ostream& os, const ConfigureAmplitude& cfgamp)
{
  return os;
}

std::istream& operator>>(std::istream& is, ConfigureAmplitude& cfgamp)
{
  is >> cfgamp.m_config;
  return is;
}

}

#endif