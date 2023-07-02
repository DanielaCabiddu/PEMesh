# PEMesh

A Graphical Framework to Study the Correlation between Geometric Design and Simulation.

<p align="center"><img src="change_gui_2d_rep_image.png" width="750"></p>

## Dependencies

The framework depends on:
- the cinolib library (commit 00b270d), which is included as a submodule ;
- Triangle library, which is included as a submodule;
- Qt framework, including Qt Charts module, which is assumed to be installed on the local machine (version 5.12.0);
- Boost library, which is assumed to be installed on the local machine.

## How to make it work

Please, use --recursive when cloning this repository.

`git clone --recursive https://github.com/DanielaCabiddu/PEMesh`

In the following, please consider `${REPO_ROOT}` variable as the folder where this README.md lies.
PMesh can be built by running either QMake or CMake. 
In both cases, the PMesh executable will be available in the `${REPO_ROOT}/build` folder.

### QMake 

First, build triangle library

`cd ${REPO_ROOT}/external/triangle`\
`mkdir build`\
`cd build`\
`cmake ..`\
`make`

Then, build PEMesh by running the following commands:

`mkdir -p ${REPO_ROOT}/build`\
`cd build`\
`qmake ../src/PMesh.pro`

### CMake

Run the following commands:

`mkdir -p ${REPO_ROOT}/build`\
`cd build`\
`cmake ../src`

Triangle library will be automatically built by CMake.
 

## Other Authors
* Giuseppe Patanè (CNR IMATI), Michela Spagnuolo (CNR IMATI)

## Citing us
PEMesh has been published as a Software Paper (https://diglib.eg.org/bitstream/handle/10.2312/stag20221251/011-019.pdf?sequence=1&isAllowed=y).

If you use PEMesh in your academic projects, please consider citing it using the following BibTeX entries:

```bibtex
@inproceedings {pemesh-stag2022,
booktitle = {Smart Tools and Applications in Graphics - Eurographics Italian Chapter Conference},
editor = {Cabiddu, Daniela and Schneider, Teseo and Allegra, Dario and Catalano, Chiara Eva and Cherchi, Gianmarco and Scateni, Riccardo},
title = {{A Graphical Framework to Study the Correlation between Geometric Design and Simulation}},
author = {Cabiddu, Daniela and Patané, Giuseppe and Spagnuolo, Michela},
year = {2022},
publisher = {The Eurographics Association},
ISSN = {2617-4855},
ISBN = {978-3-03868-191-5},
DOI = {10.2312/stag.20221251}
}

@article{benchmark-mcs,
title = {Benchmarking the geometrical robustness of a Virtual Element Poisson solver},
journal = {Mathematics and Computers in Simulation},
volume = {190},
pages = {1392-1414},
year = {2021},
issn = {0378-4754},
doi = {https://doi.org/10.1016/j.matcom.2021.07.018},
url = {https://www.sciencedirect.com/science/article/pii/S0378475421002706},
author = {Marco Attene and Silvia Biasotti and Silvia Bertoluzza and Daniela Cabiddu and Marco Livesu and Giuseppe Patanè and Micol Pennacchio and Daniele Prada and Michela Spagnuolo},
keywords = {Polytopal Element Methods, Virtual Element Methods, Polygonal meshes, Geometric metrics, Geometry-PEM correlation},
abstract = {Polytopal Element Methods (PEM) allow us solving differential equations on general polygonal and polyhedral grids, potentially offering great flexibility to mesh generation algorithms. Differently from classical finite element methods, where the relation between the geometric properties of the mesh and the performances of the solver are well known, the characterization of a good polytopal element is still subject to ongoing research. Current shape regularity criteria are quite restrictive, and greatly limit the set of valid meshes. Nevertheless, numerical experiments revealed that PEM solvers can perform well on meshes that are far outside the strict boundaries imposed by the current theory, suggesting that the real capabilities of these methods are much higher. In this work, we propose a benchmark to study the correlation between general 2D polygonal meshes and PEM solvers which we test on a virtual element solver for the Poisson equation. The benchmark aims to explore the space of 2D polygonal meshes and polygonal quality metrics, in order to understand if and how shape regularity, defined according to different criteria, affects the performance of the method. The proposed tool is quite general, and can be potentially used to study any PEM solver. Besides discussing the basics of the benchmark, we demonstrate its application on a representative member of the PEM family, namely the Virtual Element Method, also discussing our findings.}
}
```

## Acknowledgements
This paper has been realized in the framework of ERC Project CHANGE (https://cordis.europa.eu/project/id/694515), which has received funding from the European Research Council (ERC) under the European Union’s Horizon 2020 research and innovation programme (grant agreement No 694515).

Special thanks to Marco Livesu for sharing with us the source code to generate parametric polygons and compute geometric metrics.
