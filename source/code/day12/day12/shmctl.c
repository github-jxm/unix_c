#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
	key_t key = ftok(".",100);
	int shmid = shmget(key,0,0);
	if(shmid == -1) perror("shmget"),exit(-1);
	struct shmid_ds ds;
	shmctl(shmid,IPC_STAT,&ds);//查询
	printf("size=%d\n",ds.shm_segsz);//大小
	printf("mode=%o\n",ds.shm_perm.mode);//权限
	printf("key=%x\n",ds.shm_perm.__key);
	ds.shm_segsz = 400;//修改，大小不能修改
	ds.shm_perm.mode = 0644;//能修改
	shmctl(shmid,IPC_SET,&ds);
	//shmctl(shmid,IPC_RMID,0);//删除
}

