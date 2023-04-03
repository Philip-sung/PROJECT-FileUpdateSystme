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
	std::filesystem::path GetBackupRoot(void) const;
	std::filesystem::path GetFrontRoot(void) const;
	void SelectUserRoute(FileUpdateConsole& MainConsole);

private:
	void Initialize(FileUpdateConsole& MainConsole);
	void SetFrontRoot(void);
	void SetBackupRoot(void);
	std::filesystem::path BackupRoot;
	std::filesystem::path FrontRoot;
};

#endif