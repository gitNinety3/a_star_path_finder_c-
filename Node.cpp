#pragma once
#include <iostream>
#include <cmath>
#include "Node.h"

// Constructor
Node::Node(sf::Vector2i pos, Node* parent)
{
	this->parent = parent;
	this->pos = pos;
	rect.setOutlineColor(sf::Color::Black);
	rect.setOutlineThickness(1.6f);
	set_state(NodeState::open);
	g = 0;
	h = 0;
	f = 0;
}

// Calculators
void Node::calculate_h(sf::Vector2i destination)
{
	// the deltas are the distances between the respective coordinate
	float delta_x = destination.x - pos.x;
	float delta_y = destination.y - pos.y;

	h = std::sqrt((delta_x * delta_x) + (delta_y * delta_y));
}

void Node::calculate_f()
{
	f = g + h;
}


void Node::set_pos(sf::Vector2i pos)
{
	this->pos = pos;
}

// Setters
void Node::set_state(NodeState state)
{
	this->state = state;
	switch (state)
	{
	case NodeState::open:
		rect.setFillColor(sf::Color::White);			// set rect to white
		break;
	case NodeState::wall:
		rect.setFillColor(sf::Color(30, 30, 30));		// set rect to dark grey
		break;
	case NodeState::start:
		rect.setFillColor(sf::Color::Cyan);				// set rect to cyan
		break;
	case NodeState::destination:
		rect.setFillColor(sf::Color::Cyan);			// set rect to yellow
		break;
	case NodeState::path:
		rect.setFillColor(sf::Color::Cyan);			// set rect to green
		break;
	case NodeState::visited:
		rect.setFillColor(sf::Color::Red);
		break;
	case NodeState::unvisited:
		rect.setFillColor(sf::Color::Green);
		break;
	}
}

void Node::set_rect_color(sf::Color color)
{
	rect.setFillColor(color);
}

void Node::set_rect_position(sf::Vector2f position)
{
	rect.setPosition(position);
}

void Node::set_rect_size(sf::Vector2f size)
{
	rect.setSize(size);
}

const sf::Vector2i Node::get_pos()
{
	return pos;
}

// Getters
const NodeState Node::get_state()
{
	return state;
}

const sf::Color Node::get_rect_color()
{
	return rect.getFillColor();
}

const sf::Vector2f Node::get_rect_position()
{
	return rect.getPosition();
}

const sf::Vector2f Node::get_rect_size()
{
	return rect.getSize();
}

const sf::RectangleShape Node::get_rectangle()
{
	return rect;
}
