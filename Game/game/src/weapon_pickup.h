#pragma once
#include "pickup.h"

class weapon_pickup : public pickup
{
public:
	weapon_pickup(const engine::game_object_properties props);
	~weapon_pickup();

	void init() override;
	void update(glm::vec3 c, float dt) override;
	bool active() { return m_is_active; }
	static engine::ref<weapon_pickup> create(const engine::game_object_properties& props);

private:
	bool m_is_active;
};
