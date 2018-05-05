#include "stdafx.h"
#include "Tile.h"

CPathManager*	CPathManager::m_pInstance = nullptr;

node_t *OPEN = NULL, *CLOSED = NULL;
node_stack_t* STACK = NULL;

const int FINDPATH_LIMIT = 200;          //탐색 제한 루프 회수 

void CPathManager::Init()
{



}

void CPathManager::Release()
{
}

void CPathManager::init_astar()
{
	node_t* temp;
	node_stack_t* stack;

	while (OPEN) {
		temp = OPEN->next_node;
		free(OPEN);
		OPEN = temp;
	}

	while (CLOSED) {
		temp = CLOSED->next_node;
		free(CLOSED);
		CLOSED = temp;
	}

	while (STACK) {
		stack = STACK->next_node;
		free(STACK);
		STACK = stack;
	}

}

bool CPathManager::is_available_grid(int x, int y)
{
	int nIdx = x + TILEMANAGER->GetTileNum().x * y;

	if (0 > nIdx) return false;
	
	CObj* p = TILEMANAGER->SelectTile(nIdx);
	return dynamic_cast<CTile*>(p)->IsMovable();
}

node_t* CPathManager::is_open(INTPOINT pos)
{
	node_t *temp = OPEN;

	while (temp) {
		if (temp->pos.x == pos.x && temp->pos.y == pos.y)
			return temp;
		temp = temp->next_node;
	}

	return NULL;
}

node_t * CPathManager::is_closed(INTPOINT pos)
{
	node_t *temp = CLOSED;

	while (temp) {
		if (temp->pos.x == pos.x && temp->pos.y == pos.y)
			return temp;
		temp = temp->next_node;
	}

	return NULL;
}

void CPathManager::push_into_stack(node_t * node)
{
	node_stack_t* temp;

	temp = (node_stack_t *)calloc(1, sizeof(node_stack_t));
	temp->node = node;
	temp->next_node = STACK;
	STACK = temp;
}

node_t * CPathManager::pop_from_stack()
{
	node_t *temp;
	node_stack_t* stack;

	stack = STACK;
	temp = stack->node;
	STACK = stack->next_node;

	free(stack);

	return temp;

}

void CPathManager::make_sort(node_t * old)
{
	node_t *direct, *previousNode;
	int i;
	int degree = old->degree + 1;

	for (i = 0; i<8; i++) {

		if ((direct = old->direct[i]) == NULL)
			continue;

		if (direct->degree > degree) {
			direct->prev_node = old;
			direct->degree = degree;
			direct->value_factor = direct->distance + direct->degree;
			push_into_stack(direct);
		}

	}

	while (STACK) {

		previousNode = pop_from_stack();

		for (i = 0; i<8; i++) {

			if ((direct = previousNode->direct[i]) == NULL)
				break;

			if (direct->degree > previousNode->degree + 1) {
				direct->prev_node = previousNode;
				direct->degree = previousNode->degree + 1;
				direct->value_factor = direct->distance + direct->degree;
				push_into_stack(direct);
			}
		}
	}
}

void CPathManager::insert_node(node_t * present)
{
	node_t* old = NULL, *temp = NULL;

	if (OPEN == NULL) {
		OPEN = present;
		return;
	}

	temp = OPEN;

	//OPEN에 있는 노드가 현재 자식 노드보다 평가치가 낮으면
	//OPEN노드를 추적해서 현재 자식 노드보다 평가치가 높은 노드를 찾는다. 
	while (temp && (temp->value_factor < present->value_factor)) {
		old = temp;
		temp = temp->next_node;
	}

	//낮은 평가치의 OpenNode 중 출발지에 가장 가까운 노드 -> 추가할 자식 노드 -> 높은 평가치의 OpenNode중 출발지에 가장 먼 노드
	if (old) {
		present->next_node = temp;
		old->next_node = present;
	}
	else {
		present->next_node = temp;
		OPEN = present;
	}
}

void CPathManager::extend_child_node(node_t * node, int x, int y, INTPOINT tDest, int cur_direct)
{
	node_t* old = NULL, *child = NULL;
	int i;
	int degree = node->degree + 1;
	INTPOINT tSrc;
	tSrc.x = x;
	tSrc.y = y;

	if (old = is_open(tSrc)) {

		node->direct[cur_direct] = old;

		//그리고 노드 재연결 및 설정 . 참고로 노드 방향이 반대로 적용된다는 걸 고려할 것. 
		if (degree<old->degree) {
			old->prev_node = node;
			old->degree = degree;
			old->value_factor = old->distance + old->degree;
		}//if()

	}
	else if (old = is_closed(tSrc)) {

		node->direct[cur_direct] = old;

		//어떤 경우에는 기존 CloseNode에 있는 노드의 degree가 더 적을 경우가 발생할 수도 있는데
		//이 때 순서를 다시 설정      
		if (degree<old->degree) {
			old->prev_node = node;
			old->degree = degree;
			old->value_factor = old->distance + old->degree;
			make_sort(old);
		}//if()

		 //확장할 노드 생성 및 OpenNode 리스트에 추가
	}
	else {
		if ((child = (node_t*)calloc(1, sizeof(node_t))) == NULL)
			return;

		child->prev_node = node;
		child->degree = degree;
		child->distance = (tSrc.x - tDest.x) * (tSrc.x - tDest.x) + (tSrc.y - tDest.y) * (tSrc.y - tDest.y);
		child->value_factor = child->distance + child->degree;
		child->pos = tSrc;

		insert_node(child);

		node->direct[cur_direct] = child;

	}
}

