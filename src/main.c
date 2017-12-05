#include <dlfcn.h>
#include <unistd.h>
#include <test.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_loader t_loader;
typedef struct s_object t_object;

struct s_loader
{
  void *handle;
  m_init_f init;
  char **tab_method;
};

struct s_object
{
  m_method_f syscall[255];
  void *data[255];
};

void init();
void destruct();

t_loader *loader;
t_object *object;

void exec(char *tab)
{
  int i ;

  i = -1;
  while(tab[++i] != -1)
    object->syscall[(int)tab[i]](loader->tab_method);
}

int main()
{
  char tab[8] = {2,1,2,1,2,1,0,-1};

  init();
  exec(tab);
  destruct();
  return (0);
}

void init()
{
  int i = -1;

  loader = (t_loader *)malloc(sizeof(t_loader));
  object = (t_object *)malloc(sizeof(t_object));
  if (!(loader->handle = dlopen("libtest.so", RTLD_LAZY)))
    {
      printf("An error occured: %s\n", dlerror ());
      exit(-1);
    }

  if (!(loader->init = dlsym(loader->handle, "m_init")))
    {
      printf("An error occured: %s\n", dlerror ());
      dlclose(loader->handle);
      destruct();
      exit(-1);
    }
  loader->tab_method = loader->init();
  memset(object->syscall, 0, sizeof(m_method_f));
  while (loader->tab_method[++i])
    {
      if (!(object->syscall[i] = dlsym(loader->handle, loader->tab_method[i])))
	{
	  printf("An error occured: %s\n", dlerror ());
	  dlclose(loader->handle);
	  destruct();
	  exit(-1);
	}
    }
  object->syscall[i] = NULL;
}

void destruct()
{
  dlclose(loader->handle);
  free(loader);
  free(object);
}
