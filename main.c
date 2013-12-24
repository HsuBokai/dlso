#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(void) 
{
	const char* lib_path = "/home/meconin/bokai/dlso/lib/libtest.so";
	const char* fuc_name = "cos";
	double (*cosine)(double);   /* 指向 shared library 裡的函數 */


	/* 開啟 shared library 'libm' */
	void *handle = dlopen (lib_path, RTLD_LAZY);	/* shared library 的 'handle' 指標 */
	if (!handle) {
		fprintf (stderr, "%s\n", dlerror());
		exit(1);
	}
	dlerror();    /* Clear any existing error */

	/* 在 handle 指向的 shared library 裡找到 "cos" 函數,
	 * 並傳回他的 memory address 
	 */
	cosine = dlsym(handle, fuc_name);
	char *error;	/* 記錄 dynamic loader 的錯誤訊息 */
	if ((error = dlerror()) != NULL)  {
		fprintf (stderr, "%s\n", error);
		exit(1);
	}

	/* indirect function call (函數指標呼叫),
	 * 呼叫所指定的函數
	 */
	printf ("%f\n", (*cosine)(2.0));
	dlclose(handle);
	return 0;
}
