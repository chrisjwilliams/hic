class RemoteFileTest
!!!188772.cpp!!!	setUp() : void
    filename = QDir::tempPath() + "/testfile_" + QString().setNum( QCoreApplication::applicationPid() );
!!!188900.cpp!!!	tearDown() : void
    _cleanFile(filename);
!!!189028.cpp!!!	test_localhost() : void
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
!!!189412.cpp!!!	_cleanFile(in file : QString) : void
    QFile f(file);
    if( f.exists() )
        f.remove();
