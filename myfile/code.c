 #include<stdio.h>
   
  int main()
  {
     FILE *fp = fopen("log.txt","w");
     if(fp == NULL)
     {
       perror("fopen erroe!\n");
       return 1;
     }
 
    char ch='A';
     for(;ch<='Z';ch++)                                                                                                                                                 
     {
       fputc(ch,fp);
      }
    printf("\n");
 }
