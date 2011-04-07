package com.honusoftware.android.examples;

import android.app.*;
import android.os.*;
import android.widget.*;

public class AlbumsActivity 
	extends Activity 
{
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        TextView textview = new TextView(this);
        textview.setText("This is the Albums tab");
        setContentView(textview);
    }
}
