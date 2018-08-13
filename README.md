## 剑指offer in 牛客网

### 1、二维数组中的查找
##### 题目描述
在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。   
##### 题解
----->   
|   
|   
V   
可以从右上角或者左下角开始查找，比如在左下角查找，target小于a[i][j]，则向上走，target大于a[i][j]，向右走。   
```
class Solution {
public:
    bool Find(int target, vector<vector<int> > array) {
        int n = array.size();
        if (n == 0) return false;
        int m = array[0].size();
        if (m == 0) return false;
        
        int i = n-1;    //左下角开始查找
        int j = 0;
        while (i >= 0 && j < m) {
            if (array[i][j] == target) 
                return true;
            else if (array[i][j] > target) 
                i--;        //向上走
            else 
                j++;        //向右走
        }
        return false;
    }
};
```

### 2、替换空格
##### 题目描述
请实现一个函数，将一个字符串中的空格替换成“%20”。例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy。   
##### 题解
统计空格数量，先保存源字符串，使用realloc为字符重新分配空间。   
```
class Solution {
public:
	void replaceSpace(char *str,int length) {
      int space_count = 0;
      int str_len = strlen(str);
      for (int i = 0; i < str_len; i++) {   //统计空格
        if (str[i] == ' ') {
          space_count++;
        }
      }
      char tmp[str_len];    
      strncpy(tmp, str, str_len);       //保留原字符串
      if (str_len + 2*space_count > length) {
        str = (char*) realloc(str, str_len+2*space_count);      //重新分配空间
      }
      char *ptr = str;
      for (int i = 0; i < str_len; i++) {       //插入
        if (tmp[i] == ' ') {
          *ptr++ = '%';
          *ptr++ = '2';
          *ptr++ = '0';
        } else {
          *ptr++ = tmp[i];
        }
      }
      *ptr = '\0';
	}
};
```

### 3、从尾到头打印链表
##### 题目描述
输入一个链表，从尾到头打印链表每个节点的值。   

##### 题解
可用递归(实际利用栈的性质，先进后出)，或者直接保存到vector里面，然后reverse。   
```
class Solution {
public:
    void get_node(vector<int> &result, ListNode *node) {    //利用递归，方法一
        if (node->next != NULL) {
            get_node(result, node->next);
        }
        result.push_back(node->val);
    }
    
    vector<int> printListFromTailToHead(ListNode* head) {   //直接利用vector的reverse
      vector<int> result;
      
      for (ListNode *node = head; node != NULL; node = node->next) {
        result.push_back(node->val);
      } 
      if (result.size()) {
          std::reverse(result.begin(), result.end());
      }
      return result;

    }
};
```

### 4、重建二叉树
##### 题目描述
输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。例如输入前序遍历序列{1,2,4,7,3,5,6,8}和中序遍历序列{4,7,2,1,5,3,8,6}，则重建二叉树并返回。   

##### 题解
顺序取出当前先序遍历的节点，根据这个节点的val将中序遍历分成两半，一半为left，一半为right，递归处理left的一半和right的一半。    
```
class Solution {
public:
    TreeNode *constructor(vector<int>::iterator end_iter, vector<int>::iterator begin_vit, vector<int>::iterator end_vit) {
      if (iter_ == end_iter) {
        return NULL;
      }
      int val = *iter_;
      for (auto it = begin_vit; it != end_vit; it++) {
        if (*it == val) {   
          TreeNode *node = new TreeNode(val);
          iter_++;
          if (begin_vit != it)      分成left一半，并递归left一半，返回left子树的根节点
            node->left = constructor(end_iter, begin_vit, it);
          if (it+1 != end_vit)      分成right一半，并递归right一半，返回right子树的根节点
            node->right = constructor(end_iter, it+1, end_vit);
          return node;  返回节点
        }
      }
      return NULL;
    }
    
    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
        iter_ = pre.begin();        顺序遍历先序
        return constructor(pre.end(), vin.begin(), vin.end());  重构。
    }
    vector<int>::iterator iter_;
};
```

### 5、用两个栈实现队列
##### 题目描述
用两个栈来实现一个队列，完成队列的Push和Pop操作。 队列中的元素为int类型。   
##### 题解
push直接进栈1，出栈的时候先用栈2存放栈1的元素，把栈1的栈底元素输出，然后再把栈2元素重新进入栈1.    
```
class Solution
{
public:
    void push(int node) {
        stack1.push(node);
    }

    int pop() {
        while (!stack1.empty()) {
            stack2.push(stack1.top());
            stack1.pop();
        }
        int val = stack2.top();
        stack2.pop();
        while (!stack2.empty()) {
            stack1.push(stack2.top());
            stack2.pop();
        }
        return val;
    }

private:
    stack<int> stack1;
    stack<int> stack2;
};
```

### 6、旋转数组的最小数字
##### 题目描述
把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。输入一个非递减排序的数组的一个旋转，输出旋转数组的最小元素。例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。 NOTE：给出的所有元素都大于0，若数组大小为0，请返回0。   

### 7、斐波那契数列
##### 题目描述
大家都知道斐波那契数列，现在要求输入一个整数n，请你输出斐波那契数列的第n项（从0开始，第0项为0）。n<=39。   
##### 题解
O(N)复杂度
```
class Solution {
public:
    int Fibonacci(int n) {
        int a1 = 1;
        int a2 = 1;
        if (n == 1) return a1;
        if (n == 2) return a2;
        int ans = 0;
        for (int i = 2; i < n; i++){
            ans = a1 + a2;
            a1 = a2;
            a2 = ans;
        }
        return ans;
    }
};
```
### 8、跳台阶
##### 题目描述
一只青蛙一次可以跳上1级台阶，也可以跳上2级。求该青蛙跳上一个n级的台阶总共有多少种跳法（先后次序不同算不同的结果）。
##### 题解
递推，当前位于阶梯i，那么可以从i-2和i-1这两个情况到达阶梯i，所以f[i] = f[i-1]+f[i-2];
```
class Solution {
public:
    int jumpFloor(int number) {
        if (number == 1) return 1;
        if (number == 2) return 2;
        int a1 = 1;
        int a2 = 2;
        int ans = 0;
        for (int i = 2; i < number; i++) {
            ans = a2 + a1;
            a1 = a2;
            a2 = ans;
        }
        return ans;
    }
};
```
### 9、变态跳台阶
##### 题目描述
一只青蛙一次可以跳上1级台阶，也可以跳上2级……它也可以跳上n级。求该青蛙跳上一个n级的台阶总共有多少种跳法。
##### 题解
和上面那题类似，f[i] = f[i] + f[k];  其中0<=k<=i-1    
每解一次f[i]，将f[i]加到一变量可以得到O(N)解法
```
O(N^2)解法：
class Solution {
public:
    int jumpFloorII(int number) {
        int f[number+1];
        f[0] = 1;
        f[1] = 1;
        for (int i = 2; i <= number; i++) {
            f[i] = 0;
            for (int j = i-1; j >= 0; j--)
                f[i] += f[j];
        }
        return f[number];
    }
};

O(N)解法：
class Solution {
public:
    int jumpFloorII(int number) {
        int f[number+1];
        f[0] = 1;
        f[1] = 1;
        int sum = f[0] + f[1];
        for (int i = 2; i <= number; i++) {
            f[i] = sum;
            sum += f[i];
        }
        return f[number];
    }
};
```
### 10、矩阵覆盖
##### 题目描述
我们可以用2*1的小矩形横着或者竖着去覆盖更大的矩形。请问用n个2*1的小矩形无重叠地覆盖一个2*n的大矩形，总共有多少种方法？
##### 题解
跳阶梯的变形，f[i] = f[i-1] + f[i-2]; 因为f[i-2]只有横放的情况，如果是竖放就与f[i-1]重叠了。
```
class Solution {
public:
    int rectCover(int number) {
        if (number <= 1)
            return number;
        int num1 = 1;
        int num2 = 2;
        for (int i = 3; i <= number; i++) {
            int num3 = num1+num2;
            num1 = num2;
            num2 = num3;
        }
        return num2;
    }
};
```

