import math
import random

# give the size of the key to be generated in bits
def generate_key(n):

	val = list("abcdefghijklmnopqrstuvwxyz")
	key = ""
	for i in range(n):
		key += val[math.floor(random.randint(0, 25))]
	return key