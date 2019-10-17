#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include "sunaga.hpp"
#include <boost/test/unit_test.hpp>

using namespace interval_algebra::sunaga;

BOOST_AUTO_TEST_CASE(single_float) {
  Interval<float> A(6.1);
  BOOST_CHECK_EQUAL(A.l0(), float(6.1));
  BOOST_CHECK_EQUAL(A.l1(), float(6.1));
  Interval<float> B(1.2, 4);
  BOOST_CHECK_EQUAL(B.l0(), float(1.2));
  BOOST_CHECK_EQUAL(B.l1(), float(4));
  Interval<float> C(4, 1);
  Interval<float> D(-std::numeric_limits<float>::infinity(),
                    +std::numeric_limits<float>::infinity());
  Interval<float> E(+std::numeric_limits<float>::infinity(),
                    -std::numeric_limits<float>::infinity());
  BOOST_CHECK_EQUAL(A.empty(), false);
  BOOST_CHECK_EQUAL(B.empty(), false);
  BOOST_CHECK_EQUAL(C.empty(), true);
  BOOST_CHECK_EQUAL(D.empty(), false);
  BOOST_CHECK_EQUAL(E.empty(), true);
  BOOST_CHECK_EQUAL(A.full(), false);
  BOOST_CHECK_EQUAL(B.full(), false);
  BOOST_CHECK_EQUAL(C.full(), false);
  BOOST_CHECK_EQUAL(D.full(), true);
  BOOST_CHECK_EQUAL(E.full(), false);
  BOOST_CHECK_EQUAL(Interval<float>::add(A, B).l0(), A.l0() + B.l0());
  BOOST_CHECK_EQUAL(Interval<float>::add(A, B).l1(), A.l1() + B.l1());
  BOOST_CHECK_EQUAL(Interval<float>::sub(A, B).l0(), A.l0() - B.l1());
  BOOST_CHECK_EQUAL(Interval<float>::sub(A, B).l1(), A.l1() - B.l0());
  BOOST_CHECK_EQUAL(Interval<float>::incl(B, A), false);
  BOOST_CHECK_EQUAL(Interval<float>::incl(A, B), false);
  BOOST_CHECK_EQUAL(Interval<float>::incl(D, A), true);
  BOOST_CHECK_EQUAL(Interval<float>::coinside(B, A), false);
  BOOST_CHECK_EQUAL(Interval<float>::coinside(B, B), true);
}

BOOST_AUTO_TEST_CASE(double_float) {
  Interval<double> A(6.1);
  BOOST_CHECK_EQUAL(A.l0(), double(6.1));
  BOOST_CHECK_EQUAL(A.l1(), double(6.1));
  Interval<double> B(1.2, 4);
  BOOST_CHECK_EQUAL(B.l0(), double(1.2));
  BOOST_CHECK_EQUAL(B.l1(), double(4));
  Interval<double> C(4, 1);
  Interval<double> D(-std::numeric_limits<double>::infinity(),
                     +std::numeric_limits<double>::infinity());
  Interval<double> E(+std::numeric_limits<double>::infinity(),
                     -std::numeric_limits<double>::infinity());
  BOOST_CHECK_EQUAL(A.empty(), false);
  BOOST_CHECK_EQUAL(B.empty(), false);
  BOOST_CHECK_EQUAL(C.empty(), true);
  BOOST_CHECK_EQUAL(D.empty(), false);
  BOOST_CHECK_EQUAL(E.empty(), true);
  BOOST_CHECK_EQUAL(A.full(), false);
  BOOST_CHECK_EQUAL(B.full(), false);
  BOOST_CHECK_EQUAL(C.full(), false);
  BOOST_CHECK_EQUAL(D.full(), true);
  BOOST_CHECK_EQUAL(E.full(), false);
  BOOST_CHECK_EQUAL(Interval<double>::add(A, B).l0(), A.l0() + B.l0());
  BOOST_CHECK_EQUAL(Interval<double>::add(A, B).l1(), A.l1() + B.l1());
  BOOST_CHECK_EQUAL(Interval<double>::sub(A, B).l0(), A.l0() - B.l1());
  BOOST_CHECK_EQUAL(Interval<double>::sub(A, B).l1(), A.l1() - B.l0());
  BOOST_CHECK_EQUAL(Interval<double>::incl(B, A), false);
  BOOST_CHECK_EQUAL(Interval<double>::incl(A, B), false);
  BOOST_CHECK_EQUAL(Interval<double>::incl(D, A), true);
  BOOST_CHECK_EQUAL(Interval<double>::coinside(B, A), false);
  BOOST_CHECK_EQUAL(Interval<double>::coinside(B, B), true);
}