#include "stdafx.h"
#include "Application.h"
#include "triangleAlgorithm.h"
#include "trinagleVisualisation.h"
#include "tinyfiledialogs.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	CApplication app;

	while (app.GetWindow().isOpen())
	{
		app.ProcessEvents();	
		app.Update();
		app.Render();
	}

	return 0;
}