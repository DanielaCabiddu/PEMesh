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

#include "mesh_metrics.h"

#include <cinolib/polygon_kernel.h>
#include <cinolib/polygon_maximum_inscribed_circle.h>
#include <cinolib/smallest_enclosing_disk.h>


template<typename T>
void get_min_max_avg(std::vector<std::pair<T,uint>> & list,
                     T                              & min,
                     T                              & max,
                     double                         & avg,
                     uint                           & min_id,
                     uint                           & max_id)
{
    if (list.empty()) return;

    sort(list.begin(), list.end());
    min    = list.front().first;
    min_id = list.front().second;
    max    = list.back().first;
    max_id = list.back().second;
    avg    = 0.0;
    for(auto item : list) avg += item.first;
    avg/=static_cast<double>(list.size());
}

template<typename T>
void get_global_avg_norm (const std::vector<std::pair<T,uint>> & list1,
                          const std::vector<std::pair<T,uint>> & list2,
                                double &avg,
                                double &norm)
{
    avg  = 0.0;
    norm = 0.0;

    for(auto item : list1) avg += item.first;
    for(auto item : list2) avg += item.first;

    for(auto item : list1) norm += item.first * item.first;
    for(auto item : list2) norm += item.first * item.first;

    avg/=static_cast<double>(list1.size() + list2.size());

    norm/=static_cast<double>(list1.size() + list2.size());

    norm = sqrt (norm);

}

template<typename T>
void get_sum(std::vector<std::pair<T,uint>> & list, double & sum)
{
    if (list.empty()) return;
    sum = 0.0;
    for(auto item : list) sum += item.first;
}

