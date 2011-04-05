#ifndef SSH_FILETRANSFER_H
#define SSH_FILETRANSFER_H


#include "AbstractFileTransfer.h"

/**
 * @file SSH_FileTransfer.h
 */

namespace hic {

/**
 * @class SSH_FileTransfer
 * 
 * @brief
 *   plug in module for transferring files via the ssh protocol
 * @details
 *   currently uses the local command line scp clients
 */
class SSH_FileTransfer : public AbstractFileTransfer
{
    public:
        /// SSH_FileTransfer constructor.
        SSH_FileTransfer();

        /// SSH_FileTransfer destructor.
        ~SSH_FileTransfer();

        /// set the full path to the binary scp client
        void setClient(const QString& client) { _scp = client; };

        /// set the user to connect with
        void setUser(const QString& user);

        // methods requiring implementation
        virtual Report getFile(const QString& remote_filename, const QString& local_filename );
        virtual Report putFile(const QString& local_filename, const QString& remote_filename );

    private:
        QString _scp; // full path to the scp client
        QString _user;
};

} // namespace hic

#endif // SSH_FILETRANSFER_H 
