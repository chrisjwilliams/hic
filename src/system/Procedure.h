#ifndef PROCEDURE_H
#define PROCEDURE_H

#include <QObject>
#include <QString>
#include <QList>
#include "ProcedureItem.h"

/**
 * @file Procedure.h
 */

namespace hic {

/**
 * @class Procedure
 * 
 * @brief
 *   Defines a procedure that can be performed on a specific platform
 * @details
 * 
 */
class Procedure : public QObject
{
    Q_OBJECT

    public:
        /// Procedure constructor.
        Procedure(QObject* parent = 0);

        /// Procedure destructor.
        ~Procedure();

        /// copy contructor
        Procedure( const Procedure& procedure );

        /// insert a procedure to be executed
        void appendProcedure( const ProcedureItem& );

        /// add another procedure to this
        void appendProcedure( const Procedure& );

        /// run ther procedure
        Report exec();

        /// returns true if the Procedure has any content
        bool isValid() const;

    signals:
        void status(const QString& msg);

    private:
        QList<ProcedureItem> _procs;
};

} // namespace hic

#endif // PROCEDURE_H 
