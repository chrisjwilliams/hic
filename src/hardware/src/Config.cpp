/*
 * Copyright (c) 2011, The University of Oxford
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the University of Oxford nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include "Config.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDomDocumentType>
#include <QDomNodeList>
#include <QDomElement>
#include <boost/shared_ptr.hpp>
#include "SingleParameter.h"


namespace hic {


/**
 * @details Constructs a Config object.
 */
Config::Config()
    : State()
{
}

/**
 * @details Destroys the Config object.
 */
Config::~Config()
{
}

boost::shared_ptr<SingleParameter<QString> > Config::getParam(
        const QString& group, 
        const QString& name, 
        const boost::shared_ptr<SingleParameter<QString> >& default_val)
{
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
}

void Config::fromXML(QFile& file)
{
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
}

void Config::toXML(QFile& file) const
{
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                 return;
    QTextStream f(&file);
    toXML(f);
    file.close();
}


void Config::toXML(QTextStream& f) const
{
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
}


} // namespace hic
