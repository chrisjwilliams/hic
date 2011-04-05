#ifndef REPORTMODEL_H
#define REPORTMODEL_H


#include "QAbstractItemModel.h"

/**
 * @file ReportModel.h
 */

namespace hic {

/**
 * @class ReportModel
 * 
 * @brief
 *   Model for A TreeViewa to display a Report
 * @details
 * 
 */
class ReportModel : public QAbstractItemModel
{
    public:
        /// ReportModel constructor.
        ReportModel( const Report& report, QObject *parent = 0 );

        /// ReportModel destructor.
        ~ReportModel();

        QVariant data(const QModelIndex &index, int role) const;
        Qt::ItemFlags flags(const QModelIndex &index) const;
        QVariant headerData(int section, Qt::Orientation orientation,
                int role = Qt::DisplayRole) const;
        QModelIndex index(int row, int column,
                const QModelIndex &parent = QModelIndex()) const;
        QModelIndex parent(const QModelIndex &index) const;
        int rowCount(const QModelIndex &parent = QModelIndex()) const;
        int columnCount(const QModelIndex &parent = QModelIndex()) const;

    private:
};

} // namespace hic

#endif // REPORTMODEL_H 
