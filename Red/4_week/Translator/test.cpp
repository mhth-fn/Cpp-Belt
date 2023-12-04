#include <algorithm>
#include <iostream>
#include <string_view>
#include <string>
#include <vector>
#include <map>
using namespace std;

int main(){
	string str("Hello, world!");
	string_view t1 = str;
	string_view t2 = str;
	cout << (t1 == t2) << endl;

	vector<string> str_v;
	str_v.push_back(str);
	string_view t3 = str_v.back();
	string_view t4 = str_v.back();
	cout << (t1 == t2) << endl;

	auto it = find(begin(str_v), end(str_v), str);
	string_view t5 = *it;
	cout << (t3 == t5) << endl;	

	map<string_view, int> mview;
	mview[t3] = 1;
	cout << mview.at(t2) << endl;
	return 0;
}
