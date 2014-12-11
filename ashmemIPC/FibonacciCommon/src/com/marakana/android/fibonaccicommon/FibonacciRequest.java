package com.marakana.android.fibonaccicommon;

import android.os.Parcel;
import android.os.Parcelable;

public class FibonacciRequest implements Parcelable {

	public static enum Type {
		RECURSIVE_JAVA, ITERATIVE_JAVA, RECURSIVE_NATIVE, ITERATIVE_NATIVE
	}
	
	private final int ack, stop;
	

	public FibonacciRequest(int start, int stop) {
		this.ack = start;
		this.stop = stop;
	}

	
	public int getAck() {
		return ack;
	}
	
	public int getStop() {
		return stop;
	}

	public int describeContents() {
		return 0;
	}

	public void writeToParcel(Parcel parcel, int flags) {
		parcel.writeInt(ack);
		parcel.writeInt(stop);
	}

	public static final Parcelable.Creator<FibonacciRequest> CREATOR = new Parcelable.Creator<FibonacciRequest>() {
		public FibonacciRequest createFromParcel(Parcel in) {
			return new FibonacciRequest(in.readInt(), in.readInt());
		}

		public FibonacciRequest[] newArray(int size) {
			return new FibonacciRequest[size];
		}
	};
}
