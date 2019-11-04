#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE 25

int main(int argc,char* argv[]){
    
    char write_msg[BUFFER_SIZE];
    char read_msg[BUFFER_SIZE];
    strcpy(write_msg, argv[1]);
    
    char write_msg2[BUFFER_SIZE];
    char read_msg2[BUFFER_SIZE];
    
    char write_msg3[BUFFER_SIZE];
    char read_msg3[BUFFER_SIZE];
    
    
    
    srand ( time(NULL) );
    int num = rand() % 10;
    char snum = num + '0';
    
    srand ( time(NULL) );
    int n1 = rand() % strlen(write_msg);
    int n2 = rand() % strlen(write_msg);
    
    
    pid_t pid;
    int fd[2];
    
    /* create the pipe */
    if (pipe(fd) == -1) {
        fprintf(stderr,"Pipe failed");
        return 1;
    }
    
    /* now fork a child process */
    pid = fork();
    
    if (pid < 0) {
        fprintf(stderr, "Fork failed");
        return 1;
    }
    
    if (pid > 0) {

    	/* parent process */
		
        /* write to the pipe */
        write(fd[1], write_msg, strlen(write_msg)+1);
        
        wait(NULL);
        pid=fork(); /* now fork a child process */
        wait(NULL);
        
        
        
    }
    else {

    	/* child process */
		/* read from the pipe */
        
        read(fd[0], read_msg, BUFFER_SIZE);
        printf("1st Child - Received string: '%s'\n",read_msg);
        
        write_msg[n1] = toupper(write_msg[n1]);
        strcpy(write_msg2, write_msg);
        /* write to the pipe */
        write(fd[1], write_msg2, strlen(write_msg2)+1);
        printf("1st Child - Sent string: '%s'\n",write_msg2);
        
        
        exit(0);
        
    }
    
    if(pid == 0){
        read(fd[0], read_msg2, BUFFER_SIZE);
        printf("2nd Child - Received string: '%s'\n",read_msg2);
        
        read_msg2[n2] = snum;
        strcpy(write_msg3, read_msg2);
        /* write to the pipe */
        write(fd[1], write_msg3, strlen(write_msg3)+1);
        printf("2nd Child - Sent string: '%s'\n",write_msg3);
        
        exit(1);
    }
    pid=fork(); /* now fork a child process */

    if(pid == 0){
        read(fd[0], read_msg3, BUFFER_SIZE);
        printf("3rd Child - Received string: '%s'\n",read_msg3);
        
        exit(2);
    }
}
