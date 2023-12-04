#include "budget.h"

Budget::Budget(){
    Date to{2, 1, 2100};
    budget.resize(FromDateToInt(to));
}

void Budget::Earn(Date to, Date from, double earn){
    size_t begin_date = FromDateToInt(to),
    end_date = FromDateToInt(from);
    
    double daily_wage = earn / (end_date - begin_date + 1);
    
    for (; begin_date <= end_date; ++begin_date){
        budget[begin_date] += daily_wage;
    }

}

double Budget::ComputeIncome(Date to, Date from){
    int begin_date = FromDateToInt(to),
    end_date = FromDateToInt(from);
        
    return std::accumulate(budget.begin() + begin_date, budget.begin() + end_date + 1, 0.0);
}


