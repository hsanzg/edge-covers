# edge-covers

Given a nonnegative integer $N$, program `edge_covers` prints the table of
values $f(n,e)=\sum_k \binom nk (-1)^{n-k}\binom{\binom k2}e$ for $2\le n\le N$
and $n/2\le e\le\binom n2$, namely the number of ways to cover the vertices
of the complete graph $K_n$ using exactly $e$ edges. The program assumes
that $\binom N2$ fits in a `ulong`, which needs to be the case if it is
to terminate in a reasonable amount of time.

We use the [GMP library](https://gmplib.org/) to compute binomial coefficients
with multiple-precision arithmetic. The program takes about ten seconds to
count all the edge covers of the complete graph on $2\le n\le 100$ vertices.
This isn't terribly bad, but we would probably do better by avoiding repeated
calculations of $\binom{\binom k2}e$ for different values of $n$.

# License

This is free and unencumbered software released into the public domain.
See the [LICENSE] file for more details.