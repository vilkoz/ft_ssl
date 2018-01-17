#!/usr/bin/env python3

from random import randint
from subprocess import check_output as co
from subprocess import CalledProcessError

pattern = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/ "

for _ in range(100):
    length = randint(0, 1024)
    s = ''.join([pattern[randint(0, len(pattern) - 1)] for __ in range(length)])
    try:
        out = co("./a.out \"" + s + "\"", shell=True);
        ssl_encoded = co("echo -n \"" + s + "\"| base64 -w 0", shell=True);
    except CalledProcessError as e:
        print(e)
    out = out.decode()
    ssl_encoded = ssl_encoded.decode()
    encoded, decoded = out.split('\n')
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
        print("OK")
