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
#include "RemoteFileTest.h"
#include "system/RemoteFile.h"
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QCoreApplication>
#include "system/LocalHost.h"


namespace hic {

CPPUNIT_TEST_SUITE_REGISTRATION( RemoteFileTest );
/**
 * @details Constructs a RemoteFileTest object.
 */
RemoteFileTest::RemoteFileTest()
    : CppUnit::TestFixture()
{
}

/**
 * @details Destroys the RemoteFileTest object.
 */
RemoteFileTest::~RemoteFileTest()
{
}

void RemoteFileTest::setUp()
{
    filename = QDir::tempPath() + "/testfile_" + QString().setNum( QCoreApplication::applicationPid() );
}

void RemoteFileTest::tearDown()
{
    _cleanFile(filename);
}

void RemoteFileTest::test_localhost()
{
     LocalHost localhost;
     QString string("some text\n");
     {
         /*
          * Use Case:
          *     Attempt to open a file without a filename
          * Expect:
          *     throw with a suitable message
          */
         RemoteFile f(localhost);
         CPPUNIT_ASSERT_THROW( f.open(QIODevice::WriteOnly), QString );
         CPPUNIT_ASSERT_THROW( f.open(QIODevice::ReadOnly), QString );
     }
     try
     {
         /*
          * Use Case:
          *     create a file on the local host
          * Expect:
          *     a local file to be generated
          */
         RemoteFile f(localhost);
         {
             QFile file(filename);
             CPPUNIT_ASSERT_MESSAGE( filename.toStdString().c_str(), ! file.exists() );
         }
         f.setFileName(filename);
         f.open(QIODevice::WriteOnly);
         f.write( string.toStdString().c_str() , string.size() );
         fsync( f.handle() ); // make sure everything is flushed to the disk
         f.close();
         {
             // verify the file exists
             QFile file(filename);
             CPPUNIT_ASSERT(file.exists());
             CPPUNIT_ASSERT_EQUAL((long)string.size(), (long)file.size());
         }
         // try to read the file back
         /* 
         RemoteFile f2(localhost);
         f2.setFileName(filename);
         CPPUNIT_ASSERT( f2.open(QIODevice::ReadOnly) );
         CPPUNIT_ASSERT_EQUAL((long)string.size(), (long)f2.size());
         QTextStream in(&f2);
         QString line = in.readLine();
         CPPUNIT_ASSERT_EQUAL( string.toStdString(), line.toStdString() );
         */
     }
     catch( QString& s ) {
         CPPUNIT_FAIL( s.toStdString() );
         _cleanFile(filename);
     }
}

void RemoteFileTest::_cleanFile(const QString& file)
{
    QFile f(file);
    if( f.exists() )
        f.remove();
}

} // namespace hic

