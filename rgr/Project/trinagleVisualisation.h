#pragma once
#include "triangleAlgorithm.h"

class NodeVisualisation : public Node
{
public:
	sf::Text text;
};

void InitializeNodesPosition(const std::vector<std::vector<Node> >& matrix, unsigned lineCount, const sf::Font& font);