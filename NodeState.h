#pragma once
enum class NodeState
{
	open,			// WHITE
	wall,			// GREY
	start,			// CYAN
	destination,	// CYAN
	unvisited,		// RED
	visited,		// GREEN
	path,			// CYAN
};