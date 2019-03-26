#include "types.h"
#include "user.h"
#include "fcntl.h"
#include "stat.h"

int
main(int argc, char **argv)
{
  const char *policyList[3] = { "ROUND_ROBIN", "PRIORITY", "E_PRIORITY" };
  int pol = atoi(argv[1]);
  policy(pol);
  printf(2, "The policy changed to: %s\n",policyList[--pol]);
  exit(0);
}
