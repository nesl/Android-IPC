package com.marakana.android.fibonaccicommon;

import android.os.Parcel;
import android.os.Parcelable;

public class FibonacciResponse implements Parcelable {

	private long result;
	private long timeInMillis;
	
	private float data[];

	
	public FibonacciResponse(long result, long timeInMillis) 
	{ 
		this.result = result;
		this.timeInMillis = timeInMillis;
	}
	
	public FibonacciResponse(long result, long timeInMillis, float _data[]) 
	{ 
		this.result = result;
		this.timeInMillis = timeInMillis;
		this.data = _data;
	}
	
	public long getResult() {
		return result;
	}

	public long getTimeInMillis() {
		return timeInMillis;
	}

	public int describeContents() {
		return 0;
	}

	public FibonacciResponse(Parcel in){
	    readFromParcel(in);
	}

	 public static final Parcelable.Creator<FibonacciResponse> CREATOR = new Parcelable.Creator<FibonacciResponse>() {
	        public FibonacciResponse createFromParcel(Parcel in) {
	            return new FibonacciResponse(in);
	        }

	        public FibonacciResponse[] newArray(int size) {
	            return new FibonacciResponse[size];
	        }
	    };
	   
	public void writeToParcel(Parcel dest, int flags) {
	    dest.writeLong(result);
	    dest.writeLong(timeInMillis);
	    dest.writeInt(data.length);
	    dest.writeFloatArray(data);
	}

	public void readFromParcel(Parcel in){
	    this.result = in.readLong();
	    this.timeInMillis = in.readLong();
	    this.data = new float[in.readInt()];
	    in.readFloatArray(data);
	}
}
