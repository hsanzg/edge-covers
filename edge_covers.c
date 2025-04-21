#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>

// Given a nonnegative integer $N$, this program prints the table of values
// $f(n,e)=\sum_k \binom nk (-1)^{n-k}\binom{\binom k2}e$ for $2\le n\le N$
// and $n/2\le e\le\binom n2$, namely the number of ways to cover the vertices
// of the complete graph $K_n$ using exactly $e$ edges. The program assumes
// that $1+8\binom N2$ fits in a `uint`, which needs to be the case if it is
// to terminate in a reasonable amount of time.

#define MIN(a,b) (((a)<(b))?(a):(b))

int main(const int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "usage: %s <max n>\n", argv[0]);
    return 1;
  }
  const uint N = strtoul(argv[1], NULL, 0);
  mpz_t res, term, k_2_choose_e; mpz_inits(res, term, NULL), mpz_init_set_ui(k_2_choose_e, 1);
  for (uint n = 1, e_max = 0; n <= N; e_max += n, ++n) {
    for (uint e = (n + 1) / 2; e <= e_max; ++e) {
      uint k = (1 + sqrt(1 + 8 * e)) / 2, k_choose_2 = k * (k - 1) / 2;
      if (k_choose_2 < e) k_choose_2 += k++; // apply ceiling.
      for (; k <= n; k_choose_2 += k++) {
        for (uint j = 0; j < MIN(k_choose_2 - e, k - 1); ++j) {
          mpz_mul_ui(k_2_choose_e, k_2_choose_e, k_choose_2 - j);
          mpz_divexact_ui(k_2_choose_e, k_2_choose_e, k_choose_2 - j - e);
        }
        //mpz_bin_uiui(k_2_choose_e, k_choose_2, e);
        mpz_bin_uiui(term, n, k);
        ((n - k) & 1 ? mpz_submul : mpz_addmul)(res, term, k_2_choose_e);
      }
      mpz_out_str(stdout, 10, res);
      mpz_set_ui(res, 0), mpz_set_ui(k_2_choose_e, 1);
      putchar(e < e_max ? ',' : '\n');
    }
  }
  return 0;
}