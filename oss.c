//#include "oss.h"


#define maxpro 18

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include <signal.h>
#include <sys/time.h>
#include <stdbool.h>
#include <semaphore.h>
#include <pthread.h>
#include <fcntl.h>           
#include <sys/stat.h>
#include <sys/sem.h>
#include <sys/msg.h> 
#include <math.h>
#include<sys/wait.h>


/* Page Table */
typedef struct {
	int frame;
	int dirtyBit;
	int address;
	int literacy;
	int isValid;
} PT;

/* Frame Table */
typedef struct {
	int occupied[256];
} FT;

/* Process Control Block */
typedef struct {
	int pid;
	int index;
	int cast;
	int ptIndex;
	PT pageTable[32];
} PCB;

int createSharedSeconds() {
	/*---------------------------------------
		Make seconds integer for clock
			in shared memory
	----------------------------------------*/
	// shmget returns an identifier in shmid
	int shmidS = shmget(678, sizeof(unsigned long int), 0666 | IPC_CREAT);

	// error check for shmget
	if (shmidS < 0) {
		perror("shmget error\n");
		exit(1);
	}

	// shmat to attach to shared memory
	char* paddrS = (char*)shmat(shmidS, NULL, 0);
	unsigned long int* seconds = (unsigned long int*)(paddrS);
	*seconds = 0;

	// detach from shared memory
	shmdt(seconds);

	return shmidS;
}

void editSharedSeconds(int increment) {
	/*---------------------------------------
		Edit seconds integer for clock
			in shared memory
	----------------------------------------*/
	// shmget returns an identifier in shmid
	int shmidS = shmget(678, sizeof(unsigned long int), 066);

	// error check for shmget
	if (shmidS < 0) {
		perror("shmget error\n");
		exit(1);
	}

	// shmat to attach to shared memory
	char* paddrS = (char*)shmat(shmidS, NULL, 0);
	unsigned long int* seconds = (unsigned long int*)(paddrS);
	*seconds += increment;

	// detach from shared memory
	shmdt(seconds);

}

int fetchSharedSeconds() {
	/*---------------------------------------
		Fetch seconds integer for clock
			in shared memory
	----------------------------------------*/
	// shmget returns an identifier in shmid
	int shmidS = shmget(678, sizeof(unsigned long int), 066);

	// error check for shmget
	if (shmidS < 0) {
		perror("shmget error\n");
		exit(1);
	}

	// shmat to attach to shared memory
	char* paddrS = (char*)shmat(shmidS, NULL, 0);
	unsigned long int* seconds;
	seconds = (unsigned long int*)(paddrS);
	//printf("The number of seconds is %d\n", *seconds);
	int secondsPass = *seconds;
	// detach from shared memory
	shmdt(seconds);

	return secondsPass;
}

int createSharedNanoSeconds() {
	/*---------------------------------------
	Make nano seconds integer for clock
		in shared memory
	----------------------------------------*/
	// shmget returns an identifier in shmid
	int shmidNS = shmget(789, sizeof(unsigned long int), 0666 | IPC_CREAT);

	// error check for shmget
	if (shmidNS < 0) {
		perror("shmget error\n");
		exit(1);
	}

	// shmat to attach to shared memory
	char* paddrNS = (char*)shmat(shmidNS, NULL, 0);
	unsigned long int* nanoSeconds = (unsigned long int*)(paddrNS);
	*nanoSeconds = 0;

	// detach from shared memory
	shmdt(nanoSeconds);

	return shmidNS;
}

void editSharedNanoSeconds(increment) {
	/*---------------------------------------
	Edit nano seconds integer for clock
		in shared memory
	----------------------------------------*/
	// shmget returns an identifier in shmid
	int shmidNS = shmget(789, sizeof(unsigned long int), 066);

	// error check for shmget
	if (shmidNS < 0) {
		perror("shmget error\n");
		exit(1);
	}

	// shmat to attach to shared memory
	char* paddrNS = (char*)shmat(shmidNS, NULL, 0);
	unsigned long int* nanoSeconds = (unsigned long int*)(paddrNS);
	*nanoSeconds += increment;

	// detach from shared memory
	shmdt(nanoSeconds);
}

