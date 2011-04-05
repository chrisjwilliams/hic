class FileItemImpl
!!!177892.cpp!!!	isValid() : bool
    // N.B. we allow zero length files and temporary unnamed files
    return ( _filename != "" ) ||  _content.size() > 0; 
!!!177764.cpp!!!	append(in s : QString) : void
    _content += s;
!!!177636.cpp!!!	setFilename(in name : QString) : void
    _filename = name;
!!!178020.cpp!!!	exec() : Report
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
