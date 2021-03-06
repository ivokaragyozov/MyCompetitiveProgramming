/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi�zanie zadania: SZK (Szko�y)                                   *
 *   Plik:                szk.cpp                                        *
 *   Autor:               Pawe� Parys                                    *
 *   Opis:                                                               *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>

#define REP(a,n) for (int a=0; a<(n); ++a)
#define FOR(a,l,h) for (int a=(l); a<=(h); ++a)

using namespace std;

#define SIZE 200    // maximal number of schools
#define INF 1000000000

int N, cur[SIZE], low[SIZE], high[SIZE], score[SIZE];

int sch_match[SIZE], pos_match[SIZE];

int dist[SIZE], back[SIZE];
bool changed[SIZE];

inline int cost(int s, int p)
{
  return abs(cur[s]-p)*score[s];
}

void go_from_school(int s, int d)
{
  FOR(a, low[s], high[s])
    if (a!=sch_match[s])
    {
      int d2 = d+cost(s, a);
      if (d2<dist[a])
      {
        dist[a] = d2;
        back[a] = s;
        changed[a] = true;
      }
    }
}

int find_path()
{
  int ret = -1, retval = INF;
  REP(a, N)
  {
    dist[a] = INF;
    changed[a] = false;
  }
  REP(a, N)
    if (sch_match[a]<0)
      go_from_school(a, 0);
  for (;;)
  {
    bool theend = true;
    REP(a, N)
    {
      if (!changed[a]) continue;
      if (pos_match[a]<0 && dist[a]<retval)
        retval = dist[ret = a];
      changed[a] = false;
      if (pos_match[a]<0) continue;
      go_from_school(pos_match[a], dist[a]-cost(pos_match[a], a));
      theend = false;
    }
    if (theend) break;
  }
  return ret;
}

void extend(int p)
{
  while (p>=0)
  {
    int s = back[p];
    pos_match[p] = s;
    int pp = sch_match[s];
    sch_match[s] = p;
    p = pp;
  }
}

int main()
{
  scanf("%d", &N);
  REP(a,N)
  {
    scanf("%d%d%d%d", cur+a, low+a, high+a, score+a);
    --cur[a]; --low[a]; --high[a];
    sch_match[a] = pos_match[a] = -1;
  }
  REP(a, N)
  {
    int b = find_path();
    if (b<0)
    {
      printf("NIE\n");
      return 0;
    }
    extend(b);
  }
  int k = 0;
  REP(a, N)
    k += cost(a, sch_match[a]);
  printf("%d\n", k);
}
