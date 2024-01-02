#include <fstream>
#include <iostream>
#include <ctime>
#include <string>
#include <cstring>
#include <map>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

class Timer
{
    private:
        clock_t prev;
        clock_t start;
        clock_t end;
        double time;
    public:
        Timer()
        {
            time  = 0;

        }
        void runs()
        {
            start = clock();
            prev = start;
        }
        double calc_time()
        {
            end = clock();
            time = (double)(end - prev) / CLOCKS_PER_SEC;
            prev = end;
            return time;
        }
        double sumtime()
        {
            end = clock();
            time = (double)(end - start) / CLOCKS_PER_SEC;
            return time;
        }
};

class Iofile
{
    public:
        ifstream f_in;
        ofstream f_out;
        ofstream f_out1;
        Iofile(string f_name) {
            f_out.open(f_name.substr(0, f_name.size() - 8) + "_out.txt");
        }

        void exportfile(int u, int v)
        {
            f_out << u << " " << v << endl;
        }

        void savetoCSV( string s, int tri, double process, double ktruss , double sum)
        {
            f_out1.open(s, std::ios::app);
            if (!f_out1.is_open()) {
                std::cout << "Không thể mở file!" << std::endl;
                return;
            }
            f_out1 << tri << "," << process << "," << ktruss << "," << sum <<endl;
            f_out1.close();
        }

		void savetoCSV1( string s, string s1, int tri)
        {
            f_out1.open(s, std::ios::app);
            if (!f_out1.is_open()) {
                std::cout << "Không thể mở file!" << std::endl;
                return;
            }
            f_out1 <<s1<<"," << tri  <<endl;
            f_out1.close();
        }


        ~Iofile() {
            f_in.close();
            f_out.close();
            f_out1.close();
        }
};

struct Edge 
{
    int u,v;

    friend bool operator<(Edge e1, Edge e2)
    {
        return e1.u<e2.u || (e1.u==e2.u && e1.v<e2.v);
    } 
};

class Graph
{
private:      
    string f_name;
    int n, m;
    vector<int> mapto;
    vector<int> deg, bin;
    vector<Edge> binEdge;
    vector<vector<int>> A;
    vector<map<int,int>> Adj, pos;
public:
        Iofile f;
        Graph(string filename);
        bool compareVertex(int i, int j); // so sánh hai dữ liệu có cùng 
        void swapVertex(int &u, int &v);
        void supEdge(int u, int v, int delta);
        void removeE(int u, int v);
        void reorder();
        void commonVertex(const vector<int> &a,const vector<int> &b, vector<int> &c);
        void binSort();
        void updateEdge(int u, int v, int minsup);
        int preprocesss();
        void k_truss(int k);
};

Graph::Graph(string filename) : f(filename){
    f_name = filename;
}

bool Graph::compareVertex(int i, int j) {
    if (deg[i] < deg[j]) {
        return true;
    } else if (deg[i] > deg[j]) {
        return false;
    } else {
        return i < j;
    }
}

void Graph::swapVertex(int &u, int &v)
{
    if(!compareVertex(u,v)) swap(u,v);
}

void Graph::supEdge(int u, int v, int delta)
{
    Adj[u][v] += delta;
    Adj[v][u] += delta;
}

void Graph::removeE(int u, int v)
{
    Adj[u].erase(v);
    Adj[v].erase(u);
}

void Graph::reorder()
{
    mapto.resize(n);
	for (int i=0; i<n; ++i) 
		mapto[i]=i;
	
	sort(mapto.begin(), mapto.end(), [this](int i, int j) {return deg[i]<deg[j] || (deg[i]==deg[j] && i<j); });
}

void Graph::commonVertex(const vector<int> &a,const vector<int> &b, vector<int> &c)
{
    c.clear();
	int j=0;
	for (int i=0; i<a.size(); i++) 
	{
		while (j<b.size() && b[j]>a[i]) 
			j++;
		if (j>=b.size()) 
			break;
		if (b[j]==a[i]) 
			c.push_back(a[i]);
	}
}

