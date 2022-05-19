#include "Word_data_tree.h"

Word_data_tree::Word_data_tree(std::fstream& fs)
{
    std::string temp;
    while (fs >> temp)
    {
        insert(temp);
    }
}

void Word_data_tree::print_report() const
{
    statical_summary();
    style_warning();
    print_index();
}

void Word_data_tree::statical_summary() const
{
    std::cout << "\nSTATISTICAL SUMMARY\n";
    std::cout << "TOTAL NUMBER OF WORDS: " << total_size() << '\n';
    std::cout << "TOTAL NUMBER OF “UNIQUE” WORDS: " << size() << '\n';
    std::cout << "TOTAL NUMBER OF “UNIQUE” WORDS OF MORE THAN THREE LETTERS: ";
    std::cout << size_longer_than_3() << '\n';
    std::cout << "AVERAGE WORD LENGTH: ";
    std::cout << average_word_length() << " characters\n";
    std::cout << "AVERAGE SENTENCE LENGTH: ";
    std::cout << average_sentence_length() << " words\n";
}

void Word_data_tree::style_warning() const
{
    std::cout << "\nSTYLE WARNINGS\n";
    warn_word_too_often();
    if(auto value = average_sentence_length(); value > 10)
    {
        std::cout << "AVERAGE SENTENCE LENGTH TOO LONG – ";
        std::cout << value << " words\n";
    }
    if(auto value = average_word_length(); value > 10)
    {
        std::cout << "AVERAGE WORD LENGTH TOO LONG – ";
        std::cout << value << " characters\n";
    }
}

double Word_data_tree::average_sentence_length() const
{
    return double(total_sentence()) / size();
}

std::size_t Word_data_tree::total_sentence() const
{
    std::size_t total = 0;
    total_sentence_impl(total, this);
    return total;
}

void Word_data_tree::print_index() const
{
    std::cout << "\nINDEX OF UNIQUE WORDS\n";
    char section_name = 'a' - 1;
    print_index_impl(section_name, this);
}

void Word_data_tree::print_index_impl(char& section_name, const Node<Word_data> *node)
{
    if(node->data)
    {
        if(node->left)
        {
            print_index_impl(section_name, node->left.get());
        }
        if(node->data->word.front() != section_name)
        {
            section_name = node->data->word.front();
            std::cout << "   " << char(std::toupper(section_name)) << '\n';
        }
        std::cout << node->data->word << '\n';
        if(node->right)
        {
            print_index_impl(section_name, node->right.get());
        }
    }
}

std::size_t Word_data_tree::size_longer_than_3() const
{
    std::size_t size = 0;
    size_longer_than_3_impl(size, this);
    return size;
}

void Word_data_tree::size_longer_than_3_impl(size_t & size, const Node<Word_data> * node)
{
    if (node->data)
    {
        if(node->left)
        {
            size_longer_than_3_impl(size, node->left.get());
        }
        if(node->data->word.size() > 3)
        {
            ++size;
        }
        if(node->right)
        {
            size_longer_than_3_impl(size, node->right.get());
        }
    }
}

void Word_data_tree::warn_word_too_often() const
{
    std::cout << "WORDS USED TOO OFTEN: \n";
    std::size_t count = 0;
    warn_word_too_often_impl(count, size(), this);
}

void Word_data_tree::warn_word_too_often_impl(size_t & counter, std::size_t size, const Node<Word_data> * node)
{
    if (node->data)
    {
        if(node->left)
        {
            warn_word_too_often_impl(counter, size, node->left.get());
        }
        if(node->data->count > 0.05 * size && node->data->word.size() > 3)
        {
            std::string temp = node->data->word;
            temp[0] = std::toupper(temp[0]);
            std::cout << ++counter << ") " << temp << '\n';
        }
        if(node->right)
        {
            warn_word_too_often_impl(counter, size, node->right.get());
        }
    }
}

double Word_data_tree::average_word_length() const
{
    return total_character() / double(total_size());
}

void Word_data_tree::total_character_impl(size_t & size, const Node<Word_data> * node)
{
    if (node->data)
    {
        if(node->left)
        {
            total_character_impl(size, node->left.get());
        }
        size += node->data->word.size() * node->data->count;
        if(node->right)
        {
            total_character_impl(size, node->right.get());
        }
    }
}

std::size_t Word_data_tree::total_character() const
{
    std::size_t total = 0;
    total_character_impl(total, this);
    return total;
}

void Word_data_tree::total_sentence_impl(size_t & size, const Node<Word_data> * node)
{
    if (node->data)
    {
        if(node->left)
        {
            total_character_impl(size, node->left.get());
        }
        size += node->data->start_of_sentence;
        if(node->right)
        {
            total_character_impl(size, node->right.get());
        }
    }
}