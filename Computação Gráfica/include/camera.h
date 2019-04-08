#ifndef CAMERA_H
#define CAMERA_H
#include <array>
#include <cmath>
#include <cstdio>

using namespace std;

class camera {
public:
    camera(float xp, float yp, float zp,float xla,float yla,float zla,float vx,float vy,float vz, float zpf);
    const float *mptr;
    virtual ~camera()
	{
		delete mptr;
	};
    void defineVP();
	void translate(float dx, float dy, float dz);
	void rotatex(int degrees);
	void rotatey(int degrees);
	void rotatez(int degrees);
	void orbit(int degrees);
	const float *getV();
    void print();

private:
    array <float, 16> m;
    float xp, yp, zp;
	float xla, yla, zla;
	float vcx, vcy, vcz;
	float zpf;
	float v[3];

};

void camera::defineVP() {
       // Definir a matriz da câmera (UVN) e depois já multiplicá-la pela matriz de projeção.  Use o array m
		//Vetor N
		float N_norma = sqrt( pow(xp-xla,2) + pow(yp-yla,2) + pow(zp-zla,2) );
		float Nx = (xp-xla) / N_norma;
		float Ny = (yp-yla) / N_norma;
		float Nz = (zp-zla) / N_norma;
		//Vetor U
		float U_norma = sqrt( pow(Nz*vcy - Ny*vcz, 2) + pow(Nx*vcz - Nz*vcx, 2) + pow(Ny*vcx - Nx*vcy, 2) );
		float Ux = (Nz*vcy - Ny*vcz) / U_norma;
		float Uy = (Nx*vcz - Nz*vcx) / U_norma;
		float Uz = (Ny*vcx - Nx*vcy) / U_norma;
		//Vetor V
		float Vx = Ny*Uz - Nz*Uy;
		float Vy = Nz*Ux - Nx*Uz;
		float Vz = Nx*Uy - Ny*Ux;
		// M camera
		float Upcam = -(Ux*xp + Uy*yp + Uz*zp);
		float Vpcam = -(Vx*xp + Vy*yp + Vz*zp);
		float Npcam = -(Nx*xp + Ny*yp + Nz*zp);
		m = { Ux , Uy , Uz , Upcam,
								  Vx , Vy , Vz , Vpcam,
								  Nx , Ny , Nz , Npcam,
								  -Nx/zpf ,  -Ny/zpf  , -Nz/zpf , (-Npcam/zpf) + 1.0f};
		mptr = m.data();

}

const float *camera::getV(){
	float vec_norma = sqrt( (xp-xla)*(xp-xla) + (yp-yla)*(yp-yla) + (zp-zla)*(zp-zla) );
    v[0] = (xp-xla) / vec_norma;
	v[1] = (yp-yla) / vec_norma;
	v[2] = (zp-zla) / vec_norma;
	return v;
}

void camera::print() {
    printf("Camera Matrix\n");
    printf("%4.1f %4.1f %4.1f %4.1f\n", m[0], m[1], m[2], m[3]);
    printf("%4.1f %4.1f %4.1f %4.1f\n", m[4], m[5], m[6], m[7]);
    printf("%4.1f %4.1f %4.1f %4.1f\n", m[8], m[9], m[10], m[11]);
    printf("%4.1f %4.1f %4.1f %4.1f\n\n", m[12], m[13], m[14], m[15]);
}


camera::camera(float xp, float yp, float zp,float xla,float yla,float zla,float vcx,float vcy,float vcz, float zpf) {
	this->xp = xp;
	this->yp = yp;
	this->zp = zp;
	this->xla = xla;
	this->yla = yla;
	this->zla = zla;
	this->vcx = vcx;
	this->vcy = vcy;
	this->vcz = vcz;
	this->zpf = zpf;
	defineVP();
}

void camera::translate(float dx, float dy, float dz) {
	xp += dx;
	yp += dy;
	zp += dz;
	defineVP();
}

void camera::rotatex(int degrees) {
    float rads = degrees*PI/180;
    float c = cos(rads);
    float s = sin(rads);
	float temp = yp*c - zp*s;
	zp = yp*s + zp*c;
	yp = temp;
	defineVP();
}

void camera::rotatey(int degrees) {
    float rads = degrees*PI/180;
    float c = cos(rads);
    float s = sin(rads);
	float temp = zp*c - xp*s;
	xp = zp*s + xp*c;
	zp = temp;
	defineVP();
}

void camera::rotatez(int degrees) {
    float rads = degrees*PI/180;
    float c = cos(rads);
    float s = sin(rads);
	float temp = xp*c - yp*s;
	yp = xp*s + yp*c;
	xp = temp;
	defineVP();
}

void camera::orbit(int degrees) {
	translate(-xla,-yla,-zla);
	rotatey(degrees);
	translate(xla,yla,zla);
	defineVP();
}

#endif // CAMERA_H
