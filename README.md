# StatisticDirectories
A short description of how the application works:
1. User inserts path to directory by keyboard.
2. The program checks if such a path exists.
3. If yes, first function (count files) counts the amount of files in this path and displays this amount.
4. Then a number of threads equal to the amount of files is created.
5. Each thread executes the second function (count stats) for a single file, so each thread operates on one file.
6. The second function counts lines, empty lines, non empty lines, words and letters in every file, and also adds these values to total amount of those stats in all files in this path.
7. After executing the appropriate number of threads, the program displays the total amount of stats.
8. Unit Tests (written for the "mock" folder) are initiating-GTest was used.