### 11、二进制中1的个数
##### 题目描述
输入一个整数，输出该数二进制表示中1的个数。其中负数用补码表示。
##### 题解
对于大于0的整数，直接统计每位的1的个数。   
对于小于0的整数需要求补码(反码+1)，通过一个标志来表示进位，开始进位为true，表示有进位。注意-2^31次方(-2147483648)，因为该数的补码为：1 1000 0000 0000 0000 0000 0000 0000 0000，溢出了一位，在32位下补码为：1000 0000 0000 0000 0000 0000 0000，而2^31次方也是1000 0000 0000 0000 0000 0000 0000，所以32位有符号范围是：-2^31到2^31-1
```
class Solution {
  public:
    int  NumberOf1(int n) {
      int sum = 0;
      if (n >= 0) {
        while (n > 0) {
          sum += n & 1;
          n = n >> 1;
        }
      } else {
        int len = 0;
        n = -n;
        bool first = true;  因为补码需要正码取反+1，因此这个标志从低位起的进位。true表示需要进位
        while (n != 0 && len != 32) {
          if (!(n&1) && !first) {   该位取反后=1，且没有进位，则该位的补码为1
            sum++;
          } else if ((n&1) && first) {  该位取反后=0，但有进位，则该位的补码为1
            sum++;
            first = false;
          } 
          n = n >> 1;   右移
          len++;
        }
        if (len < 32)   32位封顶，负数前面为0的取反码后都为1，且符号位也为1。 注意-2^31次方(-2147483648)，因为该数的补码为：1 1000 0000 0000 0000 0000 0000 0000 0000，溢出了一位，在32位下补码为：1000 0000 0000 0000 0000 0000 0000，所以答案是包含一个1.而2^31次方也是1000 0000 0000 0000 0000 0000 0000，所以32位有符号范围是：-2^31到2^31-1
          sum += 32-len;
      }
      return sum;
    }
};
```

### 12、数值的整数次方
##### 题目描述
给定一个double类型的浮点数base和int类型的整数exponent。求base的exponent次方。   
##### 题解
直接exponent个base相乘，注意当exponent小于0时需要取倒数。   
```
class Solution {
public:
    double Power(double base, int exponent) {
        double ans = 1;
        for (int i = 0; i < abs(exponent); i++) {
            ans *= base;
        }
        if (exponent < 0) ans = 1/ans;
        return ans;
    }
};
```
### 13、调整数组顺序使奇数位于偶数前面
##### 题目描述
输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有的奇数位于数组的前半部分，所有的偶数位于位于数组的后半部分，并保证奇数和奇数，偶数和偶数之间的相对位置不变。
##### 题解
这里就是采用遇到一个偶数，从后面找到第一个奇数，替换这个偶数的位置，然后这个偶数到奇数之间的数向后移。如： ... A B C D ..., 其中A，B为偶数，C为奇数，那么就有...C A B D ...。时间复杂度O(N)。   
```
class Solution {
public:
    void reOrderArray(vector<int> &array) {
        int odd = 0;
        for (auto &it : array) {
            if (it % 2 == 1)
                odd++;
        }
        int pos = 0;
        while (pos < array.size() && odd) {
            if (array[pos] % 2 == 0) {  偶数
                int tmp = array[pos];
                int tpos = pos++;
                while (pos < array.size() && array[pos]%2==0) {
                    std::swap(tmp, array[pos]);     当前为偶数时，直接交换，以当前偶数作为新的tmp
                    pos++;
                }
                array[tpos] = array[pos];
                array[pos] = tmp;
                pos = tpos+1;
                odd--;
            } else {
                odd--;
                pos++;
            }
        }
    }
};
```
### 14、链表中倒数第k个结点
##### 题目描述
输入一个链表，输出该链表中倒数第k个结点。
##### 题解
解法一：最直观就是走一遍求出链表长度，再根据链表长度减k来走第二次。   
解法二：加分解法。用两个指针，第一个指针先走k步，然后第二次指针再开始走，当指针1到终点时，指针2就是倒数第k个节点了。   
虽然都是O(N)的解法，但明显2比1好也比1快。   
```
class Solution {
public:
    ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
        if (!pListHead) return NULL;
        if (k == 0) return NULL;
        int i = 1;
        ListNode *p1 = pListHead;
        ListNode *p2 = pListHead;
        while (i < k) {
            if (p1->next) 
                p1 = p1->next;
            else 
                return NULL;
            i++;
        }
        while (p1->next != NULL) {
            p1 = p1->next;
            p2 = p2->next;
        }
        return p2;
    }
};
```

### 15、反转链表
##### 题目描述
输入一个链表，反转链表后，输出新链表的表头。
##### 题解
很直观，A->B->C->D ===> B->A, tmp保存C，C->D; ===> C->B->A， tmp保存D，===> D->C->B->A
```
class Solution {
public:
    ListNode* ReverseList(ListNode* pHead) {
        if (!pHead || !pHead->next)
            return pHead;
        ListNode *head;
        head = pHead;
        ListNode *node = pHead->next;
        while (node) {
            ListNode *tmp = node->next;
            node->next = head;
            head = node;
            node = tmp;
        }
        pHead->next = NULL;
        return head;
    }
};
```

### 16、合并两个排序的链表
##### 题目描述
输入两个单调递增的链表，输出两个链表合成后的链表，当然我们需要合成后的链表满足单调不减规则。
##### 题解
归并排序的合并过程。
```
class Solution {
public:
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
    {
        ListNode head(0);
        ListNode *node = &head;
        while (pHead1 != NULL && pHead2 != NULL) {
            if (pHead1->val < pHead2->val) {
                node->next = pHead1;
                node = node->next;
                pHead1 = pHead1->next;
            } else {
                node->next = pHead2;
                node = node->next;
                pHead2 = pHead2->next;
            }
        }
        while (pHead1 != NULL) {
            node->next = pHead1;
            node = node->next;
            pHead1 = pHead1->next;
        }
        while (pHead2 != NULL) {
            node->next = pHead2;
            node = node->next;
            pHead2 = pHead2->next;
        }
        return head.next;
    }
};
```

### 17、树的子结构
##### 题目描述
输入两棵二叉树A，B，判断B是不是A的子结构。（ps：我们约定空树不是任意一个树的子结构） 
##### 题解
遍历以A树的某个节点作为根节点，比较以该根节点作为子树(整颗子树)是否与B相等。   
```
class Solution {
public:
    bool isSame(TreeNode* node1, TreeNode* node2) {
        if (node1 == NULL)
            return true;
        if (node2 == NULL)
            return false;
        if (node1->val != node2->val) 
            return false;
        if ((node1->left&&!node2->left) || (node1->right&&!node2->right))
            return false;
        return isSame(node1->left, node2->left) && isSame(node1->right, node2->right);
    }
    bool dfs(TreeNode* node1, TreeNode* node2) {
        if (isSame(node2, node1))
            return true;
        bool same = false;
        if (node1->left) {
            same = same || dfs(node1->left, node2);
        }
        if (node1->right) {
            same = same || dfs(node1->right, node2);
        }
        return same;
    }
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        if (!pRoot2 || !pRoot1)
            return NULL;
        return dfs(pRoot1, pRoot2);
    }
};
```

### 18、二叉树的镜像
##### 题目描述
操作给定的二叉树，将其变换为源二叉树的镜像。   
输入描述:   
二叉树的镜像定义：   
源二叉树：   
```
    8   
   /  \   
  6   10   
 / \  / \   
5  7 9 11   
```
镜像二叉树：
```
    8
   /  \
  10   6
 / \  / \
11 9 7  5
```
##### 题解
直接递归将节点的左右子树交换即可。  
```
class Solution {
public:
    void Mirror(TreeNode *pRoot) {
        if (!pRoot) 
            return;
        std::swap(pRoot->left, pRoot->right);
        Mirror(pRoot->left);
        Mirror(pRoot->right);
    }
};
```

### 19、顺时针打印矩阵
##### 题目描述
输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字，例如，如果输入如下4 X 4矩阵：    
1  2  3  4    
5  6  7  8    
9  10 11 12    
13 14 15 16    
则依次打印出数字1,2,3,4,8,12,16,15,14,13,9,5,6,7,11,10.   
##### 题解
直接模拟就好，注意边界判断。   
```
class Solution {
public:
    vector<int> printMatrix(vector<vector<int> > matrix) {
        vector<int> ans;
        int left = 0;
        int right = matrix[0].size()-1;
        int bottom = 0;
        int top = matrix.size()-1;
        int sum = 0, total = matrix.size()*(right+1);
        while(sum < total) {
            for (int i = left; i <= right; i++, sum++)
                ans.push_back(matrix[bottom][i]);
            if (sum == total) break;
            bottom++;
            for (int i = bottom; i <= top; i++, sum++)
                ans.push_back(matrix[i][right]);
            if (sum == total) break;
            right--;
            for (int i = right; i >= left; i--, sum++)
                ans.push_back(matrix[top][i]);
            if (sum == total) break;
            top--;
            for (int i = top; i>= bottom; i--, sum++)
                ans.push_back(matrix[i][left]);
            if (sum == total) break;
            left++;
        }
        return ans;
    }
};
```

