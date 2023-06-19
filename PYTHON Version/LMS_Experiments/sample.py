'''''
def xor_encrypt(message, key):
    encrypted = bytearray()
    for i in range(len(message)):
        encrypted.append(message[i] ^ key[i % len(key)])
    return encrypted

def xor_decrypt(encrypted, key):
    decrypted = bytearray()
    for i in range(len(encrypted)):
        decrypted.append(encrypted[i] ^ key[i % len(key)])
    return decrypted

# Example usage
message = input("Enter the message: ")
key = input("Enter the key: ")

# Convert the input strings to bytes
message_bytes = message.encode('utf-8')
key_bytes = key.encode('utf-8')

encrypted_message = xor_encrypt(message_bytes, key_bytes)
decrypted_message = xor_decrypt(encrypted_message, key_bytes)

print("Original Message:", message)
print("Encrypted Message:", encrypted_message.decode('utf-8'))
print("Decrypted Message:", decrypted_message.decode('utf-8'))
'''

def encrypt(plain_text, key):
    encrypted = bytearray()
    for i in range(len(plain_text)):
        encrypted.append(plain_text[i] ^ key[i % len(key)])
    return encrypted.hex()


def decrypt(encrypted_text, key):
    decrypted = bytearray.fromhex(encrypted_text)
    plain_text = bytearray()
    for i in range(len(decrypted)):
        plain_text.append(decrypted[i] ^ key[i % len(key)])
    return plain_text.decode()

# Get input from the user
plain_text = input("Enter the plain text: ")
encryption_key = input("Enter the encryption key: ")

# Convert the key to bytes
key = encryption_key.encode()

# Encrypt the plain text
encrypted_text = encrypt(plain_text.encode(), key)
print("Encrypted text:", encrypted_text)

# Decrypt the encrypted text
decrypted_text = decrypt(encrypted_text, key)
print("Decrypted text:", decrypted_text)
