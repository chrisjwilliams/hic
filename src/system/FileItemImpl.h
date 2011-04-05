#ifndef FILEITEMIMPL_H
#define FILEITEMIMPL_H


#include "ProcedureItemImpl.h"
#include <QString>

/**
 * @file FileItemImpl.h
 */

namespace hic {

/**
 * @class FileItemImpl
 * 
 * @brief
 *   Implementaion of the FileItem Procedure item
 * @details
 * 
 */
class FileItemImpl : public ProcedureItemImpl
{
    public:
        /// FileItemImpl constructor.
        FileItemImpl(const Platform& );

        /// FileItemImpl destructor.
        ~FileItemImpl();

        /// set the name of the file
        // @details
        // if no file name is set then temporary
        // unique filename willl be generated
        void setFilename( const QString& name );

        /// add content to the file
        void append(const QString& );

        virtual bool isValid() const;
        virtual Report exec() const;

    private:
        QString _filename;
        QString _content;
};

} // namespace hic

#endif // FILEITEMIMPL_H 
