#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <tuple>
#include <algorithm>

#include "graphedge.h"
#include "graphnode.h"
#include "chatbot.h"
#include "chatlogic.h"

ChatLogic::ChatLogic()
{
    // create instance of chatbot
    _chatbot = new ChatBot();

    // add pointer to chatlogic so that chatbot answers can be passed on to the GUI
    _chatbot->SetChatLogic(this);
}

ChatLogic::~ChatLogic()
{
    // delete chatbot instance again
    delete _chatbot;

    // delete all instances of edged and nodes
    for (auto it : _nodes)
        delete it;

    for (auto it : _edges)
        delete it;
}

template <typename T>
T *ChatLogic::AddToElementList(int id, std::vector<T *> &elems)
{
    // check if element with this id exists already
    T *elem = nullptr;
    auto exists = std::find_if(elems.begin(), elems.end(), [&id](T *&elem) { return elem->GetID() == id; });
    if (exists != elems.end())
    {
        elem = *exists; // assign pointer
    }
    else
    {
        // create new element and add it to the vector
        elem = new T(id);
        elems.push_back(elem);
    }
    return elem;
}

template <typename T>
void ChatLogic::addAllTokensToElement(std::string tokenID, tokenlist &tokens, T *element)
{
    // find all occurences for current node
    auto token = tokens.begin();
    while (true)
    {
        token = std::find_if(token, tokens.end(), [&tokenID](const std::pair<std::string, std::string> &pair) { return pair.first == tokenID;; });
        if (token != tokens.end())
        {
            element->AddToken(token->second); // add new keyword to edge
            token++;                          // increment iterator to next element
        }
        else
        {
            break; // quit infinite while-loop
        }
    }
}

void ChatLogic::LoadAnswerGraphFromFile(std::string filename)
{
    // load file with answer graph elements
    std::ifstream file(filename);

    // check for file availability and process it line by line
    if (file)
    {
        // loop over all lines in the file
        std::string lineStr;
        while (getline(file, lineStr))
        {
            // extract all tokens from current line
            tokenlist tokens;
            while (lineStr.size() > 0)
            {
                // extract next token
                int posTokenFront = lineStr.find("<");
                int posTokenBack = lineStr.find(">");
                if (posTokenFront < 0 || posTokenBack < 0)
                    break; // quit loop if no complete token has been found
                std::string tokenStr = lineStr.substr(posTokenFront + 1, posTokenBack - 1);

                // extract token type and info
                int posTokenInfo = tokenStr.find(":");
                if (posTokenInfo != std::string::npos)
                {
                    std::string tokenType = tokenStr.substr(0, posTokenInfo);
                    std::string tokenInfo = tokenStr.substr(posTokenInfo + 1, tokenStr.size() - 1);

                    // add token to vector
                    tokens.push_back(std::make_pair(tokenType, tokenInfo));
                }

                // remove token from current line
                lineStr = lineStr.substr(posTokenBack + 1, lineStr.size());
            }

            // process tokens for current line
            auto type = std::find_if(tokens.begin(), tokens.end(), [](const std::pair<std::string, std::string> &pair) { return pair.first == "TYPE"; });
            if (type != tokens.end())
            {
                // check for id
                auto id = std::find_if(tokens.begin(), tokens.end(), [](const std::pair<std::string, std::string> &pair) { return pair.first == "ID"; });
                if (id != tokens.end())
                {
                    // node-based processing
                    if (type->second == "NODE")
                    {
                        // check if node already exists and add it to list if not
                        GraphNode *node = AddToElementList<GraphNode>(std::stoi(id->second), _nodes);

                        // find all answers for current node
                        addAllTokensToElement("ANSWER", tokens, node);
                    }

                    // edge-based processing
                    if (type->second == "EDGE")
                    {
                        // check if edge already exists and add it to list if not
                        GraphEdge *edge = AddToElementList<GraphEdge>(std::stoi(id->second), _edges);

                        // find tokens for incoming (parent) and outgoing (child) node
                        auto inToken = std::find_if(tokens.begin(), tokens.end(), [](const std::pair<std::string, std::string> &pair) { return pair.first == "PARENT"; });
                        auto outToken = std::find_if(tokens.begin(), tokens.end(), [](const std::pair<std::string, std::string> &pair) { return pair.first == "CHILD"; });
                        if (inToken != tokens.end() && outToken != tokens.end())
                        {
                            // get iterator on incoming and outgoing node via ID search
                            auto inNode = std::find_if(_nodes.begin(), _nodes.end(), [&inToken](GraphNode *&node) { return node->GetID() == std::stoi(inToken->second); });
                            auto outNode = std::find_if(_nodes.begin(), _nodes.end(), [&outToken](GraphNode *&node) { return node->GetID() == std::stoi(outToken->second); });

                            // assign connections to current edge
                            edge->SetChildNode(*outNode);
                            edge->SetParentNode(*inNode);
                        }

                        // find all keywords for current node
                        addAllTokensToElement("KEYWORD", tokens, edge);
                    }
                }
                else
                {
                    std::cout << "Error: ID missing. Line is ignored!" << std::endl;
                }
            }
        } // eof loop over all lines in the file

        file.close();

    } // eof check for file availability
    else
    {
        std::cout << "File could not be opened!" << std::endl;
        return;
    }

    // identify root node
    GraphNode *rootNode = nullptr;
    for (auto it : _nodes)
    {
        // search for nodes which have no incoming edges
        if (it->GetNumberOfParents() == 0)
        {
            if (rootNode == nullptr)
            {
                rootNode = it; // assign current node to root
            }
            else
            {
                std::cout << "ERROR : Multiple root nodes detected" << std::endl;
            }
        }
    }

    // add chatbot to graph root node using move semantics
    _chatbot->SetRootNode(rootNode);
    rootNode->moveChatbotHere(_chatbot);
}
