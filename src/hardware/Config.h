#ifndef CONFIG_H
#define CONFIG_H


#include "State.h"
#include "SingleParameter.h"
class QFile;
class QTextStream;

/**
 * @file Config.h
 */

namespace hic {

/**
 * @class Config
 * 
 * @brief
 *    A State corresponding to elementa of a configuration file
 * @details
 * 
 */
class Config : public State
{
    public:
        /// Config constructor.
        Config();

        /// Config destructor.
        ~Config();

        /// get a parameter from the configuration. if it does
        //  not exist it is created
        boost::shared_ptr<SingleParameter<QString> > getParam(
                const QString& group, 
                const QString& name, 
                const boost::shared_ptr<SingleParameter<QString> >& default_val);

        /// read in state froman XML file
        void fromXML(QFile& file);

        /// write out state as XML
        void toXML(QFile& file) const;
        void toXML(QTextStream& stream) const;

    private:
        /// not a normal state, use getParam to generate
        void appendGroup(const ParameterGroup& g) { State::appendGroup(g); };
};

} // namespace hic

#endif // CONFIG_H 
