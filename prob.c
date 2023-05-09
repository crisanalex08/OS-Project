#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>

struct stat sb;

int wait(int *wstatus);

int getFileType(char *fileName);

void printRegularFileMenu(){
    printf("Regular file menu\n");
    printf("-n : File Name\n");
    printf("-d : File Size\n");
    printf("-h : Number of Hard Links\n");
    printf("-m : Time of last modification\n");
    printf("-a : Access rights\n");
    printf("-l : Symbolic Link | give link name \n");
    printf("-e : Exit\n");
    printf("Enter your choice: ");
}

void printSymbolicLinkMenu(){
    printf("Symbolic Link Menu\n");
    printf("-n : Link name\n");
    printf("-l : Delete link\n");
    printf("-d : Size of the link\n");
    printf("-a : Access rights\n");
    printf("-e : Exit\n");
    printf("Enter your choice: ");
}

void printDirMenu(){
    printf("Directory Menu\n");
    printf("-n : Dir name\n");
    printf("-c : Total number of files with \".c\" extension \n");
    printf("-d : Size of the dir\n");
    printf("-a : Access rights\n");
    printf("-e : Exit\n");
    printf("Enter your choice: ");
}

void printError(char* error){
    printf("\033[0;31m");
    printf("%s", error);
    printf("\033[0;37m"); 
     
}

