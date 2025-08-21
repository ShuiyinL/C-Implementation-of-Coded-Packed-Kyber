#ifndef PARAMS_H
#define PARAMS_H

#ifndef KYBER_K
#define KYBER_K 4	/* Change this for different security strengths */
#endif

/* MMSE_Q_MODE: Only applied to the proposed P_Kyber Scheme; doesn't affect the original Kyber*/
#ifndef MMSE_Q_MODE
#define MMSE_Q_MODE 'F'
/*T: Quantize both u and v with MMSE quantization: Q_mmse(u,2^du), Q_mmse(v,2^dv) */
/*F: Quantize both u and v with original Kyber quantization: compress(u,2^du),compress(v,2^dv) **/
#endif


#define Compress_More 'T'
/*T: using smaller compression parameter of KYBER1024: du=10,dv=4 */
/*F: using the original compression parameter of KYBER1024: du=11,dv=5 */

#define LATTICE_DIM 8    //value of L in P_L Kyber; set L = 8 for testing E8 encoder and decoder

//#define KYBER_90S	/* Uncomment this if you want the 90S variant */

/* Don't change parameters below this line */
#if   (KYBER_K == 2)
#ifdef KYBER_90S
#define KYBER_NAMESPACE(s) pqcrystals_kyber512_90s_ref_##s
#else
#define KYBER_NAMESPACE(s) pqcrystals_kyber512_ref_##s
#endif
#elif (KYBER_K == 3)
#ifdef KYBER_90S
#define KYBER_NAMESPACE(s) pqcrystals_kyber768_90s_ref_##s
#else
#define KYBER_NAMESPACE(s) pqcrystals_kyber768_ref_##s
#endif
#elif (KYBER_K == 4)
#ifdef KYBER_90S
#define KYBER_NAMESPACE(s) pqcrystals_kyber1024_90s_ref_##s
#else
#define KYBER_NAMESPACE(s) pqcrystals_kyber1024_ref_##s
#endif
#else
#error "KYBER_K must be in {2,3,4}"
#endif

#define KYBER_N 256
#define KYBER_Q 3329


#define KYBER_Q_INV (1.0f / KYBER_Q)  // precomputed

#define KYBER_SYMBYTES 32   /* size in bytes of hashes, and seeds */
#define KYBER_SYMBYTES_LD (LATTICE_DIM * KYBER_SYMBYTES)

#define KYBER_SSBYTES  32   /* size in bytes of shared key */

#define KYBER_POLYBYTES		384
#define KYBER_POLYVECBYTES	(KYBER_K * KYBER_POLYBYTES)

#if KYBER_K == 2
#define KYBER_ETA1 3
#define KYBER_POLYCOMPRESSEDBYTES    128
#define KYBER_POLYVECCOMPRESSEDBYTES (KYBER_K * 320)

#define KYBER_POLYCOMPRESSEDBYTES_LD    (LATTICE_DIM *128)
#define KYBER_POLYVECCOMPRESSEDBYTES_LD (KYBER_K * 320)


#elif KYBER_K == 3
#define KYBER_ETA1 2
//compresson parameters
#define KYBER_POLYCOMPRESSEDBYTES    128
#define KYBER_POLYVECCOMPRESSEDBYTES (KYBER_K * 320)

#define KYBER_POLYCOMPRESSEDBYTES_LD    (LATTICE_DIM *128)
#define KYBER_POLYVECCOMPRESSEDBYTES_LD (KYBER_K * 320)


#elif KYBER_K == 4
#define KYBER_ETA1 2


#if (Compress_More =='F')

#define KYBER_POLYCOMPRESSEDBYTES    160
#define KYBER_POLYVECCOMPRESSEDBYTES (KYBER_K * 352)

#define KYBER_POLYCOMPRESSEDBYTES_LD    (LATTICE_DIM *160)
#define KYBER_POLYVECCOMPRESSEDBYTES_LD (KYBER_K * 352)
#else

#define KYBER_POLYCOMPRESSEDBYTES    128
#define KYBER_POLYVECCOMPRESSEDBYTES (KYBER_K * 320)

#define KYBER_POLYCOMPRESSEDBYTES_LD    (LATTICE_DIM *128)
#define KYBER_POLYVECCOMPRESSEDBYTES_LD (KYBER_K * 320)

#endif

#endif

#define KYBER_ETA2 2

#define KYBER_INDCPA_MSGBYTES       (KYBER_SYMBYTES)
#define KYBER_INDCPA_MSGBYTES_LD       (LATTICE_DIM *KYBER_SYMBYTES)

#define KYBER_INDCPA_PUBLICKEYBYTES (KYBER_POLYVECBYTES + KYBER_SYMBYTES)
#define KYBER_INDCPA_PUBLICKEYBYTES_LD (LATTICE_DIM * KYBER_POLYVECBYTES + KYBER_SYMBYTES)

#define KYBER_INDCPA_SECRETKEYBYTES (KYBER_POLYVECBYTES)
#define KYBER_INDCPA_SECRETKEYBYTES_LD (LATTICE_DIM * KYBER_POLYVECBYTES)

#define KYBER_INDCPA_BYTES          (KYBER_POLYVECCOMPRESSEDBYTES + KYBER_POLYCOMPRESSEDBYTES)
#define KYBER_INDCPA_BYTES_LD          (KYBER_POLYVECCOMPRESSEDBYTES_LD + KYBER_POLYCOMPRESSEDBYTES_LD)


#define KYBER_PUBLICKEYBYTES  (KYBER_INDCPA_PUBLICKEYBYTES)
#define KYBER_PUBLICKEYBYTES_LD  (KYBER_INDCPA_PUBLICKEYBYTES_LD)

/* 32 bytes of additional space to save H(pk) */
#define KYBER_SECRETKEYBYTES  (KYBER_INDCPA_SECRETKEYBYTES + KYBER_INDCPA_PUBLICKEYBYTES + 2*KYBER_SYMBYTES)
#define KYBER_SECRETKEYBYTES_LD  (KYBER_INDCPA_SECRETKEYBYTES_LD + KYBER_INDCPA_PUBLICKEYBYTES_LD + 2*KYBER_SYMBYTES)

#define KYBER_CIPHERTEXTBYTES (KYBER_INDCPA_BYTES)
#define KYBER_CIPHERTEXTBYTES_LD (KYBER_INDCPA_BYTES_LD)


#endif
