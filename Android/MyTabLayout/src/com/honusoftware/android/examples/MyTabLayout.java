package com.honusoftware.android.examples;

import android.app.*;
import android.os.*;
import android.widget.*;
import android.content.res.*;
import android.content.*;

import com.honusoftware.android.examples.*;

public class MyTabLayout 
	extends TabActivity
{
	public void onCreate(Bundle savedInstanceState) 
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
	
		Resources res = getResources(); // Resource object to get Drawables
		TabHost tabHost = getTabHost();  // The activity TabHost
		TabHost.TabSpec spec;  // Resusable TabSpec for each tab
		Intent intent;  // Reusable Intent for each tab
	
		// Create an Intent to launch an Activity for the tab (to be reused)
		intent = new Intent().setClass(this, com.honusoftware.android.examples.ArtistsActivity.class);
	
		// Initialize a TabSpec for each tab and add it to the TabHost
		spec = tabHost.newTabSpec("artists").setIndicator("Artists", res.getDrawable(R.drawable.ic_tab_artists)).setContent(intent);
		tabHost.addTab(spec);
	
		// Do the same for the other tabs
		intent = new Intent().setClass(this, AlbumsActivity.class);
		spec = tabHost.newTabSpec("albums").setIndicator("Albums",res.getDrawable(R.drawable.ic_tab_albums)).setContent(intent);
		tabHost.addTab(spec);
	
		intent = new Intent().setClass(this, SongsActivity.class);
		spec = tabHost.newTabSpec("songs").setIndicator("Songs",res.getDrawable(R.drawable.ic_tab_songs)).setContent(intent);
		tabHost.addTab(spec);
	
		tabHost.setCurrentTab(1);
	}
}
