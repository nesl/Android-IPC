package edu.ucla.nesl.android.ashmem.datareceiver;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;
import edu.ucla.nesl.android.ashmem.datareceiver.nativelib.NativeLib;

public class SensorDataReceiver extends BroadcastReceiver {
	public final String TAG = "SensorDataReceiver";

	@Override
	public void onReceive(Context context, Intent intent) {
		Log.i(TAG, "Detected intent " + intent.getAction());
		if (intent.getAction().indexOf("DATA") >= 0) {
			byte[] data = NativeLib.readFromFD(4);
			float f = ByteBuffer.wrap(data).order(ByteOrder.LITTLE_ENDIAN).getFloat();
			Log.i(TAG, "Get data: " + f);
		}
		else if (intent.getAction().indexOf("FD") >= 0) {
			int fd = intent.getIntExtra("fd", 1);
			NativeLib.setFD(fd);
		}
	}
	
}