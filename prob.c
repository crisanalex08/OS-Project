#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

void printRegularFileMenu()
{
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

int main(int arg, char* argv[])
{
    struct stat sb;
    int badChoice = 0;
    int regFile = 0;
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
        printf("Regular File Menu\n");
        printRegularFileMenu();
    }
    else if(S_ISLNK(sb.st_mode))
    {
        printf("Symbolic Link Menu\n");
        printSymbolicLinkMenu();
    }
    else
    {
        printf("Not a regular file or symbolic link\n");
    }
    
    if(regFile){
        while (strcmp(choice, "-e") || strcmp(choice, "e") || badChoice)
        {
            printf("Enter your choice: ");
            scanf("%s", &choice);

            for(int i = 1; i < strlen(choice); i++){
                switch (choice[i])
                {
                    case 'n':
                        printf("File Name: %s\n", argv[1]);
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
                        if (symlink(argv[1], slinkName) == -1) {
                            perror("symlink");
                            exit(EXIT_FAILURE);
                        }
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
    return 0;
}
