//Program : �����˰���� �̹�ƽ �˰��� ����
//Start_Date : 2015.05.12
//End_Date : 2015.10.10
//Name : �̽���

#pragma warning(disable:4996)
#include "stdafx.h"
#include "Win32Project1.h"
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include<time.h>
#include<stdlib.h>
#include<tchar.h> 
#include<vector>
#include<queue>
#define MAX_LOADSTRING 100
HINSTANCE hInst;                                
WCHAR szTitle[MAX_LOADSTRING];                  
WCHAR szWindowClass[MAX_LOADSTRING];            

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
void choice(int house[]);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

    MSG msg;

    // �⺻ �޽��� �����Դϴ�.
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32PROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}
//Program : �����˰���� �̹�ƽ �˰��� ����
//Start_Date : 2015.05.12
//End_Date : 2015.10.10
//Name : �̽���

struct Gene
{
	int turn[1000] = { 0, };
	int distance;
	float per;
	int a, b, c, d;
};
bool compare(const Gene&i, const Gene&j)
{
	return i.distance < j.distance;
}
int  n = 20, k = 4, G_per = 0, ha = 0, generation = 20;
int city = 50,time1,top_distance=987654321,low_distance;
//n=������ ���� generation=�� ������� �������� city=���ð���
int abc = 0;
int data1[1000][2] = { 0, };
int child[1000][1000] = { 0, };
int save2[40010][4] = { 0, };
int g_per[15] = { 0, };
int count3[10010] = { 0, };
int count4[110] = { 0, };
int count2 = 0;
int top[10010][100] = { 0, };
int low[10010][100] = { 0, };
int ds[10010] = { 0, };
Gene gene1[1000];
Gene josang[1000];
void Ds() // �Ÿ����ϱ� �Լ�
{
	float x, y,distance=0;
	int turn;
	int next;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < city; j++)
		{
			turn = gene1[i].turn[j]-1;
			if (j + 1 == city)next = gene1[i].turn[0]-1;
			else next = gene1[i].turn[j + 1]-1;
			x = data1[turn][0] - data1[next][0];
			y = data1[turn][1] - data1[next][1];
			x = x*x;
			y = y*y;
			distance += sqrt(x + y);
		}
		gene1[i].distance = distance;//�� �����ڸ��� ���� ����� �Ÿ��� ����
		distance = 0;
	}
}
void rule()//�귿�ٱ������ ��������(���� �������ϼ��� ����������)
{
	for (int i = n-1; i>=0; i--)
	{
		gene1[i].per = (gene1[n-1].distance - gene1[i].distance) + (float)(gene1[n-1].distance - gene1[0].distance) / (k - 1);
		G_per += gene1[i].per;
	}
}
void modification(int t) //���� ����
{
	int pos = rand() % city;
	int num = rand() % city + 1;
	for (int i = 0; i < city; i++)
	{
		if (child[t][i] == num)
		{
			int temp = child[t][pos];
			child[t][pos] = child[t][i];
			child[t][i] = temp;
			break;
		}
	}
}
void setchild(int house[],int t)//���� ����
{
	int a = rand() % city;  //���ܼ�1
	int b=rand()%city, p, s,count=0;   //���ܼ� 2 
	int modi = rand() % 1000;
	int min = min(a, b);
	int max = max(a, b);

	for (p=min; p <=max; p++)//���س��� ���ܼ� ���̿� �ִ� ���ø� üũ
	{
		int imsi = gene1[house[0]].turn[p];
		for (int imsi2 = 0; imsi2 < city; imsi2++)
		{
			if (gene1[house[1]].turn[imsi2] == imsi)
			{
				gene1[house[1]].turn[imsi2] *= -1;
				break;
			}
		}
	}

	int q;
	for (q = 0; q < city; q++) //���ܼ� 1,2�ٱ��ʿ� �ִ� ���õ� �ڽĿ��� ����
	{
		if (gene1[house[1]].turn[q] < 0)
		{
			continue;
		}
		else if(count<min)
		{
			child[t][count] = gene1[house[1]].turn[q];
			gene1[house[1]].turn[q]*=-1;
			count++;
		}
	}

	for (count; count <= max; count++) //���ܼ�1,2���̿� �ִ� ���� ����
	{
		child[t][count] = gene1[house[0]].turn[count];
		if (house[0] == house[1])child[t][count] *= -1;
	}
	for (q = 0; q < city; q++) //�ߺ��� ���� ����
	{
		if (gene1[house[1]].turn[q]>0)
		{
			child[t][count] = gene1[house[1]].turn[q];
			count++;
		}
		else gene1[house[1]].turn[q]*=-1;
	}
	if (modi <15)
	{
		modification(t);
	}
}
void choice(int house[],int t)//���� ����
{
	int sum = 0;
	int arrow = (((long)rand() << 15) | rand()) % G_per; //���尪 ���� ��������
	for (int j = n - 1; j >= 0; j--)
	{
		sum += gene1[j].per;
		if (arrow < sum)
		{
			house[t] = j;
			break;
		}
	}
}
void choice_cross_set() //���� & ���� & ��ġ
{
	int house[2] = { 0, };
	int sum;
	int i;
	for (i = 0; i < n - 2; i++)  //�귿�ٱ������ ��ΰ� ª�� �������ϼ��� �ɸ�Ȯ���� ��������
	{							 //�� for���� �������� ������2���� �����ϰ� ���� ��θ� ���±����̴�.
		int r = rand() % 100;
		choice(house, 0);

		for (;; ha++) // ������ �θ� ���õ��� ���� ������ ���ѷ����� ���� ����
		{
			choice(house, 1);
			if (house[0] != house[1])break;
			if (ha > 100)
			{
				ha = 0;
				house[1] = rand() % 10;
				break;
			}
		}
		count3[house[0]]++;
		count3[house[1]]++;
		count2++;

		if (r < 70)
			setchild(house, i); //�θ� ����

		else // 30%�� Ȯ���� ���踦 ���� �ʰ� �θ� �״�� ����
		{
			int r2 = rand() % 2;
			for (int j = 0; j < city; j++)
			{
				child[i][j] = gene1[house[r2]].turn[j];
			}
		}
	}
	for (int j = 0; j < city; j++)   //�ڽĵ��� ������ ���缼�뿡�� ���� ���� 2���� �����ڴ� �����ؼ� ��������γѱ�
	{
		child[i][j] = gene1[0].turn[j];
		child[i + 1][j] = gene1[1].turn[j];
	}
	for (int i = 0; i < n; i++) //���뱳ü
	{
		for (int j = 0; j < city; j++)
		{
			gene1[i].turn[j] = child[i][j];
			child[i][j] = 0;
		}
	}
}
void graph(int x_length,HDC hdc)  //��ȭ�� �׷��� 
{
	int y_length = low_distance - top_distance;
	int y = 200, x = 380;
	int x3 = 520, y3 = 220;
	MoveToEx(hdc, x3, y3, NULL);
	if (x_length == 0)return;
	for (int i = 1; i <= x_length; i++)
	{
		int y2 = low_distance - top[i][city];
		double imsi = (double)y2 / y_length*y;
		double imsi2 = (double)i / x_length*x;
		LineTo(hdc, x3 + imsi2, y3 - imsi);
		MoveToEx(hdc, x3 + imsi2, y3 - imsi, NULL);
	}
}
void cp(int abc) //��� ���븦 ��Ʋ�� ���� ���� �����ڿ� ���� �����ڸ� ����ϴ� �Լ�
{
	if (top[abc][city] < top_distance)top_distance = top[abc][city];
	if (low[abc][city]>low_distance)low_distance = low[abc][city];
}
std::vector<std::vector<int>> make_graph(std::vector<std::vector<int>> graph,int i) // �������� ����ü�� �׷����� �ν��ؼ� Vector�� ������ķ� ����� �Լ�
{
	int s, e;//��� ������ ����
	for (int j = 0; j < city; j++) //���� �߰� �� �� ����� �κн���Ŭ�� ù ������
									//�����ϴ� �۾��� ���� ���� �׷��� �����(������� �ؿ� �ص�)
	{
		s = gene1[i].turn[j];
		if (j == city - 1)e = gene1[i].turn[0];
		else e = gene1[i].turn[j + 1];
		graph[s].push_back(e);
		graph[e].push_back(s);
	}
	return graph;
}
int bfs(std::vector<std::vector<int>> graph, int i)//��� ���ð� �ϳ��� �׷����� Ȯ���ϱ� ���� �Լ�
{
	using namespace std;
	queue<int> q;
	vector<int> check(city + 1, 0);
	int group = 0;
	for (int j = 0; j < city; j++)
	{
		if (check[gene1[i].turn[j]] == 1)continue;
		q.push(gene1[i].turn[j]); //ó�� ť�� ���� ���ô� s�� ���ƾ��Ѵ�.
									//������ ������ j�� 0���� ���Ƽ� �׻� s�� ����
		check[gene1[i].turn[j]] = 1;
		while (!q.empty()) // �׷��� ��ȸ
		{
			int s = q.front();
			q.pop();
			for (int k = 0; k < graph[s].size(); k++)
			{
				if (check[graph[s][k]])continue;
				q.push(graph[s][k]);
				check[graph[s][k]] = 1;
			}
		}
		group++;
	}
	return group;
}
void bfs2(std::vector<std::vector<int>> graph, int *turn, int i)//�׷����� ��ȸ�ϸ鼭 ��������ȭ�� ����� ����ü�� �ִ� ����
{
	using namespace std;
	queue<int> q;
	vector<int> check(city + 1, 0);
	int group = 0;
	for (int j = 0; j < city; j++)
	{
		if (check[gene1[i].turn[j]] == 1)continue;
		q.push(gene1[i].turn[j]); //ó�� ť�� ���� ���ô� lin_kernighan�Լ��� s�� ���ƾ��Ѵ�. 
									//������ ������ j�� 0���� ���Ƽ� �׻� s�� ����
		check[gene1[i].turn[j]] = 1;
		int count = 0;
		while (!q.empty()) // �׷��� ��ȸ �� ����ü�� ����
		{
			int s = q.front();
			q.pop();
			turn[count++] = s;
			for (int k = 0; k < graph[s].size(); k++)
			{
				if (check[graph[s][k]])continue;
				q.push(graph[s][k]);
				check[graph[s][k]] = 1;
			}
		}
		group++;
	}
}
void Erase(std::vector<int> *i,std::vector<int> *j, int X, int Y)//���� �����
{
	std::vector<int>::iterator it;
	it = find(i->begin(), i->end(), Y);
	i->erase(it);
	it = std::find(j->begin(),j->end(), X);
	j->erase(it);
}
//����Ŭ�� ù ���� ���ִ� ��: �켱 ������ ����� �� �׷����� ��. �׸��� ������ �̾����� �� ����Ŭ�� ����� �� �� ���� ���� ���� ������ ���� �� �ƹ��ų� �ϳ� ���� �� ��
//bfs�� ���� �׷� 2�� ������ ����Ŭ�� �� �������ٴ� ���� 1���� ���������� �׸��� ������ ���� �ƹ��ų� ���� �� ���� ���� ���� ������ Ǫ�ù����� �ڿ� ����
//������ �� �տ��� �����ϸ� ���� ���� ���� ������ ������ ����

