#include "UI.h"

void FileUpdateConsole::Initialize(FileUpdateConsole& MainConsole)
{
	MainConsole.FrontRoot.assign("\0");
	MainConsole.BackupRoot.assign("\0");
	std::cout << "\nConsole Initialized Successfully.\n";
}

void FileUpdateConsole::SetBackupRoot(void)
{
	string RootLocation;
	std::cout << "Select Backup Root Directory : ";
	std::getline(std::cin, RootLocation);
	BackupRoot.assign(RootLocation);

}

void FileUpdateConsole::SetFrontRoot(void)
{
	string RootLocation;
	std::cout << "Select Front Root Directory  : ";
	std::getline(std::cin, RootLocation);
	FrontRoot.assign(RootLocation);
}

std::filesystem::path FileUpdateConsole::GetBackupRoot(void) const
{
	return BackupRoot;
}

std::filesystem::path FileUpdateConsole::GetFrontRoot(void) const
{
	return FrontRoot;
}

void FileUpdateConsole::SelectUserRoute(FileUpdateConsole& MainConsole)
{
	using namespace std::string_literals;
	string Answer;

	do
	{
		MainConsole.Initialize(MainConsole);
		MainConsole.SetFrontRoot();
		MainConsole.SetBackupRoot();
		std::cout << "Selected Front Root is  **  " << (MainConsole.GetFrontRoot()).generic_string() << "  **" << std::endl;
		std::cout << "Selected Backup Root is **  " << (MainConsole.GetBackupRoot()).generic_string() << "  **" << std::endl;
		std::cout << "Are you really want to continue with selected Root? (Y/N)\n";
		getline(std::cin, Answer);
		if (Answer == "Y"s)
			std::cout << "Commited.\n";
		else if (Answer == "N"s)
		{
			std::cout << "Reselect Roots.\n";
		}
		else
		{
			std::cout << "Unexpected Commands.\n";
		}
	} while (Answer != "Y"s);

	return;
}