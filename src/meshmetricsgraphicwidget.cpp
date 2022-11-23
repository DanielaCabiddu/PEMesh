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

#include "meshmetricsgraphicwidget.h"
#include "ui_meshmetricsgraphicwidget.h"

#include "quality_metrics.h"

MeshMetricsGraphicWidget::MeshMetricsGraphicWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeshMetricsGraphicWidget)
{
    ui->setupUi(this);

    connect(ui->mesh_metrics_slider, SIGNAL(valueChanged(int)), this, SLOT(show_mesh(int)));
    connect(ui->ic_rb, SIGNAL(clicked()), this, SLOT(show_ic()));
    connect(ui->cc_rb, SIGNAL(clicked()), this, SLOT(show_cc()));
    connect(ui->cr_rb, SIGNAL(clicked()), this, SLOT(show_cr()));
    connect(ui->ar_rb, SIGNAL(clicked()), this, SLOT(show_ar()));
    connect(ui->ke_rb, SIGNAL(clicked()), this, SLOT(show_ke()));
    connect(ui->kar_rb, SIGNAL(clicked()), this, SLOT(show_kar()));
    connect(ui->par_rb, SIGNAL(clicked()), this, SLOT(show_par()));
    connect(ui->ma_rb, SIGNAL(clicked()), this, SLOT(show_ma()));
    connect(ui->se_rb, SIGNAL(clicked()), this, SLOT(show_se()));
    connect(ui->er_rb, SIGNAL(clicked()), this, SLOT(show_er()));
    connect(ui->mpd_rb, SIGNAL(clicked()), this, SLOT(show_mpd()));
    connect(ui->ns_rb, SIGNAL(clicked()), this, SLOT(show_ns()));
    connect(ui->mxa_rb, SIGNAL(clicked()), this, SLOT(show_mxa()));
    connect(ui->sr_rb, SIGNAL(clicked()), this, SLOT(show_sr()));
    connect(ui->vem_rb, SIGNAL(clicked()), this, SLOT(show_vem()));
    connect(ui->vema_rb, SIGNAL(clicked()), this, SLOT(show_vema()));

    connect(ui->min_rb, SIGNAL(clicked()), this, SLOT(show_min()));
    connect(ui->max_rb, SIGNAL(clicked()), this, SLOT(show_max()));
    connect(ui->avg_rb, SIGNAL(clicked()), this, SLOT(show_avg()));
    connect(ui->poly_rb, SIGNAL(clicked()), this, SLOT(show_poly()));

    ui->ic_rb->setText((metrics_acronym.at(0) + " - " + metrics_names.at(0)).c_str());
    ui->cc_rb->setText((metrics_acronym.at(1) + " - " + metrics_names.at(1)).c_str());
    ui->cr_rb->setText((metrics_acronym.at(2) + " - " + metrics_names.at(2)).c_str());
    ui->ar_rb->setText((metrics_acronym.at(3) + " - " + metrics_names.at(3)).c_str());
    ui->ke_rb->setText((metrics_acronym.at(4) + " - " + metrics_names.at(4)).c_str());
    ui->kar_rb->setText((metrics_acronym.at(5) + " - " + metrics_names.at(5)).c_str());
    ui->par_rb->setText((metrics_acronym.at(6) + " - " + metrics_names.at(6)).c_str());
    ui->ma_rb->setText((metrics_acronym.at(7) + " - " + metrics_names.at(7)).c_str());
    ui->se_rb->setText((metrics_acronym.at(8) + " - " + metrics_names.at(8)).c_str());
    ui->er_rb->setText((metrics_acronym.at(9) + " - " + metrics_names.at(9)).c_str());
    ui->mpd_rb->setText((metrics_acronym.at(10) + " - " + metrics_names.at(10)).c_str());
    ui->ns_rb->setText((metrics_acronym.at(11) + " - " + metrics_names.at(11)).c_str());
    ui->mxa_rb->setText((metrics_acronym.at(12) + " - " + metrics_names.at(12)).c_str());
    ui->sr_rb->setText((metrics_acronym.at(13) + " - " + metrics_names.at(13)).c_str());
    ui->vem_rb->setText((metrics_acronym.at(14) + " - " + metrics_names.at(14)).c_str());
    ui->vema_rb->setText((metrics_acronym.at(15) + " - " + metrics_names.at(15)).c_str());

}

MeshMetricsGraphicWidget::~MeshMetricsGraphicWidget()
{
    delete ui;
}

void MeshMetricsGraphicWidget::clean_canvas()
{
    for (const cinolib::DrawablePolygonmesh<> * p : mesh_with_metrics)
        ui->mesh_metrics_canvas->pop(p);

    mesh_with_metrics.clear();
}

void MeshMetricsGraphicWidget::show_mesh (int i)
{
    if (i < 0) return;

    clean_canvas();

    d->get_parametric_mesh(static_cast<uint>(i))->updateGL();
    ui->mesh_metrics_canvas->push_obj(d->get_parametric_mesh(static_cast<uint>(i)), update_scene);
    ui->mesh_metrics_canvas->updateGL();

    update_scene=false;

    mesh_with_metrics.push_back(d->get_parametric_mesh(static_cast<uint>(i)));

    curr_mesh_id = static_cast<uint>(i);

    if (ui->min_rb->isChecked()) show_min();
    else if (ui->max_rb->isChecked()) show_max();
    else if (ui->avg_rb->isChecked()) show_avg();
    else show_poly();
}

void MeshMetricsGraphicWidget::set_dataset(Dataset *ds)
{
    clean_canvas();

    d = ds;
}

void MeshMetricsGraphicWidget::set_metrics (std::vector<MeshMetrics> *m)
{
    metrics = m;
}

void MeshMetricsGraphicWidget::set_min_color(const uint i)
{
    std::cout << "Min ID " << i << std::endl;

    if (i > mesh_with_metrics.at(0)->num_polys()-1) return;

    mesh_with_metrics.at(0)->poly_data(i).color = cinolib::Color::GREEN();
}

void MeshMetricsGraphicWidget::set_max_color(const uint i)
{
    std::cout << "Max ID " << i << std::endl;

    if (i > mesh_with_metrics.at(0)->num_polys()-1) return;

    mesh_with_metrics.at(0)->poly_data(i).color = cinolib::Color::BLUE();
}

void MeshMetricsGraphicWidget::show_ic()
{
    mesh_with_metrics.at(0)->poly_set_color(cinolib::Color::WHITE());

    std::string message = "";

    uint id_min = metrics->at(curr_mesh_id).IC_min_id;
    uint id_max = metrics->at(curr_mesh_id).IC_max_id;

    if (ui->min_rb->isChecked() || ui->avg_rb->isChecked())
    {
        set_min_color(id_min);
        message += "<br><font color=\"green\">IC MIN : " + std::to_string(metrics->at(curr_mesh_id).IC_min) + "</font>";
    }

    if (ui->max_rb->isChecked() || ui->avg_rb->isChecked())
    {
        set_max_color(id_max);
        message += "<br><font color=\"blue\">IC MAX : " + std::to_string(metrics->at(curr_mesh_id).IC_max) + "</font>";
    }

    if (ui->avg_rb->isChecked())
    {
        message += "<br>IC AVG : " + std::to_string(metrics->at(curr_mesh_id).IC_avg);
    }

    if (ui->poly_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).IC_poly_min_id;
        id_max = metrics->at(curr_mesh_id).IC_poly_max_id;

        set_min_color(id_min);
        set_max_color(id_max);

        message += "<br><font color=\"green\">IC POLY MIN : " + std::to_string(metrics->at(curr_mesh_id).IC_poly_min) + "</font>";
        message += "<br><font color=\"blue\">IC POLY MAX : " + std::to_string(metrics->at(curr_mesh_id).IC_poly_max) + "</font>";
        message += "<br>IC POLY AVG : " + std::to_string(metrics->at(curr_mesh_id).IC_poly_avg);
    }


    d->get_parametric_mesh(static_cast<uint>(curr_mesh_id))->updateGL();
    ui->mesh_metrics_canvas->updateGL();

    ui->info_text->setHtml(message.c_str());
}

