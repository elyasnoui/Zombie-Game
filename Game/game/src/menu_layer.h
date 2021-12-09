#pragma once
#include <engine.h>

class menu_layer : public engine::layer
{
public:
	menu_layer();
	~menu_layer();

	void on_update(const engine::timestep& time_step) override;
	void on_render() override;
	void on_event(engine::event& event) override;

private:
	engine::ref<engine::audio_manager>  m_audio_manager{};
	float								m_prev_sphere_y_vel = 0.f;
	engine::ref<engine::text_manager>	m_text_manager{};

	engine::orthographic_camera			m_2d_camera;
	engine::perspective_camera			m_3d_camera;
};
