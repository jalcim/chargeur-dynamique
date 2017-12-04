#include <test.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define NB_METHOD 2
#define SIZE_METHOD_NAME 10

char **ft_test()
{
  char **tab_method = (char **)malloc(NB_METHOD + 1);

  tab_method[0] = (char *)malloc(SIZE_METHOD_NAME);
  tab_method[1] = (char *)malloc(SIZE_METHOD_NAME);
  tab_method[2] = NULL;

  strncpy(tab_method[0], "fonction1\0", 10);
  strncpy(tab_method[1], "fonction2\0", 10);

  return (tab_method);
}

void *fonction1(void *arg)
{
  write(1, "1\n", 2);
  return (NULL);
}

void *fonction2(void *arg)
{
  write(1, "2\n", 2);
  return (NULL);
}
