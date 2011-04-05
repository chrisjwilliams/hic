#ifndef TESTGENERATOR_H
#define TESTGENERATOR_H


#include "AbstractGenerator.h"

/**
 * @file TestGenerator.h
 */

namespace hic {

/**
 * @class TestGenerator
 * 
 * @brief
 * 
 * @details
 * 
 */
class TestGenerator : public AbstractGenerator
{
    public:
        /// TestGenerator constructor.
        TestGenerator();

        /// TestGenerator destructor.
        ~TestGenerator();

        Procedure setState(const hic::State&) const;

    private:
};

} // namespace hic

#endif // TESTGENERATOR_H 
