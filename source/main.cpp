#include <iostream>
#include <fstream>
#include <string>
#include "tokenizer.h"
#include "error.h"
// char buf[10006];
int main(int argc, char *argv[])
{
    Tokenizer tokenizer;
    std::fstream fin;
    fin.open(argv[2]);
    std::string buf;
    while (std::getline(fin,buf))
    {
        std::cout << buf << std::endl;
    }
    
    // try
    // {
    //     tokenizer.analyse(argv[1]);
    //     auto tokens = tokenizer.getTokens();
    //     // fout.open(argv[2]);
    //     for (const auto &token : tokens)
    //     {
    //         std::cout << token;
    //         // fout << token;
    //     }
    // }
    // catch (Error &err)
    // {
    //     std::cerr << err << std::endl;
    // }
    // catch (const std::exception &e)
    // {
    //     std::cerr << e.what() << '\n';
    // }

}