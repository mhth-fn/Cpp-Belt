#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int searchInsert(vector<int> nums, int target) {
        if (nums.size() == 0){
            return 0;
        }
        int low = 0,
            high = nums.size();
        for (int pos = (high - low) / 2; pos != 0; pos = (high - low) / 2){
            if (nums[low + pos] == target){
                return low + pos;
            } else if (nums[low + pos] > target){
                high -= pos;
            } else if (nums[low + pos] < target){
                low += pos;
            } else {
                break;
            }
        }
        if (target > nums[low]){
            return low + 1;
        }
        return low;
    }
};

int main(){
    Solution sol;
    std:: cout <<sol.searchInsert({3, 5, 7, 9, 10}, 8);

}