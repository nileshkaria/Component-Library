#include <iostream>
#include <vector>

using namespace std;

void printMatrix(const string               & p,
		 const string               & t,
		 const vector<vector<int> > & matrix)
{
  for(int j = 0; j <= t.size(); ++j)
  {
    if(j)
      cout << " " << t.at(j - 1);
    else
      cout << "   ";
  }

  cout << endl;

  for(int i = 0; i <= p.size(); ++i)
  {
    if(i)
      cout << p.at(i - 1) << " ";
    else
      cout << "  "; 

    for(int j = 0; j <= t.size(); ++j)
    {
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }
}

void longestCommonSubsequence(const string& p,
			      const string& t)
{
  vector<pair<int, int> > path;
  path.resize(p.size() + 1);

  vector<vector<int> >    matrix;  
  matrix.reserve(p.size() + 1);
    
  for(int i = 0; i <= p.size(); ++i)
  {
    vector<int> textRow(t.size() + 1, 0);
    matrix.push_back(textRow);
  }
  
  //Calculate edit distance
  for(int i = 1; i <= p.size(); ++i)
  {
    for(int j = 1; j <= t.size(); ++j)
    {
      if(p.at(i - 1) == t.at(j - 1))
      {
	matrix[i][j] = matrix[i - 1][j - 1] + 1;
	path.push_back(make_pair(i - 1, j -1));
      }
      else if(matrix[i - 1][j] >= matrix[i][j - 1])
      {
	matrix[i][j] = matrix[i - 1][j];
	path.push_back(make_pair(i - 1, j));
      }
      else
      {
	matrix[i][j] = matrix[i][j - 1];
	path.push_back(make_pair(i, j - 1));
      }
    }
  }

  //Print matrix
  printMatrix(p, t, matrix);
}

int main()
{
  string pattern("abcbdab");
  string text("bdcaba");

  longestCommonSubsequence(pattern, text);

  return 0;
}

