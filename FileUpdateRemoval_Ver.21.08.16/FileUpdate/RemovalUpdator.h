#ifndef REMOVALUPDATOR_H_
#define REMOVALUPDATOR_H_

#include <filesystem>
#include <string>
#include <iostream>

class BackupFile;
class FileUpdateConsole;

using std::string;

class Updator
{
private:
	std::filesystem::path CurrentBackupFilePath;
	std::filesystem::path CurrentFrontFilePath;
	std::filesystem::directory_entry CurrentBackupFile;
	std::filesystem::directory_entry CurrentFrontFile;

public:
	void Traverse(std::filesystem::path p, FileUpdateConsole& MainConsole, size_t level);
	bool GetCurrentBackupFile(std::filesystem::path p);
	bool GetCurrentFrontFile(std::filesystem::path p, FileUpdateConsole& Console);
	bool CheckIfSizeSame(void);
	int CheckRecentFile(void);
	bool UpdateFileWithRecent(int);
	bool CopyBackupFile(void);
	bool RemoveBackupFile(void);
	bool RemoveBackupDirectory(void);

};

#endif