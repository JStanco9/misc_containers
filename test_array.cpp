//
//  test_array.cpp
//  
//
//  Created by John Stanco on 6/22/18.
//
//

#include "t_array.hpp"
#include "linked_list.hpp"
#include <stdio.h>
#include <ctime>
#include <vector>


int test_array(){
	size_t len = 100000;
	clock_t t = clock();
  	//t_array<int> arr(len);
  	t = clock() - t;

  	//std::cout << "My template array constructor x" << len << "\t" << (double)t / CLOCKS_PER_SEC << std::endl;

  	t = clock();
  	//std::vector<int> vec(len);
  	t = clock() - t;

  	//std::cout << "std::vector constructor x" << len << "\t" << (double)t / CLOCKS_PER_SEC << std::endl;

  	for(size_t i = 0; i < len; i++){
  		//arr.push(0);
  	}


  	t = clock();
  	t_array<int> arr(len);
  	for(size_t i = 0; i < len; i++){
  		arr.push(i);
  	}
  	t = clock() - t;

  	std::cout << "My template array push x" << len << "\t" << (double)t / CLOCKS_PER_SEC << std::endl;

  	t = clock();
  	std::vector<int> vec(len);
  	for(size_t i = 0; i < len; i++){
  		vec[i] = i;
  	}
  	t = clock() - t;

  	std::cout << "std::vector indexing x" << len << "\t" << (double)t / CLOCKS_PER_SEC << std::endl;

  	t = clock();
  	int **intArr = new int*[len];
  	for(int i = 0; i < len; i++){
  		intArr[i] = &i;
  	}
  	t = clock() - t;

  	std::cout << "int arr indexing x" << len << "\t" << (double)t / CLOCKS_PER_SEC << std::endl;
  	return 1;
}


int main(){
	linked_list<int> ll;

	ll.push(1);
	ll.push(2);

	linked_list<int> ll2;
	ll2 = ll;

	t_array<int> a1;
	a1.push(1);
	a1.push(2);
	t_array<int> a2;
	a2 = a1;

	a1.print();
	a2.print();

	return 1;
}
