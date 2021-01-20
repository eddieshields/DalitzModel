// DalitzModel.
#include "relbreitwigner.h"
#include "flatte.h"
#include "parameter.h"
#include "configfile.h"
#include "configureamplitude.h"
#include "dalitzplot.h"
#include "msgservice.h"

// ROOT.
#include "TH2.h"
#include "TAxis.h"
#include "TCanvas.h"

int main()
{
  DalitzModel::ConfigureAmplitude configure("cfg/babar2008.cfg");
  DalitzModel::Amplitude amp = configure();
  
  TH2D* hist = new TH2D("hist","hist",1000,amp.ps().mSq12min(),amp.ps().mSq12max(),1000,amp.ps().mSq13min(),amp.ps().mSq13max());

  double mSq12, mSq13;
  for (int i = 1; i < hist->GetNbinsX() + 1; i++) {
    for (int j = 1; j < hist->GetNbinsY() + 1; j++) {
      mSq12 = hist->GetXaxis()->GetBinCenter(i);
      mSq13 = hist->GetYaxis()->GetBinCenter(j);
      hist->SetBinContent(i,j,amp.AdirSq(mSq12,mSq13));
    }
  }

  DalitzModel::DalitzPlot dp( amp.ps() );

  TCanvas* canv = dp.plot( hist );
  canv->Print("figs/dalitzplot.png");

  canv = dp.plotProjection( hist , "x" );
  canv->Print("figs/dalitzplot_x.png");

  canv = dp.plotProjection( hist , "y" );
  canv->Print("figs/dalitzplot_y.png");
  
  return 0;
}