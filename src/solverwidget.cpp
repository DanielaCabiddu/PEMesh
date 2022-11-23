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

#include "solverwidget.h"
#include "ui_solverwidget.h"

#include "solversettingsdialog.h"

#include <QDir>

SolverWidget::SolverWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SolverWidget)
{
    ui->setupUi(this);

    process = new QProcess();
    connect(process, SIGNAL(readyRead()), this, SLOT(update_log()));
}

SolverWidget::~SolverWidget()
{
    delete ui;
}

void SolverWidget::set_dataset(Dataset *d)
{
    dataset = d;
}

void SolverWidget::set_input_folder(const std::string folder)
{
    input_folder = folder;
}

void SolverWidget::update()
{
    if (dataset == nullptr)
        return;

    if (dataset->get_parametric_meshes().size() > 0 )
    {
        ui->t_slider->setMaximum(static_cast<int>(dataset->get_parametric_meshes().size())-1);
        show_parametric_mesh(ui->t_slider->value());
    }
}

void SolverWidget::clean_canvas()
{
    for (DrawablePolygonmesh<> * p : drawable_polys)
        ui->canvas->pop(p);

    drawable_polys.clear();
}

void SolverWidget::show_parametric_mesh(int index)
{
    clean_canvas();

    cinolib::DrawablePolygonmesh<> *p = dataset->get_parametric_mesh(static_cast<uint>(index));

    dataset->get_parametric_mesh(static_cast<uint>(index))->updateGL();
    ui->canvas->push_obj(p, update_scene);
    ui->canvas->updateGL();

    drawable_polys.push_back(p);

    update_scene = false;

    curr_mesh_id = static_cast<uint>(index);
}

void SolverWidget::on_t_slider_valueChanged(int value)
{
    show_parametric_mesh(value);
}

void SolverWidget::on_run_btn_clicked()
{
    SolverSettingsDialog *dialog = new SolverSettingsDialog();

    dialog->set_input_folder(input_folder);
    dialog->set_output_folder(input_folder);
    dialog->disable_input_folder_selection();

    if (dialog->exec() == 1)
    {
        //ui->log_label->append("Running solver ... ");

        QApplication::setOverrideCursor(Qt::WaitCursor);

        QString path_sep = QString(QDir::separator());

        const std::string in_folder = dialog->get_input_folder() + path_sep.toStdString();
        const std::string out_folder = dialog->get_output_folder();
        const std::string out_filename = dialog->get_output_filename();
        const std::string out_filepath = out_folder + path_sep.toStdString() + out_filename;

        const unsigned int solution_id = static_cast<uint>(ui->solver_cb->currentIndex());

        const std::string matlab_folder = dialog->get_matlab_folder();
        const std::string matlab_exe = matlab_folder + QString(QDir::separator()).toStdString() + dialog->get_matlab_exe_name();

        const std::string solver_script_path = dialog->get_solver_script_full_path();
        const std::string scripts_folder = solver_script_path.substr(0, solver_script_path.find_last_of(QDir::separator().unicode()));

        const std::string cd_cmd = std::string ("cd ") + std::string(scripts_folder);

        std::string solver_script_name = solver_script_path.substr(solver_script_path.find_last_of(QDir::separator().unicode())+1);
        solver_script_name = solver_script_name.substr(0, solver_script_name.find_last_of("."));
        const std::string matlab_script = solver_script_name + std::string(" ('")
                                            + in_folder + "','" + out_filepath + "'," + std::to_string(solution_id) +");exit;";

        std::cout << "RUNNING : " << matlab_script << std::endl;

        const std::string matlab_args = "-nodisplay -nosplash -nodesktop -r \"" + matlab_script + "\";";

        process->setWorkingDirectory(scripts_folder.c_str());

        process->moveToThread(QCoreApplication::instance()->thread());

        process->start(
            QString(matlab_exe.c_str()),
            QStringList() << QString( (matlab_args).c_str() ));

        std::string file_finished = out_filepath + "_DONE";

        while (!QFile::exists(file_finished.c_str()))
        {
            QCoreApplication::processEvents();
        }

        remove(file_finished.c_str());

        std::cout << process->exitStatus() << std::endl;
        std::cout << process->readAllStandardError().toStdString() << std::endl;
        std::cout << process->readAllStandardOutput().toStdString() << std::endl;

        std::cout << "DONE" << std::endl;

        QApplication::restoreOverrideCursor();

        emit (solver_completed (solution_id, out_folder, out_filename));
    }

    delete dialog;
}

void SolverWidget::update_log()
{
    QString appendText(process->readAll());
    ui->log_text->append(appendText);
}
