#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define PAGES 10
#define LINES_PER_PAGE 40
#define CHARS_PER_LINE 80

static const char SYMBOLS[] = "abcdefghijklmnopqrstuvwxyz ,.!?";

// FNV-1a 64bit hash pro seed
uint64_t fnv1a_64(const char *s) {
    uint64_t hash = 0xcbf29ce484222325ULL;
    while (*s) {
        hash ^= (unsigned char)(*s++);
        hash *= 0x100000001b3ULL;
    }
    return hash;
}

// jednoduchý xorshift64*
uint64_t xorshift64(uint64_t *state) {
    uint64_t x = *state;
    x ^= x >> 12;
    x ^= x << 25;
    x ^= x >> 27;
    *state = x;
    return x * 2685821657736338717ULL;
}

size_t symbols_len(void) {
    return strlen(SYMBOLS);
}

void generate_book(const char *address, FILE *out) {
    uint64_t state = fnv1a_64(address);
    size_t sym_len = symbols_len();

    for (int p = 0; p < PAGES; ++p) {
        fprintf(out, "=== PAGE %d/%d ===\n", p + 1, PAGES);
        for (int l = 0; l < LINES_PER_PAGE; ++l) {
            for (int c = 0; c < CHARS_PER_LINE; ++c) {
                uint64_t r = xorshift64(&state);
                char ch = SYMBOLS[r % sym_len];
                fputc(ch, out);
            }
            fputc('\n', out);
        }
        fputc('\n', out);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Použití: %s \"adresa_knihy\" [soubor.txt]\n", argv[0]);
        return 1;
    }

    const char *address = argv[1];

    if (argc >= 3) {
        const char *filename = argv[2];
        FILE *f = fopen(filename, "w");
        if (!f) {
            perror("Nelze otevřít výstupní soubor");
            return 1;
        }
        generate_book(address, f);
        fclose(f);
        printf("Kniha pro adresu '%s' ulozena do %s\n", address, filename);
    } else {
        generate_book(address, stdout);
    }

    return 0;
}