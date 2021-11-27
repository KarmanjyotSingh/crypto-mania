def decrypt(key, ciphertext):
    
    plaintext = ""
    alphabet = list("abcdefghijklmnopqrstuvwxyz")
    text = [alphabet.index(x.lower()) for x in ciphertext]
    key_text = [alphabet.index(x.lower()) for x in key]
    for i in range(len(text)):
        diff = text[i] - key_text[i]
        if diff < 0:
            diff += 26
        else:
            diff %= 26
        plaintext += alphabet[diff]
    return plaintext
