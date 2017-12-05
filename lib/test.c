#include <test.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define NB_METHOD 3
#define SIZE_METHOD_NAME 10

char **m_init()
{
  char **tab_method;

  tab_method = (char **)malloc((NB_METHOD + 1) * sizeof(char *));
  tab_method[0] = "m_exit\0";
  tab_method[1] = "fonction1\0";
  tab_method[2] = "fonction2\0";
  tab_method[3] = NULL;
  return (tab_method);
}

void *m_exit(void *arg)
{
  char **tab_method;

  printf("m_exit\n");
  tab_method = (char **)arg;
  free(tab_method);
  return (NULL);
}

void *fonction1(void *arg)
{
  printf("fonction 1\n");
  return (NULL);
}

void *fonction2(void *arg)
{
  printf("fonction 2\n");
  return (NULL);
}

