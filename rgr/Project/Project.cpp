#include "stdafx.h"
#include "Application.h"
#include "triangleAlgorithm.h"
#include "trinagleVisualisation.h"
#include "tinyfiledialogs.h"

int main()
{
	CApplication app;

	while (app.GetWindow().isOpen())
	{
		app.ProcessEvents();
		if (app.m_state == AppState::DO_ALGORITHM)
		{
			app.Update();
			app.Render();
		}
	}

	return 0;
}