void accesRights(struct stat sb){
    printf("Access rights: ");
    printf( (S_ISDIR(sb.st_mode)) ? "d" : "-");
    printf( (sb.st_mode & S_IRUSR) ? "r" : "-");
    printf( (sb.st_mode & S_IWUSR) ? "w" : "-");
    printf( (sb.st_mode & S_IXUSR) ? "x" : "-");
    printf( (sb.st_mode & S_IRGRP) ? "r" : "-");
    printf( (sb.st_mode & S_IWGRP) ? "w" : "-");
    printf( (sb.st_mode & S_IXGRP) ? "x" : "-");
    printf( (sb.st_mode & S_IROTH) ? "r" : "-");
    printf( (sb.st_mode & S_IWOTH) ? "w" : "-");
    printf( (sb.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");
}

int validRegularChoice(char *choice){
    for(int i = 1; i < strlen(choice); i++){
        switch(choice[i]){
            case 'n':
                break;
            case 'd':
                break;
            case 'h':
                break;
            case 'm':
                break;
            case 'a':
                break;
            case 'l':
                break;
            case 'e':
                break;
            default:
                return 0;
        }
        return 1;
    }
    return 0;
}

int validLinkChoice(char *choice){
    for(int i = 1; i < strlen(choice); i++){
        switch(choice[i]){
            case 'n':
                break;
            case 'l':
                break;
            case 'd':
                break;
            case 'a':
                break;
            case 'e':
                break;
            default:
                return 0;
                break;

        }
        return 1;
    }
    return 0;
}

int validDirectoryChoice(char  *choice){
    for(int i = 1;i<strlen(choice);i++){
        switch(choice[i]){
            case 'n':
                break;
            case 'd':
                break;
            case 'a':
                break;
            case 'c':
                break;
            case 'e':
                break;
            default:
                return 0;
        }
        return 1;
    }
    return 0;
}

int regFileMenu(char *fileName){

    char choice[32];
    printRegularFileMenu();
    scanf("%s", choice);
    //printf("Child REgular File Menu\n");
    if(validRegularChoice(choice) == 0){
        printf("Invalid choice, try again\n");
        return -1;
    }
    for(int i = 1; i < strlen(choice); i++){
        switch (choice[i])
        {
            case 'n':
                printf("File Name: %s\n", fileName);
                break;
            case 'd':
                printf("File Size: %ld\n", sb.st_size);
                break;
            case 'h':
                printf("Number of Hard Links: %ld\n", sb.st_nlink);
                break;
            case 'm':
                printf("Time of last modification: %s\n", ctime(&(sb.st_mtime)));
                break;
            case 'a':
                accesRights(sb);
                break;
            case 'l':
                char slinkName[100];
                printf("Enter the symbolic link name: ");
                scanf("%s", slinkName);
                if (symlink(fileName, slinkName) == -1) {
                    perror("symlink");
                    exit(EXIT_FAILURE);
                }
                break;
            case 'e':
                printf("Exiting...\n");
                exit(EXIT_SUCCESS);
                break;
        }
    }
    return 0;
}

int linkMenu(char *linkName){
    
    char choice[32];
    printSymbolicLinkMenu();
    scanf("%s", choice);
    if(validLinkChoice(choice) == 0){
        printf("Invalid choice, try again\n");
        return -1;
    }
    for(int i = 1; i < strlen(choice); i++){
        switch (choice[i])
        {
            case 'n':
                printf("Link Name: %s\n", linkName);
                break;
            case 'd':
                printf("Link Size: %ld\n", sb.st_size);
                break;
            case 'l':
                printf("Deleting link\n");
                if (unlink(linkName) == -1) {
                    perror("unlink");
                    exit(EXIT_FAILURE);
                }
                printf("Link deleted\n");
                break;
            case 'a':
                accesRights(sb);
                break;
            case 'e':
                printf("Exiting...\n");
                exit(EXIT_SUCCESS);
                break;
        }
    }
    return 0;
}

int isCFile(char *fileName){
    char *ext = strrchr(fileName, '.');
    if(ext != NULL && strcmp(ext, ".c") == 0){
        return 1;
    }
    return 0;
}

int countCFiles(char *dirName){
    DIR *dir;
    struct dirent *ent;
    char path[4096];
    strcpy(path, dirName);
    strcat(path, "/");
    int count = 0;
    if ((dir = opendir (dirName)) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            if(strlen(ent->d_name) > 2){
                strcat(path, ent->d_name);
                if(getFileType(path) == 1){
                    char *ext = strrchr(ent->d_name, '.');
                    if(ext != NULL && strcmp(ext, ".c") == 0){
                        count++;
                    }
                }
            }
        }
        closedir (dir);
    } else {
        perror ("");
        return EXIT_FAILURE;
    }
    return count;
}

int getFileType(char *fileName){
    if (lstat(fileName, &sb) == -1) {
        perror("lstat");
        exit(EXIT_FAILURE);
    }
    if(S_ISREG(sb.st_mode)){
        return 1;
    }
    else if(S_ISLNK(sb.st_mode)){
        return 2;
    }
    else if(S_ISDIR(sb.st_mode)){
        return 3;
    }
    else{
        return 0;
    }
}

int dirMenu(char *dirName){

    char choice[32];
    printDirMenu();
    scanf("%s", choice);
    if(validDirectoryChoice(choice) == 0){
        return -1;
    }
    for(int i = 1; i < strlen(choice); i++){
        switch (choice[i])
        {
            case 'n':
                printf("Directory Name: %s\n", dirName);
                break;
            case 'd':
                printf("Directory Size: %ld\n", sb.st_size);
                break;
            case 'a':
                accesRights(sb);
                break;
            case 'c':
                printf("Number of files with \".c\" extension: %d\n", countCFiles(dirName));
                break;
            case 'e':
                printf("Exiting...\n");
                exit(EXIT_SUCCESS);
                break;
        }
    }
    return 0;

}
int main(int arg, char* argv[])
{
    int dir = 0;
    int link = 0;
    int regMenu = 0;

    int pid;
    int wstatus;

    if(arg < 2)
    {
        printf("Usage:<filename> path1, path2, ...");
        exit(EXIT_FAILURE);
    }
    
    for(int i = 1; i < arg; i++){
        if(getFileType(argv[i]) == 1){ //if the argument is a regular file
            if((pid = fork()) < 0){
                perror("fork");
                exit(EXIT_FAILURE);
            }

            if( pid == 0){
                //child code
                if(isCFile(argv[i]) == 1){
                    if((pid = fork()) < 0){
                        perror("fork");
                        exit(EXIT_FAILURE);
                    }
                    if( pid == 0){
                        execlp("bash", "bash", "script5.sh", argv[i]);
                        exit(0);
                    }
                }else{
                    regMenu = regFileMenu(argv[i]);
                    printf("%s\n",argv[i]);
                    while(regMenu == -1){
                        system("clear");
                        printError("==========================\nInvalid choice, try again.\n==========================\n");
                        regMenu = regFileMenu(argv[i]);
                    }
                }
                exit(0);
                
            }else{
            //parent code
            }
            sleep(7);
        }

        if(getFileType(argv[i]) == 2){//link
            if((pid = fork()) < 0){
                perror("fork");
                exit(EXIT_FAILURE);
            }
            if(pid == 0){
                //child code
                link = linkMenu(argv[i]);
                while(link == -1){
                    system("clear");
                    printError("==========================\nInvalid choice, try again.\n==========================\n");
                    link = linkMenu(argv[i]);
                }
                exit(0);
            }
            sleep(7);
        }

        if(getFileType(argv[i]) == 3){//directory
            if((pid = fork()) < 0){
                perror("fork");
                exit(EXIT_FAILURE);
            }
            if(pid == 0){
                dir = dirMenu(argv[i]);
                while(dir == -1){
                    system("clear");
                    printError("==========================\nInvalid choice, try again.\n==========================\n");
                    dir = dirMenu(argv[i]);
                }
                exit(0);
            }
            sleep(7);
        }

        if(getFileType(argv[i]) == 0){
            printError("Invalid file type\n");
        }
        
        // int w = wait(&wstatus);
        //            if (w == -1) {
        //                perror("waitpid");
        //                exit(EXIT_FAILURE);
        //            }

        //            if (WIFEXITED(wstatus)) {
        //                printf("exited, status=%d\n", WEXITSTATUS(wstatus));
        //            }
    }
    do {
       int w = waitpid(pid, &wstatus, WUNTRACED | WCONTINUED);
       if (w == -1) {
           perror("waitpid");
           exit(EXIT_FAILURE);
       }
       if (WIFEXITED(wstatus)) {
           printf("exited, status=%d\n", WEXITSTATUS(wstatus));
       } else if (WIFSIGNALED(wstatus)) {
           printf("killed by signal %d\n", WTERMSIG(wstatus));
       } else if (WIFSTOPPED(wstatus)) {
           printf("stopped by signal %d\n", WSTOPSIG(wstatus));
       } else if (WIFCONTINUED(wstatus)) {
           printf("continued\n");
       }
   } while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
   exit(EXIT_SUCCESS);
            
    return 0;
}
