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

#ifndef SCATTERPLOTMARKERSETTINGWIDGET_H
#define SCATTERPLOTMARKERSETTINGWIDGET_H

#include <QWidget>

namespace Ui {
class ScatterPlotMarkerSettingWidget;
}

class ScatterPlotMarkerSettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScatterPlotMarkerSettingWidget(QWidget *parent = nullptr);
    ~ScatterPlotMarkerSettingWidget();

    void update_series_name (std::string name);
    void set_checked (bool b);
    void set_marker_size (double d);

    void set_id (uint i) { id = i;}
    void set_color (QColor c) { color = c; }

Q_SIGNALS:

    void size_changed (uint, double);
    void checked_changed (uint, int);
    void color_changed (uint, QColor);

private slots:

    void emit_size_changed (double val);
    void emit_checked_changed (int b);
    void emit_color_changed (QColor c);

    void on_color_btn_clicked();

private:
    Ui::ScatterPlotMarkerSettingWidget *ui;

    uint id;
    QColor color = QColor (150,150,150);
};

#endif // SCATTERPLOTMARKERSETTINGWIDGET_H
