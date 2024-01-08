#include "defs.h"

int main(int argc, char *argv[])
{
  if (argc == 1)
  {
    runEscape();
  }
  else if (argc == 2)
  {
    viewEscape(argv[1]);
  }
  else
  {
    printf("Usage:\n");
    printf("Server: %s\n", argv[0]);
    printf("Client: %s <server_ip>\n", argv[0]);
    return 1;
  }

  return 0;
}

/*
  Purpose:  generates a random integer
       in:  max integer
   return:  the random int modulus the max
*/
int randomInt(int max)
{
  return (rand() % max);
}