### 20、包含min函数的栈
##### 题目描述
定义栈的数据结构，请在该类型中实现一个能够得到栈中所含最小元素的min函数(时间复杂度应为O(1))。   
##### 题解
只需要两个栈，其中一个栈保存数据，另一个栈保存最小数据，s[0..n-1]表示入栈的数据，而min[0..n-1]表示栈的前n个数最小的数。如：   
6,2,4,5,1,7依次进栈，有min[0..n-1] = 6,2,2,2,1,1,这样s中栈顶元素出栈，min中的栈顶元素也会出栈。    
```
class Solution {
public:
    void push(int value) {
        data.push(value);
        if (!mins.size() || value < mins.top()) {
            mins.push(value);
        }else {
            mins.push(mins.top());
        }
    }   
    void pop() {
        data.pop();
        mins.pop();
    }
    int top() {
        return data.top();
    }
    int min() {
        return mins.top();
    }
    stack<int> data;
    stack<int> mins;
};
```     

### 21、栈的压入、弹出序列
##### 题目描述
输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否可能为该栈的弹出顺序。假设压入栈的所有数字均不相等。例如序列1,2,3,4,5是某栈的压入顺序，序列4,5,3,2,1是该压栈序列对应的一个弹出序列，但4,3,5,1,2就不可能是该压栈序列的弹出序列。（注意：这两个序列的长度是相等的）
##### 题解
用一个栈模拟即可，若栈顶元素等于弹出序列的首元素，则出栈，且弹出序列当前位置加1，如果弹出序列当前位置等于序列长度，则为true。
```
class Solution {
public:
    bool IsPopOrder(vector<int> pushV,vector<int> popV) {
        vector<int> stack;
        int i = 0, j = 0;
        while(i < popV.size()) {
            int x = popV[i++];
            if (stack.size() && stack.back() == x) {
                stack.pop_back();
                continue;
            }
            while(x != pushV[j] && j < pushV.size()) {
                stack.push_back(pushV[j]);
                j++;
            }
            if (j == pushV.size())
                return false;
            j++;
        }
        return true;
    }
};
```

### 22、从上往下打印二叉树
##### 题目描述
从上往下打印出二叉树的每个节点，同层节点从左至右打印。   
##### 题解
广度优先搜索
```
class Solution {
public:
    vector<int> PrintFromTopToBottom(TreeNode* root) {
        vector<int> ans;
        if (!root) 
            return ans;
        list<TreeNode*> nodes;
        nodes.push_back(root);
        while (nodes.size()) {
           TreeNode *node = nodes.front();
           nodes.pop_front();
           ans.push_back(node->val);
           if (node->left) {
               nodes.push_back(node->left);
           }
           if (node->right) {
               nodes.push_back(node->right);
           }
        }
        return ans;
    }
};
```

### 23、二叉搜索树的后序遍历序列
##### 题目描述
输入一个整数数组，判断该数组是不是某**二叉搜索树**的后序遍历的结果。如果是则输出Yes,否则输出No。假设输入的数组的任意两个数字都互不相同。
##### 题解
后序遍历首先遍历左子树，再遍历右子树，最后根节点。因此首先最后一个数字为根节点，可以将前面的数字分成两半，分割规则为：找到第一个数比根节点大，那么这个数前面的数为前半，这个数开始后面的数为后半。根据前半必须比根节点小的数字，后半必须为比根节点大的，此时只需要判断这两半是否符合要求。符合则递归操作这两半。   
```
class Solution {
public:
    bool isBinSearch(vector<int>& sequence, int head, int last) {
        if (head >= last) 
            return true;
        int x = sequence[last];
        int mid = head;
        for ( ; mid < last; mid++) {
            if (sequence[mid] > x) {
                break;
            }
        }
        for (int i = mid+1; i < last; i++)
            if (sequence[i] < x)
                return false;
        return isBinSearch(sequence, head, mid-1) && isBinSearch(sequence, mid, last-1);
    }
    
    bool VerifySquenceOfBST(vector<int> sequence) {
        if (sequence.size() == 0) 
            return false;
        int head = 0;
        int last = sequence.size()-1;
        return isBinSearch(sequence, head, last);
    }
};
```

### 24、二叉树中和为某一值的路径
##### 题目描述
输入一颗二叉树的跟节点和一个整数，打印出二叉树中结点值的和为输入整数的所有路径。路径定义为从树的根结点开始往下一直到叶结点所经过的结点形成一条路径。(注意: 在返回值的list中，数组长度大的数组靠前)
##### 题解
直接遍历所有的叶子得到路径和，看和是否等于给定的值。
```
class Solution {
public:
    void dfs(TreeNode *node, int sum, vector<int> &path, vector<vector<int>> &ans, int expectNumber) {
        if (!node->left && !node->right && sum == expectNumber) {
            ans.push_back(path);
            return;
        }
        if (node->left && sum+node->left->val <= expectNumber) {
            path.push_back(node->left->val);
            dfs(node->left, sum+node->left->val, path, ans, expectNumber);
            path.pop_back();
        }
        if (node->right && sum+node->right->val <= expectNumber) {
            path.push_back(node->right->val);
            dfs(node->right, sum+node->right->val, path, ans, expectNumber);
            path.pop_back();
        }
    }
    vector<vector<int> > FindPath(TreeNode* root,int expectNumber) {
        vector<vector<int>> ans;
        if (!root) 
            return ans;
        vector<int> path;
        path.push_back(root->val);
        dfs(root, root->val, path, ans, expectNumber);
        return ans;
    }
};
```
### 25、复杂链表的复制
##### 题目描述
输入一个复杂链表（每个节点中有节点值，以及两个指针，一个指向下一个节点，另一个特殊指针指向任意一个节点），返回结果为复制后复杂链表的head。（注意，输出结果中请不要返回参数中的节点引用，否则判题程序会直接返回空）
##### 题解
在每个节点x的后面插入一个节点，该节点与节点x一样，且随机指针与x指向一样。   
```
______
|     |
|     v
1->3->7->2->6   
```
插入后：   
```
_____________
|           |
|           V
1->1->3->3->7->7->2->2->6->6   
   |        ^
   |        |
   ——————————
   将random指向变为random->next即可。
```
此时只需要将新插入的节点的random指向random->next即可。     
最后将链表分成两个即可。   
```
/*
struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(NULL), random(NULL) {
    }
};
*/
class Solution {
public:
    RandomListNode* Clone(RandomListNode* pHead)
    {
        if (pHead == NULL)
            return NULL;
        RandomListNode *node = pHead;
        while (node) {
            RandomListNode* new_node = new RandomListNode(node->label);
            new_node->next = node->next;
            new_node->random = node->random;
            node->next = new_node;
            node = new_node->next;
        }
        node = pHead;
        while (node) {
            node = node->next;
            if (node->random)
                node->random = node->random->next;
            node = node->next;
        }
        node = pHead;
        RandomListNode *new_head = node->next;
        RandomListNode *new_node = new_head;
        while (new_node->next) {
            node->next = new_node->next;
            node = node->next;
            new_node->next = new_node->next->next;
            new_node = new_node->next;
        }
        node->next = NULL;
        return new_head;
    }
};
```

### 26、二叉搜索树与双向链表
##### 题目描述
输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。要求不能创建任何新的结点，只能调整树中结点指针的指向。   
##### 题解
中序遍历二叉搜索树，记录前一个访问的节点为pre，有：   
node->left = pre;   
pre->right = node;   
```
class Solution {
public:
    void dfs(TreeNode *node) {
        if (node->left)
            dfs(node->left);
        node->left = pre;
        if (pre != NULL)
            pre->right = node;
        pre = node;
        if (node->right)
            dfs(node->right);
    }
    TreeNode* Convert(TreeNode* pRootOfTree)
    {
        if (!pRootOfTree) return NULL;
        pre = NULL;
        dfs(pRootOfTree);
        pre = pRootOfTree;
        while (pre->left) pre = pre->left;
        return pre;
    }
private:
    TreeNode *pre;
};
```

### 27、字符串的排列
##### 题目描述
输入一个字符串,按字典序打印出该字符串中字符的所有排列。例如输入字符串abc,则打印出由字符a,b,c所能排列出来的所有字符串abc,acb,bac,bca,cab和cba。   
输入描述:   
输入一个字符串,长度不超过9(可能有字符重复),字符只包括大小写字母。   
##### 题解
递归搜索，每种可能试一遍，标志某一个位置的字母是否已经做选择了。需要再进行过滤掉重复的字符串，因为字符存在重复。 
```
class Solution {
public:
    void dfs(list<string> &ans, string str, string sub, vector<bool> &flag) {
        if (sub.size() == str.size()) {
            ans.push_back(sub);
            return;
        }
        for (int i = 0; i < str.size(); i++) {
            string tmp = sub;
            if (flag[i]) {
                tmp += str[i];
                flag[i] = false;
                dfs(ans, str, tmp, flag);
                flag[i] = true;
            }
        }
    }
    vector<string> Permutation(string str) {
        if (!str.size()) 
            return vector<string>();
        vector<bool> flag(str.size(), true);
        string sub = "";
        list<string> ans;
        dfs(ans, str, sub, flag);
        
        //过滤重复字符，因此上面采用了list形式
        unordered_set<string> filter;
        for (auto it = ans.begin(); it != ans.end(); ) {
            auto found = filter.find(*it);
            if (found == filter.end()) {
                filter.insert(*it);
                it++;
            } else {
                it = ans.erase(it);
            }
        }
        vector<string> rt(ans.begin(), ans.end());
        return rt;
    }
};
```

