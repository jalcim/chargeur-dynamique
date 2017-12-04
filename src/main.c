#include <dlfcn.h>
#include <unistd.h>
#include <test.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  void *handle;
  m_test_f method;

  char **tab_method;
  m_op_f operation[4];

  int i = -1;

  if (!(handle = dlopen("libtest.so", RTLD_LAZY)))
    {
      printf ("An error occured: %s\n", dlerror ());
      exit(-1);
    }

  if (!(method = dlsym(handle, "ft_test")))
    {
      printf ("An error occured: %s\n", dlerror ());
      dlclose (handle);
      exit (-1);
    }
  tab_method = method();

  while (tab_method[++i])
    {
      if (!(operation[i] = dlsym(handle, tab_method[i])))
	{
	  printf ("An error occured: %s\n", dlerror ());
	  dlclose (handle);
	  exit (-1);
	}
    }
  operation[i] = NULL;

  i = -1;

  while(operation[++i])
    {
      operation[i]((void *)tab_method);
      free(tab_method[i]);
    }
  free(tab_method);
  dlclose (handle);

  return (0);
}
