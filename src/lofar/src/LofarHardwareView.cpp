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
#include "LofarHardwareView.h"
#include <QString>
#include "hardware/ParameterGroup.h"


#include "pelican/utility/memCheck.h"

namespace hic {


/**
 * @details Constructs a LofarHardwareView object.
 */
LofarHardwareView::LofarHardwareView()
    : State()
{
    setName("Lofar Hardware View");

        // rcu mode
        StateParameter rcumode(QObject::tr("rcumode"), "The frequency range that the RCU Board should operate");
        QMap<QString,QString> rcuOptions;
        rcuOptions["LBL 10MHz HPF"] = "1";
        rcuOptions["LBL 30MHz HPF"] = "2";
        rcuOptions["LBH 10MHz HPF"] = "3";
        rcuOptions["LBH 30MHz HPF"] = "4";
        rcuOptions["HB 110-190MHz"] = "5";
        rcuOptions["HB 170-230MHz"] = "6";
        rcuOptions["HB 210-270MHz"] = "7";
        rcumode.setRestrictedValues( rcuOptions );
}

/**
 * @details Destroys the LofarHardwareView object.
 */
LofarHardwareView::~LofarHardwareView()
{
}

} // namespace hic
