#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>

class Shader {
public:
    Shader(string vs_filename, string fs_filename);
    virtual ~Shader() {}

    void enable() const;


    void sendLight(const float *light) const {
       glUniform4fv(id_light, 1, light);
    }

    void sendVCam(const float *vcam) const {
       glUniform3fv(id_vcam, 1, vcam);
    }

    void sendMVP(const float *MVP) const {
       glUniformMatrix4fv(id_MVP, 1, GL_TRUE, MVP);
    }
	void sendMaterial(const float *coef, const float *exp) const {
		 glUniform3fv(id_coef, 1, coef);
		 glUniform2fv(id_exp, 1, exp);
	}

protected:
private:
    string readFile(string filename);
    GLuint shaderProgram;

    GLuint id_MVP;
    GLuint id_light;
    GLuint id_vcam;
	GLuint id_coef;
	GLuint id_exp;
};


string Shader::readFile(string filename) {
    ifstream t(filename);
    stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}


Shader::Shader(string vs_filename, string fs_filename) {
    string vss = readFile(vs_filename);
    string fss = readFile(fs_filename);
    const char *vertexShaderText = vss.c_str();
    const char *fragmentShaderText = fss.c_str();

    cout << vertexShaderText << endl << endl;
    cout << fragmentShaderText << endl << endl;

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderText, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderText, nullptr);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);


    id_MVP = 3;
    id_light = 4;
    id_vcam = 5;
	id_coef = 6;
	id_exp = 7;
	

    GLenum ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR) {
        cout << "Problema com os Shaders! " << ErrorCheckValue << endl;
        exit(-1);
    }

}

//  Habilita este Shader
void Shader::enable() const {
    glUseProgram(shaderProgram);
}


#endif // SHADER_H



