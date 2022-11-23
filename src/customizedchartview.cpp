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

#include "customizedchartview.h"

#include <QToolTip>

#include <iostream>

CustomizedChartView::CustomizedChartView()
{
    chart()->legend()->hide();
}

void CustomizedChartView::mousePressEvent(QMouseEvent *event)
{
    QPointF const widgetPos = event->localPos();
    QPointF const scenePos = mapToScene(QPoint(static_cast<int>(widgetPos.x()), static_cast<int>(widgetPos.y())));
    QPointF const chartItemPos = chart()->mapFromScene(scenePos);
    QPointF const valueGivenSeries = chart()->mapToValue(chartItemPos);

    std::cout << "widgetPos:" << widgetPos.x() << " - " << widgetPos.y() << std::endl;
    std::cout << "scenePos:" << scenePos.x() << " - " << scenePos.y() << std::endl;
    std::cout << "chartItemPos:" << chartItemPos.x() << " - " << chartItemPos.y() << std::endl;
    std::cout << "valSeries:" << valueGivenSeries.x() << " - " << valueGivenSeries.y() << std::endl;


    QToolTip::showText(QPoint(scenePos.x(),scenePos.y()),
                       QString::number(valueGivenSeries.x()) + ", " + QString::number(valueGivenSeries.y()));

//    emit clicked(chartItemPos.x(), chartItemPos.y(), valueGivenSeries.x(), valueGivenSeries.y());
}

void CustomizedChartView::mouseDoubleClickEvent( QMouseEvent * e )
{
    if (!double_click_enabled) return;

    QChart *ch = new QChart();

    for (QAbstractSeries * series : chart()->series())
    {
        if (QLineSeries *l = static_cast<QLineSeries *>(series))
        {
            QLineSeries * ls = new QLineSeries();
            ls->setName(l->name());
            ls->setVisible(l->isVisible());
            ls->setColor(l->color());
            ls->setPointsVisible(l->pointsVisible());

            QPen pen = l->pen();
            pen.setWidth(3);
            ls->setPen(pen);

            for (int i=0; i < l->count(); i++)
                ls->append(l->at(i).x(), l->at(i).y());

            ch->addSeries(ls);
        }
    }

    ch->createDefaultAxes();

    static_cast<QValueAxis *>(ch->axisX())->setLabelFormat(static_cast<QValueAxis *>(chart()->axisX())->labelFormat());
    static_cast<QValueAxis *>(ch->axisX())->setMinorTickCount(static_cast<QValueAxis *>(ch->axisX())->minorTickCount());

    CustomizedChartView *chview = new CustomizedChartView();
    chview->setChart(ch);

    chview->setWindowTitle(chart()->title());

    chview->show();
}