void save_to_file(const char *filename, const MeshMetrics & metrics)
{
    FILE *f = fopen(filename, "w");
    if(f)
    {
        fprintf(f, "IC_min %f %d\n" , metrics.IC_min, metrics.IC_min_id);
        fprintf(f, "IC_max %f %d\n" , metrics.IC_max, metrics.IC_max_id);
        fprintf(f, "IC_avg %f\n"    , metrics.IC_avg);
        fprintf(f, "IC_poly_min %f %d\n" , metrics.IC_poly_min, metrics.IC_poly_min_id);
        fprintf(f, "IC_poly_max %f %d\n" , metrics.IC_poly_max, metrics.IC_poly_max_id);
        fprintf(f, "IC_poly_avg %f\n"    , metrics.IC_poly_avg);
        fprintf(f, "IC_global_avg %f\n"    , metrics.IC_global_avg);
        fprintf(f, "IC_global_norm %f\n"   , metrics.IC_global_norm);

        fprintf(f, "CC_min %f %d\n" , metrics.CC_min, metrics.CC_min_id);
        fprintf(f, "CC_max %f %d\n" , metrics.CC_max, metrics.CC_max_id);
        fprintf(f, "CC_avg %f\n"    , metrics.CC_avg);
        fprintf(f, "CC_poly_min %f %d\n" , metrics.CC_poly_min, metrics.CC_poly_min_id);
        fprintf(f, "CC_poly_max %f %d\n" , metrics.CC_poly_max, metrics.CC_poly_max_id);
        fprintf(f, "CC_poly_avg %f\n"    , metrics.CC_poly_avg);
        fprintf(f, "CC_global_avg %f\n"    , metrics.CC_global_avg);
        fprintf(f, "CC_global_norm %f\n"   , metrics.CC_global_norm);

        fprintf(f, "CR_min %f %d\n" , metrics.CR_min, metrics.CR_min_id);
        fprintf(f, "CR_max %f %d\n" , metrics.CR_max, metrics.CR_max_id);
        fprintf(f, "CR_avg %f\n"    , metrics.CR_avg);
        fprintf(f, "CR_poly_min %f %d\n" , metrics.CR_poly_min, metrics.CR_poly_min_id);
        fprintf(f, "CR_poly_max %f %d\n" , metrics.CR_poly_max, metrics.CR_poly_max_id);
        fprintf(f, "CR_poly_avg %f\n"    , metrics.CR_poly_avg);
        fprintf(f, "CR_global_avg %f\n"    , metrics.CR_global_avg);
        fprintf(f, "CR_global_norm %f\n"   , metrics.CR_global_norm);

        fprintf(f, "AR_min %f %d\n" , metrics.AR_min, metrics.AR_min_id);
        fprintf(f, "AR_max %f %d\n" , metrics.AR_max, metrics.AR_max_id);
        fprintf(f, "AR_avg %f\n"    , metrics.AR_avg);
        fprintf(f, "AR_poly_min %f %d\n" , metrics.AR_poly_min, metrics.AR_poly_min_id);
        fprintf(f, "AR_poly_max %f %d\n" , metrics.AR_poly_max, metrics.AR_poly_max_id);
        fprintf(f, "AR_poly_avg %f\n"    , metrics.AR_poly_avg);
        fprintf(f, "AR_global_avg %f\n"    , metrics.AR_global_avg);
        fprintf(f, "AR_global_norm %f\n"   , metrics.AR_global_norm);

        fprintf(f, "KE_min %f %d\n" , metrics.KE_min, metrics.KE_min_id);
        fprintf(f, "KE_max %f %d\n" , metrics.KE_max, metrics.KE_max_id);
        fprintf(f, "KE_avg %f\n"    , metrics.KE_avg);
        fprintf(f, "KE_poly_min %f %d\n" , metrics.KE_poly_min, metrics.KE_poly_min_id);
        fprintf(f, "KE_poly_max %f %d\n" , metrics.KE_poly_max, metrics.KE_poly_max_id);
        fprintf(f, "KE_poly_avg %f\n"    , metrics.KE_poly_avg);
        fprintf(f, "KE_global_avg %f\n"    , metrics.KE_global_avg);
        fprintf(f, "KE_global_norm %f\n"   , metrics.KE_global_norm);

        fprintf(f, "KAR_min %f %d\n", metrics.KAR_min, metrics.KAR_min_id);
        fprintf(f, "KAR_max %f %d\n", metrics.KAR_max, metrics.KAR_max_id);
        fprintf(f, "KAR_avg %f\n"   , metrics.KAR_avg);
        fprintf(f, "KAR_poly_min %f %d\n", metrics.KAR_poly_min, metrics.KAR_poly_min_id);
        fprintf(f, "KAR_poly_max %f %d\n", metrics.KAR_poly_max, metrics.KAR_poly_max_id);
        fprintf(f, "KAR_poly_avg %f\n"   , metrics.KAR_poly_avg);
        fprintf(f, "KAR_global_avg %f\n"    , metrics.KAR_global_avg);
        fprintf(f, "KAR_global_norm %f\n"   , metrics.KAR_global_norm);

        fprintf(f, "APR_min %f %d\n", metrics.APR_min, metrics.APR_min_id);
        fprintf(f, "APR_max %f %d\n", metrics.APR_max, metrics.APR_max_id);
        fprintf(f, "APR_avg %f\n"   , metrics.APR_avg);
        fprintf(f, "APR_poly_min %f %d\n", metrics.APR_poly_min, metrics.APR_poly_min_id);
        fprintf(f, "APR_poly_max %f %d\n", metrics.APR_poly_max, metrics.APR_poly_max_id);
        fprintf(f, "APR_poly_avg %f\n"   , metrics.APR_poly_avg);
        fprintf(f, "APR_global_avg %f\n"    , metrics.APR_global_avg);
        fprintf(f, "APR_global_norm %f\n"   , metrics.APR_global_norm);

        fprintf(f, "MA_min %f %d\n" , metrics.MA_min, metrics.MA_min_id);
        fprintf(f, "MA_max %f %d\n" , metrics.MA_max, metrics.MA_max_id);
        fprintf(f, "MA_avg %f\n"    , metrics.MA_avg);
        fprintf(f, "MA_poly_min %f %d\n" , metrics.MA_poly_min, metrics.MA_poly_min_id);
        fprintf(f, "MA_poly_max %f %d\n" , metrics.MA_poly_max, metrics.MA_poly_max_id);
        fprintf(f, "MA_poly_avg %f\n"    , metrics.MA_poly_avg);
        fprintf(f, "MA_global_avg %f\n"    , metrics.MA_global_avg);
        fprintf(f, "MA_global_norm %f\n"   , metrics.MA_global_norm);

        fprintf(f, "SE_min %f %d\n" , metrics.SE_min, metrics.SE_min_id);
        fprintf(f, "SE_max %f %d\n" , metrics.SE_max, metrics.SE_max_id);
        fprintf(f, "SE_avg %f\n"    , metrics.SE_avg);
        fprintf(f, "SE_poly_min %f %d\n" , metrics.SE_poly_min, metrics.SE_poly_min_id);
        fprintf(f, "SE_poly_max %f %d\n" , metrics.SE_poly_max, metrics.SE_poly_max_id);
        fprintf(f, "SE_poly_avg %f\n"    , metrics.SE_poly_avg);
        fprintf(f, "SE_global_avg %f\n"    , metrics.SE_global_avg);
        fprintf(f, "SE_global_norm %f\n"   , metrics.SE_global_norm);

        fprintf(f, "ER_min %f %d\n" , metrics.ER_min, metrics.ER_min_id);
        fprintf(f, "ER_max %f %d\n" , metrics.ER_max, metrics.ER_max_id);
        fprintf(f, "ER_avg %f\n"    , metrics.ER_avg);
        fprintf(f, "ER_poly_min %f %d\n" , metrics.ER_poly_min, metrics.ER_poly_min_id);
        fprintf(f, "ER_poly_max %f %d\n" , metrics.ER_poly_max, metrics.ER_poly_max_id);
        fprintf(f, "ER_poly_avg %f\n"    , metrics.ER_poly_avg);
        fprintf(f, "ER_global_avg %f\n"    , metrics.ER_global_avg);
        fprintf(f, "ER_global_norm %f\n"   , metrics.ER_global_norm);

        fprintf(f, "MPD_min %f %d\n", metrics.MPD_min, metrics.MPD_min_id);
        fprintf(f, "MPD_max %f %d\n", metrics.MPD_max, metrics.MPD_max_id);
        fprintf(f, "MPD_avg %f\n"   , metrics.MPD_avg);
        fprintf(f, "MPD_poly_min %f %d\n", metrics.MPD_poly_min, metrics.MPD_poly_min_id);
        fprintf(f, "MPD_poly_max %f %d\n", metrics.MPD_poly_max, metrics.MPD_poly_max_id);
        fprintf(f, "MPD_poly_avg %f\n"   , metrics.MPD_poly_avg);
        fprintf(f, "MPD_global_avg %f\n"    , metrics.MPD_global_avg);
        fprintf(f, "MPD_global_norm %f\n"   , metrics.MPD_global_norm);

        fprintf(f, "MXA_min %f %d\n", metrics.MXA_min, metrics.MXA_min_id);
        fprintf(f, "MXA_max %f %d\n", metrics.MXA_max, metrics.MXA_max_id);
        fprintf(f, "MXA_avg %f\n"   , metrics.MXA_avg);
        fprintf(f, "MXA_poly_min %f %d\n", metrics.MXA_poly_min, metrics.MXA_poly_min_id);
        fprintf(f, "MXA_poly_max %f %d\n", metrics.MXA_poly_max, metrics.MXA_poly_max_id);
        fprintf(f, "MXA_poly_avg %f\n"   , metrics.MXA_poly_avg);
        fprintf(f, "MXA_global_avg %f\n"    , metrics.MXA_global_avg);
        fprintf(f, "MXA_global_norm %f\n"   , metrics.MXA_global_norm);

        fprintf(f, "MDR_min %f %d\n", metrics.MDR_min, metrics.MDR_min_id);
        fprintf(f, "MDR_max %f %d\n", metrics.MDR_max, metrics.MDR_max_id);
        fprintf(f, "MDR_avg %f\n"   , metrics.MDR_avg);
        fprintf(f, "MDR_poly_min %f %d\n", metrics.MDR_poly_min, metrics.MDR_poly_min_id);
        fprintf(f, "MDR_poly_max %f %d\n", metrics.MDR_poly_max, metrics.MDR_poly_max_id);
        fprintf(f, "MDR_poly_avg %f\n"   , metrics.MDR_poly_avg);
        fprintf(f, "MDR_global_avg %f\n"    , metrics.MDR_global_avg);
        fprintf(f, "MDR_global_norm %f\n"   , metrics.MDR_global_norm);

        fprintf(f, "NS_min %d %d\n", metrics.NS_min, metrics.NS_min_id);
        fprintf(f, "NS_max %d %d\n", metrics.NS_max, metrics.NS_max_id);
        fprintf(f, "NS_avg %f\n"   , metrics.NS_avg);
        fprintf(f, "NS_poly_min %d %d\n", metrics.NS_poly_min, metrics.NS_poly_min_id);
        fprintf(f, "NS_poly_max %d %d\n", metrics.NS_poly_max, metrics.NS_poly_max_id);
        fprintf(f, "NS_poly_avg %f\n"   , metrics.NS_poly_avg);
        fprintf(f, "NS_global_avg %f\n"    , metrics.NS_global_avg);
        fprintf(f, "NS_global_norm %f\n"   , metrics.NS_global_norm);

        fprintf(f, "SR_min %f %d\n", metrics.SR_min, metrics.SR_min_id);
        fprintf(f, "SR_max %f %d\n", metrics.SR_max, metrics.SR_max_id);
        fprintf(f, "SR_avg %f\n"   , metrics.SR_avg);
        fprintf(f, "SR_poly_min %f %d\n", metrics.SR_poly_min, metrics.SR_poly_min_id);
        fprintf(f, "SR_poly_max %f %d\n", metrics.SR_poly_max, metrics.SR_poly_max_id);
        fprintf(f, "SR_poly_avg %f\n"   , metrics.SR_poly_avg);
        fprintf(f, "SR_global_avg %f\n"    , metrics.SR_global_avg);
        fprintf(f, "SR_global_norm %f\n"   , metrics.SR_global_norm);

        fprintf(f, "VEM_min %f %d\n", metrics.VEM_min, metrics.VEM_min_id);
        fprintf(f, "VEM_max %f %d\n", metrics.VEM_max, metrics.VEM_max_id);
        fprintf(f, "VEM_avg %f\n"   , metrics.VEM_avg);
        fprintf(f, "VEM_poly_min %f %d\n", metrics.VEM_poly_min, metrics.VEM_poly_min_id);
        fprintf(f, "VEM_poly_max %f %d\n", metrics.VEM_poly_max, metrics.VEM_poly_max_id);
        fprintf(f, "VEM_poly_avg %f\n"   , metrics.VEM_poly_avg);
        fprintf(f, "VEMA_min %f %d\n", metrics.VEMA_min, metrics.VEMA_min_id);
        fprintf(f, "VEMA_max %f %d\n", metrics.VEMA_max, metrics.VEMA_max_id);
        fprintf(f, "VEMA_avg %f\n"   , metrics.VEMA_avg);
        fprintf(f, "VEMA_sum %f\n"   , metrics.VEMA_sum);
        fprintf(f, "VEMA_poly_min %f %d\n", metrics.VEMA_poly_min, metrics.VEMA_poly_min_id);
        fprintf(f, "VEMA_poly_max %f %d\n", metrics.VEMA_poly_max, metrics.VEMA_poly_max_id);
        fprintf(f, "VEMA_poly_avg %f\n"   , metrics.VEMA_poly_avg);
        fclose(f);
    }
}

