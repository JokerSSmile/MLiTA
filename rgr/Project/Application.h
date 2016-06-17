#pragma once

#include "triangleAlgorithm.h"
#include "trinagleVisualisation.h"

static const double TRIANGLE_UPDATE_TIME = 500000;
static const unsigned SHIFT_BETWEEN_TRIANGLE_NODES = 100;

enum class AppState
{
	GET_INPUT_FILE,
	DO_ALGORITHM,
	OUTPUT_RESULT,
};

class CApplication
{
public:
	CApplication();
	~CApplication();

	void ProcessEvents();
	void Initialize(ifstream& fin);
	bool GetInputFile(ifstream& fin);
	void Render();
	void SetColor(const Vector2u& previousPosition);
	void UpdateFindingPath();
	void UpdateShowPath();
	void Update();
	bool SaveResult();
	sf::RenderWindow& GetWindow();

	AppState m_state;

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
