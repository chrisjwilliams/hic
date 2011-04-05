#ifndef PROCEDUREITEM_H
#define PROCEDUREITEM_H

#include <boost/shared_ptr.hpp>
#include <QString>

/**
 * 
 * @file ProcedureItem.h
 */

namespace hic {
    class Report;
    class ProcedureItemImpl;
    class Platform;

/**
 * @class ProcedureItem
 * 
 * @brief
 *   Base class for items to be inserted into a procedure
 * @details
 *   Wraps an implementation pointer for ease of copying into 
 *   containers etc.
 *
 *   This requires any subclasses to instantiate two
 *   new classes:
 *
 *   One that inherits form ProcedureItemImpl to do the work,
 *   and another one that inherits from this class and instantiats
 *   the  implemenation object in _impl
 * 
 */
class ProcedureItem
{
    public:
        /// ProcedureItem constructor.
        ProcedureItem( const Platform& platform );

        /// ProcedureItem destructor.
        virtual ~ProcedureItem();

        /// execute the procedure
        Report exec() const;

        /// returns true if the item has any content
        bool isValid() const;

        /// return the platform
        //
        /*
        const Platform& platform() const { 
            std::cout << "ProcedureItem:platform: " << _platform.name().toStdString() << std::endl;
            return _platform; }
            */

        /// returns a message suitable for status reporting
        //  that describes the procedure
        const QString& statusMessage() const { return _statusMessage; };

        /// set the message to be returned by statusMessage() 
        void setStatusMessage(const QString& msg) { _statusMessage = msg; }

    private:
        QString _statusMessage;

    protected:
        boost::shared_ptr<ProcedureItemImpl> _impl; // pointer to object that does the work


};

} // namespace hic

#endif // PROCEDUREITEM_H 
