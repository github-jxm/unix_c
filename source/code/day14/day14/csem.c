/*
 * filename : csem.c
 */

#include <stdio.h>
#include <errno.h>
#include <sys/sem.h>

int pmenu (void) {
	printf ("------------------\n");
	printf ("    迷你图书馆\n");
	printf ("------------------\n");
	printf ("[1] 借《三国演义》\n");
	printf ("[2] 还《三国演义》\n");
	printf ("[3] 借《水浒传》\n");
	printf ("[4] 还《水浒传》\n");
	printf ("[5] 借《红楼梦》\n");
	printf ("[6] 还《红楼梦》\n");
	printf ("[7] 借《西游记》\n");
	printf ("[8] 还《西游记》\n");
	printf ("[0] 退出\n");
	printf ("------------------\n");
	printf ("请选择：");
	int sel = -1;
	scanf ("%d", &sel);
	return sel;
}

int pleft (int semid, unsigned short semnum){
	int val = semctl (semid, semnum, GETVAL);
	if (val == -1) {
		perror ("semctl");
		return -1;
	}
	printf ("还剩%d册。\n", val);
	return 0;
}

int borrow (int semid, unsigned short semnum){
	struct sembuf sop = {semnum, -1,
		/*0*/IPC_NOWAIT};
	if (semop (semid, &sop, 1) == -1) {
		if (errno != EAGAIN) {
			perror ("semop");
			return -1;
		}
		printf ("暂时无书，下回再试。\n");
		return 0;
	}
	printf ("借阅成功。\n");
	return pleft (semid, semnum);
}
int revert (int semid, unsigned short semnum){
	struct sembuf sop = {semnum, 1, 0};
	if (semop (semid, &sop, 1) == -1) {
		perror ("semop");
		return -1;
	}
	printf ("归还成功。\n");
	return pleft (semid, semnum);
}
int main (void) {
	printf ("创建信号量...\n");
	key_t key = ftok (".", 100);
	if (key == -1) {
		perror ("ftok");
		return -1;
	}
	int semid = semget (key, 4, 0644 |
		IPC_CREAT | IPC_EXCL);
	if (semid == -1) {
		perror ("semget");
		return -1;
	}
	printf ("初始化信号量...\n");
	unsigned short semarr[] = {5, 5, 5, 5};
	if (semctl (semid, 0, SETALL,
		semarr) == -1) {
		perror ("semctl");
		return -1;
	}
	int quit = 0;
	while (! quit) {
		int sel = pmenu ();
		switch (sel) {
			case 0:
				quit = 1;
				break;
			case 1:
			case 3:
			case 5:
			case 7:
				if (borrow (semid, sel / 2) == -1)
					return -1;
				break;
			case 2:
			case 4:
			case 6:
			case 8:
				if (revert (semid, (sel-1)/2) == -1)
					return -1;
				break;
			default:
				printf ("无效选择！\n");
				scanf ("%*[^\n]");
				scanf ("%*c");
				break;
		}
	}
	printf ("销毁信号量...\n");
	if (semctl (semid, 0, IPC_RMID) == -1) {
		perror ("semctl");
		return -1;
	}
	printf ("再见！\n");
	return 0;
}
