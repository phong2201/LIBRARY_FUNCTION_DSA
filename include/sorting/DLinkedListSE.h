/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DLinkedListSE.h
 * Author: LTSACH
 *
 * Created on 31 August 2020, 14:13
 */

#ifndef DLINKEDLISTSE_H
#define DLINKEDLISTSE_H
#include "list/DLinkedList.h"
#include "sorting/ISort.h"

template<class T>
class DLinkedListSE: public DLinkedList<T>{
public:
    
    DLinkedListSE(
            void (*removeData)(DLinkedList<T>*)=0, 
            bool (*itemEQ)(T&, T&)=0 ) : 
            DLinkedList<T>(removeData, itemEQ){
        
    };
    
    DLinkedListSE(const DLinkedList<T>& list){
        this->copyFrom(list);
    }
    
    void sort(int (*comparator)(T&,T&)=0){
        //TODO: implement this function
        //     - You should implement the merge sort algorithm
        merge_Sort(*this, comparator);
    };
    
    void merge(DLinkedList<T>& left, DLinkedList<T>& right, DLinkedList<T>& merged, int (*comparator)(T&, T&) = 0) 
    {
        int leftIndex = 0, rightIndex = 0;

        while (leftIndex < left.size() && rightIndex < right.size()) {
            T& leftElement = left.get(leftIndex);
            T& rightElement = right.get(rightIndex);

            if (compare(leftElement, rightElement, comparator) <= 0) {
                merged.add(leftElement);
                leftIndex++;
            } else {
                merged.add(rightElement);
                rightIndex++;
            }
        }

        while (leftIndex < left.size()) {
            merged.add(left.get(leftIndex));
            leftIndex++;
        }

        while (rightIndex < right.size()) {
            merged.add(right.get(rightIndex));
            rightIndex++;
        }
    }

    void merge_Sort(DLinkedList<T>& list, int (*comparator)(T&, T&) = 0) 
    {
        if (list.size() <= 1) return; 

        int mid = list.size() / 2;
        DLinkedList<T> left, right;

        for (int i = 0; i < mid; i++) {
            left.add(list.get(i));
        }
        for (int i = mid; i < list.size(); i++) {
            right.add(list.get(i));
        }

        merge_Sort(left, comparator);
        merge_Sort(right, comparator);
        
        list.clear();
        merge(left, right, list, comparator);
    }

protected:
    static int compare(T& lhs, T& rhs, int (*comparator)(T&,T&)=0){
        if(comparator != 0) return comparator(lhs, rhs);
        else{
            if(lhs < rhs) return -1;
            else if(lhs > rhs) return +1;
            else return 0;
        }
    }
};

#endif /* DLINKEDLISTSE_H */

