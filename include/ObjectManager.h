#pragma once

#include <iostream>
#include <memory>
#include <map>
#include <optional>
#include <iomanip>
#include <utility>
#include <string>
#include <type_traits>
#include <vector>

#include "TMath.h"
#include "TString.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TFile.h"

class ObjectManager {

 public:

  ObjectManager() {};
  ~ObjectManager() {
    for(const auto& name : m_WriteOut) {
      auto* file = GetObject(name);
      if(file) {
	TString option = ((TFile*)file)->GetOption();
	TString filename = ((TFile*)file)->GetName();
	if(option != "READ") {
	  std::cout<<" writing out with option "<<option<<" : "<<filename<<std::endl;
	  ((TFile*)file)->Write();
	}
      }
    }
  };

  /** Static referance to the singleton */
  static ObjectManager& Instance();
  
  template<class T>
    void SetObject(const TString& name, T *obj)
    {
      auto& hist = m_Objects[name];
      if(std::is_same_v<TFile, T>) {
	m_WriteOut.push_back(name);
      }
      if(!hist) {
	hist.reset(obj);
	std::cout<<" stored "<<name<<" of type "<<typeid(*obj).name()<<std::endl;
      }
    }

  void* GetObject(const TString& name)
  {
    auto hist = m_Objects.find(name);
    if(hist != m_Objects.end()) {
      return hist->second.get();
    } else {return nullptr;}
  }

  void SetGroup(const TString& group = "Extras", const TString& fname = "OutputRootFile")
  {
    auto* tfile = GetObject(fname);
    if(tfile) {
      ((TFile*)tfile)->mkdir(group);
      ((TFile*)tfile)->cd(group);
    }
  }

 protected:
  /** Map holding pointers to all created Objects */
  std::map<TString, std::shared_ptr<void>> m_Objects;

  /** Map holding groups of all objects */
  std::map<TString, TString> m_objGroups;

  /** Map holding groups of all objects */
  std::vector<TString> m_WriteOut;

};
