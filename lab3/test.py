HEX = 16


def hex_to_dec(number):
    sum_line = 0
    length = len(number)
    for i in range(length):
        power = length - i - 1
        if number[i].isalpha():
            sum_line += (ord(number[i]) - ord('A') + 10) * HEX**power
        else:
            sum_line += (ord(number[i]) - ord('0')) * HEX**power
    return sum_line


file_sum = 0
lines = 0
print("Enter filename: ")
with open(input(), 'r') as file:
    print("Enter number of threads: ")
    threads = int(input())
    print("Enter number of string: ")
    strings_number = int(input())
    for line in file.readlines():
        number = hex_to_dec(line.rstrip())
        file_sum += number
        lines += 1
        if (lines == threads * strings_number or line == '\n'):
            break
    print(lines)
    print('Total sum:', file_sum)
    print('Average value:', file_sum / lines)
