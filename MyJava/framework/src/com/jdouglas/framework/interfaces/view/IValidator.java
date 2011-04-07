package com.jdouglas.framework.interfaces.view;

/**
* IValidator. The Validator!!! The validator is called via the ValidationSingleSelectionModel and allows
* the implementing object to validate its contents and prevent the selection from changing (by returning false). <br><br>
*
* JGD NOTE: It occurs to me that there are at least two "types" of validation, a panel\data model type and a global type. 
* JGD NOTE: The first type would be validate btwn the GOO layer and the data model, the second btwn the data model and 
* JGD NOTE: permanent storage. Some times you want both (e.g. commit's) but selection changes only requre the first type, 
* JGD NOTE: where making sure there's at least one administrator is of the second type... I need to refine the concept.
* JGD NOTE: But regardless I can use the params map to refine the validation if I need to. (The problem I'm trying to solve
* JGD NOTE: is preventing the user from deleting the last admin without validating the contents of the panel.)
* JGD NOTE: 3/3/05 <br><br>
* 
* @author Jason Douglas 9/10/03
* Copyright © 2004-2010 S-Matrix Corporation. All rights reserved.
*/

public interface IValidator
{
    /**
    * This call comes from a selection model. The params Map allows various information to be passed to the valiators. 
    * Returning false will cause the selection model from blocking the change of selection indices, so use the power wisely.
    * 
    * @param params Map<Object,Object> Constraints and other types of information necessary to validate.
    *
    * @return boolean True if the validation passed. 
    */
    public boolean validateContents(java.util.Map<Object,Object> params);
}
