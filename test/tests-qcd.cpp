/// This file tests expressions from quantum chromodynamics (QCD).
#include "test.h"
#include "taco/tensor.h"

using namespace std;
using namespace taco;

static string qcdTestData(string name) {
  return testDataDirectory() + "qcd/" + name;
}

double getScalarValue(Tensor<double> tensor) {
  return ((double*)tensor.getStorage().getValues().getData())[0];
}

IndexVar i("i"), j("j"), k("k");

TEST(qcd, mul0) {
  Tensor<double> tau("tau");
  Tensor<double> z = read(qcdTestData("z.ttx"), Dense);
  Tensor<double> theta = read(qcdTestData("theta.ttx"), Dense);

  tau = z(i) * z(j) * theta(i,j);

  tau.evaluate();
  ASSERT_DOUBLE_EQ(0.5274167972947047, getScalarValue(tau));
}

TEST(qcd, mul1) {
  Tensor<double> tau("tau");
  Tensor<double> z = read(qcdTestData("z.ttx"), Dense);
  Tensor<double> theta = read(qcdTestData("theta.ttx"), Dense);

  tau = z(i) * z(j) * theta(i,j) * theta(i,j);

  tau.evaluate();
  ASSERT_DOUBLE_EQ(0.41212798763234737, getScalarValue(tau));
}

TEST(qcd, mul2) {
  Tensor<double> tau("tau");
  Tensor<double> z = read(qcdTestData("z.ttx"), Dense);
  Tensor<double> theta = read(qcdTestData("theta.ttx"), Dense);

  tau = z(i) * z(j) * theta(i,j) * theta(i,j) * theta(i,j);

  tau.evaluate();
  ASSERT_DOUBLE_EQ(0.4120590379120669, getScalarValue(tau));
}

TEST(DISABLED_qcd, mul3) {
  Tensor<double> tau("tau");
  Tensor<double> z = read(qcdTestData("z.ttx"), Dense);
  Tensor<double> theta = read(qcdTestData("theta.ttx"), Dense);

  tau = z(i) * z(j) * z(k) * theta(i,j) * theta(i,k);

  tau.evaluate();
  if (!std::getenv("OLD_LOWER") ||
      std::string(std::getenv("OLD_LOWER")) != "1") {
    ASSERT_DOUBLE_EQ(0.3223971010027149, getScalarValue(tau));
  }
  else {
    ASSERT_DOUBLE_EQ(0.3223971010027145, getScalarValue(tau));
  }
}

