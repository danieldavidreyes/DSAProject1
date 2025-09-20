#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <main.cpp>
#include <algorithm>
// uncomment and replace the following with your own headers
// #include "AVL.h"

using namespace std;

TEST_CASE("BST Insert", "[flag]"){
    AVLTree inputTree;
    inputTree.insert(3);
    inputTree.insert(2);
    inputTree.insert(1);
    std::vector<int> actualOutput = inputTree.inorder();
    std::vector<int> expectedOutput = {1, 2, 3};
    REQUIRE(expectedOutput.size() == actualOutput.size());
    REQUIRE(actualOutput == expectedOutput);
}


TEST_CASE("BST Insert Large", "[flag]"){
    AVLTree inputTree;
    std::vector<int> expectedOutput, actualOutput;

    for(int i = 0; i < 100000; i++)
    {
        int randomInput = rand();
        if (std::count(expectedOutput.begin(), expectedOutput.end(), randomInput) == 0)
        {
            expectedOutput.push_back(randomInput);
            inputTree.insert(randomInput);
        }
    }

    actualOutput = inputTree.inorder();
    REQUIRE(expectedOutput.size() == actualOutput.size());
    std::sort(expectedOutput.begin(), expectedOutput.end());
    REQUIRE(expectedOutput == actualOutput);

}

