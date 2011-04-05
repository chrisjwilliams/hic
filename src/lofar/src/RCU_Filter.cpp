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
