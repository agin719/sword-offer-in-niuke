#include <string.h>

class Solution {
  public:
    void replaceSpace(char *str,int length) {
      int space_count = 0;
      for (int i = 0; i < length; i++) {
        if (str[i] == ' ') {
          space_count++;
        }
      }
      char tmp[length];
      strncpy(tmp, str, length);
      str = (char*) realloc(str, length+2*space_count);
      char *ptr = str;
      for (int i = 0; i < length; i++) {
        if (tmp[i] == ' ') {
          (*ptr)++ = '%';
          (*ptr)++ = '2';
          (*ptr)++ = '0';
        } else {
          *ptr++ = tmp[i];
        }
      }
    }
};

int main()
{
  return 0;
}
