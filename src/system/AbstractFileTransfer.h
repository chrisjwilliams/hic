#ifndef ABSTRACTFILETRANSFER_H
#define ABSTRACTFILETRANSFER_H
#include <QString>
#include "AbstractAgent.h"

/**
 * @file AbstractFileTransfer.h
 */

namespace hic {

/**
 * @class AbstractFileTransfer
 * 
 * @brief
 * 
 * @details
 * 
 */
class AbstractFileTransfer : public AbstractAgent
{
    public:
        /// AbstractFileTransfer constructor.
        AbstractFileTransfer();

        /// AbstractFileTransfer destructor.
        virtual ~AbstractFileTransfer();


        /// get a file from the remote system
        virtual Report getFile(const QString& remote_filename, const QString& local_filename ) = 0;

        /// put a file on the remote system
        virtual Report putFile(const QString& local_filename, const QString& remote_filename ) = 0;

    private:
};

} // namespace hic

#endif // ABSTRACTFILETRANSFER_H 
