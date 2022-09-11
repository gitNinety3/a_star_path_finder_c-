#pragma once
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
#include "Node.h"
#include <iostream>
#include "SFML/Window/Mouse.hpp"


/*
	The grid class is designed to store a 2 dimensional vector of Node objects.
	It's member variables include the width and height of the window, the width
	and height of the grid, a pointer to the current window, and the 2D vector
	of Node objects.

	1)
	A Grid object should be constructed with a pointer to the window where the grid
	should be drawn on and the width and the height of the desired grid. The 2d
	vector of Nodes must first be constructed by resizing the vector to the desired
	width and height. Then, using the "init_grid()" function will fill the 2d vector with
	Node objects. Lastly, the "update_grid_layout()" function should be called to set the
	size and position of each of the Node objects.

	2)
	The resize(int width, int height) should be used to change the size of the grid whenever
	the user desires. It should retain information about the grid before and after the function
	is called. For example, if there is a Node with a NodeState == wall and it's position is 
	(10, 10) on the graph, when the grid is resized from being 14x14 to 20x20, that Node should
	still be (10, 10) on the grid after the resize.

	3)
	The update_grid_layout() function is in charge of resizing and handling the positions for
	each Node::Rectangle on the grid. the grid only needs to be updated when changes are made
	to it. Updating the grid every render cycle will slow down the program so stray away from
	doing multiple calls of the function consecutively if you don't need to.

	4)
	The draw_grid() function draws each Node in the grid onto the Window
*/

class Grid
{
private:
	std::vector< std::vector < Node* > > grid; // 2d vector of Nodes

	unsigned int w_width = 0,	// width of the open window
			w_height = 0,		// height of the open window
			grid_width = 0,		// width of grid
			grid_height = 0;	// height of grid

	sf::Vector2i start_pos = sf::Vector2i(-1,-1);			// position of the node that holds the NodeState::start (there can only be 1)
	sf::Vector2i destination_pos = sf::Vector2i(-1, -1);	// position of the node that holds the NodeState::destination (there can only be 1)

	bool running = false;	// Flag for if the best path is currently being looked for

	sf::RenderWindow* window;	// main window for the program

public:
	Grid(sf::RenderWindow* window, unsigned int grid_width, unsigned int grid_height);
	
	// init_grid() initializes the grid with new Node objects
	// calls update_grid_layout() to set the size and position of
	// the Node objects
	void init_grid();

	/* This function resizes the grid while maintaining
		the information held in the old grid, that way
		information about the NodeState for each Node
		object isn't lost.
	*/
	void resize(int width, int height);

	// USE UPDATE_GRID_LAYOUT BEFORE DRAWING GRID IF GRID WAS CHANGED
	void update_grid_layout();

	// USE UPDATE_GRID_LAYOUT BEFORE DRAWING GRID IF GRID WAS CHANGED
	void draw_grid();

	// calculate each node's s_cost, f_cost and t_cost
	void calculate_all_h_cost();

	// check if the destination_pos and start_pos are within the bounds of the grid
	void fix_dest_start_positions();

	// A* Algorithm for finding the fastest path between the start_pos and destination_pos
	void run_a_star();

	// Sets all of the nodes in the path to NodeState::path
	void draw_path(std::stack<sf::Vector2i> path);

	// clear the grid
	void clear_grid();

	// Setters
	void set_node_state(sf::Vector2i pos, NodeState state);

	// Getters
	const bool is_running();
	const int get_width();
	const int get_height();
	const int get_rect_width();
	const int get_rect_height();
    const NodeState get_node_state(sf::Vector2i pos);
	const sf::Vector2i get_mouse_pos_in_grid(sf::Vector2i mouse_pos);

};
