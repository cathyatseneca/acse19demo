/*********************************************************************/
/*                                                                   */
/* Tester for a sorted list                                      	 */
/* Version 1.0                                                       */
/* To compile:                                                       */
/*                                                                   */
/*      g++ a1q2main.cpp -std=c++0x                                */
/*                                                                   */
/*********************************************************************/

#include "sortedlist.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;
//change the #define VERBOSE to 1 for a bit more error information
#define VERBOSE 1
const int cap=10000;
const int numSearches=200;

struct Record{
	char word_[30];
	int count_;
};
ostream& operator<<(ostream& os, const Record rec){
	os << rec.word_;
	return os;
}
bool operator==(const Record& a,const Record& b){
	bool rc=false;
	if(strcmp(a.word_,b.word_)==0 && a.count_==b.count_){
		rc=true;
	}
	return rc;
}
bool operator!=(const Record& a,const Record& b){
	return !(a==b);
}
bool operator <(const Record& a, const Record& b){
	bool rc=false;
	if(strcmp(a.word_,b.word_) < 0){
		rc=true;
	}
	return rc;
}

template <typename T>
void mergeArray(T arr[],T tmp[],int startA,int startB,int endB);
template <typename T>
void mergeSort(T arr[],T tmp[],int start,int end);
template <typename T>
void mergeSort(T arr[],int size);
template <typename T>
void addBack(const T& data,T arr[],int sz);
template <typename T>
void removeItem(T arr[],int idx,int sz);
template <typename T>
bool checkList(const SortedList<T>& list,const T arr2[],int sz);
template <typename T>
void duplicateArray(T dest[], const T src[],int sz);
template <typename T>
void printLists(const SortedList<T>& list,const T array[],int sz);
template<typename T>
typename SortedList<T>::iterator setIterator(SortedList<T>& list, int idx);

