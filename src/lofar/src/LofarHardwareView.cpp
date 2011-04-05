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
