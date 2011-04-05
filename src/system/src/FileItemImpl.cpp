#include "FileItemImpl.h"
#include "Report.h"
#include <QFile>
#include <QTextStream>


namespace hic {


/**
 * @details Constructs a FileItemImpl object.
 */
FileItemImpl::FileItemImpl(const Platform& p)
    : ProcedureItemImpl( p )
{
}

/**
 * @details Destroys the FileItemImpl object.
 */
FileItemImpl::~FileItemImpl()
{
}

bool FileItemImpl::isValid() const
{
    // N.B. we allow zero length files and temporary unnamed files
    return ( _filename != "" ) ||  _content.size() > 0; 
}

void FileItemImpl::append(const QString& s )
{
    _content += s;
}

void FileItemImpl::setFilename( const QString& name )
{
    _filename = name;
}

Report FileItemImpl::exec() const
{
    Report r;

    QString filename = _filename;
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        r.addErrorMessage("unable to open file for writing. filename=\"" + filename + "\" : " + file.errorString() );
    }
    else {
        QTextStream out(&file);
        out << _content;
        file.close();
    }
    return r;
}

} // namespace hic
