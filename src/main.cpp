#include "gui.h"
int main(int argc, char *argv[]) {
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "com.example.app");

    WelcomeScreen welcome_screen;
    welcome_screen.show_all();

    return app->run(welcome_screen);
}