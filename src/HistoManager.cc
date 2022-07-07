
#include "HistoManager.h"

HistoManager& HistoManager::Instance()
{
  static HistoManager v;
  return v;
}

void HistoManager::setRootFile(const TString& filename)
{
  if (!m_rootFile) m_rootFile.reset(new TFile(filename, "recreate"));
  else std::cout<<"Root file already exists"<<std::endl;
}

template<class T>
void HistoManager::createHisto(const TString& name, const TString& title,
			       const int& binx, const double& minx, const double& maxx)
{
  std::unique_ptr<T>& hist = m_histograms_h1[name];
  TString group = getGroup(name);
  createGroup(group); m_rootFile->cd(group);
  hist.reset(new T(name.Data(), title.Data(), binx, minx, maxx));
  std::cout<<"H1 : "<<name<<" created!"<<std::endl;
}

template<class T>
void HistoManager::createHisto(const TString& name, const TString& title,
			       const int& binx, const double& minx, const double& maxx,
			       const int& biny, const double& miny, const double& maxy)
{
  std::unique_ptr<T>& hist = m_histograms_h2[name];
  TString group = getGroup(name);
  createGroup(group); m_rootFile->cd(group);
  hist.reset(new T(name.Data(), title.Data(), binx, minx, maxx, biny, miny, maxy));
  std::cout<<"H2 : "<<name<<" created!"<<std::endl;
}

template<class T>
void HistoManager::createHisto(const TString& name, const TString& title,
			       const int& binx, const double& minx, const double& maxx,
			       const int& biny, const double& miny, const double& maxy,
			       const int& binz, const double& minz, const double& maxz)
{
  std::unique_ptr<T>& hist = m_histograms_h3[name];
  TString group = getGroup(name);
  createGroup(group); m_rootFile->cd(group);
  hist.reset(new T(name.Data(), title.Data(), binx, minx, maxx, biny, miny, maxy, binz, minz, maxz));
  std::cout<<"H3 : "<<name<<" created!"<<std::endl;
}

TH1* HistoManager::getHistogramH1(const TString& name)
{
  std::unique_ptr<TH1>& hist = m_histograms_h1[name];
  return hist.get();
}

TH2* HistoManager::getHistogramH2(const TString& name)
{
  std::unique_ptr<TH2>& hist = m_histograms_h2[name];
  return hist.get();
}

TH3* HistoManager::getHistogramH3(const TString& name)
{
  std::unique_ptr<TH3>& hist = m_histograms_h3[name];
  return hist.get();
}

void HistoManager::fillValue(const TString& name, const double& value, const double& wt)
{
  TH1* h = getHistogramH1(name);
  if(h) h->Fill(value, wt);
}

void HistoManager::fillValue(const TString& name, const double& value1, const double& value2, const double& wt)
{
  TH2* h = getHistogramH2(name);
  if(h) h->Fill(value1, value2, wt);
}

void HistoManager::fillValue(const TString& name, const double& value1, const double& value2, const double& value3, const double& wt)
{
  TH3* h = getHistogramH3(name);
  if(h) h->Fill(value1, value2, value3, wt);
}

void HistoManager::setHistogram(TH1* histo)
{
  TString name = histo->GetName();
  std::unique_ptr<TH1>& hist = m_histograms_h1[name];
  if(!hist) hist.reset(histo);
}

void HistoManager::setHistogram(TH2* histo)
{
  TString name = histo->GetName();
  std::unique_ptr<TH2>& hist = m_histograms_h2[name];
  if(!hist) hist.reset(histo);
}

void HistoManager::setHistogram(TH3* histo)
{
  TString name = histo->GetName();
  std::unique_ptr<TH3>& hist = m_histograms_h3[name];
  if(!hist) hist.reset(histo);
}

void HistoManager::setGroup(const TString& name, const TString& group)
{
  if(name != "" && group != "") m_histoGroups[name] = group;
}

TString HistoManager::getGroup(const TString& name) const
{
  TString val = "";
  auto element = m_histoGroups.find(name);
  if(element != m_histoGroups.end()) val = element->second;
  if(val == "") val = "Extras";
  return val;
}

void HistoManager::createGroup(const TString& group)
{
  m_rootFile->cd();
  m_rootFile->mkdir(group.Data(), "", true);
}
