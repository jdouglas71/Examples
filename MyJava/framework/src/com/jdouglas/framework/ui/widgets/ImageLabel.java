package com.jdouglas.framework.ui.widgets;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.*;

import com.jdouglas.framework.util.*;

/**
* ImageLabel. An image display label that allows the caller to specify the size of the label and the contained image.
* The image will be then scaled to fit in the given dimensions.
*
* @author Jason Douglas 8/10/05
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/ 

public class ImageLabel 
    extends JComponent
{
	/** Module name */
    private static final String MODULE_NAME                                     = "ImageLabel.";

	/** The contained Image */
    private Image theImage;
	/** X Scaling factor */
    private double scaleX;
	/** Y Scaling factor */
    private double scaleY;
	/** requested component width */
    private int requestedWidth;
	/** requested component height */
    private int requestedHeight;
	/** The computed Component width */
    private int theWidth;
	/** the computed component height */
    private int theHeight;
	/** Resize Image flag, if true, the image is resized to fit in the component */
    private boolean resizeImageFlag = false;
	/** Maintain aspect ratio */
	private boolean maintainAspectFlag = true;
	/** Shrink to Fit flag */
	private boolean shrinkToFitFlag = false;

    /**
    * Constructor.
    *
    * @param width int
    * @param height int
    * @param image Image
    * @param resizeImage boolean When set, the image will be resized to fit in the given component parameters, maintaining the image aspect ratio.
	* @param shrinkToFit boolean If true, once image processing has been done based on resizeImageFlag, the component will be resized to match the result image size. 
    */
    public ImageLabel(int width, int height, Image image, boolean resizeImage, boolean shrinkToFit)
    {
        requestedWidth = width;
        requestedHeight = height;
		resizeImageFlag = resizeImage;
		shrinkToFitFlag = shrinkToFit;

        setImage( image );
    }

	/**
	* Constructor.
	*
	* @param width int
	* @param height int
	* @param image Image
    * @param resizeImage boolean When set, the image will be resized to fit in the given component parameters.
	*/
	public ImageLabel(int width, int height, Image image, boolean resizeImage)
	{
		this( width, height, image, resizeImage, resizeImage );
	}

    /**
    * Constructor.
    *
    * @param width int
    * @param height int
    * @param image Image
    */
    public ImageLabel(int width, int height, Image image)
    {
        this( width, height, image, false, false );
    }

    /**
    * Constructor. Create a label that is the same size as the given image.
    *
    * @param image Image
    */
    public ImageLabel(Image image)
    {
        this( image.getWidth(null), image.getHeight(null), image, false, false );
    }

    /**
    * What can be said about paintComponent that hasn't been said one hundred times before?
    *
    * @param g Graphics
    */
    public void paintComponent(Graphics g)
    {
        String methodName = MODULE_NAME + "paintComponent(Graphics)";
        Graphics2D g2 = (Graphics2D)g;
		//Save off current transform 
        AffineTransform oldTransform = g2.getTransform();

		//Scale image transform
        g2.transform( AffineTransform.getScaleInstance(scaleX,scaleY) );
        g2.drawImage( theImage, 0, 0, this );

		//Restore old transform 
        g2.transform( oldTransform );
    }

    /**
    * Set the image for the label.
    *
    * @param image Image
    */
    public void setImage(Image image)
    {
        String methodName = MODULE_NAME + "setImage(Image)";
        
        try
        {
            theImage = image;
            
			recalculateFactors();
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Setting image failed.", e );
        }
    }

    /**
    * Get the Image from the label.
    *
    * @return Image
    */
    public Image getImage()
    {
        return theImage;
    }

    /**
    * Set the scale factors for the image. Forces repaint.
    *
    * @param _scaleX double
    * @param _scaleY double 
    */
    public void setScaleFactors(double _scaleX, double _scaleY)
    {
        scaleX = _scaleX;
        scaleY = _scaleY;
        invalidate();
        validate();
        repaint();
    }

    /**
    * Get the X Scale factor.
    *
    * @return double
    */
    public double getXScaleFactor()
    {
        return scaleX;
    }

    /**
    * Get the Y Scale factor.
    *
    * @return double
    */
    public double getYScaleFactor()
    {
        return scaleY;
    }

	/**
    * Set the resize image flag. 
	* 
	* @param b boolean
    */
	public void setResizeImageFlag(boolean b)
	{
		resizeImageFlag = b;
		recalculateFactors();
	}

	/**
    * Set the Maintain Aspect Ratio Flag 
	* 
	* @param b boolean 
    */
	public void setMaintainAspectRatioFlag(boolean b)
	{
		maintainAspectFlag = b;
		recalculateFactors();
	}

	/**
	* Set the Shrink to Fit Flag 
	* 
	* @param b boolean 
	*/
	public void setShrinkToFitFlag(boolean b)
	{
		shrinkToFitFlag = b;
		recalculateFactors();
	}

	/**
    * Recalculate Component factors. 
    */
	private void recalculateFactors()
	{
		String methodName = MODULE_NAME + "recalculateFactors()";

		theWidth = requestedWidth;
		theHeight = requestedHeight;

		if( resizeImageFlag == false )
		{
			if( shrinkToFitFlag == true )
			{
				//Not resizing image, but still resetting component size to fit the image.
				theWidth = theImage.getWidth(this);
				theHeight = theImage.getHeight(this);
			}

			scaleX = 1.0;
			scaleY = 1.0;
		}
		else
		{
			//Using requested component size to resize the image to fit. 
			//Gotta factor in the border dimensions when scaling 
			scaleX = (double)(theWidth) / theImage.getWidth(this);
			scaleY = (double)(theHeight) / theImage.getHeight(this);

			//Aspect Ratio
			if( maintainAspectFlag == true )
			{
				//Pick the smaller one?
				if( scaleX < scaleY )
				{
					scaleY = scaleX;
				}
				else 
				{
					scaleX = scaleY;
				}
			}

			if( shrinkToFitFlag == true )
			{
				theWidth = (int)(scaleX * theImage.getWidth(this));
				theHeight = (int)(scaleY * theImage.getHeight(this));
			}
		}

		setSize( theWidth, theHeight );
		setPreferredSize( new Dimension(theWidth, theHeight) );
		setMinimumSize( new Dimension(theWidth,theHeight) );

		Logger.log( methodName + " ResizeImageFlag: " + resizeImageFlag, Logger.CONFIG );
		Logger.log( methodName + " width: " + theWidth + " Height: " + theHeight, Logger.CONFIG );
		Logger.log( methodName + " theImage.getWidth(): " + theImage.getWidth(null) + " theImage.getHeight(): " + theImage.getHeight(null), Logger.CONFIG );
		Logger.log( methodName + " scaleX: " + scaleX + " scaleY: " + scaleY, Logger.CONFIG );

		invalidate();
		validate();
		repaint();
	}
}
