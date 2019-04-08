#include "scene.h"

namespace sge { namespace graphics {

	b2World* Scene::world = nullptr;

	Scene::Scene(float x, float y, float width, float height, unsigned int color)
	:Renderable2D(math::vec3(x,y,0), math::vec2(width, height), color) {
		m_Background = new Sprite(x,y,width,height, color);
		b2Vec2 gravity(0.0f, 0.0f);
		world = new b2World(gravity);
		m_DDraw = new physics::DebugDraw();
		world->SetDebugDraw( m_DDraw );
		m_DDraw->SetFlags( b2Draw::e_shapeBit );
		timeStep = 1.0f / 60.0f;
		velocityIterations = 6;
		positionIterations = 2;
	}

	Scene::Scene(float x, float y, float width, float height, Texture* background)
	:Renderable2D(math::vec3(x,y,0), math::vec2(width, height), WHITE) {
	  	m_Background = new Sprite(x,y,width,height, background);
	  	b2Vec2 gravity(0.0f, 0.0f);
		world = new b2World(gravity);
		m_DDraw = new physics::DebugDraw();
		world->SetDebugDraw( m_DDraw );
		m_DDraw->SetFlags( b2Draw::e_shapeBit );
	  	timeStep = 1.0f / 60.0f;
		velocityIterations = 6;
		positionIterations = 2;
	}

	Scene::~Scene(){
		for(int i = 0; i<m_Objects.size(); i++)
			delete m_Objects[i];
		delete m_Background;
	}

	void Scene::add(entity::Object* object){
		m_Objects.push_back(object);
	}

	void Scene::onEvent(events::Event& event) {
		for(int i = 0; i<m_Objects.size(); i++)
			m_Objects[i]->onEvent(event);
	}

	void Scene::onUpdate() {
		for(int i = 0; i<m_Objects.size(); i++)
			m_Objects[i]->onUpdate();

		world->Step(timeStep, velocityIterations, positionIterations);
		world->ClearForces();
	}

	void Scene::submit(Renderer2D* renderer) const {
		renderer->submit(m_Background);
		m_DDraw->setRenderer(renderer);
		world->DrawDebugData();
		for(int i = 0; i<m_Objects.size(); i++){
		#if _DEBUG_DRAW
			renderer->drawRect(m_Objects[i]->getSprite()->getBoundBox(), GREEN);
		#endif
			renderer->submit(m_Objects[i]->getSprite());
		}
	}
} }