//takes like forever to compile so i created my own. refer to using puzzle.txt or my own puzzle, ownPuzzle.txt. u can change in the bottom
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <string>
#include <map>

using namespace std;

map<string, string> bruh;

std::vector<char> grid;
std::size_t grid_size = 0;

void numLine(const string &thing)
{
        string line;
        ifstream file(thing);
        while (getline(file, line))
                grid_size++;
}

void load_grid(const std::string &thing)
{
        numLine(thing);

        std::ifstream inFile;
        inFile.open(thing);

        for (std::size_t i = 0; i < grid_size * grid_size; i++)
        {
                char letter;
                inFile >> letter;
                grid.push_back(letter);
        }
}

bool search_word(std::size_t x, std::size_t y, const string &word)
{

        if (x + word.length() <= grid_size)
        {
                std::size_t i = 0;
                while (i < word.length() && grid[y * grid_size + (x + i)] == word[i])
                        i++;

                if (i == word.length())
                {
                        bruh[word] = "Horz.r";
                        return true;
                }
        }

        else if (x - word.length() > 0)
        {
                std::size_t i = 0;

                while (i < word.length() && grid[y * grid_size + (x - i)] == word[i])
                        i++;

                if (i == word.length())
                {
                        bruh[word] = "Horiz.l";
                        return true;
                }
        }

        else if (y + word.length() <= grid_size)
        {
                std::size_t i = 0;
                while (i < word.length() && grid[(y + i) * grid_size + x] == word[i])
                        i++;
                if (i == word.length())
                {
                        bruh[word] = "V.down";
                        return true;
                }
        }

        else if (y - word.length() > 0)
        {
                std::size_t i = 0;
                while (i < word.length() && grid[(y - i) * grid_size + x] == word[i])
                        i++;
                if (i == word.length())
                {
                        bruh[word] = "V.up";
                        return true;
                }
        }

        else if (x + word.length() <= grid_size && y + word.length() <= grid_size)
        {
                std::size_t i = 0;
                while (i < word.length() && grid[(y + i) * grid_size + x + i] == word[i])
                        i++;
                if (i == word.length())
                {
                        bruh[word] = "D.rd";
                        return true;
                }
        }

        else if (x - word.length() > 0 && y + word.length() <= grid_size)
        {
                std::size_t i = 0;
                while (i < word.length() && grid[(y + i) * grid_size + x - i] == word[i])
                        i++;
                if (i == word.length())
                {
                        bruh[word] = "D.ld";
                        return true;
                }
        }

        else if (x + word.length() <= grid_size && y - word.length() > 0)
        {
                std::size_t i = 0;
                while (i < word.length() && grid[(y - i) * grid_size + x + i] == word[i])
                        i++;
                if (i == word.length())
                {
                        bruh[word] = "D,ru";
                        return true;
                }
        }

        else if (x - word.length() > 0 && y - word.length() > 0)
        {
                std::size_t i = 0;
                while (i < word.length() && grid[(y - i) * grid_size + x - i] == word[i])
                        i++;
                if (i == word.length())
                {
                        bruh[word] = "D,lu";
                        return true;
                }
        }

        return false;
}

int main()
{

        // string puzzle = "puzzle.txt";
        string puzzle = "thing.txt";
        string dict = "words.txt";

        load_grid(puzzle);

        ifstream indata(dict);

        unordered_set<string> words;

        //Initializes the dictionary
        string temp;
        while (indata >> temp)
                if (temp.length() >= 6)
                        words.insert(temp);

        indata.close();
        for (std::size_t x = 0; x < grid_size; x++)
        {

                for (std::size_t y = 0; y < grid_size; y++)
                        for (auto e : words)
                                if (search_word(x, y, e))
                                {
                                        if (bruh[e] == "Vertically (down)")
                                                cout << e << " from : (" << x << ", " << y << ") to (" << x << ", " << y + e.length() << ") " << endl;
                                        else if (bruh[e] == "Vertically (up)")
                                                cout << e << " from : (" << x << ", " << y << ") to (" << x << ", " << (y + 2) - e.length() << ") " << endl;
                                        else if (bruh[e] == "Horizontally (right)")
                                                cout << e << " from : (" << x << ", " << y << ") to (" << x + e.length() << ", " << y << ") " << endl;
                                        else if (bruh[e] == "Horizontally (left)")
                                                cout << e << " from : (" << x << ", " << y << ") to (" << (x + 1) - e.length() << ", " << y << ") " << endl;
                                        else if (bruh[e] == "Diagonally (left and down)")
                                                cout << e << " from : (" << x << ", " << y << ") to (" << (x + 1) - e.length() << ", " << y + e.length() << ") " << endl;
                                        else if (bruh[e] == "Diagonally (right and down)")
                                                cout << e << " from : (" << x << ", " << y << ") to (" << x + e.length() << ", " << y + e.length() << ") " << endl;
                                        else if (bruh[e] == "Diagonally (left and up)")
                                                cout << e << " from : (" << x << ", " << y << ") to (" << (x + 1) - e.length() << ", " << (y + 2) - e.length() << ") " << endl;
                                        else if (bruh[e] == "Diagonally (right and up)")
                                                cout << e << " from : (" << x << ", " << y << ") to (" << x + e.length() << ", " << (y + 1) - e.length() << ") " << endl;
                                }
        }
        return 0;
}
