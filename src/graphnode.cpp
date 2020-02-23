#include "graphedge.h"
#include "graphnode.h"
#include <iostream>

GraphNode::GraphNode(int id)
{
    //std::cout << "GraphNode Constructor" << std::endl;

    _id = id;
}

GraphNode::~GraphNode()
{
    //// STUDENT CODE
    ////
    //std::cout << "GraphNode Destructor" << std::endl;
 
 //   std::cout << "Chatbot address " << _chatBot << std::endl;
 //   if (_chatBot != nullptr){
 //       std::cout << "Delete Chatbot in GraphNode" << std::endl;
 //       delete _chatBot; 
 //       _chatBot = nullptr;
 //       std::cout << "Chatbot address " << _chatBot << std::endl;
 //   }

    ////
    //// EOF STUDENT CODE
}

void GraphNode::AddToken(std::string token)
{
    _answers.push_back(token);
}

void GraphNode::AddEdgeToParentNode(GraphEdge *edge)
{
    _parentEdges.push_back(edge);
}

void GraphNode::AddEdgeToChildNode(GraphEdge *edge)
{
    _childEdges.push_back(edge);
}

//// STUDENT CODE
////
void GraphNode::MoveChatbotHere(ChatBot *chatbot)
{
    _chatBot = chatbot;
    _chatBot->SetCurrentNode(this);
}

void GraphNode::MoveChatbotToNewNode(GraphNode *newNode)
{
    newNode->MoveChatbotHere(_chatBot);
    _chatBot = nullptr; // invalidate pointer at source
}
////
//// EOF STUDENT CODE

GraphEdge *GraphNode::GetChildEdgeAtIndex(int index)
{
    //// STUDENT CODE
    ////

    return _childEdges[index];

    ////
    //// EOF STUDENT CODE
}