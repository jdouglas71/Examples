package com.jdouglas.framework.core;

import java.awt.*;
import java.util.*;
import javax.swing.*;

import com.jdouglas.framework.interfaces.props.*;
import com.jdouglas.framework.util.*;
import static com.jdouglas.framework.interfaces.props.IFrameworkProperties.*;

/**
* FrameworkResources. Resources common to the framework
*
* @author Jason Douglas 11/14/06
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class FrameworkResources   
    extends FusionResources
{
    /** Module Name */
    private static final String MODULE_NAME                                                             = "FrameworkResources.";

    /** File Menu */
    public String fileMenu, fileSaveMenu, fileSaveAsMenu, filePrintMenu, filePrintToFileMenu, fileExitMenu;
    public String fileSaveTooltip, fileSaveAsTooltip, filePrintTooltip, filePrintToFileTooltip, fileExitTooltip;
    //public ImageIcon fileNewIcon,fileSaveIcon, fileSaveAsIcon, filePrintIcon, filePrintToFileIcon, fileExitIcon;
    /** Edit Menu */
    public String editMenu, editCutMenu, editCopyMenu, editPasteMenu, editUndoMenu, editRedoMenu;
    public String editCutTooltip, editCopyTooltip, editPasteTooltip, editUndoTooltip, editRedoTooltip;
    //public ImageIcon editCutIcon, editCopyIcon, editPasteIcon, editUndoIcon, editRedoIcon;
    /** view Menu */
    public String viewMenu;
    /** tools menu */
    public String toolsMenu;
    /** help Menu */
    public String helpMenu, helpHelpMenu, helpAboutMenu, helpLogCollectorMenu;
    public String helpHelpTooltip, helpAboutTooltip, helpLogCollectorTooltip;
    //public ImageIcon helpHelpIcon, helpAboutIcon, helpLogCollectorIcon;
    /** Button Labels */
    public String okButton, cancelButton, applyButton, clearButton, yesButton, noButton,  helpButton, browseButton, saveButton;
    public String nextButton, backButton, finishButton, selectButton, previewButton, selectAllButton, selectNoneButton, exitButton;
    /** Status bar messages */
    public String lockedText, lockedTooltip;
	/** Prompts */
	public String changePasswordPrompt;
    /** ICons */
    //public ImageIcon plusIcon, minusIcon, upArrowIcon, downArrowIcon, lockedIcon;
    /** Masks */
    public String dataSourceMask,dbUserNameMask,dbPasswordMask,recordNameMask,opIDMask,eventCodeMask,eventDataMask,userNameMask,auditCodeMask,typeMask,typeKeyMask,metaTypeMask;
    public String metaDataMask,idMask,appModMask,fileNameMask,tableNameMask,sourceDataMask,destDataMask,tableMask,dateTimeMask,reportIDMask,instrumentIDMask,instrumentXMLMask;         
    public String nameMask,driversMask,instrumentSourceMask,instrumentSystemSourceMask,dirMask,systemTokenMask,systemControlVersionMask;
    public String keyMask, valMask, parentMask,propMask,newValMask,oldValMask,daysMask;

	/** Display Strings */
	/** Products */
	public String allProductsDisplay,analyticalRnDDisplay,chemicalRnDDisplay,productRnDDisplay,qualityAssuranceDisplay;
	/** App Modules */
	public String allModulesDisplay,methodValidationDisplay,methodDevelopmentDisplay,processDevelopmentDisplay;
	/** Instrument Types */
	public String allTypesDisplay,hplcDisplay,gcDisplay;
	/** Instrument Control Programs */
	public String genericICPDisplay, totalChromDisplay, empowerDisplay, varianDisplay;     

	/** No App Module error */
	public String noAppModsAvailableError;

    /**
    * Constructor
    */
    protected FrameworkResources()
    {
        try
        {
            setBundleName( FRAMEWORK_BUNDLE );
			setResourceBaseClass(com.jdouglas.framework.core.FusionApplication.class);

            /** Menu Labels */
            fileMenu = getResourceString( FILE_MENU,"File" );
            fileSaveMenu = getResourceString( FILE_SAVE_MENU, "Save" );
            fileSaveAsMenu = getResourceString( FILE_SAVE_AS_MENU, "Save As..." );
            filePrintMenu = getResourceString( FILE_PRINT_MENU, "Print..." );
            filePrintToFileMenu = getResourceString( FILE_PRINT_TO_FILE_MENU, "Print to File..." );
            fileExitMenu = getResourceString( FILE_EXIT_MENU, "Exit" );

            editMenu = getResourceString( EDIT_MENU, "Edit" );
            editCutMenu = getResourceString( EDIT_CUT_MENU, "Cut" );
            editCopyMenu = getResourceString( EDIT_COPY_MENU, "Copy" );
            editPasteMenu = getResourceString( EDIT_PASTE_MENU, "Paste" );
            editUndoMenu = getResourceString( EDIT_UNDO_MENU, "Undo" );
            editRedoMenu = getResourceString( EDIT_REDO_MENU, "Redo" );

            viewMenu = getResourceString( VIEW_MENU, "View" );

            toolsMenu = getResourceString( TOOLS_MENU,"Tools" );

            helpMenu = getResourceString( HELP_MENU, "Help" );
            helpHelpMenu = getResourceString( HELP_HELP_MENU, "Help" );
            helpAboutMenu = getResourceString( HELP_ABOUT_MENU, "About" );
            helpLogCollectorMenu = getResourceString( HELP_LOG_COLLECTOR_MENU, "Log Collector" );

            /** tooltips */
            fileSaveTooltip = getResourceString( FILE_SAVE_TOOLTIP, "Save" );
            fileSaveAsTooltip = getResourceString( FILE_SAVE_AS_TOOLTIP, "Save As..." );
            filePrintTooltip = getResourceString( FILE_PRINT_TOOLTIP, "Print" );
            filePrintToFileTooltip = getResourceString( FILE_PRINT_TO_FILE_TOOLTIP, "Print to a file." );
            fileExitTooltip = getResourceString( FILE_EXIT_TOOLTIP, "Exit FusionAE" );

            editCutTooltip = getResourceString( EDIT_CUT_TOOLTIP, "Cut" );
            editCopyTooltip = getResourceString( EDIT_COPY_TOOLTIP, "Copy" );
            editPasteTooltip = getResourceString( EDIT_PASTE_TOOLTIP, "Paste" );
            editUndoTooltip = getResourceString( EDIT_UNDO_TOOLTIP, "Undo" );
            editRedoTooltip = getResourceString( EDIT_REDO_TOOLTIP, "Redo" );

            helpHelpTooltip = getResourceString( HELP_HELP_TOOLTIP, "Help" );
            helpAboutTooltip = getResourceString( HELP_ABOUT_TOOLTIP, "About" );
            helpLogCollectorTooltip = getResourceString( HELP_LOG_COLLECTOR_TOOLTIP, "Gathers relavent Fusion Administor state files in a single file that can be sent to Technical Support." );

            /** Button labels */
            okButton = getResourceString( OK_BUTTON, "Ok" );
            cancelButton = getResourceString( CANCEL_BUTTON, "Cancel" );
            applyButton = getResourceString( APPLY_BUTTON, "Apply" );
            clearButton = getResourceString( CLEAR_BUTTON, "Clear" );
            yesButton = getResourceString( YES_BUTTON, "Yes" );
            noButton = getResourceString( NO_BUTTON, "No" );
            helpButton = getResourceString( HELP_BUTTON, "Help" );
            browseButton = getResourceString( BROWSE_BUTTON, "Browse..." );
            saveButton = getResourceString( SAVE_BUTTON, "Save" );
            nextButton = getResourceString( NEXT_BUTTON, "Next" );
            backButton = getResourceString( BACK_BUTTON, "Back" );
            finishButton = getResourceString( FINISH_BUTTON, "Finish" );
            selectButton = getResourceString( SELECT_BUTTON, "Select" );
            previewButton = getResourceString( PREVIEW_BUTTON, "Preview" );
            selectAllButton = getResourceString( SELECT_ALL_BUTTON, "Select All" );
            selectNoneButton = getResourceString( SELECT_NONE_BUTTON, "Select None" );
			exitButton = getResourceString( EXIT_BUTTON, "Exit" );
            //Button = getResourceString( BUTTON, "" );

            /** Status bar messages */
            lockedText = getResourceString( LOCKED_TEXT, "Locked" );
            lockedTooltip = getResourceString( LOCKED_TOOLTIP, "This tab is locked" );

			/** Prompts */
			changePasswordPrompt = getResourceString( CHANGE_PASSWORD_PROMPT, "You have %DAYS% to change your password.\nWould you like to change it now?" );

			/** Icons */
			setDefaultValue( FILE_NEW_ICON, "images/fileNew.png" );
			setDefaultValue( FILE_SAVE_ICON, "images/fileSave.png" );
			setDefaultValue( FILE_SAVE_AS_ICON, "images/fileSaveAs.png" );
			setDefaultValue( FILE_PRINT_ICON, "images/filePrint.png" );
			setDefaultValue( FILE_PRINT_TO_FILE_ICON, "images/filePrintToFile.png" );
			setDefaultValue( FILE_EXIT_ICON, "images/fileExit.png" );

			setDefaultValue( EDIT_CUT_ICON, "images/editCut.png" );
			setDefaultValue( EDIT_COPY_ICON, "images/editCopy.png" ); 
			setDefaultValue( EDIT_PASTE_ICON, "images/editPaste.png" ); 
			setDefaultValue( EDIT_UNDO_ICON, "images/editUndo.png" );  
			setDefaultValue( EDIT_REDO_ICON, "images/editRedo.png" ); 

			setDefaultValue( HELP_HELP_ICON, "images/helpHelp.png" ); 
			setDefaultValue( HELP_ABOUT_ICON, "images/helpAbout.png" ); 
			setDefaultValue( HELP_LOG_COLLECTOR_ICON, "images/helpLogCollector.png" ); 

			setDefaultValue( PLUS_ICON, "images/add16.png" );
			setDefaultValue( MINUS_ICON, "images/minus16.png" );
			setDefaultValue( UP_ARROW_ICON, "images/upArrow.png" );
			setDefaultValue( DOWN_ARROW_ICON, "images/downArrow.png" );
			setDefaultValue( UP_ARROW_HEADER_ICON, "images/upArrow_16.png" );
			setDefaultValue( DOWN_ARROW_HEADER_ICON, "images/downArrow_16.png" );
			setDefaultValue( RIGHT_ARROW_ICON, "images/rightArrow.png" );
			setDefaultValue( LEFT_ARROW_ICON, "images/leftArrow.png" );
			setDefaultValue( LOCKED_ICON, "images/lock_16.png" );

			/** Titles */
			setDefaultValue( MOD_ROLE_PANEL_TITLE, "Choose the Fusion Application Module and Role." );


            /** Masks */
            dataSourceMask              = getResourceString( DATA_SOURCE_MASK );
            dbUserNameMask              = getResourceString( DB_USERNAME_MASK );
            dbPasswordMask              = getResourceString( DB_PASSWORD_MASK );
            recordNameMask              = getResourceString( RECORD_NAME_MASK );
            opIDMask                    = getResourceString( OPID_MASK );
            eventCodeMask               = getResourceString( EVENT_CODE_MASK );
            eventDataMask               = getResourceString( EVENT_DATA_MASK );
            userNameMask                = getResourceString( USER_NAME_MASK );
            auditCodeMask               = getResourceString( AUDIT_CODE_MASK );
            typeMask                    = getResourceString( TYPE_MASK ); 
            typeKeyMask                 = getResourceString( TYPE_KEY_MASK ); 
            metaTypeMask                = getResourceString( META_TYPE_MASK );
            metaDataMask                = getResourceString( META_DATA_MASK );
            idMask                      = getResourceString( ID_MASK );
            appModMask                  = getResourceString( APP_MODULE_MASK );
            fileNameMask                = getResourceString( FILENAME_MASK );
            tableNameMask               = getResourceString( TABLE_NAME_MASK );
            sourceDataMask              = getResourceString( SOURCE_DATA_MASK );
            destDataMask                = getResourceString( DESTINATION_DATA_MASK );
            tableMask                   = getResourceString( TABLE_MASK );
            dateTimeMask                = getResourceString( DATE_TIME_MASK );
            reportIDMask                = getResourceString( REPORT_ID_MASK );
            instrumentIDMask            = getResourceString( INSTRUMENT_ID_MASK );
            instrumentXMLMask           = getResourceString( INSTRUMENT_XML_MASK );
            nameMask                    = getResourceString( NAME_MASK );
            driversMask                 = getResourceString( DRIVERS_MASK );
            instrumentSourceMask        = getResourceString( INSTRUMENT_SOURCE_MASK );
            instrumentSystemSourceMask  = getResourceString( INSTRUMENT_SYSTEM_SOURCE_MASK );                                                               
            dirMask                     = getResourceString( DIR_MASK );
            systemTokenMask             = getResourceString( SYSTEM_TOKEN_MASK );
            systemControlVersionMask    = getResourceString( SYSTEM_CONTROL_VERSION_MASK );


			daysMask = getResourceString( DAYS_MASK, "%DAYS%" ); 
            valMask = getResourceString( VAL_MASK );
            keyMask = getResourceString( KEY_MASK );
			nameMask = getResourceString( NAME_MASK, "%NAME%" );
			propMask = getResourceString( PROP_MASK, "%PROP%" );
			oldValMask = getResourceString( OLDVAL_MASK,"%OLDVAL%" );
			newValMask = getResourceString( NEWVAL_MASK, "%NEWVAL%" );
			parentMask = getResourceString( PARENT_MASK, "%PARENT%" );

			noAppModsAvailableError = getResourceString( NO_APP_MOD_AVAILABLE_ERROR, "There are no available application modules for this user.\nThe application will exit." );

        }
        catch(Exception e) 
        {
            FusionUtils.logError( MODULE_NAME, "failed", e );
        }
    }

}
