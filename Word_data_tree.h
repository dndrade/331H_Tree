#pragma once
#include "Tree.h"
#include "Node.h"
#include "Word_data.h"
#include <fstream>

class Word_data_tree : public Tree<Word_data>
{
public:
    Word_data_tree() = default;
    explicit Word_data_tree(std::fstream&);
    ~Word_data_tree() override = default;

    void print_report() const;

    void statical_summary() const;
    void style_warning() const;
    void print_index() const;

    std::size_t size_longer_than_3() const;
    void warn_word_too_often() const;
    double average_word_length() const;
    std::size_t total_character() const;
    double average_sentence_length() const;
    std::size_t total_sentence() const;

protected:
    void insert_action_if_duplicate(Node<Word_data>* node) override
    {
        node->data->increment();
    }

private:
    static void size_longer_than_3_impl(std::size_t&, const Node<Word_data>*);
    static void warn_word_too_often_impl(std::size_t&, std::size_t, const Node<Word_data> *);
    static void total_character_impl(std::size_t&, const Node<Word_data>*);
    static void total_sentence_impl(std::size_t&, const Node<Word_data>*);
    static void print_index_impl(char&, const Node<Word_data>*);
};

