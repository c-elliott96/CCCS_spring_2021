# Christian Elliott

<!-- TODO: Add ToC -->

# Lecture 1 Notes - 1/11/21

## Introduction

Information Theory plays a role in cryptography

	* Information theory was founded by Claude Shannon 
		at AT&T
		
3 Important components of Cryptography

	1. Cipher
	2. Hash function
	3. (Pseudo) Random number generation
	
The algorithms we will cover in crypto will be __algebraic__ in nature

Another key area of consideration will be __number theory__ 

	* Ex: `{congruence} (mod n)`
	
__Finite fields__ 
	
	* Ex: `{0,1}` is a finite, binary field. 
	
	* Most of the useful fields used in cryptography are finite.
	
We'll also study __groups__

	* Groups are like fields, but only have one operation (while 
		fields allow four operations: +,-,/ (except 0), and *
		
The RSA algorithm uses number theory (specifically modular arithmetic)

More modern ciphers use elliptic curve cryptography (ECC)

	* Ex: y^2 = x^3 + x + 1
	
---

# Lecture 2 Notes - 1/13/21

## Introduction (pt 2)

In Crypto, we won't have to use many complex data structures

A simple cipher example is the Caesar Cipher

	* The Caesar Cipher is a simple shift cipher
	
	* CC only works for a small set of characters
	
		* Q: Why is this? 
		
__Important__: A cipher (encryption) must be invertible

	* I.e. Encryption function should be an inverse of the 
		decryption function, and opposite.
		
__<3 modular arithmetic <3__

### Components of secure communication

Secure channel

	* Furthermore, we should *always* assume a channel to be 
		public. 
		
Confidentiality & Authentication

	* Q: How do you guarantee data integrity? 

---

# Book notes

## Reference [Lecture Notes on Cryptography](http://cseweb.ucsd.edu/~mihir/papers/gb.pdf)

### Chapter 1: Introduction to Modern Cryptography

#### 1.1 Encryption: Historical Glance

Issue: secure communication over an insecure channel

* Party A wants to send Party B a secret message over a communication line which may be tapped by an adversary

	* Going forward, we will __always__ assume the channel to be public. 

* The first, and traditional choice in securing the communication is via __private key encryption__. 

	* This means A & B meet to agree on a pair of encryption and decryption algorithms, `E()` and `D()`. 

	* A and B must also agree on a __common secret key__ *S*. The adversary might know the algorithms, but the secret must be kept... secret. 

* After the meeting, if A wants to send a message *m* to B, the following procedure must occur: 

	* A encrypts *m* by computing the ciphertext `c = E(S, m)` and sends c to B. 

* To read the encrypted message *c*, B must *decrypt* it via the decryption algorithm `D()`. 

	* Therefore, the plaintext message *p* can be computed by `p = D(S, c)`.

* With this idea, the adversary cannot compute *p* without knowing *S*. 