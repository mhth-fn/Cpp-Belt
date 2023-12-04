#include <algorithm>
#include <bits/ranges_base.h>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <tuple>
#include <vector>

template <typename T>
struct Item{
	Item(T value, int priority, size_t id) : 
		value_(std::move(value)), priority_(priority), id_(id){};

	T value_;
	int priority_;
	size_t id_;

	bool operator<(const Item<T> other){
		return std::tie(priority_, value_) < std::tie(other.priority_, other.value_);
	}
};

template <typename T>
bool operator<(const Item<T>& lhs, const Item<T>& rhs){
		return std::tie(lhs.priority_, lhs.id_) < std::tie(rhs.priority_, rhs.id_);
}
template <typename T>
class PriorityCollection{
public:
	PriorityCollection(){
		vector_id.reserve(1000000);
	}
	using Id = size_t;

	size_t Add(T value){
		typename std::set<Item<T>>::iterator it = queue.insert({std::move(value), 0, vector_id.size()}).first;
		vector_value.push_back(std::move(value));	
		vector_id.push_back(it);	
		return vector_id.size() - 1;
	}
  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin){
		for (auto it = range_begin; it != range_end; ++it){
			ids_begin++ = Add(*it);	
		}
	}


  bool IsValid(Id id) const{
		if (vector_id.size() < id && vector_value[id] != nullptr){
			return true;
		} else{
			return false;
		}
	}

  const T& Get(Id id) const{
		return vector_id[id];
	}

  void Promote(Id id){
		//ERROR!
		auto max_elem = queue.extract(*vector_id[id]);
		Item tmp = std::move(max_elem.value());
		++tmp.priority_;	
		typename std::set<Item<T>>::iterator it = queue.insert(std::move(tmp)).first;
		vector_id[id] = it;	
	}
	std::pair<const T&, int> GetMax(){
		auto max_elem = rbegin(queue);
		return {vector_id[max_elem->id_], max_elem->priority};
	}
	std::pair<T, int> PopMax(){
		auto max_elem = queue.extract(*rbegin(queue));
		Item tmp = max_elem.value();
		T value = std::move(vector_value[tmp.id_]);
		vector_value[tmp.id_] = nullptr;
		return {std::move(tmp.value_), tmp.priority_};
	}
private:
	std::set<Item<T>> queue;
	std::vector<T> vector_value;
	std::vector<typename std::set<Item<T>>::iterator> vector_id;
};

int main(){
	PriorityCollection<std::string> test;
	test.Add({"a", 0});
	test.Add({"b", 0});
	test.Add({"c", 1});
	std::cout << test.PopMax().first;
return 0;
}
