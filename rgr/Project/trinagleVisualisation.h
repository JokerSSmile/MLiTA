#pragma once
#include "triangleAlgorithm.h"

enum class AlgorithmStage
{
	FIND_MAX,
	SHOW_PATH
};

struct NodeVisualisation : public Node
{
	Vector2u position;
	Text text;
};

std::vector<NodeVisualisation> InitTriangle(std::vector<std::vector<Node>>& matrix, unsigned lineCount, const Font& font);

void UpdateTriangleParts(std::vector<NodeVisualisation>& nodeVis, const std::vector<std::vector<Node>>& matrix, unsigned lineCount);