void MeshMetricsGraphicWidget::show_cc()
{
    mesh_with_metrics.at(0)->poly_set_color(cinolib::Color::WHITE());

    std::string message = "";


    uint id_min = metrics->at(curr_mesh_id).CC_min_id;
    uint id_max = metrics->at(curr_mesh_id).CC_max_id;

    if (ui->min_rb->isChecked() || ui->avg_rb->isChecked())
    {
        set_min_color(id_min);
        message += "<br><font color=\"green\">CC MIN : " + std::to_string(metrics->at(curr_mesh_id).CC_min) + "</font>";
    }

    if (ui->max_rb->isChecked() || ui->avg_rb->isChecked())
    {
        set_max_color(id_max);
        message += "<br><font color=\"blue\">CC MAX : " + std::to_string(metrics->at(curr_mesh_id).CC_max) + "</font>";
    }

    if (ui->avg_rb->isChecked())
    {
        message += "<br>CC AVG : " + std::to_string(metrics->at(curr_mesh_id).CC_avg);
    }

    if (ui->poly_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).CC_poly_min_id;
        id_max = metrics->at(curr_mesh_id).CC_poly_max_id;

        set_min_color(id_min);
        set_max_color(id_max);

        message += "<br><font color=\"green\">CC POLY MIN : " + std::to_string(metrics->at(curr_mesh_id).CC_poly_min) + "</font>";
        message += "<br><font color=\"blue\">CC POLY MAX : " + std::to_string(metrics->at(curr_mesh_id).CC_poly_max) + "</font>";
        message += "<br>CC POLY AVG : " + std::to_string(metrics->at(curr_mesh_id).CC_poly_avg);
    }

    d->get_parametric_mesh(static_cast<uint>(curr_mesh_id))->updateGL();
    ui->mesh_metrics_canvas->updateGL();

    ui->info_text->setHtml(message.c_str());
}

void MeshMetricsGraphicWidget::show_cr()
{
    mesh_with_metrics.at(0)->poly_set_color(cinolib::Color::WHITE());

    std::string message = "";

    uint id_min = metrics->at(curr_mesh_id).CR_min_id;
    uint id_max = metrics->at(curr_mesh_id).CR_max_id;

    if (ui->min_rb->isChecked() || ui->avg_rb->isChecked())
    {
        set_min_color(id_min);
        message += "<br><font color=\"green\">CR MIN : " + std::to_string(metrics->at(curr_mesh_id).CR_min) + "</font>";
    }

    if (ui->max_rb->isChecked() || ui->avg_rb->isChecked())
    {
        set_max_color(id_max);
        message += "<br><font color=\"blue\">CR MAX : " + std::to_string(metrics->at(curr_mesh_id).CR_max) + "</font>";
    }

    if (ui->avg_rb->isChecked())
    {
        message += "<br>CR AVG : " + std::to_string(metrics->at(curr_mesh_id).CR_avg);
    }

    if (ui->poly_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).CR_poly_min_id;
        id_max = metrics->at(curr_mesh_id).CR_poly_max_id;

        set_min_color(id_min);
        set_max_color(id_max);

        message += "<br><font color=\"green\">CR POLY MIN : " + std::to_string(metrics->at(curr_mesh_id).CR_poly_min) + "</font>";
        message += "<br><font color=\"blue\">CR POLY MAX : " + std::to_string(metrics->at(curr_mesh_id).CR_poly_max) + "</font>";
        message += "<br>CR POLY AVG : " + std::to_string(metrics->at(curr_mesh_id).CR_poly_avg);
    }

    d->get_parametric_mesh(static_cast<uint>(curr_mesh_id))->updateGL();
    ui->mesh_metrics_canvas->updateGL();

    ui->info_text->setHtml(message.c_str());
}

void MeshMetricsGraphicWidget::show_ar ()
{
    mesh_with_metrics.at(0)->poly_set_color(cinolib::Color::WHITE());

    std::string message = "";

    uint id_min = metrics->at(curr_mesh_id).AR_min_id;
    uint id_max = metrics->at(curr_mesh_id).AR_max_id;

    if (ui->min_rb->isChecked() || ui->avg_rb->isChecked())
    {
        set_min_color(id_min);
        message += "<br><font color=\"green\">AR MIN : " + std::to_string(metrics->at(curr_mesh_id).AR_min) + "</font>";
    }

    if (ui->max_rb->isChecked() || ui->avg_rb->isChecked())
    {
        set_max_color(id_max);
        message += "<br><font color=\"blue\">AR MAX : " + std::to_string(metrics->at(curr_mesh_id).AR_max)+ "</font>";
    }

    if (ui->avg_rb->isChecked())
    {
        message += "<br>AR AVG : " + std::to_string(metrics->at(curr_mesh_id).AR_avg);
    }

    if (ui->poly_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).AR_poly_min_id;
        id_max = metrics->at(curr_mesh_id).AR_poly_max_id;

        set_min_color(id_min);
        set_max_color(id_max);

        message += "<br><font color=\"green\">AR POLY MIN : " + std::to_string(metrics->at(curr_mesh_id).AR_poly_min) + "</font>";
        message += "<br><font color=\"blue\">AR POLY MAX : " + std::to_string(metrics->at(curr_mesh_id).AR_poly_max) + "</font>";
        message += "<br>AR POLY AVG : " + std::to_string(metrics->at(curr_mesh_id).AR_poly_avg);
    }

    d->get_parametric_mesh(static_cast<uint>(curr_mesh_id))->updateGL();
    ui->mesh_metrics_canvas->updateGL();

    ui->info_text->setHtml(message.c_str());
}

void MeshMetricsGraphicWidget::show_ke ()
{
    mesh_with_metrics.at(0)->poly_set_color(cinolib::Color::WHITE());

    std::string message = "";

    uint id_min = metrics->at(curr_mesh_id).KE_min_id;
    uint id_max = metrics->at(curr_mesh_id).KE_max_id;

    if (ui->min_rb->isChecked() || ui->avg_rb->isChecked())
    {
        set_min_color(id_min);
        message += "<br><font color=\"green\">KE MIN : " + std::to_string(metrics->at(curr_mesh_id).KE_min) + "</font>";
    }

    if (ui->max_rb->isChecked() || ui->avg_rb->isChecked())
    {
        set_max_color(id_max);
        message += "<br><font color=\"blue\">KE MAX : " + std::to_string(metrics->at(curr_mesh_id).KE_max) + "</font>";
    }

    if (ui->avg_rb->isChecked())
    {
        message += "<br>KE AVG : " + std::to_string(metrics->at(curr_mesh_id).KE_avg);
    }

    if (ui->poly_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).KE_poly_min_id;
        id_max = metrics->at(curr_mesh_id).KE_poly_max_id;

        set_min_color(id_min);
        set_max_color(id_max);

        message += "<br><font color=\"green\">KE POLY MIN : " + std::to_string(metrics->at(curr_mesh_id).KE_poly_min) + "</font>";
        message += "<br><font color=\"blue\">KE POLY MAX : " + std::to_string(metrics->at(curr_mesh_id).KE_poly_max) + "</font>";
        message += "<br>KE POLY AVG : " + std::to_string(metrics->at(curr_mesh_id).KE_poly_avg);
    }

    d->get_parametric_mesh(static_cast<uint>(curr_mesh_id))->updateGL();
    ui->mesh_metrics_canvas->updateGL();

    ui->info_text->setHtml(message.c_str());
}

