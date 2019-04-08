#ifndef MAT44_H
#define MAT44_H

#include<cmath>
#include<array>
#include<cstdio>

#define PI 3.14159265

using namespace std;

class mat44 {
public:
    mat44();  // Construtor
    ~mat44();  // Destrutor

    // Ponteiro público para os elementos da matrix
    const float *mptr;

    // Principais métodos
    void identity();  // Carrega a matriz identidade
    void rotatex(int degrees); // Multiplica a esquerda por uma matriz de rotação
    void rotatey(int degrees); // Multiplica a esquerda por uma matriz de rotação
    void rotatez(int degrees); // Multiplica a esquerda por uma matriz de rotação
    void translate(float dx, float dy, float dz); // Multiplica a esquerda por uma matriz de translação
    void scale(float sx, float sy, float sz); // Multiplica a esquerda por uma matriz de escala
    const float* multleft(const float *mtl);


    void print();  // Imprime no console a matriz atual

private:
    array <float, 16> m;  // Matriz (vetor) principal
    array <float, 16> maux; // // Matriz (vetor) auxiliar
};


void mat44::identity() {
    m = {1, 0, 0, 0,
         0, 1, 0, 0,
         0, 0, 1, 0,
         0, 0, 0, 1};
    mptr = m.data();
}

void mat44::rotatex(int degrees) {
    float rads = degrees*PI/180;
    float c = cos(rads);
    float s = sin(rads);

    maux = {m[0],           m[1],          m[2],         m[3],
            c*m[4]-s*m[8],  c*m[5]-s*m[9], c*m[6]-s*m[10], c*m[7]-s*m[11],
            s*m[4]+c*m[8],  s*m[5]+c*m[9], s*m[6]+c*m[10], s*m[7]+c*m[11],
            m[12],          m[13],         m[14],         m[15]
           };
    m=maux;
}

void mat44::rotatey(int degrees){
    float rads = degrees*PI/180;
    float c = cos(rads);
    float s = sin(rads);

    maux = {c*m[0]+s*m[8],  c*m[1]+s*m[9],  c*m[2]+s*m[10],  c*m[3]+s*m[11],
            m[4],           m[5],           m[6],            m[7],
            -s*m[0]+c*m[8], -s*m[1]+c*m[9], -s*m[2]+c*m[10], -s*m[3]+c*m[11],
            m[12],          m[13],          m[14],           m[15]
    };
    m=maux;
}

void mat44::rotatez(int degrees) {
    float rads = degrees*PI/180;
    float c = cos(rads);
    float s = sin(rads);

    maux = {c*m[0]-s*m[4],  c*m[1]-s*m[5], c*m[2]-s*m[6], c*m[3]-s*m[7],
            s*m[0]+c*m[4],  s*m[1]+c*m[5], s*m[2]+c*m[6], s*m[3]+c*m[7],
            m[8],           m[9],          m[10],         m[11],
            m[12],          m[13],         m[14],         m[15]
           };
    m=maux;
}


void mat44::translate(float dx, float dy, float dz) {
    maux = {m[0]+dx*m[12],  m[1]+dx*m[13], m[2]+dx*m[14], m[3]+dx*m[15],
            m[4]+dy*m[12],  m[5]+dy*m[13], m[6]+dy*m[14], m[7]+dy*m[15],
            m[8]+dz*m[12],  m[9]+dz*m[13], m[10]+dz*m[14],m[11]+dz*m[15],
            m[12],          m[13],          m[14],   m[15]
           };
    m=maux;
}


void mat44::scale(float sx, float sy, float sz){
    maux = {sx*m[0], sx*m[1], sx*m[2],  sx*m[3],
            sy*m[4], sy*m[5], sy*m[6],  sy*m[7],
            sz*m[8], sz*m[9], sz*m[10], sz*m[11],
            m[12],   m[13],   m[14],    m[15]
    };
    m=maux;
}

const float* mat44::multleft(const float *mtl) {
   maux[0] = mtl[0]*m[0] + mtl[1]*m[4] + mtl[2]*m[8] + mtl[3]*m[12];
   maux[1] = mtl[0]*m[1] + mtl[1]*m[5] + mtl[2]*m[9] + mtl[3]*m[13];
   maux[2] = mtl[0]*m[2] + mtl[1]*m[6] + mtl[2]*m[10] + mtl[3]*m[14];
   maux[3] = mtl[0]*m[3] + mtl[1]*m[7] + mtl[2]*m[11] + mtl[3]*m[15];

   maux[4] = mtl[4]*m[0] + mtl[5]*m[4] + mtl[6]*m[8] + mtl[7]*m[12];
   maux[5] = mtl[4]*m[1] + mtl[5]*m[5] + mtl[6]*m[9] + mtl[7]*m[13];
   maux[6] = mtl[4]*m[2] + mtl[5]*m[6] + mtl[6]*m[10] + mtl[7]*m[14];
   maux[7] = mtl[4]*m[3] + mtl[5]*m[7] + mtl[6]*m[11] + mtl[7]*m[15];

   maux[8] = mtl[8]*m[0] + mtl[9]*m[4] + mtl[10]*m[8] + mtl[11]*m[12];
   maux[9] = mtl[8]*m[1] + mtl[9]*m[5] + mtl[10]*m[9] + mtl[11]*m[13];
   maux[10] = mtl[8]*m[2] + mtl[9]*m[6] + mtl[10]*m[10] + mtl[11]*m[14];
   maux[11] = mtl[8]*m[3] + mtl[9]*m[7] + mtl[10]*m[11] + mtl[11]*m[15];

   maux[12] = mtl[12]*m[0] + mtl[13]*m[4] + mtl[14]*m[8] + mtl[15]*m[12];
   maux[13] = mtl[12]*m[1] + mtl[13]*m[5] + mtl[14]*m[9] + mtl[15]*m[13];
   maux[14] = mtl[12]*m[2] + mtl[13]*m[6] + mtl[14]*m[10] + mtl[15]*m[14];
   maux[15] = mtl[12]*m[3] + mtl[13]*m[7] + mtl[14]*m[11] + mtl[15]*m[15];

   const float *multesq = maux.data();
   return multesq;
}


void mat44::print() {
    printf("%4.1f %4.1f %4.1f %4.1f\n", m[0], m[1], m[2], m[3]);
    printf("%4.1f %4.1f %4.1f %4.1f\n", m[4], m[5], m[6], m[7]);
    printf("%4.1f %4.1f %4.1f %4.1f\n", m[8], m[9], m[10], m[11]);
    printf("%4.1f %4.1f %4.1f %4.1f\n", m[12], m[13], m[14], m[15]);
}


mat44::mat44() {
    identity();
}

mat44::~mat44() {
    //destrutor
}


#endif // MAT44_H
