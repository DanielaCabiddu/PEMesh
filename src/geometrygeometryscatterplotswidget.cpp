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

#include "geometrygeometryscatterplotswidget.h"
#include "ui_geometrygeometryscatterplotswidget.h"

#include "quality_metrics.h"

#include <QFileDialog>
#include <QPixmap>
#include <QScatterSeries>
#include <QToolTip>
#include <QtCharts/QLogValueAxis>

GeometryGeometryScatterPlotsWidget::GeometryGeometryScatterPlotsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GeometryGeometryScatterPlotsWidget)
{
    ui->setupUi(this);

    for (uint i=0; i < metrics_names.size(); i++)
//        if (!metrics_scale_dependent.at(i))
        {
            ui->x_axis_cb->addItem(metrics_names.at(i).c_str());
            ui->y_axis_cb->addItem(metrics_names.at(i).c_str());

            cbID2metricsID.push_back(i);
        }

    connect(ui->x_axis_cb, SIGNAL (currentIndexChanged(int)), this, SLOT (show_scatterplot_x(int)));
    connect(ui->y_axis_cb, SIGNAL (currentIndexChanged(int)), this, SLOT (show_scatterplot_y(int)));

    for(int i = ui->stackedWidget->count(); i >= 0; i--)
        ui->stackedWidget->removeWidget(ui->stackedWidget->widget(i));

    ui->marker_settings_widget->setLayout(new QVBoxLayout());

    extra_colors.push_back(QColor(255, 192, 203));
    extra_colors.push_back(QColor(211, 211, 211));
    extra_colors.push_back(QColor(0, 0, 139));
    extra_colors.push_back(QColor(34,139,34));

}

GeometryGeometryScatterPlotsWidget::~GeometryGeometryScatterPlotsWidget()
{
    delete ui;
}

