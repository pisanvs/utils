#include <stdio.h>

int main(int argc, char const *argv[]) {
    if (argc == 1 || argv[1][0] == '-') {
        // print stdin
        char c;
        while ((c = getchar()) != EOF) {
            putchar(c);
        }
        return 0;
    }
    
    for (int i = 1; i < argc; i++) {
        FILE *fp;
        int c;
        
        fp = fopen(argv[i],"r");
        if (fp == NULL) {
            printf("cat: %s: No such file or directory\n", argv[i]);
            continue;
        }
        while(1) {
            c = fgetc(fp);
            if( feof(fp) ) { 
                break;
            }
            printf("%c", c);
        }
        fclose(fp);
    }
    return 0;
}
