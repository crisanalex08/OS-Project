#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

struct stat sb;

void printRegularFileMenu()
{
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

void printSymbolicLinkMenu()
{
    printf("Symbolic Link Menu\n");
    printf("-n : Link name\n");
    printf("-l : Delete link\n");
    printf("-d : Size of the link\n");
    printf("-a : Access rights\n");
    printf("-e : Exit\n");
    printf("Enter your choice: ");
}

void printDirMenu(){
    printf("Symbolic Link Menu\n");
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
                break;

        }
        return 1;
    }
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
}

int regFileMenu(char *fileName){

    char choice[10];
    printRegularFileMenu();
    scanf("%s", &choice);
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
                printf("Acces rights: %o\n", sb.st_mode);//
                break;
            case 'l':
                char slinkName[100];
                printf("Enter the symbolic link name: ");
                scanf("%s", &slinkName);
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
    
    char choice[10];
    printSymbolicLinkMenu();
    scanf("%s", &choice);
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
                printf("Acces rights: %o\n", sb.st_mode);//
                break;
            case 'e':
                printf("Exiting...\n");
                exit(EXIT_SUCCESS);
                break;
        }
    }

}

int main(int arg, char* argv[])
{
    int c;
    int regFile = 0;
    int dir = 0;
    int link = 0;
    int badChoice = 0;
    int regMenu = 0;
    char choice[10];
    if(arg < 2)
    {
        printf("Usage:<filename> path1, path2, ...");
        exit(EXIT_FAILURE);
    }

    if (lstat(argv[1], &sb) == -1) {
        perror("lstat");
        exit(EXIT_FAILURE);
    }

    if(S_ISREG(sb.st_mode))
    {
        regFile = 1;
    }
    else if(S_ISLNK(sb.st_mode))
    {
        link = 1;
    }
    else
    {
        printf("Directory Menu\n");
        printDirMenu();
    }
    
    if(regFile){
        regMenu = regFileMenu(argv[1]);
        while(regMenu == -1){
            system("clear");
            printError("==========================\nInvalid choice, try again.\n==========================\n");
            regMenu = regFileMenu(argv[1]);
        }
    }else{
        if(dir == 0){
            link = linkMenu(argv[1]);
            while(link == -1){
            system("clear");
            printError("==========================\nInvalid choice, try again.\n==========================\n");
            link = linkMenu(argv[1]);
        }
        }else{
             while (strcmp(choice, "-e") || strcmp(choice, "e") || badChoice)
            {
                printf("Enter your choice: ");
                scanf("%s", &choice);

                for(int i = 1; i < strlen(choice); i++){
                    switch (choice[i])
                    {
                        case 'n':
                            printf("Link Name: %s\n", argv[1]);
                            break;
                        case 'd':
                            printf("Link Size: %ld\n", sb.st_size);
                            break;
                        case 'l':
                            printf("Deleting link\n");
                            if (unlink(argv[1]) == -1) {
                                perror("unlink");
                                exit(EXIT_FAILURE);
                            }
                            printf("Link deleted\n");
                            break;
                        case 'a':
                            printf("Acces rights: %o\n", sb.st_mode);//
                            break;
                        case 'e':
                            printf("Exiting...\n");
                            exit(EXIT_SUCCESS);
                            break;
                        default:
                            printf("Invalid choice: \"%c\"\n", choice[i]);
                            badChoice = 1;
                            break;
                    }
                }
            }
        }
    }
    return 0;
}
