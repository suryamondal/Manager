
#include <ctime>

#include "GenArray.h"
#include "ObjectManager.h"


void addBy(unsigned int* element, const int& incr, const unsigned int& index,
	   const unsigned int& maxval, const unsigned int& maxindex) {
  if(index < maxindex) {
    element[index] += incr;
    if(element[index] == maxval) {
      element[index] = 0;
      addBy(element, incr, index + 1, maxval, maxindex);
    }
  }
}


int main() {

  /** testing CMAKE_FLAG */
#ifdef DEBUG
  std::cout<<" debug "<<std::endl;
#endif

  /** testing array */

  GenArray<int, 10> testArray;
  unsigned int element[10] = {0};
  int value = 0;

  unsigned int start_s = clock();
  
  while(value<1e6) {
    testArray.SetEntry(element, value);
#ifdef DEBUG
    std::cout<<" set";
    for(unsigned int ij=0; ij<10; ij++) {
      std::cout<<" "<<element[ij];
    }
    std::cout<<" value "<<value<<std::endl;
#endif
    addBy(element, 1, 0, 10, 10);
    value++;
  }

  std::cout<<" store time "<<(clock()-start_s)/double(CLOCKS_PER_SEC)<<std::endl;
  start_s = clock();
 
  unsigned int element1[10] = {0};
  value = 0;
  
  while(value<1e6) {
    int readvalue = testArray.GetEntry(element1);
#ifdef DEBUG
    std::cout<<" get";
    for(unsigned int ij=0; ij<10; ij++) {
      std::cout<<" "<<element1[ij];
    }
    std::cout<<" value "<<readvalue<<std::endl;
#endif
    addBy(element1, 1, 0, 10, 10);
    value++;
  }

  std::cout<<" read time "<<(clock()-start_s)/double(CLOCKS_PER_SEC)<<std::endl;
  start_s = clock();

  std::cout<<" Dim "<<testArray.GetDimension()<<std::endl;
  std::cout<<" Size "<<testArray.GetSize()<<std::endl;


  std::cout<<"\n Now testing ObjectManager"<<std::endl;

  TFile *file = new TFile("test.root","recreate");
  ObjectManager::Instance().SetObject<TFile>("OutputRootFile", file);
  auto* file1 = ObjectManager::Instance().GetObject<void>("OutputRootFile");
  if(file1) std::cout<<" file1 "<<(&file1)<<std::endl;

  ObjectManager::Instance().SetGroup();
  TH1D *h1 = new TH1D("h1","h1",100,0,1);
  ObjectManager::Instance().SetObject<TH1D>("h1", h1);
  
  TFile *file2 = new TFile("test1.root");
  ObjectManager::Instance().SetObject<TFile>("InputRootFile", file2);

  ObjectManager::Instance().fillHisto("h1", 0.5, 1.);
  ObjectManager::Instance().fillHisto("h1", 0.5, 1.);
  ObjectManager::Instance().fillHisto("h1", 0.2, 1.5);

  ObjectManager::Instance().WriteOut();
  
  return 0;
}
