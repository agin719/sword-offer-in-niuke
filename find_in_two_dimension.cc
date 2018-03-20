/*
 * 二维数组中的查找
 *
 * 题目描述
 * 在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
 *
 * 题解1：
 * 从左下角出发，比a[i][j]大则向右走，比a[i][j]小则向上走。
 *
 * 题解2：
 * 从右上角出发，比a[i][j]大则向下走，比a[i][j]小则向左走。
 */

class Solution {
  public:
    bool Find(int target, vector<vector<int> > array) {
      int n = array.size();
      if (n == 0) return false;
      int m = array[0].size();
      if (m == 0) return false;

      int i = n-1;
      int j = 0;
      while (i >= 0 && j < m) {
        if (array[i][j] == target) 
          return true;
        else if (array[i][j] > target) 
          i--;
        else 
          j++;
      }
      return false;
    }
};
