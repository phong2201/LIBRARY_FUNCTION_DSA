/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DGraphModel.h
 * Author: LTSACH
 *
 * Created on 23 August 2020, 19:36
 */


#ifndef DGRAPHMODEL_H
#define DGRAPHMODEL_H
#include "graph/AbstractGraph.h"
#include "stacknqueue/Queue.h"
#include "stacknqueue/Stack.h"
#include "hash/xMap.h"
#include "sorting/DLinkedListSE.h"

//////////////////////////////////////////////////////////////////////
///////////// GraphModel: Directed Graph Model    ////////////////////
//////////////////////////////////////////////////////////////////////


template<class T>
class DGraphModel: public AbstractGraph<T>{
private:
public:
    DGraphModel(
            bool (*vertexEQ)(T&, T&), 
            string (*vertex2str)(T&) ): 
        AbstractGraph<T>(vertexEQ, vertex2str){
    }
    
    void connect(T from, T to, float weight=0){
        //TODO
        typename AbstractGraph<T>::VertexNode* from_Node = this->getVertexNode(from);
        typename AbstractGraph<T>::VertexNode* to_Node = this->getVertexNode(to);
        if ( from_Node == NULL ) throw VertexNotFoundException (this->vertex2str(from));
        if ( to_Node == NULL ) throw VertexNotFoundException (this->vertex2str(to));
        if ( from_Node->getEdge(to_Node) == NULL ) from_Node->connect ( to_Node , weight);
        else {
            from_Node->removeTo(to_Node);
            from_Node->connect ( to_Node , weight);
        }
    }
    void disconnect(T from, T to){
        //TODO
        typename AbstractGraph<T>::VertexNode* from_Node = this->getVertexNode(from);
        typename AbstractGraph<T>::VertexNode* to_Node = this->getVertexNode(to);
        if ( from_Node == NULL ) throw VertexNotFoundException (this->vertex2str(from));
        if ( to_Node == NULL ) throw VertexNotFoundException (this->vertex2str(to));
        typename AbstractGraph<T>::Edge* edge = from_Node->getEdge(to_Node);
        if ( edge == NULL )
        {
            typename AbstractGraph<T>::Edge call_edge(from_Node,to_Node) ;
            throw EdgeNotFoundException(this->edge2Str(call_edge));
        } 
        from_Node->removeTo(to_Node);
    }   
    void remove(T vertex){
        //TODO
        typename AbstractGraph<T>::VertexNode* node = this->getVertexNode(vertex);
        if ( node == NULL ) throw VertexNotFoundException (this->vertex2str(vertex));
        DLinkedList<T> out = node->getOutwardEdges() ;
        for ( auto vers : out ) 
        {
            typename AbstractGraph<T>::VertexNode* r_Node = this->getVertexNode(vers);
            node->removeTo(r_Node);
        }
        DLinkedList<T> in = this->getInwardEdges(vertex) ;
        for ( auto vers : in ) 
        {
            typename AbstractGraph<T>::VertexNode* r_Node = this->getVertexNode(vers);
            r_Node->removeTo(node);
        }
        this->nodeList.removeItem(node);
        delete node; 
    }
    
    static DGraphModel<T>* create(
            T* vertices, int nvertices, Edge<T>* edges, int nedges,
            bool (*vertexEQ)(T&, T&),
            string (*vertex2str)(T&)){
        //TODO
        DGraphModel<T>*  graph = new DGraphModel<T> ( vertexEQ , vertex2str);
        for ( int i = 0 ; i < nvertices ; i++)
        {
            graph->add(vertices[i]);
        }

        for ( int i = 0 ; i < nedges ; i++)
        {
            T from = edges[i].from;
            T to = edges[i].to;
            float weight = edges[i].weight;
            graph->connect(from,to,weight);
        }
         return graph;
    }
};

#endif /* DGRAPHMODEL_H */

