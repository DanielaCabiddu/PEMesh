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

#ifndef SOLVERSETTINGSDIALOG_H
#define SOLVERSETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SolverSettingsDialog;
}

class SolverSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SolverSettingsDialog(QWidget *parent = nullptr);
    ~SolverSettingsDialog();

    const std::string get_input_folder () const;
    const std::string get_output_folder () const;
    const std::string get_output_filename () const;
    const std::string get_matlab_folder () const;
    const std::string get_solver_script_full_path () const;

    const std::string get_matlab_exe_name () const;

    void set_input_folder (const std::string folder);
    void set_output_folder (const std::string folder);

    void disable_input_folder_selection ();

private slots:
    void on_output_directory_btn_clicked();

    void on_input_directory_btn_clicked();

    void on_solver_directory_btn_clicked();

    void on_matlab_directory_btn_clicked();

private:
    Ui::SolverSettingsDialog *ui;

    std::string matlab_folder;
    std::string solver_folder;

    std::string matlab_exe_name;

    bool check_matlab_folder_ok ();
    bool check_solver_folder_ok ();
};

#endif // SOLVERSETTINGSDIALOG_H
