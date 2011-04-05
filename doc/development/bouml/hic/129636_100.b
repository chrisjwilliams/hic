class Config
!!!131300.cpp!!!	getParam(in group : QString, in name : QString, in default_val : boost::shared_ptr<SingleParameter<QString> >) : boost::shared_ptr<SingleParameter<QString> >
    for(int i=0; i < groups().size(); ++i ) {
        if( _groups[i].name() == group ) {
            foreach( const boost::shared_ptr<ParameterQObject >& param,
                     _groups[i].parameters() )
            {
                if( param->name() == name ) {
                    param->setDoc(default_val->doc());
                    return boost::static_pointer_cast< SingleParameter<QString> >(param);
                }
            }
        }
    }
    /// group does not exist, so create one
    ParameterGroup g(name); 
    g.addParameter(default_val);
    appendGroup( g );
    return default_val;
!!!131428.cpp!!!	fromXML(inout file : QFile) : void
    QDomDocument document;
    if (!file.open(QIODevice::ReadOnly))
             return;
    if (!document.setContent(&file)) {
        file.close();
        return;
    }
    QDomNodeList groupsNodes = document.elementsByTagName("groups");
    for (int i = 0; i < groupsNodes.size(); ++i) {
         QDomElement e = groupsNodes.at(i).toElement().firstChildElement("group");
         while( ! e.isNull() )
         {
             ParameterGroup g( e.attribute("name") );
             //qDebug() << "group " << e.attribute("name");
             QDomElement param = e.firstChildElement("parameter");
             while( ! param.isNull() ) {
                 // we only deal with simple parameters
                 if( param.hasAttribute("name") && param.hasAttribute("value") )
                 {
                     QString doc; // TODO - read this in if available
                     boost::shared_ptr<SingleParameter<QString> > 
                         p( new SingleParameter<QString>(param.attribute("name"), doc ) );
                     p->setFromString( param.attribute("value") );
                     g.addParameter(p);
                 }
                 param = param.nextSiblingElement();
             }
             appendGroup(g);
             e = e.nextSiblingElement();
         }
    }

    file.close();
!!!131556.cpp!!!	toXML(inout file : QFile) : void
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                 return;
    QTextStream f(&file);
    toXML(f);
    file.close();
!!!131684.cpp!!!	toXML(inout f : QTextStream) : void
    f << "<groups>\n";
    foreach ( const ParameterGroup& group , _groups )
    {
        f << " <group name=\"" << group.name() << "\">\n";
        foreach ( const boost::shared_ptr<ParameterQObject>& param , group.parameters() )
        {
            f << "  <parameter name=\"" << param->name() << "\" value=\"" 
              << param->toString() << "\">\n";
            f << "   <doc>\n" << param->doc() << "\n</doc>\n";
            f << "  </parameter>\n";
        }
        f << " </group>\n"; 
    }
    f << "</groups>\n";
