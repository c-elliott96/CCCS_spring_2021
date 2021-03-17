from crypto import *

if __name__ == '__main__':
  pt = 'love'
  k = 'fit'

  pt_list = [c for c in pt] 
  pt_list = [to_int(c) for c in pt_list]

  offsets = []
  for c in k:
    offsets.append(to_int(c))

  out = ""
  
  for i in range(len(pt)):
    # after_offset = pt_list[i] + offsets[i % (len(key) - 1)]
    print("encrypting %s, (%d) + %d \t -> %d" % (to_chr(pt_list[i]), pt_list[i], offsets[i % len(k)], pt_list[i] + offsets[i % len(k)] % 26))
    out += to_chr((pt_list[i] + offsets[i % len(k)]) % 26)

  print(out)