unsigned long int fetchSharedNanoSeconds() {
	/*---------------------------------------
	Fetch nano seconds integer for clock
		in shared memory
	----------------------------------------*/
	// shmget returns an identifier in shmid
	int shmidNS = shmget(789, sizeof(unsigned long int), 066);

	// error check for shmget
	if (shmidNS < 0) {
		perror("shmget error\n");
		exit(1);
	}

	// shmat to attach to shared memory
	char* paddrNS = (char*)shmat(shmidNS, NULL, 0);
	unsigned long int* nanoSeconds;
	nanoSeconds = (unsigned long int*)(paddrNS);
	//printf("The number of nano-seconds is %d\n", *nanoSeconds);
	unsigned long int nanoSecondsPass = *nanoSeconds;

	// detach from shared memory
	shmdt(nanoSeconds);

	return nanoSecondsPass;
}

int createCurrentNOP() {
	/*---------------------------------------
		NOP integer in shared memory
	----------------------------------------*/
	// shmget returns an identifier in shmid
	int shmid = shmget(77789, 1024, 0666 | IPC_CREAT);

	// error check for shmget
	if (shmid < 0) {
		perror("shmget error\n");
		exit(1);
	}

	// shmat to attach to shared memory
	char* paddr = (char*)shmat(shmid, NULL, 0);
	int* pint = (int*)(paddr);
	*pint = 0;
	// detach from shared memory
	shmdt(paddr);
	shmdt(pint);

	return shmid;
}

void editCurrentNOP(int number) {
	/*---------------------------------------
	NOP integer in shared memory
----------------------------------------*/
// shmget returns an identifier in shmid
	int shmid = shmget(77789, 1024, 066);

	// error check for shmget
	if (shmid < 0) {
		perror("shmget error\n");
		exit(1);
	}

	// shmat to attach to shared memory
	char* paddr = (char*)shmat(shmid, NULL, 0);
	int* pint = (int*)(paddr);
	*pint += number;
	// detach from shared memory
	shmdt(paddr);
	shmdt(pint);

}

int fetchCurrentNOP() {
	/*---------------------------------------
	NOP integer in shared memory
----------------------------------------*/
// shmget returns an identifier in shmid
	int shmid = shmget(77789, 1024, 066);
	int number;
	// error check for shmget
	if (shmid < 0) {
		perror("shmget error\n");
		exit(1);
	}

	// shmat to attach to shared memory
	char* paddr = (char*)shmat(shmid, NULL, 0);
	int* pint = (int*)(paddr);
	number = *pint;
	// detach from shared memory
	shmdt(paddr);
	shmdt(pint);

	return number;
}


void  INThandler(int sig)
{
	int shmid = shmget(77789, 1024, 066);
	int shmidNS = shmget(789, sizeof(unsigned long int), 066);
	int sem = semget(8576, 1, 0666);
	int requestID = shmget(1337, 2 * sizeof(int), 066);
	int pcbArrayID = shmget(42096, 18 * sizeof(PCB), 066);
	
	shmctl(pcbArrayID, IPC_RMID, NULL);
	shmctl(requestID, IPC_RMID, NULL);
	signal(sig, SIG_IGN);
	shmctl(shmid, IPC_RMID, NULL);
	shmctl(shmidNS, IPC_RMID, NULL);

	if (semctl(sem, 0, IPC_RMID, 0) != 0) {
		fprintf(stderr, "Couldn't remove the semahpore!\n");
		exit(1);
	}

	printf("\nCtrl + C detected. Master process shutting down. Beep. Boop.\n");
	exit(0);

}

int makeSemaphore() {
	/* -----------------------------------------------
						SEMAPHORES
	-------------------------------------------------*/
	int sem = semget(8576, 1, IPC_CREAT | 0666);
	if (sem == -1) {
		perror("main: semget");
		exit(1);
	}
	/* use this to store return values of system calls.   */
	int rc;

	/* initialize the first semaphore in our set to '3'.  */
	rc = semctl(sem, 0, SETVAL, 1);
	if (rc == -1) {
		perror("main: semctl");
		exit(1);
	}

	return sem;
}

void semBegin() {
	/* Fetch semaphore */
	int sem = semget(8576, 1, 0666);
	if (sem == -1) {
		perror("main: semget");
		exit(1);
	}
	/* structure for semaphore operations.   */
	struct sembuf sem_op;

	/* wait on the semaphore, unless it's value is non-negative. */
	sem_op.sem_num = 0;
	sem_op.sem_op = -1;
	sem_op.sem_flg = 0;
	semop(sem, &sem_op, 1);
}

