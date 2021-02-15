#include <iostream>
#include <vector>

using namespace std;

template <class N, class E> class Edge;

template <class N, class E>
class Node {
public:
    N info;
    vector< Edge<N,E> > edges;
    Node(N inf)
    {
        info = inf;
    }
};

template <class N, class E>
class Edge {
public:
    E value;
    Node<N,E> *destination;
    Edge(Node<N,E> *dest, E val) {
        value = val;
        destination = dest;
    }
};

template <class N, class E>
class Graph {
    vector< Node<N,E> *> nodes;
public:
    Graph();
    ~Graph();
    Graph & addNode(const N &inf);
    Graph & addEdge(const N &begin, const N &end, const E &val);
    Graph & removeEdge(const N &begin, const N &end);
    E & edgeValue(const N &begin, const N &end);
    unsigned numEdges(void) const;
    unsigned numNodes(void) const;
    void print(std::ostream &os) const;
};


/**
 * Constructor of the class Graph
 * @tparam N Node
 * @tparam E Edge
 */
template<class N, class E>
Graph<N, E>::Graph()
{
    nodes.clear();
}


/**
 * Destructor of the class Graph
 * @tparam N Nodes
 * @tparam E Edges
 */
template<class N, class E>
Graph<N, E>::~Graph()
{
    for(size_t i = 0; i < nodes.size(); i--)
    {
        delete nodes[i];
    }
}


/**
 * Function that return the number os nodes of the graph
 * @tparam N Nodes
 * @tparam E Edges
 * @return The number of the nodes of the graph
 */
template<class N, class E>
unsigned Graph<N, E>::numNodes(void) const
{
    return nodes.size();
}


/**
 * Function that returns the number of edges of the graph
 * @tparam N Nodes
 * @tparam E Edges
 * @return The number of edges of the graph
 */
template<class N, class E>
unsigned Graph<N, E>::numEdges(void) const
{
    int total = 0;
    for(size_t i = 0; i < nodes.size(); i++)
    {
        total += nodes[i]->edges.size();
    }
    return total;
}


/**
 * Exception used when is created a node that already exists
 * @tparam N
 */
template <class N>
class NodeAlreadyExists
{
public:
    N info;
    NodeAlreadyExists(N inf) { info=inf; }
};


/**
 * Function that adds another node to the graph and throws an exception if that node already exists
 * @tparam N Node
 * @tparam E Edge
 * @param info Name of the node
 * @return This function return the changed graph ('this' value)
 */
template<class N, class E>
Graph<N, E> & Graph<N,E>::addNode(const N &info)
{
    for(size_t i = 0; i < nodes.size(); i++)
    {
        if(nodes[i]->info == info)
            throw NodeAlreadyExists<N>(nodes[i]->info);
    }
    nodes.push_back(new Node<N,E>(info));
    return *this;
}


/**
 * Operator << used to print the exception NodeAlreadyExists
 * @tparam N Type of the Node
 * @param out Ostream used t print the exception
 * @param no Exception that the operator uses
 * @return The ostream used
 */
template <class N>
std::ostream & operator<<(std::ostream &out, const NodeAlreadyExists<N> &no)
{ out << "Node already exists: " << no.info; return out; }


/**
 * Exception NodeDoesNotExist used when is used a node that doesn't exists
 * @tparam N type of the node
 */
template <class N>
class NodeDoesNotExist {
public:
    N info;
    NodeDoesNotExist(N inf) {
        info = inf;
    }
};

/**
 * Exception EdgeAlreadyExists used when it is added an edge that already exists to a node
 * @tparam N type of the nodes
 */
template<class N>
class EdgeAlreadyExists{
        public:
            N start, end;
            EdgeAlreadyExists<N>(N begin, N final)
            {
                start = begin;
                end = final;
            }
};


/**
 * Exception used when is used an edge that doesn't exist
 * @tparam N type of the nodes
 */
template<class N>
class EdgeDoesNotExist{
public:
    N start, end;
    EdgeDoesNotExist<N>(N begin, N final)
    {
        start = begin;
        end = final;
    }

};


/**
 *Operator << used to print the exception EdgeAlreadyExists
 * @tparam N Type of the nodes
 * @param out Ostream used to print the exception
 * @param edge Exception that the operator uses
 * @return The ostream used
 */
template<class N>
std::ostream & operator<<(std::ostream & out, const EdgeDoesNotExist<N> &edge)
{
    out << "Edge does not exist: " << edge.start << " , " << edge.end;
    return out;
}


