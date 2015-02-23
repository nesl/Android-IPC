package edu.ucla.nesl.android.datasender;

import android.app.Service;
import android.content.Intent;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Binder;
import android.os.IBinder;
import android.util.Log;

public class MainService extends Service implements SensorEventListener {
	public static final String TAG = "MainService";
	private final IBinder mBinder = new LocalBinder();
	private SensorManager mSensorManager;
	private Sensor mAcc;
	
	public class LocalBinder extends Binder {
		MainService getService() {
            return MainService.this;
        }
	}

	@Override
	public IBinder onBind(Intent intent) {
		return mBinder;
	}

	@Override
	public void onSensorChanged(SensorEvent event) {
		Log.i(TAG, "x=" + event.values[0]);
		Intent intent = new Intent();
		intent.setAction("android.intent.action.DATA");
		intent.putExtra("x", event.values[0]);
		intent.putExtra("y", event.values[1]);
		intent.putExtra("z", event.values[2]);
		sendBroadcast(intent);
	}

	@Override
	public void onAccuracyChanged(Sensor sensor, int accuracy) {
		
	}
	
	public void init() {
		Log.i(TAG, "init");
		mSensorManager = (SensorManager) getSystemService(SENSOR_SERVICE);
		mAcc = (Sensor) mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
	}
	
	public void start() {
		Log.i(TAG, "start");
		mSensorManager.registerListener(this, mAcc, SensorManager.SENSOR_DELAY_NORMAL);
	}
	
	public void stop() {
		Log.i(TAG, "stop");
		mSensorManager.unregisterListener(this);
	}

}
