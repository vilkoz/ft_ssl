#!/usr/bin/env python3

from random import randint
from subprocess import check_output
from subprocess import CalledProcessError
from os import urandom

def co(cmd, shell=True):
    try:
        return check_output(cmd, shell=shell)
    except CalledProcessError as e:
        print(e)

NUM_ITER=1000

for _ in range(NUM_ITER):
    length = randint(0, 128)
    s = bytearray(urandom(length))
    entropy_bits = randint(0, 64)
    key = hex(randint(0, 2**entropy_bits-1))[2:]
    iv = hex(randint(0, 2**entropy_bits-1))[2:]

    with open("tmp", "wb") as f:
        f.write(s)
    encoded_text = co("../../ft_ssl des-ecb -e -k "+key+" -i tmp", shell=True);
    ssl_encoded = co("openssl des-ecb -e -K "+key+" -in tmp", shell=True);
    with open("tmp", "wb") as f:
        f.write(ssl_encoded)
    decoded_text = co("../../ft_ssl des-ecb -d -k "+key+" -i tmp", shell=True);
    print("try ssl")
    ssl_decoded = co("openssl des-ecb -d -K "+key+" -in tmp", shell=True);

    encoded, decoded = encoded_text, decoded_text
    if encoded != ssl_encoded or decoded != ssl_decoded:
        print("ERROR! :")
        print(encoded, " <- encoded")
        print(ssl_encoded, " <- ssl_encoded")
        print(decoded, " <- decoded")
        print(ssl_decoded, " <- ssl_decoded")
        print(s, " <- s")
        print(key, " <- key")
        break
    else:
        print("OK len = %d, key = %s" % (length,key))
