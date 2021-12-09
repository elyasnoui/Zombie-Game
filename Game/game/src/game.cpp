// --------- Entry Point ---------------
#include "level1_layer.h"
#include "menu_layer.h"
#include "engine/core/entry_point.h"
#include "engine/events/key_event.h"

class sandbox_app : public engine::application
{
public:
    sandbox_app()
    {
        menu = new menu_layer();
        push_layer(menu);
    }

    ~sandbox_app() = default;

    void on_event(engine::event& event) override
    {
        application::on_event(event);

        engine::event_dispatcher dispatcher(event);
        // dispatch event on window X pressed 
        dispatcher.dispatch<engine::key_pressed_event>(BIND_EVENT_FN(sandbox_app::on_key_pressed));
    }

    bool on_key_pressed(engine::key_pressed_event& event)
    {
        if (event.event_type() == engine::event_type_e::key_pressed)
        {
            if (event.key_code() == engine::key_codes::KEY_ESCAPE)
            {
                application::exit();
            }

            else if (event.key_code() == engine::key_codes::KEY_ENTER && !game_running)
            {
                switch_layer(menu, new level1_layer());
                game_running = true;
            }

            //PYRO_TRACE("{0}", static_cast<char>(e.key_code())); 
        }
        return false;
    }

    void switch_layer(engine::layer *from, engine::layer *to) {
        pop_layer(from);
        push_layer(to);
    }

private:
    menu_layer *menu;
    bool game_running = false;
};

engine::application* engine::create_application()
{
    return new sandbox_app();
}
