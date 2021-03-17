from crypto import *

def Vigenere_E(k, s):
  s = cleanup(s)
  pt_list = [c for c in s] 
  pt_list = [to_int(c) for c in pt_list]

  offsets = []
  for c in k:
    offsets.append(to_int(c))

  out = ""
  
  for i in range(len(s)):
    # after_offset = pt_list[i] + offsets[i % (len(key) - 1)]
    out += to_chr((pt_list[i] + offsets[i % len(k)]) % 26)

  return out

if __name__ == '__main__':
  s = """
  Dear reader! It rests with you and me whether, in our two fields of action similar things
  shall be or not. Let them be! We shall sit with lighter bosoms on the hearth, to see the ashes
  of our fires turn grey and cold.
  """
  k = 'times'
  print(Vigenere_E(k, s))