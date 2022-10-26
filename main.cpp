#include <SFML/Graphics.hpp>
#include "Grid.h"
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include <thread>
#include <SFML/Audio.hpp>
#include <string>


int main()
{
	NodeState brushState = NodeState::open;
	sf::RenderWindow window(sf::VideoMode(500, 500), "Path Finder", sf::Style::Close);
    
    

     sf::Music music;
     
     if (!music.openFromFile("../../../res/RSL_120_synth_bass_ukg_organ_filter_Gm.wav"))
     {
        std::cout << "Error with the music file!" << std::endl;
     }
     
    music.play(); // plays music
    music.setLoop(true); // new changes
    
    
    
      std::string file_name = "../../../res/startsound.wav";
      
      sf::SoundBuffer buffer;
      buffer.loadFromFile(file_name);
       
      sf::Sound sound;
       
      sound.setBuffer(buffer);

    
	Grid grid(&window, 20, 20);
	window.setVerticalSyncEnabled(true);
	window.setKeyRepeatEnabled(false);
	std::thread t1;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Event for if the window is closed
			if(event.type == sf::Event::Closed)
				window.close();

			// Event for if the window is resized
			if(event.type == sf::Event::Resized)
			{
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}

			// Event for KeyPressed
			if(event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{

				case(sf::Keyboard::X): // X: Open

					brushState = NodeState::open;
					break;

				case(sf::Keyboard::W): // W: Wall

					brushState = NodeState::wall;
					break;

				case(sf::Keyboard::S): // S: Start

					brushState = NodeState::start;
					break;

				case(sf::Keyboard::D): // D: Destination

					brushState = NodeState::destination;
					break;


				case(sf::Keyboard::Down): // Down arrow: Make grid larger vertically (limit at 20

					// Upper Bounderies for y component
					if (grid.get_height() + 1 <= 100)
					{
						grid.resize(grid.get_width(), grid.get_height() + 1);
						window.setSize(sf::Vector2u(window.getSize().x, window.getSize().y + grid.get_rect_height()));
					}
					break;

				case(sf::Keyboard::Up): // Up arrow: Make grid smaller vertically (limit at 5)

					// Lower Bounderies for y component
					if (grid.get_height() - 1 >= 5)
					{
						grid.resize(grid.get_width(), grid.get_height() - 1);
						window.setSize(sf::Vector2u(window.getSize().x, window.getSize().y - grid.get_rect_height()));
					}

					break;
				case(sf::Keyboard::Right): // Right arrow: Make grid larger horizontally (limit at 30)

					// Upper Bounderies for x component
					if (grid.get_width() + 1 <= 100)
					{
						grid.resize(grid.get_width() + 1, grid.get_height());
						window.setSize(sf::Vector2u(window.getSize().x + grid.get_rect_width(), window.getSize().y));
					}

					break;
				case(sf::Keyboard::Left): // Left arrow: Make grid smaller horizontally (limit at 5)

					// Lower Bounderies for x component
					if (grid.get_width() - 1 >= 5)
					{
						grid.resize(grid.get_width() - 1, grid.get_height());
						window.setSize(sf::Vector2u(window.getSize().x - grid.get_rect_width(), window.getSize().y));
					}
					break;

				case(sf::Keyboard::Enter): // Enter/Return: start the program
					t1 = std::thread(&Grid::run_a_star, &grid);
					t1.detach();
					break;

				case(sf::Keyboard::C):
					grid.clear_grid();
					break;

				case(sf::Keyboard::I):
					grid.init_grid();
					break;
				}
			}

			// Set up
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !grid.is_running())
			{

				if (sf::Mouse::getPosition(window).x <= window.getSize().x && sf::Mouse::getPosition(window).y <= window.getSize().y)
				{
                    
					sf::Vector2i mouse_pos = grid.get_mouse_pos_in_grid(sf::Mouse::getPosition(window));
					int x = mouse_pos.x;
					int y = mouse_pos.y;
					grid.set_node_state(sf::Vector2i(x, y), brushState);
                    if(brushState == NodeState::wall) sound.play();
				}

			}

			
		}

		window.clear();
		grid.draw_grid();
		window.display();
	}

	return 0;

}
