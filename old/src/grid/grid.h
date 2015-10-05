#ifndef CASTLE_GRID_GRID_H
#define CASTLE_GRID_GRID_H

#include "row_exchange_policy.h"

template <typename ExchangePolicy> 
class Grid : private ExchangePolicy {
  using ExchangePolicy::exchange_borders;

  public:
  void step() {
    exchange_borders();
  }
};

#endif
