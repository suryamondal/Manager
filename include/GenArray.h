#pragma once

#include <iostream>
#include <memory>
#include <unordered_map>
#include <optional>
#include <iomanip>
#include <utility>
#include <bitset>
#include <string>

/** class to store array of data in N dimensions */
template<typename T, unsigned int N>
class GenArray {

public:

  GenArray() {};
  ~GenArray() {};

  /** Set an element to map */
  void SetEntry(const unsigned int *element, const T& val) {
    indentity nDim;
    for(unsigned int ij=0; ij<N; ij++) {nDim.point[ij] = element[ij];}
    arrayPtr[nDim] = val;
  };

  /** Get an element from map */
  T GetEntry(const unsigned int *element) const {
    indentity nDim;
    for(unsigned int ij=0; ij<N; ij++) {nDim.point[ij] = element[ij];}
    auto it = arrayPtr.find(nDim);
    T val = (it != arrayPtr.end()) ? it->second : 0; 
    return val;
  };

  /** Get dimension */
  unsigned int GetDimension() const { return N; };

  /** Get Size */
  unsigned int GetSize() const { return arrayPtr.size(); };

  /** Clear map */
  void Clear() { arrayPtr.clear(); };


protected:

  /** Identity of N-dim element
   *
   * Elements starts from 0
   */
  struct indentity {

    unsigned int point[N];

    bool operator==(const indentity &o) const {
      bool isSame = true;
      for(unsigned int ij=0; ij<N; ij++) {if (point[ij] != o.point[ij]) isSame = false; break;}
      return isSame;
    };

    bool operator<(const indentity &o) const {
      bool isSmall = false;
      for(unsigned int ij=0; ij<N; ij++) {
	if (point[ij] < o.point[ij]) { isSmall = true; break;}
	else if (point[ij] > o.point[ij]) { isSmall = false; break;}
      }
      return isSmall;
    };
  };

  /** The specialized hash function for `unordered_map` keys */
  struct hash_fn {
    std::size_t operator() (const indentity& o) const {
      std::size_t h_total = 0;
      for(unsigned int ij=0; ij<N; ij++) {
	h_total <<= 1;
	h_total ^= std::hash<unsigned int>()(o.point[ij]);
#ifdef DEBUG
	std::cout<<" index "<<ij<<", id "<<o.point[ij]<<std::endl;
	std::cout<<" \thash "<<std::bitset<64>(h_total)<<std::endl;
#endif
      }
      return h_total;
    }
  };

  /** Array element map */
  std::unordered_map<indentity, T, hash_fn> arrayPtr;

};
