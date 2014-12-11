package com.marakana.android.fibonacciclient;

import java.io.FileDescriptor;
import java.io.FileInputStream;
import java.io.IOException;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.IBinder;
import android.os.RemoteException;
import android.os.SystemClock;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RadioGroup;
import android.widget.TextView;
import android.widget.Toast;

import com.marakana.android.fibonaccicommon.FibonacciRequest;
import com.marakana.android.fibonaccicommon.FibonacciResponse;
import com.marakana.android.fibonaccicommon.IFibonacciService;

public class FibonacciActivity extends Activity implements OnClickListener,
		ServiceConnection {
	
	private void compareBuffers(byte[] buffer1, byte[] buffer2, int length) throws Exception {
        for (int i = 0; i < length; i++) {
            if (buffer1[i] != buffer2[i]) {
                throw new Exception("readBytes did not read back what writeBytes wrote");
            }
        }
        Log.d(TAG, String.format("The bytes match"));
	}

	private static final String TAG = "FibonacciActivity";

	private EditText input; // our input n

	private Button button; // trigger for fibonacci calcualtion

	private RadioGroup type; // fibonacci implementation type

	private TextView output; // destination for fibonacci result

	private IFibonacciService service; // reference to our service

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		super.setContentView(R.layout.main);
		// connect to our UI elements
		this.input = (EditText) super.findViewById(R.id.input);
		this.button = (Button) super.findViewById(R.id.button);
		this.type = (RadioGroup) super.findViewById(R.id.type);
		this.output = (TextView) super.findViewById(R.id.output);
		// request button click call-backs via onClick(View) method
		this.button.setOnClickListener(this);
		// the button will be enabled once we connect to the service
		this.button.setEnabled(false);
	}

	@Override
	protected void onResume() {
		Log.d(TAG, "onResume()'ed");
		super.onResume();
		// Bind to our FibonacciService service, by looking it up by its name
		// and passing ourselves as the ServiceConnection object
		// We'll get the actual IFibonacciService via a callback to
		// onServiceConnected() below
		if (!super.bindService(new Intent(IFibonacciService.class.getName()),
				this, BIND_AUTO_CREATE)) {
			Log.w(TAG, "Failed to bind to service");
		}
	}

	@Override
	protected void onPause() {
		Log.d(TAG, "onPause()'ed");
		super.onPause();
		// No need to keep the service bound (and alive) any longer than
		// necessary
		super.unbindService(this);
	}

	public void onServiceConnected(ComponentName name, IBinder service) {
		Log.d(TAG, "onServiceConnected()'ed to " + name);
		// finally we can get to our IFibonacciService
		this.service = IFibonacciService.Stub.asInterface(service);
		// enable the button, because the IFibonacciService is initialized
		this.button.setEnabled(true);
	}

	public void onServiceDisconnected(ComponentName name) {
		Log.d(TAG, "onServiceDisconnected()'ed to " + name);
		// our IFibonacciService service is no longer connected
		this.service = null;
		// disabled the button, since we cannot use IFibonacciService
		this.button.setEnabled(false);
	}

	// handle button clicks
	public void onClick(View view) {
		// parse n from input (or report errors)
		final long n;
		String s = this.input.getText().toString();
		if (TextUtils.isEmpty(s)) {
			return;
		}
		try {
			n = Long.parseLong(s);
		} catch (NumberFormatException e) {
			this.input.setError(super.getText(R.string.input_error));
			return;
		}

		// build the request object
		final FibonacciRequest.Type type;
		switch (FibonacciActivity.this.type.getCheckedRadioButtonId()) {
		case R.id.type_fib_jr:
			type = FibonacciRequest.Type.RECURSIVE_JAVA;
			break;
		case R.id.type_fib_ji:
			type = FibonacciRequest.Type.ITERATIVE_JAVA;
			break;
		case R.id.type_fib_nr:
			type = FibonacciRequest.Type.RECURSIVE_NATIVE;
			break;
		case R.id.type_fib_ni:
			type = FibonacciRequest.Type.ITERATIVE_NATIVE;
			break;
		default:
			return;
		}
		final FibonacciRequest request = new FibonacciRequest(n, type);

		// showing the user that the calculation is in progress
		final ProgressDialog dialog = ProgressDialog.show(this, "",
				super.getText(R.string.progress_text), true);
		// since the calculation can take a long time, we do it in a separate
		// thread to avoid blocking the UI
		new AsyncTask<Void, Void, String>() {
			@Override
			protected String doInBackground(Void... params) {
				// this method runs in a background thread
				try {
					long totalTime = SystemClock.uptimeMillis();
					Log.d(TAG, "calling fib in service");
					FibonacciResponse response = FibonacciActivity.this.service.fib(request);
					Log.d(TAG, "called fib in service");
					totalTime = SystemClock.uptimeMillis() - totalTime;
					// generate the result
					//Log.d(TAG, "Getting fd from response");
					//FileDescriptor fda = response.getfd();
					
					
					Log.d(TAG, "Getting byte buffer from response");
					byte[] buffer = new byte[testString.length];
					
					buffer = response.getbuffer();
						
					try {
						compareBuffers(testString, buffer, testString.length);
					} catch (Exception e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					Log.d(TAG, String.format("Past the compare Buffers Client"));
					

					return String.format(
							"fibonacci(%d)=%d\nin %d ms\n(+ %d ms)", n,
							response.getResult(), response.getTimeInMillis(),
							totalTime - response.getTimeInMillis());
				} catch (RemoteException e) {
					Log.wtf(TAG, "Failed to communicate with the service", e);
					return null;
				}
			}

			@Override
			protected void onPostExecute(String result) {
				// get rid of the dialog
				dialog.dismiss();
				if (result == null) {
					// handle error
					Toast.makeText(FibonacciActivity.this, R.string.fib_error,
							Toast.LENGTH_SHORT).show();
				} else {
					// show the result to the user
					FibonacciActivity.this.output.setText(result);
				}
			}
		}.execute(); // run our AsyncTask
	}
	
	private static final byte[] testString = new byte[] {
        3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3, 2, 3, 8, 4, 6, 2, 6, 4, 3, 3, 8, 3, 2, 7, 9, 5, 0, 2, 8, 8, 4, 1, 9, 7, 1, 6, 9, 3, 9, 9, 3, 7, 5, 1, 0, 5, 8, 2, 0, 9, 7, 4, 9, 4, 4, 5, 9, 2, 3, 0, 7, 8, 1, 6, 4,
        0, 6, 2, 8, 6, 2, 0, 8, 9, 9, 8, 6, 2, 8, 0, 3, 4, 8, 2, 5, 3, 4, 2, 1, 1, 7, 0, 6, 7, 9, 8, 2, 1, 4, 8, 0, 8, 6, 5, 1, 3, 2, 8, 2, 3, 0, 6, 6, 4, 7, 0, 9, 3, 8, 4, 4, 6, 0, 9, 5, 5, 0, 5, 8, 2, 2, 3, 1, 7, 2,
        5, 3, 5, 9, 4, 0, 8, 1, 2, 8, 4, 8, 1, 1, 1, 7, 4, 5, 0, 2, 8, 4, 1, 0, 2, 7, 0, 1, 9, 3, 8, 5, 2, 1, 1, 0, 5, 5, 5, 9, 6, 4, 4, 6, 2, 2, 9, 4, 8, 9, 5, 4, 9, 3, 0, 3, 8, 1, 9, 6, 4, 4, 2, 8, 8, 1, 0, 9, 7, 5,
        6, 6, 5, 9, 3, 3, 4, 4, 6, 1, 2, 8, 4, 7, 5, 6, 4, 8, 2, 3, 3, 7, 8, 6, 7, 8, 3, 1, 6, 5, 2, 7, 1, 2, 0, 1, 9, 0, 9, 1, 4, 5, 6, 4, 8, 5, 6, 6, 9, 2, 3, 4, 6, 0, 3, 4, 8, 6, 1, 0, 4, 5, 4, 3, 2, 6, 6, 4, 8, 2,
        1, 3, 3, 9, 3, 6, 0, 7, 2, 6, 0, 2, 4, 9, 1, 4, 1, 2, 7, 3, 7, 2, 4, 5, 8, 7, 0, 0, 6, 6, 0, 6, 3, 1, 5, 5, 8, 8, 1, 7, 4, 8, 8, 1, 5, 2, 0, 9, 2, 0, 9, 6, 2, 8, 2, 9, 2, 5, 4, 0, 9, 1, 7, 1, 5, 3, 6, 4, 3, 6,
        7, 8, 9, 2, 5, 9, 0, 3, 6, 0, 0, 1, 1, 3, 3, 0, 5, 3, 0, 5, 4, 8, 8, 2, 0, 4, 6, 6, 5, 2, 1, 3, 8, 4, 1, 4, 6, 9, 5, 1, 9, 4, 1, 5, 1, 1, 6, 0, 9, 4, 3, 3, 0, 5, 7, 2, 7, 0, 3, 6, 5, 7, 5, 9, 5, 9, 1, 9, 5, 3,
        0, 9, 2, 1, 8, 6, 1, 1, 7, 3, 8, 1, 9, 3, 2, 6, 1, 1, 7, 9, 3, 1, 0, 5, 1, 1, 8, 5, 4, 8, 0, 7, 4, 4, 6, 2, 3, 7, 9, 9, 6, 2, 7, 4, 9, 5, 6, 7, 3, 5, 1, 8, 8, 5, 7, 5, 2, 7, 2, 4, 8, 9, 1, 2, 2, 7, 9, 3, 8, 1,
        8, 3, 0, 1, 1, 9, 4, 9, 1, 2, 9, 8, 3, 3, 6, 7, 3, 3, 6, 2, 4, 4, 0, 6, 5, 6, 6, 4, 3, 0, 8, 6, 0, 2, 1, 3, 9, 4, 9, 4, 6, 3, 9, 5, 2, 2, 4, 7, 3, 7, 1, 9, 0, 7, 0, 2, 1, 7, 9, 8, 6, 0, 9, 4, 3, 7, 0, 2, 7, 7,
        0, 5, 3, 9, 2, 1, 7, 1, 7, 6, 2, 9, 3, 1, 7, 6, 7, 5, 2, 3, 8, 4, 6, 7, 4, 8, 1, 8, 4, 6, 7, 6, 6, 9, 4, 0, 5, 1, 3, 2, 0, 0, 0, 5, 6, 8, 1, 2, 7, 1, 4, 5, 2, 6, 3, 5, 6, 0, 8, 2, 7, 7, 8, 5, 7, 7, 1, 3, 4, 2,
        7, 5, 7, 7, 8, 9, 6, 0, 9, 1, 7, 3, 6, 3, 7, 1, 7, 8, 7, 2, 1, 4, 6, 8, 4, 4, 0, 9, 0, 1, 2, 2, 4, 9, 5, 3, 4, 3, 0, 1, 4, 6, 5, 4, 9, 5, 8, 5, 3, 7, 1, 0, 5, 0, 7, 9, 2, 2, 7, 9, 6, 8, 9, 2, 5, 8, 9, 2, 3, 5,
        4, 2, 0, 1, 9, 9, 5, 6, 1, 1, 2, 1, 2, 9, 0, 2, 1, 9, 6, 0, 8, 6, 4, 0, 3, 4, 4, 1, 8, 1, 5, 9, 8, 1, 3, 6, 2, 9, 7, 7, 4, 7, 7, 1, 3, 0, 9, 9, 6, 0, 5, 1, 8, 7, 0, 7, 2, 1, 1, 3, 4, 9, 9, 9, 9, 9, 9, 8, 3, 7,
        2, 9, 7, 8, 0, 4, 9, 9, 5, 1, 0, 5, 9, 7, 3, 1, 7, 3, 2, 8, 1, 6, 0, 9, 6, 3, 1, 8, 5, 9, 5, 0, 2, 4, 4, 5, 9, 4, 5, 5, 3, 4, 6, 9, 0, 8, 3, 0, 2, 6, 4, 2, 5, 2, 2, 3, 0, 8, 2, 5, 3, 3, 4, 4, 6, 8, 5, 0, 3, 5,
        2, 6, 1, 9, 3, 1, 1, 8, 8, 1, 7, 1, 0, 1, 0, 0, 0, 3, 1, 3, 7, 8, 3, 8, 7, 5, 2, 8, 8, 6, 5, 8, 7, 5, 3, 3, 2, 0, 8, 3, 8, 1, 4, 2, 0, 6, 1, 7, 1, 7, 7, 6, 6, 9, 1, 4, 7, 3, 0, 3, 5, 9, 8, 2, 5, 3, 4, 9, 0, 4,
        2, 8, 7, 5, 5, 4, 6, 8, 7, 3, 1, 1, 5, 9, 5, 6, 2, 8, 6, 3, 8, 8, 2, 3, 5, 3, 7, 8, 7, 5, 9, 3, 7, 5, 1, 9, 5, 7, 7, 8, 1, 8, 5, 7, 7, 8, 0, 5, 3, 2, 1, 7, 1, 2, 2, 6, 8, 0, 6, 6, 1, 3, 0, 0, 1, 9, 2, 7, 8, 7,
	}; 
}
