#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <thread>
#include <fstream>
#include <gtest/gtest.h>

using namespace std;
namespace fs = filesystem;

int f_amount = 0;
int l_amount = 0;
int el_amount = 0;
int nel_amount = 0;

void display_and_count(string path, int *f_amount, int *l_amount, int *el_amount, int *nel_amount)
{
	int files_amount = 0;
	int lines_amount = 0;
	int empty_lines_amount = 0;
	int non_empty_lines_amount = 0;
	string line;
	string f_name;

	for (const auto & name : fs::directory_iterator(path))
	{
		if (fs::is_regular_file(name))
		{
			cout << name << endl;
			files_amount++;
			f_name = name.path().string();
			ifstream file(f_name);
			while (getline(file, line))
			{
				lines_amount++;
				if (line.empty())
				{
					empty_lines_amount++;
				}
				else
				{
					non_empty_lines_amount++;
				}
			}

		}
	}
	cout << "The amount of files is: " << files_amount << endl;
	cout << "The amount of lines is: " << lines_amount << endl;
	cout << "The amount of empty lines is: " << empty_lines_amount << endl;
	cout << "The amount of lines that are not empty is: " << non_empty_lines_amount << endl;
	*f_amount = files_amount;
	*l_amount = lines_amount;
	*el_amount = empty_lines_amount;
	*nel_amount = non_empty_lines_amount;
}

TEST(MockFolderTest, FilesInMockFolder)
{
	int test_value = f_amount;
	EXPECT_EQ(1, test_value);
}

TEST(MockFolderTest, LinesInMockFolder)
{
	int test_value = f_amount;
	EXPECT_EQ(1, test_value);
}

TEST(MockFolderTest, EmptyLinesInMockFolder)
{
	int test_value = el_amount;
	EXPECT_EQ(4, test_value);
}

TEST(MockFolderTest, NonEmptyLinesInMockFolder)
{
	int test_value = nel_amount;
	EXPECT_EQ(5, test_value);
}



int main()
{
	string path;
	
	cout << "Insert path to directory:";
	cin >> path;
	if (!fs::exists(path))
	{
		cout << "There is no folder with this path";
	}
	else
	{
		display_and_count(path, &f_amount, &l_amount, &el_amount, &nel_amount);
	}
	testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}
