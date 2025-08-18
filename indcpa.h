#ifndef INDCPA_H
#define INDCPA_H

#include <stdint.h>
#include "params.h"
#include "polyvec.h"

#define gen_matrix KYBER_NAMESPACE(gen_matrix)
void gen_matrix(polyvec *a, const uint8_t seed[KYBER_SYMBYTES], int transposed);
#define indcpa_keypair KYBER_NAMESPACE(indcpa_keypair)
void indcpa_keypair(uint8_t pk[KYBER_INDCPA_PUBLICKEYBYTES],
                    uint8_t sk[KYBER_INDCPA_SECRETKEYBYTES]);

#define indcpa_enc KYBER_NAMESPACE(indcpa_enc)
void indcpa_enc(uint8_t c[KYBER_INDCPA_BYTES],
                const uint8_t m[KYBER_INDCPA_MSGBYTES],
                const uint8_t pk[KYBER_INDCPA_PUBLICKEYBYTES],
                const uint8_t coins[KYBER_SYMBYTES]);

#define indcpa_dec KYBER_NAMESPACE(indcpa_dec)
void indcpa_dec(uint8_t m[KYBER_INDCPA_MSGBYTES],
                const uint8_t c[KYBER_INDCPA_BYTES],
                const uint8_t sk[KYBER_INDCPA_SECRETKEYBYTES]);


//#define gen_at(A,B) gen_matrix(A,B,1)
//void gen_matrix(polyvec* a, const uint8_t seed[KYBER_SYMBYTES], int transposed);

#define pack_pk KYBER_NAMESPACE(pack_pk)
static void pack_pk(uint8_t r[KYBER_INDCPA_PUBLICKEYBYTES],
    polyvec* pk,
    const uint8_t seed[KYBER_SYMBYTES]);

#define unpack_pk KYBER_NAMESPACE(unpack_pk)
static void unpack_pk(polyvec* pk,
    uint8_t seed[KYBER_SYMBYTES],
    const uint8_t packedpk[KYBER_INDCPA_PUBLICKEYBYTES]);


//#define pack_ciphertext_uc KYBER_NAMESPACE(pack_ciphertext_uc)
//static void pack_ciphertext_uc(uint8_t r[KYBER_INDCPA_BYTES_UC], polyvec* b, poly* v);




#endif