char CPathManager::make_child(node_t * node, INTPOINT tDest)
{
	int x, y;
	char flag = 0;
	char checkis_available_grid[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

	x = node->pos.x;
	y = node->pos.y;


	//이동 가능한지 여부 판단.
	checkis_available_grid[DIRECTION_RIGHTDOWN] = is_available_grid(x, y + 1);
	checkis_available_grid[DIRECTION_DOWN] = is_available_grid(x, y + 1);
	checkis_available_grid[DIRECTION_LEFTDOWN] = is_available_grid(x - 1, y + 1);
	checkis_available_grid[DIRECTION_LEFT] = is_available_grid(x - 1, y);
	checkis_available_grid[DIRECTION_LEFTUP] = is_available_grid(x - 1, y - 1);
	checkis_available_grid[DIRECTION_UP] = is_available_grid(x, y - 1);
	checkis_available_grid[DIRECTION_RIGHTUP] = is_available_grid(x + 1, y - 1);
	checkis_available_grid[DIRECTION_RIGHT] = is_available_grid(x + 1, y);

	//각 이동 가능한 노드에 대한 자식 노드 생성 
	if (checkis_available_grid[DIRECTION_LEFT]) {
		extend_child_node(node, x - 1, y, tDest, DIRECTION_LEFT);
		flag = 1;
	}//if()

	if (checkis_available_grid[DIRECTION_RIGHT]) {
		extend_child_node(node, x + 1, y, tDest, DIRECTION_RIGHT);
		flag = 1;
	}//if()

	if (checkis_available_grid[DIRECTION_UP]) {
		extend_child_node(node, x, y - 1, tDest, DIRECTION_UP);
		flag = 1;
	}//if()

	if (checkis_available_grid[DIRECTION_DOWN]) {
		extend_child_node(node, x, y + 1, tDest, DIRECTION_DOWN);
		flag = 1;
	}//if()

	if (checkis_available_grid[DIRECTION_RIGHTDOWN] && checkis_available_grid[DIRECTION_RIGHT] && checkis_available_grid[DIRECTION_DOWN]) {
		extend_child_node(node, x + 1, y + 1, tDest, DIRECTION_RIGHTDOWN);
		flag = 1;
	}//if()

	if (checkis_available_grid[DIRECTION_LEFTUP] && checkis_available_grid[DIRECTION_LEFT] && checkis_available_grid[DIRECTION_UP]) {
		extend_child_node(node, x - 1, y - 1, tDest, DIRECTION_LEFTUP);
		flag = 1;
	}//if()

	if (checkis_available_grid[DIRECTION_RIGHTUP] && checkis_available_grid[DIRECTION_RIGHT] && checkis_available_grid[DIRECTION_UP]) {
		extend_child_node(node, x + 1, y - 1, tDest, DIRECTION_RIGHTUP);
		flag = 1;
	}//if()

	if (checkis_available_grid[DIRECTION_LEFTDOWN] && checkis_available_grid[DIRECTION_LEFT] && checkis_available_grid[DIRECTION_DOWN]) {
		extend_child_node(node, x - 1, y + 1, tDest, DIRECTION_LEFTDOWN);
		flag = 1;
	}//if()

	return flag;

}



node_t* CPathManager::FindPath(INTPOINT tSrc, INTPOINT tDest)
{
	init_astar();

	INTPOINT s = TILEMANAGER->GetIndex(tSrc);
	INTPOINT src;
	src.x = s.x;
	src.y = s.y;

	INTPOINT d = TILEMANAGER->GetIndex(tDest);
	INTPOINT dest;
	dest.x = d.x;
	dest.y = d.y;

	node_t* present, *best = NULL;
	int count = 0;

	//시작 위치 노드 추가 
	present = (node_t*)calloc(1, sizeof(node_t));
	present->degree = 0;
	present->distance = (dest.x - src.x)*(dest.x - src.x) + (dest.y - src.y)*(dest.y - src.y);
	present->value_factor = present->distance;
	present->pos.x = src.x;
	present->pos.y = src.y;

	OPEN = present;

	while (count < FINDPATH_LIMIT) {

		if (OPEN == NULL) return best;

		best = OPEN;					   //매 루프문을 돌면서 OpenNode의 후보로부터 탐색을 우선 시도합니다. 
		OPEN = best->next_node;     //그리고 그 다음 노드가 OpenNode의 최상위 후보노드로 지정되며 
		best->next_node = CLOSED;  //지금까지 구축된 최적의 노드를 이번에 탐색할 best노드와 연결함으로써 
								   //현재까지 탐색된  최적의 길을 유지하게 됩니다. 
		CLOSED = best;						//이 best노드는 이번 루프에서 탐색 시도되므로 close노드로 들어가게 되는거죠. 


		if (best == NULL) return NULL;

		//목적지 도착.
		if (best->pos.x == dest.x && best->pos.y == dest.y) return best;
		
		if (make_child(best, dest) == 0 && count == 0) return NULL;
		

		count++;

	}

	return best;

	
}
