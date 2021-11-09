import time
import random as rand
import numpy as np
import caesar_test_case_gen as test_case
import matplotlib.pyplot as plt

"""
key is effectively any number in the range of 0 to 25
as otherwise it would be key % 26 , which thus brings it in our range
"""


def brute_force_attack(encrypted_text, plain_text):
    for key in range(0, 26):
        if decrypt(encrypted_text, key) == plain_text:
            return key


def decrypt(encrypted_text, key):
    decrypted_text = ""
    for ch in encrypted_text:
        idx = ord(ch)
        if idx >= 65 and idx <= 90:
            new_idx = (idx - 65 - key) % 26 + 65
            decrypted_text += chr(new_idx)
        elif idx >= 97 and idx <= 122:
            new_idx = (idx - 97 - key) % 26 + 97
            decrypted_text += chr(new_idx)
        else:
            decrypted_text += ch
            continue
    return decrypted_text


def encrypt(plain_text, key):
    encrypted_text = ""
    for ch in plain_text:
        idx = ord(ch)
        if idx >= 65 and idx <= 90:
            new_idx = (idx - 65 + key) % 26 + 65
            encrypted_text += chr(new_idx)
        elif idx >= 97 and idx <= 122:
            new_idx = (idx - 97 + key) % 26 + 97
            encrypted_text += chr(new_idx)
        else:
            encrypted_text += ch
            continue
    return encrypted_text


if __name__ == "__main__":

    """
    plain_text = input("Enter plain text to be encrypted : ")
    key = 7
    encrypted_text = encrypt(plain_text, key)
    print(encrypted_text)
    decrypted_text = decrypt(encrypted_text, key)
    print(decrypted_text)
    """

    num_tests = 1000
    max_len = 1000
    str_len = []
    time_taken = []
    key_gen = []
    test_case.gen_test_case(num_tests, max_len)
    test_file = open("caesar_test_file.txt", "r")
    for line in test_file:
        plain_text = line
        key = rand.randint(0, 25)
        key_gen.append(key)
        str_len.append(len(plain_text))
        encrypted_text = encrypt(plain_text, key)
        start = time.time()
        ret_key = brute_force_attack(encrypted_text, plain_text)
        end = time.time()
        time_taken.append(end - start)

    plt.bar(str_len,time_taken , color = "red"  , width=0.2)
    average_time = np.average(time_taken)
    print("Average time taken for identifying the key is : ", average_time)
    plt.xlabel("Length of the string")
    plt.ylabel("Time Taken( in s )")
    plt.title("  Time Taken vs String Length ")
    plt.savefig('plot.png')
