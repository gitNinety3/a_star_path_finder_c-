#pragma once
#include <SFML/Graphics.hpp>
#include "NodeState.h"

/*
	The Node class should hold a RectangleShape called rect and a NodeState called state. The 
	rect object should be modified to visually represent what is going on in the program. It
	also holds information about it's current position in the window, size, color, etc.

	1)
	set_state(NodeState state) sets the state of the node and changes the color of the rectangle
	based on what state it is being changed to
*/

class Node
{
private:	
	
	sf::RectangleShape rect;	// Rectangle Associated with Node

	NodeState state;	// State of Node

	sf::Vector2i pos;	// Position of vector


public:
	Node* parent;
	
	float g;			// distance from this node to start position
	float h;			// distance from this node to distance position
	float f;			// sum of g and h

	// Constructor
	Node(sf::Vector2i pos = sf::Vector2i(0, 0), Node* parent = nullptr);

	// Calculators
	void calculate_h(sf::Vector2i distance);
	void calculate_f();

	// Setters
	void set_pos(sf::Vector2i pos);
	void set_state(NodeState state);
	void set_rect_color(sf::Color color);
	void set_rect_position(sf::Vector2f position);
	void set_rect_size(sf::Vector2f size);

	// Getters
	const sf::Vector2i get_pos();
	const NodeState get_state();
	const sf::Color get_rect_color();
	const sf::Vector2f get_rect_position();
	const sf::Vector2f get_rect_size();
	const sf::RectangleShape get_rectangle();
};

