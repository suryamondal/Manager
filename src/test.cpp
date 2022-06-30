
#include "GenArray.h"


int main() {

  /** testing CMAKE_FLAG */
#ifdef DEBUG
  std::cout<<" debug "<<std::endl;
#endif

  /** testing array */
  GenArray<double, 5> testArray;
  unsigned int element1[5] = {1,1,2,3,4};
  unsigned int element2[5] = {1,1,2,4,3};
  unsigned int element3[5] = {2,2,2,3,4};
  unsigned int element4[5] = {2,2,2,3,5};
  testArray.SetEntry(element1, 5);
  testArray.SetEntry(element2, 6);
  testArray.SetEntry(element3, 7);
  std::cout<<" entry "<<testArray.GetEntry(element1)<<std::endl;
  std::cout<<" entry "<<testArray.GetEntry(element2)<<std::endl;
  std::cout<<" entry "<<testArray.GetEntry(element3)<<std::endl;
  std::cout<<" entry "<<testArray.GetEntry(element4)<<std::endl;

  std::cout<<" Dim "<<testArray.GetDimension()<<std::endl;
  std::cout<<" Size "<<testArray.GetSize()<<std::endl;

  return 0;
}
