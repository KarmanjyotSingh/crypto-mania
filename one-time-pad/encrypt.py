
def encrypt(plaintext, key):

    if len(plaintext) != len(key):
        return "Key and plaintext have different lengths."

    vals = list("abcdefghijklmnopqrstuvwxyz")
    PLAINTEXT = []
    KEY = []
    for i in range(len(plaintext)):
        PLAINTEXT.append(vals.index(plaintext[i].lower()))
        KEY.append(vals.index(key[i].lower()))
    encrypted_msg = ""

    for i in range(len(PLAINTEXT)):
        encrypted_msg += vals[(PLAINTEXT[i] + KEY[i]) % 26]

    return encrypted_msg;