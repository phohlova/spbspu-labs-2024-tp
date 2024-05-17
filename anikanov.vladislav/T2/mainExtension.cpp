#include "mainExtension.hpp"

bool anikanov::dataStructComparator(const DataStruct &a, const DataStruct &b)
{
  if (a.key1 != b.key1) {
    return a.key1 < b.key1;
  }
  if (a.key2 != b.key2) {
    return a.key2 < b.key2;
  }
  return a.key3 < b.key3;
}
