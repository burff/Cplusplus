#include <vector>
using std::vector;

class Solution {
public:
    bool half_find(const vector<vector<int>>& nums, int target, int low, int high, int& index, int mode)
    {
        int left = low;
        int right = high;
        int num;

        while(left < right)
        {
            int mid = (left + right)/2;

            if(mode == 1)
            {
                num = nums[mid][mid];
            }
            else if(mode == 2)
            {
                num = nums[low][mid];
            }
            else
            {
                num = nums[mid][low];
            }

            if(num == target)
            {
                return true;
            }
            else if(num > target)
            {
                right = mid;
            }
            else
            {
                left = mid + 1;
            }
        }

        if(mode == 1)
        {
            index = left - 1;
        }
        
        return false;
    }
    bool findTargetIn2DPlants(vector<vector<int>>& plants, int target) 
    {
        if(plants.empty())
            return false;
        int row = plants.size();
        int col = plants[0].size();
        int index = row < col?row:col;

        if((plants[0][0] > target) || (plants[row-1][col-1] < target))
            return false;

        if(half_find(plants, target, 0, index, index, 1))
            return true;

        while(index >= 0)
        {
            if(row > 1 && half_find(plants, target, index, row, index, 3))
                return true;
            if(col > 1 && half_find(plants, target, index, col, index, 2))
                return true;
            index--;
        }
        return false;
    }
};


int main()
{

    return 0;
}