void MeshMetricsGraphicWidget::show_kar ()
{
    mesh_with_metrics.at(0)->poly_set_color(cinolib::Color::WHITE());

    std::string message = "";

    uint id_min = metrics->at(curr_mesh_id).KAR_min_id;
    uint id_max = metrics->at(curr_mesh_id).KAR_max_id;

    if (ui->min_rb->isChecked() || ui->avg_rb->isChecked())
    {
        set_min_color(id_min);
        message += "<br><font color=\"green\">KAR MIN : " + std::to_string(metrics->at(curr_mesh_id).KAR_min) + "</font>";
    }

    if (ui->max_rb->isChecked() || ui->avg_rb->isChecked())
    {
        set_max_color(id_max);
        message += "<br><font color=\"blue\">KAR MAX : " + std::to_string(metrics->at(curr_mesh_id).KAR_max) + "</font>";
    }

    if (ui->avg_rb->isChecked())
    {
        message += "<br>KAR AVG : " + std::to_string(metrics->at(curr_mesh_id).KAR_avg);
    }

    if (ui->poly_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).KAR_poly_min_id;
        id_max = metrics->at(curr_mesh_id).KAR_poly_max_id;

        set_min_color(id_min);
        set_max_color(id_max);

        message += "<br><font color=\"green\">KAR POLY MIN : " + std::to_string(metrics->at(curr_mesh_id).KAR_poly_min) + "</font>";
        message += "<br><font color=\"blue\">KAR POLY MAX : " + std::to_string(metrics->at(curr_mesh_id).KAR_poly_max) + "</font>";
        message += "<br>KAR POLY AVG : " + std::to_string(metrics->at(curr_mesh_id).KAR_poly_avg);
    }

    d->get_parametric_mesh(static_cast<uint>(curr_mesh_id))->updateGL();
    ui->mesh_metrics_canvas->updateGL();

    ui->info_text->setHtml(message.c_str());
}

void MeshMetricsGraphicWidget::show_par ()
{
    mesh_with_metrics.at(0)->poly_set_color(cinolib::Color::WHITE());

    std::string message = "";

    uint id_min = metrics->at(curr_mesh_id).APR_min_id;
    uint id_max = metrics->at(curr_mesh_id).APR_max_id;

    if (ui->min_rb->isChecked() || ui->avg_rb->isChecked())
    {
        set_min_color(id_min);
        message += "<br><font color=\"green\">PAR MIN : " + std::to_string(metrics->at(curr_mesh_id).APR_min) + "</font>";
    }

    if (ui->max_rb->isChecked() || ui->avg_rb->isChecked())
    {
        set_max_color(id_max);
        message += "<br><font color=\"blue\">PAR MAX : " + std::to_string(metrics->at(curr_mesh_id).APR_max) + "</font>";
    }

    if (ui->avg_rb->isChecked())
    {
        message += "<br>PAR AVG : " + std::to_string(metrics->at(curr_mesh_id).APR_avg);
    }

    if (ui->poly_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).APR_poly_min_id;
        id_max = metrics->at(curr_mesh_id).APR_poly_max_id;

        set_min_color(id_min);
        set_max_color(id_max);

        message += "<br><font color=\"green\">PAR POLY MIN : " + std::to_string(metrics->at(curr_mesh_id).APR_poly_min) + "</font>";
        message += "<br><font color=\"blue\">PAR POLY MAX : " + std::to_string(metrics->at(curr_mesh_id).APR_poly_max) + "</font>";
        message += "<br>PAR POLY AVG : " + std::to_string(metrics->at(curr_mesh_id).APR_poly_avg);
    }

    d->get_parametric_mesh(static_cast<uint>(curr_mesh_id))->updateGL();
    ui->mesh_metrics_canvas->updateGL();

    ui->info_text->setHtml(message.c_str());
}

void MeshMetricsGraphicWidget::show_ma ()
{
    mesh_with_metrics.at(0)->poly_set_color(cinolib::Color::WHITE());

    std::string message = "";

    uint id_min = metrics->at(curr_mesh_id).MA_min_id;
    uint id_max = metrics->at(curr_mesh_id).MA_max_id;

    if (ui->min_rb->isChecked() || ui->avg_rb->isChecked())
    {
        set_min_color(id_min);
        message += "<br><font color=\"green\">MA MIN : " + std::to_string(metrics->at(curr_mesh_id).MA_min) + "</font>";
    }

    if (ui->max_rb->isChecked() || ui->avg_rb->isChecked())
    {
        set_max_color(id_max);
        message += "<br><font color=\"blue\">MA MAX : " + std::to_string(metrics->at(curr_mesh_id).MA_max) + "</font>";
    }

    if (ui->avg_rb->isChecked())
    {
        message += "<br>MA AVG : " + std::to_string(metrics->at(curr_mesh_id).MA_avg);
    }

    if (ui->poly_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).MA_poly_min_id;
        id_max = metrics->at(curr_mesh_id).MA_poly_max_id;

        set_min_color(id_min);
        set_max_color(id_max);

        message += "<br><font color=\"green\">MA POLY MIN : " + std::to_string(metrics->at(curr_mesh_id).MA_poly_min) + "</font>";
        message += "<br><font color=\"blue\">MA POLY MAX : " + std::to_string(metrics->at(curr_mesh_id).MA_poly_max) + "</font>";
        message += "<br>MA POLY AVG : " + std::to_string(metrics->at(curr_mesh_id).MA_poly_avg);
    }

    d->get_parametric_mesh(static_cast<uint>(curr_mesh_id))->updateGL();
    ui->mesh_metrics_canvas->updateGL();

    ui->info_text->setHtml(message.c_str());
}

void MeshMetricsGraphicWidget::show_se ()
{
    mesh_with_metrics.at(0)->poly_set_color(cinolib::Color::WHITE());

    std::string message = "";

    uint id_min = metrics->at(curr_mesh_id).SE_min_id;
    uint id_max = metrics->at(curr_mesh_id).SE_max_id;

    if (ui->min_rb->isChecked() || ui->avg_rb->isChecked())
    {
        set_min_color(id_min);
        message += "<br><font color=\"green\">SE MIN : " + std::to_string(metrics->at(curr_mesh_id).SE_min) + "</font>";
    }

    if (ui->max_rb->isChecked() || ui->avg_rb->isChecked())
    {
        set_max_color(id_max);
        message += "<br><font color=\"blue\">SE MAX : " + std::to_string(metrics->at(curr_mesh_id).SE_max) + "</font>";
    }

    if (ui->avg_rb->isChecked())
    {
        message += "<br>SE AVG : " + std::to_string(metrics->at(curr_mesh_id).SE_avg);
    }

    if (ui->poly_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).SE_poly_min_id;
        id_max = metrics->at(curr_mesh_id).SE_poly_max_id;

        set_min_color(id_min);
        set_max_color(id_max);

        message += "<br>SE POLY MIN : " + std::to_string(metrics->at(curr_mesh_id).SE_poly_min);
        message += "<br>SE POLY MAX : " + std::to_string(metrics->at(curr_mesh_id).SE_poly_max);
        message += "<br>SE POLY AVG : " + std::to_string(metrics->at(curr_mesh_id).SE_poly_avg);
    }

    d->get_parametric_mesh(static_cast<uint>(curr_mesh_id))->updateGL();
    ui->mesh_metrics_canvas->updateGL();

    ui->info_text->setHtml(message.c_str());
}

void MeshMetricsGraphicWidget::show_er ()
{
    mesh_with_metrics.at(0)->poly_set_color(cinolib::Color::WHITE());

    std::string message = "";

    uint id_min = metrics->at(curr_mesh_id).ER_min_id;
    uint id_max = metrics->at(curr_mesh_id).ER_max_id;

    if (ui->min_rb->isChecked() || ui->avg_rb->isChecked())
    {
        set_min_color(id_min);
        message += "<br><font color=\"green\">ER MIN : " + std::to_string(metrics->at(curr_mesh_id).ER_min) + "</font>";
    }

    if (ui->max_rb->isChecked() || ui->avg_rb->isChecked())
    {
        set_max_color(id_max);
        message += "<br><font color=\"blue\">ER MAX : " + std::to_string(metrics->at(curr_mesh_id).ER_max) + "</font>";
    }

    if (ui->avg_rb->isChecked())
    {
        message += "<br>ER AVG : " + std::to_string(metrics->at(curr_mesh_id).ER_avg);
    }

    if (ui->poly_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).ER_poly_min_id;
        id_max = metrics->at(curr_mesh_id).ER_poly_max_id;

        set_min_color(id_min);
        set_max_color(id_max);

        message += "<br>ER POLY MIN : " + std::to_string(metrics->at(curr_mesh_id).ER_poly_min);
        message += "<br>ER POLY MAX : " + std::to_string(metrics->at(curr_mesh_id).ER_poly_max);
        message += "<br>ER POLY AVG : " + std::to_string(metrics->at(curr_mesh_id).ER_poly_avg);
    }

    d->get_parametric_mesh(static_cast<uint>(curr_mesh_id))->updateGL();
    ui->mesh_metrics_canvas->updateGL();

    ui->info_text->setHtml(message.c_str());
}

