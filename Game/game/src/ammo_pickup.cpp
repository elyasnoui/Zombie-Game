#include "ammo_pickup.h"

ammo_pickup::ammo_pickup(const engine::game_object_properties props) : pickup(props)
{}

ammo_pickup::~ammo_pickup()
{}

void ammo_pickup::init()
{
	//init();  Need to fix this later: Memory bug

	m_is_active = true;
}

void ammo_pickup::update(glm::vec3 p, float dt)
{
	//set_rotation_amount(rotation_amount() - dt * 1.5f);

	glm::vec3 d = position() - p;
	if (glm::length(d) < 1.f)
		m_is_active = false;
}

engine::ref<ammo_pickup> ammo_pickup::create(const engine::game_object_properties& props)
{
	return std::make_shared<ammo_pickup>(props);
}
