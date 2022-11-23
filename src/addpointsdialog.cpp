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

#include "addpointsdialog.h"
#include "ui_addpointsdialog.h"

AddPointsDialog::AddPointsDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::AddPointsDialog) {
  ui->setupUi(this);
  setWindowTitle(tr("Select Sampling Settings"));

  update_img(getSampleIndex());
  connect(ui->sampling_list, SIGNAL(currentIndexChanged(int)), this,
          SLOT(update_img(int)));
}

AddPointsDialog::~AddPointsDialog() { delete ui; }

int AddPointsDialog::getSampleIndex() const {
  return ui->sampling_list->currentIndex();
}

std::string AddPointsDialog::getSampleName() const {
  return ui->sampling_list->currentText().toStdString();
}

int AddPointsDialog::getNumMeshes() const { return ui->num_meshes->value(); }

int AddPointsDialog::getNumPoints() const { return ui->num_points->value(); }

void AddPointsDialog::update_img(int index) {
  QPixmap pm;

  switch (index) {
  case 0:
    pm.load(":/class_img/img/points-equispaced.png"); // <- path to image file
    break;
  case 1:
    pm.load(":/class_img/img/points-linear.png"); // <- path to image file
    break;
  case 2:
    pm.load(":/class_img/img/points-nonlinear.png"); // <- path to image file
    break;
  case 3:
    pm.load(":/class_img/img/points-poisson.png"); // <- path to image file
    break;
  case 4:
    pm.load(":/class_img/img/points-random.png"); // <- path to image file
    break;
  default:
    break;
  }

  QPixmap pms = pm.scaledToHeight(ui->preview_img->height());
  ui->preview_img->setPixmap(pms);
}
