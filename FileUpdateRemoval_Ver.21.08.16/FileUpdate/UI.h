#ifndef UI_H_
#define UI_H_

#include <string>
#include <filesystem>
#include <iostream>
#include <memory>

using std::string;

class FileUpdateConsole
{
public:
	std::filesystem::path GetFrontRoot(void) const;
	std::filesystem::path GetBackupRoot(void) const;
	void SelectUserRoute(FileUpdateConsole& MainConsole);

private:
	void Initialize(FileUpdateConsole& MainConsole);
	void SetBackupRoot(void);
	void SetFrontRoot(void);
	std::filesystem::path FrontRoot;
	std::filesystem::path BackupRoot;
};

#endif