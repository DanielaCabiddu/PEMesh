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

#ifndef MESH_METRICS_H
#define MESH_METRICS_H

#include <cinolib/meshes/polygonmesh.h>
#include <cinolib/min_max_inf.h>

#include <float.h>
#include <limits.h>
#include <vector>


using namespace cinolib;

typedef struct
{
    // IC - Inscribed Circle (radius) - Range: [0,inf) - high is good - scale dependent
    double IC_min    = 0.0;
    double IC_max    = 0.0;
    double IC_avg    = 0.0;
    double IC_poly_min   = 0.0;
    double IC_poly_max   = 0.0;
    double IC_poly_avg   = 0.0;
    double IC_global_avg   = 0.0;
    double IC_global_norm   = 0.0;
    uint   IC_min_id = UINT_MAX;
    uint   IC_max_id = UINT_MAX;
    uint   IC_poly_min_id = UINT_MAX;
    uint   IC_poly_max_id = UINT_MAX;

    // CC - Circumscribed Circle (radius) - Range: [0,inf) - low is good - scale dependent
    double CC_min    = 0.0;
    double CC_max    = 0.0;
    double CC_avg    = 0.0;
    double CC_poly_min   = 0.0;
    double CC_poly_max   = 0.0;
    double CC_poly_avg   = 0.0;
    double CC_global_avg   = 0.0;
    double CC_global_norm   = 0.0;
    uint   CC_min_id = UINT_MAX;
    uint   CC_max_id = UINT_MAX;
    uint   CC_poly_min_id = UINT_MAX;
    uint   CC_poly_max_id = UINT_MAX;

    // CR - Circle Ratio (IC/CC) - Range: [0,1] - high is good - scale INdependent
    double CR_min    = 0.0;
    double CR_max    = 0.0;
    double CR_avg    = 0.0;
    double CR_poly_min   = 0.0;
    double CR_poly_max   = 0.0;
    double CR_poly_avg   = 0.0;
    double CR_global_avg   = 0.0;
    double CR_global_norm   = 0.0;
    uint   CR_min_id = UINT_MAX;
    uint   CR_max_id = UINT_MAX;
    uint   CR_poly_min_id = UINT_MAX;
    uint   CR_poly_max_id = UINT_MAX;

    // AR - ARea - Range: [0,inf) - high is good - scale dependent
    double AR_min    = 0.0;
    double AR_max    = 0.0;
    double AR_avg    = 0.0;
    double AR_poly_min   = 0.0;
    double AR_poly_max   = 0.0;
    double AR_poly_avg   = 0.0;
    double AR_global_avg   = 0.0;
    double AR_global_norm   = 0.0;
    uint   AR_min_id = UINT_MAX;
    uint   AR_max_id = UINT_MAX;
    uint   AR_poly_min_id = UINT_MAX;
    uint   AR_poly_max_id = UINT_MAX;

    // KE - KErnel (area) - Range: [0,inf) - high is good - scale dependent
    double KE_min    = 0.0;
    double KE_max    = 0.0;
    double KE_avg    = 0.0;
    double KE_poly_min   = 0.0;
    double KE_poly_max   = 0.0;
    double KE_poly_avg   = 0.0;
    double KE_global_avg   = 0.0;
    double KE_global_norm   = 0.0;
    uint   KE_min_id = UINT_MAX;
    uint   KE_max_id = UINT_MAX;
    uint   KE_poly_min_id = UINT_MAX;
    uint   KE_poly_max_id = UINT_MAX;

    // KAR - Kernel Area Ratio (KE/AR) - Range: [0,1] - high is good - scale INdependent
    double KAR_min    = 0.0;
    double KAR_max    = 0.0;
    double KAR_avg    = 0.0;
    double KAR_poly_min   = 0.0;
    double KAR_poly_max   = 0.0;
    double KAR_poly_avg   = 0.0;
    double KAR_global_avg   = 0.0;
    double KAR_global_norm   = 0.0;
    uint   KAR_min_id = UINT_MAX;
    uint   KAR_max_id = UINT_MAX;
    uint   KAR_poly_min_id = UINT_MAX;
    uint   KAR_poly_max_id = UINT_MAX;

    // APR - Area Perimeter^2 Ratio - Range: (0,1] - high is good - scale INdependent
    double APR_min    = 0.0;
    double APR_max    = 0.0;
    double APR_avg    = 0.0;
    double APR_poly_min   = 0.0;
    double APR_poly_max   = 0.0;
    double APR_poly_avg   = 0.0;
    double APR_global_avg   = 0.0;
    double APR_global_norm   = 0.0;
    uint   APR_min_id = UINT_MAX;
    uint   APR_max_id = UINT_MAX;
    uint   APR_poly_min_id = UINT_MAX;
    uint   APR_poly_max_id = UINT_MAX;

    // MA - Minimum Angle - Range: [0,pi] - high is good - scale INdependent
    double MA_min    = 0.0;
    double MA_max    = 0.0;
    double MA_avg    = 0.0;
    double MA_poly_min   = 0.0;
    double MA_poly_max   = 0.0;
    double MA_poly_avg   = 0.0;
    double MA_global_avg   = 0.0;
    double MA_global_norm   = 0.0;
    uint   MA_min_id = UINT_MAX;
    uint   MA_max_id = UINT_MAX;
    uint   MA_poly_min_id = UINT_MAX;
    uint   MA_poly_max_id = UINT_MAX;

    // SE - Shortest Edge - Range: [0,inf) - high is good - scale dependent
    double SE_min    = 0.0;
    double SE_max    = 0.0;
    double SE_avg    = 0.0;
    double SE_poly_min   = 0.0;
    double SE_poly_max   = 0.0;
    double SE_poly_avg   = 0.0;
    double SE_global_avg   = 0.0;
    double SE_global_norm   = 0.0;
    uint   SE_min_id = UINT_MAX;
    uint   SE_max_id = UINT_MAX;
    uint   SE_poly_min_id = UINT_MAX;
    uint   SE_poly_max_id = UINT_MAX;

    // ER - Edge Ratio - Range: [0,1] - high is good - scale INdependent
    double ER_min    = 0.0;
    double ER_max    = 0.0;
    double ER_avg    = 0.0;
    double ER_poly_min   = 0.0;
    double ER_poly_max   = 0.0;
    double ER_poly_avg   = 0.0;
    double ER_global_avg   = 0.0;
    double ER_global_norm   = 0.0;
    uint   ER_min_id = UINT_MAX;
    uint   ER_max_id = UINT_MAX;
    uint   ER_poly_min_id = UINT_MAX;
    uint   ER_poly_max_id = UINT_MAX;

    // MPD - Minimum Point (to point) Distance - Range: [0,inf) - high is good - scale dependent
    double MPD_min    = 0.0;
    double MPD_max    = 0.0;
    double MPD_avg    = 0.0;
    double MPD_poly_min   = 0.0;
    double MPD_poly_max   = 0.0;
    double MPD_poly_avg   = 0.0;
    double MPD_global_avg   = 0.0;
    double MPD_global_norm   = 0.0;
    uint   MPD_min_id = UINT_MAX;
    uint   MPD_max_id = UINT_MAX;
    uint   MPD_poly_min_id = UINT_MAX;
    uint   MPD_poly_max_id = UINT_MAX;

    // MXA - MaX Angle - Range: (0,2pi) - low is good - scale INdependent
    double MXA_min         = 0.0;
    double MXA_max         = 0.0;
    double MXA_avg         = 0.0;
    double MXA_poly_min    = 0.0;
    double MXA_poly_max    = 0.0;
    double MXA_poly_avg    = 0.0;
    double MXA_global_avg   = 0.0;
    double MXA_global_norm   = 0.0;
    uint   MXA_min_id      = UINT_MAX;
    uint   MXA_max_id      = UINT_MAX;
    uint   MXA_poly_min_id = UINT_MAX;
    uint   MXA_poly_max_id = UINT_MAX;

    // MDR - Minimum Side Diameter Ratio - Range: (0,1] - high is good - scale INdependent
    double MDR_min         = 0.0;
    double MDR_max         = 0.0;
    double MDR_avg         = 0.0;
    double MDR_poly_min    = 0.0;
    double MDR_poly_max    = 0.0;
    double MDR_poly_avg    = 0.0;
    double MDR_global_avg   = 0.0;
    double MDR_global_norm   = 0.0;
    uint   MDR_min_id      = UINT_MAX;
    uint   MDR_max_id      = UINT_MAX;
    uint   MDR_poly_min_id = UINT_MAX;
    uint   MDR_poly_max_id = UINT_MAX;

    // NS - Number of Sides - Range: [3,inf) - low is good - scale INdependent
    uint   NS_min         = 0;
    uint   NS_max         = 0;
    double NS_avg         = 0.0;
    uint   NS_poly_min    = 0;
    uint   NS_poly_max    = 0;
    double NS_poly_avg    = 0.0;
    double NS_global_avg   = 0.0;
    double NS_global_norm   = 0.0;
    uint   NS_min_id      = UINT_MAX;
    uint   NS_max_id      = UINT_MAX;
    uint   NS_poly_min_id = UINT_MAX;
    uint   NS_poly_max_id = UINT_MAX;

    // SR - Shape Regularity - Range: (0,1) - high is good - scale INdependent
    double SR_min       = 0.0;
    double SR_max       = 0.0;
    double SR_avg       = 0.0;
    double SR_poly_min  = 0.0;
    double SR_poly_max  = 0.0;
    double SR_poly_avg  = 0.0;
    double SR_global_avg   = 0.0;
    double SR_global_norm   = 0.0;
    uint   SR_min_id    = UINT_MAX;
    uint   SR_max_id    = UINT_MAX;
    uint   SR_poly_min_id = UINT_MAX;
    uint   SR_poly_max_id = UINT_MAX;

    // VEM - Virtual Elements Max - Range: (1,inf) - low is good - scale INdependent
    double VEM_min       = 0.0;
    double VEM_max       = 0.0;
    double VEM_avg       = 0.0;
    double VEM_poly_min  = 0.0;
    double VEM_poly_max  = 0.0;
    double VEM_poly_avg  = 0.0;
    uint   VEM_min_id    = UINT_MAX;
    uint   VEM_max_id    = UINT_MAX;
    uint   VEM_poly_min_id = UINT_MAX;
    uint   VEM_poly_max_id = UINT_MAX;

    // VEMA - Virtual Elements Area - Range: (1,inf) - low is good - scale INdependent
    double VEMA_min       = 0.0;
    double VEMA_max       = 0.0;
    double VEMA_avg       = 0.0;
    double VEMA_sum       = 0.0;
    double VEMA_poly_min  = 0.0;
    double VEMA_poly_max  = 0.0;
    double VEMA_poly_avg  = 0.0;
    double VEMA_poly_sum  = 0.0;
    uint   VEMA_min_id    = UINT_MAX;
    uint   VEMA_max_id    = UINT_MAX;
    uint   VEMA_poly_min_id = UINT_MAX;
    uint   VEMA_poly_max_id = UINT_MAX;
}
MeshMetrics;

template<typename T>
void get_min_max_avg(std::vector<std::pair<T,uint>> & list,
                     T                              & min,
                     T                              & max,
                     double                         & avg,
                     uint                           & min_id,
                     uint                           & max_id);

void save_to_file(const char *filename, const MeshMetrics & metrics);

void compute_mesh_metrics(const Polygonmesh<> &m, MeshMetrics &metrics);

#endif
