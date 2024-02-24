Introduction
---
This project implements a text encryption and decryption system using a matrix-based encryption technique. This project serves as an educational and practical exploration of matrix-based encryption techniques, demonstrating the fundamental concepts of encryption and decryption in a user-friendly manner.

# Encryption Algorithm

## Convert Input String to ASCII Integer

### 1- Initialization
Given an input string $S$ of length $n$, where $S = s_1 s_2 s_3 \ldots s_n$, and each $s_i$ represents a character in the string.\
Initialize an empty vector $\text{parsed}$ to store the ASCII integer representations of characters extracted from the input string $S$.

Consider the input string $S = \text{"Hello World"}$. Here's how the algorithm works:\
Initialize $\text{parsed} = []$.

### 2 - Token Extraction
Extract tokens (words) from the input string $S$. Let $T_1, T_2, \ldots, T_m$ be the tokens extracted from $S$, where $m$ is the number of tokens.

Extract tokens: $T_1 = \text{"Hello"}$ and $T_2 = \text{"World"}$.

### 3- Character Processing for Token $T_i$
For each token $T_i$, consisting of characters $t_{i1}, t_{i2}, \ldots, t_{ik}$, where $k$ is the length of the token:\
Convert each character $t_{ij}$ to its ASCII integer representation $a_{ij}$.\
Add each $a_{ij}$ to end of the $parsed$ vector. 

Convert 'H' to ASCII integer $72$, 'e' to $101$, 'l' to $108$, 'l' to $108$, 'o' to $111$.\
Add these integers to $\text{parsed}$: $[72, 101, 108, 108, 111]$.

### 4- Adding Space
After processing each character in a token $T_i$, add a space character ' ' to the $parsed$ vector.

 Add a space ' ' to $\text{parsed}$.

### 5- End of Token
Repeat steps 3-4 for all tokens $T_1, T_2, \ldots, T_m$.

Process characters for $T_2$:\
Convert 'W' to ASCII integer $87$, 'o' to $111$, 'r' to $114$, 'l' to $108$, 'd' to $100$.\
Add these integers to $\text{parsed}$: $[87, 111, 114, 108, 100]$.\
Add a space ' ' to $\text{parsed}$.\
Return $\text{parsed} = [72, 101, 108, 108, 111, 32, 87, 111, 114, 108, 100, 32]$.

### 6- Return Result
The function returns the $\text{parsed}$ vector containing ASCII integer representations of characters in $S$, with spaces after each token.


