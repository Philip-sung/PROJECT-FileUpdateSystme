#include "Updator.h"
#include "UI.h"

void Updator::Traverse(std::filesystem::path p, FileUpdateConsole& MainConsole, size_t level = 0)
{
	if (!exists(p))
	{
		std::cout << "Front root path NOT exists.\n";
		return;
	}

	if (std::filesystem::is_regular_file(p)
		&& (p.generic_string()).find(" @") == string::npos
		)
	{
		GetCurrentFrontFile(p);
		bool IsBackupFileExists = GetCurrentBackupFile(p, MainConsole);
		if (IsBackupFileExists == true)
		{
			if (int Result = CheckRecentFile())
			{
				UpdateFileWithRecent(Result);
			}
			else if (CheckIfSizeSame())
			{
				std::cout << "No Update Needed\n";
			}
			else
			{
				std::cout << "**********EXCEPTION : Date is Same, Size is NOT Same**********\n";
			}
		}
		else if (IsBackupFileExists == false)
		{
			CopyFrontFile();
		}
	}
	else if (std::filesystem::is_directory(p)
		&& (p.generic_string()).find(" @") == string::npos
		&& (p.generic_string()).find("System Volume Information") == string::npos
		&& (p.generic_string()).find("RECYCLE.BIN") == string::npos
		)
	{
		GetCurrentFrontFile(p);
		bool IsBackupFileExists = GetCurrentBackupFile(p, MainConsole);
		if (IsBackupFileExists == true && p != MainConsole.GetFrontRoot())
		{
			if (int Result = CheckRecentFile())
				UpdateFileWithRecent(Result);
			else if (CheckIfSizeSame())
				std::cout << "No Update Needed\n";
			else
				std::cout << "**********EXCEPTION : Date is Same, Size is NOT Same**********\n";
		}
		else if (IsBackupFileExists == false && p != MainConsole.GetFrontRoot())
			CopyFrontFile();
		
		for (auto& entry : std::filesystem::directory_iterator(p))
		{
			Traverse(entry, MainConsole, level + 1);
		}
	}
}

bool Updator::GetCurrentFrontFile(std::filesystem::path p)
{
	string sFrontFilePath;
	sFrontFilePath = p.generic_string();
	CurrentFrontFilePath.assign(sFrontFilePath);
	CurrentFrontFile.assign(CurrentFrontFilePath);
	std::cout << "\nFront File  : " << sFrontFilePath << std::endl;

	return
		true;
}

bool Updator::GetCurrentBackupFile(std::filesystem::path p, FileUpdateConsole& MainConsole)	//To Get BackupRoot, FileUpdateConsole Needed.
{
	string sFrontFilePath;
	string sBackupFilePath;

	std::filesystem::path FrontRoot = MainConsole.GetFrontRoot();
	std::filesystem::path BackupRoot = MainConsole.GetBackupRoot();

	string sFrontRootPath = FrontRoot.generic_string();
	string sBackupRootPath = BackupRoot.generic_string();

	sFrontFilePath = p.generic_string();
	sBackupFilePath = sBackupRootPath + sFrontFilePath.substr(sFrontRootPath.size());
	std::cout << "Backup File : " << sBackupFilePath << std::endl;
	CurrentBackupFilePath.assign(sBackupFilePath);
	if (!exists(CurrentBackupFilePath))
	{
		std::cout << "BackupFile Not Exists, Copying File.\n";
		return false;
	}
	else if (exists(CurrentBackupFilePath))
	{
		CurrentBackupFile.assign(CurrentBackupFilePath);
		std::cout << "Updating Existing BackupFile.\n";
		return true;
	}
}

bool Updator::CheckIfSizeSame(void)
{
	std::cout << "Acquired Original File Size : " << CurrentFrontFile.file_size() << std::endl;
	std::cout << "Acquired Backup File Size : " << CurrentBackupFile.file_size() << std::endl;

	if (CurrentFrontFile.file_size() == CurrentBackupFile.file_size())
	{
		std::cout << "File Size Same\n";
		return true;
	}
	else
	{
		std::cout << "File Size Not Same\n";
		return false;
	}
}

int Updator::CheckRecentFile(void)
{
	std::filesystem::file_time_type CurrentFrontFileTimeData;
	CurrentFrontFileTimeData = CurrentFrontFile.last_write_time();
	std::filesystem::file_time_type CurrentBackupFileTimeData;
	CurrentBackupFileTimeData = CurrentBackupFile.last_write_time();

	if (CurrentBackupFileTimeData == CurrentFrontFileTimeData)
	{
		std::cout << "Modified Date identical.\n";
		return 0;
	}
	else if (CurrentBackupFileTimeData > CurrentFrontFileTimeData)
	{
		std::cout << "BackupFile is Recent Entry\n";
		return 1;
	}
	else if (CurrentBackupFileTimeData < CurrentFrontFileTimeData)
	{
		std::cout << "FrontFile is Recent Entry.\n";
		return 2;
	}
}

bool Updator::UpdateFileWithRecent(int CheckedResult)
{
	if (CheckedResult == 1)
	{
		std::cout << "BackupFile Remained.\n";
		return true;
	}

	if (CheckedResult == 2)
	{
		CopyFrontFile();
		std::cout << "Update Completed With FrontFile.\n";
		return true;
	}
}

bool Updator::CopyFrontFile(void)
{
	std::filesystem::copy(CurrentFrontFilePath, CurrentBackupFilePath, std::filesystem::copy_options::update_existing);
	return true;
}