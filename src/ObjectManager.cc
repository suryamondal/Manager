#include "ObjectManager.h"

void ObjectManager::WriteOut() {
  for(const auto& name : m_WriteOut) {
    auto* file = GetObject<TFile>(name);
    if(file) {
      TString filename = file->GetName();
      std::cout<<" writing out : "<<filename<<std::endl;
      file->Write();
    }
  }
  std::cout<<" writing out : success"<<std::endl;
}

ObjectManager* ObjectManager::instance = nullptr;

ObjectManager* ObjectManager::Instance()
{
  if (instance == nullptr) {
    static ObjectManager manager;
    instance = &manager;
  }
  return instance;
}

void ObjectManager::SetGroup(const TString& group, const TString& fname)
{
  auto* tfile = GetObject<TFile>(fname);
  if(tfile) {
    if(group != "") tfile->mkdir(group);
    tfile->cd(group);
  }
}

void ObjectManager::fillHisto(const TString& name, const double& value, const double& wt)
{
  TH1* h = GetObject<TH1>(name);
  if(h) h->Fill(value, wt);
}

void ObjectManager::fillHisto(const TString& name, const double& value1, const double& value2, const double& wt)
{
  TH2* h = GetObject<TH2>(name);
  if(h) h->Fill(value1, value2, wt);
}

void ObjectManager::fillHisto(const TString& name, const double& value1, const double& value2, const double& value3, const double& wt)
{
  TH3* h = GetObject<TH3>(name);
  if(h) h->Fill(value1, value2, value3, wt);
}
