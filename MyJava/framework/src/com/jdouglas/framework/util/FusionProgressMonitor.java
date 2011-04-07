/*
 * @(#)ProgressMonitor.java	1.37 06/04/12
 *
 * Copyright 2006 Sun Microsystems, Inc. All rights reserved.
 * SUN PROPRIETARY/CONFIDENTIAL. Use is subject to license terms.
 */

package com.jdouglas.framework.util;

import java.io.*;
import java.awt.*;
import java.beans.*;
import java.awt.event.*;
import java.text.*;
import java.util.*;
import javax.accessibility.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.text.*;


/** A class to monitor the progress of some operation. If it looks
 * like the operation will take a while, a progress dialog will be popped up.
 * When the ProgressMonitor is created it is given a numeric range and a
 * descriptive string. As the operation progresses, call the setProgress method
 * to indicate how far along the [min,max] range the operation is.
 * Initially, there is no ProgressDialog. After the first millisToDecideToPopup
 * milliseconds (default 500) the progress monitor will predict how long
 * the operation will take.  If it is longer than millisToPopup (default 2000,
 * 2 seconds) a ProgressDialog will be popped up.
 * <p>
 * From time to time, when the Dialog box is visible, the progress bar will
 * be updated when setProgress is called.  setProgress won't always update
 * the progress bar, it will only be done if the amount of progress is
 * visibly significant.
 *
 * <p>
 * 
 * For further documentation and examples see
 * <a
 href="http://java.sun.com/docs/books/tutorial/uiswing/components/progress.html">How to Monitor Progress</a>,
 * a section in <em>The Java Tutorial.</em>
 *
 * @see ProgressMonitorInputStream
 * @author James Gosling
 * @author Lynn Monsanto (accessibility) 
 * @version 1.37 04/12/06
 */
