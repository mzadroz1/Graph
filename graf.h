#ifndef GRAF_H
#define GRAF_H

#include<iostream>
#include<fstream>
#include<vector>
#include<stack>
#include<algorithm>
#include<utility>

class Graph
{
    unsigned vertex;
    std::vector<std::pair<unsigned,unsigned>> edgVec;
    std::vector<unsigned> *adjVec;

public:
    Graph()
    {
        vertex=0;
        adjVec=nullptr;
    }
    ~Graph()
    {
        if(adjVec!=nullptr)
            delete [] adjVec;
    }
    Graph(const unsigned v, const std::vector<std::pair<unsigned,unsigned>> edg)
    {
        vertex=v;
        edgVec=edg;
        adjVec = new std::vector<unsigned>[vertex];
        for(unsigned i=0; i<edg.size(); ++i)
        {
            adjVec[edg[i].first].push_back(edg[i].second);
            adjVec[edg[i].second].push_back(edg[i].first);
        }
    }

    bool isConnected(unsigned v1, unsigned v2) const
    {
        if(vertex-2==0) return true;

        std::stack<unsigned> s;
        unsigned counter=0;
        bool visited[vertex];
        for(unsigned i=0; i<vertex; ++i)
        {
            if(i==v1 || i==v2) visited[i]=true;
            else visited[i]=false;
        }

        unsigned start=0;
        while(start==v1 || start==v2)
            ++start;
        s.push(start);
        visited[start]=true;

        unsigned v;
        while(!s.empty())
        {
            v=s.top();
            s.pop();
            counter++;
            for(unsigned i=0; i<adjVec[v].size(); ++i)
            {
                if(!visited[adjVec[v][i]])
                {
                    visited[adjVec[v][i]] = true;
                    s.push(adjVec[v][i]);
                }
            }
        }
        if(counter==vertex-2) return true;
        else return false;
    }

    std::vector<std::pair<unsigned,unsigned>> findBridges()
    {
        std::vector<std::pair<unsigned,unsigned>> bridges;

        for(unsigned i = 0; i < edgVec.size(); ++i)
        {
            if(!isConnected( edgVec[i].first, edgVec[i].second ))
                bridges.push_back(std::make_pair( edgVec[i].first, edgVec[i].second ));
        }
        return bridges;
    }
};

void readGraph(unsigned &v, std::vector<std::pair<unsigned,unsigned>> &edg)
{
    std::cin>>v;
    unsigned v1,v2;
    std::pair<unsigned,unsigned> edge;
    while(std::cin>>v1)
    {
        std::cin>>v2;
        edge = std::make_pair(v1,v2);
        edg.push_back(edge);
    }
}


void printBridges(const std::vector<std::pair<unsigned,unsigned>> bridges)
{
    for(unsigned i=0; i<bridges.size(); ++i)
    {
        std::cout<<bridges[i].first<<" "<<bridges[i].second<<std::endl;
    }
}



#endif
