package com.jdouglas.FCAdmin.util;

import java.util.*;

import com.jdouglas.framework.util.*;
import com.jdouglas.framework.enums.data.*;

import com.jdouglas.FCAdmin.*;
import com.jdouglas.FCAdmin.interfaces.data.*;

/**
* CommandLineParser. Command line Parser. Specific to FCAdmin for now, but in the future I'd like this to be generic.<br><br>
* JGD TODO: This is just a first pass. Must be more abstract for framework. <br><br>
*
* JGD NOTE: THe command line options and descriptions need to be in separate classes so that I can gather the objects and iterate
* thru them. Need to be able to present an options list too using the commands and descriptions.<br><br>
*
* @author Jason Douglas 2/24/04
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class CommandLineParser
{
    /** the Module name */
    private static final String MODULE_NAME                     = "CommandLineParser.";
	/** TotalChrom command line option */
    private static final String CMDLN_TOTALCHROM                = "TotalChrom";
	/** Millennium command line option */
    private static final String CMDLN_MILLENNIUM                = "Millennium";
	/** Varian Command line option */
    private static final String CMDLN_VARIAN                    = "Varian";
 
	/** The Option Mpa*/
    private Map<String,Object> theOptions;

	/** the command line options list */
    private static ArrayList<CommandLineOption> cmdLineOptions = new ArrayList<CommandLineOption>();

	/** the individual command line options */
    private static CommandLineOption helpFileCmd;
    private static CommandLineOption loggingCmd;
    private static CommandLineOption fusionFlavorCmd;
    private static CommandLineOption installDirCmd;
	private static CommandLineOption databaseDirCmd;
    private static CommandLineOption resetWindowCmd;
    private static CommandLineOption encryptKeyCmd;
    private static CommandLineOption installPackCmd;
    private static CommandLineOption fingerprintCmd;
    private static CommandLineOption reportInitCmd;
    private static CommandLineOption showDebugActionsCmd;
    private static CommandLineOption showAllInstrumentsCmd;
    private static CommandLineOption reinitInstrumentsCmd;
    private static CommandLineOption allowMultipleDriversCmd;
    private static CommandLineOption printSyntaxCmd;
    private static CommandLineOption noDriverValidationCmd;
    private static CommandLineOption showPanelNamesCmd;
    private static CommandLineOption showDriverDialogCmd;
    private static CommandLineOption noInstrumentLimitCmd;
	private static CommandLineOption productCentralCmd;
	private static CommandLineOption readInstrumentsFromDBCmd;
	private static CommandLineOption writeInstrumentsToDBCmd;
	private static CommandLineOption setTimeoutCmd;
	private static CommandLineOption unlockRolesCmd;
	private static CommandLineOption unlockConfigsCmd;
	private static CommandLineOption xmlDirCmd;
	private static CommandLineOption showThreadInfoCmd;
	private static CommandLineOption liteModeCmd;
	private static CommandLineOption showSplasherCmd;

    /**
    * Constructor.
    */
    public CommandLineParser()
    {
        theOptions = new HashMap<String,Object>();

        theOptions.put( FCAdmin.HELPFILE_CMD_OPTION, "cmd /c \"help\\FusionChrom Administrator Users Guide.pdf\"" );
        theOptions.put( FCAdmin.INSTALL_DIR_OPTION, "" );
        theOptions.put( FCAdmin.DATABASE_DIR_OPTION, "" );
        theOptions.put( FCAdmin.LOGGING_OPTION, new Boolean(false) );
        theOptions.put( FCAdmin.DEMO_OPTION, new Boolean(false) );       
        theOptions.put( FCAdmin.FLAVOR_OPTION, InstrumentControlProgram.GENERIC.getID() );     
        theOptions.put( FCAdmin.RESET_WINDOW_OPTION, new Boolean(false) );
        theOptions.put( FCAdmin.ENCRYPT_KEY_OPTION, "DEADBEEF" );
        theOptions.put( FCAdmin.INSTALL_PACK_FILE, "" );
        theOptions.put( FCAdmin.FINGERPRINT, null );
        //theOptions.put( FCAdmin.WORKSTATION_VERSION, new Boolean(false) );
        theOptions.put( FCAdmin.REPORT_INIT, new Boolean(false) );
        theOptions.put( FCAdmin.SHOW_DEBUG_ACTIONS, new Boolean(false) );
        theOptions.put( FCAdmin.SHOW_ALL_INSTRUMENTS, new Boolean(false) );
        theOptions.put( FCAdmin.REINIT_INSTRUMENTS, new Boolean(false) );
        theOptions.put( FCAdmin.ALLOW_MULTIPLE_DRIVERS, new Boolean(false) );
        theOptions.put( FCAdmin.NO_DRIVER_VALIDATION, new Boolean(false) );
        theOptions.put( FCAdmin.SHOW_PANEL_NAMES, new Boolean(false) );
        theOptions.put( FCAdmin.SHOW_DRIVER_DIALOG, new Boolean(false) );
        theOptions.put( FCAdmin.NO_INSTRUMENT_LIMIT, new Boolean(false) );
		theOptions.put( FCAdmin.PRODUCT_CENTRAL_MODEL, new Boolean(false) );
		theOptions.put( FCAdmin.READ_INSTRUMENTS_FROM_DB, new Boolean(false) );
		theOptions.put( FCAdmin.WRITE_INSTRUMENTS_TO_DB, new Boolean(false) );
		theOptions.put( FCAdmin.APPLICATION_TIMEOUT, new Integer(-1) );
		theOptions.put( FCAdmin.UNLOCK_ROLES, new Boolean(false) );
		theOptions.put( FCAdmin.UNLOCK_PTCONFIGS, new Boolean(false) );
		theOptions.put( FCAdmin.SHOW_THREAD_INFO, new Boolean(false) );
		theOptions.put( FCAdmin.LITE_MODE, null );
		theOptions.put( FCAdmin.SHOW_SPLASHER, true );
    }

    /**
    * Parsing the command line options. Sets the appropriate var's in FCAdmin.
    * 
    * @param args String[] The command line arguments passed to FCAdmin.
    */
    public void parseCommandLine(String[] args)
    {
        String methodName = MODULE_NAME + "parseCommandLine(String[])";

        try
        {
            for(int i=0; i<args.length; i++)
            {
                Logger.log( MODULE_NAME + methodName + " args[" + i + "] = " + args[i] );   
            }

            for(int i=0; i<args.length; i++)
            {
                //System.out.println( "args[" + i + "] ---> " + args[i] );
                if( helpFileCmd.getCommands().contains(args[i]) == true )
                {
                    //We got a help file option
                    i++;
                    if( (args[i] != null) && !(args[i].equals("")) )
                    {
                        String helpfileCommand = "cmd /c \"" + args[i] + "\"";
                        theOptions.put( FCAdmin.HELPFILE_CMD_OPTION, helpfileCommand.trim() );
                    }
                }
                else if( loggingCmd.getCommands().contains(args[i]) == true )
                {
                    //Turn on the logging
                    theOptions.put( FCAdmin.LOGGING_OPTION, new Boolean(true) );

                    //Extract the level (if present)
                    int logLevel = Logger.CONFIG; //Tracking.
                    try
                    {                                           
                        //Take off the first two char's (/v) and see if the remainder is parsable as an integer.
                        String logLevelStr = args[i].substring(2); 
                        logLevel = Integer.parseInt(logLevelStr);
                    }
                    catch(Exception e1)
                    {
                        //Don't care, go with the default
                    }
                    Logger.setLogLevel(logLevel);
                }
                else if( fusionFlavorCmd.getCommands().contains(args[i]) == true )
                {
                    //We got a flavor option
                    InstrumentControlProgram icp = InstrumentControlProgram.TOTALCHROM;
                    i++;
                    if( args[i].equalsIgnoreCase(CMDLN_TOTALCHROM) )
                    {
                        icp = InstrumentControlProgram.TOTALCHROM; 
                    }
                    else if( args[i].equalsIgnoreCase(CMDLN_MILLENNIUM) )
                    {
                        icp = InstrumentControlProgram.EMPOWER; 
                    }
                    else if( args[i].equalsIgnoreCase(CMDLN_VARIAN) )
                    {
                        icp = InstrumentControlProgram.GALAXIE; 
                    }

                    theOptions.put( FCAdmin.FLAVOR_OPTION, icp.getID() );
                }
                else if( installDirCmd.getCommands().contains(args[i]) == true )
                {
                    //We got the install dir
                    i++;
                    if( (args[i] != null) ) 
                    {
                        String installDir = args[i];
                        //Get rid of the double quotes if they come thru.
                        if( installDir.endsWith("\"") == true )
                        {
                            installDir = installDir.substring(0,installDir.length()-1);
                        }
                        if( installDir.startsWith("\"") == true )
                        {
                            installDir = installDir.substring( 1 );
                        }

                        theOptions.put( FCAdmin.INSTALL_DIR_OPTION, installDir.trim() );
                    }
                }
				else if( databaseDirCmd.getCommands().contains(args[i]) == true )
				{
					//We got the database dir
					i++;
					if( (args[i] != null) ) 
					{
						String databaseDir = args[i];
						//Get rid of the double quotes if they come thru.
						if( databaseDir.endsWith("\"") == true )
						{
							databaseDir = databaseDir.substring(0,databaseDir.length()-1);
						}
						if( databaseDir.startsWith("\"") == true )
						{
							databaseDir = databaseDir.substring( 1 );
						}

						theOptions.put( FCAdmin.DATABASE_DIR_OPTION, databaseDir.trim() );
					}
				}
                else if( resetWindowCmd.getCommands().contains(args[i]) == true )
                {
                    theOptions.put( FCAdmin.RESET_WINDOW_OPTION, new Boolean(true) );
                }
                else if( encryptKeyCmd.getCommands().contains(args[i]) == true )
                {
                    //We got the reg key
                    i++;
                    if( args[i] != null )
                    {
                        String encryptKey = args[i].trim();
						if( !encryptKey.equals("NOTINITIALIZED") )
						{
							theOptions.put( FCAdmin.ENCRYPT_KEY_OPTION, encryptKey );
							Logger.log( methodName + " got a encryption key: " + encryptKey );
						}
                    }
                }                                                  
                else if( installPackCmd.getCommands().contains(args[i]) == true )
                {
                    i++;
                    if( args[i] != null )
                    {
                        String installPackFile = args[i];
                        theOptions.put( FCAdmin.INSTALL_PACK_FILE, installPackFile.trim() );
                        Logger.log( methodName + " installPackFile: " + installPackFile );
                    }
                }
                else if( fingerprintCmd.getCommands().contains(args[i]) == true )
                {                                                 
                    i++;
                    if( args[i] != null )
                    {
                        String fingerprint = args[i].trim();
						if( !fingerprint.equals("NOTINITIALIZED") )
						{
							theOptions.put( FCAdmin.FINGERPRINT, fingerprint );
							Logger.log( methodName + " fingerprint: " + fingerprint );
						}
                    }
                }
                else if( reportInitCmd.getCommands().contains(args[i]) == true )
                {
                    theOptions.put( FCAdmin.REPORT_INIT, new Boolean(true) );
                }
                else if( showDebugActionsCmd.getCommands().contains(args[i]) == true )
                {
                    theOptions.put( FCAdmin.SHOW_DEBUG_ACTIONS, new Boolean(true) );
                }
                else if( showAllInstrumentsCmd.getCommands().contains(args[i]) == true )
                {
                    theOptions.put( FCAdmin.SHOW_ALL_INSTRUMENTS, new Boolean(true) );
                }
                else if( reinitInstrumentsCmd.getCommands().contains(args[i]) == true )
                {
                    theOptions.put( FCAdmin.REINIT_INSTRUMENTS, new Boolean(true) );
                }
                else if( allowMultipleDriversCmd.getCommands().contains(args[i]) == true )
                {
                    theOptions.put( FCAdmin.ALLOW_MULTIPLE_DRIVERS, new Boolean(true) );
                }
                else if(printSyntaxCmd.getCommands().contains(args[i]) == true )
                {
                    System.out.println();
                    System.out.println();
                    System.out.println();
                    System.out.println();
                    System.out.println( "Fusion Administrator Command Line Options:" );
                    System.out.println( "===========================================" );

                    Iterator iter = cmdLineOptions.iterator();
                    while( iter.hasNext() )
                    {
                        CommandLineOption clo = (CommandLineOption)iter.next();
                        if( clo.isVisible() )
                        {
                            System.out.println( clo.getSyntax() );
                        }
                    }
                    System.out.println();

                    System.exit( 0 );
                }
                else if( noDriverValidationCmd.getCommands().contains(args[i]) == true )
                {
                    theOptions.put( FCAdmin.NO_DRIVER_VALIDATION, new Boolean(true) );
                }
                else if( showPanelNamesCmd.getCommands().contains(args[i]) == true )
                {
                    theOptions.put( FCAdmin.SHOW_PANEL_NAMES, new Boolean(true) );
                }
                else if( showDriverDialogCmd.getCommands().contains(args[i]) == true )
                {
                    theOptions.put( FCAdmin.SHOW_DRIVER_DIALOG, new Boolean(true) );
                }
                else if( noInstrumentLimitCmd.getCommands().contains(args[i]) == true )
                {
                    theOptions.put( FCAdmin.NO_INSTRUMENT_LIMIT, new Boolean(true) );
                }
				else if( productCentralCmd.getCommands().contains(args[i]) == true )
				{
					theOptions.put( FCAdmin.PRODUCT_CENTRAL_MODEL, new Boolean(true) );
				}
				else if( readInstrumentsFromDBCmd.getCommands().contains(args[i]) == true )
				{
					theOptions.put( FCAdmin.READ_INSTRUMENTS_FROM_DB, new Boolean(true) );
				}
				else if( writeInstrumentsToDBCmd.getCommands().contains(args[i]) == true )
				{
					theOptions.put( FCAdmin.WRITE_INSTRUMENTS_TO_DB, new Boolean(true) );
				}
				else if( setTimeoutCmd.getCommands().contains(args[i]) == true )
				{
					theOptions.put( FCAdmin.APPLICATION_TIMEOUT, new Integer(args[++i]) );
				}
				else if( unlockRolesCmd.getCommands().contains(args[i]) == true )
				{
					theOptions.put( FCAdmin.UNLOCK_ROLES, new Boolean(true) );
				}
				else if( unlockConfigsCmd.getCommands().contains(args[i]) == true )
				{
					theOptions.put( FCAdmin.UNLOCK_PTCONFIGS, new Boolean(true) );
				}
				else if( xmlDirCmd.getCommands().contains(args[i]) == true )
				{
					//We got the xml dir
					i++;
					if( (args[i] != null) ) 
					{
						String xmlDir = args[i];
						//Get rid of the double quotes if they come thru.
						if( xmlDir.endsWith("\"") == true )
						{
							xmlDir = xmlDir.substring(0,xmlDir.length()-1);
						}
						if( xmlDir.startsWith("\"") == true )
						{
							xmlDir = xmlDir.substring( 1 );
						}

						theOptions.put( FCAdmin.XML_DIR_OPTION, xmlDir.trim() );
					}
				}
				else if( showThreadInfoCmd.getCommands().contains(args[i]) == true )
				{
					theOptions.put( FCAdmin.SHOW_THREAD_INFO, new Boolean(true) );
				}
				else if( liteModeCmd.getCommands().contains(args[i]) == true )
				{
					//We got the Lite mode flag
					i++;
					if( (args[i] != null) ) 
					{
						String famStr = args[i];
						Integer famVal = new Integer(-1);
						if( famStr.equals("FIT") )
						{
							famVal = new Integer(FusionApplicationModule.INHALER_TESTING_LITE.getID());
						}
						else if( famStr.equals("MD") )
						{
							famVal = new Integer(FusionApplicationModule.METHOD_DEVELOPMENT_LITE.getID());
						}
						else if( famStr.equals("MV") )
						{
							famVal = new Integer(FusionApplicationModule.METHOD_VALIDATION_LITE.getID());
						}
						else
						{
							famVal = null;
						}

						theOptions.put( FCAdmin.LITE_MODE, famVal );
					}
				}
				else if( showSplasherCmd.getCommands().contains(args[i]) == true )
				{
					theOptions.put( FCAdmin.SHOW_SPLASHER, false );
				}
            }
        }
        catch(Exception e)
        {
            Logger.log( MODULE_NAME + methodName + " error parsing command line." );
            Logger.logStackTrace( e );
        }
    }

    /**
    * Return the option associcated with the given string, if it exists. Null otherwise.
    *
    * @param optionKey String Option name key associated with option value.
    * @return Object containing the value associated with the key (or null).
    */
    public Object getOption(String optionKey)
    {
        String methodName = MODULE_NAME + "getOption(String)";
        Object retval = null;

        try
        {
            retval = theOptions.get( optionKey );
        }
        catch(Exception e)
        {
            FusionUtils.logError( methodName, "Failed", e );
        }

        return retval;
    }

    //JGD TODO Get from prop file. MORE ABSTRACT.
    private static final String[] helpFileCmdOptions            = { "/hf", 
                                                                    "-hf", 
                                                                    "/helpfile", 
                                                                    "-helpfile" 
                                                                  }; 

    private static final String[] loggingCmdOptions             = { "/v","-v",
                                                                    "/v10", "-v10",
                                                                    "/v9", "-v9",
                                                                    "/v8", "-v8",
                                                                    "/v7", "-v7",
                                                                    "/v6", "-v6",
                                                                    "/v5", "-v5",
                                                                    "/v4", "-v4",
                                                                    "/v3", "-v3",
                                                                    "/v2", "-v2",
                                                                    "/v1", "-v1",
                                                                    "/verbose",
                                                                    "-verbose"
                                                                  };

    private static final String[] fusionFlavorCmdOptions        = { "/fv",
                                                                    "-fv", 
                                                                    "/FusionVersion",
                                                                    "-FusionVersion"
                                                                 };

    private static final String[] installDirCmdOptions          = { "/id",
                                                                    "-id",
                                                                    "/InstallDir",
                                                                    "-InstallDir"
                                                                  };

    private static final String[] databaseDirCmdOptions         = { "/dbd",
     															    "-dbd",
     															    "/DatabaseDir",
     															    "-DatabaseDir"
     															  };


    private static final String[] resetWindowStateOptions       = { "/rw",
                                                                    "-rw",
                                                                    "/ResetWindow",
                                                                    "-ResetWindow"
                                                                  };

    private static final String[] encryptKeyOptions             = { "/ek",
                                                                    "-ek",
                                                                    "/EncryptKey",
                                                                    "-EncryptKey"
                                                                  };

    private static final String[] installPackOptions            = { "/ip",
                                                                    "-ip",
                                                                    "/InstallPack",
                                                                    "-InstallPack"
                                                                  };

    private static final String[] fingerprintOptions            = { "/f",
                                                                    "-f",
                                                                    "/Fingerprint",
                                                                    "-Fingerprint"
                                                                  };

    private static final String[] reportInitOptions             = { "/ri",
                                                                    "-ri",
                                                                    "/ReportInit",
                                                                    "-ReportInit"
                                                                  };

     private static final String[] showDebugActionsOptions      = { "/sd",
                                                                    "-sd",
                                                                    "/ShowDebug",
                                                                    "-ShowDebug"
                                                                  };

     private static final String[] showAllInstrumentsOptions    = { "/sa",
                                                                    "-sa",
                                                                    "/ShowAllInstruments",
                                                                    "-ShowAllInstruments"
                                                                  };

     private static final String[] reinitInstrumentsOptions     =  { "/rc",
                                                                     "-rc",
                                                                     "/ReinitInstruments",
                                                                     "-ReinitInstruments"
                                                                   };

    private static final String[] allowMultipleDriversOptions   =  { "/ad",
                                                                     "-ad",
                                                                     "/AllowMultipleDrivers",
                                                                     "-AllowMultipleDriverss"
                                                                   };

    private static final String[] printSyntaxOptions            =  { "/?",
                                                                     "-?",
                                                                     "/help",
                                                                     "-help"
                                                                   };

    private static final String[] noDriverValidationOptions     =  { "/ndv",
                                                                     "-ndv",
                                                                     "/NoDriverValidation",
                                                                     "-NoDriverValidation"
                                                                   };

    private static final String[] showPanelNamesOptions         =  { "/spn",
                                                                     "-spn",
                                                                     "/ShowPanelNames",
                                                                     "-ShowPanelNames"
                                                                   };

    private static final String[] showDriverDialogOptions       =  { "/sdd",
                                                                     "-sdd",
                                                                     "/ShowDriverDialog",
                                                                     "-ShowDriverDialog"
                                                                   };

    private static final String[] noInstrumentLimitOptions      = { "/nil",
                                                                    "-nil",
                                                                    "/NoInstrumentLimit",
                                                                    "-NoInstrumentLimit"
                                                                  };

	private static final String[] productCentralOptions         = { "/pcm",
																	"-pcm",
		                                                            "/ProductCentralModel",
		                                                            "-ProductCentralModel"
																  };

	private static final String[] readInstrumentsFromDBOptions  = { "/ridb",
		                                                            "-ridb",
		                                                            "/ReadInstrumentsFromDB",
		                                                            "-ReadInstrumentsFromDB" 
																  };

	private static final String[] writeInstrumentsToDBOptions   = { "/widb",
																    "-widb",
																    "/WriteInstrumentsToDB",
																    "-WriteInstrumentstoDB" 
																  };

	private static final String[] setTimeoutOptions             = { "/st",
																	"-st",
																	"/SetTimeout",
																	"-SetTimeout"
																  };

	private static final String[] unlockRolesOptions            = { "/ur",
																    "-ur",
																    "/UnlockRoles",
																    "-UnlockRoles"
															      };

	private static final String[] unlockConfigsOptions          = { "/uc",
																	"-uc",
																	"/UnlockConfigs",
																	"-UnlockConfigs"
																  };


	private static final String[] xmlDirOptions	                = { "/xmlDir",
																	"-xmlDir" 
		                                                          };

	private static final String[] showThreadInfoOptions        =  { "/sti",
		                                                            "-sti",
																    "/ShowThreadInfo",
		                                                            "-ShowThreadInfo"
															      };

	private static final String[] liteModeOptions 			   =  { "/lm",
		                                                            "-lm",
		                                                            "/LiteMode",
		                                                            "-LiteMode"
																  };


	private static final String[] showSplasherOptions          = { "/nss",
		                                                           "-nss",
		                                                           "/NoSplashScreen",
		                                                           "-NoSplashScreen"
																 };


    /**
    * Initialize the List's
    */
    static
    {
        helpFileCmd = new CommandLineOption( helpFileCmdOptions, "Specify location of helpfile." );
        cmdLineOptions.add( helpFileCmd );

        loggingCmd = new CommandLineOption( loggingCmdOptions, "Specify Logging Level." );                
        cmdLineOptions.add( loggingCmd );

        fusionFlavorCmd = new CommandLineOption( fusionFlavorCmdOptions, "Specify CDS type (e.g. Varian) for FA" );
        cmdLineOptions.add( fusionFlavorCmd  );

        installDirCmd = new CommandLineOption( installDirCmdOptions, "Specify FA installation directory"  );
        cmdLineOptions.add( installDirCmd );

		databaseDirCmd = new CommandLineOption( databaseDirCmdOptions, "Specify FA database directory"  );
		cmdLineOptions.add( databaseDirCmd );

		xmlDirCmd = new CommandLineOption( xmlDirOptions, "Specify XML directory" );
		cmdLineOptions.add( xmlDirCmd );

        resetWindowCmd = new CommandLineOption( resetWindowStateOptions, "Reset the window state." );
        cmdLineOptions.add( resetWindowCmd );

        encryptKeyCmd = new CommandLineOption( encryptKeyOptions, "Specify the key used to encrypt the license packs." );
        cmdLineOptions.add( encryptKeyCmd );

        installPackCmd = new CommandLineOption( installPackOptions, "Specify a license pack to be installed automatically" );
        cmdLineOptions.add( installPackCmd );

        fingerprintCmd = new CommandLineOption( fingerprintOptions, "Specify the hardware fingerprint." );
        cmdLineOptions.add( fingerprintCmd );

        reportInitCmd = new CommandLineOption( reportInitOptions, "Initialize the report tables." );
        cmdLineOptions.add( reportInitCmd );

        showDebugActionsCmd = new CommandLineOption( showDebugActionsOptions, "Show the debug actions." );
        cmdLineOptions.add( showDebugActionsCmd );

        showAllInstrumentsCmd = new CommandLineOption( showAllInstrumentsOptions, "Show all instruments regardless of the state of the visible flag." );
        cmdLineOptions.add( showAllInstrumentsCmd );

        reinitInstrumentsCmd = new CommandLineOption( reinitInstrumentsOptions, "Reinitialize all the instruments." );
        cmdLineOptions.add( reinitInstrumentsCmd );

        allowMultipleDriversCmd  = new CommandLineOption(  allowMultipleDriversOptions, "Allow drivers of the same category when defining an instrument." );
        cmdLineOptions.add( allowMultipleDriversCmd );

        noDriverValidationCmd  = new CommandLineOption( noDriverValidationOptions, "No Driver Validation." );
        cmdLineOptions.add( noDriverValidationCmd );

        showPanelNamesCmd  = new CommandLineOption( showPanelNamesOptions, "Show Panel Names (DEBUG ONLY)." );
        cmdLineOptions.add( showPanelNamesCmd );

        showDriverDialogCmd  = new CommandLineOption( showDriverDialogOptions, "Enable the Device Driver Dialog." );
        cmdLineOptions.add( showDriverDialogCmd );

        noInstrumentLimitCmd  = new CommandLineOption( noInstrumentLimitOptions, "No Instrument Limit." );
        cmdLineOptions.add( noInstrumentLimitCmd );

		productCentralCmd = new CommandLineOption( productCentralOptions, "Product Central Model." );
		cmdLineOptions.add( productCentralCmd );

		readInstrumentsFromDBCmd = new CommandLineOption( readInstrumentsFromDBOptions, "Read Instruments from the Database." );
		cmdLineOptions.add( readInstrumentsFromDBCmd );

		writeInstrumentsToDBCmd = new CommandLineOption( writeInstrumentsToDBOptions, "Write Instruments to the Database." );
		cmdLineOptions.add( writeInstrumentsToDBCmd );

		setTimeoutCmd = new CommandLineOption( setTimeoutOptions, "Set Application Timeout (in minutes)" );
		cmdLineOptions.add( setTimeoutCmd );

		unlockRolesCmd = new CommandLineOption( unlockRolesOptions, "Unlock roles." );
		cmdLineOptions.add( unlockRolesCmd );

		unlockConfigsCmd = new CommandLineOption( unlockConfigsOptions, "Unlock Product Testing Configs." );
		cmdLineOptions.add( unlockConfigsCmd );

		showThreadInfoCmd = new CommandLineOption( showThreadInfoOptions, "Show Thread info in log." );
		cmdLineOptions.add( showThreadInfoCmd );

		liteModeCmd = new CommandLineOption( liteModeOptions, "Run in Lite Mode." );
		liteModeCmd.setVisible( false );
		cmdLineOptions.add( liteModeCmd );

		showSplasherCmd = new CommandLineOption( showSplasherOptions, "Show the Splash Screen on Startup." );
		cmdLineOptions.add( showSplasherCmd );

        // Keep print syntax last in the list
        printSyntaxCmd  = new CommandLineOption( printSyntaxOptions, "Display command line options." );
        cmdLineOptions.add( printSyntaxCmd );
    }
}


