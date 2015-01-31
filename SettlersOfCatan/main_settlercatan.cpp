/*!
 * \brief Find out the length of the longest road for the given input.
 * The input contains the roads built.( Solving SK C&C problem.)
 * \author Choi, Jinsook
 */

#include <iostream>
#include <fstream>

using namespace std;

/*!
 * \class Node represents a city.
 */
class Node{

	int mDepth;
	int mNCount; ///< neighbor count
	int mNeighbor[3]; ///< adjacent node numbers
	bool mBeenIn[3]; ///< have we been in the node mNeighbor[i] from current node?
	                 ///< meaning, the edge between the current node and the neighbor visited?
public:
	Node(){
		mDepth = -1;
		mNCount = 0;
		for (int i=0; i <3; i++) {
			mNeighbor[i]=-1;
			mBeenIn[i] = false;
		}
	}

	/*!
	 * add node number n as neighbor
	 */
	void putNeighbor( int n) {
		if (mNCount >= 3){
			cerr<<"Input is wrong. There are more than 3 roads connected to a city"<<endl;
			assert(mNCount<3);
		}
		mNeighbor[mNCount] =n;
		mNCount++;
	}

	/*!
	 * return the node number of ith neighbor
	 */
	int neighbor(int i) const { return mNeighbor[i];}

	/*!
	 * return the number of neighbors
	 */
	int numNeighbor() const { return mNCount;}

	/*!
	 * return the depth of the current node from the root
	 */
	int depth() const { return mDepth;}

	/*!
	 * set the depth of the current node from the root as d
	 */
	void setDepth(int d){ mDepth = d; }

	/*!
	 * visited the ith neighbor?
	 */
	bool beenIn(int i) const { return mBeenIn[i]; }

	/*!
	 * set the ith neighbor as visited
	 */
	void setBeenIn(int i) { mBeenIn[i] = true;}

	/*!
	 * set the neighbor with node number nn as visited
	 */
	void setBeenInNode(int nn){
		for (int i=0; i<3; i++ )
			if (mNeighbor[i]==nn) mBeenIn[i] = true;
	}

};

/*!
 * The Settlers of Catan game.
 * Currently, we have only the method to calculate the longest road.
 */
class SettlerCatan
{
	Node *mNodes;
	int mDeepest;
	int mNumNode;

public:

	SettlerCatan(){
		mNodes = 0;
		mDeepest = -1;
		mNumNode =0;
	}

	~SettlerCatan(){
		if (mNodes) delete [] mNodes;
	}

	/*!
	 * restart to build roads. clears all internal memory
	 * and gets ready for a net set of roads.
	 */
	void resetLongestRoad(int nNode, int nEdge){
		mNumNode = nNode;
		if (mNodes) delete [] mNodes;

		mNodes = new Node[mNumNode];
		mDeepest = -1;
	}

	/*!
	 * add road between node1 and node2
	 */
	void putRoad(int node1, int node2){
		mNodes[node1].putNeighbor(node2);
		mNodes[node2].putNeighbor(node1);
	}

	/*!
	 * calculate and return the longest road length
	 * for the given set of roads
	 */
	int getLongestRoadLength() {

		//try depthFirst with each node as the root node.
		for (int i=0; i <mNumNode; i++){
			Node *newNodes = new Node[mNumNode];
			for (int j=0; j<mNumNode; j++)	newNodes[j]=mNodes[j];
			depthFirst(newNodes, i, 0);
			delete newNodes;
		}

		return mDeepest;
	}

private:

	/*!
	 * traverse the network nodes depthFirst starting nodes[numNum].
	 * The starting depth of node[nodeNum] is newDepth
	 */
	void depthFirst(Node *nodes, int nodeNum, int newDepth){

		Node &node = nodes[nodeNum];

		if (node.depth() > newDepth) return;
		node.setDepth(newDepth);
	//	cout<<"depth("<<nodeNum<<")="<<newDepth<<endl;

		if (mDeepest<newDepth) mDeepest=newDepth;

		for( int i =0; i< node.numNeighbor(); i++) {

			int ni = node.neighbor(i);
			if( node.beenIn(i)) continue;
			node.setBeenIn(i);
			nodes[ni].setBeenInNode(nodeNum);

			//try each node ahead with a new set of nodes which keep the history up to now.
			Node *newNodes = new Node[mNumNode];
			for (int j=0; j<mNumNode; j++)	newNodes[j] = nodes[j];
			depthFirst(newNodes, node.neighbor(i), node.depth()+1);
			delete newNodes;
		}
	}

};

void usage(){
	cerr<<"usage: settler filename"<<endl;
	exit(-1);
}

int main(int argc, char** argv)
{
	if ( argc < 2 ){
		usage();
	}

	ifstream ifs(argv[1], ifstream::in);
	if (!ifs.is_open()) {
		cerr<<"file "<<argv[1]<<" doesn't exist!"<<endl;
	}

	SettlerCatan catan;
	int numNode, numEdge, node1, node2;
	while (ifs.good()) {
		ifs>>numNode>>numEdge;
		//if both numNode and numEdge are zero, exit the program.
		if (numNode==0 && numEdge==0) break;

		if (numNode<2 || numNode > 25 ){
			cerr<<"The number of node should be greater than 1 and less than 26"<<endl;
			exit(-1);
		}

		if (numEdge <1 || numEdge>25){
			cerr<<"The number of edge should be greater than 0 and less than 26"<<endl;
			exit(-1);
		}

		catan.resetLongestRoad(numNode, numEdge);
		for (int edge=0; edge<numEdge; edge++){
			ifs>>node1>>node2;
			if ( node1 < 0 || node2 <0 || node1 >= numNode || node2 >= numNode){
				cerr<<"input "<<node1<<" "<<node2<<" is not correct."<<endl;
				cerr<<"Node number should be equal or greater than 0 and less than the number of node "
					<<numNode;
				exit(-1);
			}
			catan.putRoad(node1, node2);
		}
		cout<<catan.getLongestRoadLength()<<endl;
	}

	return 0;
}
