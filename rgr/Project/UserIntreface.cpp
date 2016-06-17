#include "stdafx.h"
#include "UserIntreface.h"


UserIntreface::UserIntreface(RenderWindow& window)
{
	window.setSize(Vector2u(400, 400));
}

void UserIntreface::Initialize(const Font& font, const Vector2u& windowSize)
{
	setlocale(LC_ALL, "Russian");
	string infoStr({ "Triangle\n"
		"\n"
		"Find the greatest amount of numbers,\n"
		"located on the way from the top point of\n"
		"the triangle to the base.\n"
		"Each step in the path occurs in a direction\n"
		"diagonally downward (to the left or right). Number of\n"
		"rows in the triangle from 1 to 100. The triangle\n"
		"is composed of integers from 0 to 99.\n"
		"Input from INPUT.TXT.First file number determines the\n"
		"number N of rows of the triangle\n"
		"Output in the first line of the file OUTPUT.TXT. In\n"
		"output a single number - the largest\n"
		"summ.In the second line are given through the gap\n"
		"of the triangle from the top to the bottom,\n"
		"giving greatest summ. If several solutions, output any of them." });

	m_startText.setFont(font);
	m_startText.setCharacterSize(30);
	m_startText.setString("Open file");
	m_startText.setColor(Color::Black);
	m_startText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
	m_startText.setOrigin(m_startText.getLocalBounds().width / 2, m_startText.getGlobalBounds().height / 2 + 100);

	m_helpText.setFont(font);
	m_helpText.setCharacterSize(30);
	m_helpText.setString("Help");
	m_helpText.setColor(Color::Black);
	m_helpText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
	m_helpText.setOrigin(m_helpText.getLocalBounds().width / 2, m_helpText.getGlobalBounds().height / 2 - 100);

	m_info.setFont(font);
	m_info.setCharacterSize(10);
	m_info.setString(infoStr);
	m_info.setColor(Color::Black);
	m_info.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
	m_info.setOrigin(m_info.getLocalBounds().width / 2, m_info.getGlobalBounds().height / 2);

	m_back.setFont(font);
	m_back.setCharacterSize(30);
	m_back.setString("Back");
	m_back.setColor(Color::Black);
	m_back.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
	m_back.setOrigin(m_back.getLocalBounds().width / 2, m_back.getGlobalBounds().height / 2 - 150);


}

UserIntreface::~UserIntreface()
{

}

void UserIntreface::Draw(RenderWindow& window)
{
	window.draw(m_startText);
	//window.draw(m_helpText);
}

void UserIntreface::DrawHelp(RenderWindow& window)
{
	window.draw(m_info);
	window.draw(m_back);
}

int UserIntreface::Update(RenderWindow& window)
{
	if (m_startText.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
	{
		m_startText.setColor(Color(70, 70, 70));
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			return static_cast<int>(uiState::START_HANDLER);
		}
	}
	else
	{
		m_startText.setColor(Color::Black);
	}

	/*
	if (m_helpText.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
	{
		m_helpText.setColor(Color(70, 70, 70));
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			return static_cast<int>(uiState::HELP_HANDLER);
		}
	}
	else
	{
		m_helpText.setColor(Color::Black);
	}

	if (m_back.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
	{
		m_back.setColor(Color(70, 70, 70));
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			return static_cast<int>(uiState::MENU);
		}
	}
	else
	{
		m_back.setColor(Color::Black);
	}
	*/
}
