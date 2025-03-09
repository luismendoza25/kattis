#include <iostream>
#include <vector>
#include <sstream>
#include <string>

typedef std::vector<std::string> Song;

void insertion_sort(std::vector<Song> &songs, int index)
{
    int size = songs.size();
    for (int i = 1; i < size; i++)
    {
        Song song = songs[i];
        int j = i - 1;
        while (j >= 0 && songs[j][index] > song[index])
        {
            songs[j + 1] = songs[j];
            j--;
        }
        songs[j + 1] = song;
    }
}

void sort(std::vector<std::string> &attributes, std::vector<Song> &songs, const std::vector<std::string> &sortComm)
{
    for (size_t j = 0; j < sortComm.size(); j++)
    {
        std::string command = sortComm[j];
        int index = -1;

        for (size_t k = 0; k < attributes.size(); k++)
        {
            if (attributes[k] == command)
            {
                index = k;
                break;
            }
        }
        if (index == -1)
        {
            continue;
        }

        insertion_sort(songs, index);
        std::cout << "\n";
        for (size_t i = 0; i < attributes.size(); i++)
        {
            if (i > 0)
                std::cout << " ";
            std::cout << attributes[i];
        }
        std::cout << "\n";
        for (size_t i = 0; i < songs.size(); i++)
        {
            for (size_t j = 0; j < songs[i].size(); j++)
            {
                if (j > 0)
                    std::cout << " ";
                std::cout << songs[i][j];
            }
            std::cout << "\n";
        }
    }
}

int main()
{
    std::string line;
    getline(std::cin, line);
    std::vector<std::string> attributes;
    std::string word;
    std::stringstream ss(line);
    while (ss >> word)
    {
        attributes.push_back(word);
    }

    int m;
    std::cin >> m;
    std::cin.ignore();

    std::vector<Song> songs(m);
    for (int i = 0; i < m; i++)
    {
        getline(std::cin, line);
        std::stringstream song_stream(line);
        std::vector<std::string> song;
        while (song_stream >> word)
        {
            song.push_back(word);
        }
        songs[i] = song;
    }

    int n;
    std::cin >> n;
    std::cin.ignore();

    std::vector<std::string> sortComms(n);
    for (int i = 0; i < n; ++i)
    {
        getline(std::cin, sortComms[i]);
    }

    sort(attributes, songs, sortComms);

    return 0;
}
