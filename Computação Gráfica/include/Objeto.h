#ifndef OBJETO_H
#define OBJETO_H

#include <string>
#include <iostream>
#include <cmath>
#include "Shader.h"

using namespace std;

struct vertex {
    float x, y, z;
    float r, g, b;
    float nx, ny, nz;
};

struct material {
    float ka, kd, ks;
    float expd, exps;
};

typedef  unsigned int indexT;

class Objeto {
public:
    Objeto(const camera &cam, string meshfilename):cam(cam) {
       	r = 1.0;
		g = 1.0;
		b = 1.0;
		load(meshfilename);
        mesh = meshfilename;
        faceculling = false;
		mat = new material;
		mat->ka = 0.1;
		mat->kd = mat->ks = 0.5;
		mat->expd = mat->exps = 1.0;
    }

    ~Objeto() {
        delete vert;
        delete ind;
		delete mat;
    }
    bool faceculling;

    void scale(float s) {
        modelMatrix.scale(s, s, s);
    }
    void rotatey(int a) {
        modelMatrix.rotatey(a);
    }
    void rotatez(int a) {
        modelMatrix.rotatez(a);
    }
    void rotatex(int a) {
        modelMatrix.rotatex(a);
    }
    void translate(float dx, float dy, float dz) {
        modelMatrix.translate(dx, dy, dz);
    }
    void draw(const Shader *shader);

	void defineMaterial(float ka, float kd, float expd, float ks, float exps);

	void defineColor(float r, float g, float b);

protected:
private:
    int nv, nf, ne;
    float r, g, b;
    string mesh;

    mat44 modelMatrix;
    const camera &cam;

    vertex *vert;
    indexT *ind;
	material *mat;
    GLuint iVBO, iIBO;

    void load(string filename);
};

void Objeto::load(string filename) {
    ifstream f(filename);

    int i, j, k;
    string s;
    f >> s;  // le a palavra "OFF"
    f >> nv >> nf >> ne;  // lê o nro de vértices, faces e arestas

    vert = new vertex[nv];
    ind = new indexT[3*nf];
    // lê a posição dos pontos
    for (i=0; i<nv; i++) f >> vert[i].x >> vert[i].y >> vert[i].z; // >> vert[i].r >> vert[i].g >> vert[i].b;
    // lê os índices dos polígonos
    for (i=0, j=0; i<nf; i++, j+=3) f >> k >> ind[j] >> ind[j+1] >> ind[j+2];

    // lê as cores e zera as normais
    for (i=0; i<nv; i++) {
        vert[i].r = r;
        vert[i].g = g;
        vert[i].b = b;
        vert[i].nx = 0.0;
        vert[i].ny = 0.0;
        vert[i].nz = 0.0;
    }

    //  Calcular as normais
    vertex *v1, *v2, *v3;
    float ax, ay, az, bx, by, bz, nx, ny, nz, norm;

    for(i = 0, j = 0; i<nf; i++) {
        v1 = vert + ind[j++];
        v2 = vert + ind[j++];
        v3 = vert + ind[j++];

        ax = v1->x-v2->x;
        ay = v1->y-v2->y;
        az = v1->z-v2->z;

        bx = v1->x-v3->x;
        by = v1->y-v3->y;
        bz = v1->z-v3->z;

        nx = ay*bz - az*by;
        ny = az*bx - ax*bz;
        nz = ax*by - ay*bx;

        v1->nx += nx;
        v1->ny += ny;
        v1->nz += nz;

        v2->nx += nx;
        v2->ny += ny;
        v2->nz += nz;

        v3->nx += nx;
        v3->ny += ny;
        v3->nz += nz;

    }

    for (i=0; i<nv; i++) {
        ax = vert[i].nx;
        ay = vert[i].ny;
        az = vert[i].nz;

        norm = sqrt(ax*ax + ay*ay + az*az);

        vert[i].nx = ax/norm;
        vert[i].ny = ay/norm;
        vert[i].nz = az/norm;
    }

    // Criação do VBO e IBO
    glGenBuffers(1, &iVBO);
    glBindBuffer(GL_ARRAY_BUFFER, iVBO);
    glBufferData(GL_ARRAY_BUFFER, nv*sizeof(vertex), vert, GL_STATIC_DRAW);

    glGenBuffers(1, &iIBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3*nf*sizeof(indexT), ind, GL_STATIC_DRAW);
}

void Objeto::draw(const Shader *shader) {
    glBindBuffer(GL_ARRAY_BUFFER, iVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)12);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)24);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iIBO);

    if (faceculling) glEnable(GL_CULL_FACE);
    else  glDisable(GL_CULL_FACE);

	const float coef[3] = {mat->ka, mat->kd, mat->ks};
	const float exp[2] = {mat->expd, mat->exps};
	shader->sendMaterial(coef,exp);

    shader->sendMVP(modelMatrix.multleft(cam.mptr));

    glDrawElements(GL_TRIANGLES, 3*nf, GL_UNSIGNED_INT, (GLvoid*)0);
}

void Objeto::defineMaterial(float ka, float kd, float expd, float ks, float exps){
	mat->ka = ka;
	mat->kd = kd;
	mat->ks = ks;
	mat->expd = expd;
	mat->exps = exps;
}

void Objeto::defineColor(float r, float g, float b){
	this->r = r;
	this->g = g;
	this->b = b;
	load(mesh);
}

#endif // OBJETO_H
