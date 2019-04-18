#include <application.h>

// LED instance
bc_led_t led;

// Button instance
bc_button_t button;

// Relay instance
bc_module_relay_t relay;

void button_event_handler(bc_button_t *self, bc_button_event_t event, void *event_param)
{
    if (event == BC_BUTTON_EVENT_PRESS)
    {
        bc_radio_pub_bool("doorBell", true);
        bc_module_relay_set_state(&relay, true);

    }
    else if (event == BC_BUTTON_EVENT_RELEASE)
    {
        bc_module_relay_set_state(&relay, false);
    }
}

void application_init(void)
{
    bc_log_init(BC_LOG_LEVEL_DUMP, BC_LOG_TIMESTAMP_ABS);

    // Initialize Relay Module
    bc_module_relay_init(&relay, 0x3B);

    // Initialze battery module
    bc_module_battery_init();

    // Initialize radio
    bc_radio_pairing_request("smart-bell", VERSION);
    bc_radio_init(BC_RADIO_MODE_NODE_SLEEPING);

    // Initialize button
    bc_button_init(&button, BC_GPIO_BUTTON, BC_GPIO_PULL_DOWN, false);
    bc_button_set_event_handler(&button, button_event_handler, NULL);
}
