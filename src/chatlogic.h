#ifndef CHATLOGIC_H_
#define CHATLOGIC_H_

#include <vector>
#include <string>
#include "chatgui.h"

// forward declarations
class ChatBot;
class GraphEdge;
class GraphNode;


class ChatLogic
{
private:
    // proprietary type definitions
    typedef std::vector<std::pair<std::string, std::string>> tokenlist;

    // pointers to chatbot elements
    std::vector<GraphNode *> _nodes;
    std::vector<GraphEdge *> _edges;
    GraphNode *_currentNode;
    ChatBot *_chatbot;
    ChatBotPanelDialog *_chatBotPanelDialog;

    // proprietary functions
    template <typename T>
    T *AddToElementList(int id, std::vector<T *> &elems); // checks wether a given edge or node already exist based on their id
    template <typename T>
    void addAllTokensToElement(std::string tokenID, tokenlist &tokens, T *element);

public:
    // constructor / destructor
    ChatLogic();
    ~ChatLogic();

    // getter / setter
    ChatBotPanelDialog *getChatBotPanelDialog() { return _chatBotPanelDialog; }
    ChatBot *getChatBot() { return _chatbot; }
    void setChatBotPanelDialog(ChatBotPanelDialog *dialog) { _chatBotPanelDialog = dialog; }

    // proprietary functions
    void LoadAnswerGraphFromFile(std::string filename);
};

#endif /* CHATLOGIC_H_ */