void semEnd() {
	/* Fetch semaphore */
	int sem = semget(8576, 1, 0666);
	if (sem == -1) {
		perror("main: semget");
		exit(1);
	}
	/* structure for semaphore operations.   */
	struct sembuf sem_op;
	/* finally, signal the semaphore - increase its value by one. */
	sem_op.sem_num = 0;
	sem_op.sem_op = 1;
	sem_op.sem_flg = 0;
	semop(sem, &sem_op, 1);
}

int createRequest() {
	/*---------------------------------------
	Set up shared memory array 
	----------------------------------------*/
	int* array;
	/* We gon shmget us some memory! Yeehaw! */
	int shmidAr2 = shmget(1337, 2 * sizeof(int), 0666 | IPC_CREAT);
	/* Check for errors */
	if (shmidAr2 < 0) {
		perror("shmget error\n");
		exit(1);
	}
	/* Attach our array to the shared memory */
	array = (int*)shmat(shmidAr2, NULL, 0);

	/* Set control array variables */
	array[0] = -1;
	array[1] = -1;
	

	/* Detach our array from shared memory */
	shmdt(array);
	/*-------------------------------------*/

	return shmidAr2;
}


int makeRequest(int index, int address) {
	/*---------------------------------------
	Set up shared memory array
	----------------------------------------*/
	int* array;
	/* We gon shmget us some memory! Yeehaw! */
	int shmidAr2 = shmget(1337, 2 * sizeof(int), 066);
	/* Check for errors */
	if (shmidAr2 < 0) {
		perror("shmget error\n");
		exit(1);
	}
	/* Attach our array to the shared memory */
	array = (int*)shmat(shmidAr2, NULL, 0);

	/* Set control array variables */
	array[0] = index;
	array[1] = address;


	/* Detach our array from shared memory */
	shmdt(array);
	/*-------------------------------------*/

	return shmidAr2;
}

int* checkRequest() {
	/*---------------------------------------
	Set up shared memory array
	----------------------------------------*/
	int* array;
	int returnValue[2];
	/* We gon shmget us some memory! Yeehaw! */
	int shmidAr2 = shmget(1337, 2 * sizeof(int), 066);
	/* Check for errors */
	if (shmidAr2 < 0) {
		perror("shmget error\n");
		exit(1);
	}
	/* Attach our array to the shared memory */
	array = (int*)shmat(shmidAr2, NULL, 0);

	returnValue[0] = array[0];
	returnValue[1] = array[1];

	/* Detach our array from shared memory */
	shmdt(array);
	/*-------------------------------------*/

	return returnValue;
}

void printMemLayout() {
	FILE* file;
	semBegin();
	file = fopen("log.txt", "a");
	unsigned long int nSec = fetchSharedNanoSeconds();
	fprintf(file, "Current memory layout at time 0:%d is:\n", nSec);
	fprintf(file, "         Occupied   RefByte   DirtyBit   Address\n");
	int i;
	for (i = 0; i < 255; i++)
		fprintf(file, "Frame %d: No         0         0   %d\n", i, 0);

	fclose(file);
	semEnd();
}

int createProcessControlTable() {
	PCB* pcbArray;
	/* We gon shmget us some memory! Yeehaw! */
	int shmidAr1 = shmget(42096, 18 * sizeof(PCB), 0666 | IPC_CREAT);
	/* Check for errors */
	if (shmidAr1 < 0) {
		perror("shmget error on PCBT\n");
		exit(1);
	}
	/* Attach shared memory */
	pcbArray = (PCB*)shmat(shmidAr1, NULL, 0);

	/* Instantiate PCBs with arbitrary data */
	int i;
	for (i = 0; i < 18; i++) {
		pcbArray[i].pid = -1;
		pcbArray[i].index = -1;
		pcbArray[i].cast = -1;
		int k;
		for (k = 0; k < 32; k++) {
			pcbArray[i].pageTable[k].address = -1;
			pcbArray[i].pageTable[k].frame = -1;
			pcbArray[i].pageTable[k].isValid = -1;
			pcbArray[i].pageTable[k].literacy = -1;
			pcbArray[i].pageTable[k].dirtyBit = -1;
		}
	}

	/* Detach from shared memory */
	shmdt(pcbArray);

	return shmidAr1;
}

