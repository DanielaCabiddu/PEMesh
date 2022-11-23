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

#include "vem_elements.h"
#include <cinolib/geometry/n_sided_poygon.h>
#include <cinolib/sampling.h>
#include <numeric>

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

IsotropyTester::IsotropyTester() : AbstractVEMelement()
{
    // define a regular quad
    std::vector<vec3d>             verts = { vec3d(0,0,0), vec3d(1,0,0), vec3d(1,1,0), vec3d(0,1,0) };
    std::vector<std::vector<uint>> face  = {{ 0, 1, 2, 3 }};

    base_elem = Polygonmesh<>(verts,face);
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Polygonmesh<> IsotropyTester::deform(float t) const
{
    if (t==1.0) t -= 1e-5; // avoid perfectly collapsed element

    Polygonmesh<> m = base_elem;

    vec3d up  (0,0.5,0);
    vec3d down(0,-0.5,0);

    m.vert(0) = vec3d(0,0,0) + up   * t;
    m.vert(1) = vec3d(1,0,0) + up   * t;
    m.vert(2) = vec3d(1,1,0) + down * t;
    m.vert(3) = vec3d(0,1,0) + down * t;

    return m;
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

ConvexityTester::ConvexityTester() : AbstractVEMelement()
{
    // define a regular quad
    std::vector<vec3d>             verts = { vec3d(0,0,0), vec3d(1,0,0), vec3d(1,1,0), vec3d(0,1,0) };
    std::vector<std::vector<uint>> face  = {{ 0, 1, 2, 3 }};

    base_elem = Polygonmesh<>(verts,face);
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Polygonmesh<> ConvexityTester::deform(float t) const
{
    if (t==1.0) t-= 1e-5; // avoid perfectly collapsed element

    Polygonmesh<> m = base_elem;
    m.vert(0) = vec3d(1,1,0) * t;
    return m;
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

NumSidesTester::NumSidesTester(const uint max_sides) : AbstractVEMelement()
  , max_sides(max_sides)
{
    base_elem = n_sided_polygon(3);
    base_elem.rotate(vec3d(0,0,1), M_PI*0.5);
    base_elem.center_bbox();
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Polygonmesh<> NumSidesTester::deform(float t) const
{
    uint n_sides = 3 + std::ceil(t*(max_sides-3));
    Polygonmesh<> m = n_sided_polygon(n_sides);
    m.rotate(vec3d(0,0,1), M_PI*0.5);
    return m;
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Polygonmesh<> NumSidesTester::n_sided_polygon(const uint n_sides) const
{
    std::vector<vec3d> verts = cinolib::n_sided_polygon(n_sides, cinolib::CIRCLE);
    std::vector<std::vector<uint>> faces(1);
    faces.front().resize(n_sides);
    std::iota(faces.front().begin(), faces.front().end(), 0);
    return Polygonmesh<>(verts, faces);
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

MazeTester::MazeTester() : AbstractVEMelement()
{
    std::vector<vec3d> verts =
    {
        vec3d(0, 1, 0),
        vec3d(0, 0.75, 0),
        vec3d(0, 0.5, 0),
        vec3d(0, 0.25, 0),
        vec3d(0, 0, 0),
        vec3d(0.25, 0, 0),
        vec3d(0.5, 0, 0),
        vec3d(0.75, 0, 0),
        vec3d(1, 0, 0),
        vec3d(1, 0.25, 0),
        vec3d(1, 0.5, 0),
        vec3d(1, 0.75, 0),
        vec3d(0.75, 0.75, 0),
        vec3d(0.5, 0.75, 0),
        vec3d(0.5, 0.5, 0),
        vec3d(0.75, 0.5, 0),
        vec3d(0.75, 0.25, 0),
        vec3d(0.5, 0.25, 0),
        vec3d(0.25, 0.25, 0),
        vec3d(0.25, 0.5, 0),
        vec3d(0.25, 0.75, 0),
        vec3d(0.25, 1, 0)
    };
    std::vector<std::vector<uint>> face  = {{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21 }};

    base_elem = Polygonmesh<>(verts,face);
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Polygonmesh<> MazeTester::deform(float t) const
{
    Polygonmesh<> m = base_elem;
    m.vert(14) = vec3d(0.5,0.5,0)   * (1.0-t) + vec3d(0.5,0.745,0)   * t;
    m.vert(15) = vec3d(0.75,0.5,0)  * (1.0-t) + vec3d(0.995,0.745,0) * t;
    m.vert(16) = vec3d(0.75,0.25,0) * (1.0-t) + vec3d(0.995,0.005,0) * t;
    m.vert(17) = vec3d(0.5,0.25,0)  * (1.0-t) + vec3d(0.5,0.005,0)   * t;
    m.vert(18) = vec3d(0.25,0.25,0) * (1.0-t) + vec3d(0.005,0.005,0) * t;
    m.vert(19) = vec3d(0.25,0.5,0)  * (1.0-t) + vec3d(0.005,0.5,0)   * t;
    m.vert(20) = vec3d(0.25,0.75,0) * (1.0-t) + vec3d(0.005,0.75,0)  * t;
    m.vert(21) = vec3d(0.25,1,0)    * (1.0-t) + vec3d(0.005,1,0)     * t;
    return m;
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

StarTester::StarTester(const uint max_spikes) : AbstractVEMelement()
  , max_spikes(max_spikes)
{
    uint n_sides = 6;
    base_elem = n_sided_polygon(n_sides);
    vec3d c = base_elem.centroid();
    for(uint i=0; i<n_sides; ++i)
    {
        if (i%2==0) base_elem.vert(i) -= (c-base_elem.vert(i)) * 0.8;
    }
    base_elem.rotate(vec3d(0,0,1), M_PI*0.5);
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Polygonmesh<> StarTester::deform(float t) const
{
    uint n_spikes = 3 + std::ceil(t*(max_spikes-3));
    uint n_sides  = 2*n_spikes;
    Polygonmesh<> m = n_sided_polygon(n_sides);
    vec3d c = m.centroid();
    for(uint i=0; i<n_sides; ++i)
    {
        if (i%2==0) m.vert(i) -= (c-m.vert(i)) * 0.8;
    }
    m.update_p_tessellations();
    m.rotate(vec3d(0,0,1), M_PI*0.5);
    return m;
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Polygonmesh<> StarTester::n_sided_polygon(const uint n_sides) const
{
    std::vector<vec3d> verts = cinolib::n_sided_polygon(n_sides, cinolib::CIRCLE);
    std::vector<std::vector<uint>> faces(1);
    faces.front().resize(n_sides);
    std::iota(faces.front().begin(), faces.front().end(), 0);
    return Polygonmesh<>(verts, faces);
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

UTester::UTester() : AbstractVEMelement()
{
    std::vector<vec3d> verts =
    {
        vec3d(0,0,0),
        vec3d(0.25,0,0),
        vec3d(0.5,0,0),
        vec3d(0.75,0,0),
        vec3d(1,0,0),
        vec3d(1,1,0),
        vec3d(0,1,0)
    };
    std::vector<std::vector<uint>> face = {{ 0, 1, 2, 3, 4, 5, 6 }};
    base_elem = Polygonmesh<>(verts,face);
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Polygonmesh<> UTester::deform(float t) const
{
    if (t==0.0) t = 1e-5; // avoid perfectly collapsed element
    Polygonmesh<> m = base_elem;
    m.vert(1) = vec3d(0.25,0,0) * (1.0-t) + vec3d(0.01,0.99,0) * t;
    m.vert(2) = vec3d(0.5,0,0)  * (1.0-t) + vec3d(0.5,0.99,0)  * t;
    m.vert(3) = vec3d(0.75,0,0) * (1.0-t) + vec3d(0.99,0.99,0) * t;
    m.update_p_tessellations();
    return m;
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

ZetaTester::ZetaTester() : AbstractVEMelement()
{
    std::vector<vec3d> verts =
    {
        vec3d(0,0,0),
        vec3d(1,0,0),
        vec3d(1,0.5,0),
        vec3d(1,1,0),
        vec3d(0,1,0),
        vec3d(0,0.5,0),
    };
    std::vector<std::vector<uint>> face = {{ 0, 1, 2, 3, 4, 5 }};
    base_elem = Polygonmesh<>(verts,face);
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Polygonmesh<> ZetaTester::deform(float t) const
{
    Polygonmesh<> m = base_elem;
    m.vert(2) = vec3d(1,0.5,0) * (1.0-t) + vec3d(0.02,0.01,0) * t;
    m.vert(5) = vec3d(0,0.5,0) * (1.0-t) + vec3d(0.98,0.99,0) * t;
    m.update_p_tessellations();
    return m;
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

CombTester::CombTester(const uint max_dents) : AbstractVEMelement()
  , max_dents(max_dents)
{
    std::vector<vec3d> verts =
    {
        vec3d(0,0,0),
        vec3d(2,0,0),
        vec3d(2,1,0),
        vec3d(0,1,0)
    };
    std::vector<std::vector<uint>> face = {{ 0, 1, 2, 3 }};
    base_elem = Polygonmesh<>(verts,face);
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Polygonmesh<> CombTester::deform(float t) const
{
    uint n_dents = std::round(t * max_dents);
    std::vector<float> samples = sample_within_interval(0.f, 2.f, n_dents*2+3);
    std::vector<uint>  f;
    std::vector<vec3d> verts;
    for(uint i=0; i<samples.size(); ++i)
    {
        verts.push_back(vec3d(samples.at(i), ((i%2)==0)?0:0.5, 0));
        f.push_back(i);
    }
    verts.push_back(vec3d(2,1,0));
    verts.push_back(vec3d(0,1,0));
    f.push_back(f.size());
    f.push_back(f.size());

    std::vector<std::vector<uint>> face = { f };
    Polygonmesh<> m(verts,face);
    return m;
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

RandomTester::RandomTester(const std::string fname) : AbstractVEMelement()
  , filename(fname)
{
    base_elem = Polygonmesh<>(fname.c_str());
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Polygonmesh<> RandomTester::deform(float t) const
{
    return base_elem;
}