void MeshMetricsGraphicWidget::show_mpd ()
{
    mesh_with_metrics.at(0)->poly_set_color(cinolib::Color::WHITE());

    std::string message = "";

    uint id_min = metrics->at(curr_mesh_id).MPD_min_id;
    uint id_max = metrics->at(curr_mesh_id).MPD_max_id;

    if (ui->min_rb->isChecked() || ui->avg_rb->isChecked())
    {
        set_min_color(id_min);
        message += "<br><font color=\"green\">MPD MIN : " + std::to_string(metrics->at(curr_mesh_id).MPD_min) + "</font>";
    }

    if (ui->max_rb->isChecked() || ui->avg_rb->isChecked())
    {
        set_max_color(id_max);
        message += "<br><font color=\"blue\">MPD MAX : " + std::to_string(metrics->at(curr_mesh_id).MPD_max) + "</font>";
    }

    if (ui->avg_rb->isChecked())
    {
        message += "<br>MDP AVG : " + std::to_string(metrics->at(curr_mesh_id).MPD_avg);
    }

    if (ui->poly_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).MPD_poly_min_id;
        id_max = metrics->at(curr_mesh_id).MPD_poly_max_id;

        set_min_color(id_min);
        set_max_color(id_max);

        message += "<br>MPD POLY MIN : " + std::to_string(metrics->at(curr_mesh_id).MPD_poly_min);
        message += "<br>MPD POLY MAX : " + std::to_string(metrics->at(curr_mesh_id).MPD_poly_max);
        message += "<br>MPD POLY AVG : " + std::to_string(metrics->at(curr_mesh_id).MPD_poly_avg);
    }

    d->get_parametric_mesh(static_cast<uint>(curr_mesh_id))->updateGL();
    ui->mesh_metrics_canvas->updateGL();

    ui->info_text->setHtml(message.c_str());
}

void MeshMetricsGraphicWidget::show_ns ()
{
    mesh_with_metrics.at(0)->poly_set_color(cinolib::Color::WHITE());

    std::string message = "";

    uint id_min = metrics->at(curr_mesh_id).NS_min_id;
    uint id_max = metrics->at(curr_mesh_id).NS_max_id;

    if (ui->min_rb->isChecked() || ui->avg_rb->isChecked())
    {
        set_min_color(id_min);
        message += "<br><font color=\"green\">AR MIN : " + std::to_string(metrics->at(curr_mesh_id).NS_min) + "</font>";
    }

    if (ui->max_rb->isChecked() || ui->avg_rb->isChecked())
    {
        set_max_color(id_max);
        message += "<br><font color=\"blue\">AR MAX : " + std::to_string(metrics->at(curr_mesh_id).NS_max)+ "</font>";
    }

    if (ui->avg_rb->isChecked())
    {
        message += "<br>AR AVG : " + std::to_string(metrics->at(curr_mesh_id).NS_avg);
    }

    if (ui->poly_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).NS_poly_min_id;
        id_max = metrics->at(curr_mesh_id).NS_poly_max_id;

        set_min_color(id_min);
        set_max_color(id_max);

        message += "<br><font color=\"green\">NS POLY MIN : " + std::to_string(metrics->at(curr_mesh_id).NS_poly_min) + "</font>";
        message += "<br><font color=\"blue\">NS POLY MAX : " + std::to_string(metrics->at(curr_mesh_id).NS_poly_max) + "</font>";
        message += "<br>NS POLY AVG : " + std::to_string(metrics->at(curr_mesh_id).NS_poly_avg);
    }

    d->get_parametric_mesh(static_cast<uint>(curr_mesh_id))->updateGL();
    ui->mesh_metrics_canvas->updateGL();

    ui->info_text->setHtml(message.c_str());
}

void MeshMetricsGraphicWidget::show_mxa ()
{
    mesh_with_metrics.at(0)->poly_set_color(cinolib::Color::WHITE());

    std::string message = "";

    uint id_min = metrics->at(curr_mesh_id).MXA_min_id;
    uint id_max = metrics->at(curr_mesh_id).MXA_max_id;

    if (ui->min_rb->isChecked() || ui->avg_rb->isChecked())
    {
        set_min_color(id_min);
        message += "<br><font color=\"green\">MXA MIN : " + std::to_string(metrics->at(curr_mesh_id).MXA_min) + "</font>";
    }

    if (ui->max_rb->isChecked() || ui->avg_rb->isChecked())
    {
        set_max_color(id_max);
        message += "<br><font color=\"blue\">MXA MAX : " + std::to_string(metrics->at(curr_mesh_id).MXA_max)+ "</font>";
    }

    if (ui->avg_rb->isChecked())
    {
        message += "<br>MXA AVG : " + std::to_string(metrics->at(curr_mesh_id).MXA_avg);
    }

    if (ui->poly_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).MXA_poly_min_id;
        id_max = metrics->at(curr_mesh_id).MXA_poly_max_id;

        set_min_color(id_min);
        set_max_color(id_max);

        message += "<br><font color=\"green\">MXA POLY MIN : " + std::to_string(metrics->at(curr_mesh_id).MXA_poly_min) + "</font>";
        message += "<br><font color=\"blue\">MXA POLY MAX : " + std::to_string(metrics->at(curr_mesh_id).MXA_poly_max) + "</font>";
        message += "<br>MXA POLY AVG : " + std::to_string(metrics->at(curr_mesh_id).MXA_poly_avg);
    }

    d->get_parametric_mesh(static_cast<uint>(curr_mesh_id))->updateGL();
    ui->mesh_metrics_canvas->updateGL();

    ui->info_text->setHtml(message.c_str());
}

void MeshMetricsGraphicWidget::show_sr ()
{
    mesh_with_metrics.at(0)->poly_set_color(cinolib::Color::WHITE());

    std::string message = "";

    uint id_min = metrics->at(curr_mesh_id).SR_min_id;
    uint id_max = metrics->at(curr_mesh_id).SR_max_id;

    if (ui->min_rb->isChecked() || ui->avg_rb->isChecked())
    {
        set_min_color(id_min);
        message += "<br><font color=\"green\">SR MIN : " + std::to_string(metrics->at(curr_mesh_id).SR_min) + "</font>";
    }

    if (ui->max_rb->isChecked() || ui->avg_rb->isChecked())
    {
        set_max_color(id_max);
        message += "<br><font color=\"blue\">SR MAX : " + std::to_string(metrics->at(curr_mesh_id).SR_max)+ "</font>";
    }

    if (ui->avg_rb->isChecked())
    {
        message += "<br>SR AVG : " + std::to_string(metrics->at(curr_mesh_id).SR_avg);
    }

    if (ui->poly_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).SR_poly_min_id;
        id_max = metrics->at(curr_mesh_id).SR_poly_max_id;

        set_min_color(id_min);
        set_max_color(id_max);

        message += "<br><font color=\"green\">SR POLY MIN : " + std::to_string(metrics->at(curr_mesh_id).SR_poly_min) + "</font>";
        message += "<br><font color=\"blue\">SR POLY MAX : " + std::to_string(metrics->at(curr_mesh_id).SR_poly_max) + "</font>";
        message += "<br>SR POLY AVG : " + std::to_string(metrics->at(curr_mesh_id).SR_poly_avg);
    }

    d->get_parametric_mesh(static_cast<uint>(curr_mesh_id))->updateGL();
    ui->mesh_metrics_canvas->updateGL();

    ui->info_text->setHtml(message.c_str());
}

