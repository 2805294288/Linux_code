#include"proc.h"

void proc()
{
  char bar[NUM];
  memset(bar,'\0',sizeof(bar));
  const char*label="|/-\\";

  int i=0;
  while(i<100)
  {
    bar[i++]='#';
    printf("[%-100s][%3d%%][%c]\r",bar,i,label[i%4]);
    fflush(stdout);
    usleep(30000);
  }
  printf("\n");
}
