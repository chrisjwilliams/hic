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
#include "RangeTest.h"
#include "Range.h"


namespace hic {

CPPUNIT_TEST_SUITE_REGISTRATION( RangeTest );
/**
 * @details Constructs a RangeTest object.
 */
RangeTest::RangeTest()
    : CppUnit::TestFixture()
{
}

/**
 * @details Destroys the RangeTest object.
 */
RangeTest::~RangeTest()
{
}

void RangeTest::setUp()
{
}

void RangeTest::tearDown()
{
}

void RangeTest::test_strings()
{
    // Use case:
    // String has a good range definition
    // Expect:
    // valid Range with correct min and max
    {
        Range<int> r;
        QString s("-10..24");
        r.fromString(s,"..");
        CPPUNIT_ASSERT( r.isValid() );
        CPPUNIT_ASSERT_EQUAL( -10, r.min() );
        CPPUNIT_ASSERT_EQUAL( 24, r.max() );
        CPPUNIT_ASSERT_EQUAL( s.toStdString(), r.toString("..").toStdString() );
    }

    // Use case:
    // String has bad characters
    // Expect:
    // not valid Range
    {
        Range<int> r;
        QString s("abc..24");
        r.fromString(s,"..");
        CPPUNIT_ASSERT( ! r.isValid() );
    }

    // Use case:
    // String has bad seperator
    // Expect:
    // not valid Range
    {
        Range<int> r;
        QString s("10...24");
        r.fromString(s,"..");
        CPPUNIT_ASSERT( ! r.isValid() );
    }
}

} // namespace hic
