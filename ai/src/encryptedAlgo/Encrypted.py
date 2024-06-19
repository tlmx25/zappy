import random


class Encrypted:
    def __init__(self, key):
        self.key = key

    def encrypt(self, message):
        message += str(random.randint(0, 999999))
        encrypted = ""
        for i in range(len(message)):
            encrypted += chr(ord(message[i]) ^ ord(self.key[i % len(self.key)]))
        return encrypted

    def decrypt(self, encrypted):
        decrypted = ""
        for i in range(len(encrypted)):
            decrypted += chr(ord(encrypted[i]) ^ ord(self.key[i % len(self.key)]))
        return decrypted
