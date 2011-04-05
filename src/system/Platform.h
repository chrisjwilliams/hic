#ifndef PLATFORM_H
#define PLATFORM_H

#include <QObject>
#include <QList>
#include <QString>
#include <boost/shared_ptr.hpp>

/**
 * @file Platform.h
 */

namespace hic {
    class Report;
    class AbstractFileTransfer;
    class AbstractExecAgent;
    class Command;

/**
 * @class Platform
 * 
 * @brief
 *   Base class for Accessing different platforms
 * @details
 *   Inheriting class must call the
 *   setFileTransferAgent() method in its constructor
 * 
 */
class Platform : public QObject
{
    Q_OBJECT

    public:
        /// Platform constructor.
        Platform(const QString& name = "", QObject* parent = 0 );
        Platform(const Platform&);

        /// Platform destructor.
        virtual ~Platform();

        /// return a descriptive name for the platform
        const QString& name() const { return _name; }
        void setHostName(const QString& host) { _name = host; };

        /// execute the commands on the specified platform
        Report exec( const QList<Command>& ) const;

        /// methods to move files to/from the platform
        Report getFile(const QString& remote_filename, 
                       const QString& local_filename ) const;
        Report putFile(const QString& local_filename, 
                       const QString& remote_filename ) const;

    protected:
        void setFileTransferAgent(AbstractFileTransfer*); // must be called be inheriting class
        void setExecAgent(AbstractExecAgent*); // must be called be inheriting class

    private:
        boost::shared_ptr<AbstractFileTransfer>   _fileTransferAgent;
        boost::shared_ptr<AbstractExecAgent>      _execAgent;
        QString                                   _name;
};

} // namespace hic

#endif // PLATFORM_H 
