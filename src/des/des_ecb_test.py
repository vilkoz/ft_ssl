#!/usr/bin/env python3

from random import randint
from subprocess import check_output as co
from subprocess import CalledProcessError

pattern = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/ "

for _ in range(100):
    length = randint(0, 128)
    s = ''.join([pattern[randint(0, len(pattern) - 1)] for __ in range(length)])
    try:
        encoded_text = co("echo -n \"" + s + "\" | ../../ft_ssl des-ecb -e -k 1122334455667788 -a", shell=True);
        ssl_encoded = co("echo -n \"" + s + "\"| openssl des-ecb -e -K 1122334455667788 -a", shell=True);
        decoded_text = co("echo -n \"" + ssl_encoded.decode() + "\"| ../../ft_ssl des-ecb -d -k 1122334455667788 -a", shell=True);
        ssl_decoded = co("echo -n \"" + ssl_encoded.decode() + "\"| openssl des-ecb -d -K 1122334455667788 -a", shell=True);
    except CalledProcessError as e:
        print(e)
    encoded_text = encoded_text.decode()
    decoded_text = decoded_text.decode()
    ssl_encoded = ssl_encoded.decode()
    encoded, decoded = encoded_text, decoded_text
    if decoded != s or decoded != ssl_decoded.decode():
        print("ERROR! :")
        print(decoded, " <- decoded")
        print(s, " <- s")
        break
    elif encoded != ssl_encoded:
        print("ERROR! :")
        print(s, " <- input")
        print(encoded, " <- encoded")
        print(ssl_encoded, " <- ssl_encoded")
        break
    else:
        print("OK len = %d" % length)
