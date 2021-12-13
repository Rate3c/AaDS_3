#include "pch.h"
#include "CppUnitTest.h"
#include "..\Tree, Stack and Queue.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestfortree
{
    TEST_CLASS(UnitTestfortree)
    {
    public:

        TEST_METHOD(Test_for_insert_element_for_tree)
        {
            tree a;
            a.insert(30);
            a.insert(33);
            a.insert(25);
            a.insert(28);

            Iterator* tree_iterator_queue = a.create_bft_iterator();
            Assert::IsTrue(tree_iterator_queue->next() == 30);
            Assert::IsTrue(tree_iterator_queue->next() == 25);
            Assert::IsTrue(tree_iterator_queue->next() == 33);
            Assert::IsTrue(tree_iterator_queue->next() == 28);
        }
        TEST_METHOD(Test_for_remove_element_without_tree_and_contains)
        {
            tree a;
            a.insert(20);
            a.insert(23);
            a.insert(15);
            a.insert(18);

            a.remove(20);

            Assert::IsTrue(a.contains(20) == false);

            a.remove(15);

            Assert::IsTrue(a.contains(18) == true);
            Assert::IsTrue(a.contains(15) == false);

            a.remove(23);
            try {
                a.remove(1);
            }
            catch (const invalid_argument error) {
                Assert::AreEqual("Element doesn't exist", error.what());
            }

        }
        TEST_METHOD(Test_DFT)
        {
            tree a;
            a.insert(33);
            a.insert(20);
            a.insert(34);
            a.insert(14);
            a.insert(35);
            a.insert(16);
            a.insert(24);
            a.insert(22);
            a.insert(26);
            a.insert(15);
            a.insert(17);

            a.remove(20);

            Iterator* tree_iterator_stack = a.create_dft_iterator();
            Assert::IsTrue(tree_iterator_stack->next() == 33);
            Assert::IsTrue(tree_iterator_stack->next() == 22);
            Assert::IsTrue(tree_iterator_stack->next() == 14);
            Assert::IsTrue(tree_iterator_stack->next() == 16);
            Assert::IsTrue(tree_iterator_stack->next() == 15);
            Assert::IsTrue(tree_iterator_stack->next() == 17);
            Assert::IsTrue(tree_iterator_stack->next() == 24);
            Assert::IsTrue(tree_iterator_stack->next() == 26);
            Assert::IsTrue(tree_iterator_stack->next() == 34);
            Assert::IsTrue(tree_iterator_stack->next() == 35);

        }
        TEST_METHOD(Test_BFT)
        {
            tree a;

            a.insert(33);
            a.insert(20);
            a.insert(34);
            a.insert(14);
            a.insert(35);
            a.insert(16);
            a.insert(24);
            a.insert(22);
            a.insert(26);
            a.insert(15);
            a.insert(17);

            a.remove(20);

            Iterator* tree_iterator_queue = a.create_bft_iterator();
            Assert::IsTrue(tree_iterator_queue->next() == 33);
            Assert::IsTrue(tree_iterator_queue->next() == 22);
            Assert::IsTrue(tree_iterator_queue->next() == 34);
            Assert::IsTrue(tree_iterator_queue->next() == 14);
            Assert::IsTrue(tree_iterator_queue->next() == 24);
            Assert::IsTrue(tree_iterator_queue->next() == 35);
            Assert::IsTrue(tree_iterator_queue->next() == 16);
            Assert::IsTrue(tree_iterator_queue->next() == 26);
            Assert::IsTrue(tree_iterator_queue->next() == 15);
            Assert::IsTrue(tree_iterator_queue->next() == 17);
        }
    };
}