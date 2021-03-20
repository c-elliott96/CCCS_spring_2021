<!-- Author: Christian Elliott -->

# Computer Architecture - Notes on Chapters 4-6

-------------------------------------------------------------------------------

## Chapter 4 - The Memory Hierarchy: Locality

### 4.1 Principle of Locality

* Memory refernces made by programs tend to cluster over time

  * That is to say, a program will often make sequential and
    frequent reads/writes to local area in memory, due to the
    nature of programming

  * Define **Temporal/Spatial locality**
  
  * Helpful example: Imagine Bob works in an office and he does a lot of paper-
  work filing. For ease, he keeps a small filer at his desk that can hold only
  a few documents. If he works on a document, he will put it in his nearby
  filer in case he needs to retrieve it again in a few moments. This is him
  prioritizing temporal locality. Bob also decides that when he fetches folders
  from the other room (with all the documents) he often needs to work on
  documents from folders neaby to the folder he is fetching. Bob might decide
  to grab several folders (maybe a couple from in front of and a couple from
  behind) around the location of the folder he is pulling, so he doesn't have
  to go back to the filing room unnecessarily. This is Bob prioritizing spatial
  locality.
  
-------------------------------------------------------------------------------

### 4.2 Characteristics of Memory Systems

* Important terms to understand

	* **Word**: The "natural" unit of organization of memory; usually, the size
	of the word is equal to the number of bits used to represent an integer and
	to the instruction length. There are exceptions to that rule.
	
	* **Addressible units**: In some systems, the addressible unit is the word.
	However, many sytems allow addressing at the byte level. In any case, the
	relationship between the length in bits _A_ of an address and the number
	_N_ of addressible units is 2^_A_ = _N_.

	* **Unit of transfer**: For main memory, this is the number of bits read
	out of or written into memory at a time. The unit of transfer need not
	equal a word or an addressible unit. For external memory, data are often
	transferred in much larger units than a word, and these are referred to
	as blocks. 
	
	* Sequential access - e.g. magnetic tape
	
	* Direct access - e.g. disk
	
	* Random access - e.g. RAM
	
	* Associative access - e.g. some cache systems (this definition is weird)
	
	* Access time (latency): For random access memory, this is the time it
	takes to perform a read or write operation
	
	* Memory cycle time: (mainly concerning RAM) consists of the access time
	plus any additional time required before a second access can commence
	(note: this is regarding the system bus, not the processor)
	
	* Transfer rate: The rate at which data can be transferred into or out of
	a memory unit
	
		* For RAM: 1/(cycle time)
		* For non-random-access memory:
			* T\_n = T\_A + (n / R) where
				* T\_n = Average time to read/write n bits
				* T\_A = Average access time
				* n = Number of bits
				* R = Transfer rate, in bits per second

-------------------------------------------------------------------------------

### 4.3 The Memory Hierarchy

* Three concerns with memory:

	* Make it as fast as possible
	* Make it as big as possible
	* Make it as cheap as possible

* In a typical hierarchy, the following occur:

	1. Decreasing cost per bit
	2. Increasing cpacity
	3. Increasing access time
	4. Decreasing frequency of access of the memory by the processor
	
	* Important formulas for calculating Memory hierarchy cost values
	should be LaTex'd and added, time permitting
	