void GeometryGeometryScatterPlotsWidget::create_scatterPlots(const Dataset &d, const std::vector<MeshMetrics> &metrics)
{
    std::vector<uint> class_chages;
    class_chages.push_back(0);

    for (uint i=1; i < d.get_num_parametric_meshes(); i++)
        if (d.get_parametric_mesh_class_id(i) != d.get_parametric_mesh_class_id(i-1))
            class_chages.push_back(i);

    class_chages.push_back(d.get_num_parametric_meshes());

    for (int i=0; i < ui->x_axis_cb->count(); i++)
    {
        for (int j=0; j < ui->x_axis_cb->count(); j++)
        {
            QChart *ch = new QChart();

            double maxX = -DBL_MAX;
            double maxY = -DBL_MAX;

            for (uint cc=0; cc < class_chages.size()-1; cc++)
            {
                std::string class_name = "Unknown";
                if (d.get_num_parametric_meshes() > 0)
                    class_name = d.get_parametric_mesh_class_name(d.get_parametric_mesh_class_id(class_chages.at(cc))).c_str();

                QScatterSeries *s = new QScatterSeries();
                s->setName(class_name.c_str());

                if (cc > 4)
                    s->setColor(extra_colors.at(cc-5));

                for (uint m=class_chages.at(cc); m < class_chages.at(cc+1); m++)
                {
                    double x, y;

                    double min_IC = std::min(metrics.at(m).IC_min,
                                             metrics.at(m).IC_poly_min);

                    if (metrics.at(m).IC_min_id == UINT_MAX) min_IC = metrics.at(m).IC_poly_min;
                    else if (metrics.at(m).IC_poly_min_id == UINT_MAX) min_IC = metrics.at(m).IC_min;

                    double min_CC = std::min(metrics.at(m).CC_min,
                                             metrics.at(m).CC_poly_min);

                    if (metrics.at(m).CC_min_id == UINT_MAX) min_CC = metrics.at(m).CC_poly_min;
                    else if (metrics.at(m).CC_poly_min_id == UINT_MAX) min_CC = metrics.at(m).CC_min;

                    double min_CR = std::min(metrics.at(m).CR_min,
                                             metrics.at(m).CR_poly_min);

                    if (metrics.at(m).CR_min_id == UINT_MAX) min_CR = metrics.at(m).CR_poly_min;
                    else if (metrics.at(m).CR_poly_min_id == UINT_MAX) min_CR = metrics.at(m).CR_min;

                    double min_AR = std::min(metrics.at(m).AR_min,
                                             metrics.at(m).AR_poly_min);

                    if (metrics.at(m).AR_min_id == UINT_MAX) min_AR = metrics.at(m).AR_poly_min;
                    else if (metrics.at(m).AR_poly_min_id == UINT_MAX) min_AR = metrics.at(m).AR_min;

                    double min_KE = std::min(metrics.at(m).KE_min,
                                             metrics.at(m).KE_poly_min);

                    if (metrics.at(m).KE_min_id == UINT_MAX) min_KE = metrics.at(m).KE_poly_min;
                    else if (metrics.at(m).KE_poly_min_id == UINT_MAX) min_KE = metrics.at(m).KE_min;

                    double min_KAR = std::min(metrics.at(m).KAR_min,
                                              metrics.at(m).KAR_poly_min);

                    if (metrics.at(m).KAR_min_id == UINT_MAX) min_KAR = metrics.at(m).KAR_poly_min;
                    else if (metrics.at(m).KAR_poly_min_id == UINT_MAX) min_KAR = metrics.at(m).KAR_min;

                    double min_APR = std::min(metrics.at(m).APR_min,
                                              metrics.at(m).APR_poly_min);

                    if (metrics.at(m).APR_min_id == UINT_MAX) min_APR = metrics.at(m).APR_poly_min;
                    else if (metrics.at(m).APR_poly_min_id == UINT_MAX) min_APR = metrics.at(m).APR_min;

                    double min_MA = std::min(metrics.at(m).MA_min,
                                             metrics.at(m).MA_poly_min);

                    if (metrics.at(m).MA_min_id == UINT_MAX) min_MA = metrics.at(m).MA_poly_min;
                    else if (metrics.at(m).MA_poly_min_id == UINT_MAX) min_MA = metrics.at(m).MA_min;

                    double min_SE = std::min(metrics.at(m).SE_min,
                                             metrics.at(m).SE_poly_min);
                    min_SE = log(min_SE);

                    if (metrics.at(m).SE_min_id == UINT_MAX) min_SE = metrics.at(m).SE_poly_min;
                    else if (metrics.at(m).SE_poly_min_id == UINT_MAX) min_SE = metrics.at(m).SE_min;

                    double min_ER = std::min(metrics.at(m).ER_min,
                                             metrics.at(m).ER_poly_min);

                    if (metrics.at(m).ER_min_id == UINT_MAX) min_ER = metrics.at(m).ER_poly_min;
                    else if (metrics.at(m).ER_poly_min_id == UINT_MAX) min_ER = metrics.at(m).ER_min;

                    double min_MPD = std::min(metrics.at(m).MPD_min,
                                             metrics.at(m).MPD_poly_min);

                    if (metrics.at(m).MPD_min_id == UINT_MAX) min_MPD = metrics.at(m).MPD_poly_min;
                    else if (metrics.at(m).MPD_poly_min_id == UINT_MAX) min_MPD = metrics.at(m).MPD_min;

                    double min_NS = std::min(metrics.at(m).NS_min,
                                             metrics.at(m).NS_poly_min);

                    if (metrics.at(m).NS_min_id == UINT_MAX) min_NS = metrics.at(m).NS_poly_min;
                    else if (metrics.at(m).NS_poly_min_id == UINT_MAX) min_NS = metrics.at(m).NS_min;

                    double min_MXA = std::min(metrics.at(m).MXA_min,
                                              metrics.at(m).MXA_poly_min);

                    if (metrics.at(m).MXA_min_id == UINT_MAX) min_MXA = metrics.at(m).MXA_poly_min;
                    else if (metrics.at(m).MXA_poly_min_id == UINT_MAX) min_MXA = metrics.at(m).MXA_min;

                    double min_SR = std::min(metrics.at(m).SR_min,
                                             metrics.at(m).SR_poly_min);
                    min_SR = log(min_SR);

                    if (metrics.at(m).SR_min_id == UINT_MAX) min_SR = metrics.at(m).SR_poly_min;
                    else if (metrics.at(m).SR_poly_min_id == UINT_MAX) min_SR = metrics.at(m).SR_min;

                    double max_VEM = std::max(metrics.at(m).VEM_max, metrics.at(m).VEM_poly_max);
                    max_VEM = log(max_VEM);

                    if (metrics.at(m).VEM_max_id == UINT_MAX) max_VEM = metrics.at(m).VEM_poly_max;
                    else if (metrics.at(m).VEM_poly_max_id == UINT_MAX) max_VEM = metrics.at(m).VEM_max;

                    double sum_VEMA = sqrt(metrics.at(m).VEMA_sum + metrics.at(m).VEMA_poly_sum);
                    sum_VEMA = log(sum_VEMA);

                    std::cout <<min_SE<<" "<<max_VEM<<std::endl;
                    std::cout <<min_SE<<" "<<sum_VEMA<<std::endl;

                    switch (cbID2metricsID.at(i)) {
                        case 0: x = min_IC; break;
                        case 1: x = min_CC; break;
                        case 2: x = min_CR; break;

                        case 3: x = min_AR; break;
                        case 4: x = min_KE; break;
                        case 5: x = min_KAR; break;
                        case 6: x = min_APR; break;
                        case 7: x = min_MA; break;
                        case 8: x = min_SE; break;
                        case 9: x = min_ER; break;
                        case 10: x = min_MPD; break;
                        case 11: x = min_NS; break;
                        case 12: x = min_MXA; break;
                        case 13: x = min_SR; break;
                        case 14: x = max_VEM; break;
                        case 15: x = sum_VEMA; break;
                    default: x = DBL_MAX;
                    }
                    switch (cbID2metricsID.at(j)) {
                        case 0: y = min_IC; break;
                        case 1: y = min_CC; break;
                        case 2: y = min_CR; break;
                        case 3: y = min_AR; break;
                        case 4: y = min_KE; break;
                        case 5: y = min_KAR; break;
                        case 6: y = min_APR; break;
                        case 7: y = min_MA; break;
                        case 8: y = min_SE; break;
                        case 9: y = min_ER; break;
                        case 10: y = min_MPD; break;
                        case 11: y = min_NS; break;
                        case 12: y = min_MXA; break;
                        case 13: y = min_SR; break;
                        case 14: y = max_VEM; break;
                        case 15: y = sum_VEMA; break;
                    default: y = DBL_MAX;
                    }
                    s->append(x,y);

                    if(x>maxX)  maxX=x;
                    if(y>maxY)  maxY=y;
                }
                ch->addSeries(s);
            }

            ch->createDefaultAxes();

//            QLogValueAxis *axisXlog = new QLogValueAxis();
//            axisXlog->setLabelFormat("%e");
//            axisXlog->setBase(10.0);
//            axisXlog->setMax(maxX);
//            ch->removeAxis(ch->axes().at(0));
//            ch->addAxis(axisXlog, Qt::AlignBottom);

//            QLogValueAxis *axisYlog = new QLogValueAxis();
//            axisYlog->setLabelFormat("%e");
//            axisYlog->setBase(10.0);
//            axisYlog->setMax(maxY);
//            ch->removeAxis(ch->axes().at(1));
//            ch->addAxis(axisYlog, Qt::AlignLeft);

            ch->axes()[0]->setTitleText(metrics_names.at(cbID2metricsID.at(i)).c_str());
            ch->axes()[1]->setTitleText(metrics_names.at(cbID2metricsID.at(j)).c_str());

            std::cout << chart_views.size() << " : " << metrics_names.at(cbID2metricsID.at(i)) <<
                                               " - " << metrics_names.at(cbID2metricsID.at(j)) << std::endl;
            CustomizedChartView *ch_view = new CustomizedChartView();
            ch_view->setChart(ch);

//            connect(ch_view, SIGNAL(clicked(double, double, double, double)),
//                    this, SLOT (show_tooltip (double, double, double, double)));

            chart_views.push_back(ch_view);
            ui->stackedWidget->addWidget(ch_view);
        }
    }
    ui->stackedWidget->setCurrentIndex(0);

    ui->x_axis_cb->setCurrentIndex(0);
    ui->y_axis_cb->setCurrentIndex(0);

    QScatterSeries * s = static_cast<QScatterSeries*>(chart_views.at(0)->chart()->series()[0]);
    ui->marker_size_dsb->setValue(s->markerSize());

    for (uint cc=0; cc < class_chages.size()-1; cc++)
    {
        std::string class_name = "Unknown";

        if (d.get_num_parametric_meshes() > 0)
            class_name = d.get_parametric_mesh_class_name(d.get_parametric_mesh_class_id(class_chages.at(cc))).c_str();

        ScatterPlotMarkerSettingWidget * msw = new ScatterPlotMarkerSettingWidget();
        msw->update_series_name(class_name.c_str());
        msw->set_checked(true);

        QScatterSeries * s = static_cast<QScatterSeries*>(chart_views.at(0)->chart()->series()[cc]);
        ui->marker_size_dsb->setValue(s->markerSize());
        msw->set_marker_size(s->markerSize());
        msw->set_id(cc);
        msw->set_color(s->color());

        connect(msw, SIGNAL(size_changed(uint, double)), this, SLOT (update_marker_size (uint, double)));
        connect(msw, SIGNAL(checked_changed(uint, int)), this, SLOT (update_show_series (uint, int)));
        connect(msw, SIGNAL(color_changed(uint, QColor)), this, SLOT (update_color_series (uint, QColor)));

        ui->marker_settings_widget->layout()->addWidget(msw);
        marker_settings_widgets.push_back(msw);
    }
    connect(ui->marker_size_dsb, SIGNAL(valueChanged(double)), this, SLOT (update_marker_size (double)));
}

