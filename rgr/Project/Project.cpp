#include "stdafx.h"
#include "triangleAlgorithm.h"
#include "trinagleVisualisation.h"

void Render(sf::RenderWindow& window, const std::vector<NodeVisualisation>& nodeVis)
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::White);
		for (auto& node : nodeVis)
		{
			window.draw(node.text);
		}

		window.display();
	}
}

void Initialize(std::vector<NodeVisualisation>& nodeVis, std::vector<std::vector<Node>>& matrix, unsigned& lineCount, sf::Font& font)
{
	if (!font.loadFromFile("manteka.ttf"))
	{
		throw std::exception("Invalid font file");
	}
	std::ifstream fin("input.txt");
	fin >> lineCount;
	matrix = InitializeNodeMatrix(fin, lineCount);
	//InitializeNodesPosition(matrix, lineCount, font);
}

int main()
{
	sf::Font font;
	sf::RenderWindow window(sf::VideoMode(600, 600), "Triangle");
	std::vector<NodeVisualisation> nodeVis;
	std::vector<std::vector<Node>> matrix;
	unsigned lineCount;

	Initialize(nodeVis, matrix, lineCount, font);
	Render(window, nodeVis);

	return 0;
}