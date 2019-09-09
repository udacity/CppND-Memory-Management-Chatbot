#ifndef CHATBOT_H_
#define CHATBOT_H_

#include <string>

class GraphNode; // forward declaration
class ChatLogic; // forward declaration

class ChatBot
{
private:

    // pointers to chatbot elements
    GraphNode *_currentNode;
    GraphNode *_rootNode;
    ChatLogic *_chatLogic;

    // proprietary functions
    int ComputeLevenshteinDistance(std::string s1, std::string s2);

public:
    // constructors / destructors
    ChatBot() {}

    // getters / setters
    void SetCurrentNode(GraphNode *node);
    void SetRootNode(GraphNode *rootNode) { _rootNode = rootNode; }
    void SetChatLogic(ChatLogic *chatLogic) { _chatLogic = chatLogic; }

    // proprietary functions
    void ReceiveUserQuery(std::string query);
    
};

#endif /* CHATBOT_H_ */