#include <iostream>
#include <cmath>
#include "list.h";
#define INITIAL_CAPACITY 5
#define GROWTH_FACTOR 1.5
#define SHRINK_FACTOR 0.75
using namespace std;

class ArrayList : public List {
    int* array;
    int index;
    int capacity;

    void dynamic_expand(){
        int new_size = ceil(capacity * GROWTH_FACTOR);
        int* new_array = (int*) realloc(array, new_size * sizeof(int));
        if(new_array){
        array = new_array;
        capacity = new_size;
    }
    void dynamic_shrink(){
        if(capacity == INITIAL_CAPACITY) return;
        int new_size = ceil(capacity * SHRINK_FACTOR);
        if(capacity < INITIAL_CAPACITY) new_size = INITIAL_CAPACITY;
        int* new_array = (int*) realloc(array,new_size * sizeof(int));
        if(new_array){
            array = new_array;
            capacity = new_size;
        }
    }

    public:
    ArrayList(){
        array = malloc(INITIAL_CAPACITY * sizeof(int));
        index = 0;
        capacity = INITIAL_CAPACITY;
    }
    ~ArrayList(){
        free(array);
    }

    void add(int num){
        if(index == capacity) dynamic_expand();
        array[index++] = num;
    }
    int remove(int num){
        for(int i = 0 ; i < index ; i++){
            if(array[i] == num){
                int pos = i + 1;
                for(int j = 0 ; j < index - 1 ; j++) array[j] = array[j + 1];
                index--;
                array[index] = 0;
                if(index < 2.0/3 *capacity) dynamic_shrink();
                return pos;
            }
        }
        return -1;
    }

    int removeAt(int pos){
        if(pos < 1 || pos > index + 1) return - 1;
        int removed = array[pos - 1];
        for(int i = pos - 1 ; i < index - 1 ; i++) array[i] = array[i + 1];
        index--;
        array[index] = 0;
        if(index < 2.0/3 *capacity){
            dynamic_shrink();
            return removed;
        }
        return -1;
    }
    void removeAll(int num){
        int i = 0;
        while(i < index){
            if(array[i] == num){
                remove(num);
            }else{
                i++;
            }
        }
    }
    int get(int pos){
        if(pos < 1 || pos > index + 1) return;
        return array[pos - 1];
    }
    int size(){
        return index;
    }
    void addAt(int pos,int num){
        if(pos < 1 || pos > index + 1) return;
        if(index == capacity)dynamic_expand();
        for(int i = index ; i >= pos ; i--) array[i] = array[i - 1];
        array[pos - 1] = num;
        index++;
    }
    bool isEmpt(){
        return index == 0;
    }
    void print(){
        if(isEmpty()){
            cout << "List is empty" << endl;
            return;
        }
        for(int i = 0 ; i < index ; i++){
            cout << array[i] << " ";
        }
        for(int i = index ; i < capacity ; i++){
            cout << "? ";
        }
        cout << endl;
    }
}