template <typename T>
void add(const T& data,int idx, T arr[],int sz);
int main(void){

	Record data[20]={
		{"the",1},
		{"quick",2},
		{"brown ",3},
		{"fox",4},
		{"jumped",5},
		{"over",6},
		{"lazy",7},
		{"dog",8},
		{"Calvin",9},
		{"and",10},
		{"Hobbes",11},
		{"night",12},
		{"watch",13},
		{"captain",14},
		{"carrot",15},
		{"lilac",16},
		{"lavender",17},
		{"lily",18},
		{"coffee",19},
		{"tea",20}
	};
	int intData[cap];

	//these array will mirror what happens to LL
	Record mirror[20];
	int intMirror[cap];
	for(int i=0;i<cap;i++){
		intData[cap-1-i]=rand();
		intMirror[cap-1-i]=intData[cap-1-i];
	}
	for(int i=0;i<20;i++){
		mirror[i]=data[i];
	}
	SortedList<Record> recList;
	SortedList<int> intList;

	bool passtest=true;
	int numPassed=0;



	/* Test constructors, begin and end functions*/
	cout << "test 1: create list empty list, check c/begin() and c/end()" << endl;
	if((recList.cbegin() != recList.cend()) || (intList.cbegin() != intList.cend()) ||
		(recList.begin() != recList.end()) || (intList.begin() != intList.end())){
		cout << "error 1: check your constructor, c/begin() and c/end() functions" << endl;
		passtest=false;
	}
	else{
		numPassed++;
	}
	/* Test end() and size() functions for empty lists*/
	cout << "test 2: size() and empty() functions on empty list" << endl;
	if((recList.size() != 0 )|| (!recList.empty()) || 
	 	(intList.size() != 0 )|| (!intList.empty())){
		cout << "error 2: check your size() and empty() functions" << endl;
		passtest=false;
	}
	else{
		numPassed++;
	}

	if(passtest){
		SortedList<Record>::iterator it=recList.begin();

		SortedList<int>::iterator it2=intList.begin();

		for(int i=0;i<20;i++){
			recList.insert(data[i]);
		}
		mergeSort(mirror,20);
		mergeSort(intMirror,cap);
		for(int i=0;i<cap;i++){
			intList.insert(intData[cap-1-i]);
		}

		cout << "test 3: create list, insert some records." << endl;	
		if(!checkList(recList,mirror,20) || recList.empty() || recList.size()!=20){
			passtest=false;
			cout << "Error 3a: Bug in either constructor, insert(), or iterator (operator++(int) or operator*)"<< endl;
			#if VERBOSE <= 1
			printLists(recList,mirror,20);
			#endif
		}
		if(!checkList(intList,intMirror,cap) || intList.empty() || intList.size()!=cap){
			passtest=false;
			cout << "Error 3b: Bug in either constructor, insert(), or iterator (operator++(int) or operator*"<< endl;
			#if VERBOSE <= 1
			printLists(intList,intMirror,cap);
			#endif
		}
	}
	if(passtest){
		numPassed++;
		cout << "test 4: check iterator ++ and -- operators"  << endl;
		SortedList<Record>::const_iterator it=recList.cbegin();
        for(int i=0;i<20 && passtest;i++){
            if(mirror[i] != *(it++)){
                passtest=false;
				cout << "Error 4a: postfix ++ (it++) operator is not returning iterator to correct node" << endl;
			}
		}
        if(passtest && it!=recList.cend()){
            passtest=false;
            cout << "Error 4b: postfix ++ operator did not advance iterator pass last data" << endl;
		}
        if(passtest && (it--) != recList.cend()){
            passtest=false;
            cout << "Error 4c: postfix -- operator did not return iterator to correct node" << endl;
        }		
        if(passtest && it == recList.cend()){
            passtest=false;
            cout << "Error 4d: postfix -- operator iterator did not move to last data from cend()" << endl;
		}            
        for(int i=19;i>0 && passtest;i--){
            if(mirror[i] != *(it--)){
                passtest=false;
				cout << "Error 4e: postfix -- (it--) operator is not returning iterator to correct node" << endl;
			}
		}
        for(int i=0;i<19 && passtest;i++){
            if(*(++it) != mirror[i+1]){
                passtest=false;
				cout << "Error 4f: prefix ++ (++it) operator is not returning iterator to correct node" << endl;
			}
		}
        if(passtest && (++it) != recList.cend()){
            passtest=false;
            cout << "Error 4g: prefix ++ operator did not return cend() when advancing from last node" << endl;
        }
        if(passtest && it!=recList.cend()){
            passtest=false;
            cout << "Error 4h: prefix ++ operator did not advance iterator pass last data" << endl;
        }
        //puts iterator back to last data, should return cend()
        if(passtest && *(--it) != mirror[19]){
            passtest=false;
            cout << "Error 4i: prefix -- operator did not return iterator to correct node" << endl;
        }
        if(passtest && it == recList.cend()){
            passtest=false;
            cout << "Error 4j: prefix -- operator iterator did not move to last data from cend()" << endl;
        }
        for(int i=19;i>0 && passtest;i--){
            if(*(--it) != mirror[i-1]){
                passtest=false;
                cout << "Error 4k: prefix -- operator is not returning iterator to correct node" << endl;
            }
        }
	}
    if(passtest){
        numPassed++;
        cout << "test 5: check iterator ++ and -- operators"  << endl;
        SortedList<Record>::iterator it=recList.begin();
        for(int i=0;i<20 && passtest;i++){
            if(mirror[i] != *(it++)){
                passtest=false;
                cout << "Error 5a: postfix ++ operator is not returning iterator to correct node" << endl;
            }
        }
        if(passtest && it!=recList.end()){
            passtest=false;
            cout << "Error 5b: postfix ++ operator did not advance iterator pass last data" << endl;
        }
        //puts iterator back to last data, should return end()
        if(passtest && (it--) != recList.end()){
            passtest=false;
            cout << "Error 5c: postfix -- operator did not return iterator to correct node" << endl;
        }
        if(passtest && it == recList.end()){
            passtest=false;
            cout << "Error 5d: postfix -- operator iterator did not move to last data from end()" << endl;
        }
        for(int i=19;i>0 && passtest;i--){
            if(mirror[i] != *(it--)){
                passtest=false;
                cout << "Error 5e: postfix -- operator is not returning iterator to correct node" << endl;
            }
        }
        for(int i=0;i<19 && passtest;i++){
            if(*(++it) != mirror[i+1]){
                passtest=false;
                cout << "Error 5f: prefix ++ operator is not returning iterator to correct node" << endl;
            }
        }
        if(passtest && (++it) != recList.end()){
            passtest=false;
            cout << "Error 5g: prefix ++ operator did not return end() when advancing from last node" << endl;
        }
        if(passtest && it!=recList.end()){
            passtest=false;
            cout << "Error 5h: prefix ++ operator did not advance iterator pass last data" << endl;
        }
        //puts iterator back to last data, should return end()
        if(passtest && *(--it) != mirror[19]){
            passtest=false;
            cout << "Error 5i: prefix -- operator did not return iterator to correct node" << endl;
        }
        if(passtest && it == recList.end()){
            passtest=false;
            cout << "Error 5j: prefix -- operator iterator did not move to last data from end()" << endl;
        }
        for(int i=19;i>0 && passtest;i--){
            if(*(--it) != mirror[i-1]){
                passtest=false;
                cout << "Error 5k: prefix -- operator is not returning iterator to correct node" << endl;
            }
        }
    }


    SortedList<Record> recCopy=recList;
    SortedList<int> intCopy=intList;               //copy constructor calls
    SortedList<Record> recCopy2=recCopy;
    SortedList<int> intCopy2=intCopy;

    duplicateArray(data,mirror,20);              //ensure that data and mirror hold same data
    duplicateArray(intData,intMirror,cap);

    if(passtest){
        numPassed++;
        cout << "test 6: create a duplicate of the lists with copy constructor, ensure they match" << endl;
        if(!checkList(recCopy,mirror,20) || !checkList(recCopy2,mirror,20) || recCopy.size()!=20 || recCopy2.size() != 20 || recCopy.empty() || recCopy2.empty()){
            passtest=false;
            cout << "Error 6a: Bug in copy constructor, either your rhs or current object does not contain the correct data"  << endl;  		
            #if VERBOSE >= 1
            printLists(recCopy,mirror,20);
            #endif
        }
        if(!checkList(intCopy,intMirror,cap) || !checkList(intCopy2,intMirror,cap) || intCopy.size()!=cap ||intCopy2.size()!=cap || recCopy.empty() || recCopy2.empty()){
            passtest=false;
            cout << "Error 6b: Bug in copy constructor" << endl;
            #if VERBOSE > 1
            printLists(intList,intMirror,cap);
            #endif
        }
    }

	if(passtest){
		numPassed++;
		cout << "test 7: test search() function" << endl;
		for(int i=0;i<20;i++){
			//const reference to int list ensures const version of search
			//gets called
			const SortedList<Record>& recListRef=recList; 

			SortedList<Record>::const_iterator it = recListRef.search(mirror[i]);
			if(it == recList.cend() || *it != mirror[i]){
				passtest=false;
				cout << "Error 7a: Bug in search, iterator returned does not point at correct node" << endl;
			}
		}
		for(int i=0;i<cap && passtest;i++){
			int pick=i;
			SortedList<int>::iterator it = intList.search(intMirror[pick]);
			if(it == intList.end() || *it != intMirror[pick]){
				passtest=false;
				cout << "Error 7b: Bug in search, iterator returned does not point at correct node" << endl;
			}
		}
	}

    if(passtest){
        numPassed++;
        cout << "test 8: test erase function"  << endl;
        SortedList<Record>::iterator it;
        it=setIterator(recList,19);
        recList.erase(it);
        removeItem(mirror,19,20);
        if(!checkList(recList,mirror,19)){
            passtest=false;
            cout << "Error 8a: Bug in erase.  something went wrong when erasing last item from list" << endl;
            #if VERBOSE >= 1
            printLists(recList,mirror,19);
            #endif
        }
        recList.erase(recList.begin());
        removeItem(mirror,0,19);
        if(!checkList(recList,mirror,18)){
            passtest=false;
            cout << "Error 8b: Bug in erase. something went wrong when erasing first item from list" << endl;
            #if VERBOSE >= 1
            printLists(recList,mirror,18);
            #endif
        }
        for(int i=0;i<3 && passtest;i++){
            int pick=rand()%(18-i);
            it=setIterator(recList,pick);
            recList.erase(it);
            removeItem(mirror,pick,18-i);
            if(!checkList(recList,mirror,18-i-1)){
                passtest=false;
                cout << "Error 8c:  Bug in erase." << endl;
            }
        }
        intList.erase(intList.begin());
        removeItem(intMirror,0,cap);
        if(!checkList(intList,intMirror,cap-1)){
            passtest=false;
            cout << "Error 8d: Bug in erase, something went wrong when erasing first item from list" << endl;
        }
        intList.erase(intList.begin());
        removeItem(intMirror,0,cap-1);
        if(!checkList(intList,intMirror,cap-2)){
            passtest=false;
            cout << "Error 8e: Bug in erase. something went wrong when erasing first item from list a second time" << endl;
        }
        SortedList<int>::iterator it2;
        it2=setIterator(intList,cap-3);
        intList.erase(it2);
        removeItem(intMirror,cap-3,cap-2);
        if(!checkList(intList,intMirror,cap-3)){
            passtest=false;
            cout << "Error 8f: Bug in erase.  something went wrong when erasing last item from list" << endl;
        }
        it2=setIterator(intList,cap-4);
        intList.erase(it2);
        removeItem(intMirror,cap-4,cap-3);
        if(!checkList(intList,intMirror,cap-4)){
            passtest=false;
            cout << "Error 8g: Bug in erase. something went wrong when erasing last item from list a second time" << endl;
        }
        #if VERBOSE > 1
        if(!passtest){
            printLists(intList,intMirror,cap-4);
        }
        #endif
        for(int i=0;i<100 && passtest;i++){
            int pick=rand()%(cap-4-i);
            it2=setIterator(intList,pick);
            intList.erase(it2);
            removeItem(intMirror,pick,cap-4-i);
            if(!checkList(intList,intMirror,cap-i-5)){
                passtest=false;
                cout << "Error 8h:  Bug in erase." << endl;
                #if VERBOSE > 1
                printLists(intList,intMirror,cap-i-5);
                #endif
            }
        }
    }


	if(passtest){
		numPassed++;
		cout << "test 9: ensure that copied list were not altered (proper deep copy was made) " << endl;
		if(!checkList(recCopy,data,20) || recCopy.empty() || recCopy.size()!=20 || 
			!checkList(recCopy2,data,20) || recCopy2.empty() || recCopy2.size()!=20){
			passtest=false;
			cout << "Error 9a: Bug in copy constructor, deep copy not made?"  << endl;
			#if VERBOSE >= 1
			printLists(recCopy,data,20);
			#endif
		}
		if(!checkList(intCopy,intData,cap)|| intCopy.empty() || intCopy.size()!=cap ||
			!checkList(intCopy,intData,cap)|| intCopy2.empty() || intCopy2.size()!=cap){
			passtest=false;
			cout << "Error 9b: Bug in copy constructor, deep copy not made?" << endl;
			#if VERBOSE >= 2
			printLists(intCopy,intData,cap);
			#endif
		}
	}
	if(passtest){
		numPassed++;
		cout << "test 10: test assignment operator"  << endl;
		recCopy2 = recList;
		intCopy2 = intList;
		if(!checkList(recCopy2,mirror,15)|| recCopy2.empty() || recCopy2.size()!=15){
			passtest=false;
			cout << "Error 10a: Bug in = operator"  << endl;  		
			#if VERBOSE >= 1
			printLists(recCopy2,mirror,15);
			#endif
		}
		if(!checkList(intCopy2, intMirror,cap-104) || intCopy2.empty() || intCopy2.size()!=cap-104){
			passtest=false;
			cout << "Error 10b: Bug in = operator"  << endl;  		
			#if VERBOSE >= 2
			printLists(intCopy2,intMirror,cap-104);
			#endif
		}
		if(!checkList(recCopy,data,20) || recCopy.empty() || recCopy.size()!=20){
			passtest=false;
			cout << "Error 10c: Bug in copy constructor or = operator, deep copy not made?"  << endl;
			#if VERBOSE >= 1
			printLists(recCopy,data,20);
			#endif
		}
		if(!checkList(intCopy,intData,cap)|| intCopy.empty() || intCopy.size()!=cap){
			passtest=false;
			cout << "Error 10d: Bug in copy constructor or = operator, deep copy not made?" << endl;
			#if VERBOSE >= 2
			printLists(intCopy,intData,cap);
			#endif
		}
	}

	if(passtest){
		recCopy2.erase(recCopy2.begin());
		intCopy2.erase(intCopy2.begin());
		numPassed++;
		cout << "test 11: test assignment operator (deep copy)"  << endl;
		if(!checkList(recList,mirror,15)|| recList.empty() || recList.size()!=15){
			passtest=false;
			cout << "Error 11a: Bug in = operator, no deepcopy?"  << endl;
		}
		if(!checkList(intList,intMirror,cap-104)|| intList.empty() || intList.size()!=cap-104){
			passtest=false;
			cout << "Error 11b: Bug in = operator,no deep copy?"  << endl;     
		}
	}

	if(passtest){
		numPassed++;
		cout << "test 12: search for removed items" << endl;
		int pick[2]={0,19};
		for(int i=0;i<2;i++){
			auto it =recList.search(data[pick[i]]);
			if(it!=recList.end()){
				cout << "Error 12a: Bug in search, returned iterator is not correct" << endl;
				passtest=false;
			}
		}

	}
	if(passtest){
		int pick[4]={0,1,cap-1,cap-2};
		for(int i=0;i<4;i++){
			auto it = intList.search(intData[pick[i]]);
			if(it != intList.end()){

				passtest=false;
				cout << "Error 12b: Bug in search."<< endl;
			}
		}
	}
	if(passtest){
       numPassed++;
        cout << "test 13: test erase(a,b) function"  << endl;
        SortedList<Record>::iterator it;
        SortedList<Record>::iterator it2;
  		Record tmp[20];
        duplicateArray(tmp,mirror,15);
        removeItem(tmp,0,15);
        it=setIterator(recCopy2,2);
        it2=setIterator(recCopy2,5);

        recCopy2.erase(it,it2);
        removeItem(tmp,4,14);
        removeItem(tmp,3,13);  
        removeItem(tmp,2,13);
        if(!checkList(recCopy2,tmp,11)){
            passtest=false;
            cout << "Error 13a: Bug erase(it) function"  << endl;  		
            #if VERBOSE >= 1
            printLists(recCopy2,tmp,11);
            #endif
        }
        if(!checkList(recList,mirror,15)){
            passtest=false;
            cout << "Error 13b: assignment operator"  << endl;  		
            #if VERBOSE >= 1
            printLists(recList,mirror,15);
            #endif

        }

	}

	if(passtest){
		numPassed++;
		cout << "test 14: test erase(front,end()) function"  << endl;
		SortedList<Record>::iterator it;
		SortedList<Record>::iterator it2;
		Record tmp[20];
		recCopy2=recList;
		intCopy2=intList;
		duplicateArray(tmp,mirror,15);
		it=setIterator(recCopy2,11);

		recCopy2.erase(it,recCopy2.end());
		removeItem(tmp,14,15);
		removeItem(tmp,13,14);  
		removeItem(tmp,12,13);
		removeItem(tmp,11,12);
		if(!checkList(recCopy2,tmp,11)){
			passtest=false;
			cout << "Error 14a: Bug erase function"  << endl;  		
			#if VERBOSE >= 1
			printLists(recCopy2,tmp,11);
			#endif
		}
		if(!checkList(recList,mirror,15)){
			passtest=false;
			cout << "Error 14b: assignment operator, (deep copy not made?)"  << endl;  		
			#if VERBOSE >= 1
			printLists(recList,mirror,15);
			#endif

		}
	}
	SortedList<Record>::iterator it=recList.begin();
	SortedList<Record>::iterator it2;
	SortedList<Record> recCopy3=std::move(recList);
	if(passtest){
		numPassed++;
		it2=recCopy3.begin();
		cout << "test 15: test move constructor"  << endl;

		if(!checkList(recCopy3,mirror,15) || recCopy3.size() != 15 || recCopy3.empty()){
			passtest=false;
			cout << "Error 15a: Bug in move constructor"  << endl;  		
			#if VERBOSE >= 1
			printLists(recCopy3,mirror,15);
			#endif
		}
		if(passtest && it != it2){
			passtest = false;
			cout << "Error 15b: Move constructor is suppose to \"steal\" the data from rhs" << endl;
		}
	}

	if(passtest){
		numPassed++;
		recList=recCopy3;
		it = recList.begin();
		cout << "test 16: test move assignment operator"  << endl;
		recCopy3=std::move(recList);
		it2=recCopy3.begin();
		if(!checkList(recCopy3,mirror,15)){
			passtest=false;
			cout << "Error 16a: Bug in move assignment operator"  << endl;  		
			#if VERBOSE >= 1
			printLists(recCopy3,mirror,15);
			#endif
		}
		if(passtest && it != it2){
			passtest = false;
			cout << "Error 16b: Move constructor is suppose to \"steal\" the data from rhs" << endl;
		}
	}
	if(passtest){
		numPassed++;
	}
	if(numPassed == 16){
		cout << "Testing for Assignment 1 completed successfully" << endl;
	}
	else{
		cout << numPassed << " / 16 tests passed.  Looks like you still" << endl;
		cout << "have some work to do" << endl;
	}
	return 0;
}


