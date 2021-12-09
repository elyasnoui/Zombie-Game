#include "pch.h"
#include "player.h"
#include "engine/core/input.h"
#include "engine/key_codes.h"

player::player()
{
	m_timer = m_speed = 0.0f;
}

player::~player()
{}

void player::initialise(engine::ref<engine::game_object> object)
{
	m_object = object;
	m_object->set_forward(glm::vec3(0.f, 0.f, -1.f));
	m_object->set_position(glm::vec3(4.f, 0.5, 5.f));
	m_object->animated_mesh()->set_default_animation(1);
}

void player::on_update(const engine::timestep& time_step)
{
	m_object->set_position(m_object->position() += m_object->forward() * m_speed *
		(float)time_step);

	m_object->animated_mesh()->on_update(time_step);

	m_object->set_rotation_amount(atan2(m_object->forward().x, m_object->forward().z));

	float m_prev_speed = m_speed;

	bool left = (engine::input::key_pressed(engine::key_codes::KEY_A) ||
		engine::input::key_pressed(engine::key_codes::KEY_LEFT))
		&& !m_jumping;

	bool right = (engine::input::key_pressed(engine::key_codes::KEY_D) ||
		engine::input::key_pressed(engine::key_codes::KEY_RIGHT))
		&& !m_jumping;

	bool forward = (engine::input::key_pressed(engine::key_codes::KEY_W) ||
		engine::input::key_pressed(engine::key_codes::KEY_UP))
		&& !m_jumping;

	bool backward = (engine::input::key_pressed(engine::key_codes::KEY_S) ||
		engine::input::key_pressed(engine::key_codes::KEY_DOWN))
		&& !m_jumping;

	// Turning Left
	if (left && m_camera_mode != 3)
		turn(1.0f * time_step);

	// Turning Right
	if (right && m_camera_mode != 3)
		turn(-1.0f * time_step);

	// Move Forward
	if (forward && m_camera_mode != 3)
	{
		if (engine::input::key_pressed(engine::key_codes::KEY_LEFT_SHIFT) && !(left || right || backward))
		{
			run();

			if (m_prev_speed == m_walking_speed)
				m_moving = false;
		}
		else
		{
			walk(m_walking_speed);

			if (m_prev_speed == m_running_speed)
				m_moving = false;
		}
			
	}

	// Move Backwards
	if (backward && m_camera_mode != 3)
		walk(-m_walking_speed);

	if (!left && !right && !forward && !backward)
		m_moving = false;

	if (!m_moving && !m_idle)
	{
		m_speed = 0.f;
		m_idle = true;
		m_object->animated_mesh()->switch_animation(m_object->animated_mesh()
			->default_animation());
	}

	// Jumping
	if (engine::input::key_pressed(engine::key_codes::KEY_SPACE) && !m_jumping && m_camera_mode != 3)
		jump();

	// Changing camera lock
	if (engine::input::key_pressed(engine::key_codes::KEY_V))
	{
		m_camera_mode++;

		if (m_camera_mode > 2)
			m_camera_mode = 0;

		Sleep(100);
	}

	if (m_timer > 0.0f)
	{
		m_timer -= (float)time_step;
		if (m_timer < 0.0f)
		{
			m_object->animated_mesh()->switch_root_movement(false);
			m_object->animated_mesh()->switch_animation(m_object->animated_mesh()
				-> default_animation());
			m_jumping = false;
			m_idle = true;
		}
	}
}

void player::update_camera(engine::perspective_camera& camera, const engine::timestep& time_step) {
	// Default first person view
	float A = 1.f;  // Make this follow head position of player when jumping
	float B = 0.f;
	float C = 6.f;

	switch (m_camera_mode)
	{
	// Third person view 1
	case 1:
		A = 1.5f;
		B = 2.5f;
		C = 6.f;
		break;

	// Third person view 2
	case 2:
		A = 2.5f;
		B = 3.5f;
		C = 6.f;
		break;

	/*
	// Free view
	case 3:
		camera.on_update(time_step);
		break;
	*/
	}


	if (m_camera_mode != 3)
	{
		glm::vec3 c_position =
			m_object->position() - glm::normalize(m_object->forward()) * B;
		c_position.y += A;

		glm::vec3 c_direction =
			m_object->position() + glm::normalize(m_object->forward()) * C;
		c_direction.y = 0.f;

		camera.set_view_matrix(c_position, c_direction);
	}
}

void player::turn(float angle)
{
	m_object->set_forward(glm::rotate(m_object->forward(), angle, glm::vec3(0.f, 1.f,
		0.f)));

	if (!m_moving)
		m_object->animated_mesh()->switch_animation(2);

	m_idle = false;
	m_moving = true;
}

void player::jump()
{
	m_idle = false;
	m_moving = false;
	m_jumping = true;

	m_object->animated_mesh()->switch_root_movement(true);
	m_object->animated_mesh()->switch_animation(3);

	m_timer = m_object->animated_mesh()->animations().at(3)->mDuration;
}

void player::walk(float speed)
{
	m_speed = speed;

	if (!m_moving)
		m_object->animated_mesh()->switch_animation(2);

	m_idle = false;
	m_moving = true;
}

void player::run()
{
	m_speed = m_running_speed;

	if (!m_moving)
		m_object->animated_mesh()->switch_animation(4);

	m_idle = false;
	m_moving = true;
}
