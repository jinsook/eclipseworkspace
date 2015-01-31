/*
 * mainprism.cpp
 *
 *  Created on: 2013. 10. 1.
 *      Author: jin sook
 */

class Node{

public:
	enum NType{ Empty, Prism, Wall };

public:
	Node(NType type)
	: mType(type)
	{}

	Node(NType type)

	NType getNodeType() const { return mType; }

private:
	NType mType;

};

class PrismNode : public Node {

public:
	enum Direct{ East, South, North, West};

	PrismNode(Direct direct):
		Node(Prism), mDirect(direct)
	{}

	void setVisited() { mVisited = true; }
	bool isVisited() const { return mVisited; }
	Direct getDirect() const { return mDirect; }
private:
	Direct mDirect;
	bool mVisited;
};

class PrismRoom{

	int traverse(){

		Node curNode; //TODO!!! initialize
		int row,column; //TODO initilize

		PrismNode::Direct direct = PrismNode::East;

		while (curNode.getNodeType() != Node::Wall ){


			if (curNode.getNodeType() == Node::Prism){
				//change direction
				PrismNode& node = dynamic_cast<PrismNode>(curNode);
				if ( node.isVisited() ) return -1; // infinite loop
				direct = node.getDirect();
				node.setVisited();
			}

			switch ( direct ){
			case PrismNode::East: curNode = mRoom[row][++column]; break;
			case PrismNode::West: curNode = mRoom[row][--column]; break;
			case PrismNode::South: curNode = mRoom[++row][column]; break;
			case PrismNode::North: curNode = mRoom[--row][column]; break;
			default:
				assert(0);
			}
		}

		return -1;
	}
private:
	enum {MAXROW=50, MAXCOLUMN=50};
	Node mRoom[MAXROW][MAXCOLUMN];
};


