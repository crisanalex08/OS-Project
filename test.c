// C program to demonstrate working of status
// from wait.
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
 int pid;
void waitexample()
{
    if((pid = fork()) < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if( pid == 0){
        //child code
        printf("Child regular\n");
        exit(0);
    }
    else{
    printf("PArent\n");
    //parent code
    }
}


 
// Driver code
int main()
{
    waitexample();
    return 0;
}