#include<graphics.h>  
#include<windows.h>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <set>
#include <conio.h>

using namespace std;

template <typename T>
class Tree {
private:
    vector<pair<int, set<int> > > x;
    vector<T> value;
    vector<vector<int> > lt;
    int h=0, l=0;
    void adjust(vector<pair<int, set<int> > >& tree, int root) {
        if(!tree[root].second.empty()) {
            h++;
            set<int>::iterator it;
            for(it=tree[root].second.begin(); it!=tree[root].second.end(); it++) {
                tree[*it].second.erase(root);
                tree[*it].first=root;
                adjust(tree, *it);
            }
        }
    }
    void levelWise(vector<pair<int, set<int> > >& tree, int root, int g) {
        lt[g].push_back(root);
        if(!tree[root].second.empty()) {
            set<int>::iterator it;
            for(it=tree[root].second.begin(); it!=tree[root].second.end(); it++) {
                levelWise(tree, *it, g+1);
            }
        }
    }
public:
    Tree(vector<pair<int, int> > edge, int size) {
        x.resize(size+1);
        value.resize(size+1, 0);
        for(int i=0; i<size-1; i++) {
            x[edge[i].first].second.insert(edge[i].second);
            x[edge[i].second].second.insert(edge[i].first);
        }
        adjust(x, 1);
        lt.resize(level());
        levelWise(x, 1, 0);
    };

    int level() {return h+1;}
    int height() {return h;}
    int size() {
        return x.size()-1;
    }
    int father(int node) {
        return x[node].first;
    }
    set<int> children(int node) {
        return x[node].second;
    }
    int children_count(int node) {
        return x[node].second.size();
    }
    T getValue(int node) {
        return value[node];
    }
    void setValue(int node, T val) {
        value[node]=val;
    }
    vector<int> level_element(int level_position) {return lt[level_position-1];}
};

char* to_char(int n) {
    char* a;
    a=(char*)malloc(20 * sizeof(char));
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
    return a;
}

void drawTree(int left, int top, int right, int bottom, Tree<int> t1, int node) {
	int x = (left+right)/2;
    int y = (top+bottom)/2;
    int font = 8;
    int direction = 0;
    int font_size = 2;
    
    //floodfill(x, y, WHITE);
    settextstyle(font, direction, font_size);
    //setcolor(WHITE);
    outtextxy(x-5, y-5, to_char(node));
    ellipse(x, y, 0, 360, 30, 20);
    if(t1.children_count(node)!=0) {
    	int n=t1.children_count(node);
    	int mul=(right-left)/n;
    	vector<int> v1;
    	for(int i=0; i<=n; i++) {
    		v1.push_back(left+(mul*i));
		}
		set<int>::iterator it;
		int j=0;
		set<int> s1=t1.children(node);
        for(it=s1.begin(); it!=s1.end(); it++) {
        	line(x, y+20, (v1[j]+v1[j+1])/2, bottom+50-20);
        	delay(500);
           	drawTree(v1[j], bottom, v1[j+1], bottom+100, t1, *it);
           	j++;
        }
	}
}

main()  
{  
	int n;
	cout<<"Enter the number of nodes of the tree : ";
	cin>>n;
	cout<<"Enter "<<n-1<<" edges : \n";
	vector<pair<int, int> > v1;
	for(int i=1; i<n; i++) {
		int a, b;
		cin>>a>>b;
		v1.push_back(make_pair(a, b));
	}
	Tree<int> t1(v1, n);
	DWORD screenWidth = GetSystemMetrics(SM_CXSCREEN);
    DWORD screenHeight = GetSystemMetrics(SM_CYSCREEN);
    
    int gd = DETECT, gm;
    
    initgraph(&gd, &gm, "Tree Builder");
    drawTree(0, 0, screenWidth, 100, t1, 1);
    getch();
}
