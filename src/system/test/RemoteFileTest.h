#ifndef REMOTEFILETEST_H
#define REMOTEFILETEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <QString>

/**
 * @file RemoteFileTest.h
 */

namespace hic {

/**
 * @class RemoteFileTest
 * 
 * @brief
 * 
 * @details
 * 
 */
class RemoteFileTest : public CppUnit::TestFixture
{
    public:
        CPPUNIT_TEST_SUITE( RemoteFileTest );
        CPPUNIT_TEST( test_localhost );
        CPPUNIT_TEST_SUITE_END();

    public:
        void setUp();
        void tearDown();

        // Test Methods
        void test_localhost();

    public:
        /// RemoteFileTest constructor.
        RemoteFileTest();

        /// RemoteFileTest destructor.
        ~RemoteFileTest();

    private:
        QString filename;
        void _cleanFile(const QString& file);
};

} // namespace hic

#endif // REMOTEFILETEST_H 
