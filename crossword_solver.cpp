#include<bits/stdc++.h>
using namespace std;
#define ll long long int 
#define ii pair<int ,int >
#define pb push_back
#define range 
#define vi vector <int >
#define mod 1000000007
#define eps 1e-9
#define fi first
#define se second
#define _ <<" "<<
#define forn(x,	n) for(int x = 0; x < n ;++ x) 
#define forn1(x,n) for(int x = 1; x <= n ;++ x)
#define IOS ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0); 

void display(vector<vector<char> > v)
{
	forn1(i,v.size()-1)
	{
		forn1(j,v.size()-1)
			cout<<v[i][j];
		cout<<"\n";
	}
}

vector<pair<int,int> > set_clue(vector<vector<char> >& v)
{
	int n = v.size();
	vector<pair<int,int> > clue;
	clue.push_back({0,0});
	for(int i=1; i<v.size();i++)
	{
		for(int j=1; j<v.size();j++)
		{
			if((v[i][j]!='#')&&(i<n-1||j<n-1)&&((i>1&&i<n-1&&v[i-1][j]=='#'&&v[i+1][j]=='0')||(j>1&&j<n-1&&v[i][j-1]=='#'&&v[i][j+1]=='0')
				||(i==1&&v[i+1][j]=='0')||(j==1&&v[i][j+1]=='0')||(i==n-1&&v[i][j-1]=='#'&&v[i][j+1]=='0')
				||(j==n-1&&v[i-1][j]=='#'&&v[i+1][j]=='0')))
				{
					clue.push_back({i,j});
				}
		}
	}
	return clue;
}

void display_clue(vector<pair<int,int> >v)
{
	cout<<endl;
	for(auto& x:v)
	{
		cout<<x.first<<" "<<x.second;
		cout<<endl;
	}
}

vector<vector<char> >checkVertical(pair<int,int>& clue,
	vector<vector<char> > matrix, string word)
{
	int row = clue.first;
	int col = clue.second;
	int wordindex = 0;
	for(int i=row;i<matrix.size();i++)
	{
		if(wordindex>=word.size())
			break;
		if(matrix[i][col] == '0'|| matrix[i][col] == word[wordindex])
			{
				matrix[i][col] = word[wordindex];
			}
		else
			{
				matrix[0][0] = '@';
				return matrix;
			}
		wordindex++;
	}
	if(wordindex<word.size())
		matrix[0][0] = '@';
	return matrix;
}

vector<vector<char> >checkHorizontal(pair<int,int>& clue,
	vector<vector<char> > matrix, string word)
{

	int row = clue.first;
	int col = clue.second;
	int wordindex = 0;
	for(int j=col;j<matrix.size();j++)
	{
		if(wordindex>=word.size())
			break;
		if(matrix[row][j] == '0'|| matrix[row][j] == word[wordindex])
			{
				matrix[row][j] = word[wordindex];
			}
		else
			{
				matrix[0][0] = '@';
				return matrix;
			}
		wordindex++;
	}
	if(wordindex<word.size())
		matrix[0][0] = '@';
return matrix;
}

void solvePuzzle(vector<string>& words, 
                 vector<vector<char> > matrix, 
                 int index, int n, vector<pair<int,int> >& clue) 
{ 
    if(index < words.size())
    {
    	for(int k=1; k<clue.size(); k++)
    	{
    		auto temp = checkVertical(clue[k],matrix,words[index]);
    		if(temp[0][0]!='@')
    			solvePuzzle(words, temp, index + 1, n, clue);    		
    	}

    	for(int k=1; k<clue.size(); k++)
    	{
    		auto temp = checkHorizontal(clue[k],matrix,words[index]);
    		if(temp[0][0]!='@')
    			solvePuzzle(words, temp, index + 1, n, clue);    		
    	}
    }
    else
    {
    	display(matrix);
    	cout<<endl;
    	return;
    }
} 

int main(){
	IOS
	#ifndef ONLINE_JUDGE 
	//freopen("test.txt","r",stdin);
 	clock_t begin = clock();
	#endif

 	int n,m;
 	cin>>n;
 	vector<vector<char> >matrix(n+1,vector<char>(n+1,'0'));
 	int count = 0; 
 	matrix[0][0] = '!';
 	for(int k=1; k<=n; k++)
 	{
 		string temp;
 		cin>>temp;
 		std::stringstream ss(temp);
 		int indicator = 1;
 		int a,b;
    	for (int i; ss >> i;indicator*=-1) {
        	if (ss.peek() == ',')
            	ss.ignore();
            if(indicator==1)
            	a=i;
            else
            {
            	b = i;
            	if(a != 0 && b != 0)
            		for(int j=a;j < a+b;j++)
            			matrix[k][j] = '#';
            }
    	}
    	ss.flush();
 	}
 	auto clue = set_clue(matrix);
 	display(matrix);
 	cout<<endl;
 	display_clue(clue);
 	cin>>m;

 	vector<string> words;
 	string temp;
 	for(int i=0;i<m;i++)
 	{
 		cin>>temp;
 		words.push_back(temp);
 	}

 	solvePuzzle(words,matrix,0,(int)matrix.size(), clue);


	#ifndef ONLINE_JUDGE 
	clock_t end = clock();
	cout<<endl<<double(end - begin) / CLOCKS_PER_SEC;
	#endif 
	return 0;	
}