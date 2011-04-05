class FileItem
!!!176868.cpp!!!	FileItem(in platform : Platform)
    _impl.reset( new FileItemImpl( platform ) );
    setStatusMessage( QString("creating file on platform %1")
                            .arg(platform.name()) ); // default status message
!!!177124.cpp!!!	append(in content : QString) : void
    static_cast<FileItemImpl*>(_impl.get())->append(content);
!!!177252.cpp!!!	setFilename(in name : QString) : void
    static_cast<FileItemImpl*>(_impl.get())->setFilename(name);
