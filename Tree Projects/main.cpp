#include <iostream>
#include <vector>
#include <set>
#include <graphics.h>
#include <windows.h>
#include <iterator>
#include <conio.h>

using namespace std;

char* to_char(int n) {
	char *a;
	a=(char*)malloc(20*sizeof(char));
	char b[20];
	int g=0;
	while(n>0) {
		int r=n%10;
		n = n/10;
		b[g]=48+r;
		g++;
	}
	for(int i=0; i<20; i++) {
		a[i]=' ';
	}
	int j=0;
	for(int i=g-1; i>=0; i--) {
		a[j]=b[i];
		j++;
	}
	a[j]=10;
	return a;
}

void drawTree(int left, int top, int right, int bottom, vector<set<int> >& tree, int node) {
	//position of the center.
	int center_x=(left+right)/2;
	int center_y=(top+bottom)/2;
	
	//Writing the node value in the circle.
	settextstyle(8, 0, 2);
	outtextxy(center_x-5, center_y-5, to_char(node));
	
	//Drawing a circle around the center
	circle(center_x, center_y, 20);
	
	//checking for the children
	if(!tree[node].empty()) {
		//Number of children
		int n=tree[node].size();
		
		//Multilying factor
		int mul = (right-left)/n;
		
		//Generating the left upper x co-ordinate of all the children.
		vector<int> v1;
		for(int i=0; i<=n; i++) {
			v1.push_back(left+(mul*i));
		}
		
		set<int>::iterator it;
		int j=0;
		for(it=tree[node].begin(); it!=tree[node].end(); it++) {
			//erasing the parent node
			tree[*it].erase(node);
			
			//Drawing a line form parent node to children node.
			line(center_x, center_y+20, (v1[j]+v1[j+1])/2, bottom+50-20);
			
			//Calling the same function with the next node.
			drawTree(v1[j], bottom, v1[j+1], bottom+100, tree, *it);
			
			j++;
		}
	}
}

main() {
	//Getting data from user
	cout<<"Enter the number of nodes of a tree : ";
	int n;
	cin>>n;
	cout<<"Enter "<<n-1<<" edges : \n";
	vector<set<int> > tree(n+1);
	for(int i=1; i<n; i++) {
		int a, b;
		cin>>a>>b;
		tree[a].insert(b);
		tree[b].insert(a);
	}
	cout<<"Enter the node which is root : ";
	int node;
	cin>>node;
	
	
	//Next part is to draw the tree
	
	
	//Getting the size of the window screen of the system
	DWORD screenWidth = GetSystemMetrics(SM_CXSCREEN);
	DWORD screenHeight = GetSystemMetrics(SM_CYSCREEN);
	
	//Auto detect the graphics window
	int gd = DETECT, gm;
	
	//Initialising the graph
	initgraph(&gd, &gm, "Tree Maker");
	
	//Drawing tree with the root 'node'
	drawTree(0, 0, screenWidth, 100, tree, node);
	getch();
}


