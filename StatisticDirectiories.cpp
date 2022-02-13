#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <thread>
#include <fstream>

using namespace std;
namespace fs = filesystem;

void show_and_count_files_and_lines(string path)
{
	int file_amount = 0;
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
				file_amount++;
				f_name=name.path().string();
				ifstream file(f_name);
					while (getline(file,line))
					{
					lines_amount++;
						if(line.empty())
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
		cout << "The amount of files is: " << file_amount << endl;
		cout << "The amount of lines is: " << lines_amount << endl;
		cout << "The amount of empty lines is: " << empty_lines_amount << endl;
		cout << "The amount of lines that are not empty is: " << empty_lines_amount << endl;
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
	show_and_count_files_and_lines(path);
	}
}

