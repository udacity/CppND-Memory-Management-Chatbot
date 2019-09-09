#include "graphnode.h"
#include "graphedge.h"

GraphEdge::GraphEdge(int id)
{
    _id = id;
}

void GraphEdge::SetChildNode(GraphNode *childNode)
{
    _childNode = childNode;
    _childNode->AddEdgeToParentNode(this);
}

void GraphEdge::SetParentNode(GraphNode *parentNode)
{
    _parentNode = parentNode;
    _parentNode->AddEdgeToChildNode(this);

}

void GraphEdge::AddToken(std::string token)
{
    _keywords.push_back(token);
}