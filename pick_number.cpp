#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

int calc_pr(vector<int> &vec, int num) {
    vector<int>::iterator upp = upper_bound(vec.begin(), vec.end(), num);
    int pr = (vec.size() - (vec.end() - upp))*100/vec.size();
    return pr;
}

int main(int argc, char **argv) {
    if (argc < 5) {
        cout << "usage: pick PR(int), pick wait(int), #sample, #turns" << endl;
        return 0;
    }
    int const rand_max = 10000;

    int const pick_pr = atoi(argv[1]);
    int const pick_wait = atoi(argv[2]);
    int const sample_count = atoi(argv[3]);
    int const round_count = atoi(argv[4]);

    srand(time(NULL));
    map<int, int> result_pr_count;
    for (int round = 0; round < round_count; round++) {
        int picked_num = -1;
        vector<int> nums;
        int i;
        for (i = 0; i < sample_count; i++) {
            int num = rand()%rand_max + 1;
            nums.insert(lower_bound(nums.begin(), nums.end(), num), num);

            int pr = calc_pr(nums, num);
            if (picked_num == -1 && i >= pick_wait && pr >= pick_pr) {
                picked_num = num;
                break;
            }
            if (i == sample_count - 1)
                picked_num = num;
        }
        for (; i < sample_count; i++)
            nums.push_back(rand()%rand_max+1);
        sort(nums.begin(), nums.end());
        result_pr_count[calc_pr(nums, picked_num)]++;
    }
    int sum;
    for (int i = 0; i < 101; i++) {
        sum += result_pr_count[i]*i;
    }
    cout << 1.*sum / round_count << endl;
}
