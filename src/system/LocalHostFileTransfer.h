#ifndef LOCALHOSTFILETRANSFER_H
#define LOCALHOSTFILETRANSFER_H


#include "AbstractFileTransfer.h"

/**
 * @file LocalHostFileTransfer.h
 */

namespace hic {

/**
 * @class LocalHostFileTransfer
 * 
 * @brief
 * 
 * @details
 * 
 */
class LocalHostFileTransfer : public AbstractFileTransfer
{
    public:
        /// LocalHostFileTransfer constructor.
        LocalHostFileTransfer();

        /// LocalHostFileTransfer destructor.
        ~LocalHostFileTransfer();

        // methods requiring implementation
        virtual Report getFile(const QString& remote_filename, const QString& local_filename );
        virtual Report putFile(const QString& local_filename, const QString& remote_filename );

    private:
};

} // namespace hic

#endif // LOCALHOSTFILETRANSFER_H 
