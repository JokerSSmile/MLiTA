#include "stdafx.h"
#include "Application.h"
#include "triangleAlgorithm.h"
#include "trinagleVisualisation.h"
#include "tinyfiledialogs.h"

int main()
{
	CApplication app;

	const char *filters[] = { "*.txt" };
	char const *result = tinyfd_openFileDialog("Select input file", "", 1, filters, "", false);

	while (app.GetWindow().isOpen())
	{
		
		app.ProcessEvents();
		app.Update();
		app.Render();	
	}

	return 0;
}