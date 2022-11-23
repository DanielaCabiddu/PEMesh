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

#ifndef PARAMETRICDATASETSETTINGSDIALOG_H
#define PARAMETRICDATASETSETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class ParametricDatasetSettingsDialog;
}

typedef enum
{
    UNDEFINED,
    BASED_ON_MIN_EDGE,
    BASED_ON_AVG_POLY_DIAGONAL,
    CONSTANT_USER_DEFINED
}
MAX_AREA_TYPES;

class ParametricDatasetSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ParametricDatasetSettingsDialog(QWidget *parent = nullptr);
    ~ParametricDatasetSettingsDialog();

    void set_is_parametric (const bool b);

    unsigned int get_num_meshes() const;
//    double get_min_angle_value () const;
    double get_max_deformation_value () const;

    double get_max_area_value () const;
    MAX_AREA_TYPES   get_max_area_type  () const;

    double get_min_angle_value () const;

    bool get_aggregate () const;

private slots:
    void on_max_area_type_currentIndexChanged(int index);

private:
    Ui::ParametricDatasetSettingsDialog *ui;
};

#endif // PARAMETRICDATASETSETTINGSDIALOG_H