void setPCB(int pid, int index, int cast, int address, int frame,
	int isValid, int literacy, int dirtyBit, int ptIndex, int init) {
	PCB* pcbArray;
	semBegin();
	/* We gon shmget us some memory! Yeehaw! */
	int shmidAr1 = shmget(42096, 18 * sizeof(PCB), 066);
	/* Check for errors */
	if (shmidAr1 < 0) {
		perror("shmget error on PCBT1\n");
		exit(1);
	}
	/* Attach shared memory */
	pcbArray = (PCB*)shmat(shmidAr1, NULL, 0);

	/* if init */
	if (init == 1) {
		int k;
		for (k = 0; k < 18; k++) {
			if (pcbArray[k].pid == -1) {
				pcbArray[k].pid = pid;
				break;
			}

		}
	}
	/* Instantiate PCBs with data */
	int i;
	
	for (i = 0; i < 18; i++) {
		if (pcbArray[i].pid == pid)
			break;
	}
	

	pcbArray[i].pid = pid;
	pcbArray[i].index = index;
	pcbArray[i].cast = cast;
	pcbArray[i].ptIndex = ptIndex;

	pcbArray[i].pageTable[ptIndex].address = address;
	if (init == 1)
	pcbArray[i].pageTable[ptIndex].frame = frame;
	if (init == 1)
		pcbArray[i].pageTable[ptIndex].isValid = isValid;
	pcbArray[i].pageTable[ptIndex].literacy = literacy;
	pcbArray[i].pageTable[ptIndex].dirtyBit = dirtyBit;

	if (init == 2) {
		pcbArray[i].pid = -1;
		pcbArray[i].index = -1;
		pcbArray[i].cast = -1;
		pcbArray[i].ptIndex = -1;
		
		int k;
		for (k = 0; k < 32; k++) {
			pcbArray[i].pageTable[k].address = -1;
			pcbArray[i].pageTable[k].frame = -1;
			pcbArray[i].pageTable[k].isValid = -1;
			pcbArray[i].pageTable[k].literacy = -1;
			pcbArray[i].pageTable[k].dirtyBit = -1;
		}
	}
	/* Detach from shared memory */
	shmdt(pcbArray);
	semEnd();
}

int checkCast(int pid, int ptIndex) {
	PCB* pcbArray;
	semBegin();
	/* We gon shmget us some memory! Yeehaw! */
	int shmidAr1 = shmget(42096, 18 * sizeof(PCB), 066);
	/* Check for errors */
	if (shmidAr1 < 0) {
		perror("shmget error on PCBT1\n");
		exit(1);
	}
	/* Attach shared memory */
	pcbArray = (PCB*)shmat(shmidAr1, NULL, 0);

	
	int i;
	int rValue;

	for (i = 0; i < 18; i++) {
		if (pcbArray[i].pid == pid)
			break;
	}
	if (pcbArray[i].cast == 0) {
		pcbArray[i].cast = -1;
		rValue = 1;
	}
	else {
		rValue = 0;
	}

	/* Detach from shared memory */
	shmdt(pcbArray);
	semEnd();
	return rValue;
}


/*----------------------------------------
			FUNCTION PROTOTYPES
----------------------------------------*/
void forkOneProcess();


/*----------------------------------------
				GLOBALS
----------------------------------------*/  
int currentNOP = 0; //Number of Processes that exist now
int maxCurrentNOP = maxpro; //Maximum Simultaneous Number Of Processes
int totalNOP = 0; //How many processes exist cumulative
int maxTotalNOP = 10; //Total processes we will create
int memoryAccessType = 0;
FILE* file;
int ft[256];