void MeshMetricsGraphicWidget::show_vem ()
{
    mesh_with_metrics.at(0)->poly_set_color(cinolib::Color::WHITE());

    std::string message = "";

    uint id_min = metrics->at(curr_mesh_id).VEM_min_id;
    uint id_max = metrics->at(curr_mesh_id).VEM_max_id;

    if (ui->min_rb->isChecked() || ui->avg_rb->isChecked())
    {
        set_min_color(id_min);
        message += "<br><font color=\"green\">VEM MIN : " + std::to_string(metrics->at(curr_mesh_id).VEM_min) + "</font>";
    }

    if (ui->max_rb->isChecked() || ui->avg_rb->isChecked())
    {
        set_max_color(id_max);
        message += "<br><font color=\"blue\">VEM MAX : " + std::to_string(metrics->at(curr_mesh_id).VEM_max)+ "</font>";
    }

    if (ui->avg_rb->isChecked())
    {
        message += "<br>VEM AVG : " + std::to_string(metrics->at(curr_mesh_id).VEM_avg);
    }

    if (ui->poly_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).VEM_poly_min_id;
        id_max = metrics->at(curr_mesh_id).VEM_poly_max_id;

        set_min_color(id_min);
        set_max_color(id_max);

        message += "<br><font color=\"green\">VEM POLY MIN : " + std::to_string(metrics->at(curr_mesh_id).VEM_poly_min) + "</font>";
        message += "<br><font color=\"blue\">VEM POLY MAX : " + std::to_string(metrics->at(curr_mesh_id).VEM_poly_max) + "</font>";
        message += "<br>VEM POLY AVG : " + std::to_string(metrics->at(curr_mesh_id).VEM_poly_avg);
    }

    d->get_parametric_mesh(static_cast<uint>(curr_mesh_id))->updateGL();
    ui->mesh_metrics_canvas->updateGL();

    ui->info_text->setHtml(message.c_str());
}

void MeshMetricsGraphicWidget::show_vema ()
{
    mesh_with_metrics.at(0)->poly_set_color(cinolib::Color::WHITE());

    std::string message = "";

    uint id_min = metrics->at(curr_mesh_id).VEMA_min_id;
    uint id_max = metrics->at(curr_mesh_id).VEMA_max_id;

    if (ui->min_rb->isChecked() || ui->avg_rb->isChecked())
    {
        set_min_color(id_min);
        message += "<br><font color=\"green\">VEMA MIN : " + std::to_string(metrics->at(curr_mesh_id).VEMA_min) + "</font>";
    }

    if (ui->max_rb->isChecked() || ui->avg_rb->isChecked())
    {
        set_max_color(id_max);
        message += "<br><font color=\"blue\">VEMA MAX : " + std::to_string(metrics->at(curr_mesh_id).VEMA_max)+ "</font>";
    }

    if (ui->avg_rb->isChecked())
    {
        message += "<br>VEMA SUM : " + std::to_string(metrics->at(curr_mesh_id).VEMA_sum);
    }

    if (ui->poly_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).VEMA_poly_min_id;
        id_max = metrics->at(curr_mesh_id).VEMA_poly_max_id;

        set_min_color(id_min);
        set_max_color(id_max);

        message += "<br><font color=\"green\">VEMA POLY MIN : " + std::to_string(metrics->at(curr_mesh_id).VEMA_poly_min) + "</font>";
        message += "<br><font color=\"blue\">VEMA POLY MAX : " + std::to_string(metrics->at(curr_mesh_id).VEMA_poly_max) + "</font>";

        double VEMA = sqrt(metrics->at(curr_mesh_id).VEMA_sum + metrics->at(curr_mesh_id).VEMA_poly_sum);
        message += "<br>VEMA : " + std::to_string(VEMA);
    }

    d->get_parametric_mesh(static_cast<uint>(curr_mesh_id))->updateGL();
    ui->mesh_metrics_canvas->updateGL();

    ui->info_text->setHtml(message.c_str());
}


void MeshMetricsGraphicWidget::show_min()
{
    mesh_with_metrics.at(0)->poly_set_color(cinolib::Color::WHITE());

    uint id;
    std::string message = "";

    if (ui->ic_rb->isChecked())
    {
        id = metrics->at(curr_mesh_id).IC_min_id;
        message = "IC MIN : " + std::to_string(metrics->at(curr_mesh_id).IC_min);
    }
    else
    if (ui->cc_rb->isChecked())
    {
        id = metrics->at(curr_mesh_id).CC_min_id;
        message = "CC MIN : " + std::to_string(metrics->at(curr_mesh_id).CC_min);
    }
    else
    if (ui->cr_rb->isChecked())
    {
        id = metrics->at(curr_mesh_id).CR_min_id;
        message = "CR MIN : " + std::to_string(metrics->at(curr_mesh_id).CR_min);
    }
    else
    if (ui->ar_rb->isChecked())
    {
        id = metrics->at(curr_mesh_id).AR_min_id;
        message = "AR MIN : " + std::to_string(metrics->at(curr_mesh_id).AR_min);
    }
    else
    if (ui->ke_rb->isChecked())
    {
        id = metrics->at(curr_mesh_id).KE_min_id;
        message = "KE MIN : " + std::to_string(metrics->at(curr_mesh_id).KE_min);
    }
    else
    if (ui->kar_rb->isChecked())
    {
        id = metrics->at(curr_mesh_id).KAR_min_id;
        message = "KAR MIN : " + std::to_string(metrics->at(curr_mesh_id).KAR_min);
    }
    else
    if (ui->par_rb->isChecked())
    {
        id = metrics->at(curr_mesh_id).APR_min_id;
        message = "PAR MIN : " + std::to_string(metrics->at(curr_mesh_id).APR_min);
    }
    else
    if (ui->ma_rb->isChecked())
    {
        id = metrics->at(curr_mesh_id).MA_min_id;
        message = "MA MIN : " + std::to_string(metrics->at(curr_mesh_id).MA_min);
    }
    else
    if (ui->se_rb->isChecked())
    {
        id = metrics->at(curr_mesh_id).SE_min_id;
        message = "SE MIN : " + std::to_string(metrics->at(curr_mesh_id).SE_min);
    }
    else
    if (ui->er_rb->isChecked())
    {
        id = metrics->at(curr_mesh_id).ER_min_id;
        message = "ER MIN : " + std::to_string(metrics->at(curr_mesh_id).ER_min);
    }
    else
    if (ui->mpd_rb->isChecked())
    {
        id = metrics->at(curr_mesh_id).MPD_min_id;
        message = "MPD MIN : " + std::to_string(metrics->at(curr_mesh_id).MPD_min);
    }
    else
    if (ui->ns_rb->isChecked())
    {
        id = metrics->at(curr_mesh_id).NS_min_id;
        message = "NS MIN : " + std::to_string(metrics->at(curr_mesh_id).NS_min);
    }
    else
    if (ui->mxa_rb->isChecked())
    {
        id = metrics->at(curr_mesh_id).MXA_min_id;
        message = "MXA MIN : " + std::to_string(metrics->at(curr_mesh_id).MXA_min);
    }
    else
    if (ui->sr_rb->isChecked())
    {
        id = metrics->at(curr_mesh_id).SR_min_id;
        message = "SR MIN : " + std::to_string(metrics->at(curr_mesh_id).SR_min);
    }
    else
    if (ui->vem_rb->isChecked())
    {
        id = metrics->at(curr_mesh_id).VEM_min_id;
        message = "VEM MIN : " + std::to_string(metrics->at(curr_mesh_id).VEM_min);
    }
    else
    if (ui->vema_rb->isChecked())
    {
        id = metrics->at(curr_mesh_id).VEMA_min_id;
        message = "VEMA MIN : " + std::to_string(metrics->at(curr_mesh_id).VEMA_min);
    }
    else
    {
        return;
    }

    set_min_color(id);

    d->get_parametric_mesh(static_cast<uint>(curr_mesh_id))->updateGL();
    ui->mesh_metrics_canvas->updateGL();

    message = "<br><font color=\"green\">" + message + "</font>";

    ui->info_text->setHtml(message.c_str());
}

