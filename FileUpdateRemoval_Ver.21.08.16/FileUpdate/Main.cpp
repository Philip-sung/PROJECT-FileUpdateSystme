#include "UI.h"
#include "RemovalUpdator.h"

int main(void)
{
	FileUpdateConsole MainConsole;
	Updator MainUpdator;

	MainConsole.SelectUserRoute(MainConsole);

	MainUpdator.Traverse(MainConsole.GetBackupRoot(), MainConsole, 0);

	std::cout << "\n*** Update Completed. ***\n";
	std::cin.get();

	return 0;
}