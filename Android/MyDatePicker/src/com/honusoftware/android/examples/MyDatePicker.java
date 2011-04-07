package com.honusoftware.android.examples;

import java.util.*;

import android.app.*;
import android.os.*;
import android.widget.*;
import android.view.*;

public class MyDatePicker 
	extends Activity
{
	private TextView theDateDisplay;
	private Button pickDateButton;
	private int year;
	private int month;
	private int day;

	public static final int DATE_DIALOG_ID = 0;


    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

		//Capture the view elements
		theDateDisplay = (TextView)findViewById(R.id.dateDisplay);
		pickDateButton = (Button)findViewById(R.id.pickDate);

		//Add click listener
		pickDateButton.setOnClickListener( new View.OnClickListener() 
										   {
												public void onClick(View v)
												{
													showDialog( DATE_DIALOG_ID );
												}
										    }
										  );

		//get the current date
		final Calendar c = Calendar.getInstance();
		year = c.get(Calendar.YEAR);
		month = c.get(Calendar.MONTH);
		day = c.get(Calendar.DAY_OF_MONTH);

		//Display the current date
		updateDisplay();
    }

	/**
    * Update the display
    */
	private void updateDisplay()
	{
		StringBuilder buf = new StringBuilder();

		buf.append( month+1 + "-" );
		buf.append( day + "-" );
		buf.append( year + " " );

		theDateDisplay.setText( buf );
	}

	/** Date Picker listener */
	private DatePickerDialog.OnDateSetListener dateSetListener = new DatePickerDialog.OnDateSetListener() 
																	{
																		public void onDateSet(DatePicker view, int _year, int _month, int _day)
																		{
																			year = _year;
																			month = _month;
																			day = _day;
																			updateDisplay();
																		}
																	};
    /**
    * Create dialogs 
    */
	@Override
	protected Dialog onCreateDialog(int id)
	{
		switch( id )
		{
			case DATE_DIALOG_ID:
				return new DatePickerDialog( this, dateSetListener, year, month, day );
			default:
				return null;
		}
	}

}
