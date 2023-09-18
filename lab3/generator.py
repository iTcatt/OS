import random


def hex_generator():
    hex_number = ''
    alphabet = '0123456789ABCDEF'
    for _ in range(32):
        hex_number += alphabet[random.randint(0, 15)]
    
    return hex_number + '\n'


print("Enter name of file")
with open(input(), 'w') as file:
    print('Enter number of strings')
    for _ in range(int(input())):
        file.write(hex_generator())

