#include "doctest.h"
#include <stdio.h>
#include <string>
#include <stdexcept>
#include "BinaryTree.hpp"
using namespace std;
using namespace ariel;

BinaryTree<int> tree;
BinaryTree<string> s_tree;
BinaryTree<double> d_tree;

int i = 0;

TEST_CASE("root test")
{

    CHECK_NOTHROW(tree.add_root(1));
    auto iter1 = tree.begin_preorder();
    CHECK_EQ((*iter1), 1);

    CHECK_NOTHROW(s_tree.add_root("hello"));
    auto iter2 = s_tree.begin_preorder();
    CHECK_EQ((*iter2), "hello");

    CHECK_NOTHROW(d_tree.add_root(3.14));
    auto iter3 = d_tree.begin_preorder();
    CHECK_EQ((*iter3), 3.14);

    CHECK_NOTHROW(tree.add_root(30));
    auto iter4 = tree.begin_preorder();
    CHECK_EQ((*iter4), 30);
}

TEST_CASE("override root")
{
    CHECK_NOTHROW(tree.add_root(5));
    auto iter1 = tree.begin_preorder();
    CHECK_EQ((*iter1), 5);

    CHECK_NOTHROW(s_tree.add_root("bye"));
    auto iter2 = s_tree.begin_preorder();
    CHECK_EQ((*iter2), "bye");

    CHECK_NOTHROW(d_tree.add_root(7.3));
    auto iter3 = d_tree.begin_preorder();
    CHECK_EQ((*iter3), 7.3);
}

TEST_CASE("add left and right sons")
{

    CHECK_NOTHROW(tree.add_left(5, 4));
    CHECK_NOTHROW(tree.add_right(5, 6));

    CHECK_NOTHROW(s_tree.add_left("bye", "left"));
    CHECK_NOTHROW(s_tree.add_right("bye", "right"));

    CHECK_NOTHROW(d_tree.add_left(7.3, 1));
    CHECK_NOTHROW(d_tree.add_right(7.3, 2));
}

TEST_CASE("add left and right sons to none existing root")
{

    CHECK_THROWS(tree.add_left(0, 4));
    CHECK_THROWS(tree.add_right(0, 6));

    CHECK_THROWS(s_tree.add_left("NUL", "left"));
    CHECK_THROWS(s_tree.add_right("NUL", "right"));

    CHECK_THROWS(d_tree.add_left(0, 1));
    CHECK_THROWS(d_tree.add_right(0, 2));
}

TEST_CASE("test preorder for BinaryTree<int>")
{

    CHECK_NOTHROW(tree.add_left(6, 7));
    CHECK_NOTHROW(tree.add_right(6, 2));
    CHECK_NOTHROW(tree.add_left(7, 9));
    CHECK_NOTHROW(tree.add_right(7, 1));

    int preorder_traversal_int[] = {5, 4, 6, 7, 9, 1, 2};

    i = 0;
    for (auto it = tree.begin_preorder(); it != tree.end_preorder(); ++it)
    {
        CHECK_EQ((*it), preorder_traversal_int[i]);
        i++;
    }
}

TEST_CASE("test preorder for BinaryTree<string>")
{

    CHECK_NOTHROW(s_tree.add_left("right", "l.son"));
    CHECK_NOTHROW(s_tree.add_right("right", "r.son"));
    CHECK_NOTHROW(s_tree.add_left("l.son", "l.gson"));
    CHECK_NOTHROW(s_tree.add_right("l.son", "r.gson"));

    string preorder_traversal_string[] = {"bye", "left", "right", "l.son", "l.gson", "r.gson", "r.son"};

    i=0;

    for (auto it = s_tree.begin_preorder(); it != s_tree.end_preorder(); ++it)
    {
        CHECK_EQ((*it), preorder_traversal_string[i]);
        i++;
    }
}

