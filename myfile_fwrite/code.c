 1 #include<stdio.h>
  2 #include<string.h>
  3 
  4 int main()
  5 {
  6     FILE *fp = fopen("log.txt","w");
  7     if(fp == NULL)
  8     {
  9       perror("fopen erroe!\n");
 10       return 1;
 11     }
 12 
 13 
 14     const char *str = "Hello World!";
 15     fwrite(str,strlen(str),1,fp);                                                                                                                                      
 16    //  char ch='A';
 17    //  for(;ch<='Z';ch++)
 18    //  {
 19    //    fputc(ch,fp);
 20    //  }
 21 
 22     printf("\n");
 23 }