int main(int argc, char* argv[]) {
	/* OPTIONS */
	int options;
	while ((options = getopt(argc, argv, "hm:")) != -1) {
		 
		switch (options) {
		case 'h':
			
			
			printf("OPTIONS:\n");
			printf("-h Describe how the project should be run, options, and then terminate.\n");
			printf("-m x Specify memory access type, 0 for simple, 1 for weighted : (0 by default)\n");
			exit(0);
		case 'm':	
			if (atoi(optarg) == 0 || atoi(optarg) == 1)
			memoryAccessType = atoi(optarg);
			break;	
		default:
			exit(0);
		}
	}
	/* Create/wipe log file */
	file = fopen("log.txt", "w");
	fclose(file);

	/* Ctrl + C signal handler */
	signal(SIGINT, INThandler);

	int m;
	for (m = 0; m < 256; m++) {
		ft[m] = 0;
	}

	/* Make semaphore */
	int sem = makeSemaphore();

	/*---------------Create PCT------------------*/
	int pcbArrayID = createProcessControlTable();

	/* Create shared nano seconds */
	int sharedNanoID = createSharedNanoSeconds();

	/* Create current NOP ID */
	int currentNOPID = createCurrentNOP();

	/* Create request */
	int requestID = createRequest();

	/* init */
	remplir();
	 
	/*---------------------------------
					loop
	---------------------------------*/
	unsigned long int timeToCreate = 0;
	 
	int times = 1;
	srand(getpid());
	while (1) {
		 
		/* check request */
		 
		processRequests(ft);
		
		/* Increment the nanoseconds */
		semBegin();
		editSharedNanoSeconds(1000000);
		semEnd();

		/* Get shared nanoseconds */
		unsigned long int currentNanos = fetchSharedNanoSeconds();

		currentNOP = fetchCurrentNOP();
		if (currentNOP < 18) {
			if (totalNOP < maxTotalNOP) {


				/* If nanos are greater than threshold, activate forking! */
				if (currentNanos >= (timeToCreate)) {
					timeToCreate = fetchSharedNanoSeconds();
					timeToCreate += (rand() % (500000000 - 1000000 + 1)) + 1000000;
					forkOneProcess();
					editCurrentNOP(1);
					totalNOP++;
					times++;

				}
			}
		}
		else
		{		
			while (wait(NULL) > 0) {

			}		
		}
		if (totalNOP >= maxTotalNOP) {
			if (currentNOP == 0)
				break;
		}
	}
	
	/* "Wait" for all remaining user processes to terminate */
	int k;
	int* check;
	for (k = 0; k < 99; k++) {
		check = checkRequest();
		wait(NULL);
	}
	if (check[0] != -1) {
		printf("P%d requested %d\n", *check, *(check + 1));
	}
	printMemLayout();
	/*----------------------------------*/
	/* Remove shared memory */
	shmctl(sharedNanoID, IPC_RMID, NULL);
	shmctl(pcbArrayID, IPC_RMID, NULL);
	shmctl(currentNOPID, IPC_RMID, NULL);
	shmctl(requestID, IPC_RMID, NULL);
	if (semctl(sem, 0, IPC_RMID, 0) != 0) {
		fprintf(stderr, "Couldn't remove the semahpore!\n");
		exit(1);
	}

	return 0;
}

void forkOneProcess() {
	//printf("Current # of processes are %d\n", currentNOP);
	int pid = fork();
	if (pid != 0) {
	
	}
	if (pid < 0) {
		//printf("reforking\n");
		wait(NULL);
		int pid = fork();
		if (pid < 0) {
			perror("There was a forking error.\n");
			printf("Current processes %d\n", currentNOP);
			printf("Total processes %d\n", totalNOP);
			int shmid = shmget(77789, 1024, 066);		
			int shmidNS = shmget(789, sizeof(unsigned long int), 066);
			int requestID = shmget(1337, 2 * sizeof(int), 066);
			int pcbArrayID = shmget(42096, 18 * sizeof(PCB), 066);
			shmctl(shmid, IPC_RMID, NULL);	
			shmctl(pcbArrayID, IPC_RMID, NULL);
			shmctl(shmidNS, IPC_RMID, NULL);
			shmctl(requestID, IPC_RMID, NULL);
			exit(1);
		} 
		else if (pid == 0) {
			char* command = "./user";
			char isRealPass[32];
			snprintf(isRealPass, sizeof(isRealPass), "%d", totalNOP);
			char isSchemePass[32];
			snprintf(isSchemePass, sizeof(isSchemePass), "%d", memoryAccessType);

			int value = execlp(command, isRealPass, isSchemePass, (char*)NULL);
			if (value < 0) {
				perror("Error with exec().\n");
				exit(1);
			}
		}
	}   
	else if (pid == 0) {
		//printf("goodbye, cruel world\n");

		char* command = "./user";
		char isRealPass[32];
		snprintf(isRealPass, sizeof(isRealPass), "%d", totalNOP);
		char isSchemePass[32];
		snprintf(isSchemePass, sizeof(isSchemePass), "%d", memoryAccessType);

		int value = execlp(command, isRealPass, isSchemePass, (char*)NULL);
		if (value < 0) {
			perror("Error with exec().\n");
			exit(1);
		}
	}
}

