package com.jdouglas.framework.util.math;

import java.util.*;

import org.apache.commons.math.stat.descriptive.*;
import org.apache.commons.math.distribution.*;

import com.jdouglas.framework.interfaces.data.*;
import com.jdouglas.framework.interfaces.props.*;
import com.jdouglas.framework.util.*;
import com.jdouglas.framework.core.*;
import com.jdouglas.framework.plots.*;

/**
* FusionMathUtils. A central class to hang math operations for use by framework clients. First iteration. Will rely on 
* the apache common math library (and thus double arrays) for the math operations.
*
* JGD NOTES: First pass. Maybe too ambitious to just hang this off one class a la FusionUtils. Also not sure about using
* JGD NOTES: doubles instead of BigDecimal as this will be used by FusionAE. Ideally, this class will operate on iTData
* JGD NOTES: object impl's so that we can maintain an interface layer btwn the actual math operations and the rest of the framework.
* JGD NOTES: 5/1/07
*
* @author Jason Douglas 5/1/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class FusionMathUtils
		implements IMathProperties
{
    /** Module name */
    private static final String MODULE_NAME                                                                 = "FusionMathUtils.";

    /** Me Pointer */
    private static FusionMathUtils Me = null;

	/** Resources */
	private static MathResources theResources;

    /**
    * Only FusionMathUtils can create FusionMathUtils. 
    */
    private FusionMathUtils()
    {
    }
                                              
    /**
    * Get me one.
    *
    * @return FusionMathUtils
    */
    public static FusionMathUtils getFusionMathUtils()
    {
        if( FusionMathUtils.Me == null )
        {
            FusionMathUtils.Me = new FusionMathUtils();
            FusionMathUtils.Me.initFusionMathUtils();
        }
        return Me;
    }

    /**
    * Start me up.
    */
    private void initFusionMathUtils()
    {
    }

    /**
    * Get the mean.
    *
    * @param vals ArrayList<Double>
    *
    * @return double
    */ 
    public static double getMean(ArrayList<Double> vals)
    {
        String methodName = MODULE_NAME + "getMean(ArrayList<Double>)";
        double retval = Double.NaN;

        try
        {
            DescriptiveStatistics stats = DescriptiveStatistics.newInstance();

            Iterator<Double> iter = vals.iterator();
            while( iter.hasNext() )
            {
                stats.addValue( iter.next().doubleValue() );
            }

            retval = stats.getMean();
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }

        return retval;
    }

    /**
    * Get the Standard Deviation.
    *
    * @param vals ArrayList<Double>
    *
    * @return double
    */ 
    public static double getStandardDeviation(ArrayList<Double> vals)
    {
        String methodName = MODULE_NAME + "getStandardDeviation(ArrayList<Double>)";
        double retval = Double.NaN;

        try
        {
            DescriptiveStatistics stats = DescriptiveStatistics.newInstance();

            Iterator<Double> iter = vals.iterator();
            while( iter.hasNext() )
            {
                stats.addValue( iter.next().doubleValue() );
            }

            retval = stats.getStandardDeviation();
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }

        return retval;
    }

    /**
    * Get the variance.
    *
    * @param vals ArrayList<Double>
    *
    * @return double
    */ 
    public static double getVariance(ArrayList<Double> vals)
    {
        String methodName = MODULE_NAME + "getVariance(ArrayList<Double>)";
        double retval = Double.NaN;

        try
        {
            DescriptiveStatistics stats = DescriptiveStatistics.newInstance();

            Iterator<Double> iter = vals.iterator();
            while( iter.hasNext() )
            {
                stats.addValue( iter.next().doubleValue() );
            }

            retval = stats.getVariance();
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }

        return retval;
    }

    /** 
    * Get the Relative Standard Deviation.
    * 
    * @param vals ArrayList<Double>
    * 
    * @return double
    */
    public static double getRelativeStandardDeviation(ArrayList<Double> vals) 
    {
        String methodName = MODULE_NAME + "getRelativeStandardDeviation(ArrayList<Double>)";
        double retval = Double.NaN;

        try
        {
            DescriptiveStatistics stats = DescriptiveStatistics.newInstance();

            Iterator<Double> iter = vals.iterator();
            while( iter.hasNext() )
            {
                stats.addValue( iter.next().doubleValue() );
            }

            double stdDev = stats.getStandardDeviation();
            double mean = stats.getMean();

            retval = Math.abs( (stdDev/mean) );
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }

        return retval;
    }

	/** 
	* Get the Relative Standard Deviation Percentage.
	* 
	* @param vals ArrayList<Double>
	* 
	* @return double
	*/
	public static double getRelativeStandardDeviationPercent(ArrayList<Double> vals) 
	{
		String methodName = MODULE_NAME + "getRelativeStandardDeviation(ArrayList<Double>)";
		double retval = Double.NaN;

		try
		{
			DescriptiveStatistics stats = DescriptiveStatistics.newInstance();

			Iterator<Double> iter = vals.iterator();
			while( iter.hasNext() )
			{
				stats.addValue( iter.next().doubleValue() );
			}

			double stdDev = stats.getStandardDeviation();
			double mean = stats.getMean();

			retval = Math.abs( ((stdDev/mean)*100) );
		}
		catch(Exception e)
		{
			FusionUtils.logError( methodName, "Failed", e );
		}

		return retval;
	}

    /** 
    * Get the sum of the squares for the given double array.
    *
    * @param vals ArrayList<Double>
    * 
    * @return double
    */
    public static double getSumOfSquares(ArrayList<Double> vals)
    {
        String methodName = MODULE_NAME + "getSumOfSquares(ArrayList<Double>)";
        double retval = 0;

        try
        {
            Iterator<Double> iter = vals.iterator();
            while( iter.hasNext() )
            {
                Double val = iter.next();
                retval += Math.pow( val.doubleValue(), 2 );
            }
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }

        return retval;
    }

    /**
    * Generate the Weibull shape and scale parameters with the given data. 
    * The data must be in the form of a Cumulative Probability Distribution Function. The x values should be time and 
    * the y values some percentage (thus falling btwn 0 and 100, dur). This function will calculate the shape (beta) and 
    * scale (theta) parameters and return them in a IPointData object where the x value is the shape and the Y value is the
	* scale. This code has been adapted from a VB module that GAC gave me. JGD 5/16/07 
	*  
	* @throws FusionException 
    *
    * @param data IPlotData
    *
    * @return IPointData
    */
    public static IPointData generateWeibullParamsForCPDF(IPlotData data)
		throws FusionException
    {
        String methodName = MODULE_NAME + "generateWeibullParamforCPDF(IPlotData)";
        IPointData retval = null;
        double fudgeFactor = 0.0000000001;

		//Logger.log( methodName  + " Starting points: ", Logger.DEBUG );
        ArrayList<Double> xVals = new ArrayList<Double>();
        ArrayList<Double> yVals = new ArrayList<Double>();

        Iterator<IPointData> ptIter = data.getPoints().iterator();
        while( ptIter.hasNext() )
        {
            IPointData pt = ptIter.next();

			//Logger.log( pt.toString(), Logger.DEBUG );

            double x = pt.getX();
            double y = pt.getY();

            if( (x<0) || (y<0) )
            {
                //We out. No values less than zero.
				throw new FusionException( theResources.getResourceString(LESS_THAN_ZERO_IN_WEIBULL_ERROR) );
            }

            //If the values are 0, continue without adding point.
            if( x < fudgeFactor ) continue;
            if( y < fudgeFactor ) continue;

            xVals.add( x ); //Autoboxing!!!
            yVals.add( y );
			//Logger.log( "X = " + x + " Y = " + y, Logger.DEBUG );
        }

        //Convert points into values that can be used to calculate Shape(beta) and Scale(theta)
        ArrayList<Double> linearTableXVals = new ArrayList<Double>();
        ArrayList<Double> linearTableYVals = new ArrayList<Double>();

        for(int i=0; i<xVals.size(); i++)
        {
            double x = Math.log( xVals.get(i).doubleValue() );
            double y = Math.log( -Math.log(1 - yVals.get(i).doubleValue()/100) );

            linearTableXVals.add( x ); //Autoboxing!!!
            linearTableYVals.add( y ); //Autoboxing!!!
			//Logger.log( methodName + " Logx = " + x + " log(-log(1-y/100)) = " + y, Logger.DEBUG );
		}

        //All values from here on out are derived from the Linear Table ArrayList.
        double meanXVals = getMean( linearTableXVals );
        double meanYVals = getMean( linearTableYVals );
        double sumOfSquaresX = 0;
        double sumOfSquaresY = 0;
        double sumOfSquaresXY = 0;
        double sumOfSquaresXiVals = getSumOfSquares(linearTableXVals);

        //Calculate B1 (GAC NOTE)
        for(int i=0; i<linearTableXVals.size(); i++)
        {
            sumOfSquaresX +=  Math.pow((linearTableXVals.get(i).doubleValue() - meanXVals), 2);
            sumOfSquaresXY += (linearTableXVals.get(i).doubleValue() - meanXVals) * (linearTableYVals.get(i) - meanYVals);
            sumOfSquaresY +=  Math.pow((linearTableYVals.get(i).doubleValue() - meanYVals), 2);
        }

        // Sanity checks
        if( meanYVals == 0 )
        {
            if( Math.abs(sumOfSquaresY) < fudgeFactor )
            {
				throw new FusionException( theResources.getResourceString(SUM_OF_SQUARES_ERROR) + " " + fudgeFactor + ".");
            }
        }
        else if( Math.abs(sumOfSquaresY/meanYVals) < fudgeFactor ) 
        {
			throw new FusionException( theResources.getResourceString(SUM_OF_SQUARES_MEAN_ERROR) + " " + fudgeFactor + ".");
        }

        //Beta 
        double shapeParam = 0.0;
        //Theta
        double scaleParam = 0.0;
		//True theta (whatever)
		double trueScaleParam = 0.0;

        //Calculate Shape
        if( sumOfSquaresX > 0 )
        {
            shapeParam = sumOfSquaresXY / sumOfSquaresX;
        }
        //Calculate Scale
        scaleParam = meanYVals - (shapeParam * meanXVals);
		trueScaleParam = Math.exp( -scaleParam / shapeParam );

		Logger.log( data.getStringProperty(IPlotData.PLOT_NAME), Logger.CONFIG );
		Logger.log( "Beta = " + shapeParam + " theta= " + scaleParam + " trueTheta: " + trueScaleParam, Logger.CONFIG );

        retval = new PointData( shapeParam, trueScaleParam );

        return retval;
    }

	/**
	* Generate the F1 Difference factor. The equation is
	* {sum[abs(observed - standard)]/sum(standard)}*100. 
	*  
	* @throws FusionException 
	* 
	* @param observedPlot IPlotData
	* @param standardPlot IPlotData
	* 
	* @return double
    */
	public static double generateF1Factor(IPlotData observedPlot, IPlotData standardPlot)
		throws FusionException
	{
		String methodName = MODULE_NAME + "generateF1Factor(IPlotData,IPlotData)";
		double retval = 0.0;

		double sumDelta = 0.0;
		double sumStandard = 0.0;

		Iterator<IPointData> ptIter = observedPlot.getPoints().iterator();
		while( ptIter.hasNext() )
		{
			IPointData pt = ptIter.next();
			IPointData standardPt = standardPlot.findPointForX( pt.getX() );
			if( standardPt == null )
			{
				String errMsg = theResources.getResourceString( MISSING_VAL_ERROR );
				throw new FusionException( errMsg.replaceAll(VAL_MASK, ""+pt.getX()) );
			}
			sumDelta += Math.abs( standardPt.getY()-pt.getY() );
			sumStandard += standardPt.getY();
		}

		retval = (sumDelta/sumStandard)*100;

		return retval; 
	}

	/**
	* Generate the F2 Similarity factor. The equation is 
	* 50*Log(100*{1 + sum[(observed-standard)^2]/number of time 
	* intervals}^-0.5. 
	*  
	* @throws FusionException 
	* 
	* @param observedPlot IPlotData
	* @param standardPlot IPlotData
	* 
	* @return double
	*/
	public static double generateF2Factor(IPlotData observedPlot, IPlotData standardPlot)
		throws FusionException
	{
		String methodName = MODULE_NAME + "generateF2Factor(IPlotData,IPlotData)";
		double retval = 0.0;

		double sumDeltaSquared = 0.0;
		int numberOfIntervals = 0;

		Iterator<IPointData> ptIter = observedPlot.getPoints().iterator();
		while( ptIter.hasNext() )
		{
			IPointData pt = ptIter.next();
			IPointData standardPt = standardPlot.findPointForX( pt.getX() );
			if( standardPt == null )
			{
				String errMsg = theResources.getResourceString( MISSING_VAL_ERROR );
				throw new FusionException( errMsg.replaceAll(VAL_MASK, ""+pt.getX()) );
			}

			sumDeltaSquared += Math.pow( standardPt.getY()-pt.getY(), 2 );
			numberOfIntervals++;
		}

		retval = 50 * Math.log10( 100 * Math.pow(1 + (sumDeltaSquared/numberOfIntervals),-0.5) );

		return retval; 
	}

	/**
    * Calculate the Effective Cutoff Diameter using the formula:
	* EffectiveCutoffDiameter = NominalCutoffDiameter * (EffectiveNozzleDiameter/NominalNozzleDiameter)^3/2
	* 
	* @param nominalCutoffDiameter Double
	* @param effectiveNozzleDiameter Double
	* @param nominalNozzleDiameter Double
	* 
	* @return Double
    */
	public static Double calculateEffectiveCutoffDiameter(Double nominalCutoffDiameter, Double effectiveNozzleDiameter, Double nominalNozzleDiameter)
	{
		String methodName = MODULE_NAME + "calculateEffectiveCutoffDiameter(Double,Double,Double)";
		Double retval = null;

		try
		{
			double nozzleFactor = (effectiveNozzleDiameter.doubleValue())/(nominalNozzleDiameter.doubleValue());
			nozzleFactor = Math.sqrt( nozzleFactor );
			nozzleFactor = Math.pow( nozzleFactor, 3 );
			retval = new Double( nominalCutoffDiameter.doubleValue() * nozzleFactor );
		}
		catch( Exception e )
		{
			FusionUtils.logError( methodName, "Failed", e );
		}

		return retval;
	}

	/** THere can be only one */
	static
	{
		theResources = new MathResources();
	}
}
