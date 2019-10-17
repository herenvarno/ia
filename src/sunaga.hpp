// Copyright (c) 2019 herenvarno
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef __SUNAGA_HPP__
#define __SUNAGA_HPP__

#include <limits>

namespace interval_algebra {
namespace sunaga {

template <typename T> class Interval {

private:
  T _l0;
  T _l1;

public:
  Interval(T l_) {
    _l0 = l_;
    _l1 = l_;
  }
  Interval(T l0_, T l1_) {
    _l0 = l0_;
    _l1 = l1_;
  }

public:
  void l0(T l0_) { _l0 = l0_; }
  void l1(T l1_) { _l1 = l1_; }
  T l0() const { return _l0; }
  T l1() const { return _l1; }
  inline bool empty() const { return (l0() > l1()); }
  inline bool full() const {
    return (l0() == -std::numeric_limits<T>::infinity() &&
            l1() == +std::numeric_limits<T>::infinity());
  }

public:
  // Relation Operations
  static inline bool incl(const Interval<T> A_, const Interval<T> B_) {
    return (A_.l0() <= B_.l0() && A_.l1() >= B_.l1());
  }
  static inline bool coinside(const Interval<T> A_, const Interval<T> B_) {
    return (incl(A_, B_) && incl(B_, A_));
  }
  static inline Interval<T> join(const Interval<T> A_, const Interval<T> B_) {
    return Interval<T>(min(A_.l0(), B_.l0()), max(A_.l1(), B_.l1()));
  }
  static inline Interval<T> meet(const Interval<T> A_, const Interval<T> B_) {
    return Interval<T>(max(A_.l0(), B_.l0()), min(A_.l1(), B_.l1()));
  }

public:
  // Arithmetic Operations
  static inline Interval<T> add(const Interval<T> A_, const Interval<T> B_) {
    if (A_.empty() || B_.empty()) {
      return Interval<T>(+std::numeric_limits<T>::infinity(),
                         -std::numeric_limits<T>::infinity());
    }
    if (A_.full()) {
      return B_;
    }
    if (B_.full()) {
      return A_;
    }
    return Interval<T>(A_.l0() + B_.l0(), A_.l1() + B_.l1());
  }
  static inline Interval<T> sub(const Interval<T> A_, const Interval<T> B_) {
    return add(A_, Interval<T>(-B_.l1(), -B_.l0()));
  }
};

} // namespace sunaga
} // namespace interval_algebra

#endif // __SUNAGA_HPP__