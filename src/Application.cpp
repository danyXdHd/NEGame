#include <Application.hpp>

Application::Application(int value)
{
}

int Application::Start()
{
    width = 1080;
    height = 608;

    View.setSize(sf::Vector2f(width, height));
    View.setCenter(sf::Vector2f(0, 0));

    Window.create(sf::VideoMode(width, height), "SFML Application");
    Window.setFramerateLimit(100);
    Window.setView(View);
        
    Player.Start();
    Scene.Start("Scene1");

    while (Window.isOpen())
    {
        Update();
    }

    return 0;
}

void Application::Update()
{
    sf::Event event;
    while (Window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            Window.close();
    }

    /*if (Timer == 450) {
        std::cout << "Hello";
        ChangeScene("Scene2");
    }
    Timer++;*/

    // Clear the window
    Window.clear(sf::Color(10, 160, 210));

    // Draw and update Objects
    Scene.Update(Window);
    Player.Update(Window, View, width, height, Scene.Walls);

    // Display the window
    Window.display();
}

void Application::ChangeScene(std::string name)
{
    Scene.Start("Scene2");
}
