#pragma once

class UserIntreface
{
public:

	enum class uiState
	{
		MENU,
		START_HANDLER,
		HELP_HANDLER
	};

	UserIntreface(RenderWindow& window);
	~UserIntreface();

	void Initialize(const Font& font, const Vector2u& windowSize);
	void Draw(RenderWindow& window);
	void DrawHelp(RenderWindow& window);
	int Update(RenderWindow& window);

private:

	Text m_startText;
	Text m_helpText;
	Text m_back;
	Text m_info;

};