void MeshMetricsGraphicWidget::show_max()
{
    mesh_with_metrics.at(0)->poly_set_color(cinolib::Color::WHITE());

    uint id;
    std::string message = "";

    if (ui->ic_rb->isChecked())
    {
        id = metrics->at(curr_mesh_id).IC_max_id;
        message = "IC MAX : " + std::to_string(metrics->at(curr_mesh_id).IC_max);
    }
    else
    if (ui->cc_rb->isChecked())
    {
        id = metrics->at(curr_mesh_id).CC_max_id;
        message = "CC MAX : " + std::to_string(metrics->at(curr_mesh_id).CC_max);
    }
    else
    if (ui->cr_rb->isChecked())
    {
        id = metrics->at(curr_mesh_id).CR_max_id;
        message = "CR MAX : " + std::to_string(metrics->at(curr_mesh_id).CR_max);
    }
    else
    if (ui->ar_rb->isChecked())
    {
        id = metrics->at(curr_mesh_id).AR_max_id;
        message = "AR MAX : " + std::to_string(metrics->at(curr_mesh_id).AR_max);
    }
    else
    if (ui->ke_rb->isChecked())
    {
        id = metrics->at(curr_mesh_id).KE_max_id;
        message = "KE MAX : " + std::to_string(metrics->at(curr_mesh_id).KE_max);
    }
    else
    if (ui->kar_rb->isChecked())
    {
        id = metrics->at(curr_mesh_id).KAR_max_id;
        message = "KAR MAX : " + std::to_string(metrics->at(curr_mesh_id).KAR_max);
    }
    else
    if (ui->par_rb->isChecked())
    {
        id = metrics->at(curr_mesh_id).APR_max_id;
        message = "PAR MAX : " + std::to_string(metrics->at(curr_mesh_id).APR_max);
    }
    else
    if (ui->ma_rb->isChecked())
    {
        id = metrics->at(curr_mesh_id).MA_max_id;
        message = "MA MAX : " + std::to_string(metrics->at(curr_mesh_id).MA_max);
    }
    else
    if (ui->se_rb->isChecked())
    {
        id = metrics->at(curr_mesh_id).SE_max_id;
        message = "SE MAX : " + std::to_string(metrics->at(curr_mesh_id).SE_max);
    }
    else
    if (ui->er_rb->isChecked())
    {
        id = metrics->at(curr_mesh_id).ER_max_id;
        message = "ER MAX : " + std::to_string(metrics->at(curr_mesh_id).ER_max);
    }
    else
    if (ui->mpd_rb->isChecked())
    {
        id = metrics->at(curr_mesh_id).MPD_max_id;
        message = "MPD MAX : " + std::to_string(metrics->at(curr_mesh_id).MPD_max);
    }
    else
    if (ui->ns_rb->isChecked())
    {
        id = metrics->at(curr_mesh_id).NS_max_id;
        message = "NS MAX : " + std::to_string(metrics->at(curr_mesh_id).NS_max);
    }
    else
    if (ui->mxa_rb->isChecked())
    {
        id = metrics->at(curr_mesh_id).MXA_max_id;
        message = "MXA MAX : " + std::to_string(metrics->at(curr_mesh_id).MXA_max);
    }
    else
    if (ui->sr_rb->isChecked())
    {
        id = metrics->at(curr_mesh_id).SR_max_id;
        message = "SR MAX : " + std::to_string(metrics->at(curr_mesh_id).SR_max);
    }
    else
    if (ui->vem_rb->isChecked())
    {
        id = metrics->at(curr_mesh_id).VEM_max_id;
        message = "VEM MAX : " + std::to_string(metrics->at(curr_mesh_id).VEM_max);
    }
    else
    if (ui->vema_rb->isChecked())
    {
        id = metrics->at(curr_mesh_id).VEMA_max_id;
        message = "VEMA MAX : " + std::to_string(metrics->at(curr_mesh_id).VEMA_max);
    }
    else
    {
        return;
    }

    set_max_color(id);

    d->get_parametric_mesh(static_cast<uint>(curr_mesh_id))->updateGL();
    ui->mesh_metrics_canvas->updateGL();

    message = "<br><font color=\"blue\">" + message + "</font>";

    ui->info_text->setHtml(message.c_str());
}