### 28、数组中出现次数超过一半的数字
##### 题目描述
数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。例如输入一个长度为9的数组{1,2,3,2,2,2,5,4,2}。由于数字2在数组中出现了5次，超过数组长度的一半，因此输出2。如果不存在则输出0。
##### 题解
对于answer来说，因为answer出现的次数超过一半，所以，如果每个answer与其他数进行一对一抵消的话，那么最后肯定还有answer剩余下来。可以根据这种规则去寻找answer。   
采用阵地攻守的思想：   
第一个数字作为第一个士兵，守阵地；count = 1;   
遇到相同元素，count++;   
遇到不相同元素，即为敌人，同归于尽,count--；   
当遇到count为0的情况，又以新的i值作为守阵地的士兵，继续下去，到最后还留在阵地上的士兵，有可能是主元素。   
再加一次循环，记录这个士兵的个数看是否大于数组一半即可。   
作者：cm问前程   
链接：https://www.nowcoder.com/questionTerminal/e8a1b01a2df14cb2b228b30ee6a92163   
来源：牛客网   
```
class Solution {
public:
    int MoreThanHalfNum_Solution(vector<int> numbers) {
        int ans = numbers[0];
        int count = 1;
        for (int i = 1; i < numbers.size(); i++) {
            if (count == 0) {
                ans = numbers[i];    
                count = 1;
                continue;
            } 
            if (numbers[i] != numbers[i-1]) 
                count--;
            else 
                count++;
        }
        if (count == 0) 
            return 0;
        count = 0;
        for (int i = 0; i < numbers.size(); i++) {
            if (ans == numbers[i])
                count++;
        }
        if (count > numbers.size()/2)
            return ans;
        return 0;
    }
};
```

### 29、最小的K个数
##### 题目描述
输入n个整数，找出其中最小的K个数。例如输入4,5,1,6,2,7,3,8这8个数字，则最小的4个数字是1,2,3,4,。
##### 题解
top-k问题，可用堆实现，stl提供priority_queue容器，底层采用heap实现。   
```
class Solution {
public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        if (input.size() < k) 
            return vector<int>();
        priority_queue<int, vector<int>, greater<int>> qu;
        for (auto &it : input) {
            qu.push(it);
        }
        vector<int> ans;
        for (int i = 0; i < k; i++) {
            ans.push_back(qu.top());
            qu.pop();
        }
        return ans;
    }
};
```

### 30、连续子数组的最大和
##### 题目描述
HZ偶尔会拿些专业问题来忽悠那些非计算机专业的同学。今天测试组开完会后,他又发话了:在古老的一维模式识别中,常常需要计算连续子向量的最大和,当向量全为正数的时候,问题很好解决。但是,如果向量中包含负数,是否应该包含某个负数,并期望旁边的正数会弥补它呢？例如:{6,-3,-2,7,-15,1,2,2},连续子向量的最大和为8(从第0个开始,到第3个为止)。给一个数组，返回它的最大连续子序列的和，你会不会被他忽悠住？(子向量的长度至少是1)
##### 题解
贪心比较，当小于0时重新选择。   
```
class Solution {
public:
    int FindGreatestSumOfSubArray(vector<int> array) {
        int max = array[0];
        int sum = max;
        for (int i = 1; i < array.size(); i++) {
            sum += array[i];
            if (sum > max)
                max = sum;
            if (sum < 0) {
                sum = 0;
            }
        }
        return max;
    }
};
```

### 31、整数中1出现的次数（从1到n整数中1出现的次数）

### 32、把数组排成最小的数
##### 题目描述
输入一个正整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。例如输入数组{3，32，321}，则打印出这三个数字能排成的最小数字为321323。
##### 题解
将数字转换成字符串后，进行排序，规则如下：   
对于字符串A和B有：   
若AB > BA，则 A > B；   
若AB < BA，则 B > A;   
若AB = BA, 则 A = B；   
解释说明：   
比如 "3" < "31"但是 "331" > "313"，所以要将二者拼接起来进行比较.
```
class Solution {
public:
    struct Comp {
        bool operator()(const string &x, const string &y) {
            string a = "";
            string b = "";
            a = x+y;
            b = y+x;
            return a < b;
        }
    };
    string PrintMinNumber(vector<int> numbers) {
        vector<string> data;
        for (auto &it : numbers) {
            data.emplace_back(to_string(it));
        }
        std::sort(data.begin(), data.end(), Comp());
        string ans = "";
        for (auto &it : data) {
            ans += it;
        }
        return ans;
    }
};
```

### 33、丑数
##### 题目描述
把只包含质因子2、3和5的数称作丑数（Ugly Number）。例如6、8都是丑数，但14不是，因为它包含质因子7。 习惯上我们把1当做是第一个丑数。求按从小到大的顺序的第N个丑数。
##### 题解
将已经是丑数的数分别乘2，乘3、乘5，那么得出来的结果也是丑数。依次按照大小如队列。    
```
class Solution {
public:
    int GetUglyNumber_Solution(int index) {
        if (index == 0) return 0;
        vector<int> ans;
        ans.push_back(1);
        int t2 = 0, t3 = 0, t5 = 0;
        for (int i = 1; i < index; i++) {
            int tmp = std::min(ans[t2]*2, std::min(ans[t3]*3, ans[t5]*5));
            ans.push_back(tmp);
            if (tmp == ans[t2]*2) t2++;
            if (tmp == ans[t3]*3) t3++;
            if (tmp == ans[t5]*5) t5++;
        }
        return ans.back();
    }
};
```

### 34、第一个只出现一次的字符
##### 题目描述
在一个字符串(0<=字符串长度<=10000，全部由字母组成)中找到第一个只出现一次的字符,并返回它的位置, 如果没有则返回 -1（需要区分大小写）.   
##### 题解
直接hash，char类型最大只是256。 
```
class Solution {
public:
    int FirstNotRepeatingChar(string str) {
        int hash[256];
        memset(hash, 0, sizeof(hash));
        for_each(str.c_str(), str.c_str()+str.size(), [&](char ch){ hash[ch]++;});
        int index = 0;
        for (char ch : str) {
            if (hash[ch] == 1)
                return index;
            index++;
        }
        return -1;
    }
};
```

### 35、数组中的逆序对
##### 题目描述
在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。输入一个数组,求出这个数组中的逆序对的总数P。并将P对1000000007取模的结果输出。 即输出P%1000000007
输入描述:   
题目保证输入的数组中没有的相同的数字   
数据范围：   
对于%50的数据,size<=10^4   
对于%75的数据,size<=10^5   
对于%100的数据,size<=2*10^5   
##### 题解
O(NLogN)算法，可以通过归并排序来统计逆序对。   
```
class Solution {
public:
    int merge(vector<int> &data, int h1, int l1, int h2, int l2) {
        vector<int> tmp;
        int s1 = h1;
        int s2 = h2;
        int ans = 0;
        while (s1 <= l1 && s2 <= l2) {
            if (data[s1] < data[s2]) {
                tmp.push_back(data[s1++]);
            }
            else {
                tmp.push_back(data[s2++]);
                ans += l1-s1+1;
                ans %= 1000000007;
            }
        }
        while (s1 <= l1) {
            tmp.push_back(data[s1++]);
        }
        while (s2 <= l2) {
            tmp.push_back(data[s2++]);
        }
        int index = 0;
        for (int i = h1; i <= l1; i++)
            data[i] = tmp[index++];
        for (int i = h2; i <= l2; i++)
            data[i] = tmp[index++];
        return ans;
    }
    void mergeSort(vector<int> &data, int head, int last, int &ans) 
    {
        if (head >= last)
            return;
        int mid = (head+last)/2;
        mergeSort(data, head, mid, ans);
        mergeSort(data, mid+1, last, ans);
        ans += merge(data, head, mid, mid+1, last);
        ans %= 1000000007;
    }
    int InversePairs(vector<int> data) {
        int ans = 0;
        mergeSort(data, 0, data.size()-1, ans);
        return ans;
    }
};
```

