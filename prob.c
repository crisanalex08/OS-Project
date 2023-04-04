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
}

void printSymbolicLinkMenu()
{
    printf("-n : Link name\n");
    printf("-l : Delete link\n");
    printf("-d : Size of the link\n");
    printf("-a : Access rights\n");
    printf("-e : Exit\n");
}

void printDirMenu(){
    printf("-n : Dir name\n");
    printf("-c : Total number of files with \".c\" extension \n");
    printf("-d : Size of the dir\n");
    printf("-a : Access rights\n");
    printf("-e : Exit\n");
}

int checkRegularChoice(char *choice){
    for(int i = 0; i < strlen(choice)){
        if()

    }
}

int regFileMenu(char *fileName){

    int badChoice = 1;
    char choice[10];

    while (badChoice)
    {
            printRegularFileMenu();
            printf("Enter your choice: ");
            scanf("%s", &choice);

            for(int i = 1; i < strlen(choice); i++){
                switch (choice[i])
                {
                    case 'n':
                        printf("File Name: %s\n", fileName);
                        badChoice = 0;
                        break;
                    case 'd':
                        printf("File Size: %ld\n", sb.st_size);
                        badChoice = 0;
                        break;
                    case 'h':
                        printf("Number of Hard Links: %ld\n", sb.st_nlink);
                        badChoice = 0;
                        break;
                    case 'm':
                        printf("Time of last modification: %s\n", ctime(&(sb.st_mtime)));
                        badChoice = 0;
                        break;
                    case 'a':
                        printf("Acces rights: %o\n", sb.st_mode);//
                        badChoice = 0;
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
                    default:
                        printf("Invalid choice: \"%c\"\n", choice[i]);
                        badChoice = 1;
                        break;
                }
        }
    }
    return 0;
}

int main(int arg, char* argv[])
{
    int c;
    int regFile = 0;
    int dir = 0;
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
        printf("Symbolic Link Menu\n");
        printSymbolicLinkMenu();
    }
    else
    {
        printf("Directory Menu\n");
        printDirMenu();
    }
    
    if(regFile){
       regMenu = regFileMenu(argv[1]);
    }else{
        if(dir == 0){
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
