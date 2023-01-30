//Program : 유전알고리즘과 미미틱 알고리즘 구현
//Name : 이시현

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

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

    MSG msg;

    // 기본 메시지 루프입니다.
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
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
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
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

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
//Program : 유전알고리즘과 미미틱 알고리즘 구현
//Name : 이시현

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
//n=유전자 갯수 generation=몇 세대까지 갈것인지 city=도시갯수
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
void Ds() // 거리구하기 함수
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
		gene1[i].distance = distance;//각 유전자마다 각각 경로의 거리를 저장
		distance = 0;
	}
}
void rule()//룰렛휠기법으로 범위지정(좋은 유전자일수록 범위가넓음)
{
	for (int i = n-1; i>=0; i--)
	{
		gene1[i].per = (gene1[n-1].distance - gene1[i].distance) + (float)(gene1[n-1].distance - gene1[0].distance) / (k - 1);
		G_per += gene1[i].per;
	}
}
void modification(int t) //변이 연산
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
void setchild(int house[],int t)//교차 연산
{
	int a = rand() % city;  //절단선1
	int b=rand()%city, p, s,count=0;   //절단선 2 
	int modi = rand() % 1000;
	int min = min(a, b);
	int max = max(a, b);

	for (p=min; p <=max; p++)//정해놓은 절단선 사이에 있는 도시를 체크
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
	for (q = 0; q < city; q++) //절단선 1,2바깥쪽에 있는 도시들 자식에게 유전
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

	for (count; count <= max; count++) //절단선1,2사이에 있는 도시 유전
	{
		child[t][count] = gene1[house[0]].turn[count];
		if (house[0] == house[1])child[t][count] *= -1;
	}
	for (q = 0; q < city; q++) //중복된 도시 수정
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
void choice(int house[],int t)//선택 연산
{
	int sum = 0;
	int arrow = (((long)rand() << 15) | rand()) % G_per; //랜드값 범위 넓힌거임
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
void choice_cross_set() //선택 & 교차 & 대치
{
	int house[2] = { 0, };
	int sum;
	int i;
	for (i = 0; i < n - 2; i++)  //룰렛휠기법으로 경로가 짧은 유전자일수록 걸릴확률이 높아지며
	{							 //이 for문이 랜덤으로 유전자2개를 선택하고 서로 경로를 섞는구문이다.
		int r = rand() % 100;
		choice(house, 0);

		for (;; ha++) // 동일한 부모가 선택되지 않을 때까지 무한루프를 도는 구문
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
			setchild(house, i); //부모 교차

		else // 30%의 확률로 교배를 하지 않고 부모를 그대로 복사
		{
			int r2 = rand() % 2;
			for (int j = 0; j < city; j++)
			{
				child[i][j] = gene1[house[r2]].turn[j];
			}
		}
	}
	for (int j = 0; j < city; j++)   //자식들을 낳지만 현재세대에서 가장 좋은 2개의 유전자는 보존해서 다음세대로넘김
	{
		child[i][j] = gene1[0].turn[j];
		child[i + 1][j] = gene1[1].turn[j];
	}
	for (int i = 0; i < n; i++) //세대교체
	{
		for (int j = 0; j < city; j++)
		{
			gene1[i].turn[j] = child[i][j];
			child[i][j] = 0;
		}
	}
}
void graph(int x_length,HDC hdc)  //변화량 그래프 
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
void cp(int abc) //모든 세대를 통틀어 가장 좋은 유전자와 나쁜 유전자를 기억하는 함수
{
	if (top[abc][city] < top_distance)top_distance = top[abc][city];
	if (low[abc][city]>low_distance)low_distance = low[abc][city];
}
std::vector<std::vector<int>> make_graph(std::vector<std::vector<int>> graph,int i) // 유전자의 염록체를 그래프로 인식해서 Vector에 인접행렬로 만드는 함수
{
	int s, e;//사실 방향은 없음
	for (int j = 0; j < city; j++) //간선 추가 할 때 생기는 부분싸이클의 첫 간선을
									//제거하는 작업을 위한 사전 그래프 만들기(방법설명 밑에 해둠)
	{
		s = gene1[i].turn[j];
		if (j == city - 1)e = gene1[i].turn[0];
		else e = gene1[i].turn[j + 1];
		graph[s].push_back(e);
		graph[e].push_back(s);
	}
	return graph;
}
int bfs(std::vector<std::vector<int>> graph, int i)//모든 도시가 하나의 그룹인지 확인하기 위한 함수
{
	using namespace std;
	queue<int> q;
	vector<int> check(city + 1, 0);
	int group = 0;
	for (int j = 0; j < city; j++)
	{
		if (check[gene1[i].turn[j]] == 1)continue;
		q.push(gene1[i].turn[j]); //처음 큐에 들어가는 도시는 s와 같아야한다.
									//지금은 다행히 j가 0부터 돌아서 항상 s와 같음
		check[gene1[i].turn[j]] = 1;
		while (!q.empty()) // 그래프 순회
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
void bfs2(std::vector<std::vector<int>> graph, int *turn, int i)//그래프를 순회하면서 지역최적화한 결과를 염록체에 넣는 구문
{
	using namespace std;
	queue<int> q;
	vector<int> check(city + 1, 0);
	int group = 0;
	for (int j = 0; j < city; j++)
	{
		if (check[gene1[i].turn[j]] == 1)continue;
		q.push(gene1[i].turn[j]); //처음 큐에 들어가는 도시는 lin_kernighan함수의 s와 같아야한다. 
									//지금은 다행히 j가 0부터 돌아서 항상 s와 같음
		check[gene1[i].turn[j]] = 1;
		int count = 0;
		while (!q.empty()) // 그래프 순회 및 염록체에 대입
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
void Erase(std::vector<int> *i,std::vector<int> *j, int X, int Y)//간선 지우기
{
	std::vector<int>::iterator it;
	it = find(i->begin(), i->end(), Y);
	i->erase(it);
	it = std::find(j->begin(),j->end(), X);
	j->erase(it);
}
//싸이클의 첫 간선 없애는 법: 우선 위에서 만들어 둔 그래프를 씀. 그리고 간선이 이어졌을 때 싸이클이 생기고 난 뒤 이은 간선 제외 인접한 간선 중 아무거나 하나 제거 그 뒤
//bfs를 돌아 그룹 2개 나오면 싸이클이 안 없어졌다는 거임 1개면 없어진거임 그리고 인접한 간선 아무거나 제거 할 때는 새로 이은 간선이 푸시백으로 뒤에 들어가기
//때문에 맨 앞에꺼 제거하면 절대 새로 이은 간선은 없애지 않음

//도시데이터는 도시번호의 -1
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
		vector<vector<int>> past(city + 1, vector<int>(3, 0)); //0번지는 새로 생긴거 1번지는 없앤거 (돌아갈때 복구하기 위해 저장)
		vector<vector<int>> cut(city+1);   //정점이 잘림을 당할 때 자신을 자른 정점을 저장하는 배열(자신을 자르는 정점은 여러개가 나올 수 있다 왜냐면 2개랑 이어져있기 때문 하지만 2개이상 새로 만든 간선이 다시 잘릴 수 도 있어서
		vector<int>::iterator it;
		graph = make_graph(graph,i);
		int s = gene1[i].turn[0]; //s는 무조건 1개의 정점과 이어져있다. 그러므로 turn을 갱신할 때 bfs를 s부터 돌면 됨.
		int u = gene1[i].turn[1];
		Erase(&graph[s], &graph[u], s, u); //처음 시작시 간선하나 지우고 시작
		cut[u].push_back(s); // 나중에 다시 돌아와야 하므로 돌아올 때 필요한 정보를 저장
		past[s][0] = -1;
		past[s][1] = u;
		lock[s] = 1;
		float max = -1;
		float gain = 0;
		int X,Y,K=1;//K는 만약 max가 음수라면 개선이 된게 하나도 없음으로 처음으로 되돌아가야하기때문에 1로번지로해놓은거임
		start = clock();
		for (int a = 2; a <= city; a++)//처음에 도시하나 락걸고 시작해서 1개 줄임
		{
			float min = 987654321;
			int near1 = graph[u][0];
			int near2 = -1;
			float dis;
			if(graph[u].size()>1)near2 = graph[u][1];
			for (int j = 0; j < city; j++) //도시 번호가 담겨있는 인덱스번호가 j  절대 turn에 있는 도시 순이 아닌 1번부터 city번까지 순차 방문임(도시번호는 j+1)
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
			int group = bfs(graph, i); //간선 하나 지워보고 그룹 2개나오면 사이클이 아직 존재하므로 다시 잇고 다른 인접한 간선을 지움
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
			cut[Y].push_back(X); //잘림을 당한 Y가 자신을 자른 X를 저장
			u = Y;
			lock[X] = 1;
		}
		if (max < 0)K = 1; //이득이 최대였을 때도 음수면 원상태로 되돌아가기
		for (int z = city; z > K; z--)
		{
			X = cut[Y][cut[Y].size()-1]; //마지막 숫자
			u = past[X][0];
			Y = past[X][1];
			if(u!=-1)Erase(&graph[u], &graph[X], u, X);  //u=-1은 처음 시작 정점이라 나한테 온 간선이 없음
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
	for (int i2 = 0; i2 < generation; i2++)  //유전자 전부돔
	{
		G_per = 0;
		if (memetic)Lin_Kernighan();

		Ds(); //각유전자마다 가지고있는 경로거리 구하기 함수
		std::sort(gene1, gene1 + n, compare); // 정렬이적합도함수 거리로 짧은 순으로 순위지정
											  //여기까지가  유전자마다 거리까지 구한것
		rule();//룰렛 범위 지정
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
		choice_cross_set();//선택하고 교배하고 적용까지
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
			scanf_s("%d %d", &data1[i][0], &data1[i][1]); //정점 좌표입력받는곳(랜덤생성)
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < city; j++)	
			{
				scanf_s("%d", &gene1[i].turn[j]); //초기에 랜덤으로 생성된 경로들을 입력받는곳 랜덤생성은 다른프로그램으로 생성했음 
			}
			josang[i] = gene1[i];                //리셋버튼누를를대비해서 처음 데이터 저장해놓는구문
		}
		start();                          //알고리즘 시작
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
            // 메뉴 선택을 구문 분석합니다.
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
    case WM_PAINT:   //그리는곳
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

			wsprintf(Dis, TEXT("Distance: %d (알고리즘 종료될가지 가장짧은 경로)"), ds[generation-1]);
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

// 정보 대화 상자의 메시지 처리기입니다.
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
