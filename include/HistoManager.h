#pragma once

#include <iostream>
#include <memory>
#include <map>
#include <optional>
#include <iomanip>
#include <utility>

#include "TMath.h"
#include "TString.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TFile.h"


class HistoManager {

public:

  HistoManager() {};
  ~HistoManager() {};

  /** Static referance to the singleton */
  static HistoManager& Instance();

  /** Create Root File */
  void setRootFile(const TString& filename);

  /** create new histograms
   * All in double
   */
  void createHisto(const TString& name, const TString& title,
		   const int& binx, const double& minx, const double& maxx);
  void createHisto(const TString& name, const TString& title,
		   const int& binx, const double& minx, const double& maxx,
		   const int& biny, const double& miny, const double& maxy);
  void createHisto(const TString& name, const TString& title,
		   const int& binx, const double& minx, const double& maxx,
		   const int& biny, const double& miny, const double& maxy,
		   const int& binz, const double& minz, const double& maxz);

  /** get histogram for a given name */
  TH1* getHistogramH1(const TString& name);
  TH2* getHistogramH2(const TString& name);
  TH3* getHistogramH3(const TString& name);

  /** Fill the values into the corresponding histogram */
  void fillValue(const TString& name, const double& value, const double& wt);
  void fillValue(const TString& name, const double& value1, const double& value2, const double& wt);
  void fillValue(const TString& name, const double& value1, const double& value2, const double& value3, const double& wt);

  /** push histogram */
  void setHistogram(TH1* histo);
  void setHistogram(TH2* histo);
  void setHistogram(TH3* histo);

  /** Groups of Histograms */
  void setGroup(const TString& name, const TString& group);
  TString getGroup(const TString& name) const;

  /** Create group in root file */
  void createGroup(const TString& group);

protected:
  /** Map holding pointers to all created histograms */
  std::map<TString, std::unique_ptr<TH1>> m_histograms_h1;
  std::map<TString, std::unique_ptr<TH2>> m_histograms_h2;
  std::map<TString, std::unique_ptr<TH3>> m_histograms_h3;

  /** Map holding groups of all histograms
   *
   * Names of histograms must be unique irrespective of dimensions. So one map is enough
   */
  std::map<TString, TString> m_histoGroups;

  /** TFile pointer */
  std::unique_ptr<TFile> m_rootFile;

};
