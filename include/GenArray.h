#pragma once

#include <iostream>
#include <memory>
#include <map>
#include <optional>
#include <iomanip>
#include <utility>

/** class to store array of data in N dimensions */
template<typename T, unsigned int N>
class GenArray {

public:

  GenArray() {};
  ~GenArray() {};

  /** Set an element to map */
  void SetEntry(const unsigned int *element, const T& val) {
    indentity nDim;
    for(int ij=0;ij<N;ij++) {nDim.point[ij] = element[ij];}
    arrayPtr[nDim] = val;
  };

  /** Get an element from map */
  T GetEntry(const unsigned int *element) {
    indentity nDim;
    for(int ij=0;ij<N;ij++) {nDim.point[ij] = element[ij];}
    auto it = arrayPtr.find(nDim);
    T val = (it != arrayPtr.end()) ? it->second : 0; 
    return val;
  };

protected:

  /** Identity of N-dim element
   *
   * Elements starts from 0
   */
  struct indentity {
    unsigned int point[N];
  };

  /** Array element map */
  std::map<indentity, T> arrayPtr;

};
