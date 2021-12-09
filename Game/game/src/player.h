#pragma once
#include <engine.h>
#include "glm/gtx/rotate_vector.hpp"

class player
{
public:
	player();
	~player();

	void initialise(engine::ref<engine::game_object> object);
	void on_update(const engine::timestep& time_step);

	engine::ref<engine::game_object> object() const { return m_object; }

	void turn(float angle);
	void update_camera(engine::perspective_camera& camera, const engine::timestep& time_step);

	void jump();
	void walk(float speed);
	void run();

private:
	float	m_speed{ 0.f };
	float	m_timer;

	bool    m_idle = true;
	bool	m_moving = false;
	bool    m_jumping = false;

	int		m_camera_mode = 0;

	const float m_walking_speed = 3.f;
	const float m_running_speed = 5.f;

	engine::ref<engine::game_object> m_object;
};
