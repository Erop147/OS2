#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
void add(char *name, vector<int> &res)
{
	FILE *in = fopen(name, "r");
	if (in == NULL)
	{
		fprintf(stderr, "can't open file %s\n", name);
		return;
	}
	int num;
	try
    {
	    while (fscanf (in, "%d", &num) > 0)
    	{	
    		res.push_back(num);
	    }
		if (!feof(in))
	   	{
    		fprintf(stderr, "file %s contains non digit\n", name);
    	}
    
   	}
   	catch (exception e)
   	{
   		fprintf(stderr, "something wrong with vectors\n");
   	}
   	if (fclose(in))
   	{
   		fprintf(stderr, "can't close file %s \n", name);
   	}
}
int main(int argv, char* args[])
{
	vector<int> numbers;
	if (argv < 2)
	{
		fprintf(stderr, "Too few arguments");
		return 0;
	}
	for (int i = 1; i < argv; ++i)                       
	{
		add(args[i], numbers);
	}
	sort(numbers.begin(), numbers.end());
	for (vector<int>::iterator it = numbers.begin(); it != numbers.end(); ++it)
	{
		printf ("%d ", *it);
	}
	return 0; 
}