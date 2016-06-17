#include "stdafx.h"
#include "Application.h"
#include "triangleAlgorithm.h"
#include "trinagleVisualisation.h"
#include "tinyfiledialogs.h"
#include "UserIntreface.h"

CApplication::CApplication()
	:m_window(sf::VideoMode(400, 400), "Triangle"),
	m_ui(m_window)
{
	m_state = AppState::MENU;
	if (!m_font.loadFromFile("manteka.ttf"))
	{
		throw std::exception("Invalid font file");
	}

	Initialize();
}

CApplication::~CApplication()
{

}

void CApplication::ProcessEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
	}
}

bool CApplication::GetInputFile(ifstream& fin)
{
	const char *filters[] = { "*.txt" };
	char const *result = tinyfd_openFileDialog("Select input file", "", 1, filters, "", false);
	if (result == nullptr)
	{
		return false;
	}
	fin.open(result);
	if (!fin.is_open())
	{
		tinyfd_messageBox("Error", "I/O error when reading input file", "ok", "error", 1);
		return false;
	}
	m_state = AppState::DO_ALGORITHM;
	return true;
}

void CApplication::InitializeFromInputDate(ifstream& fin)
{
	fin >> m_lineCount;

	m_matrix = InitializeNodeMatrix(fin, m_lineCount);
	m_nodeVis = InitTriangle(m_matrix, m_lineCount, m_font);

	if (m_lineCount != 0)
	{
		m_window.setSize(Vector2u(m_lineCount * SHIFT_BETWEEN_TRIANGLE_NODES + 50, m_lineCount * SHIFT_BETWEEN_TRIANGLE_NODES + 50));
	}

	m_ui.Initialize(m_font, m_window.getSize());

}

void CApplication::Initialize()
{

	m_lastUpdateTime = 0;
	m_lastUpdatetdPosition = Vector2u(0, 0);
	m_state = AppState::MENU;

	m_ui.Initialize(m_font, m_window.getSize());

}

void CApplication::SetColor(const Vector2u& previousPosition)
{
	for (auto& node : m_nodeVis)
	{
		if (node.position == m_lastUpdatetdPosition)
		{
			node.text.setColor(Color::Blue);
		}
		else if (node.position == previousPosition)
		{
			node.text.setColor(Color::Cyan);
		}
		else
		{
			node.text.setColor(Color::Black);
		}
	}
}

void CApplication::UpdateFindingPath()
{
	Vector2u previousPosition;
	if (m_time > m_lastUpdateTime + TRIANGLE_UPDATE_TIME)
	{
		while (m_lastUpdatetdPosition.x <= m_lineCount)
		{
			while (m_lastUpdatetdPosition.y < m_lastUpdatetdPosition.x)
			{
				previousPosition = CalculatePathWithMaxWeight(m_matrix, m_lineCount, m_lastUpdatetdPosition);
				SetColor(previousPosition);

				m_lastUpdatetdPosition.y += 1;
				m_lastUpdateTime = m_time;
				break;
			}
			if (m_lastUpdatetdPosition.y == m_lastUpdatetdPosition.x)
			{
				m_lastUpdatetdPosition.x += 1;
				m_lastUpdatetdPosition.y = 0;
			}
			break;
		}
	}

	if (m_lastUpdatetdPosition.x > m_lineCount)
	{
		SetColor({0, 0});
		m_lastUpdatetdPosition = FindMaxValuePosition(m_matrix, m_lineCount);
		m_outputResult << m_matrix[m_lastUpdatetdPosition.x][m_lastUpdatetdPosition.y].value << endl;

		m_algorithmStage = AlgorithmStage::SHOW_PATH;
	}

	UpdateTriangleParts(m_nodeVis, m_matrix, m_lineCount);
}

void CApplication::UpdateShowPath()
{
	if (m_lastUpdatetdPosition.x != 0)
	{
		if (m_time > m_lastUpdateTime + TRIANGLE_UPDATE_TIME)
		{
			for (auto& node : m_nodeVis)
			{
				if (node.position == m_lastUpdatetdPosition)
				{
					node.text.setColor(Color::Red);
				}
			}

			m_outputResult << m_matrix[m_lastUpdatetdPosition.x][m_lastUpdatetdPosition.y].startValue << " ";
			m_lastUpdatetdPosition = m_matrix[m_lastUpdatetdPosition.x][m_lastUpdatetdPosition.y].previousCell;
			
			m_lastUpdateTime = m_time;
		}
	}
	else
	{
		m_algorithmStage = AlgorithmStage::FIND_MAX;
		m_state = AppState::OUTPUT_RESULT;
	}
}

void CApplication::Update()
{
	m_time = static_cast<double>(m_clock.getElapsedTime().asMicroseconds());
	
	if (m_state == AppState::MENU || m_state == AppState::HELP)
	{
		switch (m_ui.Update(m_window))
		{
		case 1:
			m_state = AppState::GET_INPUT_FILE;
			break;
		case 2:
			m_state = AppState::HELP;
			break;
		case 0:
			m_state = AppState::MENU;
		default:
			break;
		};
	}
	else if (m_state == AppState::GET_INPUT_FILE)
	{
		ifstream fin;
		GetInputFile(fin);
		InitializeFromInputDate(fin);
		m_state = AppState::DO_ALGORITHM;
	}
	else if (m_state == AppState::DO_ALGORITHM)
	{
		switch (m_algorithmStage)
		{
		case AlgorithmStage::FIND_MAX:
			UpdateFindingPath();
			break;
		case AlgorithmStage::SHOW_PATH:
			UpdateShowPath();
			break;
		default:
			break;
		}
	}
	else if (m_state == AppState::OUTPUT_RESULT)
	{
		SaveResult();
		Initialize();

		m_state = AppState::MENU;
	}
	
}

void CApplication::Render()
{
	m_window.clear(sf::Color::White);

	if (m_state == AppState::DO_ALGORITHM || m_state == AppState::OUTPUT_RESULT)
	{
		for (auto& node : m_nodeVis)
		{
			m_window.draw(node.text);
		}
	}

	if (m_state == AppState::MENU)
	{
		m_ui.Draw(m_window);
	}
	else if (m_state == AppState::HELP)
	{
		m_ui.DrawHelp(m_window);
	}

	m_window.display();
}

bool CApplication::SaveResult()
{
	const char *filters[] = { "*.txt" };
	char const *result = tinyfd_openFileDialog("Select output file", "", 1, filters, "", false);
	if (result == nullptr)
	{
		return false;
	}

	std::ofstream fout(result);
	fout << m_outputResult.str();
	return true;
}

sf::RenderWindow& CApplication::GetWindow()
{
	return m_window;
}