//���õ����ʹ� ���ù�ȣ�� -1
void Lin_Kernighan()
{
	printf("----------------------------------------------------------\n");
 	using namespace std;
	int qwer = 0;
	float start, start2;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < city; j++)printf("%d ", gene1[i].turn[j]);
		printf("\n");
		vector<int> lock(city+1, 0);
		vector<vector<int>> graph(city+1, vector<int>(0, 0));
		vector<vector<int>> past(city + 1, vector<int>(3, 0)); //0������ ���� ����� 1������ ���ذ� (���ư��� �����ϱ� ���� ����)
		vector<vector<int>> cut(city+1);   //������ �߸��� ���� �� �ڽ��� �ڸ� ������ �����ϴ� �迭(�ڽ��� �ڸ��� ������ �������� ���� �� �ִ� �ֳĸ� 2���� �̾����ֱ� ���� ������ 2���̻� ���� ���� ������ �ٽ� �߸� �� �� �־
		vector<int>::iterator it;
		graph = make_graph(graph,i);
		int s = gene1[i].turn[0]; //s�� ������ 1���� ������ �̾����ִ�. �׷��Ƿ� turn�� ������ �� bfs�� s���� ���� ��.
		int u = gene1[i].turn[1];
		Erase(&graph[s], &graph[u], s, u); //ó�� ���۽� �����ϳ� ����� ����
		cut[u].push_back(s); // ���߿� �ٽ� ���ƿ;� �ϹǷ� ���ƿ� �� �ʿ��� ������ ����
		past[s][0] = -1;
		past[s][1] = u;
		lock[s] = 1;
		float max = -1;
		float gain = 0;
		int X,Y,K=1;//K�� ���� max�� ������� ������ �Ȱ� �ϳ��� �������� ó������ �ǵ��ư����ϱ⶧���� 1�ι������س�������
		start = clock();
		for (int a = 2; a <= city; a++)//ó���� �����ϳ� ���ɰ� �����ؼ� 1�� ����
		{
			float min = 987654321;
			int near1 = graph[u][0];
			int near2 = -1;
			float dis;
			if(graph[u].size()>1)near2 = graph[u][1];
			for (int j = 0; j < city; j++) //���� ��ȣ�� ����ִ� �ε�����ȣ�� j  ���� turn�� �ִ� ���� ���� �ƴ� 1������ city������ ���� �湮��(���ù�ȣ�� j+1)
			{
				if (lock[j + 1] == 1 || j + 1 == u || near1 == j + 1 || near2 == j + 2)continue;
				float x = (data1[u - 1][0] - data1[j][0]);
				float y = (data1[u - 1][1] - data1[j][1]);
				x = x*x;
				y = y*y;
				dis = sqrt(x + y);
				if (min > dis)
				{
					min = dis;
					X = j + 1;
				}
			}
			if (min == 987654321)
			{
				break;
			}
			bool check = false;
			it = find(graph[X].begin(), graph[X].end(), u);
			if (it == graph[X].end())
			{
				graph[u].push_back(X);
				graph[X].push_back(u);
				Y = *graph[X].begin();
			}
			else
			{
				if (it == graph[X].begin())Y = *graph[X].rbegin();
				else Y = *graph[X].begin();
			}
			if (u == Y)
			{
				qwer = 1;
			}
			Erase(&graph[X], &graph[Y], X, Y);
			int group = bfs(graph, i); //���� �ϳ� �������� �׷� 2�������� ����Ŭ�� ���� �����ϹǷ� �ٽ� �հ� �ٸ� ������ ������ ����
			if (group == 2)
			{
				graph[X].push_back(Y);
				graph[Y].push_back(X);
				Y = *graph[X].begin();
				Erase(&graph[X], &graph[Y], X, Y);
			}
			float x = data1[X-1][0] - data1[Y-1][0];
			float y = data1[X-1][1] - data1[Y-1][1];
			x = x*x;
			y = y*y;
			float dis_xy = sqrt(x + y);
			gain += (dis_xy - min);
			if (max < gain)
			{
				max = gain;
				K = a;
			}
			past[X][0] = u;
			past[X][1] = Y;
			cut[Y].push_back(X); //�߸��� ���� Y�� �ڽ��� �ڸ� X�� ����
			u = Y;
			lock[X] = 1;
		}
		if (max < 0)K = 1; //�̵��� �ִ뿴�� ���� ������ �����·� �ǵ��ư���
		for (int z = city; z > K; z--)
		{
			X = cut[Y][cut[Y].size()-1]; //������ ����
			u = past[X][0];
			Y = past[X][1];
			if(u!=-1)Erase(&graph[u], &graph[X], u, X);  //u=-1�� ó�� ���� �����̶� ������ �� ������ ����
			else
			{
				Erase(&graph[X], &graph[*graph[X].begin()], X, *graph[X].begin());
			}
			graph[X].push_back(Y);
			graph[Y].push_back(X);
			if (u == -1)break;
			cut[Y].pop_back();
			Y = u;
		}
		bfs2(graph, gene1[i].turn, i);
	}
}
bool memetic = 1;
void start()
{
	freopen("output.txt", "w", stdout);
	int start = clock();
	using namespace std;
	for (int i2 = 0; i2 < generation; i2++)  //������ ���ε�
	{
		G_per = 0;
		if (memetic)Lin_Kernighan();

		Ds(); //�������ڸ��� �������ִ� ��ΰŸ� ���ϱ� �Լ�
		std::sort(gene1, gene1 + n, compare); // ���������յ��Լ� �Ÿ��� ª�� ������ ��������
											  //���������  �����ڸ��� �Ÿ����� ���Ѱ�
		rule();//�귿 ���� ����
		if (G_per == 0)break;
		for (int j2 = 0; j2 < city; j2++)
		{
			top[i2][j2] = gene1[0].turn[j2];
			low[i2][j2] = gene1[n - 1].turn[j2];   
		}
		top[i2][city] = gene1[0].distance;
		low[i2][city] = gene1[n - 1].distance;
		int j3;
		ds[i2] = gene1[0].distance;
		choice_cross_set();//�����ϰ� �����ϰ� �������
	}
	int start2 = clock();
	time1 = start2 - start;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT rect;
	SetRect(&rect, 0, 0, 1200,1200);
	TCHAR string[100];
	TCHAR Dis[100];
	TCHAR gr[100];
    switch (message)
    {
	case WM_CREATE:
	{
		CreateWindow(TEXT("BUTTON"), TEXT("Next Age"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 620, 475, 100, 25, hWnd, (HMENU)1, hInst, NULL);
		CreateWindow(TEXT("BUTTON"), TEXT("Reset"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 750, 475, 100, 25, hWnd, (HMENU)2, hInst, NULL);
		FILE *stream;
	//	FILE *stream2;
		errno_t err;
		errno_t err2;
		err = freopen_s(&stream, "input.txt", "r", stdin);
		//err = freopen_s(&stream, "output.txt", "w", stdout);
		srand((unsigned)time(NULL));
		for (int i = 0; i < city; i++)
		{
			scanf_s("%d %d", &data1[i][0], &data1[i][1]); //���� ��ǥ�Է¹޴°�(��������)
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < city; j++)	
			{
				scanf_s("%d", &gene1[i].turn[j]); //�ʱ⿡ �������� ������ ��ε��� �Է¹޴°� ���������� �ٸ����α׷����� �������� 
			}
			josang[i] = gene1[i];                //���¹�ư������������ؼ� ó�� ������ �����س��±���
		}
		start();                          //�˰��� ����
		fclose(stream);
	}
    case WM_COMMAND:
        {
			switch (LOWORD(wParam))
			{
			case 1:
				InvalidateRect(hWnd, &rect, TRUE);
				//if (abc == 9)abc += 40;
				//else if (abc > 9)abc += 50;
				//else abc++;
				if (abc == generation - 1)abc = generation - 1;
				//else abc+=100;
				else abc++;
				break;
			case 2:
				InvalidateRect(hWnd, &rect, TRUE);
				abc = 0;
				for (int i = 0; i < n; i++)
				{
					gene1[i] = josang[i];
				}
				start();
				break;
			}
            int wmId = LOWORD(wParam);
            // �޴� ������ ���� �м��մϴ�.
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            }
        }
        //break;
    case WM_PAINT:   //�׸��°�
        {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			for (int c = 0; c < city; c++)
			{
				Ellipse(hdc, data1[c][0] - 5, data1[c][1] - 5, data1[c][0] + 5, data1[c][1] + 5);
			}
			for (int j = 0; j < city; j++)
			{
				MoveToEx(hdc, data1[top[abc][j]-1][0], data1[top[abc][j]-1][1], NULL);
				if(j==city-1)LineTo(hdc, data1[top[abc][0]-1][0], data1[top[abc][0]-1][1]);
				else LineTo(hdc, data1[top[abc][j + 1]-1][0], data1[top[abc][j + 1]-1][1]);
			}
			cp(abc);
			graph(abc,hdc);
			wsprintf(gr, TEXT("generation: %d"), abc+1);
			TextOut(hdc, 550, 300, gr, lstrlen(gr));

			wsprintf(Dis, TEXT("Distance: %d (�˰��� ����ɋ����� ����ª�� ���)"), ds[generation-1]);
			TextOut(hdc, 550, 350, Dis, lstrlen(Dis));

			wsprintf(string, TEXT("Time :%d  ms"),time1);
			TextOut(hdc, 550, 400, string, lstrlen(string));

			EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
	return DefWindowProc(hWnd, message, wParam, lParam);
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
