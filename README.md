# edge-covers

Given a nonnegative integer $N$, program `edge_covers` prints the table of
values $f(n,e)=\sum_k \binom nk (-1)^{n-k}\binom{\binom k2}e$ for $2\le n\le N$
and $n/2\le e\le\binom n2$, namely the number of ways to cover the vertices
of the complete graph $K_n$ using exactly $e$ edges. The program assumes
that $1+8\binom N2$ fits in a `uint`, which needs to be the case if it is
to terminate in a reasonable amount of time.

We use the [GMP library](https://gmplib.org/) to compute binomial coefficients
with multiple-precision arithmetic. The program takes about nine seconds to
count all the edge covers of the complete graphs on $2\le n\le 100$ vertices.
(For your convenience, these initial values are tabulated in the 103-megabyte
[`edge_covers100.txt`](edge_covers100.txt) file.) This isn't terribly bad, but
we would probably do better by avoiding repeated calculations of $\binom{\binom k2}e$
for different values of $n$. Another idea would be to apply the identity
```math
\binom{\binom k2}e=\frac{\binom k2^{\underline k}}{\left(\binom k2-e\right)^{\underline k}}
\binom{\binom{k-1}2}e,\quad e<\binom{k-1}2.
```
The [`mpz_bin_uiui`] routine is so fast that this approach gives no significant
improvement over the brute force method; see commit [`8fc8e1`]. Suggestions and
comments are welcome.

# License

This is free and unencumbered software released into the public domain.
See the [`LICENSE`](LICENSE) file for more details.

[`mpz_bin_uiui`]: https://gmplib.org/manual/Number-Theoretic-Functions#index-mpz_005fbin_005fuiui
[`8fc8e1`]: https://github.com/hsanzg/edge-covers/commit/8fc8e1be25fd491831f966ba03bd6a81d638bf7a