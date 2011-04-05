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
#ifndef CONFIG_H
#define CONFIG_H


#include "State.h"
#include "SingleParameter.h"
class QFile;
class QTextStream;

/**
 * @file Config.h
 */

namespace hic {

/**
 * @class Config
 * 
 * @brief
 *    A State corresponding to elementa of a configuration file
 * @details
 * 
 */
class Config : public State
{
    public:
        /// Config constructor.
        Config();

        /// Config destructor.
        ~Config();

        /// get a parameter from the configuration. if it does
        //  not exist it is created
        boost::shared_ptr<SingleParameter<QString> > getParam(
                const QString& group, 
                const QString& name, 
                const boost::shared_ptr<SingleParameter<QString> >& default_val);

        /// read in state froman XML file
        void fromXML(QFile& file);

        /// write out state as XML
        void toXML(QFile& file) const;
        void toXML(QTextStream& stream) const;

    private:
        /// not a normal state, use getParam to generate
        void appendGroup(const ParameterGroup& g) { State::appendGroup(g); };
};

} // namespace hic

#endif // CONFIG_H 
