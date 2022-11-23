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

#include "aggregatedialog.h"
#include "ui_aggregatedialog.h"

AggregateDialog::AggregateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AggregateDialog)
{
    ui->setupUi(this);

    setWindowTitle(tr("Select Aggregation Technique"));

    ui->bound_btn->hide();
    ui->label_2->hide();

    ui->nsteps_btn->hide();
    ui->label_4->hide();
}

AggregateDialog::~AggregateDialog()
{
    delete ui;
}

void AggregateDialog::setAggregateMode()
{
    ui->nsteps_btn->setEnabled(false);
    return;
}

void AggregateDialog::setDatasetMode()
{
    ui->bound_btn->setEnabled(false);
    return;
}

int AggregateDialog::getAggregationIndex() const
{
    return ui->type_btn->currentIndex();
}

std::string AggregateDialog::getAggregationName() const
{
    return ui->type_btn->currentText().toStdString();
}

int AggregateDialog::getNumSteps() const
{
    return ui->nsteps_btn->value();
}

double AggregateDialog::getAggregationBound() const
{
    return ui->bound_btn->value();
}

void AggregateDialog::on_type_btn_currentIndexChanged(int index)
{
    if (index < 2)
    {
        ui->bound_btn->hide();
        ui->label_2->hide();

        ui->nsteps_btn->hide();
        ui->label_4->hide();
    }
    else
    {
        ui->bound_btn->show();
        ui->label_2->show();

        ui->nsteps_btn->show();
        ui->label_4->show();
    }
}
