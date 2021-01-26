import string

TO_LOWER_ASCII_OFFSET = 32


def cleanup(s):
    str = ''
    for char in s:
        if char in string.ascii_lowercase:
            str += char
        if char in string.ascii_uppercase:
            str += (chr(ord(char) + TO_LOWER_ASCII_OFFSET))

    return str


def Shift_E(k, s):
    alphabet = string.ascii_lowercase
    alphabet_len = 26
    first = ord('a')
    # ord() value of first char in our alphabet - 'a'
    out_str = ''
    print("Cleanup of s: %s" % cleanup(s))
    for char in cleanup(s):
        print(ord(char))
        print(ord(char) - first)
        print(((ord(char) - first) % 26))
        print(chr(((ord(char) - first) % 26)) + first)

        ord_val = ord(char) - first
        
        out_str += chr((ord(char) - first) % alphabet_len)

    return out_str

print(ord('a'))
print(ord('A'))

print(ord('a') - ord('A'))

print(cleanup("Hello, My name is dadsbasement#1234"))

print(Shift_E(1, 'abc'))
