#include "MainApp.h"

void MainApp::Init()
{
    _window.create(sf::VideoMode(800, 800), "SFML sorting visuialization!");

    // Create bars
    int bar_width = _window.getSize().x / _num_elements;
    for (int i = 0; i < _num_elements; i++) {
        int bar_height = _window.getSize().y * (i / _num_elements);
        Bar bar = Bar(bar_height, bar_height, i);
        bar.getRect()->setPosition(10, 10);

        _element_array.push_back(bar);
    }

    // Shuffle bars
    Shuffle();
    // Run sorting 
    Run();
}

void MainApp::Shuffle()
{

}

void MainApp::Run()
{
    while (_window.isOpen())
    {
        sf::Event event;
        while (_window.pollEvent(event))
        {
            HandleEvent(event);
        }

        // Step through sort
        Update();
        // Show bars
        Draw();
    }
}

void MainApp::HandleEvent(sf::Event event)
{
    if (event.type == sf::Event::Closed)
        Quit();
}

void MainApp::Update()
{

}

void MainApp::Draw()
{
    _window.clear(sf::Color::Blue);

    // Draw bars array
    for (int i = 0; i < _num_elements; i++) {
        _window.draw(sf::RectangleShape(*_element_array[i].getRect()));
    }

    _window.display();
}

void MainApp::Quit()
{
    _window.close();
}