void GeometryGeometryScatterPlotsWidget::show_scatterplot_x(int xID)
{
    int yID = ui->y_axis_cb->currentIndex();

    std::cout << xID << " - " << yID << std::endl;

    ui->stackedWidget->setCurrentIndex(xID * ui->y_axis_cb->count()+ yID);
}

void GeometryGeometryScatterPlotsWidget::show_scatterplot_y(int yID)
{
    int xID = ui->x_axis_cb->currentIndex();

    std::cout << xID << " - " << yID << std::endl;

    ui->stackedWidget->setCurrentIndex(xID * ui->y_axis_cb->count()+ yID);
}

void GeometryGeometryScatterPlotsWidget::update_marker_size(double size)
{
    for (CustomizedChartView *ch_view : chart_views)
    {
        for (int i=0; i < ch_view->chart()->series().count(); i++)
        {
            QScatterSeries * s = static_cast<QScatterSeries*>(ch_view->chart()->series()[i]);
            s->setMarkerSize(size);
        }
    }
}

void GeometryGeometryScatterPlotsWidget::update_marker_size(uint id, double size)
{
    for (CustomizedChartView *ch_view : chart_views)
    {
        QScatterSeries * s = static_cast<QScatterSeries*>(ch_view->chart()->series()[id]);
        s->setMarkerSize(size);
    }
}

