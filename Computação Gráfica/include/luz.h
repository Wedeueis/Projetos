#ifndef LUZ_H
#define LUZ_H


class luz {
public:
    // Construtor
    luz(float x, float y, float z, float i) {
        this->x = x;         this->y = y;         this->z = z;
        this->i = i;
    }
	~luz(){};

    // transforma a posi��o da luz para o sistema de coordenada da c�mera
    const float *viewpos(const camera &c) {
        const float *m = c.mptr;
        vp[0] = m[0]*x + m[1]*y + m[2]*z + m[3];
        vp[1] = m[4]*x + m[5]*y + m[6]*z + m[7];
        vp[2] = m[8]*x + m[9]*y + m[10]*z + m[11];
		vp[3] = this-> i;

        return vp;
    }

    const float getIntensidade(){
        return this->i;
    }
private:
    // Posi��o da luz no sistema de coordenadas do mundo
    float x, y, z;
    float i;

    // Coordenadas da luz transformadas para o sistema da c�mera
    float vp[4];
};

#endif // LUZ_H
