/* Метод Read должен обновлять страницу у конкретного пользователя,
	 если такого пользователя нет, то он должен его внести в базу.
	 
	 Метод Cheer должен для конкретного пользователя должен вывести
	 вещественное число, которое покажет прогресс относительного других
	 пользователей (не включая его самого).

	 Метод Read и Cheer должны иметь сложность меньше Q ~ logQ

	 Надо придумать, как метод Cheer может работать за лог. сложность. */

	

/* Read(0, 5);
	 Read(1, 10);
	 Read(2, 15);
	 Cheer(0) = 0%
	 Cheer(2) = 100%
	 Cheear(1) = 50% */

/* TotalPage = 30;
	 TotalUsers = 3; */

/*  ИДЕИ
 1)Пусть будет переменная bool flag, которая будет характеризовать необходимость
 в сортировке.
 2) Прогресс можно будет расчитать по формуле:
 				res = (begin_it - user_it)/(TotalUsers - 1);                           */
#include <typeinfo>
#include <iomanip>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <utility>
#include <set>

using namespace std;

struct Reader{
	int id;
	int page;
	Reader(int user_id, int page_id) : 
		id(user_id), page(page_id){};

};


bool operator<(const Reader& lhs, const Reader& rhs){
	return tie(lhs.page, lhs.id) < tie(rhs.page, rhs.id);
}


class ReadingManager{
public:
  ReadingManager()
      : user_page_counts_(MAX_USER_COUNT_ + 1, 0),
        sorted_users_(),
        user_positions_(MAX_USER_COUNT_ + 1, -1) {}
	
  void Read(int user_id, int page_count){
		Reader user{user_id, page_count};
  	if (user_page_counts_[user_id] == 0){
			sorted_users.insert({user_id, page_count});
    } else {
			auto it = sorted_users.lower_bound(user);
			sorted_users.erase(it);
			sorted_users.insert({user_id, page_count});
			auto it1 = sorted_users.lower_bound(user);
		}
 
	}
	double Cheer();
private:
  // Статическое поле не принадлежит какому-то конкретному
  // объекту класса. По сути это глобальная переменная,
  // в данном случае константная.
  // Будь она публичной, к ней можно было бы обратиться снаружи
  // следующим образом: ReadingManager::MAX_USER_COUNT.
  static const int MAX_USER_COUNT_ = 100'000;
	
	set<Reader> sorted_users;
	vector<set<int>::iterator> user_position;

  vector<int> user_page_counts_;
  vector<int> sorted_users_;   // отсортированы по убыванию количества страниц
  vector<int> user_positions_; // позиции в векторе sorted_users_

  int GetUserCount() const { //1
    return sorted_users_.size(); 
  }
  void AddUser(int user_id) { //1
    sorted_users_.push_back(user_id); //1
    user_positions_[user_id] = sorted_users_.size() - 1; //1
  }
  void SwapUsers(int lhs_position, int rhs_position) { //1
    const int lhs_id = sorted_users_[lhs_position];
    const int rhs_id = sorted_users_[rhs_position];
    swap(sorted_users_[lhs_position], sorted_users_[rhs_position]);
    swap(user_positions_[lhs_id], user_positions_[rhs_id]);
  }


};


int main(){
	

}