void MeshMetricsGraphicWidget::show_avg()
{
    mesh_with_metrics.at(0)->poly_set_color(cinolib::Color::WHITE());

    uint id_min, id_max;
    std::string message = "";

    if (ui->ic_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).IC_min_id;
        id_max = metrics->at(curr_mesh_id).IC_max_id;
        message += "<br><font color=\"green\">IC MIN : " + std::to_string(metrics->at(curr_mesh_id).IC_min) + "</font>";
        message += "<br><font color=\"blue\">IC MAX : " + std::to_string(metrics->at(curr_mesh_id).IC_max) + "</font>";
        message += "<br>IC AVG : " + std::to_string(metrics->at(curr_mesh_id).IC_avg);
    }
    else
    if (ui->cc_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).CC_min_id;
        id_max = metrics->at(curr_mesh_id).CC_max_id;
        message += "<br><font color=\"green\">CC MIN : " + std::to_string(metrics->at(curr_mesh_id).CC_min) + "</font>";
        message += "<br><font color=\"blue\">CC MAX : " + std::to_string(metrics->at(curr_mesh_id).CC_max) + "</font>";
        message += "<br>CC AVG : " + std::to_string(metrics->at(curr_mesh_id).CC_avg);
    }
    else
    if (ui->cr_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).CR_min_id;
        id_max = metrics->at(curr_mesh_id).CR_max_id;
        message += "<br><font color=\"green\">CR MIN : " + std::to_string(metrics->at(curr_mesh_id).CR_min) + "</font>";
        message += "<br><font color=\"blue\">CR MAX : " + std::to_string(metrics->at(curr_mesh_id).CR_max) + "</font>";
        message += "<br>CR AVG : " + std::to_string(metrics->at(curr_mesh_id).CR_avg);
    }
    else
    if (ui->ar_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).AR_min_id;
        id_max = metrics->at(curr_mesh_id).AR_max_id;
        message += "<br><font color=\"green\">AR MIN : " + std::to_string(metrics->at(curr_mesh_id).AR_min) + "</font>";
        message += "<br><font color=\"blue\">AR MAX : " + std::to_string(metrics->at(curr_mesh_id).AR_max) + "</font>";
        message += "<br>AR AVG : " + std::to_string(metrics->at(curr_mesh_id).AR_avg);
    }
    else
    if (ui->ke_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).KE_min_id;
        id_max = metrics->at(curr_mesh_id).KE_max_id;
        message += "<br><font color=\"green\">KE MIN : " + std::to_string(metrics->at(curr_mesh_id).KE_min) + "</font>";
        message += "<br><font color=\"blue\">KE MAX : " + std::to_string(metrics->at(curr_mesh_id).KE_max) + "</font>";
        message += "<br>KE AVG : " + std::to_string(metrics->at(curr_mesh_id).KE_avg);
    }
    else
    if (ui->kar_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).KAR_min_id;
        id_max = metrics->at(curr_mesh_id).KAR_max_id;
        message += "<br><font color=\"green\">KAR MIN : " + std::to_string(metrics->at(curr_mesh_id).KAR_min) + "</font>";
        message += "<br><font color=\"blue\">KAR MAX : " + std::to_string(metrics->at(curr_mesh_id).KAR_max) + "</font>";
        message += "<br>KAR AVG : " + std::to_string(metrics->at(curr_mesh_id).KAR_avg);
    }
    else
    if (ui->par_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).APR_min_id;
        id_max = metrics->at(curr_mesh_id).APR_max_id;
        message += "<br><font color=\"green\">PAR MIN : " + std::to_string(metrics->at(curr_mesh_id).APR_min) + "</font>";
        message += "<br><font color=\"blue\">PAR MAX : " + std::to_string(metrics->at(curr_mesh_id).APR_max) + "</font>";
        message += "<br>PAR AVG : " + std::to_string(metrics->at(curr_mesh_id).APR_avg);
    }
    else
    if (ui->ma_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).MA_min_id;
        id_max = metrics->at(curr_mesh_id).MA_max_id;
        message += "<br><font color=\"green\">MA MIN : " + std::to_string(metrics->at(curr_mesh_id).MA_min) + "</font>";
        message += "<br><font color=\"blue\">MA MAX : " + std::to_string(metrics->at(curr_mesh_id).MA_max) + "</font>";
        message += "<br>MA AVG : " + std::to_string(metrics->at(curr_mesh_id).MA_avg);
    }
    else
    if (ui->se_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).SE_min_id;
        id_max = metrics->at(curr_mesh_id).SE_max_id;
        message += "<br><font color=\"green\">SE MIN : " + std::to_string(metrics->at(curr_mesh_id).SE_min) + "</font>";
        message += "<br><font color=\"blue\">SE MAX : " + std::to_string(metrics->at(curr_mesh_id).SE_max) + "</font>";
        message += "<br>SE AVG : " + std::to_string(metrics->at(curr_mesh_id).SE_avg);
    }
    else
    if (ui->er_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).ER_min_id;
        id_max = metrics->at(curr_mesh_id).ER_max_id;
        message += "<br><font color=\"green\">ER MIN : " + std::to_string(metrics->at(curr_mesh_id).ER_min) + "</font>";
        message += "<br><font color=\"blue\">ER MIN : " + std::to_string(metrics->at(curr_mesh_id).ER_max) + "</font>";
        message += "<br>ER MIN : " + std::to_string(metrics->at(curr_mesh_id).ER_avg);
    }
    else
    if (ui->mpd_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).MPD_min_id;
        id_max = metrics->at(curr_mesh_id).MPD_max_id;
        message += "<br><font color=\"green\">MPD MIN : " + std::to_string(metrics->at(curr_mesh_id).MPD_min) + "</font>";
        message += "<br><font color=\"blue\">MPD MAX : " + std::to_string(metrics->at(curr_mesh_id).MPD_max) + "</font>";
        message += "<br>MPD AVG : " + std::to_string(metrics->at(curr_mesh_id).MPD_avg);
    }
    else
    if (ui->ns_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).NS_min_id;
        id_max = metrics->at(curr_mesh_id).NS_max_id;
        message += "<br><font color=\"green\">NS MIN : " + std::to_string(metrics->at(curr_mesh_id).NS_min) + "</font>";
        message += "<br><font color=\"blue\">NS MAX : " + std::to_string(metrics->at(curr_mesh_id).NS_max) + "</font>";
        message += "<br>NS AVG : " + std::to_string(metrics->at(curr_mesh_id).NS_avg);
    }
    else
    if (ui->mxa_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).MXA_min_id;
        id_max = metrics->at(curr_mesh_id).MXA_max_id;
        message += "<br><font color=\"green\">MXA MIN : " + std::to_string(metrics->at(curr_mesh_id).MXA_min) + "</font>";
        message += "<br><font color=\"blue\">MXA MAX : " + std::to_string(metrics->at(curr_mesh_id).MXA_max) + "</font>";
        message += "<br>MXA AVG : " + std::to_string(metrics->at(curr_mesh_id).MXA_avg);
    }
    else
    if (ui->sr_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).SR_min_id;
        id_max = metrics->at(curr_mesh_id).SR_max_id;
        message += "<br><font color=\"green\">SR MIN : " + std::to_string(metrics->at(curr_mesh_id).SR_min) + "</font>";
        message += "<br><font color=\"blue\">SR MAX : " + std::to_string(metrics->at(curr_mesh_id).SR_max) + "</font>";
        message += "<br>SR AVG : " + std::to_string(metrics->at(curr_mesh_id).SR_avg);
    }
    else
    if (ui->vem_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).VEM_min_id;
        id_max = metrics->at(curr_mesh_id).VEM_max_id;
        message += "<br><font color=\"green\">VEM MIN : " + std::to_string(metrics->at(curr_mesh_id).VEM_min) + "</font>";
        message += "<br><font color=\"blue\">VEM MAX : " + std::to_string(metrics->at(curr_mesh_id).VEM_max) + "</font>";
        message += "<br>VEM AVG : " + std::to_string(metrics->at(curr_mesh_id).VEM_avg);
    }
    else
    if (ui->vema_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).VEMA_min_id;
        id_max = metrics->at(curr_mesh_id).VEMA_max_id;
        message += "<br><font color=\"green\">VEMA MIN : " + std::to_string(metrics->at(curr_mesh_id).VEMA_min) + "</font>";
        message += "<br><font color=\"blue\">VEMA MAX : " + std::to_string(metrics->at(curr_mesh_id).VEMA_max) + "</font>";

        double VEMA = sqrt(metrics->at(curr_mesh_id).VEMA_sum + metrics->at(curr_mesh_id).VEMA_poly_sum);
        message += "<br>VEMA : " + std::to_string(VEMA);
    }
    else
    {
        return;
    }

    set_min_color(id_min);
    set_max_color(id_max);

    d->get_parametric_mesh(static_cast<uint>(curr_mesh_id))->updateGL();
    ui->mesh_metrics_canvas->updateGL();

    ui->info_text->setHtml(message.c_str());
}