template <typename T>
void mergeSort(T arr[],T tmp[],int start,int end){
  //if the array is more than one element big
	if(start<end){
		int mid=(start+end)/2;
		mergeSort(arr,tmp,start,mid);
		mergeSort(arr,tmp,mid+1,end);
		mergeArray(arr,tmp,start,mid+1,end);
	}
}
/*function merges the two halfs of a sorted array together.
  The arrays are defined from arr[startA]to arr[startB-1] and arr[startB]
to arr[endB]*/

template <typename T>
void mergeArray(T arr[],T tmp[],int startA,int startB,int endB){
	int aptr=startA;
	int bptr=startB;
	int idx=startA;
	while(aptr < startB && bptr < endB+1){
		if(arr[aptr] < arr[bptr]){
			tmp[idx++]=arr[aptr];
			aptr++;
		}
		else{
			tmp[idx++]=arr[bptr];
			bptr++;
		}
	}
//merge function only does one of the two following loops
	while(aptr<startB){
		tmp[idx]=arr[aptr];
		idx++;
		aptr++;    
	}
	while(bptr < endB+1){
		tmp[idx++]=arr[bptr];
		bptr++;
	}

//copy back into arr
	for(int i=startA;i<=endB;i++){
		arr[i]=tmp[i];
	}
}

