#include <iostream>
#include <vector>

using namespace std;

template <class N, class E> class Edge;

template<class N> class NodeAlreadyExists;

template<class N> class NodeDoesNotExist;

template<class N> class EdgeAlreadyExists;

template<class N> class EdgeDoesNotExist;

template <class N, class E>
class Node {
public:
    N info;
    vector< Edge<N,E> > edges;
    Node(N inf) {
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
    Graph(){nodes.clear();}
    ~Graph(){for(Node<N,E> * n: nodes){delete n;};}
    Graph & addNode(const N &inf){
        for(Node<N,E>* n:nodes){
            if(n->info == inf)
                throw NodeAlreadyExists<N>(inf);
        }
        nodes.push_back(new Node<N,E>(inf));
        return *this;
    }
    Graph & addEdge(const N &begin, const N &end, const E &val){
        bool exist1 = false, exist2 = false;
        int i1 = 0, i2 = 0;
        for(i1; i1< nodes.size(); i1++)
        {
            if(nodes[i1]->info == begin){
                exist1 = true;
                break;
            }
        }
        if(!exist1)
            throw NodeDoesNotExist<N>(begin);
        for(i2; i2 < nodes.size(); i2++)
        {
            if(nodes[i2]->info == end){
                exist2 = true;
                break;
            }
        }
        if(!exist2)
            throw NodeDoesNotExist<N>(end);
        for(Edge<N,E> e:nodes[i1]->edges)
        {
            if(e.destination->info == end)
                throw EdgeAlreadyExists<N>(begin, end);
        }
        nodes[i1]->edges.push_back(Edge<N,E>(nodes[i2], val));
        return *this;
    }
    Graph & removeEdge(const N &begin, const N &end){
        for(Node<N, E> * &n:nodes)
        {
            if(n->info == begin){
                for(int i = 0; i < n->edges.size(); i++)
                    if(n->edges[i].destination->info == end){
                        n->edges.erase(n->edges.begin() + i);
                        return *this;
                    }
                throw EdgeDoesNotExist<N>(begin, end);
            }
        }
        throw  NodeDoesNotExist<N>(begin);
    }
    E & edgeValue(const N &begin, const N &end){
        for(Node<N, E> * &n:nodes)
        {
            if(n->info == begin){
                for(Edge<N,E> &e:n->edges)
                    if(e.destination->info == end)
                        return (e.value);
                throw EdgeDoesNotExist<N>(begin, end);
            }
        }
        throw  NodeDoesNotExist<N>(begin);
    }
    unsigned numEdges(void) const{
        unsigned sum = 0;
        for(Node<N,E> * n:nodes){
            sum += n->edges.size();
        }
        return sum;
    }
    unsigned numNodes(void) const{return nodes.size();}
    void print(std::ostream &os) const
    {
        for(Node<N,E>* n:nodes)
        {
            os << "( " << n->info;
            for(Edge<N,E> e:n->edges){
                os << "[ " << e.destination->info << " " << to_string(e.value) << "] ";
            }
            os << ") ";
        }
    }
};
template<class N, class E>
ostream & operator<<(ostream &out, const Graph<N,E> &g){
    g.print(out);
    return out;
}
template <class N, class E>
std::ostream & operator<<(std::ostream &out, const Graph<N,E> &g);


// exception NodeAlreadyExists
template <class N>
class NodeAlreadyExists
{
public:
    N info;
    NodeAlreadyExists(N inf) { info=inf; }
};

template <class N>
std::ostream & operator<<(std::ostream &out, const NodeAlreadyExists<N> &no)
{ out << "Node already exists: " << no.info; return out; }


// exception NodeDoesNotExist
template <class N>
class NodeDoesNotExist {
public:
    N info;
    NodeDoesNotExist(N inf) {
        info = inf;
    }
};

template <class N>
std::ostream & operator<<(std::ostream &out, const NodeDoesNotExist<N> &no)
{ out << "Node does not exist: " << no.info; return out; }

template<class N>
class EdgeAlreadyExists{
public:
    N begin, end;
    EdgeAlreadyExists(const N &begin,const N &end){
        this->begin = begin;
        this->end = end;
    }
 };

template<class N>
std::ostream & operator<<(std::ostream &out, const EdgeAlreadyExists<N>&error){
    out << "Edge already exists: " << error.begin << " , " << error.end;
    return out;
}

template<class N>
class EdgeDoesNotExist{
public:
    N begin, end;
    EdgeDoesNotExist<N>(const N &begin, const N &end){ this->begin = begin; this->end = end;}
};

template<class N>
ostream & operator<<(ostream& out, const EdgeDoesNotExist<N> &error){
    out << "Edge does not exist: " << error.begin << " , " << error.end;
    return out;
}