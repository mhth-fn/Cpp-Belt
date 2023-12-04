#include "date.h"

int FromDateToInt(Date date){
  return DaysFromYear(date.Year) + DaysFromMonths(date.Year, date.Month) + date.Day;
}

size_t DaysFromYear(int year){
  if (year <= 2000){
		return 0;
  } else  if ((year % 100 != 0 && year % 4 == 0) || year % 400 == 0 ){
		return 366 + DaysFromYear (--year);
  }
  return 365 + DaysFromYear(--year);
}

size_t DaysFromMonths(int year, int month){
	std::vector <int> DaysPerMonth{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int res = 0;
  if ((year % 100 != 0 && year % 4 == 0) || year % 400 == 0 ){
    ++DaysPerMonth[1];
  }
  for (int i = 0; i < month - 1; ++i){
    res += DaysPerMonth[i];
  }

  return res;
}

std::istream& operator>>(std::istream& in, Date &date){
    in >> date.Year;
    in.get();
    in >> date.Month;
    in.get();
    in >> date.Day;
    
    return in;
}


