#pragma once

#include <vector>
#include "../../entity/gameobject.h"
#include "../../../ext/box2d/include/Box2D.h"
#include "../../physics/debugdraw.h"
#include "renderable2D.h"

namespace sge { namespace graphics {

	class Scene: public Renderable2D {
	public:
		static b2World *world;
	private:
		physics::DebugDraw *m_DDraw;
		std::vector<entity::Object*> m_Objects;
		Sprite *m_Background;
		float timeStep;
		int velocityIterations;
		int positionIterations;
		bool hasGravity;
	public:
		Scene(float x, float y, float width, float height, unsigned int color);

		Scene(float x, float y, float width, float height, Texture* background);

		~Scene();

		void add(entity::Object* object);

		virtual void onEvent(events::Event& event) override;
		virtual void onUpdate() override;

		virtual void submit(Renderer2D* renderer) const override;

		inline const std::vector<entity::Object*>& getObjects() const { return m_Objects; }
	};

} }