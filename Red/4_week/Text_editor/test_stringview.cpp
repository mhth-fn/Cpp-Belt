#include <iostream>
#include <string>
#include <string_view>

using namespace std;

int main(){
	string str = "Hello, world";
	string_view str_v = str;
	
	cout << str_v.begin();
}
