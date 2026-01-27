#include <bits/stdc++.h>
using namespace std;

void disp(vector<int>& arr) {
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
}

void lb(vector<int>& arr, int target) {
    auto it = lower_bound(arr.begin(), arr.end(), target);
    if (it != arr.end()) {
        cout << "Lower bound of " << target << " is at index "
             << (it - arr.begin()) << " with value " << *it << endl;
    } else {
        cout << "Lower bound of " << target << " is at the end of the array."
             << endl;
    }
}

void ub(vector<int>& arr, int target) {
    auto it = upper_bound(arr.begin(), arr.end(), target);
    if (it != arr.end()) {
        cout << "Upper bound of " << target << " is at index "
             << (it - arr.begin()) << " with value " << *it << endl;
    } else {
        cout << "Upper bound of " << target << " is at the end of the array."
             << endl;
    }
}

int main() {
    vector<int> nums;
    for (int i = 0; i < 10; i++) {
        nums.push_back(2 * i + 1);
    }

    disp(nums);

    lb(nums, 5);
    ub(nums,5);
    lb(nums, 4);
    ub(nums, 3);
    ub(nums, 4);
    return 0;
}
