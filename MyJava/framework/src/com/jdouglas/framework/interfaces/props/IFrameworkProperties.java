package com.jdouglas.framework.interfaces.props;

/**
* IFrameworkProperties. The property strings for the basic framework GUI.
*
* @author Jason Douglas 11/14/06
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public interface IFrameworkProperties
{
    /** bundle name */
    public static final String FRAMEWORK_BUNDLE                             = "com.jdouglas.framework.core.FrameworkResources";

    /** menu labels */
    public static final String FILE_MENU                                    = "FileMenu";
    public static final String FILE_SAVE_MENU                               = "FileSaveMenu";
    public static final String FILE_SAVE_AS_MENU                            = "FileSaveAsMenu";
    public static final String FILE_PRINT_MENU                              = "FilePrintMenu";
    public static final String FILE_PRINT_TO_FILE_MENU                      = "FilePrintToFileMenu";
    public static final String FILE_EXIT_MENU                               = "FileExitMenu";

    public static final String EDIT_MENU                                    = "EditMenu";
    public static final String EDIT_CUT_MENU                                = "EditCutMenu";
    public static final String EDIT_COPY_MENU                               = "EditCopyMenu";
    public static final String EDIT_PASTE_MENU                              = "EditPasteMenu";
    public static final String EDIT_UNDO_MENU                               = "EditUndoMenu";
    public static final String EDIT_REDO_MENU                               = "EditRedoMenu";

    public static final String VIEW_MENU                                    = "ViewMenu";

    public static final String TOOLS_MENU                                   = "ToolsMenu";

    public static final String HELP_MENU                                    = "HelpMenu";
    public static final String HELP_HELP_MENU                               = "HelpHelpMenu";
    public static final String HELP_ABOUT_MENU                              = "HelpAboutMenu";
    public static final String HELP_LOG_COLLECTOR_MENU                      = "HelpLogCollectorMenu";

    /** Button Labels */
    public static final String OK_BUTTON                                    = "OkButton";
    public static final String CANCEL_BUTTON                                = "CancelButton";
    public static final String APPLY_BUTTON                                 = "ApplyButton";
    public static final String CLEAR_BUTTON                                 = "ClearButton";
    public static final String YES_BUTTON                                   = "YesButton";
    public static final String NO_BUTTON                                    = "NoButton";
    public static final String HELP_BUTTON                                  = "HelpButton";
    public static final String BROWSE_BUTTON                                = "BrowseButton";
    public static final String SAVE_BUTTON                                  = "SaveButton";
    public static final String NEXT_BUTTON                                  = "NextButton";
    public static final String BACK_BUTTON                                  = "BackButton";
    public static final String FINISH_BUTTON                                = "FinishButton";
    public static final String SELECT_BUTTON                                = "SelectButton";
    public static final String PREVIEW_BUTTON                               = "PreviewButton";
    public static final String SELECT_ALL_BUTTON                            = "SelectAllButton";
    public static final String SELECT_NONE_BUTTON                           = "SelectNoneButton";
    public static final String EXIT_BUTTON                                  = "ExitButton";
	public static final String RESET_BUTTON									= "ResetButton";
	public static final String NEW_BUTTON									= "NewButton";
	public static final String DELETE_BUTTON								= "DeleteButton";
	public static final String COMMIT_BUTTON								= "CommitButton";
	public static final String ADD_ROWS_BUTTON								= "AddRowsButton";

    /** Status bar messages */
    public static final String LOCKED_TEXT                                  = "LockedText";
    public static final String LOCKED_TOOLTIP                               = "LockedTooltip";

    /** Prompts */
    public static final String CHANGE_PASSWORD_PROMPT                       = "ChangePasswordPrompt";

    /** Icons */
    public static final String FILE_NEW_ICON                                = "FileNewIcon";
    public static final String FILE_SAVE_ICON                               = "FileSaveIcon";
    public static final String FILE_SAVE_AS_ICON                            = "FileSaveAsIcon";
    public static final String FILE_PRINT_ICON                              = "FilePrintIcon";
    public static final String FILE_PRINT_TO_FILE_ICON                      = "FilePrintToFileIcon";
    public static final String FILE_EXIT_ICON                               = "FileExitIcon";

    public static final String EDIT_CUT_ICON                                = "EditCutIcon";
    public static final String EDIT_COPY_ICON                               = "EditCopyIcon";
    public static final String EDIT_PASTE_ICON                              = "EditPasteIcon";
    public static final String EDIT_UNDO_ICON                               = "EditUndoIcon";
    public static final String EDIT_REDO_ICON                               = "EditRedoIcon";

    public static final String HELP_HELP_ICON                               = "HelpHelpIcon";
    public static final String HELP_ABOUT_ICON                              = "HelpAboutIcon";
    public static final String HELP_LOG_COLLECTOR_ICON                      = "HelpLogCollectorIcon";

    public static final String PLUS_ICON                                    = "PlusIcon";
    public static final String MINUS_ICON                                   = "MinusIcon";
    public static final String UP_ARROW_ICON                                = "UpArrowIcon";
    public static final String DOWN_ARROW_ICON                              = "DownArrowIcon";
    public static final String UP_ARROW_HEADER_ICON                         = "UpArrowHeaderIcon";
    public static final String DOWN_ARROW_HEADER_ICON                       = "DownArrowHeaderIcon";
    public static final String RIGHT_ARROW_ICON                             = "RightArrowIcon";
    public static final String LEFT_ARROW_ICON                              = "LeftArrowIcon";
    public static final String LOCKED_ICON                                  = "LockedIcon";
	public static final String PRECISION_ICON								= "PrecisionIcon";
	public static final String PRECISION_PLUS_ICON							= "PrecisionPlusIcon";
	public static final String PRECISION_MINUS_ICON							= "PrecisionMinusIcon";
	public static final String RED_DOT_ICON									= "RedDotIcon";
	public static final String GREEN_DOT_ICON								= "GreenDotIcon";
	public static final String DIRTY_ICON									= "DirtyIcon";
	public static final String GREEN_FLAG_ICON								= "GreenFlagIcon";
	public static final String YELLOW_FLAG_ICON								= "YellowFlagIcon";
	public static final String RED_FLAG_ICON								= "RedFlagIcon";

    /** Selection Properties */
    public static final String SELECTION_INDEX                              = "SelectionIndex";
    public static final String SELECTION_PATH                               = "SelectionPath";

    /** Masks */
    public static final String FILENAME_MASK                                = "FileNameMask";
    public static final String DATA_SOURCE_MASK                             = "DataSourceMask";
    public static final String DB_USERNAME_MASK                             = "DBUserNameMask";
    public static final String DB_PASSWORD_MASK                             = "DBPasswordMask";
    public static final String RECORD_NAME_MASK                             = "RecordNameMask";
    public static final String OPID_MASK                                    = "OpIDMask";
    public static final String EVENT_CODE_MASK                              = "EventCodeMask";
    public static final String USER_NAME_MASK                               = "UserNameMask";
    public static final String EVENT_DATA_MASK                              = "EventDataMask";
    public static final String AUDIT_CODE_MASK                              = "AuditCodeMask";
    public static final String TYPE_MASK                                    = "TypeMask";
    public static final String TYPE_KEY_MASK                                = "TypeKeyMask";
    public static final String META_TYPE_MASK                               = "MetaTypeMask";
    public static final String META_DATA_MASK                               = "MetaDataMask";
    public static final String ID_MASK                                      = "IdMask";
    public static final String APP_MODULE_MASK                              = "AppModuleMask";
    public static final String TABLE_NAME_MASK                              = "TableNameMask";
    public static final String SOURCE_DATA_MASK                             = "SourceDataMask";
    public static final String DESTINATION_DATA_MASK                        = "DestinationDataMask";
    public static final String TABLE_MASK                                   = "TableMask";
    public static final String DATE_TIME_MASK                               = "DateTimeMask";
    public static final String REPORT_ID_MASK                               = "ReportIDMask";
    public static final String INSTRUMENT_ID_MASK                           = "InstrumentIDMask";
    public static final String INSTRUMENT_XML_MASK                          = "InstrumentXMLMask";
    public static final String DRIVERS_MASK                                 = "DriversMask";
    public static final String INSTRUMENT_SOURCE_MASK                       = "InstrumentSourceMask";
    public static final String INSTRUMENT_SYSTEM_SOURCE_MASK                = "InstrumentSystemSourceMask";
    public static final String DIR_MASK                                     = "DirMask";
    public static final String SYSTEM_CONTROL_VERSION_MASK                  = "SystemControlVersionMask";
    public static final String SYSTEM_TOKEN_MASK                            = "SystemTokenMask";
    public static final String KEY_MASK                                     = "KeyMask";
    public static final String VAL_MASK                                     = "ValMask";
    public static final String NAME_MASK                                    = "NameMask";
    public static final String PROP_MASK                                    = "PropMask";
    public static final String OLDVAL_MASK                                  = "OldValMask";
    public static final String NEWVAL_MASK                                  = "NewValMask";
    public static final String PARENT_MASK                                  = "ParentMask";
    public static final String DAYS_MASK                                    = "DaysMask";

    /** General */
    public static final String WIZARD_CONTAINER                             = "WizardContainer";
    public static final String MOD_ROLE_PANEL_TITLE                         = "ModRolePanelTitle";
    public static final String PRECISION_DIALOG_TITLE                       = "PrecisionDialogTitle";
    public static final String NUM_DECIMAL_PLACES_LABEL                     = "NumDecimalPlacesLabel";
	public static final String UNITS_LABEL									= "UnitsLabel";

    /** Tooltips */
    public static final String FILE_SAVE_TOOLTIP                            = "FileSaveTooltip";
    public static final String FILE_SAVE_AS_TOOLTIP                         = "FileSaveAsTooltip";
    public static final String FILE_PRINT_TOOLTIP                           = "FilePrintTooltip";
    public static final String FILE_PRINT_TO_FILE_TOOLTIP                   = "FilePrintToFileTooltip";
    public static final String FILE_EXIT_TOOLTIP                            = "FileExitTooltip";

    public static final String EDIT_CUT_TOOLTIP                             = "EditCutTooltip";
    public static final String EDIT_COPY_TOOLTIP                            = "EditCopyTooltip";
    public static final String EDIT_PASTE_TOOLTIP                           = "EditPasteTooltip";
    public static final String EDIT_UNDO_TOOLTIP                            = "EditUndoTooltip";
    public static final String EDIT_REDO_TOOLTIP                            = "EditRedoTooltip";

    public static final String HELP_HELP_TOOLTIP                            = "HelpHelpTooltip";
    public static final String HELP_ABOUT_TOOLTIP                           = "HelpAboutTooltip";
    public static final String HELP_LOG_COLLECTOR_TOOLTIP                   = "HelpLogCollectorTooltip";

    /** Messages */
	public static final String VALID_SETTINGS_MSG							= "ValidSettingsMsg";
    public static final String NO_APP_MOD_AVAILABLE_ERROR                   = "NoAppModsAvailableError";
}
