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
#ifndef PARAMWIDGETMULTIRANGE_H
#define PARAMWIDGETMULTIRANGE_H


#include "ParameterWidget.h"
#include <boost/shared_ptr.hpp>

class QLineEdit;
class QLabel;

/**
 * @file ParamWidgetMultiRange.h
 */

namespace hic {
    class MultiRangeParameterInterface;

/**
 * @class ParamWidgetMultiRange
 * 
 * @brief
 *    Widget to display and operate actions on a 
 *    MultiParameterRange
 * @details
 * 
 */
class ParamWidgetMultiRange : public ParameterWidget
{
    Q_OBJECT

    public:
        /// ParamWidgetMultiRange constructor.
        ParamWidgetMultiRange( const boost::shared_ptr<MultiRangeParameterInterface>& param,
                                         QWidget* parent=0 );

        /// ParamWidgetMultiRange destructor.
        ~ParamWidgetMultiRange();

    protected:
        virtual QString doc() const;
        virtual void refresh();
        virtual void selectionUpdate();

        inline MultiRangeParameterInterface* param() const;
        void _setBadColor();
        void _setOKColor();

    protected slots:
        void setParam();


    private:
        MultiRangeParameterInterface* _mparam;
        QLabel* _rangeLabel;
        QLineEdit* _text;
};

} // namespace hic

#endif // PARAMWIDGETMULTIRANGE_H 
