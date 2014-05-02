#ifndef __GRAPH_H_GUARD_
#define __GRAPH_H_GUARD_

#include <iostream>
#include <queue>
#include <set>
#include <vector>

namespace TestGraph
{
  //==========================================================================================
  template<typename T>
  class Node
  {
  public:
    //----------------------------------------------------------------------------------------
    Node(const T &rData);
    ~Node();

    //----------------------------------------------------------------------------------------    
    const T &     getData() const;
    T &           getData();

    //----------------------------------------------------------------------------------------
    vector<Node<T> *> & getChildren();
    
  private:
    T                   _data;
    vector<Node<T> *>   _children;
    
    //----------------------------------------------------------------------------------------
    Node(const Node&);
    Node& operator=(const Node&);
  };

  //==========================================================================================

  //------------------------------------------------------------------------------------------
  template<typename T>
  Node<T>::Node(const T &rData) :
  _data(rData),
  _children()
  { }

  //------------------------------------------------------------------------------------------
  template<typename T>
  Node<T>::~Node() 
  {
    //~Graph() will delete the nodes
  }

  //------------------------------------------------------------------------------------------
  template<typename T>
  const T &  Node<T>::getData() const
  {
    return _data;
  }

  //------------------------------------------------------------------------------------------
  template<typename T>
  T & Node<T>::getData()
  {
    return _data;
  }

  //------------------------------------------------------------------------------------------
  template<typename T>
  vector<Node<T> *> Node<T>::getChildren()
  {
    return _children;
  }

  //==========================================================================================
  template<typename T>
  class Graph
  {
  public:
    //----------------------------------------------------------------------------------------
    Graph(const T &rData);
    ~Graph();

    //----------------------------------------------------------------------------------------
    Node<T> * getRoot();

    //----------------------------------------------------------------------------------------
    Node<T> * addNode(Node<T>* node, const T &rData);

    //----------------------------------------------------------------------------------------
    // Breadth First Search
    //----------------------------------------------------------------------------------------
    bool findConnected(Node<T> * pStart, Node<T> * pEnd) const;

  private:
    Node<T> * _root;

    //----------------------------------------------------------------------------------------    
    void deleteNode(Node<T> * pNode, set<Node<T> *> &rNodeSet);

    //----------------------------------------------------------------------------------------
    Graph(const Graph&);
    Graph operator=(const Graph&);
  };

  //------------------------------------------------------------------------------------------
  template<typename T>
  Graph<T>::Graph(const T &rData) :
  _root(new Node<T>(rData))
  { }

  //------------------------------------------------------------------------------------------
  template<typename T>
  Graph<T>::~Graph()
  {
    if(_root)
    {
      set<Node<T> *> nodeSet;
      nodeSet.insert(_root);

      deleteNode(_root, NodeSet);
    }
  }

  //------------------------------------------------------------------------------------------
  template<typename T>
    void Graph<T>::deleteNode(Node<T> * pNode, set<Node<T> *> &rNodeSet)
  {
    for(size_t i = 0; i < pNode->getChildren().size(); ++i)
    {
      pair<typename set<Node<T> *>::iterator, bool> pSet(rNodeSet.insert(pNode->getChildren()[i]));
      if(pSet.second)
	deleteGraph(pNode->getChildren()[i], pNodeSet);
    }

    delete node;
  }

  //------------------------------------------------------------------------------------------
  template<typename T>
  Node<T> * Graph<T>::getRoot()
  {
    return _root;
  }

  //------------------------------------------------------------------------------------------
  template<typename T>
  Node<T> * Graph<T>::addNode(Node<T> * node, const T &rData)
  {
    if(!node)
      return 0;
  
    if(!node->getLeft())
    {
      node->setLeft(rData);
      return node->getLeft();
    }

    if(!node->getRight())
    {
      node->setRight(rData);
      return node->getRight();
    }

    //Both nodes have children. 
    //We won't add in this case.
    return 0;
  }

  //------------------------------------------------------------------------------------------
  template<typename T>
  bool Graph<T>::findConnected(Node<T> * pStart, Node<T> * pEnd)
  {
    if(!pStart || !pEnd || !pStart->getChildren().size())
      return false;

    set<Node<T> *>   discovered; 
    queue<Node<T> *> toVisit;
    
    toVisit.push(pStart);
    discovered.insert(pStart);
    
    while(toVisit.size())
    {
      Node<T> * node = toVisit.front();
      
      toVisit.pop();
      
      if(node == pEnd)
	return true;
      
      for(size_t i = 0; i < node->getChildren().size(); ++i)
      {
	//If one of the children is the pEnd node, report path found.
	if(node->getChildren()[i] == pEnd)
	  return true;
	
	//If this child node was not visited earlier, enqueue it.
	pair<typename set<Node<T> *>::iterator, bool> pSet(discovered.insert(node->getChildren()[i]));
	if(pSet.second)
	  toVisit.push(node->getChildren()[i]);
	
      }//for
    }//while
  }

} // end namespace TestGraph

#endif

