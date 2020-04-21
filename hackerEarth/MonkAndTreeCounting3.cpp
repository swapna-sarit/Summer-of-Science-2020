#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


int tree_height(int left[], int right[], int curr_node);

void tree_to_array(int tree_array[], int array_size, int curr_arr_pos, int curr_node, int node_val[], int left_of[], int right_of[]);

int num_of_triplets(int K, int tree_array[], int array_size, int curr_pose, int node_val[]);




int main() 
{

	// Variable Declaration
	int N;  // N : No. of nodes
	int K;  // K : Value of K
	int node_val[N + 1]; // node_val[i] is value of node no. i
	int parent_of[N + 1]; // parent_of[i] is node number of parent of node no. i
	int left_of[N + 1]; // left_of[i] is node number of left child of node no. i
	int right_of[N + 1]; // right_of[i] is node number of right child of node no. i
	
	
	// Taking in Test Case Values 
	cin >> N;
	cin >> K;	

    // If I put lines 22-25 here, then (left_of + 1) is different from (right_of + 5)
    // If line 22-25 remain where they are, then (left_of + 1) is same as (right_of + 5)


	// Debug code start
    cout<<endl;
    cout<<"Just after entering values of N and K"<<endl;
    cout<<left_of + 1<< "   " <<right_of + 5;
    cout<<endl<<endl;
	// Debug code end


	// Fill left_of and right_of with -1's
	for(int i = 0; i < N + 1; ++i)
	{
		left_of[i] = -1;
		right_of[i] = -1;
	}

    // Fill node_val from input
	node_val[0] = -1;
	for(int i = 1; i < N + 1; ++i)
	{
		cin >> node_val[i];
	}

    // Fill parent_of[2 onwards] from input
	parent_of[0] = -1;
	parent_of[1] = -1;
	for(int i = 2; i < N + 1; ++i)
	{

		cin >> parent_of[i];
		
	}

    
    // debug code start
	cout<<endl;
    cout<<"before the for loop that fills left and right"<<endl;
	cout<<"left of 1  : "<<left_of[1]<<endl;
	cout<<"right of 5 : "<<right_of[5]<<endl;
	cout<<endl;
	left_of[1] = 9;
    cout<<"left of 1  : "<<left_of[1]<<endl;
	cout<<"right of 5 : "<<right_of[5]<<endl;
	cout<<endl;
    left_of[1]++;
    cout<<"left of 1  : "<<left_of[1]<<endl;
	cout<<"right of 5 : "<<right_of[5]<<endl;
	cout<<endl;
    cout<<left_of + 1<< "   " <<right_of + 5;
    cout<<endl;
	cout<<endl;
    cout<<"~~~~~~~~~~~iteration 0~~~~~~~~~~~~~~"<<endl; 
    cout<<left_of + 1<< "   " <<right_of + 5;
    cout<<endl;
	// debug code end
    

	for(int i = 2; i < N + 1; ++i)
	{
        // debug code start
	    cout<<endl;
        cout<<"~~~~~~~~~~~iteration "<<i<<"  ~~~~~~~~~~~~~~"<<endl; 
        cout<<left_of + 1<< "   " <<right_of + 5;
        cout<<endl;
		// debug code end
        
        if(left_of[parent_of[i]] == -1)
		{			
			left_of[parent_of[i]] = i;
		}
		else
		{
			right_of[parent_of[i]] = i;
		}
	
	}

	// debug code start
	cout<<endl;
    cout<<"after the for loop that fill left and right"<<endl;
	cout<<"left of 1  : "<<left_of[1]<<endl;
	cout<<"right of 5 : "<<right_of[5]<<endl;
	cout<<endl;
	left_of[1] = 9;
    cout<<"left of 1  : "<<left_of[1]<<endl;
	cout<<"right of 5 : "<<right_of[5]<<endl;
	cout<<endl;
    left_of[1]++;
    cout<<"left of 1  : "<<left_of[1]<<endl;
	cout<<"right of 5 : "<<right_of[5]<<endl;
	cout<<endl;
    cout<<left_of + 1<< "   " <<right_of + 5;
    cout<<endl;
	// debug code end
	
	int height = tree_height(left_of, right_of, 1);
	
	// Got the height. Tree with 0 nodes has height 0. Tree with 1 node has height 1. 

	// Below code lacks documentation

	int array_size = pow(2, height);
	int tree_array[array_size] = {-1, -1, -1, -1, -1, -1, -1, -1};
	tree_array[0] = -1;	
	int curr_array_pos = 1;
	int curr_node = 1;
	tree_to_array(tree_array, array_size, curr_array_pos, curr_node, node_val, left_of, right_of);


	cout << "checkpoint 1 : filled tree_to_array" << endl;
	for(int i = 0; i < array_size; ++i)
		cout << tree_array[i];


	int beg_pos = 1;
	int end_pos = array_size - 1;

	cout << num_of_triplets(K, tree_array, array_size, curr_array_pos, node_val);
	
	return 0;
}

int num_of_triplets(int K, int tree_array[], int array_size, int curr_pos, int node_val[])
{
	int count = 0;

	if(tree_array[curr_pos] == -1)
	{
		return count;
	}
	
	for(int i = curr_pos + 1; i < curr_pos + array_size - 2; ++i)
	{
		if(tree_array[i] == -1)
		{
			continue;
		}

		for(int j = i + 1; j <= curr_pos + array_size - 2; ++j)
		{
			if(tree_array[j] == -1)
			{
				continue;
			}
	
			if(node_val[tree_array[curr_pos]] + node_val[tree_array[i]] + node_val[tree_array[j]] >= K)
			{
				count++;
			}
		} 
	}

	return count + 
		       num_of_triplets(K, tree_array, array_size / 2, curr_pos + 1, node_val) + 
				num_of_triplets(K, tree_array, array_size / 2, curr_pos + (array_size) / 2, node_val);
}

void tree_to_array(int tree_array[], int array_size, int curr_arr_pos, int curr_node, int node_val[], int left_of[], int right_of[])
{	
	static int stack_ctr = 0;
	stack_ctr++;
	cout << endl << "Entering : " << stack_ctr;

	tree_array[curr_arr_pos] = curr_node;
	
	if(left_of[curr_node] != -1)
	{
		tree_to_array(tree_array, array_size / 2, curr_arr_pos + 1, left_of[curr_node], node_val, left_of, right_of);
	}

	if(right_of[curr_node] != -1)
	{
		tree_to_array(tree_array, array_size / 2, curr_arr_pos + (array_size / 2), right_of[curr_node], node_val, left_of, right_of);
	}


	cout << "tree_array : ";
	for(int i = 0; i < 8; ++i)
		cout << tree_array[i];
	cout << endl << "Exiting  : " << stack_ctr;	
	return;
}



int tree_height(int left[], int right[], int curr_node)
{
	int height = 1;
 	int left_height = 0;
	int right_height = 0;

	if(curr_node == -1)
	{
		return 0;
	}
	else if(left[curr_node] == -1 and right[curr_node] == -1)
	{
		return height;
	}
	else
	{
		left_height = tree_height(left, right, left[curr_node]);
		right_height = tree_height(left, right, right[curr_node]);

		if(left_height > right_height)
			return height + left_height;
		else
			return height + right_height;		
	}
}


