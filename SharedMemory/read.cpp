#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
 
#define BUFSZ 4096
 
int main(int argc, char *argv[])
{   
    //创建key值
    ket_t key = ftok("../", 2015);
    if(key == -1)
    {
        perror("ftok");
    }
    
    system("ipcs -m"); //查看共享内存
    
    //打开共享内存
    int shmid = shmget(key, BUFSZ, IPC_CREAT|0666);
    if(shmid < 0)
    {
        perror("shmget");
        exit(-1);
    }
    
    //映射
    char *shmadd = shmat(shmid, NULL, 0);
    if(shmadd < 0)
    {
        perror("shmat");
        exit(-1);
    }
    
    //读共享内存区数据
    printf("data = [%s]\n", shmadd);
    
    //分离共享内存和当前进程
    int ret = shmdt(shmadd);
    if(ret < 0)
    {
        perror("shmdt");
        exit(1);
    }
    else
    {
        printf("deleted shared-memory\n");
    }
    
    //删除共享内存
    shmctl(shmid, IPC_RMID, NULL);
    //成功返回0，失败返回-1；
    
    system("ipcs -m"); //查看共享内存
    return 0;
}
