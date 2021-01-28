#include "relbreitwigner.h"
#include "flatte.h"
#include "parameter.h"
#include "configfile.h"
#include "configureamplitude.h"
#include "msgservice.h"

int main()
{
  DalitzModel::ConfigureAmplitude configure("cfg/babar2008.cfg");
  DalitzModel::Amplitude amp = configure();
  INFO( amp );
  return 0;
}