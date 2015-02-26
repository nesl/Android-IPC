package edu.ucla.nesl.android.ashmem.datasender;

import java.nio.ByteBuffer;

import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import edu.ucla.nesl.android.ashmem.datasender.nativelib.NativeLib;

public class MainActivity extends ActionBarActivity {
	private static final String TAG = "AshmemDataSender: MainActivity";
	private static float count = 0;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		
		Button button1 = (Button)findViewById(R.id.button1);
        button1.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				Log.i(TAG, "createFD clicked");
				NativeLib.createFD();
			}        	
        });
        
        
        Button button2 = (Button)findViewById(R.id.button2);
        button2.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				Log.i(TAG, "writeFD clicked");
				byte[] data = ByteBuffer.allocate(4).putFloat(count++).array();
				NativeLib.writeToFD(data, 4);
			}
        });
        
        Button button3 = (Button)findViewById(R.id.button3);
        button3.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				Log.i(TAG, "closeFD clicked");
				NativeLib.closeFD();
			}
        });
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			return true;
		}
		return super.onOptionsItemSelected(item);
	}
}
