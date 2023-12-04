#pragma once

#include <iostream>
#include <vector>

struct Date{
    int Day;
    int Month;
    int Year;
};

size_t DaysFromYear(int year);

size_t DaysFromMonths(int year, int month);

int FromDateToInt(Date date);

std::istream& operator>>(std::istream& is, Date& date);
