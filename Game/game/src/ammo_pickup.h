#pragma once
#include "pickup.h"

class ammo_pickup : public pickup
{
public:
	ammo_pickup(const engine::game_object_properties props);
	~ammo_pickup();

	void init() override;
	void update(glm::vec3 c, float dt) override;
	bool active() { return m_is_active; }
	static engine::ref<ammo_pickup> create(const engine::game_object_properties& props);

private:
	bool m_is_active;
};
