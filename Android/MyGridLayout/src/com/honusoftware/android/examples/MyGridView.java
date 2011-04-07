package com.honusoftware.android.examples;

import android.app.*;
import android.view.*;
import android.widget.*;
import android.widget.AdapterView.OnItemClickListener;
import android.content.*;
import android.os.*;

public class MyGridView 
	extends Activity
{
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        GridView gridview = (GridView) findViewById(R.id.gridview);
		gridview.setAdapter(new ImageAdapter(this));

		gridview.setOnItemClickListener(new OnItemClickListener() {
			public void onItemClick(AdapterView<?> parent, View v, int position, long id) {
				Toast.makeText(MyGridView.this, "" + position, Toast.LENGTH_SHORT).show();
			}
		});

    }
}


/** 
* 
*/
class ImageAdapter 
	extends BaseAdapter 
{
    private Context mContext;

    public ImageAdapter(Context c) 
	{
        mContext = c;
    }

    public int getCount() 
	{
        return mThumbIds.length;
    }

    public Object getItem(int position) 
	{
        return null;
    }

    public long getItemId(int position) 
	{
        return 0;
    }

    // create a new ImageView for each item referenced by the Adapter
    public View getView(int position, View convertView, ViewGroup parent) 
	{
        ImageView imageView;
        if (convertView == null) {  // if it's not recycled, initialize some attributes
            imageView = new ImageView(mContext);
            imageView.setLayoutParams(new GridView.LayoutParams(85, 85));
            imageView.setScaleType(ImageView.ScaleType.CENTER_CROP);
            imageView.setPadding(8, 8, 8, 8);
        } else {
            imageView = (ImageView) convertView;
        }

        imageView.setImageResource(mThumbIds[position]);
        return imageView;
    }

    // references to our images
    private Integer[] mThumbIds = { R.drawable.uradork, 
		                            R.drawable.classicpookie,
		                            R.drawable.pookieatarigame,
		                            R.drawable.pookieatbar,
		                            R.drawable.poopernpookie,
		                            R.drawable.poops,
		                            R.drawable.theeyesofpookie,
		                            R.drawable.whocansayno
		                          };
}
