#ifndef CHATBOT_H_
#define CHATBOT_H_

#include <wx/bitmap.h>
#include <string>
#include <iostream>

class GraphNode; // forward declaration
class ChatLogic; // forward declaration

class ChatBot
{
private:
    // data handles (owned)
    wxBitmap *_image; // avatar image

    // data handles (not owned)
    GraphNode *_currentNode;
    GraphNode *_rootNode;
    ChatLogic *_chatLogic;

    // proprietary functions
    int ComputeLevenshteinDistance(std::string s1, std::string s2);

public:
    // constructors / destructors
    ChatBot();                      // constructor WITHOUT memory allocation
    ChatBot(std::string filename);  // constructor WITH memory allocation
    ~ChatBot();
    ChatBot(const ChatBot &source); // copy constructor
    ChatBot(ChatBot &&source);      // move constructor

    // TODO: Is this the best place to implement copy assignment operator?
    ChatBot &operator=(const ChatBot &source)
    {
        std::cout << "ASSIGNING content of instance " << &source << " to instance " << this << std::endl;

        if (this == &source) { return *this; }

        this->_image = nullptr;
        this->_chatLogic = nullptr;
        this->_rootNode = nullptr;

        // Copy Data
        this->_chatLogic = source._chatLogic;
        this->_rootNode = source._rootNode;
        this->_image = source._image;
        return *this;
    }


    // getters / setters
    void SetCurrentNode(GraphNode *node);
    void SetRootNode(GraphNode *rootNode) { _rootNode = rootNode; }
    void SetChatLogicHandle(ChatLogic *chatLogic) { _chatLogic = chatLogic; }
    wxBitmap *GetImageHandle() { return _image; }

    // communication
    void ReceiveMessageFromUser(std::string message);
};

#endif /* CHATBOT_H_ */