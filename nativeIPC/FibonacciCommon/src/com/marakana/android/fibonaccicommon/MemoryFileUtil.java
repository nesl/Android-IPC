package com.marakana.android.fibonaccicommon;

import java.io.FileDescriptor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import android.os.MemoryFile;

public class MemoryFileUtil {
	private static final Method sMethodGetFileDescriptor;
    static {
        sMethodGetFileDescriptor = get("getFileDescriptor");
    }

    public static FileDescriptor getFileDescriptor(MemoryFile file) {
        try {
            return (FileDescriptor) sMethodGetFileDescriptor.invoke(file);
        } catch (IllegalAccessException e) {
            throw new RuntimeException(e);
        } catch (InvocationTargetException e) {
            throw new RuntimeException(e);
        }
    }

    private static Method get(String name) {
        try {
            return MemoryFile.class.getDeclaredMethod(name);
        } catch (NoSuchMethodException e) {
            throw new RuntimeException(e);
        }
    }
}
