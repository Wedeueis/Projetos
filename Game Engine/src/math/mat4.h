#pragma once

#include "maths.h"
#include <cstring>

namespace sge{ namespace math {

    struct mat4 {
        mat4();
        mat4(float diagonal);
        ~mat4();

        union { 
          float elements[16]; 
          vec4 columns[4]; 
        };

        static mat4 identity();
        static mat4 ones();

        mat4& multiply(const mat4& other);
        friend mat4 operator*(mat4 left, const mat4& right);
        mat4 operator*=(const mat4& other);

        vec3 multiply(const vec3& other) const;
        friend vec3 operator*(const mat4& left, const vec3& right);

        vec4 multiply(const vec4& other) const;
        friend vec4 operator*(const mat4& left, const vec4& right);

        mat4& invert();

        static mat4 orthographic(float left, float right, float bottom, float top, 
                                  float near, float far);
        static mat4 perspective(float fov, float aspectRatio, float near, float far);

        static mat4 translate(const vec3& translation);
        static mat4 rotate(float angle, const vec3& axis);
        static mat4 scale(const vec3& scale);

        void printElements();
    };

} }


