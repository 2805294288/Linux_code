1 #include<stdio.h>
  2 #include<unistd.h>
  3 #include<string.h>
  4 #include<sys/wait.h>
  5 #include<stdlib.h>
  6 
  7 #define SIZE 128
  8                                                                                                                                                          
  9 int main()
 10 {
 11   while(1) //注释1
 12   {
 13     printf("[myshell@VM-8-16-centos shell]$ ");//注释2
 14     char str[SIZE]={0};
 15 
 16     fgets(str,SIZE,stdin); //注释3
 17     str[strlen(str)-1]='\0'; //注释4
 18 
 19     char *arg[SIZE]={0};
 20 
 21     arg[0]=strtok(str," "); //注释5
 22 
 23     int i=1;
 24 
 25     do //注释6
 26     {
 27       arg[i]=strtok(NULL," ");
 28       if(!arg[i])
 29       {
 30				break;
 31       }
 32     i++;
 33     }while(1);
 34 
 35     pid_t id=fork();//注释7
 36     if(id<0)
 37     {
 38       perror("fork error!");
 39     }
 40     if(id==0)
 41     {
 42       execvp(arg[0],arg);//注释8
 43 
 44       printf("comman not error!");
 45       exit(1);
 46     }
 47 
 48     int st;
 49     waitpid(id,&st,0);//注释9
 50 
 51     printf("state is:%d \n",(st>>8)&0xff);//注释10                                                                                                               
 52   }
 53 
 54   return 0;
 55 }