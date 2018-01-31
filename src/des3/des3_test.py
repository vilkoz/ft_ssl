#!/usr/bin/env python3

from random import randint
from subprocess import check_output as co
from subprocess import CalledProcessError

pattern = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/ "

for _ in range(100):
    length = randint(0, 128)
    s = ''.join([pattern[randint(0, len(pattern) - 1)] for __ in range(length)])
    try:
        encoded_text = co("printf \"" + s + "\" | ../../ft_ssl des3 -e -k 112233445566778811223344556677881122334455667788 -v 1020304050607080 -a", shell=True);
        ssl_encoded = co("printf \"" + s + "\"| openssl des3 -e -K 112233445566778811223344556677881122334455667788 -iv 1020304050607080 -a", shell=True);
        decoded_text = co("printf \"" + ssl_encoded.decode() + "\"| ../../ft_ssl des3 -d -k 112233445566778811223344556677881122334455667788 -v 1020304050607080 -a", shell=True);
        ssl_decoded = co("printf \"" + ssl_encoded.decode() + "\"| openssl des3 -d -K 112233445566778811223344556677881122334455667788 -iv 1020304050607080 -a", shell=True);
    except CalledProcessError as e:
        print(e)
    encoded_text = encoded_text.decode()
    decoded_text = decoded_text.decode()
    ssl_encoded = ssl_encoded.decode().replace("\n", "") + "\n"
    encoded, decoded = encoded_text, decoded_text
    if encoded != ssl_encoded:
        print("ERROR! :")
        print(s, " <- input")
        print(encoded, " <- encoded")
        print(ssl_encoded, " <- ssl_encoded")
        break
    elif decoded != s or decoded != ssl_decoded.decode():
        print("ERROR! :")
        print(decoded, " <- decoded")
        print(s, " <- s")
        break
    else:
        print("OK len = %d" % length)
