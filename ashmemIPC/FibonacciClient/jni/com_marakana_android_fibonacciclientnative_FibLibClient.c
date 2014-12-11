/* Include the header file that was created via "javah -jni" command */
#include "com_marakana_android_fibonacciclientnative_FibLibClient.h"
#include <android/log.h>
//#include <linux/ashmem.h>
//#include <android/include/system/core/include/cutils/ashmem.h>
//#include <C:/Shubham/UCLA/ACADS/Eclipse_Android/NDK/android-ndk-r10c/platforms/android-17/arch-arm/usr/include/linux/stddef.h>
#include <linux/stddef.h>
#include <errno.h>
#include <sys/mman.h>
#include <linux/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>


/* Recursive implementation of the fibonacci algorithm (in a helper function) */
static jlong fib(jlong n) {
    return n <= 0 ? 0 : n == 1 ? 1 : fib(n - 1) + fib(n - 2);
}

/* Actual implementation of JNI-defined `fibNR` (recursive) function */
JNIEXPORT jlong JNICALL Java_com_marakana_android_fibonacciclientnative_FibLibClient_fibNR
  (JNIEnv *env, jclass clazz, jlong n) {
	__android_log_print(ANDROID_LOG_DEBUG, "FibLib.c", "fibNR(%lld)", n);
	return fib(n);
}

/* Actual implementation of JNI-defined `fibNI` (iterative) function */
JNIEXPORT jlong JNICALL Java_com_marakana_android_fibonacciclientnative_FibLibClient_fibNI
  (JNIEnv *env, jclass clazz, jlong n) {
	jlong previous = -1;
	jlong result = 1;
	jlong i;
	__android_log_print(ANDROID_LOG_DEBUG, "FibLib.c", "fibNI(%lld)", n);
	for (i = 0; i <= n; i++) {
		jlong sum = result + previous;
		previous = result;
		result = sum;
	}
	return result;
}


int data_fd = -1;
char * blah;
JNIEXPORT jint JNICALL Java_com_marakana_android_fibonacciclientnative_FibLibClient_SetDataFD
/* int SetDataFD(int fd) */
(JNIEnv * env, jclass jthis, jint fd)
{
    data_fd = fd;
    blah = (char*)mmap(NULL, 1100, PROT_READ, MAP_SHARED, data_fd, 0);
    if(blah == MAP_FAILED)
    {
    	__android_log_print(ANDROID_LOG_DEBUG, "FibLib.c", "blah could not be created");
    	return errno;
    }

    __android_log_print(ANDROID_LOG_DEBUG, "FibLib.c", "Data read is %s", blah);
    return 0;
}

JNIEXPORT jint JNICALL Java_com_marakana_android_fibonacciclientnative_FibLibClient_ReadDataFD
/* int SetDataFD(int fd) */
(JNIEnv * env, jclass jthis)
{
    /*char * blah = (char*)mmap(NULL, 1100, PROT_READ, MAP_SHARED, data_fd, 0);
    if(blah == MAP_FAILED)
    {
    	__android_log_print(ANDROID_LOG_DEBUG, "FibLib.c", "blah could not be created");
    	return errno;
    }*/

    __android_log_print(ANDROID_LOG_DEBUG, "FibLib.c", "Data read is %s", blah);
    return 0;
}

JNIEXPORT jint JNICALL Java_com_marakana_android_fibonacciclientnative_FibLibClient_CloseFD
/* int SetDataFD(int fd) */
(JNIEnv * env, jclass jthis)
{
	int a = close(data_fd);
    return 0;
}

JNIEXPORT jbyteArray JNICALL Java_com_marakana_android_fibonacciclientnative_FibLibClient_GetStringFD
/* int SetDataFD(int fd) */
(JNIEnv * env, jclass jthis)
{
	jbyteArray ret = (*env)->NewByteArray(env, 1000);
	//__android_log_print(ANDROID_LOG_DEBUG, "FibLib.c", "Length of data is is ---  %d", strlen(blah));
	(*env)->SetByteArrayRegion(env, ret, 0, strlen(blah), (jbyte *)blah);
	/*__android_log_print(ANDROID_LOG_DEBUG, "FibLib.c", "Data sending to Activity is ---  %s", ret);

	char * p = (char *) (*env)->GetByteArrayElements( env, ret, NULL);

	__android_log_print(ANDROID_LOG_DEBUG, "FibLib.c", "Data before sending activity is ---- %s", p);

	(*env)->ReleaseByteArrayElements( env, ret, (char *) p, 0);
	*/
	return ret;
}
