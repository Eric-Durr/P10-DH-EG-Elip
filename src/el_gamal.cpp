#include "../include/el_gamal.h"

int main(int argc, char *argv[])
{
  int flag = filter(argc, argv);
  if (flag != 0)
  {
    return flag;
  }

  return 0;
}
