# C Implementation of Coded/Uncoded P-Kyber with MMSE/Kyber Quantization
Flatform: Arm FVP (installed with Arm DS) with MPS2_Cortex_M4

The code is based on the official Kyber reference implementation: https://github.com/pq-crystals/kyber

- P_Kyber_Test.c
  - This main file contains all sub-functions used in P_Kyber PKE and KEM.
  - Extra global parameters are defined in params.h.
- randombytes.c
  - Because FVP runs on bare-metal or an undefined OS, randombytes.c currently uses a deterministic test seed for testing only.
  - A secure seed source must be used when available.

Performance Comparison: Original Kyber KEM vs. P-Kyber KEM in 8 AES Key Exchanges:

| Method                 | KeyGen (CPU Clock Cycles)| Enc (CPU Clock Cycles) | Dec (CPU Clock Cycles) |Ciphertext Size (bytes) |Decryption Failure Rate |
|----------------------- |--------------------------|------------------------|------------------------|------------------------|------------------------|
| KYBER1024 (8 calls)    | 3,330,736                | 4,040,784              | 4,272,704              |12544                   | 2^{-174}               |
| Uncoded P_8-KYBER1024  | 1,982,539                | 1,710,068              | 1,782,147              |2688                    | 2^{-187}               |
| E8 Coded P_8-KYBER1024 | 1,982,490                | 1,713,772              | 1,977,249              |2688                    | 2^{-336}               |
 
