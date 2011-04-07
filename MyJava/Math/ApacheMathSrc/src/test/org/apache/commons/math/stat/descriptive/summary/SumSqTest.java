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
package org.apache.commons.math.stat.descriptive.summary;

import junit.framework.Test;
import junit.framework.TestSuite;

import org.apache.commons.math.stat.descriptive.StorelessUnivariateStatisticAbstractTest;
import org.apache.commons.math.stat.descriptive.UnivariateStatistic;

/**
 * Test cases for the {@link SumOfSquares} class.
 * 
 * @version $Revision: 155427 $ $Date: 2005-02-26 06:11:52 -0700 (Sat, 26 Feb 2005) $
 */
public class SumSqTest extends StorelessUnivariateStatisticAbstractTest{

    protected SumOfSquares stat;
    
    /**
     * @param name
     */
    public SumSqTest(String name) {
        super(name);
    }

    public static Test suite() {
        TestSuite suite = new TestSuite(SumSqTest.class);
        suite.setName("SumSq Tests");
        return suite;
    }
    
    /* (non-Javadoc)
     * @see org.apache.commons.math.stat.descriptive.UnivariateStatisticAbstractTest#getUnivariateStatistic()
     */
    public UnivariateStatistic getUnivariateStatistic() {
        return new SumOfSquares();
    }

    /* (non-Javadoc)
     * @see org.apache.commons.math.stat.descriptive.UnivariateStatisticAbstractTest#expectedValue()
     */
    public double expectedValue() {
        return this.sumSq;
    }
    
    public void testSpecialValues() {
        SumOfSquares sumSq = new SumOfSquares();
        assertTrue(Double.isNaN(sumSq.getResult()));
        sumSq.increment(2d);
        assertEquals(4d, sumSq.getResult(), 0);
        sumSq.increment(Double.POSITIVE_INFINITY);
        assertEquals(Double.POSITIVE_INFINITY, sumSq.getResult(), 0);
        sumSq.increment(Double.NEGATIVE_INFINITY);
        assertEquals(Double.POSITIVE_INFINITY, sumSq.getResult(), 0);
        sumSq.increment(Double.NaN);
        assertTrue(Double.isNaN(sumSq.getResult())); 
        sumSq.increment(1);
        assertTrue(Double.isNaN(sumSq.getResult())); 
    }

}
