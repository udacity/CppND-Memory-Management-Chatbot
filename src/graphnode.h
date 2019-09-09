#ifndef GRAPHNODE_H_
#define GRAPHNODE_H_

#include <vector>
#include <string>

// forward declarations
class GraphEdge; 
class ChatBot;

class GraphNode
{
private:
    // pointers to chatbot elements
    std::vector<GraphEdge *> _parentEdges; // edges to preceding nodes
    std::vector<GraphEdge *> _childEdges;  // edges to subsequent nodes
    ChatBot *_chatBot;

    // proprietary members
    int _id;
    std::vector<std::string> _answers;
    

public:
    // constructor / destructor
    GraphNode(int id);

    // getter / setter
    int GetID() { return _id; }
    std::vector<GraphEdge *> GetEdgesToChildNodes() { return _childEdges; };
    std::vector<std::string> GetAnswers() { return _answers; }
    int GetNumberOfParents() { return _parentEdges.size(); }

    // proprietary functions
    void AddToken(std::string token); // add answers to list
    void AddEdgeToParentNode(GraphEdge *edge);
    void AddEdgeToChildNode(GraphEdge *edge);
    void moveChatbotHere(ChatBot *chatbot);
    void moveChatbotToNewNode(GraphNode *newNode);
};

#endif /* GRAPHNODE_H_ */