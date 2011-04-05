#ifndef RCU_FILTER_H
#define RCU_FILTER_H
#include <QString>
#include <QList>


/**
 * @file RCU_Filter.h
 */

namespace hic {
    class Array;

/**
 * @class RCU_Filter
 * 
 * @brief
 *   Container for Filter types that can be applied to RCU units
 * @details
 * 
 */
class RCU_Filter
{
    public:
        enum Type { UNSET, LBL_10MHz_HPF, LBL_30MHz_HPF, LBH_10MHz_HPF,
                    LBH_30MHz_HPF, HB_110MHz, HB_170MHz, HB_210MHz };

    public:
        /// RCU_Filter constructor.
        RCU_Filter();
        RCU_Filter(const QString& type);

        /// RCU_Filter destructor.
        ~RCU_Filter();

        /// return the filter type
        int filterId() const;

        /// return the filters name
        const QString& name() const;

        /// comparision operator
        bool operator==(const RCU_Filter&) const;
        bool operator!=(const RCU_Filter&) const;

        /// select one of the valid filters
        void setType(const QString& type);

        // return a list of options for the filter
        const QList<QString>& options() const;

    private:
        int  _type;
};


} // namespace hic

#endif // RCU_FILTER_H 