### 36、两个链表的第一个公共结点
##### 题目描述
输入两个链表，找出它们的第一个公共结点。   
##### 题解
基本思路就是求出两个链表的长度len1和len2，其中长的那个先走abs(len2-len1)步，再一起走，边走边比较节点。   
```
class Solution {
public:
    ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
        ListNode *node1 = pHead1;
        ListNode *node2 = pHead2;
        while (node1 && node2) {
            node1 = node1->next;
            node2 = node2->next;
        }
        if (node1) {
            ListNode *tmp = node1;  
            node1 = pHead1;
            node2 = pHead2;
            while (tmp) {
                node1 = node1->next;    长的那个先走多出来的步数
                tmp = tmp->next;
            }
        } else {
            ListNode *tmp = node2;
            node2 = pHead2;
            node1 = pHead1;
            while (tmp) {
                node2 = node2->next;    长的那个先走多出来的步数
                tmp = tmp->next;
            }
        }
        while (node1 && node2) {
            if (node1 == node2)
                return node1;
            node1 = node1->next;
            node2 = node2->next;
        }
        return NULL;
    }
};
```

### 37、数字在排序数组中出现的次数
##### 题目描述
统计一个数字在排序数组中出现的次数。   
##### 题解
二分找到数字，然后向前向后走统计。   
```
class Solution {
public:
    int GetNumberOfK(vector<int> data ,int k) {
        int left = 0;
        int right = data.size()-1;
        int sum = 0;
        while (left <= right) {
            int mid = (left+right)/2;
            if (data[mid] < k) {
                left = mid+1;
            } else if (data[mid] > k) {
                right = mid-1;
            } else {
                sum++;
                int tmp = mid+1;
                while (tmp < data.size() && data[tmp++] == k)
                    sum++;
                tmp = mid-1;
                while (tmp >= 0 && data[tmp--] == k) 
                    sum++;
                break;
            }
        }
        return sum;
    }
};
```

### 38、二叉树的深度
##### 题目描述
输入一棵二叉树，求该树的深度。从根结点到叶结点依次经过的结点（含根、叶结点）形成树的一条路径，最长路径的长度为树的深度。 
##### 题解
直接深搜。   
```
class Solution {
public:
    int TreeDepth(TreeNode* pRoot)
    {
        if (pRoot == NULL)
            return 0;
        return std::max(TreeDepth(pRoot->left), TreeDepth(pRoot->right))+1;
    }
};
```

### 39、平衡二叉树
##### 题目描述
输入一棵二叉树，判断该二叉树是否是平衡二叉树。
##### 题解
首先平衡二叉树是一颗二叉搜索树，因此需要判断左子树是否小于根节点，右子树是否大于根节点。其次，就是需要判断左子树的深度与右子树的深度之差不能超过1。然后一直向下递归。   
```
class Solution {
public:
    int depth(TreeNode* node, bool *over) {
        if (node == NULL || !*over) {
            return 0;
        }
        /* 目测这里的平衡二叉树并不等于平衡二叉排序树，wtf？？
        if (node->left && node->left->val > node->val)
            *over = false;
        if (node->right && node->right->val < node->val)
            *over = false;
        */
        int left_depth = depth(node->left, over);
        int right_depth = depth(node->right, over);
        if (abs(left_depth-right_depth) >= 2) 
            *over = false;
        return std::max(left_depth, right_depth)+1;
    }
    bool IsBalanced_Solution(TreeNode* pRoot) {
        bool over = true;
        depth(pRoot, &over);
        return over;
    }
};
```

### 40、数组中只出现一次的数字
##### 题目描述
一个整型数组里除了两个数字之外，其他的数字都出现了偶数次。请写程序找出这两个只出现一次的数字。    
##### 题解
采用异或，最后得到的结果就是这两个数字进行的异或，此时可以从低位开始比较结果的bit，当碰到第一个bit不为0时，表示这个两个数字一定只有一个在该bit上为1。因此可以根据这个bit将数据分成两份，然后这两份进行各自进行异或即可得到这两个数字。   
```
class Solution {
public:
    void FindNumsAppearOnce(vector<int> data,int* num1,int *num2) {
        if (data.size() < 2) 
            return;
        int sum = 0;
        for (auto &it : data) {
            sum = sum^it;
        }
        int index = 0;
        while ((sum&0x1) == 0) {
            sum >>= 1;
            index++;
        }
        *num1 = 0;
        *num2 = 0;
        for (auto &it : data) {
            int bit = (it>>index)&0x1;
            if (bit) {
                *num1 = *num1 ^ it;
            } else {
                *num2 = *num2 ^ it;
            }
        }
    }
};
```

### 41、和为S的连续正数序列
##### 题目描述
小明很喜欢数学,有一天他在做数学作业时,要求计算出9~16的和,他马上就写出了正确答案是100。但是他并不满足于此,他在想究竟有多少种连续的正数序列的和为100(至少包括两个数)。没多久,他就得到另一组连续正数和为100的序列:18,19,20,21,22。现在把问题交给你,你能不能也很快的找出所有和为S的连续正数序列? Good Luck!   
输出描述:   
输出所有和为S的连续正数序列。序列内按照从小至大的顺序，序列间按照开始数字从小到大的顺序   
##### 题解
窗口滑动，窗口为[left, right], 处于窗口内的相加是否等于S：   
1）若等于，成功得到一组，此时right+1继续查找。   
2）若小于，right+1，继续判断。   
3）若大于，left+1，继续判断。   
```
class Solution {
public:
    vector<vector<int> > FindContinuousSequence(int sum) {
        int total = 0;
        list<int> seq;
        vector<vector<int>> ans;
        for (int i = 1; i < sum; i++) {
            total += i;
            seq.push_back(i);
            while (total > sum && seq.size()) {
                total -= seq.front();
                seq.pop_front();
            }
            if (total > sum) {
                total = 0;
                seq.clear();
            }
            if (total == sum) {
                ans.emplace_back(seq.begin(), seq.end());
            }
        }
        return ans;
    }
};
```

### 42、和为S的两个数字
##### 题目描述
输入一个递增排序的数组和一个数字S，在数组中查找两个数，使得他们的和正好是S，如果有多对数字的和等于S，输出两个数的乘积最小的。   
输出描述:   
对应每个测试案例，输出两个数，小的先输出。   
##### 题解
解法一：O(NlogN)，直接找到一个数x，然后二分查找S-x是否存在。    
```
class Solution {
public:
    vector<int> FindNumbersWithSum(vector<int> array,int sum) {
        if (!array.size()) 
            return vector<int>();
        int ansx;
        int ansy;
        int minM = array.back()*array.back();
        for (int i = 0; i < array.size()-1; i++) {
            int x = array[i];
            int y = sum-x;
            int head = i+1, last = array.size()-1;
            while (head <= last) {
                int mid = (head+last)/2;
                if (array[mid] == y) {
                    if (x*y < minM) {
                        minM = x*y;
                        ansx = x;
                        ansy = y;
                    }
                    break;
                } else if (array[mid] < y) {
                    head = mid+1;
                } else 
                    last = mid-1;
            }
        }
        vector<int> ans;
        if (minM != array.back()*array.back()) {
            ans.push_back(ansx);
            ans.push_back(ansy);
        }
        return ans;
    }
};
```
解法二：因为有序，可以采用左右夹逼算法。a[i]+a[j] < S, 则i++, 若a[i]+a[j] > S, 则j--。   
```
class Solution {
public:
    vector<int> FindNumbersWithSum(vector<int> array,int sum) {
        vector<int> ans;
        if (!array.size() || array.size() == 1) 
            return ans;
        int i = 0, j = array.size()-1;
        while (i < j) {
            if (array[i]+array[j] == sum) {
                //实际上遇到的第一组乘积肯定是最少的
                ans.push_back(array[i]);
                ans.push_back(array[j]);
                return ans;
            } else if (array[i]+array[j] > sum) {
                j--;
            } else {
                i++;
            }
        }
        return ans;
    }
};
```

### 43、左旋转字符串
##### 题目描述
汇编语言中有一种移位指令叫做循环左移（ROL），现在有个简单的任务，就是用字符串模拟这个指令的运算结果。对于一个给定的字符序列S，请你把其循环左移K位后的序列输出。例如，字符序列S=”abcXYZdef”,要求输出循环左移3位后的结果，即“XYZdefabc”。是不是很简单？OK，搞定它！
##### 题解
就是将前n%S.size()位移动到后面。   
```
class Solution {
public:
    string LeftRotateString(string str, int n) {
        if (!str.size()) 
            return "";
        n = n%str.size();
        string ans = str.substr(n, str.size()-n);
        ans.append(str.substr(0,n));
        return ans;
    }
};
```

