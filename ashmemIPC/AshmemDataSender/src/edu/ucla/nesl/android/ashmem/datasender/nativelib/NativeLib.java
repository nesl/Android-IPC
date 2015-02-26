package edu.ucla.nesl.android.ashmem.datasender.nativelib;

public class NativeLib {
	public native static int getFD();
	
	public native static int writeToFD(byte[] data, int length);
	
	public native static int closeFD();
	
	public native static int createFD();
	
	static {
		System.loadLibrary("edu_ucla_nesl_android_ashmem_datasender_nativelib_NativeLib");
	}
}