#include "pickup.h"

pickup::pickup(const engine::game_object_properties props) : engine::game_object(props)
{}

pickup::~pickup()
{}

void pickup::init()
{
	m_is_active = true;
}

void pickup::update(glm::vec3 c, float dt)
{}

engine::ref<pickup> pickup::create(const engine::game_object_properties& props)
{
	return std::make_shared<pickup>(props);
}
