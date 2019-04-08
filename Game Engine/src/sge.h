#pragma once

#include "app/window.h"
#include "app/input.h"
#include "graphic/renderer/batch2Drenderer.h"
#include "graphic/layers/layer.h"
#include "graphic/layers/group.h"
#include "graphic/renderable/sprite.h"
#include "gui/label.h"
#include "graphic/animation/spritesheet.h"
#include "font/fontmanager.h"

#include "audio/soundmanager.h"

#include "utils/timer.h"
#include "utils/colors.h"

#include "math/maths.h"

#ifndef DEBUG
#define DEBUG
#define LOG(x) std::cout << x << std::endl
#endif