void compute_mesh_metrics(const Polygonmesh<> &m, MeshMetrics &metrics)
{
    // convenient compact representations for each item
    std::vector<std::pair<double,uint>> IC;
    std::vector<std::pair<double,uint>> CC;
    std::vector<std::pair<double,uint>> CR;
    std::vector<std::pair<double,uint>> AR;
    std::vector<std::pair<double,uint>> KE;
    std::vector<std::pair<double,uint>> KAR;
    std::vector<std::pair<double,uint>> APR;
    std::vector<std::pair<double,uint>> MA;
    std::vector<std::pair<double,uint>> SE;
    std::vector<std::pair<double,uint>> ER;
    std::vector<std::pair<double,uint>> MPD;
    std::vector<std::pair<double,uint>> MXA;
    std::vector<std::pair<double,uint>> MDR;
    std::vector<std::pair<uint,uint>> NS;
    std::vector<std::pair<double,uint>> SR;
    std::vector<std::pair<double,uint>> VEM;
    std::vector<std::pair<double,uint>> VEMA;

    std::vector<std::pair<double,uint>> IC_poly;
    std::vector<std::pair<double,uint>> CC_poly;
    std::vector<std::pair<double,uint>> CR_poly;
    std::vector<std::pair<double,uint>> AR_poly;
    std::vector<std::pair<double,uint>> KE_poly;
    std::vector<std::pair<double,uint>> KAR_poly;
    std::vector<std::pair<double,uint>> APR_poly;
    std::vector<std::pair<double,uint>> MA_poly;
    std::vector<std::pair<double,uint>> SE_poly;
    std::vector<std::pair<double,uint>> ER_poly;
    std::vector<std::pair<double,uint>> MPD_poly;
    std::vector<std::pair<double,uint>> MXA_poly;
    std::vector<std::pair<double,uint>> MDR_poly;
    std::vector<std::pair<uint,uint>> NS_poly;
    std::vector<std::pair<double,uint>> SR_poly;
    std::vector<std::pair<double,uint>> VEM_poly;
    std::vector<std::pair<double,uint>> VEMA_poly;

    for(uint pid=0; pid<m.num_polys(); ++pid)
    {
        //std::cout << "[pid " << pid << "] " << std::endl;

        std::vector<vec3d> points = m.poly_verts(pid);
        bool is_triangle = (points.size() == 3);

        vec3d  dummy;
        double ic, cc;
        polygon_maximum_inscribed_circle(points, dummy, ic);
        //std::cout << "[polygon_maximum_inscribed_circle] " << ic << std::endl;

        smallest_enclosing_disk(points, dummy, cc);
        //std::cout << "[smallest_enclosing_disk] " << cc << std::endl;

        if (is_triangle)
        {
            IC.push_back(std::make_pair(ic,pid));
            CC.push_back(std::make_pair(cc,pid));
            CR.push_back(std::make_pair(ic/cc,pid));
        }
        else
        {
            IC_poly.push_back(std::make_pair(ic,pid));
            CC_poly.push_back(std::make_pair(cc,pid));
            CR_poly.push_back(std::make_pair(ic/cc,pid));
        }

        std::vector<double> a;
        for(uint vid : m.adj_p2v(pid)) a.push_back(m.poly_angle_at_vert(pid, vid, DEG));
        double min_a = *std::min_element(a.begin(), a.end());
        double max_a = *std::max_element(a.begin(), a.end());

        //std::cout << "[min/max angle] " << min_a << " - " << max_a << std::endl;

        if (is_triangle)
        {
            MA.push_back(std::make_pair(min_a,pid));
            MXA.push_back(std::make_pair(max_a,pid));
        }
        else
        {
            MA_poly.push_back(std::make_pair(min_a,pid));
            MXA_poly.push_back(std::make_pair(max_a,pid));

            for (double d : a) std::cout << d << std::endl;
            std::cout << "===============" << std::endl;
        }


        std::vector<double> e;
        for(uint eid : m.adj_p2e(pid)) {e.push_back(m.edge_length(eid)); }
        double min_e = *std::min_element(e.begin(), e.end());
        double max_e = *std::max_element(e.begin(), e.end());

//        std::cout << "[min_max edge] " << min_e << " - " << max_e << std::endl;

        if (is_triangle)
        {
            SE.push_back(std::make_pair(min_e,pid));
            ER.push_back(std::make_pair(min_e/max_e,pid));
            MDR.push_back(std::make_pair(min_e/ic,pid));
        }
        else
        {
            SE_poly.push_back(std::make_pair(min_e,pid));
            ER_poly.push_back(std::make_pair(min_e/max_e,pid));
            MDR_poly.push_back(std::make_pair(min_e/ic,pid));
        }

        std::vector<vec3d> dummy2;
        double perim  = std::accumulate(e.begin(), e.end(), 0.0);
        double area   = m.poly_area(pid);
        double kernel = polygon_kernel(points, dummy2);

        double radius = 0.0;
        vec3d center;

        if (dummy2.size() > 0)
            polygon_maximum_inscribed_circle(dummy2, center, radius);

        double shape_regularity = (radius > 0.0) ? cc/radius : DBL_MAX;

        //std::cout << "[perim area kernel] " << perim << " - " << area << " - " << kernel << std::endl;

        if (is_triangle)
        {
            AR.push_back(std::make_pair(area,pid));
            APR.push_back(std::make_pair(area/(perim*perim),pid));
            KE.push_back(std::make_pair(kernel,pid));
            if(area>0) KAR.push_back(std::make_pair(kernel/area,pid));

            SR.push_back(std::make_pair(shape_regularity, pid));
        }
        else
        {
            AR_poly.push_back(std::make_pair(area,pid));
            APR_poly.push_back(std::make_pair(area/(perim*perim),pid));
            KE_poly.push_back(std::make_pair(kernel,pid));
            if(area>0) KAR_poly.push_back(std::make_pair(kernel/area,pid));

            SR_poly.push_back(std::make_pair(shape_regularity, pid));
        }

        double d = inf_double, he = -inf_double;
        for(uint i=0;   i<points.size()-1; ++i)
            for(uint j=i+1; j<points.size();   ++j)
            {
                d = std::min(d, points.at(i).dist(points.at(j)));
                he = std::max(he, points.at(i).dist(points.at(j)));
            }
        double rho = he / std::min(sqrt(area), min_e);
//        double angle = std::min(min_a, 1/max_a);
        double rho_a = rho * rho * area;

    //    std::cout << "[ro] " << ro << std::endl;

        if (is_triangle)
        {
            MPD.push_back(std::make_pair(d,pid));
            NS.push_back(std::make_pair(m.adj_p2e(pid).size(),pid));
            VEM.push_back(std::make_pair(rho, pid));
            VEMA.push_back(std::make_pair(rho_a, pid));
        }
        else
        {
            MPD_poly.push_back(std::make_pair(d,pid));
            NS_poly.push_back(std::make_pair(m.adj_p2e(pid).size(),pid));
            VEM_poly.push_back(std::make_pair(rho, pid));
            VEMA_poly.push_back(std::make_pair(rho_a, pid));
        }
    }

    //std::cout << "[getting min max avg] " << std::endl;

    get_min_max_avg(IC,  metrics.IC_min,  metrics.IC_max,  metrics.IC_avg,  metrics.IC_min_id,  metrics.IC_max_id );
    get_min_max_avg(CC,  metrics.CC_min,  metrics.CC_max,  metrics.CC_avg,  metrics.CC_min_id,  metrics.CC_max_id );
    get_min_max_avg(CR,  metrics.CR_min,  metrics.CR_max,  metrics.CR_avg,  metrics.CR_min_id,  metrics.CR_max_id );
    get_min_max_avg(AR,  metrics.AR_min,  metrics.AR_max,  metrics.AR_avg,  metrics.AR_min_id,  metrics.AR_max_id );
    get_min_max_avg(KE,  metrics.KE_min,  metrics.KE_max,  metrics.KE_avg,  metrics.KE_min_id,  metrics.KE_max_id );
    get_min_max_avg(KAR, metrics.KAR_min, metrics.KAR_max, metrics.KAR_avg, metrics.KAR_min_id, metrics.KAR_max_id);
    get_min_max_avg(APR, metrics.APR_min, metrics.APR_max, metrics.APR_avg, metrics.APR_min_id, metrics.APR_max_id);
    get_min_max_avg(MA,  metrics.MA_min,  metrics.MA_max,  metrics.MA_avg,  metrics.MA_min_id,  metrics.MA_max_id );
    get_min_max_avg(SE,  metrics.SE_min,  metrics.SE_max,  metrics.SE_avg,  metrics.SE_min_id,  metrics.SE_max_id );
    get_min_max_avg(ER,  metrics.ER_min,  metrics.ER_max,  metrics.ER_avg,  metrics.ER_min_id,  metrics.ER_max_id );
    get_min_max_avg(MPD, metrics.MPD_min, metrics.MPD_max, metrics.MPD_avg, metrics.MPD_min_id, metrics.MPD_max_id);
    get_min_max_avg(MXA, metrics.MXA_min, metrics.MXA_max, metrics.MXA_avg, metrics.MXA_min_id, metrics.MXA_max_id);
    get_min_max_avg(MDR, metrics.MDR_min, metrics.MDR_max, metrics.MDR_avg, metrics.MDR_min_id, metrics.MDR_max_id);
    get_min_max_avg(NS, metrics.NS_min, metrics.NS_max, metrics.NS_avg, metrics.NS_min_id, metrics.NS_max_id);
    get_min_max_avg(SR, metrics.SR_min, metrics.SR_max, metrics.SR_avg, metrics.SR_min_id, metrics.SR_max_id);
    get_min_max_avg(VEM, metrics.VEM_min, metrics.VEM_max, metrics.VEM_avg, metrics.VEM_min_id, metrics.VEM_max_id);
    get_min_max_avg(VEMA, metrics.VEMA_min, metrics.VEMA_max, metrics.VEMA_avg, metrics.VEMA_min_id, metrics.VEMA_max_id);
    get_sum(VEMA, metrics.VEMA_sum);

    get_min_max_avg(IC_poly,  metrics.IC_poly_min,  metrics.IC_poly_max,  metrics.IC_poly_avg,  metrics.IC_poly_min_id,  metrics.IC_poly_max_id );
    get_min_max_avg(CC_poly,  metrics.CC_poly_min,  metrics.CC_poly_max,  metrics.CC_poly_avg,  metrics.CC_poly_min_id,  metrics.CC_poly_max_id );
    get_min_max_avg(CR_poly,  metrics.CR_poly_min,  metrics.CR_poly_max,  metrics.CR_poly_avg,  metrics.CR_poly_min_id,  metrics.CR_poly_max_id );
    get_min_max_avg(AR_poly,  metrics.AR_poly_min,  metrics.AR_poly_max,  metrics.AR_poly_avg,  metrics.AR_poly_min_id,  metrics.AR_poly_max_id );
    get_min_max_avg(KE_poly,  metrics.KE_poly_min,  metrics.KE_poly_max,  metrics.KE_poly_avg,  metrics.KE_poly_min_id,  metrics.KE_poly_max_id );
    get_min_max_avg(KAR_poly, metrics.KAR_poly_min, metrics.KAR_poly_max, metrics.KAR_poly_avg, metrics.KAR_poly_min_id, metrics.KAR_poly_max_id);
    get_min_max_avg(APR_poly, metrics.APR_poly_min, metrics.APR_poly_max, metrics.APR_poly_avg, metrics.APR_poly_min_id, metrics.APR_poly_max_id);
    get_min_max_avg(MA_poly,  metrics.MA_poly_min,  metrics.MA_poly_max,  metrics.MA_poly_avg,  metrics.MA_poly_min_id,  metrics.MA_poly_max_id );
    get_min_max_avg(SE_poly,  metrics.SE_poly_min,  metrics.SE_poly_max,  metrics.SE_poly_avg,  metrics.SE_poly_min_id,  metrics.SE_poly_max_id );
    get_min_max_avg(ER_poly,  metrics.ER_poly_min,  metrics.ER_poly_max,  metrics.ER_poly_avg,  metrics.ER_poly_min_id,  metrics.ER_poly_max_id );
    get_min_max_avg(MPD_poly, metrics.MPD_poly_min, metrics.MPD_poly_max, metrics.MPD_poly_avg, metrics.MPD_poly_min_id, metrics.MPD_poly_max_id);
    get_min_max_avg(MXA_poly, metrics.MXA_poly_min, metrics.MXA_poly_max, metrics.MXA_poly_avg, metrics.MXA_poly_min_id, metrics.MXA_poly_max_id);
    get_min_max_avg(MDR_poly, metrics.MDR_poly_min, metrics.MDR_poly_max, metrics.MDR_poly_avg, metrics.MDR_poly_min_id, metrics.MDR_poly_max_id);
    get_min_max_avg(NS_poly, metrics.NS_poly_min, metrics.NS_poly_max, metrics.NS_poly_avg, metrics.NS_poly_min_id, metrics.NS_poly_max_id);
    get_min_max_avg(SR_poly, metrics.SR_poly_min, metrics.SR_poly_max, metrics.SR_poly_avg, metrics.SR_poly_min_id, metrics.SR_poly_max_id);
    get_min_max_avg(VEM_poly, metrics.VEM_poly_min, metrics.VEM_poly_max, metrics.VEM_poly_avg, metrics.VEM_poly_min_id, metrics.VEM_poly_max_id);
    get_min_max_avg(VEMA_poly, metrics.VEMA_poly_min, metrics.VEMA_poly_max, metrics.VEMA_poly_avg, metrics.VEMA_poly_min_id, metrics.VEMA_poly_max_id);
    get_sum(VEMA_poly, metrics.VEMA_poly_sum);


    get_global_avg_norm(IC, IC_poly, metrics.IC_global_avg, metrics.IC_global_norm);
    get_global_avg_norm(CC, CC_poly, metrics.CC_global_avg, metrics.CC_global_norm);
    get_global_avg_norm(CR, CR_poly, metrics.CR_global_avg, metrics.CR_global_norm);
    get_global_avg_norm(AR, AR_poly, metrics.AR_global_avg, metrics.AR_global_norm);
    get_global_avg_norm(KE, KE_poly, metrics.KE_global_avg, metrics.KE_global_norm);
    get_global_avg_norm(KAR, KAR_poly, metrics.KAR_global_avg, metrics.KAR_global_norm);
    get_global_avg_norm(APR, APR_poly, metrics.APR_global_avg, metrics.APR_global_norm);
    get_global_avg_norm(MA, MA_poly, metrics.MA_global_avg, metrics.MA_global_norm);
    get_global_avg_norm(SE, SE_poly, metrics.SE_global_avg, metrics.SE_global_norm);
    get_global_avg_norm(ER, ER_poly, metrics.ER_global_avg, metrics.ER_global_norm);
    get_global_avg_norm(MPD, MPD_poly, metrics.MPD_global_avg, metrics.MPD_global_norm);
    get_global_avg_norm(MXA, MXA_poly, metrics.MXA_global_avg, metrics.MXA_global_norm);
    get_global_avg_norm(MDR, MDR_poly, metrics.MDR_global_avg, metrics.MDR_global_norm);
    get_global_avg_norm(NS, NS_poly, metrics.NS_global_avg, metrics.NS_global_norm);
    get_global_avg_norm(SR, SR_poly, metrics.SR_global_avg, metrics.SR_global_norm);
}