public class FusionProgressMonitor 
	extends Object 
{
	private FusionProgressMonitor root;
	private JDialog         dialog;
	private JOptionPane     pane;
	private JProgressBar    myBar;
	private JLabel          noteLabel;
	private Component       parentComponent;
	private String          note;
	private Object[]        cancelOption = null;
	private Object          message;
	private long            T0;
	private int             millisToDecideToPopup = 500;
	private int             millisToPopup = 2000;
	private int             min;
	private int             max;
	private int    			parentHWND = -1;

	/**
	* Constructs a graphic object that shows progress, typically by filling
	* in a rectangular bar as the process nears completion.
	*
	* @param parentComponent the parent component for the dialog box
	* @param message a descriptive message that will be shown
	*        to the user to indicate what operation is being monitored.
	*        This does not change as the operation progresses.
	*        See the message parameters to methods in
	*        {@link JOptionPane#message}
	*        for the range of values.
	* @param note a short note describing the state of the
	*        operation.  As the operation progresses, you can call
	*        setNote to change the note displayed.  This is used,
	*        for example, in operations that iterate through a
	*        list of files to show the name of the file being processes.
	*        If note is initially null, there will be no note line
	*        in the dialog box and setNote will be ineffective
	* @param min the lower bound of the range
	* @param max the upper bound of the range
	* @see JDialog
	* @see JOptionPane
	*/
	public FusionProgressMonitor(Component parentComponent,
								 Object message,
								 String note,
								 int min,
								 int max)
	{
		this(parentComponent, message, note, min, max, null);
	}


	/** 
	 * 
	 * @param parentComponent
	 * @param message
	 * @param note
	 * @param min
	 * @param max
	 * @param group
	 */
	private FusionProgressMonitor(Component parentComponent,
								  Object message,
								  String note,
								  int min,
								  int max,
								  FusionProgressMonitor group)
	{
		this.min = min;
		this.max = max;
		this.parentComponent = parentComponent;

		cancelOption = new Object[1];
		cancelOption[0] = UIManager.getString("OptionPane.cancelButtonText");

		this.message = message;
		this.note = note;
		if(group != null)
		{
			root = (group.root != null) ? group.root : group;
			T0 = root.T0;
			dialog = root.dialog;
		}
		else
		{
			T0 = System.currentTimeMillis();
		}
	}

	/** 
	* 
	* 
	*/
	private class ProgressOptionPane 
		extends JOptionPane
	{
		/** 
		 * 
		 * 
		 * @param messageList
		 */
		ProgressOptionPane(Object messageList)
		{
			super(messageList,
				  JOptionPane.INFORMATION_MESSAGE,
				  JOptionPane.DEFAULT_OPTION,
				  null,
				  FusionProgressMonitor.this.cancelOption,
				  null);
		}

		/** 
		 * 
		 * @return int
		 */
		public int getMaxCharactersPerLineCount()
		{
			return 60;
		}


		/** 
		 * Equivalent to JOptionPane.createDialog,                       
		 * but create a modeless dialog.                                 
		 * This is necessary because the Solaris implementation doesn't  
		 * support Dialog.setModal yet.                                  
		 * 
		 * @param parentComponent
		 * @param title
		 * 
		 * @return JDialog
		 */
		public JDialog createDialog(Component parentComponent, String title)
		{
			final JDialog dialog;

			if( (parentComponent instanceof Frame) || (parentComponent == null) )
			{
				dialog = new JDialog((Frame)parentComponent, title, false);  
			}
			else
			{
				dialog = new JDialog((Dialog)parentComponent, title, false);
			}

			Container contentPane = dialog.getContentPane();

			contentPane.setLayout(new BorderLayout());
			contentPane.add(this, BorderLayout.CENTER);
			dialog.pack();
			dialog.setLocationRelativeTo(parentComponent);
			dialog.addWindowListener(new WindowAdapter()
									 {
										 boolean gotFocus = false;

										 public void windowClosing(WindowEvent we)
										 {
											 setValue(cancelOption[0]);
										 }

										 public void windowActivated(WindowEvent we)
										 {
											 // Once window gets focus, set initial focus
											 if(!gotFocus)
											 {
												 if( parentHWND > 0 )
												 {
												     int myHWND = FusionUtils.getForegroundHWND();
												     FusionUtils.hookParentWindow(parentHWND, myHWND); 
													 //JOptionPane.showMessageDialog( null, "Hooking " + Integer.toHexString(myHWND) + " to " + Integer.toHexString(parentHWND) );
												 }
												 selectInitialValue();
												 gotFocus = true;
											 }
										 }

									 });

			addPropertyChangeListener(new PropertyChangeListener()
									  {
										  public void propertyChange(PropertyChangeEvent event)
										  {
											  if(dialog.isVisible() && 
												 event.getSource() == ProgressOptionPane.this &&
												 (event.getPropertyName().equals(VALUE_PROPERTY) ||
												  event.getPropertyName().equals(INPUT_VALUE_PROPERTY)))
											  {
												  if( parentHWND > 0 )
												  {
													  FusionUtils.unhookParentWindow( parentHWND );
												  }
												  dialog.setVisible(false);
												  dialog.dispose();
											  }
										  }
									  });

			return dialog;
		}
	}

	/**
    * Set the parent HWND to use for the dialog.
	* 
	* @param _parentHWND String
    */
	public void setParentHWND(String _parentHWND)
	{
		try
		{
			if( _parentHWND != null )
			{
				parentHWND = Integer.parseInt( _parentHWND );
			}
		}
		catch( Exception e )
		{
			e.printStackTrace( System.out );
			parentHWND = -1;
		}
	}

	/** 
	* Indicate the progress of the operation being monitored.
	* If the specified value is >= the maximum, the progress
	* monitor is closed. 
	* @param nv an int specifying the current value, between the
	*        maximum and minimum specified for this component
	* @see #setMinimum
	* @see #setMaximum
	* @see #close
	*/
	public void setProgress(int nv)
	{
		if(nv >= max)
		{
			close();
		}
		else
		{
			if(myBar != null)
			{
				myBar.setValue(nv);
			}
			else
			{
				long T = System.currentTimeMillis();
				long dT = (int)(T-T0);
				if(dT >= millisToDecideToPopup)
				{
					int predictedCompletionTime;
					if(nv > min)
					{
						predictedCompletionTime = (int)(dT *
														(max - min) /
														(nv - min));
					}
					else
					{
						predictedCompletionTime = millisToPopup;
					}
					if(predictedCompletionTime >= millisToPopup)
					{
						myBar = new JProgressBar();
						myBar.setMinimum(min);
						myBar.setMaximum(max);
						myBar.setValue(nv);
						if(note != null) noteLabel = new JLabel(note);
						pane = new ProgressOptionPane(new Object[] {message,
														  noteLabel,
														  myBar});
						dialog = pane.createDialog(parentComponent,
												   UIManager.getString("ProgressMonitor.progressText"));
						dialog.setVisible(true);
					}
				}
			}
		}
	}


	/** 
	 * Indicate that the operation is complete.  This happens automatically
	 * when the value set by setProgress is >= max, but it may be called
	 * earlier if the operation ends early.
	 */
	public void close()
	{
		if(dialog != null)
		{
			if( parentHWND > 0 )
			{
				FusionUtils.unhookParentWindow( parentHWND );
			}
			dialog.setVisible(false);
			dialog.dispose();
			dialog = null;
			pane = null;
			myBar = null;
		}
	}


	/**
	 * Returns the minimum value -- the lower end of the progress value.
	 *
	 * @return an int representing the minimum value
	 * @see #setMinimum
	 */
	public int getMinimum()
	{
		return min;
	}


	/**
	 * Specifies the minimum value.
	 *
	 * @param m  an int specifying the minimum value
	 * @see #getMinimum
	 */
	public void setMinimum(int m)
	{
		if(myBar != null)
		{
			myBar.setMinimum(m);
		}
		min = m;
	}


	/**
	 * Returns the maximum value -- the higher end of the progress value.
	 *
	 * @return an int representing the maximum value
	 * @see #setMaximum
	 */
	public int getMaximum()
	{
		return max;
	}


	/**
	 * Specifies the maximum value.
	 *
	 * @param m  an int specifying the maximum value
	 * @see #getMaximum
	 */
	public void setMaximum(int m)
	{
		if(myBar != null)
		{
			myBar.setMaximum(m);
		}
		max = m;
	}


	/** 
	 * Returns true if the user hits the Cancel button in the progress dialog.
	 */
	public boolean isCanceled()
	{
		if(pane == null) return false;
		Object v = pane.getValue();
		return((v != null) &&
			   (cancelOption.length == 1) &&
			   (v.equals(cancelOption[0])));
	}


	/**
	 * Specifies the amount of time to wait before deciding whether or
	 * not to popup a progress monitor.
	 *
	 * @param millisToDecideToPopup  an int specifying the time to wait,
	 *        in milliseconds
	 * @see #getMillisToDecideToPopup
	 */
	public void setMillisToDecideToPopup(int millisToDecideToPopup)
	{
		this.millisToDecideToPopup = millisToDecideToPopup;
	}


	/**
	 * Returns the amount of time this object waits before deciding whether
	 * or not to popup a progress monitor.
	 *
	 * @see #setMillisToDecideToPopup
	 */
	public int getMillisToDecideToPopup()
	{
		return millisToDecideToPopup;
	}


	/**
	 * Specifies the amount of time it will take for the popup to appear.
	 * (If the predicted time remaining is less than this time, the popup
	 * won't be displayed.)
	 *
	 * @param millisToPopup  an int specifying the time in milliseconds
	 * @see #getMillisToPopup
	 */
	public void setMillisToPopup(int millisToPopup)
	{
		this.millisToPopup = millisToPopup;
	}


	/**
	 * Returns the amount of time it will take for the popup to appear.
	 *
	 * @see #setMillisToPopup
	 */
	public int getMillisToPopup()
	{
		return millisToPopup;
	}


	/**
	 * Specifies the additional note that is displayed along with the
	 * progress message. Used, for example, to show which file the
	 * is currently being copied during a multiple-file copy.
	 *
	 * @param note  a String specifying the note to display
	 * @see #getNote
	 */
	public void setNote(String note)
	{
		this.note = note;
		if(noteLabel != null)
		{
			noteLabel.setText(note);
		}
	}


	/**
	 * Specifies the additional note that is displayed along with the
	 * progress message.
	 *
	 * @return a String specifying the note to display
	 * @see #setNote
	 */
	public String getNote()
	{
		return note;
	}
}
