#include "edu_ucla_nesl_android_ashmem_datasender_nativelib_NativeLib.h"
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

#define BUF_SIZE 100

int fd = -1;
char *buffer;

/*
 * Class:     edu_ucla_nesl_android_datasender_nativelib_NativeLib
 * Method:    getFD
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_edu_ucla_nesl_android_datasender_nativelib_NativeLib_getFD
  (JNIEnv *env, jclass class) {
	return fd;
}

/*
 * Class:     edu_ucla_nesl_android_datasender_nativelib_NativeLib
 * Method:    writeToFD
 * Signature: ([BI)I
 */
JNIEXPORT jint JNICALL Java_edu_ucla_nesl_android_datasender_nativelib_NativeLib_writeToFD
  (JNIEnv *env, jclass class, jbyteArray data, jint length) {
	char *p = (char *) (*env)->GetByteArrayElements( env, data, NULL);
	__android_log_print(ANDROID_LOG_DEBUG, "FibLib.c", "Data received from service is --- %s", p);

	memcpy (data, p, length);
	(*env)->ReleaseByteArrayElements(env, data, (char *)p, 0);

	memcpy (buffer, data, length);

	return 0;
}

/*
 * Class:     edu_ucla_nesl_android_datasender_nativelib_NativeLib
 * Method:    closeFD
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_edu_ucla_nesl_android_datasender_nativelib_NativeLib_closeFD
  (JNIEnv *env, jclass class) {
	if (munmap(buffer, BUF_SIZE) == -1) {
		__android_log_print(ANDROID_LOG_DEBUG, "FibLib.c", "Unmapping the file failed");
		close(fd);
		return -1;
	}
	close(fd);
    return 0;
}

/*
 * Class:     edu_ucla_nesl_android_datasender_nativelib_NativeLib
 * Method:    createFD
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_edu_ucla_nesl_android_datasender_nativelib_NativeLib_createFD
  (JNIEnv *env, jclass class) {
	__android_log_print(ANDROID_LOG_DEBUG, "NativeLib", "In createFD");

	fd = open("/dev/ashmem", O_RDWR);
	ioctl(fd, ASHMEM_SET_NAME, "data_mem");
	ioctl(fd, ASHMEM_SET_SIZE, BUF_SIZE);

//	fd = ashmem_create_region("my_mem", BUF_SIZE);
	__android_log_print(ANDROID_LOG_DEBUG, "NativeLib", "created ashmem file in NDK with fd as %d", fd);
	buffer = mmap(NULL, BUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(buffer == MAP_FAILED)
	{
		__android_log_print(ANDROID_LOG_DEBUG, "FibLib.c", "buff is not valid");
		return -1;
	}

	return fd;
}
