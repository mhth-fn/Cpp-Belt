#include <vector>
#include <stdexcept>
using namespace std;

template <typename T>
class Deque{
public:
	Deque(){
		size_ = 0;
	}
	//tested
	bool Empty() const{
		if (size_ == 0){
			return true;
		} 
		return false;
	}
	//tested
	size_t Size() const{
		return size_;
	}

	T& operator[](size_t index){
		if (InFront(index)){
			return front_[index];
		} else {
			return back_[size_ - 1 - index];
		}
	}
	const T& operator[](size_t index) const{
		if (InFront(index)){
			return front_[index];
		} else {
			return back_[size_ - 1 - index];
		}
	}

	T& At(size_t index){
		if (index >= size_){
			throw out_of_range("index >= size");
		} else if (InFront(index)){
			front_.at(index);	
		} else {
			return back_.at(size_ - 1 - index);
		}
	}

	const T& At(size_t index) const{
		return At(index);
	}
	//tested
	T& Front(){
		return front_.back();
	}
	//tested;
	const T& Front() const{
		return front_.back();
	}
	//tested;
	T& Back(){
		return back_.back();
	}
	//tested;
	const T& Back() const{
		return back_.back();
	}
	//tested;
	void PushFront(const T& item){
		front_.push_back(item);
		++size_;
	}
	//tested
	void PushBack(const T& item){
		back_.push_back(item);
		++size_;
	}

private:
	vector<T> front_, back_;
	size_t size_;

	bool InFront(size_t size){
		return front_.size > size; 
	}
};

