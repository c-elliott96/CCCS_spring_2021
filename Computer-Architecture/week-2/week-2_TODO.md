# TODO - Computer Architecture Week 2

* [ ] 2 Discussion comments
* [ ] Dropbox assignment (using software? See D2L)

## Dropbox 02 - Problem 5.7 or 5.9 of Chapter 5

* 5.7 - Given the following specifications for an external cache memory:
  * Four-way set associative
  * Line size of two 16-bit words
  * Able to accommodate a total of 4K 32-bit words from main memory
  * used with a 16-bit processor that issues 24-bit addresses
  design the cache structure with all pertinent information and show
  how it interprets the processor's addresses
  
* 5.9 - Consider a machine with a byte addressable main memory of 2^16
  bytes and a block size of 8 bytes. Assume that a direct mapped cache
  consisting of 32 lines is used with this machine. 
	  a. How is a 16-bit memory address divided into tag, line number,
	  and byte number?
	  b. Into what line would bytes with each of the following addresses
	  be stored? 
	  
	  |      |      |      |      |
	  |------|------|------|------|
	  | 0001 | 0001 | 0001 | 1011 |
	  | 1100 | 0011 | 0011 | 0100 |
	  | 1101 | 0000 | 0001 | 1101 |
	  | 1010 | 1010 | 1010 | 1010 |

	  c. Suppose the byte with address `0001 1010 0001 1010` is stored in the 
	  cache. What are the addresses of the other bytes stored along with it? 
	  d. How many total bytes of memory can be stored in the cache?
	  e. Why is the tag also stored in the cache? 
