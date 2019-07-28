//
// Created by lucas on 12/06/19.
//

#include "HandsParser.hpp"

using namespace touchless;


int main(int argc, char **argv)
{
    HandsParser hands_parser;
  hands_parser.SetOnCanParseHands([]() {
    std::cout << "DAYUM!" << std::endl;
  });

    return 0;
}