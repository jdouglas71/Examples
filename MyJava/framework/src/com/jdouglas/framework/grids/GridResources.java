package com.jdouglas.FusionAE.grids;

import java.awt.*;
import java.util.*;
import javax.swing.*;

import com.jdouglas.framework.util.*;
import com.jdouglas.framework.core.*;

import com.jdouglas.FusionAE.interfaces.data.*;
import com.jdouglas.FusionAE.interfaces.props.*;
import static com.jdouglas.FusionAE.interfaces.props.IGridProperties.*;

/**
* GridResources. 
*
* @author Jason Douglas 3/6/07
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public class GridResources
    extends FusionResources
{
    /** Module name */
    private static final String MODULE_NAME                                                                     = "GridResources.";

    /** Data */
    public String addGridMenu, addGridTooltip, responseDataHandlerMenu, responseDataHandlerTooltip;
    public String buildGoldCurveTitle,enterResponseNameLabel,enterTimeSeriesLabel,descriptiveStatisticsLabel,numMeasurementsLabel;
    public String timeUnitsLabel,totalTimePeriodLabel,numRepeatsLabel,repeatRunLabel,timeSeriesColLabel;
    public String createResponsesTitle,f1CheckerLabel,f2CheckerLabel,responseAtXLabel,yValAtXLabel,numResponsesLabel,includeInMainGridLabel;
    public String f1ColTitle,f2ColTitle,rrWizardTitle,weibullShapeColTitle,weibullScaleColTitle,weibullShapeColTitleVB,weibullScaleColTitleVB; 
    public String meanLabel,varianceLabel,stdDevLabel,relStdDevLabel,relStdDevPercentLabel,currentDataPanelTitle,currentPlotLabel,updateButton,runNumberLabel;
    public String endPtLabel,targetLabel,curveTypeLabel,invalidEndPtError,addGridWizardTitle;
    public String timeSeriesEditorTitle,timeSeriesWorkAreaTitle,plotOptionsPanelTitle,selectRunsButton,editRunsButton;
    public String rrToolsNode,defineTargetProfileNode,buildCurveNode,currentDataNode,userEntryNode,createResponsesNode,responseOptionsNode;
    public String userEntryPanelTitle,createResponsesPanelTitle,weibullCheckerLabel,statsHelp,timeSeriesHelp;
    public String meanColName,stdDevColName,varColName,relStdDevColName,relStdDevPercentColName,goldCurveDisplay,noXValError,selectPlotsTitle,setGoldCurveButton;
	public String noGoldCurveDefinedError,selectGoldCurveStatus,selectActivityStatus,numberOfSegmentsLabel,updateComputedResponsesPrompt;

    public Image goldCurveImage;
    public ImageIcon addGridIcon,responseDataHandlerIcon;

    /**
    * Constructor
    */
    public GridResources()
    {
        try
        {
            setBundleName( GRID_BUNDLE );
			setResourceBaseClass(com.jdouglas.FusionAE.FusionAE.class);

            addGridMenu = getResourceString( ADD_GRID_MENU, "Add Grid..." );
            addGridTooltip = getResourceString( ADD_GRID_TOOLTIP, "Add Grid..." );
            addGridIcon = loadIcon( getResourceString( ADD_GRID_ICON, "images/editAddGrid.png" ) );
            responseDataHandlerMenu = getResourceString( RESPONSE_DATA_HANDLER_MENU, "Response Data Handler..." );
            responseDataHandlerTooltip = getResourceString( RESPONSE_DATA_HANDLER_TOOLTIP, "Launch Response Data Handler Tool." );
            responseDataHandlerIcon = loadIcon( getResourceString( RESPONSE_DATA_HANDLER_ICON, "images/chart.png" ) );

            buildGoldCurveTitle = getResourceString( BUILD_GOLD_CURVE_TITLE, "Build Gold Curve" );
            enterResponseNameLabel = getResourceString( ENTER_RESPONSE_NAME_LABEL, "Enter Response Name" );
            enterTimeSeriesLabel = getResourceString( ENTER_TIME_SERIES_LABEL, "Enter Time Series" );
            descriptiveStatisticsLabel = getResourceString( DESCRIPTIVE_STATISTICS_LABEL, "Descriptive Statistics" );
            numMeasurementsLabel = getResourceString( NUM_MEASUREMENTS_LABEL, "Number of measurements per time unit" );
            timeUnitsLabel = getResourceString( TIME_UNITS_LABEL, "Time Units" );
            totalTimePeriodLabel = getResourceString( TOTAL_TIME_PERIOD_LABEL, "Total Time Period" );
            numRepeatsLabel = getResourceString( NUM_REPEATS_LABEL, "Number of Repeats" );
            repeatRunLabel = getResourceString( REPEAT_RUN_LABEL, "Repeat Run #" );
            timeSeriesColLabel = getResourceString( TIME_SERIES_COL_LABEL, "T" );
            createResponsesTitle = getResourceString( CREATE_RESPONSES_TITLE, "Profile Similarity Metrics" );
            f1CheckerLabel = getResourceString( F1_LABEL, "f1 (Difference Factor)" );
            f2CheckerLabel = getResourceString( F2_LABEL, "f2 (Similarity Factor)" );
            responseAtXLabel = getResourceString( RESPONSE_AT_X_LABEL, "Response at X=" );
            yValAtXLabel = getResourceString( Y_VAL_AT_X_LABEL, "Y value at X=" );
            numResponsesLabel = getResourceString( NUM_RESPONSES_LABEL, "Number of Responses" );
            includeInMainGridLabel = getResourceString( INCLUDE_IN_MAIN_DESIGN_LABEL, "Include Responses in Main Grid" );
            f1ColTitle = getResourceString( F1_COL_TITLE, "f1 (Difference Factor)" );
            f2ColTitle = getResourceString( F2_COL_TITLE, "f2 (Similarity Factor)" );
            weibullShapeColTitle = getResourceString( WEIBULL_SHAPE_COL_TITLE, "Weibull Shape Delta" );
            weibullScaleColTitle = getResourceString( WEIBULL_SCALE_COL_TITLE, "Weibull Scale Delta" );
			weibullShapeColTitleVB = getResourceString( WEIBULL_SHAPE_COL_TITLE_VB, "Weibull Shape Delta" );
			weibullScaleColTitleVB = getResourceString( WEIBULL_SCALE_COL_TITLE_VB, "Weibull Scale Delta" );
            rrWizardTitle = getResourceString( RR_WIZARD_TITLE, "Response Reduction Wizard" );
            meanLabel = getResourceString( MEAN_LABEL, "Mean" );
            varianceLabel = getResourceString( VARIANCE_LABEL, "Variance" );
            stdDevLabel = getResourceString( STD_DEV_LABEL, "Standard Deviation (SD)" );
            relStdDevLabel = getResourceString( REL_STD_DEV_LABEL, "Relative Standard Deviation (RSD)" );
            relStdDevPercentLabel = getResourceString( REL_STD_DEV_PERCENT_LABEL, "%RSD" );
            currentDataPanelTitle = getResourceString( CURRENT_DATA_PANEL_TITLE, "Select the plot for use as the Gold Curve." );
            currentPlotLabel = getResourceString( CURRENT_PLOT_LABEL, "Current Plot" );
            updateButton = getResourceString( UPDATE_BUTTON, "Update" );
            runNumberLabel = getResourceString( IGrid.RUN_NUMBER, "Run Number" );
            endPtLabel = getResourceString( END_PT_LABEL, "Endpoint X Value" );
            targetLabel = getResourceString( TARGET_LABEL, "Response Target" );
            curveTypeLabel = getResourceString( CURVE_TYPE_LABEL, "Curve Type" );
            invalidEndPtError = getResourceString( INVALID_END_PT_ERROR, "A number must be entered for the Endpoint Value and Target." );
            addGridWizardTitle = getResourceString( ADD_GRID_WIZARD_TITLE, "Add Grid Wizard" );
            timeSeriesEditorTitle = getResourceString( TIME_SERIES_EDITOR_TITLE, "Time Series Response Reduction" );
            timeSeriesWorkAreaTitle = getResourceString( TIME_SERIES_WORK_AREA_TITLE, "Work Area" );
            plotOptionsPanelTitle = getResourceString( PLOT_OPTIONS_PANEL_TITLE, "Plot Options" );
            selectRunsButton = getResourceString( SELECT_RUNS_BUTTON, "Select Runs" );
            editRunsButton = getResourceString( EDIT_RUNS_BUTTON, "Edit Runs" );
            rrToolsNode = getResourceString( RR_TOOLS_NODE, "Response Reduction Tools" );
            defineTargetProfileNode = getResourceString( DEFINE_TARGET_PROFILE_NODE, "Define Target Profile" );
            buildCurveNode = getResourceString( BUILD_CURVE_NODE, "Build Curve" );
            currentDataNode = getResourceString( CURRENT_DATA_NODE, "Current Data" );
            userEntryNode = getResourceString( USER_ENTRY_NODE, "User Entry" );
            createResponsesNode = getResourceString( CREATE_RESPONSES_NODE, "Create Responses for Analysis" );
            responseOptionsNode = getResourceString( RESPONSE_OPTIONS_NODE, "Response Options" );
            userEntryPanelTitle = getResourceString( USER_ENTRY_PANEL_TITLE, "Enter Gold Curve Data" );
            createResponsesPanelTitle = getResourceString( CREATE_RESPONSES_PANEL_TITLE, "Create Responses" );
            weibullCheckerLabel = getResourceString( WEIBULL_CHECKER_LABEL, "Weibull Distribution" );
            meanColName = getResourceString( MEAN_COL_NAME, "Mean" );
            stdDevColName = getResourceString( STD_DEV_COL_NAME, "Standard Deviation" );
            varColName = getResourceString( VAR_COL_NAME, "Variance" );
            relStdDevColName = getResourceString( REL_STD_DEV_COL_NAME, "Relative Standard Deviation" );
            relStdDevPercentColName = getResourceString( REL_STD_DEV_PERCENT_COL_NAME, "%Relative Standard Deviation" );
            goldCurveDisplay = getResourceString( IGrid.GOLD_CURVE, "Gold Curve" );
            statsHelp = getResourceString( STATS_HELP, "Please select the statistics you wish calculated." );
            timeSeriesHelp = getResourceString( TIME_SERIES_HELP, "Please define the gold curve and the type of statistics to be generated." );
            selectPlotsTitle = getResourceString( SELECT_PLOTS_TITLE, "Select the plots to graph." );
            setGoldCurveButton = getResourceString( SET_GOLD_CURVE_BUTTON, "Set Gold Curve" );

            noXValError = getResourceString( NO_X_VAL_ERROR, "There must be an X value specified." );

			noGoldCurveDefinedError = getResourceString( NO_GOLD_CURVE_DEFINED_ERROR, "A Gold Curve must be defined in order to complete this operation." );
			selectGoldCurveStatus = getResourceString( SELECT_GOLD_CURVE_STATUS, "A Gold Curve must be defined in order for this activity to become available" );
			selectActivityStatus = getResourceString( SELECT_ACTIVITY_STATUS, "Please select a sub-activity." );
			numberOfSegmentsLabel = getResourceString( NUMBER_OF_SEGMENTS_LABEL, "Number of Segments" );
			updateComputedResponsesPrompt = getResourceString( UPDATE_COMPUTED_RESPONSES_PROMPT, "The computed responses will be updated. Do you wish to continue?" );
                                                                                            

            goldCurveImage = loadImage( getResourceString(GOLD_CURVE_IMAGE, "images/curve.png") );
        }
        catch(Exception e) 
        {
            FusionUtils.logError( MODULE_NAME, "failed", e );
        }
    }
}