/**
 * Function that gives the value of the edge that connects two nodes
 * @tparam N Type of the node
 * @tparam E Type of the edge
 * @param begin Node where the edge begins
 * @param end Node where the edge ends
 * @return The value of the edge
 */
template<class N, class E>
E & Graph<N,E>::edgeValue(const N &begin, const N &end)
{
    bool find = false;
    for(size_t i = 0; i < nodes.size(); i++)
    {
        if(nodes[i]->info == begin) {
            find = true;
            for (size_t j = 0; j < nodes[i]->edges.size(); j++) {
                if(nodes[i]->edges[j].destination->info == end)
                    return nodes[i]->edges[j].value;
            }
        }
    }
    if(find)
        throw EdgeDoesNotExist<N>(begin, end);
    else
        throw NodeDoesNotExist<N>(begin);
}


/**
 * Function that removes an edge of the graph
 * @tparam N Type of the nodes
 * @tparam E Type of the edges
 * @param begin Node where the edge begins
 * @param end Node where the edge ends
 * @return The changed Graph
 */
template<class N, class E>
Graph<N,E> & Graph<N,E>::removeEdge(const N &begin, const N &end)
{
    bool find = false;
    for(size_t i = 0; i < nodes.size(); i++)
    {
        if(nodes[i]->info == begin)
        {
            find = true;
            for(size_t j = 0; j < nodes[i]->edges.size(); j++)
            {
                if(nodes[i]->edges[j].destination->info == end)
                {
                    nodes[i]->edges.erase(nodes[i]->edges.begin()+j);
                    return *this;
                }
            }
            throw EdgeDoesNotExist<N>(begin, end);
        }
    }
    throw NodeDoesNotExist<N>(begin);
}


/**
 *Function that adds an edge to a node of the graph
 * @tparam N type of the Node
 * @tparam E type of the Edge
 * @param begin Node where the edge begins
 * @param end Node where the edge ends
 * @param val Value of the edge
 * @return This function returns the changed Graph (*this)
 */
template<class N, class E>
Graph<N, E> & Graph<N,E>::addEdge(const N &begin, const N &end, const E &val)
{
    size_t index;
    bool node1 = false, node2 = false;
    for(size_t i = 0; i < nodes.size(); i++)
    {
        if(nodes[i]->info == begin) {
            node1 = true;
            index = i;
        }
        else if(nodes[i]->info == end)
            node2 = true;
    }
    if(!node1)
        throw NodeDoesNotExist<N>(begin);
    else if(!node2)
        throw NodeDoesNotExist<N>(end);
    else
    {
        for(size_t j = 0; j < nodes[index]->edges.size(); j++)
        {
            if(nodes[index]->edges[j].destination->info == end)
                throw EdgeAlreadyExists<N>(begin, end);
        }
        nodes[index]->edges.push_back(Edge<N,E>(new Node<N,E>(end), val));
    }
    return *this;
}


/**
 *Operator << used to print the exception EdgeAlreadyExists
 * @tparam N Type of the nodes
 * @param out Ostream used to print the exception
 * @param edge Exception that the operator uses
 * @return The ostream used
 */
template<class N>
std::ostream & operator<<(std::ostream & out, const EdgeAlreadyExists<N> &edge)
{
    out << "Edge already exists: " << edge.start << " , " << edge.end;
    return out;
}


/**
 * Operator << used to print the exception NodeDoesNotExist
 * @tparam N Type of the Node
 * @param out Ostream used t print the exception
 * @param no Exception that the operator uses
 * @return The ostream used
 */
template <class N>
std::ostream & operator<<(std::ostream &out, const NodeDoesNotExist<N> &no)
{ out << "Node does not exist: " << no.info; return out; }


/**
 * Function that uses th ostream to print the information of the Graph
 * @tparam N Type of the nodes
 * @tparam E Type of the edges
 * @param os ostream used
 */
template<class N, class E>
void Graph<N,E>::print(std::ostream &os) const
{
    for(size_t i = 0; i < nodes.size(); i++)
    {
        os << "( " << nodes[i]->info;
        for(size_t j = 0; j < nodes[i]->edges.size(); j++)
        {
            os << "[ " << nodes[i]->edges[j].destination->info << " " << nodes[i]->edges[j].value << "] ";
        }
        os << ") ";
    }
}

/**
 * Operator used to print the Graph
 * @tparam N Type of the nodes
 * @tparam E Type of the edges
 * @param out ostream used
 * @param g Graph that should be printed
 * @return The ostream used
 */
template<class N, class E>
std::ostream & operator<<(std::ostream &out, const Graph<N,E> &g)
{
    g.print(out);
    return out;
}