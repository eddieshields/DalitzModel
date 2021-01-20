#ifndef D02KSKK_DALITZPLOT_H
#define D02KSKK_DALITZPLOT_H

// Package.
#include "phasespace.h"
#include "amplitude.h"
#include "lhcbstyle.h"

// SL.
#include <iostream>
#include <string>
#include <vector>

// ROOT.
#include "TCanvas.h"
#include "TH2.h"
#include "TGraph.h"
#include "TStyle.h"

namespace DalitzModel {

/** @brief DalitzPlot class used to plots and projections of a Dalitz Plot.
 * 
 * Given the masses of the of the particles invloved in the decay, this class
 * provides methods for plotting an amplitude models dalitz plot and projections
 * of it. Further methods can be used to configure the plots.
 * 
 * @author Edward Shields
 * @date   05/11/2020
 */
class DalitzPlot
{
public:
  /** Constructor. */
  DalitzPlot() = default;
  DalitzPlot(PhaseSpace& ps) :
    m_ps( ps )
  {
    lhcbStyle();
  }
  /** Constructor. */
  DalitzPlot(const double& mMother, const double& m1, const double& m2, const double& m3) :
    m_ps( mMother, m1, m2, m3 )
  {
    lhcbStyle();
  }
  /** Destructor. */
  virtual ~DalitzPlot() {};

  /** Returns canvas with Dalitz plot. */
  TCanvas* plot(TH2* his);
  /** Returns projection of Dalitz plot. */
  TCanvas* plotProjection(TH2* his, std::string var = "x");
  /** Returns projections of multiple dalitz plots. Takes vector of histograms as input. */
  TCanvas* plotProjection(std::vector<TH2*> hiss, std::string var = "x");

  /** Set unit of variables. */
  void setUnit(std::string unit) { m_unit = unit; }
  /** Set X-axis title. */
  void setXtitle(std::string xaxis) { m_xaxis = xaxis; }
  /** Set Y-axis title. */
  void setYtitle(std::string yaxis) { m_yaxis = yaxis; }

private:
  void decorate(TH2* his);
  void setBoundaryOptions(TGraph* boundary);
  TGraph* setBoundary(const int& boundary_points = 1000);

  std::string m_unit = {std::string("MeV/#it{c}^{2}")};
  std::string m_xaxis = {std::string("m^{2}(K_{S}^{0}K^{+})")};
  std::string m_yaxis = {std::string("m^{2}(K_{S}^{0}K^{-})")};

  PhaseSpace m_ps;
};

TCanvas* DalitzPlot::plot(TH2* his)
{
  TGraph* boundary = setBoundary();
  decorate(his);

  gStyle->SetPalette( kBird );
  gStyle->SetPadRightMargin(0.14);

  TCanvas* canv = new TCanvas("canv","canv",650,600);
  canv->cd();
  gPad->SetFixedAspectRatio();

  his->Draw("COLZ");
  boundary->Draw("SAME L");

  canv->Update();

  return canv;
}

TCanvas* DalitzPlot::plotProjection(TH2* his, std::string var)
{
  decorate(his);

  gStyle->SetPadRightMargin(0.05);

  TCanvas* canv = new TCanvas("canv","canv",650,600);
  canv->cd();

  TH1* proj;
  if ( var == std::string("x") ) proj = his->ProjectionX();
  else if ( var == std::string("y") ) {
    proj = his->ProjectionY();
    proj->GetXaxis()->ImportAttributes(his->ProjectionX()->GetXaxis());
  }
  proj->GetYaxis()->SetTitle("|A|^{2}");

  proj->Draw("HIST");

  canv->Update();

  return canv;
}

TCanvas* DalitzPlot::plotProjection(std::vector<TH2*> hiss, std::string var)
{
  decorate( hiss[0] );
  gStyle->SetPadRightMargin(0.05);

  TCanvas* canv = new TCanvas("canv","canv",650,600);
  canv->cd();

  TH1* proj;
  if ( var == std::string("x") ) proj = hiss[0]->ProjectionX();
  else if ( var == std::string("y") ) {
    proj = hiss[0]->ProjectionY();
    proj->GetXaxis()->ImportAttributes(hiss[0]->ProjectionX()->GetXaxis());
  }
  proj->GetYaxis()->SetTitle("|A|^{2}");  

  proj->Draw("HIST");

  for (int i = 1; i < hiss.size(); i++) {
    if ( var == std::string("x") ) hiss[i]->ProjectionX()->Draw("SAME HIST");
    else if ( var == std::string("y") ) hiss[i]->ProjectionY()->Draw("SAME HIST");
  }

  canv->Update();

  return canv;
}

void DalitzPlot::decorate(TH2* his)
{
  his->GetXaxis()->SetTitle( (m_xaxis+std::string(" [")+m_unit+std::string("]")).c_str() );
  his->GetYaxis()->SetTitle( (m_yaxis+std::string(" [")+m_unit+std::string("]")).c_str() );
}

void DalitzPlot::setBoundaryOptions(TGraph* boundary)
{
  boundary->SetLineWidth(2);
  boundary->SetLineColor(kRed);
  boundary->SetMarkerColor(kRed);
  boundary->SetMarkerStyle(8);
  boundary->SetMarkerSize(0.4);
}

TGraph* DalitzPlot::setBoundary(const int& boundary_points)
{
  // Fill vectors with boundary points.
  std::vector< double > _mSqABbound, _mSqBCbound;
  double step = ( m_ps.mSq12max() - m_ps.mSq12min() ) / boundary_points;
  double mSqAB = m_ps.mSq12min();
  while ( mSqAB < m_ps.mSq12max() ) {
      _mSqABbound.push_back( mSqAB );
      _mSqBCbound.push_back( m_ps.mSq13max( mSqAB ) );
      mSqAB += step;
  }
  mSqAB -= step;
  while ( mSqAB > m_ps.mSq12min() ) {
      _mSqABbound.push_back( mSqAB );
      _mSqBCbound.push_back( m_ps.mSq13min( mSqAB ) );
      mSqAB -= step;
  }
  mSqAB += step;
  _mSqABbound.push_back( mSqAB );
  _mSqBCbound.push_back( m_ps.mSq13max( mSqAB ) );

  // Create boundary graph.
  TGraph* boundary = new TGraph( _mSqABbound.size(), _mSqABbound.data(), _mSqBCbound.data() );

  // Set options.
  setBoundaryOptions( boundary );

  return boundary;
}

} // namespace DalitzModel

#endif