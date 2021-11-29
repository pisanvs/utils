#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>

char *basedir = "~/code";

char* concat(const char *s1, const char *s2) {
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int xis_dir (const char *d) {
    DIR *dirptr;

    if (access ( d, F_OK ) != -1 ) {
        // file exists
        if ((dirptr = opendir (d)) != NULL) {
            closedir (dirptr); /* d exists and is a directory */
        } else {
            return -2; /* d exists but is not a directory */
        }
    } else {
        return -1;     /* d does not exist */
    }

    return 1;
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Creating new code project...\n");
        printf("Enter project name: ");
        char name[50];
        scanf("%s", name);
        printf("Enter short project description: ");
        char desc[100];
        scanf("%s", desc);

        printf("\nCreating project...\n");

        struct stat st;
        char *dirloc = "/media/DATA/EXTRA/Code/";
        
        dirloc = concat(dirloc, name);

        if (xis_dir(dirloc) == -1) {
            mkdir(dirloc, 7777);
            chdir(dirloc);
        } else {
            printf("Directory already exists.\n");
            return 0;
        }

        FILE *readme = fopen("README.md", "w");
        fprintf(readme, "## %s\n\n%s", name, desc);
        fclose(readme);

        system("git init");
        system("git add --all");
    } else {
        if (argc != 2) {
            printf("Usage: newp <project name>\n");
            return 0;
        }
        
        printf("Enter short project description: ");
        char desc[100];
        scanf("%s", desc);

        printf("\nCreating project...\n");

        struct stat st;
        char *dirloc = "/media/DATA/EXTRA/Code/";

        dirloc = concat(dirloc, argv[1]);

        if (xis_dir(dirloc) == -1) {
            mkdir(dirloc, 7777);
            chdir(dirloc);
        } else {
            printf("Directory already exists.\n");
            return 0;
        }

        FILE *readme = fopen("README.md", "w");
        fprintf(readme, "## %s\n\n%s", argv[1], desc);
        fclose(readme);

        system("git init");
        system("git add --all");
        
    }
}