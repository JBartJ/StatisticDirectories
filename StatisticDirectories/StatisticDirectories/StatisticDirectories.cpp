#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <string.h>
#include <thread>
#include <fstream>
#include <gtest/gtest.h>

using namespace std;
namespace fs = filesystem;

int f_amount;
int l_amount;
int el_amount;
int nel_amount;
int w_amount;
int lt_amount;

void count_files(string path, int* f_amount)
{
	int files_amount = 0;

		for (const auto& name : fs::directory_iterator(path))
		{
			if (fs::is_regular_file(name))
			{
				cout << name << endl;
				files_amount++;
			}
		}

		cout << "The amount of files is: " << files_amount << endl;
		cout << endl;
		*f_amount = files_amount;
}

void count_stats(string path, int* i, int* l_amount, int* el_amount, int* nel_amount, int* w_amount, int* lt_amount)
{
	int file_number=0;
	int lines_amount = 0;
	int empty_lines_amount = 0;
	int non_empty_lines_amount = 0;
	int words_amount = 0;
	int letters_amount = 0;
	char w[1000];
	string line;
	string word;
	string f_name;

	for (const auto & name : fs::directory_iterator(path))
	{

		if (fs::is_regular_file(name))
		{
			if (file_number == *i)
			{
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
						stringstream ls(line);
						while (getline(ls, word, ' '))
						{
							words_amount++;
						}
							for (int i = 0; i < line.length(); i++)
							{
							w[i] = line.at(i);
								if (isalpha((unsigned char)w[i]))
								{
								letters_amount++;
								}
							}
					}
				}
			}
			file_number++;
		}
	}
	cout << "The amount of lines in this file is: " << lines_amount << endl;
	cout << "The amount of empty lines in this file is: " << empty_lines_amount << endl;
	cout << "The amount of lines that are not empty in this file is: " << non_empty_lines_amount << endl;
	cout << "The amount of words in this file is: " << words_amount << endl;
	cout << "The amount of letters in this file is:" << letters_amount << endl;
	cout << endl;
	*l_amount += lines_amount;
	*el_amount += empty_lines_amount;
	*nel_amount += non_empty_lines_amount;
	*w_amount += words_amount;
	*lt_amount += letters_amount;
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

TEST(MockFolderTest, WordsInMockFolder)
{
	int test_value = w_amount;
	EXPECT_EQ(99, test_value);
}

TEST(MockFolderTest, LettersInMockFolder)
{
	int test_value = lt_amount;
	EXPECT_EQ(497, test_value);
}



int main()
{
	string path;
	thread* t[50];

	cout << "Insert path to directory:";
	cin >> path;
		if (!fs::exists(path))
		{
		cout << "There is no folder with this path";
		}
		else
		{
		count_files(path, &f_amount);
			for (int i=0; i < f_amount; i++)
			{
			t[i] = new thread(count_stats, path, &i, &l_amount, &el_amount, &nel_amount, &w_amount, &lt_amount);
			t[i]->join();
			}
		}
	cout << "The total amount of lines is: " << l_amount << endl;
	cout << "The total amount of empty lines is: " << el_amount << endl;
	cout << "The total amount of lines that are not empty is: " << nel_amount << endl;
	cout << "The total amount of words is: " << w_amount << endl;
	cout << "The total amount of letters is:" << lt_amount << endl; 
	cout << endl;
	testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}
