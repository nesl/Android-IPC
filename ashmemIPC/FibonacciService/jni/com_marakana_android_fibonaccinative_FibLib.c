/* Include the header file that was created via "javah -jni" command */
#include "com_marakana_android_fibonaccinative_FibLib.h"
#include <android/log.h>
#include <linux/stddef.h>
#include <errno.h>
#include <sys/mman.h>
#include <linux/types.h>
#include <linux/ashmem.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

//#include <android/include/system/core/include/cutils/ashmem.h>

/* Recursive implementation of the fibonacci algorithm (in a helper function) */
static jlong fib(jlong n) {
    return n <= 0 ? 0 : n == 1 ? 1 : fib(n - 1) + fib(n - 2);
}

/* Actual implementation of JNI-defined `fibNR` (recursive) function */
JNIEXPORT jlong JNICALL Java_com_marakana_android_fibonaccinative_FibLib_fibNR
  (JNIEnv *env, jclass clazz, jlong n) {
	__android_log_print(ANDROID_LOG_DEBUG, "FibLib.c", "fibNR(%lld)", n);
	return fib(n);
}

/* Actual implementation of JNI-defined `fibNI` (iterative) function */
JNIEXPORT jlong JNICALL Java_com_marakana_android_fibonaccinative_FibLib_fibNI
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

static int offset = 0;
int fd;
char *buff;
char data[1001];
ssize_t bytes;
JNIEXPORT jint JNICALL Java_com_marakana_android_fibonaccinative_FibLib_getTestFD
/* int Test.getTestFD() */
 (JNIEnv * env, jclass jthis) {

	/*int dd;
	ssize_t bytes;
	dd = open("/sdcard/acc_data.json",O_RDWR);
	if(dd != -1)
	{
		__android_log_print(ANDROID_LOG_DEBUG, "FibLib.c", "Read from file with descr as %d", dd);
		bytes = read(dd,data,1000);
		int off = close(dd);
		if(bytes == -1)
		{
			__android_log_print(ANDROID_LOG_DEBUG, "FibLib.c", "Oh dear, something went wrong with read()! %s\n", strerror(errno));
		}
	}*/
	__android_log_print(ANDROID_LOG_DEBUG, "FibLib.c", "Read from file the data as %s, size is %d", data, bytes);

    fd = open("/dev/ashmem", O_RDWR); // I couldn't find library with ashmem_create_region
    __android_log_print(ANDROID_LOG_DEBUG, "FibLib.c", "created mem file in NDK with fd as %d", fd);

    ioctl(fd, ASHMEM_SET_NAME, "my_mem");
    ioctl(fd, ASHMEM_SET_SIZE, 640*480*12);
    buff = mmap(NULL, 640*480*12, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(buff == MAP_FAILED)
    {
    	__android_log_print(ANDROID_LOG_DEBUG, "FibLib.c", "buff is not valid");
    	return -1;
    }

    memcpy (buff, data, bytes);
    //offset = offset + bytes;
    return fd;
  }

JNIEXPORT jint JNICALL Java_com_marakana_android_fibonaccinative_FibLib_writeToFD
/* int Test.getTestFD() */
 (JNIEnv * env, jclass jthis) {

	/*int dd;
	ssize_t bytes;
	dd = open("/sdcard/acc_data.json",O_RDWR);
	if(dd != -1)
	{
		__android_log_print(ANDROID_LOG_DEBUG, "FibLib.c", "Read from file with descr as %d", dd);
		lseek(dd, offset,SEEK_CUR);
		bytes = read(dd,data,1000);
		int off = close(dd);
		if(bytes == -1)
		{
			__android_log_print(ANDROID_LOG_DEBUG, "FibLib.c", "Oh dear, something went wrong with read()! %s\n", strerror(errno));
		}
	}*/
	__android_log_print(ANDROID_LOG_DEBUG, "FibLib.c", "Read from file the data as %s, size is %d", data, bytes);

    memcpy (buff, data, bytes);
    //offset = offset + bytes;
    return 1;
  }

JNIEXPORT jint JNICALL Java_com_marakana_android_fibonaccinative_FibLib_CloseFD
/* int Test.getTestFD() */
 (JNIEnv * env, jclass jthis) {
	if (munmap(buff, 640*480*12) == -1) {
		__android_log_print(ANDROID_LOG_DEBUG, "FibLib.c", "Unmapping the file failed");
		/* Decide here whether to close(fd) and exit() or not. Depends... */
	    }
	int a = close(fd);
    return 1;
  }

JNIEXPORT jint JNICALL Java_com_marakana_android_fibonaccinative_FibLib_CreateDataFD
/* int Test.getTestFD() */
 (JNIEnv * env, jclass jthis, jbyteArray sense_data, jint length) {

	char * p = (char *) (*env)->GetByteArrayElements( env, sense_data, NULL);
	__android_log_print(ANDROID_LOG_DEBUG, "FibLib.c", "Data received from service is --- %s", p);

	memcpy (data, p, length);
	bytes = length;
	(*env)->ReleaseByteArrayElements( env, sense_data, (char *) p, 0);
	return 1;
  }
