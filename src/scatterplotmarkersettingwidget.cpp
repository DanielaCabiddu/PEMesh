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

#include "scatterplotmarkersettingwidget.h"
#include "ui_scatterplotmarkersettingwidget.h"

#include <QColorDialog>

ScatterPlotMarkerSettingWidget::ScatterPlotMarkerSettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScatterPlotMarkerSettingWidget)
{
    ui->setupUi(this);

    connect(ui->size_dsp, SIGNAL(valueChanged(double)), this, SLOT (emit_size_changed (double)));
    connect(ui->series_cb, SIGNAL(stateChanged(int)), this, SLOT (emit_checked_changed (int)));

}

ScatterPlotMarkerSettingWidget::~ScatterPlotMarkerSettingWidget()
{
    delete ui;
}

void ScatterPlotMarkerSettingWidget::update_series_name(std::string name)
{
    ui->series_cb->setText(name.c_str());
}

void ScatterPlotMarkerSettingWidget::set_checked(bool b)
{
    ui->series_cb->setChecked(b);
}

void ScatterPlotMarkerSettingWidget::set_marker_size(double d)
{
    ui->size_dsp->setValue(d);
}

void ScatterPlotMarkerSettingWidget::emit_size_changed (double val)
{
    emit (size_changed (id, val));
}

void ScatterPlotMarkerSettingWidget::emit_checked_changed (int b)
{
    emit (checked_changed (id, b));
}

void ScatterPlotMarkerSettingWidget::emit_color_changed (QColor c)
{
    emit (color_changed (id, c));
}

void ScatterPlotMarkerSettingWidget::on_color_btn_clicked()
{
    QColorDialog *colorDialog = new QColorDialog(this);
    QColor color = colorDialog->getColor(color, this, "Effect Color", QColorDialog::DontUseNativeDialog);

    if (color == nullptr) return;

    emit_color_changed(color);
}
