#include "FileItem.h"
#include "FileItemImpl.h"

namespace hic {


/**
 * @details Constructs a FileItem object.
 */
FileItem::FileItem(const Platform& platform)
    : ProcedureItem(platform)
{
    _impl.reset( new FileItemImpl( platform ) );
    setStatusMessage( QString("creating file on platform %1")
                            .arg(platform.name()) ); // default status message
}

/**
 * @details Destroys the FileItem object.
 */
FileItem::~FileItem()
{
}

/**
 * @details append text content to the file
 */
void FileItem::append( const QString& content )
{
    static_cast<FileItemImpl*>(_impl.get())->append(content);
}

void FileItem::setFilename( const QString& name )
{
    static_cast<FileItemImpl*>(_impl.get())->setFilename(name);
}

} // namespace hic