void remplir() {
	
		
} 


void processRequests() {
	PCB* pcbArray;
	unsigned long int nanos;
	semBegin();
	FILE* file;
	file = fopen("log.txt", "a");
	/* We gon shmget us some memory! Yeehaw! */
	int shmidAr1 = shmget(42096, 18 * sizeof(PCB), 066);
	/* Check for errors */
	if (shmidAr1 < 0) {
		perror("shmget error on PCBT2\n");
		exit(1);
	}
	/* Attach shared memory */
	pcbArray = (PCB*)shmat(shmidAr1, NULL, 0);

	int i;

	for (i = 0; i < 18; i++) {
		if (pcbArray[i].cast > -1) {
			//found request
			/* set some variables */
			int index = pcbArray[i].index;
			int ptIndex = pcbArray[i].ptIndex;
			int address = pcbArray[i].pageTable[ptIndex].address;
			int literacy = pcbArray[i].pageTable[ptIndex].literacy;
			int isValid = pcbArray[i].pageTable[ptIndex].isValid;
			int frame = pcbArray[i].pageTable[ptIndex].frame;

			if (literacy == 0) {
				nanos = fetchSharedNanoSeconds();
				fprintf(file, "P%d requesting read of address %d at time 0:%d\n",
					index, address, nanos);
			}
			else {
				nanos = fetchSharedNanoSeconds();
				fprintf(file, "P%d requesting write of address %d at time 0:%d\n",
					index, address, nanos);
			}
			if (isValid == 1) {
				nanos = fetchSharedNanoSeconds();
				fprintf(file, "Address %d in frame %d, giving data to P%d at time 0:%d\n",
					address, frame, index, nanos);
			}
			else {
				fprintf(file, "Address %d is not in a frame, pagefault\n", address);
				/* check for free memory */
				int m;
				bool freeMem = false;
				for (m = 0; m < 256; m++) {
					if (ft[m] == 0) {
						freeMem = true;
						break;
					} 
				}
				if (freeMem == true) {
					/* we found mem */
					fprintf(file, "Frame %d clear, assigning to P%d page %d\n",
						m, index, ptIndex);
					//fprintf(file, "im m %d\n", m);
					ft[m] = 1;
					if (literacy == 1) {
						fprintf(file, "Indicating to P%d that write has happened to address %d\n",
							index, address);
					}
					else {
						nanos = fetchSharedNanoSeconds();
						fprintf(file, "Address %d in frame %d, giving data to P%d at time 0:%d\n",
							address, m, index, nanos);
					}
					//fprintf(file, "im m2 %d\n", m);
					pcbArray[i].pageTable[ptIndex].frame = m;
					//fprintf(file, "just set frame %d, thats frame %d\n", m, pcbArray[i].pageTable[ptIndex].frame);
				}
				else {
					/* we didnt find mem */
					srand(pcbArray[i].pid);
					int r = (rand() % (256 - 0 + 1)) + 0;
					fprintf(file, "Clearing frame %d and swapping in P%d page %d\n",
						r, index, ptIndex);
					pcbArray[i].pageTable[ptIndex].frame = r;
					fprintf(file, "Dirty bit of frame %d set, adding additional time to the clock\n", r);
					pcbArray[i].pageTable[ptIndex].dirtyBit = 1;
					if (literacy == 1)
						fprintf(file, "Indicating to P%d that write has happened to address %d\n",
							index, address);
					else {
						nanos = fetchSharedNanoSeconds();
						fprintf(file, "Address %d in frame %d, giving data to P%d at time 0:%d\n",
							address, r, index, nanos);
					}

				}
				pcbArray[i].pageTable[ptIndex].isValid = 1;
			}
			pcbArray[i].cast = 0;
		}
	}


	/* Detach from shared memory */
	shmdt(pcbArray);
	fclose(file);
	semEnd();
}
