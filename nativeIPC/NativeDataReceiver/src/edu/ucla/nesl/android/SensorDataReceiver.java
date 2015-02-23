package edu.ucla.nesl.android;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

public class SensorDataReceiver extends BroadcastReceiver {
	public final String TAG = "SensorDataReceiver";

	@Override
	public void onReceive(Context context, Intent intent) {
		Log.i(TAG, "Detected intent " + intent.getAction());
		if (intent.getAction().indexOf("DATA") >= 0) {
			float x = intent.getFloatExtra("x", 0.0f);
			float y = intent.getFloatExtra("y", 0.0f);
			float z = intent.getFloatExtra("z", 0.0f);
			Log.i(TAG, "data: x=" + x + ",y=" + y + ",z=" + z);
		}
	}
	
}