void Graph::binSort()
{
    bin.clear(); bin.resize(n,0);
	int nBins=0;
	int mp=0;
	for (int u=0; u<n; ++u) 
	{
		auto tadj = Adj[u];
		for (auto it=tadj.begin(); it!=tadj.end(); ++it) 
		{
			int v=it->first;
			if (!compareVertex(u,v)) 
				continue;
			int sup=it->second;
			if (sup == 0) 
			{
				removeE(u,v);
				continue;
			}
			++mp;
			++bin[sup];
			nBins=max(sup,nBins);
		}
	}
	m=mp;
	++nBins;
	int count=0;
	for (int i=0; i<nBins; ++i) 
	{
		int binsize=bin[i];
		bin[i]=count;
		count+=binsize;
	}
	pos.clear(); pos.resize(n);
	for (int i=0; i<n; ++i) 
		pos[i].clear();

	binEdge.resize(m);
	for (int u=0; u<n; ++u)
	{
		for (auto it=Adj[u].begin(); it!=Adj[u].end(); ++it) 
		{
			int v=it->first;
			if (!compareVertex(u,v)) 
				continue;
			int sup=it->second; 
			Edge e={u,v};
			int b=bin[sup];
			binEdge[b]=e;
			pos[u][v]=b;
			bin[sup]++;
		}
	}
	for (int i=nBins; i>0; --i) 
	{
		bin[i]=bin[i-1];
	}
	bin[0]=0;
}

void Graph::updateEdge(int u, int v, int minsup) {
	swapVertex(u,v);
	int sup=Adj[u][v];
	if (sup<=minsup) return;
	int p=pos[u][v];
	int posbin=bin[sup];
	Edge se=binEdge[posbin];
	Edge e={u,v};
	if (p!=posbin) {
		pos[u][v]=posbin;
		pos[se.u][se.v]=p;
		binEdge[p]=se;
		binEdge[posbin]=e;
	}
	--bin[sup];
	supEdge(u,v,-1);
}


int Graph::preprocesss()
{
    f.f_in.open(f_name);
    int vMax=0;
	int u,v, d;
    while(f.f_in >> u >> v >> d)
    {
        if (u==v) continue;
		vMax=max(vMax,max(u,v));
        m++;
    }
	
	n=vMax+1;
	f.f_in.close();
    f.f_in.open(f_name.c_str());
	deg.clear(); deg.resize(n,0);
	Adj.resize(n);
	for (int i=0; i<n; ++i) Adj[i].clear();
	for (int i=0; i<m; ++i) {
		f.f_in >> u >> v >> d;
		if (u==v) continue;
		if (Adj[u].find(v)==Adj[u].end()) {
			Adj[u][v]=0;
			Adj[v][u]=0;
			++deg[u]; ++deg[v];
		}
	}
    f.f_in.close();
    reorder();
    A.resize(n);
	for (int i=0; i<n; ++i) A[i].clear();
	int triangle=0;
	for (int vi=n-1; vi>=0; vi--) {
		int v=mapto[vi];
		auto it = Adj[v].begin();
		while(it != Adj[v].end())
		{
			int u = it->first;
			if (!compareVertex(u,v)) { it++; continue;}
			vector<int> common;
			commonVertex(A[u], A[v], common);
			for (int i=0; i<common.size(); i++) {
				int w=mapto[common[i]];
				++triangle;
				supEdge(u,v,1);
				supEdge(v,w,1);
				supEdge(w,u,1);
			}
			A[u].push_back(vi);
			it++;
		}
	}
	return triangle;
}

void Graph::k_truss(int k)
{
    binSort();
    for (int s=0; s<m; ++s) 
	{
		int u=binEdge[s].u;
		int v=binEdge[s].v;
		swapVertex(u,v);
		int supuv=Adj[u][v];
		if (supuv >= k - 2)
		{
			int nfound=0;
			for (auto it=Adj[u].begin(); it!=Adj[u].end(); ++it) 
			{
				if (nfound==supuv)
				{
					f.exportfile(u,v);
					break;
				} 
				int w=it->first;
				if (w==v) 
					continue;
				if (Adj[v].find(w)!=Adj[v].end()) 
				{
					++nfound;
					updateEdge(u,w,supuv);
					updateEdge(v,w,supuv);
				}
			}
			removeE(u,v);
		} 
	}
}

int main(int argc, char **argv)
{
    string filename = argv[2]; //amazon0302_adj.tsv
    int k = atoi(argv[1]);
    Timer time;
    time.runs();
    Graph g(filename);
    int tri = g.preprocesss();
    cout<<tri << " triangle found!"<<endl;
    double x = time.calc_time();
    g.k_truss(k);
    double y = time.calc_time();
    double z = time.sumtime();
    cout<<"Thoi gian :" <<z<<" sec."<<endl;
    // g.f.savetoCSV("data.csv",tri, x, y, z);
    // g.f.savetoCSV1("triangle.csv",filename, tri);
    return 0;
}
