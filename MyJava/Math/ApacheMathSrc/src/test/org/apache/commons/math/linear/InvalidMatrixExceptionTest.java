/*
 * Copyright 2003-2004 The Apache Software Foundation.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package org.apache.commons.math.linear;

import junit.framework.TestCase;

/**
 * @version $Revision: 155427 $ $Date: 2005-02-26 06:11:52 -0700 (Sat, 26 Feb 2005) $
 */
public class InvalidMatrixExceptionTest extends TestCase {
    /**
     * 
     */
    public void testConstructor(){
        InvalidMatrixException ex = new InvalidMatrixException();
        assertNull(ex.getMessage());
    }
    
    /**
     * 
     */
    public void testConstructorMessage(){
        String msg = "message";
        InvalidMatrixException ex = new InvalidMatrixException(msg);
        assertEquals(msg, ex.getMessage());
    }
}
