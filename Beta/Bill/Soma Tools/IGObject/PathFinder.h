#if !defined(AFX_ASTAR_H__42CDC7E1_CD91_11D2_B0A3_0060970DBAD5__INCLUDED_)
#define AFX_ASTAR_H__42CDC7E1_CD91_11D2_B0A3_0060970DBAD5__INCLUDED_

const int MAX_PATH_CHECK_COUNT = 1024;

class CPathFinder
{
private:
	typedef struct _NODE
	{     // node structure
		long f, h;
		int g, tmpg;
		int x, y;
		int NodeNum;
		_NODE *Parent;
		_NODE *Child[8]; // a node may have upto 8+(NULL) children.
		_NODE *NextNode;  // for filing purposes
	} NODE;
	
	struct _STACK // the stack structure
	{
		_NODE *NodePtr;
		_STACK *NextStackPtr;
	} STACK;

	_NODE*	OPEN;	// the node list pointers
	_NODE*	CLOSED;	
	_NODE*	PATH;	// �ִܰ�� pointer

	_STACK	*Stack;

	BOOL	isPath; // �ùٸ� ����϶��� ���̴�..  

	int		m_nWidth, m_nHeight; 			// ��ȿ�� ���� ���� (���� ���� �����¿� 1�� ũ��..)
	int		m_nTileWidth, m_nTileHeight;	// ���� Ÿ�� ���� ����, ����
	int		m_nPixelWidth, m_nPixelHeight; 	// �ȼ� ���� ���� ����
	DWORD	m_dwTotalTiles; // �� Ÿ�ϰ���.. - �� ������ ���� �ѷ��� �ִ�..
	int*	m_pTiles;				// Ÿ�� �� ����Ÿ ������

private:
	void	DeleteNodes(void);	// ��� ������ �����Ѵ�.
	int SetTile(int x, int y, int val) // �ش� �ȼ� ��ǥ�� Ÿ�ϰ��� �����ش�.
	{
		if(x < 0 || y < 0 || x >= m_nPixelWidth || y >= m_nPixelHeight) return 0;
		int oldVal = m_pTiles[((y>>TILE_SHIFT)+1)*m_nTileWidth + (x>>TILE_SHIFT)+1];
		m_pTiles[((y>>TILE_SHIFT)+1)*m_nTileWidth + (x>>TILE_SHIFT)+1] = val;
		return oldVal;
	}

	// The A* Algorithm and it's stuff
	BOOL 	FindPath(int sx, int sy, int dx, int dy);
	_NODE*	ReturnBestNode(void);
	void	GenerateSuccessors(_NODE *BestNode, int dx, int dy);
	void	GenerateSucc(_NODE *BestNode,int x, int y, int dx, int dy);
	_NODE*	CheckOPEN(int tilenum);
	_NODE*	CheckCLOSED(int tilenum);
	void	Insert(_NODE *Successor);
	void	PropagateDown(_NODE *Old);
	void	Push(_NODE *Node); // stack functions
	_NODE*	Pop(void);

public:
	CPathFinder();
	~CPathFinder();
	
	int		TileNum(int x, int y) // �ش� Ÿ�� ��ǥ�� ���° �迭���� �����ش�. // ������ 1 �β��� �庮�� �ѷ��� �ֱ� ���� 1 �� ���� �ش�..
	{
		if(x < 0 || y < 0 || x >= m_nPixelWidth || y >= m_nPixelHeight) return 0;
		return ((y>>TILE_SHIFT)+1)*m_nTileWidth + (x>>TILE_SHIFT)+1;
	}  

	int		GetTile(int x, int y) // �ش� �ȼ� ��ǥ�� Ÿ�ϰ��� �����ش�.
	{
		if(x < 0 || y < 0 || x >= m_nPixelWidth || y >= m_nPixelHeight) return 0;
		return m_pTiles[((y>>TILE_SHIFT)+1)*m_nTileWidth + (x>>TILE_SHIFT)+1];
	} 

	void	Init(const int* pTiles, int width, int height); // �ٸ� �������� ���� ���� �ִ�..
	BOOL	CalcNewPath(int sx, int sy, int dx, int dy);	// ����� ���.. - ��ΰ� ������ ������ ����

	BOOL	ReachedGoal(void); // ���� �������� ��Ҵ��� üũ.. ���� ��� ���� ����.
	POINT	GetNextWay(void); // ���� ���� ���ٸ� 0,0 �� ����..

	void SetCol(int x, int y, int nTile) // �ش� Ÿ�� ��ǥ �浹���� ����
	{
		if(x < 0 || y < 0 || x >= m_nWidth || y >= m_nHeight) return;
		m_pTiles[(y+1)*m_nTileWidth + (x+1)] |= nTile;
	}

	void ReleaseCol(int x, int y) // �ش� Ÿ�� ��ǥ �浹�� ����..
	{
		if(x < 0 || y < 0 || x >= m_nWidth || y >= m_nHeight) return;
		m_pTiles[(y+1)*m_nTileWidth + (x+1)] &= 1;
	}

	void SetChrCol(int x, int y, int nSN) // zebra - �μ��� �ȼ� �����̴�.
	{
		int x2 = (x>>TILE_SHIFT), y2 = (y>>TILE_SHIFT);
		if(x2 < 0 || y2 < 0 || x2 > m_nWidth || y2 > m_nHeight) return;
		x2+=2; y2+=2;
		for(y = y2-2; y <= y2; y++)
		{
			for(x = x2-2; x <= x2; x++)
			{
				if(!m_pTiles[y*m_nTileWidth + x])
					m_pTiles[y*m_nTileWidth + x] |= nSN; // ĳ���� �浹�� 2 �� or �����Ѵ�.
			}
		}
	}

	void ReleaseChrCol(int x, int y, int nSN) // zebra - �μ��� �ȼ� �����̴�.
	{
		int x2 = (x>>TILE_SHIFT), y2 = (y>>TILE_SHIFT);
		if(x2 < 0 || y2 < 0 || x2 > m_nWidth || y2 > m_nHeight) return;
		x2+=2; y2+=2;
		for(y = y2-2; y <= y2; y++)
		{
			for(x = x2-2; x <= x2; x++)
			{
				if((m_pTiles[y*m_nTileWidth + x] & nSN) == nSN)
					m_pTiles[y*m_nTileWidth + x] &= 1; // ĳ���� �浹�� 2 �� or �����Ѵ�.
			}
		}
	}

	int Get(int x, int y) // zebra - Ÿ�� ���� ��ǥ���� ���� ���Ѵ�..
	{
		if(x < 0 || y < 0 || x >= m_nWidth || y >= m_nHeight) return 0;
		return m_pTiles[(y+1)*m_nTileWidth + (x+1)];
	}
};

#endif // ASTAR_H

