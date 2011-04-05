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
#include "RCU_Filter.h"


namespace hic {


/**
 * @details Constructs a RCU_Filter object.
 */
RCU_Filter::RCU_Filter()
    : _type(0)
{
}

RCU_Filter::RCU_Filter(const QString& type)
{
    setType(type);
}

/**
 * @details Destroys the RCU_Filter object.
 */
RCU_Filter::~RCU_Filter()
{
}

inline const QList<QString>& RCU_Filter::options() const
{
    static QList<QString> _options;
    _options << "UNSET" << "LBL 10MHz HPF" 
             << "LBL 30MHz HPF" << "LBH 10MHz HPF" 
             << "LBH 30MHz HPF" << "HB 110-190MHz" 
             << "HB 170-230MHz" << "HB 210-270MHz";
    return _options;
}

void RCU_Filter::setType(const QString& type)
{
    int index = options().indexOf(type);
    if( index >= 0 )
        _type = index;
}

const QString& RCU_Filter::name() const
{
    return options()[_type];
}

int RCU_Filter::filterId() const
{
    return _type;
}

bool RCU_Filter::operator==(const RCU_Filter& f) const
{
    return _type == f._type;
}

bool RCU_Filter::operator!=(const RCU_Filter& f) const
{
    return _type != f._type;
}

} // namespace hic