void MeshMetricsGraphicWidget::show_poly()
{
    mesh_with_metrics.at(0)->poly_set_color(cinolib::Color::WHITE());

    uint id_min, id_max;
    std::string message = "";

    if (ui->ic_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).IC_poly_min_id;
        id_max = metrics->at(curr_mesh_id).IC_poly_max_id;
        message += "<br><font color=\"green\">IC POLY MIN: " + std::to_string(metrics->at(curr_mesh_id).IC_poly_min) + "</font>";
        message += "<br><font color=\"blue\">IC POLY MAX: " + std::to_string(metrics->at(curr_mesh_id).IC_poly_max) + "</font>";
        message += "<br>IC POLY AVG : " + std::to_string(metrics->at(curr_mesh_id).IC_poly_avg);
    }
    else
    if (ui->cc_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).CC_poly_min_id;
        id_max = metrics->at(curr_mesh_id).CC_poly_max_id;
        message += "<br><font color=\"green\">CC POLY MIN : " + std::to_string(metrics->at(curr_mesh_id).CC_poly_min) + "</font>";
        message += "<br><font color=\"blue\">CC POLY MAX : " + std::to_string(metrics->at(curr_mesh_id).CC_poly_max) + "</font>";
        message += "<br>CC POLY AVG : " + std::to_string(metrics->at(curr_mesh_id).CC_poly_avg);
    }
    else
    if (ui->cr_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).CR_poly_min_id;
        id_max = metrics->at(curr_mesh_id).CR_poly_max_id;
        message += "<br><font color=\"green\">CR POLY MIN : " + std::to_string(metrics->at(curr_mesh_id).CR_poly_min) + "</font>";
        message += "<br><font color=\"blue\">CR POLY MAX : " + std::to_string(metrics->at(curr_mesh_id).CR_poly_max) + "</font>";
        message += "<br>CR POLY AVG : " + std::to_string(metrics->at(curr_mesh_id).CR_poly_avg);
    }
    else
    if (ui->ar_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).AR_poly_min_id;
        id_max = metrics->at(curr_mesh_id).AR_poly_max_id;
        message += "<br><font color=\"green\">AR POLY MIN : " + std::to_string(metrics->at(curr_mesh_id).AR_poly_min) + "</font>";
        message += "<br><font color=\"blue\">AR POLY MAX : " + std::to_string(metrics->at(curr_mesh_id).AR_poly_max) + "</font>";
        message += "<br>AR POLY AVG : " + std::to_string(metrics->at(curr_mesh_id).AR_poly_avg);
    }
    else
    if (ui->ke_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).KE_poly_min_id;
        id_max = metrics->at(curr_mesh_id).KE_poly_max_id;
        message += "<br><font color=\"green\">KE POLY MIN : " + std::to_string(metrics->at(curr_mesh_id).KE_poly_min) + "</font>";
        message += "<br><font color=\"blue\">KE POLY MAX : " + std::to_string(metrics->at(curr_mesh_id).KE_poly_max) + "</font>";
        message += "<br>KE POLY AVG : " + std::to_string(metrics->at(curr_mesh_id).KE_poly_avg);
    }
    else
    if (ui->kar_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).KAR_poly_min_id;
        id_max = metrics->at(curr_mesh_id).KAR_poly_max_id;
        message += "<br><font color=\"green\">KAR POLY MIN : " + std::to_string(metrics->at(curr_mesh_id).KAR_poly_min) + "</font>";
        message += "<br><font color=\"blue\">KAR POLY MAX : " + std::to_string(metrics->at(curr_mesh_id).KAR_poly_max) + "</font>";
        message += "<br>KAR POLY AVG : " + std::to_string(metrics->at(curr_mesh_id).KAR_poly_avg);
    }
    else
    if (ui->par_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).APR_poly_min_id;
        id_max = metrics->at(curr_mesh_id).APR_poly_max_id;
        message += "<br><font color=\"green\">PAR POLY MIN: " + std::to_string(metrics->at(curr_mesh_id).APR_poly_min) + "</font>";
        message += "<br><font color=\"blue\">PAR POLY MAX : " + std::to_string(metrics->at(curr_mesh_id).APR_poly_max) + "</font>";
        message += "<br>PAR POLY AVG : " + std::to_string(metrics->at(curr_mesh_id).APR_poly_avg);
    }
    else
    if (ui->ma_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).MA_poly_min_id;
        id_max = metrics->at(curr_mesh_id).MA_poly_max_id;
        message += "<br><font color=\"green\">MA POLY MIN : " + std::to_string(metrics->at(curr_mesh_id).MA_poly_min) + "</font>";
        message += "<br><font color=\"blue\">MA POLY MAX : " + std::to_string(metrics->at(curr_mesh_id).MA_poly_max) + "</font>";
        message += "<br>MA POLY AVG : " + std::to_string(metrics->at(curr_mesh_id).MA_poly_avg);
    }
    else
    if (ui->se_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).SE_poly_min_id;
        id_max = metrics->at(curr_mesh_id).SE_poly_max_id;
        message += "<br><font color=\"green\">SE POLY MIN : " + std::to_string(metrics->at(curr_mesh_id).SE_poly_min) + "</font>";
        message += "<br><font color=\"blue\">SE POLY MAX : " + std::to_string(metrics->at(curr_mesh_id).SE_poly_max) + "</font>";
        message += "<br>SE POLY AVG : " + std::to_string(metrics->at(curr_mesh_id).SE_poly_avg);
    }
    else
    if (ui->er_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).ER_poly_min_id;
        id_max = metrics->at(curr_mesh_id).ER_poly_max_id;
        message += "<br><font color=\"green\">ER POLY MIN : " + std::to_string(metrics->at(curr_mesh_id).ER_poly_min) + "</font>";
        message += "<br><font color=\"blue\">ER POLY MIN : " + std::to_string(metrics->at(curr_mesh_id).ER_poly_max) + "</font>";
        message += "<br>ER POLY MIN : " + std::to_string(metrics->at(curr_mesh_id).ER_poly_avg);
    }
    else
    if (ui->mpd_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).MPD_poly_min_id;
        id_max = metrics->at(curr_mesh_id).MPD_poly_max_id;
        message += "<br><font color=\"green\">MPD POLY MIN : " + std::to_string(metrics->at(curr_mesh_id).MPD_poly_min) + "</font>";
        message += "<br><font color=\"blue\">MPD POLY MAX : " + std::to_string(metrics->at(curr_mesh_id).MPD_poly_max) + "</font>";
        message += "<br>MPD POLY AVG : " + std::to_string(metrics->at(curr_mesh_id).MPD_poly_avg);
    }
    else
    if (ui->ns_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).NS_poly_min_id;
        id_max = metrics->at(curr_mesh_id).NS_poly_max_id;
        message += "<br><font color=\"green\">NS POLY MIN : " + std::to_string(metrics->at(curr_mesh_id).NS_poly_min) + "</font>";
        message += "<br><font color=\"blue\">NS POLY MAX : " + std::to_string(metrics->at(curr_mesh_id).NS_poly_max) + "</font>";
        message += "<br>NS POLY AVG : " + std::to_string(metrics->at(curr_mesh_id).NS_poly_avg);
    }
    else
    if (ui->mxa_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).MXA_poly_min_id;
        id_max = metrics->at(curr_mesh_id).MXA_poly_max_id;
        message += "<br><font color=\"green\">MXA POLY MIN : " + std::to_string(metrics->at(curr_mesh_id).MXA_poly_min) + "</font>";
        message += "<br><font color=\"blue\">MXA POLY MAX : " + std::to_string(metrics->at(curr_mesh_id).MXA_poly_max) + "</font>";
        message += "<br>MXA POLY AVG : " + std::to_string(metrics->at(curr_mesh_id).MXA_poly_avg);
    }
    else
    if (ui->sr_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).SR_poly_min_id;
        id_max = metrics->at(curr_mesh_id).SR_poly_max_id;
        message += "<br><font color=\"green\">SR POLY MIN : " + std::to_string(metrics->at(curr_mesh_id).SR_poly_min) + "</font>";
        message += "<br><font color=\"blue\">SR POLY MAX : " + std::to_string(metrics->at(curr_mesh_id).SR_poly_max) + "</font>";
        message += "<br>SR AVG : " + std::to_string(metrics->at(curr_mesh_id).SR_poly_avg);
    }
    else
    if (ui->vem_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).VEM_poly_min_id;
        id_max = metrics->at(curr_mesh_id).VEM_poly_max_id;
        message += "<br><font color=\"green\">VEM POLY MIN : " + std::to_string(metrics->at(curr_mesh_id).VEM_poly_min) + "</font>";
        message += "<br><font color=\"blue\">VEM POLY MAX : " + std::to_string(metrics->at(curr_mesh_id).VEM_poly_max) + "</font>";
        message += "<br>VEM AVG : " + std::to_string(metrics->at(curr_mesh_id).VEM_poly_avg);
    }
    else
    if (ui->vema_rb->isChecked())
    {
        id_min = metrics->at(curr_mesh_id).VEMA_poly_min_id;
        id_max = metrics->at(curr_mesh_id).VEMA_poly_max_id;
        message += "<br><font color=\"green\">VEMA POLY MIN : " + std::to_string(metrics->at(curr_mesh_id).VEMA_poly_min) + "</font>";
        message += "<br><font color=\"blue\">VEMA POLY MAX : " + std::to_string(metrics->at(curr_mesh_id).VEMA_poly_max) + "</font>";

        double VEMA = sqrt(metrics->at(curr_mesh_id).VEMA_sum + metrics->at(curr_mesh_id).VEMA_poly_sum);
        message += "<br>VEMA : " + std::to_string(VEMA);
    }
    else
    {
        return;
    }

    //set_min_color(d->get_parametric_mesh(curr_mesh_id)->num_polys()-1);
    set_min_color(id_min);
    set_max_color(id_max);

    d->get_parametric_mesh(static_cast<uint>(curr_mesh_id))->updateGL();
    ui->mesh_metrics_canvas->updateGL();

    ui->info_text->setHtml(message.c_str());
}

void MeshMetricsGraphicWidget::set_slider_max(const uint max)
{
    ui->mesh_metrics_slider->setMaximum(static_cast<int>(max));
}

void MeshMetricsGraphicWidget::on_mesh_metrics_slider_valueChanged(int value)
{
    clean_canvas();

    show_mesh(value);

    ui->mesh_number_label->setText(std::to_string(value).c_str());
}


