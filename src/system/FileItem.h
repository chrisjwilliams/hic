#ifndef FILEITEM_H
#define FILEITEM_H
#include "ProcedureItem.h"


/**
 * @file FileItem.h
 */

namespace hic {

/**
 * @class FileItem
 * 
 * @brief
 *   A ProcedureItem to create a file on the specifed platform
 * @details
 * 
 */
class FileItem : public ProcedureItem
{
    public:
        /// FileItem constructor.
        FileItem(const Platform& platform);

        /// FileItem destructor.
        ~FileItem();

        /// adds content to the file
        void append( const QString& );

        /// set a specific filename to be created
        void setFilename( const QString& name );

    private:
};

} // namespace hic

#endif // FILEITEM_H 