TEST_CASE("test preorder for BinaryTree<double>, Also check ++ prefix")
{
    CHECK_NOTHROW(d_tree.add_left(2, 3));
    CHECK_NOTHROW(d_tree.add_right(2, 4));
    CHECK_NOTHROW(d_tree.add_left(3, 5));
    CHECK_NOTHROW(d_tree.add_right(3, 6));

    double preorder_traversal_double[] = {7.3, 1, 2, 3, 5, 6, 4};

    i = 0;
    for (auto it = d_tree.begin_preorder(); it != d_tree.end_preorder(); ++it)
    {
        CHECK_EQ((*it), preorder_traversal_double[i]);
        i++;
    }
}

TEST_CASE("test inorder for BinaryTree<int>")
{

    int inorder_traversal_int[] = {4, 5, 9, 7, 1, 6, 2};

    i = 0;
    for (auto it = tree.begin_preorder(); it != tree.end_preorder(); ++it)
    {
        CHECK_EQ((*it), inorder_traversal_int[i]);
        i++;
    }
}

TEST_CASE("test inorder for BinaryTree<string>")
{

    string inorder_traversal_string[] = {"left", "bye", "l.gson", "l.son", "r.gson", "right", "r.son"};

    i = 0;
    for (auto it = s_tree.begin_preorder(); it != s_tree.end_preorder(); ++it)
    {
        CHECK_EQ((*it), inorder_traversal_string[i]);
        i++;
    }
}

TEST_CASE("test inorder for BinaryTree<double>")
{
    double inorder_traversal_double[] = {1, 7.3, 5, 3, 6, 2, 4};

    i = 0;
    for (auto it = d_tree.begin_preorder(); it != d_tree.end_preorder(); ++it)
    {
        CHECK_EQ((*it), inorder_traversal_double[i]);
        i++;
    }
}

TEST_CASE("test postorder for BinaryTree<int>")
{
    int postorder_traversal_int[] = {4, 9, 1, 7, 2, 6, 5};

    i = 0;
    for (auto it = tree.begin_preorder(); it != tree.end_preorder(); ++it)
    {
        CHECK_EQ((*it), postorder_traversal_int[i]);
        i++;
    }
}

TEST_CASE("test postorder for BinaryTree<string>")
{
    string postorder_traversal_string[] = {"left", "l.gson", "r.gson", "l.son", "r.son", "right", "bye"};

    i = 0;
    for (auto it = s_tree.begin_preorder(); it != s_tree.end_preorder(); ++it)
    {
        CHECK_EQ((*it), postorder_traversal_string[i]);
        i++;
    }
}

TEST_CASE("test postorder for BinaryTree<double>")
{
    double postorder_traversal_double[] = {1, 5, 6, 3, 4, 2, 7.3};

    i = 0;
    for (auto it = d_tree.begin_preorder(); it != d_tree.end_preorder(); ++it)
    {
        CHECK_EQ((*it), postorder_traversal_double[i]);
        i++;
    }
}

    TEST_CASE("check if prior iterator hasnt changed tree for BinaryTree<int>")
    {

        int inorder_traversal_int[] = {4, 5, 9, 7, 1, 6, 2};

        i = 0;
        for (auto it = tree.begin_preorder(); it != tree.end_preorder(); ++it)
        {
            CHECK_EQ((*it), inorder_traversal_int[i]);
            i++;
        }
    }

    TEST_CASE("check if prior iterator hasnt changed tree for BinaryTree<string>")
    {
        string inorder_traversal_string[] = {"left", "bye", "l.gson", "l.son", "r.gson", "right", "r.son"};

        i = 0;
        for (auto it = s_tree.begin_preorder(); it != s_tree.end_preorder(); ++it)
        {
            CHECK_EQ((*it), inorder_traversal_string[i]);
            i++;
        }
    }

    TEST_CASE("check if prior iterator hasnt changed tree for BinaryTree<double>")
    {
        double inorder_traversal_double[] = {1, 7.3, 5, 3, 6, 2, 4};

        i = 0;
        for (auto it = d_tree.begin_preorder(); it != d_tree.end_preorder(); ++it)
        {
            CHECK_EQ((*it), inorder_traversal_double[i]);
            i++;
        }
    };
