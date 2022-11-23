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

#include "parametricdatasetsettingsdialog.h"
#include "ui_parametricdatasetsettingsdialog.h"

ParametricDatasetSettingsDialog::ParametricDatasetSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParametricDatasetSettingsDialog)
{
    ui->setupUi(this);
    ui->max_area_value->hide();
}

ParametricDatasetSettingsDialog::~ParametricDatasetSettingsDialog()
{
    delete ui;
}

unsigned int ParametricDatasetSettingsDialog::get_num_meshes() const
{
    return static_cast<uint>( ui->n_meshes->value() );
}

double ParametricDatasetSettingsDialog::get_max_deformation_value () const
{
    return ui->max_deformation_value->value();
}

double ParametricDatasetSettingsDialog::get_max_area_value () const
{
    return ui->max_area_value->value();
}

MAX_AREA_TYPES ParametricDatasetSettingsDialog::get_max_area_type  () const
{
    return (MAX_AREA_TYPES) ui->max_area_type->currentIndex();
}

//double ParametricDatasetSettingsDialog::get_min_angle_value() const
//{
//    return ui->min_angle_value->value();
//}

//bool ParametricDatasetSettingsDialog::get_aggregate() const
//{
//    return ui->aggregate_cb->isChecked();
//}

void ParametricDatasetSettingsDialog::on_max_area_type_currentIndexChanged(int index)
{
    if (index == MAX_AREA_TYPES::CONSTANT_USER_DEFINED)
        ui->max_area_value->show();
    else
        ui->max_area_value->hide();
}

double ParametricDatasetSettingsDialog::get_min_angle_value () const
{
    return  ui->min_angle_dsb->value();
}

void ParametricDatasetSettingsDialog::set_is_parametric(const bool b)
{
    ui->n_meshes->setVisible(b);
    ui->n_meshes_label->setVisible(b);

    ui->max_deform_label->setVisible(b);
    ui->max_deformation_value->setVisible(b);

    ui->line->setVisible(b);
}
