#pragma once
#include <string>
#include <iostream>

struct Word_data
{
public:
    explicit Word_data(std::string str)
    {
        sentence_start = (str.back() == '.');
        for (auto it = str.begin(); it != str.end(); ++it)
        {
            *it = static_cast<char>(std::tolower(*it));
            if(!std::isalpha(*it))
            {
                str.erase(it);
                --it;
            }
        }
        word = str;
    }

    void increment() { ++count; }

    bool operator<(const Word_data& other) const
    {
        return word < other.word;
    }
    bool operator>(const Word_data& other) const
    {
        return word > other.word;
    }
    bool operator==(const Word_data& other) const
    {
        return word == other.word;
    }

    std::string word;
    std::size_t count = 1;
    bool start_of_sentence = sentence_start;

    static bool sentence_start;

    friend std::ostream& operator<<(std::ostream& os, const Word_data& word_data)
    {
        return os << '(' << word_data.word << ',' << word_data.count << ')';
    }
};

inline bool Word_data::sentence_start = true;