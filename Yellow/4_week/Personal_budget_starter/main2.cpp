#include <iostream>
#include <vector>
#include <string>
#include <numeric>

using namespace std;

enum class Command{
    ComputeIncome,
    Earn
};

struct Date{
    int Day;
    int Month;
    int Year;
};

istream& operator>>(istream& in, Command& q);

istream& operator>>(istream& in, Date &date);


class Budget{
public:
    Budget();
    void Earn(Date from, Date to, double earn);
    double ComputeIncome(Date from, Date to);

private:
    vector<double> budget;
};

bool IsLeap(int year);

size_t FromDateToInt(Date date);

size_t DaysFromYear(int year);

size_t DaysFromMonths(int year, int month);

int main(){
    size_t N;
    cin >> N;

    Budget personal;	
    for (size_t i = 0; i != N; ++i){
        Command q;    
        Date from, to;
        cin >> q >> from >> to;
        switch (q)
        {
        case Command::ComputeIncome:
        		cout.precision(25);    
						cout << personal.ComputeIncome(from, to) << endl;
            break;
        case Command::Earn:
            double earn;
            cin >> earn;
            personal.Earn(from, to, earn);
            break;
        default:
            break;
        }
    }

    return 0;
}

istream& operator>>(istream& in, Command& q){
    string str;
    in >> str;
    if (str == "ComputeIncome"){
        q = Command::ComputeIncome;
    } else if (str == "Earn"){
        q = Command::Earn;
    }

    return in;
}

istream& operator>>(istream& in, Date& date){
    in >> date.Year;
    in.get();
    in >> date.Month;
    in.get();
    in >> date.Day;
    
    return in;
}

Budget::Budget(){
    Date to{9, 1, 2100};
    budget.resize(FromDateToInt(to));
}

void Budget::Earn(Date from, Date to, double earn){
    size_t begin_date = FromDateToInt(from),
    end_date = FromDateToInt(to);
    
    double daily_wage = earn / (end_date - begin_date + 1);
    
    for (; begin_date <= end_date; ++begin_date){
        budget[begin_date] += daily_wage;
    }
}

double Budget::ComputeIncome(Date from, Date to){
    size_t begin_date = FromDateToInt(from),
    end_date = FromDateToInt(to);
        
    return accumulate(budget.begin() + begin_date, budget.begin() + end_date + 1, 0.0);
}

size_t FromDateToInt(Date date){
    return DaysFromYear(date.Year) + DaysFromMonths(date.Year, date.Month) + date.Day;
}

size_t DaysFromYear(int year){
    if (year <= 2000){
        return 0;
    } else  if (IsLeap(year)){
        return 366 + DaysFromYear (--year);
    }
    return 365 + DaysFromYear(--year);
}

size_t DaysFromMonths(int year, int month){
    vector <int> DaysPerMonth{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    size_t res = 0;
    if (IsLeap(year)){
        ++DaysPerMonth[1];
    }
    for (int i = 0; i != month - 1; ++i){
        res += DaysPerMonth[i];
    }

    return res;
}

bool IsLeap(int year){
	return ((year % 100 != 0 && year % 4 == 0) || year % 400 == 0);
}
