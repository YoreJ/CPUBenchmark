#include "SHA_256.h"
#define ROUNDS 1ULL 

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

#define ROTRIGHT(word, bits) (((word) >> (bits)) | ((word) << (32 - (bits))))
#define CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (ROTRIGHT(x, 2) ^ ROTRIGHT(x, 13) ^ ROTRIGHT(x, 22))
#define EP1(x) (ROTRIGHT(x, 6) ^ ROTRIGHT(x, 11) ^ ROTRIGHT(x, 25))
#define SIG0(x) (ROTRIGHT(x, 7) ^ ROTRIGHT(x, 18) ^ ((x) >> 3))
#define SIG1(x) (ROTRIGHT(x, 17) ^ ROTRIGHT(x, 19) ^ ((x) >> 10))

static const uint32_t K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

static void sha256_transform(hash_context* ctx, const uint8_t data[]) {
    uint32_t a, b, c, d, e, f, g, h, i, j, t1, t2, m[64];

    for (i = 0, j = 0; i < 16; ++i, j += 4)
        m[i] = (data[j] << 24) | (data[j + 1] << 16) | (data[j + 2] << 8) | (data[j + 3]);
    for (; i < 64; ++i)
        m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[i - 16];

    a = ctx->state[0];
    b = ctx->state[1];
    c = ctx->state[2];
    d = ctx->state[3];
    e = ctx->state[4];
    f = ctx->state[5];
    g = ctx->state[6];
    h = ctx->state[7];

    for (i = 0; i < 64; ++i) {
        t1 = h + EP1(e) + CH(e, f, g) + K[i] + m[i];
        t2 = EP0(a) + MAJ(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }

    ctx->state[0] += a;
    ctx->state[1] += b;
    ctx->state[2] += c;
    ctx->state[3] += d;
    ctx->state[4] += e;
    ctx->state[5] += f;
    ctx->state[6] += g;
    ctx->state[7] += h;
}

void hash_start(hash_context* ctx) {
    ctx->state[0] = 0x6a09e667;
    ctx->state[1] = 0xbb67ae85;
    ctx->state[2] = 0x3c6ef372;
    ctx->state[3] = 0xa54ff53a;
    ctx->state[4] = 0x510e527f;
    ctx->state[5] = 0x9b05688c;
    ctx->state[6] = 0x1f83d9ab;
    ctx->state[7] = 0x5be0cd19;

    ctx->total[0] = 0;
    ctx->total[1] = 0;
}

void hash_update(hash_context* ctx, uint8_t* input, size_t ilen) {
    size_t fill;
    uint32_t left;

    if (ilen == 0)
        return;

    left = ctx->total[0] & 0x3F;
    fill = 64 - left;

    ctx->total[0] += (uint32_t)ilen;
    ctx->total[0] &= 0xFFFFFFFF;

    if (ctx->total[0] < (uint32_t)ilen)
        ctx->total[1]++;

    if (left && ilen >= fill) {
        memcpy((void*)(ctx->buffer + left), input, fill);
        sha256_transform(ctx, ctx->buffer);
        input += fill;
        ilen -= fill;
        left = 0;
    }

    while (ilen >= 64) {
        sha256_transform(ctx, input);
        input += 64;
        ilen -= 64;
    }

    if (ilen > 0) {
        memcpy((void*)(ctx->buffer + left), input, ilen);
    }
}

void hash_finish(hash_context* ctx, uint8_t* output) {
    uint32_t last, padn;
    uint32_t high, low;
    uint8_t msglen[8];
    high = (ctx->total[0] >> 29) | (ctx->total[1] << 3);
    low = (ctx->total[0] << 3);

    msglen[0] = (uint8_t)(high >> 24);
    msglen[1] = (uint8_t)(high >> 16);
    msglen[2] = (uint8_t)(high >> 8);
    msglen[3] = (uint8_t)(high);
    msglen[4] = (uint8_t)(low >> 24);
    msglen[5] = (uint8_t)(low >> 16);
    msglen[6] = (uint8_t)(low >> 8);
    msglen[7] = (uint8_t)(low);

    last = ctx->total[0] & 0x3F;
    padn = (last < 56) ? (56 - last) : (120 - last);

    hash_update(ctx, (uint8_t*)"\x80", 1);
    hash_update(ctx, (uint8_t*)(msglen + 1), padn - 1);
    hash_update(ctx, msglen, 8);

    for (int i = 0; i < 8; i++) {
        output[i * 4] = (uint8_t)(ctx->state[i] >> 24);
        output[i * 4 + 1] = (uint8_t)(ctx->state[i] >> 16);
        output[i * 4 + 2] = (uint8_t)(ctx->state[i] >> 8);
        output[i * 4 + 3] = (uint8_t)(ctx->state[i]);
    }
}

Tuple HashTest(int Size, PerfCounter& pc)
{
    pc.reset();
    const unsigned int NUM_THREADS = std::thread::hardware_concurrency(); // Get the number of available threads
    const unsigned long long TOTAL_ROUNDS = ROUNDS * NUM_THREADS; // Total rounds for all threads

    hash_context ctx;

    uint8_t hash[32]; // SHA-256 输出长度为 32 字节
    clock_t start, end;

    // 初始化随机数生成器
    srand(static_cast<unsigned int>(time(NULL)));

    uint8_t* data = (uint8_t*)malloc(Size); // 分配数据缓冲区

    // 生成随机数据填充到 data 数组中
    for (unsigned long long i = 0; i < Size; i++) // 使用 unsigned long long
    {
        data[i] = rand() & 0xFF;
    }

    std::vector<std::thread> threads;
    pc.start();
    for (unsigned int t = 0; t < NUM_THREADS; ++t) {
        threads.emplace_back([&, data]() { // Capture all local variables by reference
            hash_context local_ctx = ctx; // Create a local copy of ctx for each thread
            for (unsigned long long i = 0; i < ROUNDS; i++) {
                hash_start(&local_ctx);
                hash_update(&local_ctx, data, Size);
                hash_finish(&local_ctx, hash);
            }
            });
    }

    for (auto& thread : threads) {
        thread.join();
    }
    free(data);
    return pc.stop();
}