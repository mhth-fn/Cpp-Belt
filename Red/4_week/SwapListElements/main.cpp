#include <iterator>
#include <list>
#include <iostream>

using namespace std;

template<typename type, typename Iterator>
void SwapListElements(list<type> lst, Iterator iterator1, Iterator iterator2){
	const auto iterator2_next = next(iterator2);
	lst.splice(iterator1, lst, iterator2);
	lst.splice(iterator2_next, lst, iterator1);
}

int main(){
	list<int> l{1, 2};
	for(const int& x : l){
		std::cout << x << " ";
	}
	std::cout << endl;

	SwapListElements(l, begin(l), ++begin(l));
	
	for(const int& x : l){
		std::cout << x << " ";
	}
	std::cout << endl;



}
