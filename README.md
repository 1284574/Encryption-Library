# Encryption-Library
Encryption Library in C. Uses the RC4 Cipher. RC4 Cipher - stream cipher and variable-length key algorithm. The algorithm encrypts one byte at a time. A key is a pseudorandom bit generator that produces a stream 8-bit number that is unpredictable without knowledge of input key, output is key-stream and is combined one byte at a time with XOR.

3 functions in library:
rc4init(key), rc4encrypt(text), rc4decrypt(), rc4unint()

RC4 basic algorithm:
for i from 0 to 255
    S[i] := i
endfor
j := 0
for i from 0 to 255
    j := (j + S[i] + key[i mod keylength]) mod 256
    swap values of S[i] and S[j]
endfor