#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Check if bomb is inside the radius of the center bomb
bool isBombInRadius(vector<int> &bomb, vector<int> &centerBomb)
{
  long centerX = centerBomb[0];
  long centerY = centerBomb[1];
  long R = centerBomb[2];

  long X = bomb[0];
  long Y = bomb[1];

  return (X - centerX) * (X - centerX) + (Y - centerY) * (Y - centerY) <= R * R;
}

// Depth-first search
void dfs(int i, vector<bool> &detonated, vector<int> graph[])
{
  detonated[i] = true;
  for (int x : graph[i])
  {
    if (!detonated[x])
    {
      dfs(x, detonated, graph);
    }
  }
}
// Find the maximum detonation for a vector of bombs
int maximumDetonation(vector<vector<int>> &bombs)
{
  // Number of the bombs
  int n = bombs.size();

  // Graph of possible detonations
  vector<int> graph[n];

  for (int i = 0; i < n; i++)
  {
    vector<int> bomb = bombs[i];
    for (int j = 0; j < n; j++)
    {
      if (i != j)
      {
        vector<int> otherBomb = bombs[j];

        if (isBombInRadius(otherBomb, bomb))
        {
          graph[i].push_back(j);
        }
      }
    }
  }

  // Detonated bombs
  vector<bool> detonated(n);
  int maxDetonation = 0;

  for (int i = 0; i < n; i++)
  {
    if (maxDetonation == bombs.size())
      return maxDetonation;

    dfs(i, detonated, graph);
    int detonations = false;

    for (int j = 0; j < n; j++)
      if (detonated[j])
        detonations++;

    maxDetonation = max(maxDetonation, detonations);
    fill(detonated.begin(), detonated.end(), false);
  }

  return maxDetonation;
}

int main()
{
  vector<vector<int>> bombs1 = {{2, 1, 3}, {6, 1, 4}};
  vector<vector<int>> bombs2 = {{1, 1, 5}, {10, 10, 5}};
  vector<vector<int>> bombs3 = {{1, 2, 3}, {2, 3, 1}, {3, 4, 2}, {4, 5, 3}, {5, 6, 4}};
  vector<vector<int>> bombs4 = {{1000, 1000, 1}, {1, 1, 1000}};

  cout << maximumDetonation(bombs1) << " = 2" << endl;
  cout << maximumDetonation(bombs2) << " = 1" << endl;
  cout << maximumDetonation(bombs3) << " = 5" << endl;
  cout << maximumDetonation(bombs4) << " = 1" << endl;

  return 0;
}