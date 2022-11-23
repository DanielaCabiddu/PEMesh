/********************************************************************************
*  This file is part of PEMesh                                                  *
*  Copyright(C) 2022: Daniela Cabiddu                                           *

*                                                                               *
*  Author(s):                                                                   *
*                                                                               *
*     Daniela Cabiddu (daniela.cabiddu@cnr.it)                                  *
*                                                                               *
*     Italian National Research Council (CNR)                                   *
*     Institute for Applied Mathematics and Information Technologies (IMATI)    *
*     Via de Marini, 6                                                          *
*     16149 Genoa,                                                              *
*     Italy                                                                     *
*                                                                               *
*                                                                               *
*                                                                               *
*  This program is free software: you can redistribute it and/or modify it      *
*  under the terms of the GNU General Public License as published by the        *
*  Free Software Foundation, either version 3 of the License, or (at your       *
*  option) any later version.                                                   *
*                                                                               *
*  This program is distributed in the hope that it will be useful, but          *
*  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY   *
*  or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for  *
*  more details.                                                                *
*                                                                               *
*  You should have received a copy of the GNU General Public License along      *
*  with this program. If not, see <https://www.gnu.org/licenses/>.              *
*                                                                               *
*********************************************************************************/

#ifndef AGGREGATEDIALOG_H
#define AGGREGATEDIALOG_H

#include <QDialog>

namespace Ui {
class AggregateDialog;
}

class AggregateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AggregateDialog(QWidget *parent = nullptr);
    ~AggregateDialog();

    void setAggregateMode();
    void setDatasetMode();
    int getAggregationIndex() const;
    std::string getAggregationName() const;
    int getNumSteps() const;
    double getAggregationBound() const;

private slots:
    void on_type_btn_currentIndexChanged(int index);

private:
    Ui::AggregateDialog *ui;
};

#endif // AGGREGATEDIALOG_H
