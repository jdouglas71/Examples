
import java.util.*;
import java.awt.*;
import javax.swing.*;
import java.math.*;
import java.awt.event.*;
import java.text.*;


public class Test   
    extends JFrame
        implements ActionListener
{
    private JLabel theLabel;
    private JButton theButton;

    /** RJB - 2005-06-03: FAE_8_2_FDD_013  Localized Date
     *  @param longMilliseconds to format
     *  @return String of formatted, localized date with [ GMT offset ]
     **/
    static public String getLocalizedDateTimeGMT( long longMilliseconds )
    {
        DateFormat dateFormat = DateFormat.getDateTimeInstance(DateFormat.LONG, DateFormat.LONG );

        SimpleDateFormat dateFormatGMTOffset = new SimpleDateFormat( "hh:mm" );

        long GMTOffset = dateFormat.getCalendar().get( Calendar.ZONE_OFFSET );

       // GMTOffset -= 60*1000;

        System.out.println( "Zone offset: " + GMTOffset );
        System.out.println( "Zone offset: " + (GMTOffset/3600000) );
        System.out.println( "Hours: " + (GMTOffset/3600000) );
        System.out.println( "Minutes: " + (GMTOffset%3600000) );
        Date d = new Date();

        if( dateFormat.getTimeZone().inDaylightTime(new Date(longMilliseconds)) )
        {
            GMTOffset += dateFormat.getCalendar().get( Calendar.DST_OFFSET ); 
        }

        d.setMinutes( Math.abs((int)(GMTOffset%3600000)) );
        d.setHours( Math.abs((int)(GMTOffset/3600000)) );
        System.out.println( "Zone offset: " + dateFormatGMTOffset.format(d) );
        System.out.println( "Zone offset: " + dateFormat.format(d) );

        StringBuffer buf = new StringBuffer( dateFormat.format(new Date(longMilliseconds) ) );

        if( GMTOffset != 0 )
        {
            buf.append( " [GMT" );
            if( GMTOffset < 0 )
            {
                buf.append( "-" );
            }
            else
            {
                buf.append( "+" );
            }

            buf.append( dateFormatGMTOffset.format(d) + "]" );
        }

        return buf.toString();
    }


    static public String newGetLocalizedDateTimeGMT( long longMilliseconds )
    {
        DateFormat dateFormat = DateFormat.getDateTimeInstance(DateFormat.LONG, DateFormat.LONG );
        long GMTOffset = dateFormat.getTimeZone().getRawOffset();
        Date theDate = new Date( longMilliseconds );

		System.out.println( dateFormat.getTimeZone().toString() );

        if( dateFormat.getTimeZone().inDaylightTime(theDate) )
        {
            GMTOffset += dateFormat.getTimeZone().getDSTSavings();
        }

        /* RJB - 2006-01-05 IR_2031: Previous method to obtain timezone GMT offset was double offsetting.
         *   This method now computes the offset and then gets the ID in the format desired.
         * NOTE:  Special time zones for Afghanistan, India, Nepal, and Australia are fraction of hours.
         *   The raw timezone offset is requires calculating the minutes.
         */
        long milliseconds_per_hour = 3600000L;
        long milliseconds_per_minute = 60000L;
        long GMTMinutes = ( GMTOffset % milliseconds_per_hour )/ milliseconds_per_minute;
        String GMTOffsetString = TimeZone.getTimeZone("GMT" + ( GMTOffset < 0 ? "" : "+" ) + (GMTOffset/3600000)).getID();
        return(   dateFormat.format( theDate )
              + ( GMTOffset != 0 ? " [" + ( GMTMinutes == 0L  ? GMTOffsetString : GMTOffsetString.substring(0, GMTOffsetString.length()-2) + Long.toString( GMTMinutes ))
                        + "]"
                       : "" ) );
    }

    /**
    * Ctor
    */ 
    public Test()
    {
        setTitle( "Make Bigger Test" );
        setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );

//        Date d = new Date(1110344093703L);
        Date d = new Date(1141665458433L);

        System.out.println( d.toLocaleString() );

        Date d2 = new Date(105,3,26);

        System.out.println( d2.getTime() );

        theLabel = new JLabel( "this is a label" );
        theLabel.setBorder( BorderFactory.createLineBorder(Color.YELLOW) );
        theButton = new JButton( "MakeBigger" );

        theButton.addActionListener( this );

        JPanel p = new JPanel();
        p.setLayout( new GridBagLayout() );
        GridBagConstraints gbc = new GridBagConstraints();

        gbc.anchor = GridBagConstraints.WEST;
        gbc.gridwidth = GridBagConstraints.REMAINDER;
        gbc.insets = new Insets( 10, 10, 10, 10 );

        p.add( theLabel, gbc );
        p.add( theButton, gbc );

        getContentPane().add( p );

        setSize( 400, 400 );
    }

    /**
    * Button handler
    */
    public void actionPerformed(ActionEvent e)
    {
        if( e.getSource().equals(theButton) )
        {
            makeBigger();
        }
    }

    /**
    * Attempt to resize the label.
    */
    private void makeBigger()
    {
        Dimension d = theLabel.getSize();
        d.width += 100;
        theLabel.setSize( d );
        theLabel.setPreferredSize( d );
        theLabel.getGraphics();
    }

    /**
    * Main
    */
    public static void main(String[] args)
    {
        //Test t = new Test();
        //t.show();

        //System.out.println( Test.getLocalizedDateTimeGMT( (new Date()).getTime() ) );
        System.out.println( Test.newGetLocalizedDateTimeGMT( (new Date()).getTime() ) );
        //System.out.println( (new Date()).getTime() );
        //System.out.println( Test.newGetLocalizedDateTimeGMT( 1170984529077L ) );
        //System.out.println( Test.newGetLocalizedDateTimeGMT( 1209000000000L ) );

        //System.out.println( Test.newGetLocalizedDateTimeGMT( 1200524059206L ) );
        //System.out.println( Test.newGetLocalizedDateTimeGMT( 1209000000000L ) );
        //System.out.println( Test.newGetLocalizedDateTimeGMT( 1230000000000L ) );

        
        //Locale[] locales = Locale.getAvailableLocales();

        //System.out.println( Locale.getDefault().getLanguage() );

        //BigDecimal bd = new BigDecimal( "10.0" );
        /*System.out.println( bd.toString() );
        bd.setScale( 4 );
        System.out.println( bd.toString() );
        bd.setScale( 2 );
        System.out.println( bd.toString() );
        System.out.println( BigDecimal.valueOf( 1, 1 ) );
        
        for(int i=0; i<locales.length; i++)
        {
            DecimalFormat df = new DecimalFormat("0.0000", new DecimalFormatSymbols(locales[i]));
            System.out.print( locales[i].getDisplayCountry() + " " );
            System.out.println( df.format(bd.doubleValue() ));
        }
        */
    }

}

