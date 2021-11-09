from os import close
import random


def gen_test_case(NUM_TESTS,  MAXLEN):
    test_file = open('caesar_test_file.txt', 'w')
    for i in range(NUM_TESTS):
        LEN = random.randint(1, MAXLEN)
        test_line = ""
        for j in range(LEN):
            test_line += chr(random.randint(48, 123))
        test_file.write(test_line + '\n')

    test_file.close()
    
"""
if __name__ == '__main__':
    max_len = int(input("Enter max length of test case: "))
    num_tests = int(input("Enter number of test cases: "))
    gen_test_case(num_tests, max_len)
    print("Test case generated")
"""