### 44、翻转单词顺序列
##### 题目描述
牛客最近来了一个新员工Fish，每天早晨总是会拿着一本英文杂志，写些句子在本子上。同事Cat对Fish写的内容颇感兴趣，有一天他向Fish借来翻看，但却读不懂它的意思。例如，“student. a am I”。后来才意识到，这家伙原来把句子单词的顺序翻转了，正确的句子应该是“I am a student.”。Cat对一一的翻转这些单词顺序可不在行，你能帮助他么？   
##### 题解
直接模拟即可。   
```
class Solution {
public:
    string ReverseSentence(string str) {
        int st = 0;
        int pos = 0;
        string ans = "";
        while ((pos = str.find(' ', st)) != string::npos) {
            ans = " " + str.substr(st, pos-st) + ans;
            st = pos+1;
        }
        ans = str.substr(st) + ans;
        return ans;
    }
};
```

### 45、扑克牌顺子
##### 题目描述
LL今天心情特别好,因为他去买了一副扑克牌,发现里面居然有2个大王,2个小王(一副牌原本是54张^_^)...他随机从中抽出了5张牌,想测测自己的手气,看看能不能抽到顺子,如果抽到的话,他决定去买体育彩票,嘿嘿！！“红心A,黑桃3,小王,大王,方片5”,“Oh My God!”不是顺子.....LL不高兴了,他想了想,决定大\小王可以看成任何数字,并且A看作1,J为11,Q为12,K为13。上面的5张牌就可以变成“1,2,3,4,5”(大小王分别看作2和4),“So Lucky!”。LL决定去买体育彩票啦。 现在,要求你使用这幅牌模拟上面的过程,然后告诉我们LL的运气如何， 如果牌能组成顺子就输出true，否则就输出false。为了方便起见,你可以认为大小王是0。  
##### 题解
直接哈希保存。    
```
class Solution {
public:
    bool IsContinuous( vector<int> numbers ) {
        int shunzi[14];
        memset(shunzi, 0, sizeof(shunzi));
        for (auto &it : numbers) {
            shunzi[it]++;
        }
        int wang = shunzi[0];
        int flag = 0;
        for (int i = 1; i < 14; i++) {
            if (shunzi[i] == 1) {
                flag++;
            } else if (flag && shunzi[i]==0 && wang > 0) {
                wang--;
                flag++;
            } else if (shunzi[i] > 1) {
                return false;
            } else if (shunzi[i] == 0 && wang == 0) {
                flag = 0;
            } 
            if (flag == 5) 
                return true;
        }
        return false;
    }
};
```