/*this is the wrapper function that "main" uses.  The world see's this and
  use this. The actual work is done by the other MergeSort() function*/
template <typename T>
void mergeSort(T arr[],int size){
	T* tmp=new T[size];
	mergeSort(arr,tmp,0,size-1);
	delete [] tmp;
}


template <typename T>
void add(const T& data,int idx, T arr[],int sz){
	for(int i=sz-1;i>=idx;i--){
		arr[i+1]=arr[i];
	}
	arr[idx]=data;
}
template <typename T>
void removeItem(T arr[],int idx,int sz){
	for(int i=idx;i<sz-1;i++){
		arr[i]=arr[i+1];
	}
}
template <typename T>
bool checkList(const SortedList<T>& list,const T array[],int sz){
	bool rc=true;
	auto it=list.cbegin();
	int i;
	for(i=0;i<sz && it!=list.cend() && rc;i++,it++){
		if(*it != array[i]){
			rc=false;
		}
	}
	if(it!=list.cend() || i < sz){
		rc=false;
	}
	return rc;
}
template <typename T>
void addBack(const T& data,T arr[],int sz){
	arr[sz]=data;
}
template <typename T>
void duplicateArray(T dest[], const T src[],int sz){
	for(int i=0;i<sz;i++){
		dest[i]=src[i];
	}
}

template <typename T>
void printLists(const SortedList<T>& list,const T array[],int sz){
	cout << "your size() returned: " << list.size() << endl;
	cout << "correct size returned: " << sz << endl;
	auto it=list.cbegin();
	for(int i=0;i<sz;i++,(it==list.cend())?it:it++){
		cout << "correct: "  << array[i];
		if(it!=list.cend()){
			cout << " your list: " << *it << endl;
		}
		else{
			cout << "your list: " << "<no data>" <<  endl;
		}
	}
}
//returns iterator to the idx'th node in the list
template <typename T>
typename SortedList<T>::iterator setIterator(SortedList<T>& list, int idx){
	typename SortedList<T>::iterator it=list.begin();
	for(int i=0;i<idx;i++){
		it++;
	}
	return it;
}
