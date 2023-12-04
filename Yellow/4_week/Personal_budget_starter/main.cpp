#include <string>
#include "date.h"
#include "budget.h"
#include "tests.h"

enum class Command{
    ComputeIncome,
    Earn
};

std::istream& operator>>(std::istream& in, Command& q){
		std::string str;
    in >> str;
    if (str == "ComputeIncome"){
        q = Command::ComputeIncome;
    } else if (str == "Earn"){
        q = Command::Earn;
    }

    return in;
}
int main(){
   	TestAll(); 
		size_t N;
		std::cin >> N;

    Budget personal;
		std::cout.precision(25);
    for (size_t i = 0; i != N; ++i){
        Command q;    
        Date to, from;
				std::cin >> q >> to >> from;
        switch (q)
        {
        case Command::ComputeIncome:
						std::cout << personal.ComputeIncome(to, from) << std::endl;
            break;
        case Command::Earn:
            double earn;
						std::cin >> earn;
            personal.Earn(to, from, earn);
            break;
        default:
            break;
        }
    }

    return 0;
}


