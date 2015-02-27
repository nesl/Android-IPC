#include "edu_ucla_nesl_android_ashmem_datareceiver_nativelib_NativeLib.h"
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

int fd = -1;
char *buffer;

#define BUF_SIZE 100

/*
 * Class:     edu_ucla_nesl_android_ashmem_datareceiver_nativelib_NativeLib
 * Method:    setFD
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_edu_ucla_nesl_android_ashmem_datareceiver_nativelib_NativeLib_setFD
  (JNIEnv *env, jclass class, jint _fd) {
	fd = _fd;
	buffer = (char *)mmap(NULL, BUF_SIZE, PROT_READ, MAP_SHARED, fd, 0);
	if(buffer == MAP_FAILED)
	{
		__android_log_print(ANDROID_LOG_DEBUG, "Receiver NativeLib.h", "cannot mmap to fd: %d", fd);
		return -1;
	}
	__android_log_print(ANDROID_LOG_DEBUG, "Receiver NativeLib.h", "Data read is %s", buffer);
	return fd;
}

/*
 * Class:     edu_ucla_nesl_android_ashmem_datareceiver_nativelib_NativeLib
 * Method:    readFromFD
 * Signature: (I)[B
 */
JNIEXPORT jbyteArray JNICALL Java_edu_ucla_nesl_android_ashmem_datareceiver_nativelib_NativeLib_readFromFD
  (JNIEnv *env, jclass class, jint length) {
	__android_log_print(ANDROID_LOG_DEBUG, "Receiver NativeLib.h", "Data read is %s", buffer);
	jbyteArray ret = (*env)->NewByteArray(env, length);
	(*env)->SetByteArrayRegion(env, ret, 0, length, (jbyte *)buffer);
	return ret;
}

/*
 * Class:     edu_ucla_nesl_android_ashmem_datareceiver_nativelib_NativeLib
 * Method:    closeFD
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_edu_ucla_nesl_android_ashmem_datareceiver_nativelib_NativeLib_closeFD
  (JNIEnv *env, jclass class) {
	if (munmap(buffer, BUF_SIZE) == -1) {
		__android_log_print(ANDROID_LOG_DEBUG, "Receiver NativeLib.c", "Unmapping the file failed");
		close(fd);
		return -1;
	}
	close(fd);
	return 0;
}
