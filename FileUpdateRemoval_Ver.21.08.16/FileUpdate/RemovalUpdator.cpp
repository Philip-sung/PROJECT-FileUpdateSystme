#include "RemovalUpdator.h"
#include "UI.h"

void Updator::Traverse(std::filesystem::path p, FileUpdateConsole& MainConsole, size_t level = 0)
{
	if (!exists(p))
	{
		std::cout << "Backup root path NOT exists.\n";
		return;
	}

	if (std::filesystem::is_regular_file(p))
	{
		GetCurrentBackupFile(p);
		bool IsFrontFileExists = GetCurrentFrontFile(p, MainConsole);
		if (IsFrontFileExists == true)
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
		else if (IsFrontFileExists == false)
		{
			RemoveBackupFile();
		}
	}
	else if (std::filesystem::is_directory(p) 
		&& (p.generic_string()).find(" @") == string::npos 
		&& (p.generic_string()).find("System Volume Information") == string::npos
		&& (p.generic_string()).find("RECYCLE.BIN") == string::npos
		)
	{
		GetCurrentBackupFile(p);
		bool IsFrontFileExists = GetCurrentFrontFile(p, MainConsole);
		if (IsFrontFileExists == true)
		{
			if (int Result = CheckRecentFile())
				std::cout << "Directory Doesn't Need Update\n";
			else if (CheckIfSizeSame())
				std::cout << "Directory Doesn't Need Update\n";
			else
				std::cout << "**********EXCEPTION : Date is Same, Size is NOT Same**********\n";
		}
		else if (IsFrontFileExists == false)
			RemoveBackupDirectory();

		if (IsFrontFileExists)
		{
			for (auto& entry : std::filesystem::directory_iterator(p))
			{
				Traverse(entry, MainConsole, level + 1);
			}
		}
	}
}

bool Updator::GetCurrentBackupFile(std::filesystem::path p)
{
	string sBackupFilePath;
	sBackupFilePath = p.generic_string();
	CurrentBackupFilePath.assign(sBackupFilePath);
	CurrentBackupFile.assign(CurrentBackupFilePath);
	std::cout << "\nBackup File : " << sBackupFilePath << std::endl;

	return
		true;
}

bool Updator::GetCurrentFrontFile(std::filesystem::path p, FileUpdateConsole& MainConsole)	//To Get FrontRoot, FileUpdateConsole Needed.
{
	string sBackupFilePath;
	string sFrontFilePath;

	std::filesystem::path BackupRoot = MainConsole.GetBackupRoot();
	std::filesystem::path FrontRoot = MainConsole.GetFrontRoot();

	string sBackupRootPath = BackupRoot.generic_string();
	string sFrontRootPath = FrontRoot.generic_string();

	sBackupFilePath = p.generic_string();
	sFrontFilePath = sFrontRootPath + sBackupFilePath.substr(sBackupRootPath.size());
	std::cout << "Front File  : " << sFrontFilePath << std::endl;
	CurrentFrontFilePath.assign(sFrontFilePath);
	
	if (!exists(CurrentFrontFilePath))
	{
		std::cout << "FrontFile Not Exists, Deleting BackupFile.\n";
		return false;
	}
	else if (exists(CurrentFrontFilePath))
	{
		CurrentFrontFile.assign(CurrentFrontFilePath);
		std::cout << "Updating Existing FrontFile.\n";
		return true;
	}
}

bool Updator::CheckIfSizeSame(void)
{
	std::cout << "Acquired Original File Size : " << CurrentBackupFile.file_size() << std::endl;
	std::cout << "Acquired Front File Size : " << CurrentFrontFile.file_size() << std::endl;

	if (CurrentBackupFile.file_size() == CurrentFrontFile.file_size())
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
	std::filesystem::file_time_type CurrentBackupFileTimeData;
	CurrentBackupFileTimeData = CurrentBackupFile.last_write_time();
	std::filesystem::file_time_type CurrentFrontFileTimeData;
	CurrentFrontFileTimeData = CurrentFrontFile.last_write_time();

	if (CurrentFrontFileTimeData == CurrentBackupFileTimeData)
	{
		std::cout << "Modified Date identical.\n";
		return 0;
	}
	else if (CurrentFrontFileTimeData > CurrentBackupFileTimeData)
	{
		std::cout << "FrontFile is Recent Entry\n";
		return 1;
	}
	else if (CurrentFrontFileTimeData < CurrentBackupFileTimeData)
	{
		std::cout << "BackupFile is Recent Entry.\n";
		return 2;
	}
}

bool Updator::UpdateFileWithRecent(int CheckedResult)
{
	if (CheckedResult == 1)
	{
		std::cout << "FrontFile Remained.\n";
		return true;
	}

	if (CheckedResult == 2)
	{
		CopyBackupFile();
		std::cout << "Update Completed With BackupFile.\n";
		return true;
	}
}

bool Updator::CopyBackupFile(void)
{
	std::filesystem::copy(CurrentBackupFilePath, CurrentFrontFilePath, std::filesystem::copy_options::update_existing);
	return true;
}

bool Updator::RemoveBackupFile(void)
{
	std::filesystem::remove(CurrentBackupFilePath);
	return true;
}

bool Updator::RemoveBackupDirectory(void)
{
	std::filesystem::remove_all(CurrentBackupFilePath);
	return true;
}