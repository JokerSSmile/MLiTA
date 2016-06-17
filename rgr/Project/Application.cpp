#include "stdafx.h"
#include "Application.h"
#include "triangleAlgorithm.h"
#include "trinagleVisualisation.h"

CApplication::CApplication()
{
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

void CApplication::Initialize()
{
	if (!m_font.loadFromFile("manteka.ttf"))
	{
		throw std::exception("Invalid font file");
	}
	m_lastUpdateTime = 0;
	m_lastUpdatetdPosition = Vector2u(0, 0);

	ifstream fin("input.txt");
	fin >> m_lineCount;

	m_matrix = InitializeNodeMatrix(fin, m_lineCount);
	m_nodeVis = InitTriangle(m_matrix, m_lineCount, m_font);

	if (!m_window.isOpen())
	{
		m_window.create(sf::VideoMode(m_lineCount * 100 + 50, m_lineCount * 100 + 50), "Triangle");
	}
	else
	{
		m_window.setSize(Vector2u(m_lineCount * 100 + 50, m_lineCount * 100 + 50));
	}
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
}

void CApplication::Update()
{
	m_time = static_cast<double>(m_clock.getElapsedTime().asMicroseconds());
	
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

void CApplication::Render()
{
	m_window.clear(sf::Color::White);

	for (auto& node : m_nodeVis)
	{
		m_window.draw(node.text);
	}

	m_window.display();
}

void CApplication::SaveResult()
{
	ofstream fout("output.txt");
	
}

sf::RenderWindow& CApplication::GetWindow()
{
	return m_window;
}
