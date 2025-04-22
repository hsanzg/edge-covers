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

mpz_t n_choose_k, k_2_choose_e;

void f(mpz_ptr res, const uint n, const uint e) {
  mpz_set_ui(res, 0);
  uint k = (1 + (uint) sqrt(1 + 8 * e)) / 2, k_choose_2 = k * (k - 1) / 2;
  if (k_choose_2 < e) k_choose_2 += k++; // apply ceiling.
  for (; k <= n; k_choose_2 += k++) {
    mpz_bin_uiui(n_choose_k, n, k);
    mpz_bin_uiui(k_2_choose_e, k_choose_2, e);
    if ((n - k) & 1) mpz_neg(n_choose_k, n_choose_k);
    mpz_addmul(res, n_choose_k, k_2_choose_e);
  }
}

int main(const int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "usage: %s <max n>\n", argv[0]);
    return 1;
  }
  const uint N = strtoul(argv[1], NULL, 0);
  mpz_t res; mpz_inits(n_choose_k, k_2_choose_e, res, NULL);
  for (uint n = 1, e_max = 0; n <= N; e_max += n++)
    for (uint e = (n + 1) / 2; e <= e_max; ++e) {
      f(res, n, e);
      mpz_out_str(stdout, 10, res);
      putchar(e < e_max ? ',' : '\n');
    }
  return 0;
}