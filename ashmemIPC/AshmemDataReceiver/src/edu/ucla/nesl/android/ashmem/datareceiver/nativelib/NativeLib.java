package edu.ucla.nesl.android.ashmem.datareceiver.nativelib;

public class NativeLib {
	public native static int setFD(int fd);
	
	public native static byte[] readFromFD(int length);
	
	public native static int closeFD();
	
	static {
		System.loadLibrary("edu_ucla_nesl_android_ashmem_datareceiver_nativelib_NativeLib");
	}
}