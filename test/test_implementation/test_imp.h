#pragma once

#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include "RedBlackTree.h"

enum Requests
{
	KEY = 'k',
	QUERY = 'q'
};

namespace test_rbt
{
    int answer ( std::ifstream& answer_file )
    {
        int answer;
        answer_file >> answer;

        return answer;
    }

    void run_test (const std::string& test_name)
    {
        std::filesystem::path test_task_path = std::filesystem::current_path().parent_path();
        std::filesystem::path test_ans_path = std::filesystem::current_path().parent_path();

        test_task_path /= "data/tasks/" + test_name + ".dat";
        test_ans_path /= "data/answers/" + test_name + ".ans";

        RedBlackTree<int> rb_tree;

        char request;

        int key;
        int key1, key2;
        int res;
        int ans;

        std::ifstream task_file(test_task_path);
        std::ifstream answer_file(test_ans_path);

        while (task_file >> request)
        {
            switch(request)
            {
                case KEY   : 
                            if (!(std::cin >> key)) throw "Error reading from input stream\n";

                            rb_tree.insert(key);

                            break;

                case QUERY :
                            if (!(std::cin >> key1 >> key2))  throw "Error reading from input stream\n"; 

                            res = rb_tree.range_queries(key1, key2);
                            ans = answer(answer_file);

                            EXPECT_EQ(res, ans);

                            break;

                default :
                            throw "Error reading from input stream\n"; 
            }
        }
    }
}
