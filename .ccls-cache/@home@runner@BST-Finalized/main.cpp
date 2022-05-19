#include <iostream>
#include <fstream>
#include "Word_data_tree.h"

int main()
{
    Word_data_tree t1;
    for(auto word : {"World.", "Hello", "World", "You", "World", "Ok", "Hello"})
    {
        t1.insert(word);
    }
    t1.print_report();

	std::cout << "\n\n\n";
	
    std::fstream fs("text.txt");
    Word_data_tree t2(fs);
    t2.print_report();
}
