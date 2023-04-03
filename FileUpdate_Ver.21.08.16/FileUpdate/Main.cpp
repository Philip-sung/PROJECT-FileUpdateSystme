#include "UI.h"
#include "Updator.h"

int main(void)
{
	FileUpdateConsole MainConsole;
	Updator MainUpdator;

	MainConsole.SelectUserRoute(MainConsole);

	MainUpdator.Traverse(MainConsole.GetFrontRoot(), MainConsole, 0);

	std::cout << "\n*** Update Completed. ***\n";
	std::cin.get();

	return 0;
}