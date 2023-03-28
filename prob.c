#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

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
    printf("-l : Symbolic Link | give link name \n");
    printf("-a : Access rights\n");
    printf("-e : Exit\n");
}

int main(int arg, char* argv[])
{
    struct stat sb;
    char choice[2];
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
    
    
    while (strcmp(choice, "-e"))
    {
        printf("Enter your choice: ");
        scanf("%s", &choice);

        switch (choice[1])
        {
        case 'n':
            printf("%s", argv[1]);
            break;
        
        default:
            break;
        }
    }
    
    
    return 0;
}