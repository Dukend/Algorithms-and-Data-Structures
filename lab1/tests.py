import random
import string
MAX_VALUE_LEN = 18446744073709551614
TESTS_COUNT = 1000000

def generate_random_value():
    return random.randint(0, MAX_VALUE_LEN)

def generate_random_key_0():
    return "".join([random.choice(string.ascii_uppercase)])

def generate_random_key_1():
    return "".join([str(random.randint(0, 9)) for _ in range(0, 3)])

def generate_random_key_2():
    return "".join([random.choice(string.ascii_uppercase) for _ in range(0, 2)])

def main():
    values = []
    with open("test.txt", 'w') as foutput:
        for _ in range(0, TESTS_COUNT):
            key_0 = generate_random_key_0()
            key_1 = generate_random_key_1()
            key_2 = generate_random_key_2()
            value = generate_random_value()
            values.append((key_0, key_1, key_2, value))
            foutput.write("{} {} {}\t{}\n".format(key_0, key_1, key_2, value))
        with open("test_answer.txt", 'w') as fans:
            values = sorted(sorted(sorted(values, key=lambda x: x[2]),  key=lambda x: x[1]),  key=lambda x: x[0])
            for value in values:
                fans.write("{} {} {}\t{}\n".format(value[0], value[1], value[2], value[3]))

if __name__ == "__main__":
    main()