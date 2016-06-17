#pragma once

#include "triangleAlgorithm.h"
#include "trinagleVisualisation.h"

static const double TRIANGLE_UPDATE_TIME = 300000;

class CApplication
{
public:
	CApplication();
	~CApplication();

	void ProcessEvents();
	void Initialize();
	void Render();
	void SetColor(const Vector2u& previousPosition);
	void UpdateFindingPath();
	void UpdateShowPath();
	void Update();
	void SaveResult();
	sf::RenderWindow& GetWindow();

private:

	Clock m_clock;
	unsigned m_lineCount;
	double m_time;
	double m_lastUpdateTime;
	Vector2u m_lastUpdatetdPosition;
	AlgorithmStage m_algorithmStage;
	ostringstream m_outputResult;

	sf::RenderWindow m_window;
	Font m_font;

	std::vector<std::vector<Node>> m_matrix;
	std::vector<NodeVisualisation> m_nodeVis;
};
