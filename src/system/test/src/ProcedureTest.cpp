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
#include "ProcedureTest.h"
#include "Procedure.h"
#include "system/Report.h"
#include "system/test/TestProcedureItem.h"


namespace hic {

CPPUNIT_TEST_SUITE_REGISTRATION( ProcedureTest );
/**
 * @details Constructs a ProcedureTest object.
 */
ProcedureTest::ProcedureTest()
    : CppUnit::TestFixture()
{
}

/**
 * @details Destroys the ProcedureTest object.
 */
ProcedureTest::~ProcedureTest()
{
}

void ProcedureTest::setUp()
{
}

void ProcedureTest::tearDown()
{
}

void ProcedureTest::test_empty()
{
    {
        // Use Case:
        // Empty Procedure
        // Expect
        // return invalid and do nothing on a call to exec()
        Procedure p;
        CPPUNIT_ASSERT( ! p.isValid() );
        Report r = p.exec();
        CPPUNIT_ASSERT( r.success() );
    }
}

void ProcedureTest::test_appendProcedure()
{
    {
        // Use Case:
        // Add an invalid Procedure
        // Expect:
        // No merge to take place, and status of orig to remain unchanged
        Procedure p;
        bool status = p.isValid();
        Procedure p2;
        CPPUNIT_ASSERT( ! p2.isValid() );
        p.appendProcedure(p2);
        CPPUNIT_ASSERT_EQUAL( status, p.isValid() );
    }
    {
        // Use Case:
        // Add a valid Procedure to an empty Procedure
        // Expect:
        // Merge to take place, and Procedure to become valid
        Procedure p;
        Procedure p2;
        TestProcedureItem testItem;
        p2.appendProcedure(testItem);
        CPPUNIT_ASSERT( p2.isValid() );
        p.appendProcedure( p2 );
        CPPUNIT_ASSERT( p.isValid() );
        // Use Case:
        // call exec on a valid procedure - no errors
        // Expect:
        // success report
        Report r = p.exec();
        CPPUNIT_ASSERT( r.success() );
    }
}
} // namespace hic
