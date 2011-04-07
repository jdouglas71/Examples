package com.jdouglas.framework.enums.data;

/**
* FusionOperationID. An Enumeration for Operations in Fusion AE. Corresponds to the FusionOperationID enum defined in
* SMXExt.IActivityControl.
*
* @author Jason Douglas 2/7/08
* Copyright © 2006-2010 S-Matrix Corporation. All rights reserved.
*/

public enum FusionOperationID
{       
    /** Unknown (no-op)*/
    UNKNOWN(-1),
    /** Select Instrument */
	//OP_SELECT_INSTRUMENT(0),
    OP_INSTRUMENT_CONFIG(0),  //Backward compat 
    /** Review */
    OP_REVIEW(1),
    /** Approve */
    OP_APPROVE(2),
    /** Authenticate */
    OP_AUTHENTICATE(3),
    /** Error */
    OP_ERROR(4),
    /** Reject Operation */
    OP_REJECT(5),
    /** Save */
    OP_SAVE(6),
    /** Save as */
    OP_SAVE_AS(7),
    /** New File */
    OP_NEW_FILE(8),
    /** Print */
    OP_PRINT(9),
    /** Experiment Setup */
    OP_EXPERIMENT_SETUP(10),
    /** Generate Design */
    OP_GENERATE_DESIGN(20),
    /** Standards Bracketing */
    OP_STANDARDS_BRACKETING(30),
    /** Export Design */
    OP_EXPORT_DESIGN(40),
    /** Matrix Master */
    OP_MATRIX_MASTER(50),
    /** Import Responses */
    OP_IMPORT_RESPONSES(60),
    /** Enter Responses */
    OP_ENTER_RESPONSES(70),
    /** Capability Robustness */
    OP_CAPABILITY_ROBUSTNESS(71),
	/** Add Testing Design */
	OP_ADD_TESTING_DESIGN(72),
	/** Remove Testing Design */
	OP_REMOVE_TESTING_DESIGN(73),
    /** Enter Sample Preperation */
    OP_ENTER_SAMPLE_PREP(80),
    /** Analyze Data */
    OP_ANALYZE_DATA(90),
    /** Analyze Compounds */
    OP_ANALYZE_COMPOUNDS(91),
    /** Model Options */
    OP_MODEL_OPTIONS(100),
    /** Add Model Terms */
    OP_ADD_MODEL_TERMS(110),
    /** Optimize Responses */
    OP_OPTIMIZE_RESPONSES(120),
    /** Export Optimizer */
    OP_EXPORT_OPTIMZER(130),
    /** Overlay Graphics */
    OP_OVERLAY_GRAPHICS(140),
    /** Generate Predictions */
    OP_GENERATE_PREDICTIONS(150),
    /** Export Point Predictions */
    //OP_EXPORT_POINT_PREDICTIONS(160),
	OP_EXPORT_USER_SETTINGS(160), //Backward compat 
    /** Import Images */
    OP_IMPORT_IMAGES(169),
    /** Fusion Reporter */
    OP_FUSION_REPORTER(170),
    /** Generate Audit Log */
    //OP_GENERATE_AUDIT_LOG(180),
	OP_AUDIT_LOG(180), //Backward compat
    /** Save as Template */
    OP_SAVE_AS_TEMPLATE(190),
    /** Fusion Administrator Generate Audit Log */
    OP_FA_AUDIT_LOG(200),
    /** Fusion Administrator Save */
    OP_FA_SAVE(201),
    /** Fusion Administrator Import FA Data */
    OP_FA_IMPORT(202),
    /** Fusion Administrator Export FA Data */
    OP_FA_EXPORT(203),
    /** Fusion Administrator Import Licenses */
    OP_FA_IMPORT_LICENSES(204),
    /** Fusion Administrator Import Instruments from Galaxie */
    OP_FA_IMPORT_FROM_GALAXIE(205),
    /** Print as Editable PDF */
    OP_PRINT_AS_EDITABLE_PDF(210),
    /** Backward Compatable */
    OP_BACKWARD_COMPATIBILITY(220);

    /** Maintain compatability with the prior values for save and restore */
    private int id; 

    /**
    * Constructor
    * @param _id int
    */
    private FusionOperationID(int _id) 
    {
        id = _id;
    }

    /**
    * Gets the id. 
    * @return int The id.
    */
    public int getID()
    {
        return id;
    }

    /**
    * Get the enum value that corresponds to the given Integer. We need this because we store the value
    * as an integer. 
    *
    * @param id Integer (take advantage of autoboxing)
    * @return FusionOperationID
    */
    public static FusionOperationID getFusionOperationID(Integer id)
    {
        switch( id.intValue() )
        {
            case -1:
                return UNKNOWN;
            case 0:
                return OP_INSTRUMENT_CONFIG;
            case 1:
                return OP_REVIEW;
            case 2:
                return OP_APPROVE;
            case 3:
                return OP_AUTHENTICATE;
            case 4:
                return OP_ERROR;
            case 5:
                return OP_REJECT;
            case 6:
                return OP_SAVE;
            case 7:
                return OP_SAVE_AS;
            case 8:
                return OP_NEW_FILE;
            case 9:
                return OP_PRINT;
            case 10:
                return OP_EXPERIMENT_SETUP;
            case 20:
                return OP_GENERATE_DESIGN;
            case 30:
                return OP_STANDARDS_BRACKETING;
            case 40:
                return OP_EXPORT_DESIGN;
            case 50:
                return OP_MATRIX_MASTER;
            case 60:
                return OP_IMPORT_RESPONSES;
            case 70:
                return OP_ENTER_RESPONSES;
            case 71:
                return OP_CAPABILITY_ROBUSTNESS;
            case 80:
                return OP_ENTER_SAMPLE_PREP;
            case 90:
                return OP_ANALYZE_DATA;
            case 91:
                return OP_ANALYZE_COMPOUNDS;
            case 100:
                return OP_MODEL_OPTIONS;
            case 110:
                return OP_ADD_MODEL_TERMS;
            case 120:
                return OP_OPTIMIZE_RESPONSES;
            case 130:
                return OP_EXPORT_OPTIMZER;
            case 140:
                return OP_OVERLAY_GRAPHICS;
            case 150:
                return OP_GENERATE_PREDICTIONS;
            case 160:
                //return OP_EXPORT_POINT_PREDICTIONS;
				return OP_EXPORT_USER_SETTINGS;
            case 169:
                return OP_IMPORT_IMAGES;
            case 170:
                return OP_FUSION_REPORTER;
            case 180:
                //return OP_GENERATE_AUDIT_LOG;
				return OP_AUDIT_LOG;
            case 190:
                return OP_SAVE_AS_TEMPLATE;
            case 200:
                return OP_FA_AUDIT_LOG;
            case 201:
                return OP_FA_SAVE;
            case 202:
                return OP_FA_IMPORT;
            case 203:
                return OP_FA_EXPORT;
            case 204:
                return OP_FA_IMPORT_LICENSES;
            case 205:
                return OP_FA_IMPORT_FROM_GALAXIE;
            case 210:
                return OP_PRINT_AS_EDITABLE_PDF;
            case 220:
                return OP_BACKWARD_COMPATIBILITY;
            default:
                return UNKNOWN;
        }
    }
};

