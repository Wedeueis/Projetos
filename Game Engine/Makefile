all: bin/game

clean:
	-rm bin/game
	-rm bin/*.o

CFLAGS = -std=c++11
LIBS = -lGL -lGLU -lglfw -lGLEW -lX11 -lXxf86vm -lXrandr -lXi -lfreeimage -Lext/freetype-gl/lib/ -lfreetype-gl \
-lfreetype -Lext/gorilla-audio/lib/ -lgorilla -Lext/openal/lib/ -lopenal -lpthread -Lext/box2d/lib/ -lBox2D

bin/window.o: src/app/window.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/vec2.o: src/math/vec2.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/vec3.o: src/math/vec3.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/vec4.o: src/math/vec4.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/mat4.o: src/math/mat4.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/rec.o: src/math/rectangle.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/aabb.o: src/math/aabb.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/shader.o: src/graphic/shader/shader.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/buffer.o: src/graphic/buffers/buffer.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/indexbuffer.o: src/graphic/buffers/indexbuffer.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/vertexarray.o: src/graphic/buffers/vertexarray.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/sprite.o: src/graphic/renderable/sprite.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/scene.o: src/graphic/renderable/scene.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/spritesheet.o: src/graphic/animation/spritesheet.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/animation.o: src/graphic/animation/animation.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/brenderer.o: src/graphic/renderer/batch2Drenderer.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/layer.o: src/graphic/layers/layer.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/tilelayer.o: examples/tilelayer.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/group.o: src/graphic/layers/group.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/texture.o: src/graphic/texture/texture.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/texturemanager.o: src/graphic/texture/texturemanager.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/label.o: src/gui/label.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/font.o: src/font/font.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/fontmanager.o: src/font/fontmanager.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/sound.o: src/audio/sound.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/soundmanager.o: src/audio/soundmanager.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/app.o: src/app/application.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/input.o: src/app/input.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/event.o: src/event/event.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/keyevent.o: src/event/keyevent.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/mouseevent.o: src/event/mouseevent.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/windowevent.o: src/event/windowevent.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/panel.o: src/gui/panel.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/widget.o: src/gui/widget.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/comp.o: src/gui/component.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/button.o: src/gui/button.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/slider.o: src/gui/slider.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/entity.o: src/entity/entity.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/object.o: src/entity/object.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/gameobject.o: src/entity/gameobject.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/component.o: src/entity/component/component.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/spritecomponent.o: src/entity/component/spritecomponent.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/transformcomponent.o: src/entity/component/transformcomponent.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/body.o: src/physics/body.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/dynamicbody.o: src/physics/dynamicbody.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/debugdraw.o: src/physics/debugdraw.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/robot.o: examples/Robots/robot.cpp
	g++ $< -o $@ $(CFLAGS) -c

bin/game: examples/Robots/robots.cpp bin/robot.o bin/debugdraw.o bin/window.o bin/vec2.o bin/vec3.o bin/vec4.o bin/mat4.o bin/shader.o \
	bin/buffer.o bin/indexbuffer.o bin/vertexarray.o bin/sprite.o bin/brenderer.o bin/layer.o \
	bin/tilelayer.o bin/group.o bin/texture.o bin/label.o bin/font.o bin/fontmanager.o bin/sound.o \
	bin/soundmanager.o bin/app.o bin/input.o bin/event.o bin/keyevent.o bin/mouseevent.o bin/windowevent.o \
	bin/texturemanager.o bin/rec.o bin/panel.o bin/widget.o bin/comp.o bin/button.o bin/slider.o \
	bin/entity.o bin/scene.o bin/component.o bin/spritecomponent.o bin/transformcomponent.o bin/spritesheet.o \
	bin/gameobject.o bin/animation.o bin/body.o bin/object.o bin/dynamicbody.o
	g++ $< -o $@ bin/robot.o  bin/shader.o bin/window.o bin/vec2.o bin/vec3.o bin/vec4.o bin/mat4.o bin/buffer.o \
	bin/indexbuffer.o bin/vertexarray.o bin/sprite.o bin/brenderer.o bin/layer.o bin/tilelayer.o \
	bin/group.o bin/texture.o bin/label.o bin/font.o bin/fontmanager.o bin/sound.o bin/soundmanager.o \
	bin/app.o bin/input.o bin/event.o bin/keyevent.o bin/mouseevent.o bin/windowevent.o bin/texturemanager.o \
	bin/rec.o bin/panel.o bin/widget.o bin/comp.o bin/button.o bin/slider.o bin/entity.o bin/scene.o \
	bin/component.o bin/spritecomponent.o bin/transformcomponent.o bin/spritesheet.o \
	bin/gameobject.o bin/animation.o bin/body.o bin/object.o bin/dynamicbody.o bin/debugdraw.o $(CFLAGS) $(LIBS) 