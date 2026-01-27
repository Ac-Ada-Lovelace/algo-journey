#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        return merge2(nums1, m, nums2, n);
        vector<int> arr(m + n);
        int i = 0, j = 0;
        while (i < m && j < n) {
            if (nums1[i] < nums2[j]) {
                arr[i + j] = nums1[i];
                i++;
            } else {
                arr[i + j] = nums2[j];
                j++;
            }
        }

        while (i < m) {
            arr[i + j] = nums1[i];
            i++;
        }
        while (j < n) {
            arr[i + j] = nums2[j];
            j++;
        }

        nums1 = arr;
    }

    void merge2(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        nums1.resize(m + n);
        int p1 = m - 1;
        int p2 = n - 1;
        int tail = m + n - 1;
        while (p1 >= 0 || p2 >= 0) {
            int cur = 0;
            if (p1 == -1) {
                cur = nums2[p2--];
            } else if (p2 == -1) {
                cur = nums1[p1--];
            } else if (nums1[p1] > nums2[p2]) {
                cur = nums1[p1--];
            } else {
                cur = nums2[p2--];
            }

            nums1[tail--] = cur;
        }
    }
};
