#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include "randombytes.h"




// Bare-metal / unknown OS on FVP:
// ⚠️ Deterministic test seed; replace with a secure seed source if available.
#include <string.h>
#include "fips202.h"
static uint64_t rng_counter = 0;  // increment each call
void esp_randombytes(uint8_t *out, size_t outlen) {
    uint8_t seed[32] = {0};    // test seed, can be host-provided in real use
    uint8_t shake_input[40];   // seed + counter

    memcpy(shake_input, seed, sizeof(seed));
    // append counter in little-endian
    for (int i = 0; i < 8; i++) {
        shake_input[32 + i] = (uint8_t)(rng_counter >> (8*i));
    }

    shake256(out, outlen, shake_input, sizeof(shake_input));
    rng_counter++;
}


/*
#ifdef _WIN32
#include <windows.h>
#include <wincrypt.h>
#else
#include <fcntl.h>
#include <errno.h>
#ifdef __linux__
#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#elif __NetBSD__
#include <sys/random.h>
#else
#include <unistd.h>
#endif
#endif

#ifdef _WIN32
void esp_randombytes(uint8_t* out, size_t outlen) {
    HCRYPTPROV ctx;
    size_t len;

    if (!CryptAcquireContext(&ctx, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
        abort();

    while (outlen > 0) {
        len = (outlen > 1048576) ? 1048576 : outlen;
        if (!CryptGenRandom(ctx, len, (BYTE*)out))
            abort();

        out += len;
        outlen -= len;
    }

    if (!CryptReleaseContext(ctx, 0))
        abort();
}
#elif defined(__linux__) && defined(SYS_getrandom)
void esp_randombytes(uint8_t* out, size_t outlen) {
    ssize_t ret;

    while (outlen > 0) {
        ret = syscall(SYS_getrandom, out, outlen, 0);
        if (ret == -1 && errno == EINTR)
            continue;
        else if (ret == -1)
            abort();

        out += ret;
        outlen -= ret;
    }
}
#elif defined(__NetBSD__)
void esp_randombytes(uint8_t* out, size_t outlen) {
    ssize_t ret;

    while (outlen > 0) {
        ret = getrandom(out, outlen, 0);
        if (ret == -1 && errno == EINTR)
            continue;
        else if (ret == -1)
            abort();

        out += ret;
        outlen -= ret;
    }
}
#else
void esp_randombytes(uint8_t* out, size_t outlen) {
    static int fd = -1;
    ssize_t ret;

    while (fd == -1) {
        fd = open("/dev/urandom", O_RDONLY);
        if (fd == -1 && errno == EINTR)
            continue;
        else if (fd == -1)
            abort();
    }

    while (outlen > 0) {
        ret = read(fd, out, outlen);
        if (ret == -1 && errno == EINTR)
            continue;
        else if (ret == -1)
            abort();

        out += ret;
        outlen -= ret;
    }
}
#endif
*/
