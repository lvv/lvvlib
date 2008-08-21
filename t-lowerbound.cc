#include <iostream>
#include <algorithm>
#include "lvv.h"

int main() {
  int a[10]={1,3,3,4,5,7,8,8,9,10};

  PR1(*std::lower_bound(a, a+10, 5))
}

