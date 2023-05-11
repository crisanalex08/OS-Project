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

FILE *gradefile;

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
    printf("\033[0;31m"); //color code for red
    printf("%s", error);
    printf("\033[0;37m"); //color code for white
}

void accesRights(struct stat sb){
    printf("Access rights: ");
    printf( (S_ISDIR(sb.st_mode)) ? "d" : "-");
    printf(" User: \n");
    printf("\n");
    printf( (sb.st_mode & S_IRUSR) ? "Read - yes\n" : "Read - no\n");
    printf( (sb.st_mode & S_IWUSR) ? "Write - yes\n" : "Write - no\n");
    printf( (sb.st_mode & S_IXUSR) ? "Exec - yes\n" : "Write - no\n");
    
    printf("\n");
    printf(" Group: \n");
    printf("\n");
    
    printf( (sb.st_mode & S_IRGRP) ? "Read - yes\n" : "Read - no\n");
    printf( (sb.st_mode & S_IWGRP) ? "Write - yes\n" : "Write - no\n");
    printf( (sb.st_mode & S_IXGRP) ? "Exec - yes\n" : "Exec - no\n");

    printf("\n");
    printf(" Other: \n");
    printf("\n");

    printf( (sb.st_mode & S_IROTH) ? "Read - yes\n" : "Read - no\n");
    printf( (sb.st_mode & S_IWOTH) ? "Write - yes\n" : "Write - no\n");
    printf( (sb.st_mode & S_IXOTH) ? "Exec - yes\n" : "Exec - no\n");
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
    return 0; //fixing warnings
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
    printRegularFileMenu(); //print regular file menu
    // sleep(7);
    if((scanf("%s", choice)) == 0)
        printf("You need to enter a choice");

    while(validRegularChoice(choice) == 0){
        if(system("clear") == -1){
            printf("Clear failed\n");
        }
        printError("Invalid choice, try again\n");
        printRegularFileMenu();
        if((scanf("%s", choice)) == 0)
            printf("You need to enter a choice");
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
                if((scanf("%s", slinkName)) == 0)
                {
                    printf("I need a link name\n");
                }
                if (symlink(fileName, slinkName) == -1) { //check if the link was succsefully created
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
    printSymbolicLinkMenu(); //print link menu
    // sleep(7);
    if((scanf("%s", choice)) == 0)
        printf("You need to enter a choice");

    while(validLinkChoice(choice) == 0){
        if(system("clear") == -1){
            printf("Clear failed\n");
        }
        printError("Invalid choice, try again\n");
        printSymbolicLinkMenu();
        if((scanf("%s", choice)) == 0)
            printf("You need to enter a choice");
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
                if (unlink(linkName) == -1) { // check if the link was deleted succecfully
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
    if(ext != NULL && strcmp(ext, ".c") == 0){ // if file name contains
        return 1;
    }
    return 0;
}

int countCFiles(char *dirName){
    printf("Dir name: %s\n", dirName);
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
                if(isCFile(path) == 1){
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
    printDirMenu(); //print dir menu
    // sleep(7);
    if((scanf("%s", choice)) == 0)
        printf("You need to enter a choice");

    while(validDirectoryChoice(choice) == 0){
        if(system("clear") == -1){
            printf("Clear failed\n");
        }
        printError("Invalid choice, try again\n");
        printDirMenu();
        if((scanf("%s", choice)) == 0)
            printf("You need to enter a choice");
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

void printScore(char* filename, int errorNumber, int warningNumber){
    int score = 0;
    if(errorNumber == 0 && warningNumber == 0){
        score = 10;
    }

    if(errorNumber >= 1){
        score  = 1;
    }

    if(errorNumber == 0 && warningNumber >= 10){
        score = 2;
    }

    if(errorNumber == 0 && warningNumber >= 1 && warningNumber <= 9){
        score = 2 + 8 * (10 - warningNumber) / 10;
    }

    if(score){
        if((gradefile = fopen("grades.txt", "a+")) == NULL){
            printf("The file could not be opened\n");
            exit(EXIT_FAILURE);
        }else{
            fprintf(gradefile, "%s: %d\n", filename, score);

            if((fclose(gradefile)) == EOF){
                printf("The file could not be closed\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    else{
        printf("The score could not be computed\n");
        exit(EXIT_FAILURE);
    }
}

void processCFile(char* fileName, int pfd[2]){
    
}

void handleMenu(char* fileName){
    pid_t pid, pid2;
    int pfd[2];
    int fileType = getFileType(fileName);

    if((pipe(pfd) == -1)){
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    if((pid = fork()) == 0){
        if(pid == -1){
            perror("fork");
            exit(EXIT_FAILURE);
        }
        //child process
        switch (fileType)
        {
            case 1:
                regFileMenu(fileName);
                break;
            case 2:
                linkMenu(fileName);
                break;
            case 3:
                dirMenu(fileName);
                break;
            default:
                printError("Invalid file type\n");
                break;
        }
        exit(EXIT_SUCCESS);
    }
    else
    {
        if((pid2 = fork()) == 0){
            if(pid2 == -1){
                perror("fork");
                exit(EXIT_FAILURE);
            }
            //second child process
            switch (fileType)
            {
                case 1:
                    close(pfd[0]);
                    int newfd = dup2(pfd[1],STDOUT_FILENO); //1 - stdout
                    if(newfd < 0){
                        perror("Error while dup2-ing");
                        exit(1);
                    }
                    close(pfd[1]);
                    if( execlp("bash", "bash", "script5.sh", fileName, (char *)0) == -1){
                        perror("execlp");
                        exit(EXIT_FAILURE);
                    }
                    break;
                case 2:
                    execlp("chmod", "chmod", "760", fileName, (char *)0);
                    break;
                case 3:
                    char dirName[4096];
                            char dirPath[4096];
                            strcpy(dirName, fileName);
                            strcpy(dirPath, fileName);
                            strcat(dirName, "/");
                            strcat(dirPath, "_file.txt");
                            strcat(dirName, dirPath);
                            execlp("touch", "touch", dirName, (char *)0);
                            exit(0);
                    break;
            }
            exit(EXIT_SUCCESS);
        }
        else{
            //parent process
            if(pid2 == -1){
                perror("fork");
                exit(EXIT_FAILURE);
            }

            if (fileType == 1){
                if((close(pfd[1])) == -1){
                    perror("close");
                    exit(EXIT_FAILURE);
                }
                int switchToWarning = 0;
                int errorNumber = 0, warningNumber = 0;
                char buff[1];

                while((read(pfd[0], buff, 1)) > 0){
                    buff[1]='\0';
                    if(buff[0] != ' ' && switchToWarning == 0){
                        errorNumber = errorNumber * 10 + (buff[0] - '0');
                    }
                    if(buff[0] == ' '){
                        switchToWarning = 1;
                        continue;
                    }
                    if(buff[0] != ' ' && switchToWarning == 1){
                        if(buff[0] <= '9' && buff[0] >= '0'){
                            warningNumber = warningNumber * 10 + (buff[0] - '0');
                        }
                    }
                }
                printScore(fileName ,errorNumber, warningNumber);
            }
        }
    }
}

int main(int arg, char* argv[])
{
    int wstatus;

    if(arg < 2)
    {
        printf("Usage:<filename> path1, path2, ...");
        exit(EXIT_FAILURE);
    }
    
    for(int i = 1; i < arg; i++){
        handleMenu(argv[i]);
        sleep(7);
    }

    do {
            int w = wait(&wstatus);
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
