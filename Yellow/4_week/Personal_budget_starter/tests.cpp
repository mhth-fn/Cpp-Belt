#include "tests.h"
#include "date.h"
#include "budget.h"

void TestBudget(){
	{
		Date from{1, 1, 2000}, to{5, 1, 2000};
		Budget test;
		test.Earn(from, to, 50);
		Assert(test.ComputeIncome(from, to) == 50, "Test 1.1");
		Assert(test.ComputeIncome(from, from) == 10, "Test 1.2");
	}
}

void TestDate(){
	{
		Date test{1,1,2000};
		Assert(FromDateToInt(test) == 1, "Test 1.1");
		Assert(DaysFromYear(test.Year) == 0, "Test 1.2");
		Assert(DaysFromMonths(test.Year, test.Month) == 0, "Test 1.3");
	}
	{
		Date test{31, 12, 2099};
		Assert(FromDateToInt(test) == 36524, "Test 2.1");
		Assert(DaysFromYear(test.Year) == 36159, "Test 2.2");
		Assert(DaysFromMonths(test.Year, test.Month) == 334, "Test 2.3");
	}
	{
		Date test{31, 12, 2000};
		Assert(FromDateToInt(test) == 366, "Test 3.1");
		Assert(DaysFromMonths(test.Year, test.Month) == 335, "Test 3.2");
	}
	{
		Date test{1, 3, 2004};
		Assert(DaysFromMonths(test.Year, test.Month) == 60, "Test 4.1");
	}
}

void TestAll(){
	TestRunner tr;
	tr.RunTest(TestDate, "TestDate");
	tr.RunTest(TestBudget, "TestBudget");
}
