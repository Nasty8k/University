#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#define MAX_STRING  128

void API_method(char *lib, char *method, double x, double y) {
    void *dl_handle;
    double (*func)(double, double);
    char *error;

    dl_handle = dlopen( lib, RTLD_LAZY );
    if (!dl_handle) {
        printf( "!!! %s\n", dlerror() );
        return;
    }

    func = dlsym(dl_handle, method);    
    if ((error = dlerror()) != NULL) {
        printf( "!!! %s\n", error );
      return;
    }

    printf("%8c(%lf) %s (%lf) = %lf\n", ' ', x, method, y, (*func)(x, y));
    dlclose( dl_handle );
    return;
}

void help_show() {
    FILE *fp = fopen("help.txt", "r");
    char buf[MAX_STRING];
    while (!feof(fp)) {
        fgets(buf, MAX_STRING, fp);
        fputs(buf, stdout);
    }
    while (getc(stdin)!='\n');
    return;
}
 
int main(int argc, char **argv) {
    
    char line[MAX_STRING+1];
    char lib[MAX_STRING+1];
    char method[MAX_STRING+1];
    double x, y;
 
    if (argc == 1) {
        printf("Input path to lib: ");
        scanf("%s", lib);
        lib[strlen(lib)] = '\0';
        while (getc(stdin)!='\n');
    } else strcpy(lib, argv[1]);
    
    if (!(dlopen(lib, RTLD_LAZY )))
        printf("%s", dlerror());
    else 
    {
        while (1) {
            printf("Method: ");
            fgets( line, MAX_STRING, stdin);
            if (!strncmp(line, "help", 4)) {help_show(); continue;}
            if (!strncmp(line, "end", 3))  break;
            sscanf( line, "%lf %s %lf\n", &x, method, &y);
            API_method(lib, method, x, y);
        }
    }
}
