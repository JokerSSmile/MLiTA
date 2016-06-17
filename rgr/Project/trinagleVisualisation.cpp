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

std::vector<NodeVisualisation> InitTriangle(std::vector<std::vector<Node>>& matrix, unsigned lineCount, const Font& font)
{
	std::vector<NodeVisualisation> vecNodes;
	for (size_t i = 0; i <= lineCount; i++)
	{
		for (size_t k = 0; k < i; k++)
		{
			NodeVisualisation vNode;
			vNode.value = matrix[i][k].value;
			vNode.startValue = matrix[i][k].startValue;
			vNode.previousCell = matrix[i][k].previousCell;
			vNode.position = { i, k };

			InitText(font, vNode, sf::Vector2f(k  * 100.f + 50, i  * 100.f - 50));

			vecNodes.push_back(vNode);
		}
	}

	return vecNodes;
}

void UpdateTriangleParts(std::vector<NodeVisualisation>& nodeVis, const std::vector<std::vector<Node>>& matrix, unsigned lineCount)
{
	size_t elementCount = 0;
	for (size_t i = 0; i <= lineCount; i++)
	{
		for (size_t k = 0; k < i; k++)
		{
			nodeVis[elementCount].text.setString(std::to_string(matrix[i][k].value));
			elementCount++;
		}
	}
}
