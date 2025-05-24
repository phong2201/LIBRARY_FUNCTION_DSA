/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   UGraphModel.h
 * Author: LTSACH
 *
 * Created on 24 August 2020, 15:16
 */

#ifndef UGRAPHMODEL_H
#define UGRAPHMODEL_H

#include "graph/AbstractGraph.h"


//////////////////////////////////////////////////////////////////////
///////////// UGraphModel: Undirected Graph Model ////////////////////
//////////////////////////////////////////////////////////////////////

template <class T>
class UGraphModel : public AbstractGraph<T>
{
private:
public:
    // class UGraphAlgorithm;
    // friend class UGraphAlgorithm;

    UGraphModel(
        bool (*vertexEQ)(T &, T &),
        string (*vertex2str)(T &)) : AbstractGraph<T>(vertexEQ, vertex2str)
    {
    }

    void connect(T from, T to, float weight = 0)
    {
        // TODO
        typename AbstractGraph<T>::VertexNode* from_Node = this->getVertexNode(from);
        typename AbstractGraph<T>::VertexNode* to_Node = this->getVertexNode(to);
        
        if (from_Node == NULL) throw VertexNotFoundException(this->vertex2str(from));
        if (to_Node == NULL) throw VertexNotFoundException(this->vertex2str(to));
        if ( from_Node->getEdge(to_Node) == NULL ) from_Node->connect ( to_Node , weight);
        else {
            from_Node->removeTo(to_Node);
            from_Node->connect(to_Node, weight);
        }
        if (!this->vertexEQ(from, to)) {
            if ( to_Node->getEdge(from_Node) == NULL ) to_Node->connect(from_Node, weight);
            else{
                to_Node->removeTo(from_Node);
                to_Node->connect(from_Node, weight);
            }
        }
    }
    void disconnect(T from, T to)
    {
        // TODO
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
        to_Node->removeTo(from_Node);
    }
    void remove(T vertex)
    {
        // TODO
        typename AbstractGraph<T>::VertexNode* node = this->getVertexNode(vertex);
        if ( node == NULL ) throw VertexNotFoundException (this->vertex2str(vertex));
        DLinkedList<T> out = node->getOutwardEdges() ;
        for ( auto vers : out ) 
        {
            typename AbstractGraph<T>::VertexNode* r_Node = this->getVertexNode(vers);
            node->removeTo(r_Node);
            r_Node->removeTo(node);
        }
        this->nodeList.removeItem(node);
        delete node; 
    }
    static UGraphModel<T> *create(
        T *vertices, int nvertices, Edge<T> *edges, int nedges,
        bool (*vertexEQ)(T &, T &),
        string (*vertex2str)(T &))
    {
        // TODO
        UGraphModel<T> * ugraph = new UGraphModel(vertexEQ,vertex2str);

        for ( int i = 0 ; i < nvertices ; i++)
        {
            ugraph->add(vertices[i]);
        }

        for ( int i = 0 ; i < nedges ; i++)
        {
            T from = edges[i].from;
            T to = edges[i].to;
            float weight = edges[i].weight;
            ugraph->connect(from,to,weight);
        }
        return ugraph;
    }
};

#endif /* UGRAPHMODEL_H */
