#include <iostream>

#include "non_uniform_scaling_01.h"

int main(int argc, char *argv[])
{
    Polygonmesh<> mesh(argv[1]);

    non_uniform_scaling (mesh);

    char filename[2048];
    strcpy(filename, argv[1]);
    filename[strlen(filename) - 4] = 0;
    strcat(filename, "_norm01.obj");
    mesh.save(filename);

    return 0;

}
