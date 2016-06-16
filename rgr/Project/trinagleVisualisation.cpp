#include "stdafx.h"
#include "trinagleVisualisation.h"

void InitText(const sf::Font& font, NodeVisualisation& vNode, const sf::Vector2f& position)
{
	vNode.text.setFont(font);
	vNode.text.setString(std::to_string(vNode.value));
	vNode.text.setColor(sf::Color::Black);
	vNode.text.setPosition(position);
	vNode.text.setCharacterSize(25);
}

void InitializeNodesPosition(const std::vector<std::vector<Node>>& matrix, unsigned lineCount, const sf::Font& font)
{
	//std::this_thread::sleep_for(std::chrono::nanoseconds(10000000000));



	std::vector<NodeVisualisation> nodeVis;

	/*
	int rawCount = 0;
	for (size_t i = 0; i <= lineCount; i++)
	{
		int colomnCount = 0;
		for (size_t k = 0; k < i; k++)
		{
			NodeVisualisation vNode;
			vNode.value = matrix[i][k].value;
			vNode.startValue = matrix[i][k].startValue;
			vNode.previousCell = matrix[i][k].previousCell;
			InitText(font, vNode, sf::Vector2f(i * 25.f, k * 25.f));

			nodeVis.push_back(vNode);

			colomnCount++;
		}

		rawCount++;
	}
	*/

}
