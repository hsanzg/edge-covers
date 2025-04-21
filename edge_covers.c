#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

// Given a nonnegative integer $N$, this program prints the table of values
// $f(n,e)=\sum_k \binom nk (-1)^{n-k}\binom{\binom k2}e$ for $2\le n\le N$
// and $n/2\le e\le\binom n2$, namely the number of ways to cover the vertices
// of the complete graph $K_n$ using exactly $e$ edges. The program assumes
// that $\binom N2$ fits in a `ulong`, which needs to be the case if it is
// to terminate in a reasonable amount of time.

int main(const int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "usage: %s <max n>\n", argv[0]);
    return 1;
  }
  const ulong N = strtoul(argv[1], NULL, 0);
  mpz_t res, term, n_choose_k; mpz_inits(res, term, n_choose_k, NULL);
  for (ulong n = 1, e_max = 0; n <= N; e_max += n, ++n) {
    for (ulong e = (n + 1) / 2; e <= e_max; ++e) {
      for (ulong k = 0, k_choose_2 = 0; k <= n; k_choose_2 += k, ++k) {
        mpz_bin_uiui(term, k_choose_2, e);
        mpz_bin_uiui(n_choose_k, n, k);
        (n - k & 1 ? mpz_submul : mpz_addmul)(res, term, n_choose_k);
      }
      mpz_out_str(stdout, 10, res), mpz_set_ui(res, 0);
      putchar(e < e_max ? ',' : '\n');
    }
  }
  return 0;
}