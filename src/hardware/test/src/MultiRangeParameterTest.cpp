/*
 * Copyright (c) 2011, The University of Oxford
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the University of Oxford nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include "MultiRangeParameterTest.h"
#include "MultiRangeParameter.h"
#include "Range.h"
#include "system/Report.h"


namespace hic {

CPPUNIT_TEST_SUITE_REGISTRATION( MultiRangeParameterTest );
/**
 * @details Constructs a MultiRangeParameterTest object.
 */
MultiRangeParameterTest::MultiRangeParameterTest()
    : CppUnit::TestFixture()
{
}

/**
 * @details Destroys the MultiRangeParameterTest object.
 */
MultiRangeParameterTest::~MultiRangeParameterTest()
{
}

void MultiRangeParameterTest::setUp()
{
}

void MultiRangeParameterTest::tearDown()
{
}

void MultiRangeParameterTest::test_setMaximum()
{
    QString name("testparam");
    QString doc("test documentation");
    { // Use case:
      // set maximum less than current min
      // single contiguous range
      MultiRangeParameter<float> p(name,doc);
      QString s("-10..25");
      Report r = p.setFromString(s);
      CPPUNIT_ASSERT( r.success() );
      p.setMaximum(-12.5);
      CPPUNIT_ASSERT_EQUAL( 1, p.ranges().size() );
      CPPUNIT_ASSERT_EQUAL( (float)-12.5, p.min() );
      CPPUNIT_ASSERT_EQUAL( (float)-12.5, p.max() );
    }
    { // Use case:
      // set maximum > than current min < current max
      // single range
      MultiRangeParameter<float> p(name,doc);
      QString s("-10..25");
      Report r = p.setFromString(s);
      CPPUNIT_ASSERT( r.success() );
      p.setMaximum(12.5);
      CPPUNIT_ASSERT_EQUAL( 1, p.ranges().size() );
      CPPUNIT_ASSERT_EQUAL( (float)-10.0, p.min() );
      CPPUNIT_ASSERT_EQUAL( (float)12.5, p.max() );
    }
    { // Use case:
      // set maximum > than current max
      // single range
      MultiRangeParameter<float> p(name,doc);
      QString s("-10..25");
      Report r = p.setFromString(s);
      CPPUNIT_ASSERT( r.success() );
      p.setMaximum(122.5);
      CPPUNIT_ASSERT_EQUAL( 1, p.ranges().size() );
      CPPUNIT_ASSERT_EQUAL( (float)-10.0, p.min() );
      CPPUNIT_ASSERT_EQUAL( (float)122.5, p.max() );
    }
}

void MultiRangeParameterTest::test_setMinimum()
{
    QString name("testparam");
    QString doc("test documentation");
    { // Use case:
      // set minimum less than current min
      // single contiguous range
      MultiRangeParameter<float> p(name,doc);
      QString s("-10..25");
      Report r = p.setFromString(s);
      CPPUNIT_ASSERT( r.success() );
      p.setMinimum(-12.5);
      CPPUNIT_ASSERT_EQUAL( 1, p.ranges().size() );
      CPPUNIT_ASSERT_EQUAL( (float)-12.5, p.min() );
      CPPUNIT_ASSERT_EQUAL( (float)25.0, p.max() );
    }
    { // Use case:
      // set minimum > than current min < current max
      MultiRangeParameter<float> p(name,doc);
      QString s("-10..25");
      Report r = p.setFromString(s);
      CPPUNIT_ASSERT( r.success() );
      p.setMinimum(12.5);
      CPPUNIT_ASSERT_EQUAL( 1, p.ranges().size() );
      CPPUNIT_ASSERT_EQUAL( (float)12.5, p.min() );
      CPPUNIT_ASSERT_EQUAL( (float)25.0, p.max() );
    }
    { // Use case:
      // set minimum > than current min > current max
      // expect min = max = new value
      MultiRangeParameter<float> p(name,doc);
      QString s("-10..25");
      Report r = p.setFromString(s);
      CPPUNIT_ASSERT( r.success() );
      p.setMinimum(122.5);
      CPPUNIT_ASSERT_EQUAL( 1, p.ranges().size() );
      CPPUNIT_ASSERT_EQUAL( (float)122.5, p.min() );
      CPPUNIT_ASSERT_EQUAL( (float)122.5, p.max() );
    }
}

void MultiRangeParameterTest::test_stringsInt()
{
    QString name("testparam");
    QString doc("test documentation");
    { // Use case:
      // correct single range specified
      // no range restrictions applied
      // Expect:
      // A valid range object
      QString s("-10..25");
      MultiRangeParameter<int> p(name,doc);
      Report r = p.setFromString(s);
      CPPUNIT_ASSERT( r.success() );
    }
    { // Use case:
      // multiple correct ranges specified
      // no range restrictions applied
      // Expect:
      // A valid range object
      QString s("-10..25,30,35..40");
      MultiRangeParameter<int> p(name,doc);
      Report r = p.setFromString(s);
      CPPUNIT_ASSERT( r.success() );
      CPPUNIT_ASSERT_EQUAL( 3, p.ranges().size() );
      //CPPUNIT_ASSERT_EQUAL( "-10", p.minimum().toStdString().c_str() );
      //CPPUNIT_ASSERT_EQUAL( "40", p.maximum().toStdString().c_str() );
    }
    { // Use case:
      // multiple correct ranges specified, and one bad syntax
      // no range restrictions applied
      // Expect:
      // A invalid range object
      QString s("-10..25,30,35..40,abcde");
      MultiRangeParameter<int> p(name,doc);
      Report r = p.setFromString(s);
      CPPUNIT_ASSERT( ! r.success() );
      CPPUNIT_ASSERT_EQUAL( 0, p.ranges().size() );
    }
    { // Use case:
      // multiple correct range sytax specified
      // mutliple allowed ranges set that cover these ranges
      // Expect:
      // A good report 
      QString s("-10..25,30,35..40");
      MultiRangeParameter<int> p(name,doc);
      Range<int> r1(-10,33);
      Range<int> r2(35,43);
      QList<Range<int> > l; l << r1 << r2;
      p.setAllowableValues( l );
      Report r = p.setFromString(s);
      CPPUNIT_ASSERT(  r.success() );
      CPPUNIT_ASSERT_EQUAL( 3, p.ranges().size() );
    }
    { // Use case:
      // multiple correct range sytax specified
      // last range is outside of allowed bounds
      // Expect:
      // A bad report 
      QString s("-10..25,30,35..40");
      MultiRangeParameter<int> p(name,doc);
      Range<int> r1(-10,35);
      QList<Range<int> > l; l << r1;
      p.setAllowableValues( l );
      Report r = p.setFromString(s);
      CPPUNIT_ASSERT( ! r.success() );
      CPPUNIT_ASSERT_EQUAL( 0, p.ranges().size() );
    }
}

} // namespace hic
