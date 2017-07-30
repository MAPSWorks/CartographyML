#include "rand_p.h"

#include <cstdlib>
#include <cmath>

#include "rand_salt_p.h"

inline quint64 permuteWhole(quint64 n, quint64 a, quint64 b)
{
  return ((n * a) + b);
}

inline quint64 part(quint64 n1, quint64 n2, int p)
{
  int b = p * 8;
  int i = (n1 >> b) & 0xFF;
  int j = (n2 >> b) & 0xFF;
  return quint64(salt[i][j]) << b;
}


quint64 random64At(qint64 x, qint64 y, qint64 seed)
{
  const quint64 kxa = 427140578808118991LL;
  const quint64 kya = 166552399647317237LL;
  const quint64 kxb = 48058817213113801LL;
  const quint64 kyb = 9206429469018994469LL;

  // Generate salts
  quint64 n1 = (quint64(x + 5) * kxa) * seed;
  quint64 n2 = (quint64(y + 7) * kya) + (seed * 1040097393733LL);
  n1 = permuteWhole(n1, 8759824322359LL, 13);
  n2 = permuteWhole(n2, 200560490131LL, 2707);
  n1 = (n1 >> 32) ^ (n1 << 32);
  n2 = (n2 >> 32) ^ (n2 << 32);
  n1 ^= x ^ (quint64(y ^ seed) * kyb);
  n2 ^= y ^ (quint64(x + 13)   * kxb);

  // Combine salts
  quint64 v = 0;
  for (int p = 0; p < 8; ++p)
      v |= part(n1, n2, p);
  return v;
}

namespace TerrainML {
  namespace Random
  {
    float floatRandomAt(qint32 x, qint32 y, qint32 seed)
    {
      quint64 r = random64At(x, y, seed);
      float v = r / (float)UINT64_MAX;
      return v;
    }

    qint32 intRandomAt(qint32 x, qint32 y, qint32 seed)
    {
      return random64At(x, y, seed);
    }
  }
}

