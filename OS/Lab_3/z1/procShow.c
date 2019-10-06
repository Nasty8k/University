#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

int main(int argc, char *argv[]){
       
    int ch = ' ';
    FILE *file;
    struct dirent *pDirent;
    DIR *pDir = opendir("/proc");
    
    while((pDirent = readdir(pDir)) != NULL) {
        if ((pDirent->d_name[0] < '9') && (pDirent->d_name[0] != '.')) {
            char str[64] = "/proc/";
            strcat(str, pDirent->d_name);
            strcat(str, "/stat\0");
            file = fopen(str, "r");
            printf("[%s] ", pDirent->d_name);
            
            while (!feof(file) && !ferror(file)) {
                while (ch != '(') ch = getc(file);
                while ( (ch = getc(file)) != ')') putchar(ch);
                break;
            }
            fclose(file);
            putchar('\n');        
        }
    }
    closedir(pDir);
    return 0;
}
