/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TopoSorter.h
 * Author: ltsach
 *
 * Created on July 11, 2021, 10:21 PM
 */

#ifndef TOPOSORTER_H
#define TOPOSORTER_H
#include "graph/DGraphModel.h"
#include "hash/xMap.h"
#include "list/DLinkedList.h"
#include "sorting/DLinkedListSE.h"
#include "stacknqueue/Queue.h"
#include "stacknqueue/Stack.h"
template <class T, class V>
using XHashMap = xMap<T, V>;

template<class T>
class TopoSorter{
public:
    static int DFS;
    static int BFS; 
    
protected:
    DGraphModel<T>* graph;
    int (*hash_code)(T&, int);
    
public:
    TopoSorter(DGraphModel<T>* graph, int (*hash_code)(T&, int)=0){
        //TODO
        this->graph = graph;
        this->hash_code = hash_code;
    }   
    DLinkedList<T> sort(int mode=0, bool sorted=true){
        //TODO
        return (mode == BFS) ? bfsSort(sorted) : dfsSort(sorted);
    }
    DLinkedList<T> bfsSort(bool sorted=true){ 
        //TODO
        DLinkedList<T> kq ;
        XHashMap<T, int> degree(hash_code); 
        Queue<T> queue;          
        DLinkedList<T> list = graph->vertices();

        if (list.empty()) return kq ;

        if(sorted)
            {
                DLinkedListSE<T> merge;
                for (auto ver : list )
                {
                    merge.add(ver);
                }
                merge.sort(&SortSimpleOrder<T>::compare4Ascending);
                list = merge;
            }
        for (T vertex : list) {
            degree.put(vertex, 0);
        }

        for (T vertex : list) {
            DLinkedList<T> nears = graph->getOutwardEdges(vertex);
            for (T near : nears) {
                degree.put(near, degree.get(near) + 1);
            }
        }

        for (T vertex : list) {
            if (degree.get(vertex) == 0) {
                queue.push(vertex);
            }
        }

        while (!queue.empty()) {
            T cur = queue.pop();
            kq.add(cur);
            DLinkedList<T> nears = graph->getOutwardEdges(cur);
            if(sorted)
            {
                DLinkedListSE<T> merge;
                for (auto ver : nears )
                {
                    merge.add(ver);
                }
                merge.sort(&SortSimpleOrder<T>::compare4Ascending);
                nears = merge;
            }
            for (T near : nears) {
                degree.put(near, degree.get(near) - 1);
                if (degree.get(near) == 0) {
                    queue.push(near);
                }
            }
        }
        return kq;
    }

    DLinkedList<T> dfsSort(bool sorted=true){
        //TODO
        DLinkedList<T> kq;              
        XHashMap<T, bool> visited(this->hash_code);          
        Stack<T> stack;                     
        DLinkedList<T> list = graph->vertices(); 
        if (list.empty()) return kq ;
        if(sorted)
            {
                DLinkedListSE<T> merge;
                for (auto ver : list )
                {
                    merge.add(ver);
                }
                merge.sort(&SortSimpleOrder<T>::compare4Desending);
                list = merge;
            }
        for (T vertex : list) {
            visited.put(vertex, false);
        }

        for (auto &vertex : list) {
            if (!visited.get(vertex)) {
                stack.push(vertex);                 
                while (!stack.empty()) {
                    T cur = stack.peek();   
                    
                    if (!visited.get(cur)) {
                        visited.put(cur, true); 
                        DLinkedList<T> nears = graph->getOutwardEdges(cur);
                        for (auto &near : nears) {
                            if (!visited.get(near)) stack.push(near); 
                        }
                    } else {
                        stack.pop();               
                        if (!kq.contains(cur)) kq.add(0,cur);    
                    }
                }
            }
        }
        return kq; 
    }

protected:

    //Helper functions
    XHashMap<T, int> vertex2inDegree(int (*hash)(T&, int));
    XHashMap<T, int> vertex2outDegree(int (*hash)(T&, int));
    DLinkedList<T> listOfZeroInDegrees();

}; //TopoSorter
template<class T>
int TopoSorter<T>::DFS = 0;
template<class T>
int TopoSorter<T>::BFS = 1;

/////////////////////////////End of TopoSorter//////////////////////////////////


#endif /* TOPOSORTER_H */

