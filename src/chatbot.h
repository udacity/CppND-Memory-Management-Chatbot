#ifndef CHATBOT_H_
#define CHATBOT_H_

#include <wx/bitmap.h>
#include <string>

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
    ChatBot()
    { 
        std::cout << "ChatBot Constructor Called\n"; 
    };                     // constructor WITHOUT memory allocation
    ChatBot(std::string filename)
    { 
        std::cout << "ChatBot Constructor Called\n"; 
    }; // constructor WITH memory allocation
    ~ChatBot()
    { 
        std::cout << "ChatBot Destructor Called\n"; 
    };

    //// STUDENT CODE
    ////
    // copy constructor
    ChatBot(const ChatBot &source) 
    { 
        std::cout << "ChatBot Copy Constructor Called\n"; 
    };
    // copy assignment operator
    ChatBot& operator=(const ChatBot& source)
    {
        std::cout << "ChatBot Copy Assignment Operator Called\n";
        if (this == &source)
            return *this;
        return *this;
    };
    // move constructor
    ChatBot(ChatBot&& source)
    { 
        std::cout << "ChatBot Move Constructor Called\n"; 
    };
    // move assignment operator
    ChatBot &operator=(ChatBot &&source) 
    {
        std::cout << "ChatBot Move Assignment Operator Called\n";
        if (this == &source)
            return *this;
        return *this;
    }    
    ////
    //// EOF STUDENT CODE

    // getters / setters
    void SetCurrentNode(GraphNode *node);
    void SetRootNode(GraphNode *rootNode) { _rootNode = rootNode; }
    void SetChatLogicHandle(ChatLogic *chatLogic) { _chatLogic = chatLogic; }
    ChatLogic* GetChatLogicHandle() { return _chatLogic; }
    wxBitmap *GetImageHandle() { return _image; }

    // communication
    void ReceiveMessageFromUser(std::string message);
};

#endif /* CHATBOT_H_ */