### 46、孩子们的游戏(圆圈中最后剩下的数)
##### 题目描述
每年六一儿童节,牛客都会准备一些小礼物去看望孤儿院的小朋友,今年亦是如此。HF作为牛客的资深元老,自然也准备了一些小游戏。其中,有个游戏是这样的:首先,让小朋友们围成一个大圈。然后,他随机指定一个数m,让编号为0的小朋友开始报数。每次喊到m-1的那个小朋友要出列唱首歌,然后可以在礼品箱中任意的挑选礼物,并且不再回到圈中,从他的下一个小朋友开始,继续0...m-1报数....这样下去....直到剩下最后一个小朋友,可以不用表演,并且拿到牛客名贵的“名侦探柯南”典藏版(名额有限哦!!^_^)。请你试着想下,哪个小朋友会得到这份礼品呢？(注：小朋友的编号是从0到n-1)     
##### 题解
约瑟夫环，用循环链表模拟需要O(NM)的时间复杂度，采用数学方法可以实现O(N)的时间复杂度。   
n个人编号从0到n-1，报到m-1的退出，剩下的人重新从0开始，第一个人(编号一定是(m-1)%n出列后，剩下n-1个人组成一个新的约瑟夫环，编号从k=m%n开始：k，k+1，k+2，...,n-2，n-1，0，1，2，...，k-2。并且从k开始报0。现在我们从编号做一下转换：   
k --> 0    
k+1 --> 1   
k+2 --> 2   
...
k-2 --> n-2   
变换后就完全变成了n-1个人报数的子问题了，此时k这个编号实际上应该是(m-1)%n+1,即第一个人出列后的下一个人的编号，(m-1)%n+1 ==> (m-1+1)%n ==> m%n。   
```
class Solution {
public:
    int LastRemaining_Solution(int n, int m)
    {
        if (n == 0) 
            return -1;
        if (n == 1) 
            return 0;
        return (LastRemaining_Solution(n-1, m)+m)%n;
    }
};
```

### 47、求1+2+3+...+n
##### 题目描述
求1+2+3+...+n，要求不能使用乘除法、for、while、if、else、switch、case等关键字及条件判断语句（A?B:C）。   
##### 题解
使用&&判断是否需要再递归。   
```
class Solution {
public:
    int Sum_Solution(int n) {
        int ans = n;
        ans && (ans += Sum_Solution(n-1));
        return ans;
    }
};
```

### 48、不用加减乘除做加法
##### 题目描述
写一个函数，求两个整数之和，要求在函数体内不得使用+、-、*、/四则运算符号。
##### 题解
num1^num2：num1异或num2，相当于无进位的加法。   
(num1&num2)<< 1： num1与num2，并左移一位，相当于所有的进位。   
让无进位的加法+所有位的进位=加法。    
一直运算，直到没有进位为止。   
```
class Solution {
public:
    int Add(int num1, int num2)
    {
        while (num2 != 0) {
            int sum = num1 ^ num2;
            int jinwei = (num1 & num2) << 1;
            num1 = sum;
            num2 = jinwei;
        }
        return num1;
    }
};
```

### 49、把字符串转换成整数
##### 题目描述
将一个字符串转换成一个整数(实现Integer.valueOf(string)的功能，但是string不符合数字要求时返回0)，要求不能使用字符串转换整数的库函数。数值为0或者字符串不是一个合法的数值则返回0。
##### 题解
需要判断正负。
```
class Solution {
public:
    int StrToInt(string str) {
        if (!str.size()) return 0;
        int ans = 0, i = 0;
        if (str[0] == '+' || str[0] == '-')
            i++;
        for ( ; i < str.size(); i++) {
            if (!(str[i] >='0' && str[i] <= '9')) {
                return 0;
            }
            ans = ans*10 + str[i]-'0';
        }
        if (str[0] == '-')
            return -ans;
        return ans;
    }
};
```

### 50、数组中重复的数字
##### 题目描述
在一个长度为n的数组里的所有数字都在0到n-1的范围内。 数组中某些数字是重复的，但不知道有几个数字是重复的。也不知道每个数字重复几次。请找出数组中任意一个重复的数字。 例如，如果输入长度为7的数组{2,3,1,0,2,5,3}，那么对应的输出是第一个重复的数字2。   
##### 题解
数组的数在0到n-1之间，将number[number[i]] += n; 若number[number[i]] >= 2*n表示number[i]超过两次，原来的number[number[i]]的数就是number[number[i]]%n.   
```
class Solution {
public:
    bool duplicate(int numbers[], int length, int* duplication) {
        for (int i = 0; i < length; i++) {
            int tmp = numbers[i];
            tmp %= length;
            numbers[tmp] += length;
        }
        for (int i = 0; i < length; i++) {
            int tmp = numbers[i];
            tmp %= length;
            if (numbers[tmp] >= 2*length) {
                *duplication = tmp;
                return true;
            }
        }
        return false;
    }
};
```

### 51、构建乘积数组
##### 题目描述
给定一个数组A[0,1,...,n-1],请构建一个数组B[0,1,...,n-1],其中B中的元素B[i]=A[0]\*A[1]\*...\*A[i-1]\*A[i+1]\*...\*A[n-1]。不能使用除法。   
##### 题解  
先从前开始走，B[i] = tmp\*A[i-1]; tmp=A[0]\*...A[i-2], 然后再从后向前走，B[i] = tmp\*A[i+1]; tmp = A[i+2]\*...\*A[n-1].
```
class Solution {
public:
    vector<int> multiply(const vector<int>& A) {
        if (A.size() == 0)
            return vector<int>();
        vector<int> B(A.size(), 1);
        for (int i = 1; i < A.size(); i++)
            B[i] = B[i-1]*A[i-1];
        int tmp = A[A.size()-1];
        for (int i = A.size()-2; i >= 0; i--) {
            B[i] = B[i] * tmp;
            tmp *= A[i];
        }
        return B;
    }
};
```

### 52、正则表达式匹配
##### 题目描述
请实现一个函数用来匹配包括'.'和'*'的正则表达式。模式中的字符'.'表示任意一个字符，而'*'表示它前面的字符可以出现任意次（包含0次）。在本题中，匹配是指字符串的所有字符匹配整个模式。例如，字符串"aaa"与模式"a.a"和"ab*ac*a"匹配，但是与"aa.a"和"ab*a"均不匹配   
##### 题解

### 53、表示数值的字符串
##### 题目描述
请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。例如，字符串"+100","5e2","-123","3.1416"和"-1E-16"都表示数值。 但是"12e","1a3.14","1.2.3","+-5"和"12e+4.3"都不是。  
##### 题解
逐个检查。
```
class Solution {
public:
    bool isNumeric(char* string)
    {
        if (strlen(string) == 0)
            return false;
        int pos = 0;
        if (string[pos] == '+' || string[pos] == '-')
            pos++;
        bool eflag = true, pflag = true;    //eflag表示e的次数，pflag表示小数点的次数，他们都只能存在一次。
        for (int i = pos; i < strlen(string); i++) {
            if (string[i] >= '0' && string[i] <= '9')
                continue;
            if (tolower(string[i]) == 'e' && eflag && i < strlen(string)-1) {
                eflag = false;
                pflag = false;
                continue;
            }
            if (string[i] == '+' || string[i] == '-') {
                if (tolower(string[i-1]) == 'e')
                    continue;
            }
            if (string[i] == '.' && pflag) {
                pflag = false;
                continue;
            }
                
            return false;
        }
        return true;
    }

};
```

### 54、字符流中第一个不重复的字符
##### 题目描述
请实现一个函数用来找出字符流中第一个只出现一次的字符。例如，当从字符流中只读出前两个字符"go"时，第一个只出现一次的字符是"g"。当从该字符流中读出前六个字符“google"时，第一个只出现一次的字符是"l"。   
输出描述:   
如果当前字符流没有存在出现一次的字符，返回#字符。   
##### 题解
直接hash吧，char只有256大小。 
```
class Solution
{
public:
  //Insert one char from stringstream
    void Insert(char ch)
    {
        str.push_back(ch);
        chset.insert(ch);
    }
  //return the first appearence once char in current stringstream
    char FirstAppearingOnce()
    {
        for (auto &ch : str) {
            int count = chset.count(ch);
            if (count == 1) 
                return ch;
        }
        return '#';
    }
    unordered_multiset<char> chset;
    vector<char> str;
};
```

### 55、链表中环的入口结点
##### 题目描述
给一个链表，若其中包含环，请找出该链表的环的入口结点，否则，输出null。 
##### 题解
快慢指针相遇，再得到环的长度，然后重新开始，一指针先走环的长度，另一指针再走，再次相遇即为入口点。    
还是比较难理解的思想：快慢指针相遇，此时其中一个指针从0重新开始，一个指针在相遇点开始，两指针同时走，再次相遇点即为入口点。   
```
/*
struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
    TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {
        
    }
};
*/
class Solution {
public:
    ListNode* EntryNodeOfLoop(ListNode* pHead)
    {
        if (!pHead) return NULL;
        ListNode *fast = pHead;
        ListNode *slow = pHead;
        while (fast->next) {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow)
                break;
        }
        if (!fast->next)
            return NULL;
        int size = 1;
        fast = fast->next;
        while (fast != slow) {
            fast = fast->next;
            size++;
        }
        fast = pHead;
        for (int i = 0; i < size; i++)
            fast = fast->next;
        slow = pHead;
        while (fast != slow) {
            fast = fast->next;
            slow = slow->next;
        }
        return fast;
    }
};
```

### 56、删除链表中重复的结点
##### 题目描述
在一个排序的链表中，存在重复的结点，请删除该链表中重复的结点，重复的结点不保留，返回链表头指针。 例如，链表1->2->3->3->4->4->5 处理后为 1->2->5   
##### 题解
需要保存一个prev节点。因此建立一个头结点，指向pHead，查找将相同的节点点删除。   
```
class Solution {
public:
    ListNode* deleteDuplication(ListNode* pHead)
    {
        if (!pHead) 
            return NULL;
        ListNode *pRoot = new ListNode(0);
        pRoot->next = pHead;
        int val = pHead->val;
        int count = 1;
        ListNode *node = pHead->next;
        ListNode *pre = pRoot;
        while (node) {
           while (node && node->val == val) {
               node = node->next;
               count++;
           }
           if (count > 1) {
               for (ListNode *i = pre->next; i != node; ) {
                }     
               count = 1;
               pre->next = node;
           } else {
               pre = pre->next;
           }
           if (!node) break;
           val = node->val;
           node = node->next;
        }
        if (!pRoot->next)
            return NULL;
        ListNode *head = pRoot->next;
        delete pRoot;
        return head;
    }
};
```

### 57、二叉树的下一个结点
##### 题目描述
给定一个二叉树和其中的一个结点，请找出中序遍历顺序的下一个结点并且返回。注意，树中的结点不仅包含左右子结点，同时包含指向父结点的指针。
##### 题解
直接找到根节点再进行遍历。
```
class Solution {
public:
    void midsearch(TreeLinkNode *node, TreeLinkNode *target) {
        if (node->left)
            midsearch(node->left, target);
        if (pre == target) {
            ans = node;
        }
        pre = node;
        if (node->right)
            midsearch(node->right, target);
    }
    TreeLinkNode* GetNext(TreeLinkNode* pNode)
    {
        if (!pNode) 
            return NULL;
        TreeLinkNode *root = pNode;
        while (root->next)
            root = root->next;
        pre = NULL;
        ans = NULL;
        midsearch(root, pNode);
        return ans;
    }
private:
    TreeLinkNode *pre;
    TreeLinkNode *ans;
};
```

### 58、对称的二叉树
##### 题目描述
请实现一个函数，用来判断一颗二叉树是不是对称的。注意，如果一个二叉树同此二叉树的镜像是同样的，定义其为对称的。
##### 题解
对根节点的左子树node1和根节点的node2比较，符合则node1->left和node2->right比较、node2->right和node1->left比较。递归进行。   
```
class Solution {
public:
    bool isSame(TreeNode *left, TreeNode *right) {
        if (!left && !right) 
            return true;
        if (!left && right || !right && left)
            return false;
        if (left && right && left->val != right->val) {
            return false;
        }
        return isSame(left->right, right->left) && isSame(left->left, right->right);
    }
    bool isSymmetrical(TreeNode* pRoot)
    {
        if (!pRoot) 
            return true;
        return isSame(pRoot->left, pRoot->right);
    }

};
```

### 59、按之字形顺序打印二叉树
##### 题目描述
请实现一个函数按照之字形打印二叉树，即第一行按照从左到右的顺序打印，第二层按照从右至左的顺序打印，第三行按照从左到右的顺序打印，其他行以此类推。
##### 题解
广度搜索，设置标志，从某一层的从左到右入队列，到下一层从右到左入队列。   
```

class Solution {
public:
    vector<vector<int> > Print(TreeNode* pRoot) {
        vector<TreeNode*> nodes;
        vector<vector<int>> result;
        if (!pRoot) 
            return result;
        nodes.push_back(pRoot);
        int pos = 0;
        int next_level = 1;
        bool flag = true;
        while (pos < next_level) {
             vector<int> level;
            if (flag) {
                for (int i = pos; i < next_level; i++)
                    level.push_back(nodes[i]->val);    
                flag = !flag;
            } else {
                for (int i = next_level-1; i >= pos; i--)
                    level.push_back(nodes[i]->val);
                flag = !flag;
            }
            for (int i = pos; i < next_level; i++) {
                if (nodes[i]->left)
                    nodes.push_back(nodes[i]->left);
                if (nodes[i]->right)
                    nodes.push_back(nodes[i]->right);
            }
            pos = next_level;
            next_level = nodes.size();
            if (level.size())
                result.push_back(level);
        }
        return result;
    }
    
};
```

### 60、把二叉树打印成多行
##### 题目描述
从上到下按层打印二叉树，同一层结点从左至右输出。每一层输出一行。
##### 题解
直接就是一个广度优先搜索。   
```
class Solution {
public:
        vector<vector<int> > Print(TreeNode* pRoot) {
            vector<vector<int>> ans;
            if (!pRoot) 
                return ans;
            list<TreeNode*> nodes;
            nodes.push_back(pRoot);
            vector<int> value;
            TreeNode* flag_node = pRoot;
            while (nodes.size()) {
                TreeNode *node = nodes.front();
                value.push_back(node->val);
                nodes.pop_front();
                if (node->left) 
                    nodes.push_back(node->left);
                if (node->right)
                    nodes.push_back(node->right);
                if (flag_node == node) {
                    ans.push_back(value);
                    value.clear();
                    flag_node = nodes.back();
                }
            }
            return ans;
        }
};
```

### 61、序列化二叉树
##### 题目描述
请实现两个函数，分别用来序列化和反序列化二叉树

##### 题解

### 62、二叉搜索树的第k个结点
##### 题目描述
给定一棵二叉搜索树，请找出其中的第k小的结点。例如， （5，3，7，2，4，6，8）    中，按结点数值大小顺序第三小结点的值为4。
##### 题解
直接中序遍历得到第k小的数。   
```
class Solution {
public:
    void dfs(TreeNode* node, int &m, int k, TreeNode **ans) {
        
        if (node->left) 
            dfs(node->left, m, k, ans);
        m++;
        if (m == k) 
            *ans = node;
        if (node->right) 
            dfs(node->right, m, k, ans);
    }
    TreeNode* KthNode(TreeNode* pRoot, int k)
    {
        if (!pRoot) return NULL;
        int m = 0;
        TreeNode* ans = NULL;
        dfs(pRoot, m, k, &ans);
        return ans;
    }
};
```

### 63、数据流中的中位数
##### 题目描述
如何得到一个数据流中的中位数？如果从数据流中读出奇数个数值，那么中位数就是所有数值排序之后位于中间的数值。如果从数据流中读出偶数个数值，那么中位数就是所有数值排序之后中间两个数的平均值。我们使用Insert()方法读取数据流，使用GetMedian()方法获取当前读取数据的中位数。   
##### 题解
很直接解法的有序插入法，插入时间O(N)，得到中位数时间O(1)。
加分解法：
插入时间O(logN)，得到中位数时间O(1)。建立一个大根堆和小根堆，比较大的那部分数放入小根堆，比较小的那部分数放入大根堆，取两根节点得到中位数。   
```
class Solution {
public:
    void Insert(int num)
    {
        if (!max_heap.size() || max_heap.top() > num)
            max_heap.push(num);
        else 
            min_heap.push(num);
    }

    double GetMedian()
    {
        if (max_heap.size() > min_heap.size()+1) {
            min_heap.push(max_heap.top());
            max_heap.pop();
        } else if (max_heap.size() + 1 < min_heap.size()) {
            max_heap.push(min_heap.top());
            min_heap.pop();
        }
        if (max_heap.size() > min_heap.size()) {
            return max_heap.top();
        } else if (max_heap.size() < min_heap.size()) {
            return min_heap.top();
        } else {
            return (min_heap.top()+max_heap.top())/2.0;
        }
    }
    priority_queue<int, vector<int>, less<int>> max_heap;
    priority_queue<int, vector<int>, greater<int>> min_heap;
};
```

### 64、滑动窗口的最大值
##### 题目描述
给定一个数组和滑动窗口的大小，找出所有滑动窗口里数值的最大值。例如，如果输入数组{2,3,4,2,6,2,5,1}及滑动窗口的大小3，那么一共存在6个滑动窗口，他们的最大值分别为{4,4,6,6,6,5}； 针对数组{2,3,4,2,6,2,5,1}的滑动窗口有以下6个： {[2,3,4],2,6,2,5,1}， {2,[3,4,2],6,2,5,1}， {2,3,[4,2,6],2,5,1}， {2,3,4,[2,6,2],5,1}， {2,3,4,2,[6,2,5],1}， {2,3,4,2,6,[2,5,1]}。
##### 题解
使用一个队列list保存最大值，队列的第一个元素表示当前窗口的最大值，当窗口滑动一次，有：   
1）判断当前最大值是否过期。   
2）新加入的数从队尾开始比较，如果队尾的数比新加入的数小，那么删除队尾的数，直到删无可删则将新的数加入队尾。   
```
class Solution {
public:
    vector<int> maxInWindows(const vector<int>& num, unsigned int size)
    {
        list<int> max_num;
        vector<int> ans;
        if (!num.size()) 
            return ans;
        bool flag = false;
        for (int i = 0; i < num.size(); i++) {
            if (flag) { //已形成窗口
                if (max_num.front() == num[i-size])     //最大的数是否过期了
                    max_num.pop_front();
                while (max_num.size() && max_num.back() < num[i]) {     //小于号，相等的是不会被删除的
                    max_num.pop_back();
                }
                max_num.push_back(num[i]);
                ans.push_back(max_num.front());
            } else {    //还未形成窗口
                while (max_num.size() && max_num.back() < num[i]) {
                    max_num.pop_back();
                }
                max_num.push_back(num[i]);
                if (i == size-1) {
                    ans.push_back(max_num.front());
                    flag = true;
                }
            }
        }
        return ans;
    }
};
```

### 65、矩阵中的路径
##### 题目描述
请设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有字符的路径。路径可以从矩阵中的任意一个格子开始，每一步可以在矩阵中向左，向右，向上，向下移动一个格子。如果一条路径经过了矩阵中的某一个格子，则之后不能再次进入这个格子。 例如 a b c e s f c s a d e e 这样的3 X 4 矩阵中包含一条字符串"bcced"的路径，但是矩阵中不包含"abcb"路径，因为字符串的第一个字符b占据了矩阵中的第一行第二个格子之后，路径不能再次进入该格子。   
##### 题解
搜索，当矩阵某个点等于字符串的头结点，则开始深度搜索。   
```
class Solution {
public:
    bool dfs(char matrix[],int i, int j, int rows, int cols, char str[], int index, int len, vector<vector<int>> &flag){
        if (matrix[i*cols+j] != str[index]) {
            return false;
        }
        if (index+1 == len)
            return true;
        bool ans = false;
        if (i-1 >= 0 && !flag[i-1][j]) {
            flag[i-1][j] = 1;
            ans = ans || dfs(matrix, i-1, j, rows, cols, str, index+1, len, flag);
            flag[i-1][j] = 0;
        }
        if (i+1 < rows && !flag[i+1][j]) {
            flag[i+1][j] = 1;
            ans = ans || dfs(matrix, i+1, j, rows, cols, str, index+1, len, flag);
            flag[i+1][j] = 0;
        }
        if (j-1 >= 0 && !flag[i][j-1]) {
            flag[i][j-1] = 1;
            ans = ans || dfs(matrix, i, j-1, rows, cols, str, index+1, len, flag);
            flag[i][j-1] = 0;
        }
        
        if (j+1 < cols && !flag[i][j+1]) {
            flag[i][j+1] = 1;
            ans = ans || dfs(matrix, i, j+1, rows, cols, str, index+1, len, flag);
            flag[i][j+1] = 0;
        }
        return ans;
    }
    bool hasPath(char* matrix, int rows, int cols, char* str)
    {
        for (int i = 0; i < rows; i++)
            for(int j = 0; j < cols; j++) {
                if (*(matrix+i*cols+j) == *str) {
                    vector<vector<int>> flag(rows, vector<int>(cols, 0));
                    flag[i][j] = 1;
                    bool ans = dfs(matrix, i, j, rows, cols, str, 0, strlen(str), flag);
                    if (ans)
                        return ans;
                }
            }
        return false;
    }
};
```

### 66、机器人的运动范围
##### 题目描述
地上有一个m行和n列的方格。一个机器人从坐标0,0的格子开始移动，每一次只能向左，右，上，下四个方向移动一格，但是不能进入行坐标和列坐标的数位之和大于k的格子。 例如，当k为18时，机器人能够进入方格（35,37），因为3+5+3+7 = 18。但是，它不能进入方格（35,38），因为3+5+3+8 = 19。请问该机器人能够达到多少个格子？    
##### 题解
深度搜索。
```
class Solution {
public:
    int dfs(vector<vector<int>> &f, int i, int j, int rows, int cols) {
        int ans = 1;
        f[i][j] = 1;
        if (i > 0 && !f[i-1][j])
            ans += dfs(f, i-1, j, rows, cols);
        if (j > 0 && !f[i][j-1])
            ans += dfs(f, i, j-1, rows, cols);
        if (i < rows-1 && !f[i+1][j])
            ans += dfs(f, i+1, j, rows, cols);
        if (j < cols-1 && !f[i][j+1])
            ans += dfs(f, i, j+1, rows, cols);
        return ans;
    }
    int movingCount(int threshold, int rows, int cols)
    {
        int maxindex = std::max(rows, cols);
        int count[maxindex];
        for (int i = 0; i < maxindex; i++) {
            int tmp = i;
            count[i] = 0;
            while (tmp > 0) {
                count[i] += tmp%10;
                tmp /= 10;
            }                
        }
        vector<vector<int>> f(rows, vector<int>(cols, 0));
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (count[i]+count[j] > threshold)
                    f[i][j] = 1;
            }
        }
        if (!f[0][0])
            return dfs(f, 0, 0, rows, cols);
        return 0;
    }
};
```
