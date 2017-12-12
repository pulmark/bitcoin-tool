#ifndef BITCOIN_INCLUDE_COMBINATION_H
#define BITCOIN_INCLUDE_COMBINATION_H

#ifdef __cplusplus
extern "C" {
#endif

struct Combination {
  int n;  /* total number of elements */
  int r;  /* number of elements to select from total */
  int *k; /* current state */
};

void Combination_create(struct Combination *c, int n, int r);
void Combination_destroy(struct Combination *c);
int Combination_next(struct Combination *c);

#ifdef __cplusplus
}
#endif

#endif
