package com.honusoftware.android.examples;

import android.app.*;
import android.os.*;
import android.widget.*;

public class SongsActivity 
	extends Activity 
{
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        TextView textview = new TextView(this);
        textview.setText("This is the Songs tab");
        setContentView(textview);
    }
}
