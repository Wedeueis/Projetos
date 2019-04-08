#pragma once

#include "../math/vec2.h"

namespace sge{ namespace physics {

    using namespace math;

    const float xoffset = 1.16;
    const float yoffset = 1.2;
    const float rate = 1;

    inline vec2 worldToScreen(vec2 pos){
        pos.x = (pos.x - xoffset)/rate;
        pos.y = (pos.y - yoffset)/rate;

        return pos;
    }

    inline vec3 worldToScreen(vec3 pos){
        pos.x = (pos.x - xoffset)/rate;
        pos.y = (pos.y - yoffset)/rate;

        return pos;
    }

    inline vec2 screenToWorld(vec2 pos){
        pos.x = (pos.x + xoffset)*rate;
        pos.y = (pos.y + yoffset)*rate;

        return pos;
    }

    inline vec3 screenToWorld(vec3 pos){
        pos.x = (pos.x + xoffset)*rate;
        pos.y = (pos.y + yoffset)*rate;

        return pos;
    }
}}