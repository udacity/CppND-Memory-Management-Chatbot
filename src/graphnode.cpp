#include "graphnode.h"
#include "graphedge.h"

GraphNode::GraphNode(int id) { _id = id; }

GraphNode::~GraphNode() { std::cout << "GraphNode Destructor\n"; }

void GraphNode::AddToken(std::string token) { _answers.push_back(token); }

void GraphNode::AddEdgeToParentNode(GraphEdge *edge) {
  _parentEdges.push_back(edge);
}

void GraphNode::AddEdgeToChildNode(std::unique_ptr<GraphEdge> edge) {
  _childEdges.push_back(std::move(edge));
}

void GraphNode::MoveChatbotHere(ChatBot chatBot) {
  // replace the object managed by _chatBot before setting current node
  _chatBot.reset(new ChatBot());
  *_chatBot = std::move(chatBot);
  _chatBot->SetCurrentNode(this);
}

void GraphNode::MoveChatbotToNewNode(GraphNode *newNode) {
  newNode->MoveChatbotHere(std::move(*_chatBot));
  // release the pointer
  _chatBot.reset();
}

GraphEdge *GraphNode::GetChildEdgeAtIndex(int index) {

  return _childEdges[index].get();
}