#!/usr/bin/env python3

from random import randint
from subprocess import check_output as co
from subprocess import CalledProcessError

pattern = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/ "

for _ in range(100):
    length = randint(0, 128)
    s = ''.join([pattern[randint(0, len(pattern) - 1)] for __ in range(length)])
    try:
        encoded_text = co("printf \"" + s + "\" | ../../ft_ssl base64 -e", shell=True);
        ssl_encoded = co("printf \"" + s + "\"| base64", shell=True);
        decoded_text = co("printf \"" + ssl_encoded.decode() + "\"| ../../ft_ssl base64 -d", shell=True);
    except CalledProcessError as e:
        print(e)
    encoded_text = encoded_text.decode()
    decoded_text = decoded_text.decode()
    ssl_encoded = ssl_encoded.decode()
    encoded, decoded = encoded_text, decoded_text
    encoded = encoded.replace("\n", "")
    decoded = decoded.replace("\n", "")
    ssl_encoded = ssl_encoded.replace("\n", "")
    if decoded != s:
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
