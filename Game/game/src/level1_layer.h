#pragma once
#include <engine.h>
#include "player.h"

class weapon_pickup;
class ammo_pickup;

class level1_layer : public engine::layer
{
public:
	level1_layer();
	~level1_layer();

    void on_update(const engine::timestep& time_step) override;
    void on_render() override; 
    void on_event(engine::event& event) override;

private:
	void check_bounce();

	engine::ref<engine::skybox>			m_skybox{};
	engine::ref<engine::game_object>	m_terrain{};
	engine::ref<engine::game_object>	m_cow{};
	engine::ref<engine::game_object>	m_tree{};
	engine::ref<engine::game_object>	m_ball{};
	engine::ref<engine::game_object>	m_tetrahedron{};
	engine::ref<engine::game_object>	m_tetrahedron_wrapped{};
	engine::ref<engine::material>		m_tetrahedron_material{};
	engine::ref<engine::game_object>	m_mannequin{};

	engine::ref<weapon_pickup>			m_weapon_pickup{};
	engine::ref<weapon_pickup>			m_weapon_pickup2{};
	engine::ref<weapon_pickup>			m_weapon_pickup3{};
	engine::ref<ammo_pickup>			m_ammo_pickup{};

	engine::ref<engine::material>		m_material{};
	engine::ref<engine::material>		m_mannequin_material{};

	player								m_player{};

	engine::DirectionalLight            m_directionalLight;
	
	std::vector<engine::ref<engine::game_object>>     m_game_objects{};

	engine::ref<engine::bullet_manager> m_physics_manager{};
	engine::ref<engine::audio_manager>  m_audio_manager{};
	float								m_prev_sphere_y_vel = 0.f;
	engine::ref<engine::text_manager>	m_text_manager{};

    engine::orthographic_camera			m_2d_camera; 
    engine::perspective_camera			m_3d_camera;
};
