#ifndef ABSTRACTGENERATOR_H
#define ABSTRACTGENERATOR_H

/**
 * @file AbstractGenerator.h
 */

namespace hic {
    class Procedure;
    class State;
    class LocalHost;

/**
 * @class AbstractGenerator
 * 
 * @brief
 *    Base class that represents a state generator plug-in.
 * @details
 *    The function of a generator is to produce the steps required
 *    to realise a specific state. This can be done either directly
 *    or indirectly via a Process object
 * 
 */
class AbstractGenerator
{
    public:
        /// AbstractGenerator constructor.
        AbstractGenerator();

        /// AbstractGenerator destructor.
        virtual ~AbstractGenerator();

        /// stop the state if it is active
        virtual Procedure stop() const;

        /// generates the necessary commands to realise the passed state
        virtual Procedure setState( const State& ) const = 0;

        /// returns a LocalHost platfrom
        LocalHost localhost() const;

    private:
};

} // namespace hic

#endif // ABSTRACTGENERATOR_H 
