import crypto

def Vigenere_E(k, s):
  s = crypto.cleanup(s)
  pt = [c for c in s] 
  pt = [crypto.to_int(c) for c in pt]

  offsets = []
  for c in k:
    offsets.append(crypto.to_int(c))

  out = ""
  
  for i in range(len(s)):
    out += crypto.to_chr((pt[i] + offsets[i % len(k)]) % 26)

  return out

# def Vigenere_D(k, s):
#   neg_offsets = []
#   for c in k:
#     neg_offsets.append(-(crypto.to_int(c)))
#     print(-(crypto.to_int(c)))

#   print("neg_offsets: ", neg_offsets)
  
#   inv_key = ''
#   for i in range(len(k)):
#     print("key[i]: ", k[i])
#     new_chr = crypto.to_chr((crypto.to_int(k[i]) + neg_offsets[i]) % 26)
#     inv_key += new_chr
#     print("new_chr: ", new_chr)

#   print("inv_key: ", inv_key )

#   return Vigenere_E(inv_key, s)

def Vigenere_D(k, c):
  # we have the key, so we compute the offset (which is actually
  # the inverse offset)

  # suppose key = 'hello' --> offsets = [7, 4, 11, 11, 14]
  # therefore key^-1 --> [-7, -4, -11, -11, -14]
  neg_offsets = []
  for v in k:
    neg_offsets.append(-(crypto.to_int(v)))
  out = ''
  
  for i in range(len(c)):
    out_c = crypto.to_chr((crypto.to_int(c[i]) + neg_offsets[i % len(k)]) % 26)
    out += out_c

  return out

if __name__ == '__main__':
  # ciphertext = '''
  # mpqzalqfsjaihmfzafvgetqhlhbtiobvpsotvpfwbvsxzxvqry
  # toqhagtascbvsgskmxikltksmmemwslczqgompfqmpuwafxdik
  # lqhiwgbdcslumruhcxhhhaemtegnizxafsgwetmkmturymwtme
  # lmxjobbtedeqyeybvmfdxkasdgmewobbtlalpmxkmqxpggizhs
  # vmdxsbvmmjhnqbztcexahvgtggpuqagxmvltzuwagorvgfmjgw
  # lauzwlcyqwkizhagxmvlyzaqwqkqwkbdqkwgbupamgrsjbbiek
  # mwnikxmzaamptedyiziqxbtelamiektbtsjhcslyxvfpwfizqs
  # wmfslamysvxtajlamfmexeqejrwrinxzkxzbvsefwxgxlbvsrg
  # fwdixtqflagizclaqzklaizpmvqrij
  # '''

  ciphertext = '''
  Dear reader! It rests with you and me whether, in our two fields of action similar things
  shall be or not. Let them be! We shall sit with lighter bosoms on the hearth, to see the ashes
  of our fires turn grey and cold.
  '''
  key = 'times'
  c = Vigenere_E(key, ciphertext)
  print("c = ", c)
  print(Vigenere_D(key, c))


