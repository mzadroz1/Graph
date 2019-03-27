#include "graf.h"

int main()
{
    unsigned v;
    std::vector<std::pair<unsigned,unsigned>> edg;
    readGraph(v,edg);
    Graph g(v,edg);
    printBridges(g.findBridges());

    return 0;
}
