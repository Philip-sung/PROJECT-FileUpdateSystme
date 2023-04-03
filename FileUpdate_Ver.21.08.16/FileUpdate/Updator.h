#ifndef UPDATOR_H_
#define UPDATOR_H_

#include <filesystem>
#include <string>
#include <iostream>

class FrontFile;
class FileUpdateConsole;

using std::string;

class Updator
{
private:
	std::filesystem::path CurrentFrontFilePath;
	std::filesystem::path CurrentBackupFilePath;
	std::filesystem::directory_entry CurrentFrontFile;
	std::filesystem::directory_entry CurrentBackupFile;

public:
	void Traverse(std::filesystem::path p, FileUpdateConsole& MainConsole, size_t level);
	bool GetCurrentFrontFile(std::filesystem::path p);
	bool GetCurrentBackupFile(std::filesystem::path p, FileUpdateConsole& Console);
	bool CheckIfSizeSame(void);
	int CheckRecentFile(void);
	bool UpdateFileWithRecent(int);
	bool CopyFrontFile(void);

};

#endif