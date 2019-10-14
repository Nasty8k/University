#include <stdio.h>
#include <dlfcn.h>

int main(int argc, char **argv) {
    char *error;
    void *handle = dlopen("/lib64/libm.so.6",RTLD_LAZY); // хандлер внешней библиотеки
    if (!handle) { //если ошибка, то вывести ее на экран
		fprintf(stderr,"dlopen() error: %s\n", dlerror());
		return 1;
	};
	double(*cosine)(double) = dlsym(handle, "cos");// переменная для хранения адреса функции
	if ((error = dlerror()) != NULL) {
	   fprintf(stderr,"%s\n", error);
	   return 1;
    }
    printf("%f\n", (*cosine)(2.0));
    dlclose(handle);
    return 0;
}

/*https://www.opennet.ru/docs/RUS/glib_api/glib-Dynamic-Loading-of-Modules.html#id2619743*/ 
