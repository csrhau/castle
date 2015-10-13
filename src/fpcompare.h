#ifndef CSRHAU_CPPSAMPLES_FPCOMPARE_H 
#define CSRHAU_CPPSAMPLES_FPCOMPARE_H 

#include <cmath>

namespace Tools {
  template <typename T, int decimal_places>
  struct FPCompare {
    // N.B. this class is not to be extended, hence the non-virtual dtor.
    FPCompare() {}
    ~FPCompare() {}

    static T epsilon() {
      static T value = T(1.0/pow(10.0, decimal_places + 1.0));
      return value;
    }
    
    static bool equal (T lhs_, T rhs_) {
      T delta = lhs_ - rhs_;
      T eps = epsilon();
      return (-eps <= delta) && (delta <= eps);
    }

    static bool not_equal (T lhs_, T rhs_) { return !equal(lhs_, rhs_); }
    static bool greater (T lhs_, T rhs_) { return lhs_ > rhs_ + epsilon(); }
    static bool less (T lhs_, T rhs_) { return lhs_ < rhs_ + epsilon(); }
    static bool greater_equal (T lhs_, T rhs_) { return !less(lhs_, rhs_); }
  };

  typedef FPCompare<double, 6> DoubleCompare;
  typedef FPCompare<float, 6> FloatCompare;
}
#endif
