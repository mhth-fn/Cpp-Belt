#pragma once

#include "date.h"
#include <numeric>

class Budget{
public:
  Budget();
  void Earn(Date to, Date from, double earn);
  double ComputeIncome(Date to, Date from);

private:
	std::vector<double> budget;
};