void GeometryGeometryScatterPlotsWidget::update_show_series(uint id, int b)
{
    for (CustomizedChartView *ch_view : chart_views)
    {
        QScatterSeries * s = static_cast<QScatterSeries*>(ch_view->chart()->series()[id]);
        s->setVisible(b);
    }
}

void GeometryGeometryScatterPlotsWidget::update_color_series(uint id, QColor c)
{
    for (CustomizedChartView *ch_view : chart_views)
    {
        QScatterSeries * s = static_cast<QScatterSeries*>(ch_view->chart()->series()[id]);
        s->setColor(c);
    }
}

void GeometryGeometryScatterPlotsWidget::show_tooltip(double posX, double posY, double x, double y)
{
    QToolTip::showText(QPoint(posX,posY),
                       QString::number(x) + ", " + QString::number(y));
}

void GeometryGeometryScatterPlotsWidget::on_save_btn_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Select Directory"),
                                                        "/tmp",
                                                        QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);
    if (dir.isNull())
        return;

    for (QChartView *chview : chart_views)
    {
        std::string x_axis = chview->chart()->axisX()->titleText().toStdString();
        std::string y_axis = chview->chart()->axisY()->titleText().toStdString();

        std::replace( x_axis.begin(), x_axis.end(), ' ', '_'); // replace all 'x' to 'y'
        std::replace( y_axis.begin(), y_axis.end(), ' ', '_'); // replace all 'x' to 'y'

        std::string filename = dir.toStdString() + "/" + x_axis + "__..__" + y_axis + ".png";

        std::cout << "Saving "  << filename << std::endl;

//        const auto dpr = chview->devicePixelRatioF();
//        QPixmap buffer(chview->width() * dpr, chview->height() * dpr);
//        buffer.setDevicePixelRatio(dpr);
//        buffer.fill(Qt::transparent);

//        QPainter *paint = new QPainter(&buffer);
//        paint->setPen(*(new QColor(255,34,255,255)));
//        chview->render(paint);

//        QFile file(filename.c_str());
//        file.open(QIODevice::WriteOnly);
//        buffer.save(&file, "PNG");

//        delete  paint;

        QPixmap p = chview->grab();
        p.save(filename.c_str());
    }

}
