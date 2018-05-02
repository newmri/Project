#include "stdafx.h"
#include "Tile.h"

CPathManager*	CPathManager::m_pInstance = nullptr;

node_t *OPEN = NULL, *CLOSED = NULL;
node_stack_t* STACK = NULL;

const int FINDPATH_LIMIT = 200;          //Ž�� ���� ���� ȸ�� 

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
	CObj* p = TILEMANAGER->SelectTile(nIdx);
	return dynamic_cast<CTile*>(p)->IsMovable();
}

node_t * CPathManager::is_open(int x, int y)
{
	node_t *temp = OPEN;

	while (temp) {
		if (temp->x == x && temp->y == y)
			return temp;
		temp = temp->next_node;
	}

	return NULL;
}

node_t * CPathManager::is_closed(int x, int y)
{
	node_t *temp = CLOSED;

	while (temp) {
		if (temp->x == x && temp->y == y)
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

	//OPEN�� �ִ� ��尡 ���� �ڽ� ��庸�� ��ġ�� ������
	//OPEN��带 �����ؼ� ���� �ڽ� ��庸�� ��ġ�� ���� ��带 ã�´�. 
	while (temp && (temp->value_factor < present->value_factor)) {
		old = temp;
		temp = temp->next_node;
	}

	//���� ��ġ�� OpenNode �� ������� ���� ����� ��� -> �߰��� �ڽ� ��� -> ���� ��ġ�� OpenNode�� ������� ���� �� ���
	if (old) {
		present->next_node = temp;
		old->next_node = present;
	}
	else {
		present->next_node = temp;
		OPEN = present;
	}
}

void CPathManager::extend_child_node(node_t * node, int x, int y, int dest_x, int dest_y, int cur_direct)
{
	node_t* old = NULL, *child = NULL;
	int i;
	int degree = node->degree + 1;

	if (old = is_open(x, y)) {

		node->direct[cur_direct] = old;

		//�׸��� ��� �翬�� �� ���� . ����� ��� ������ �ݴ�� ����ȴٴ� �� ����� ��. 
		if (degree<old->degree) {
			old->prev_node = node;
			old->degree = degree;
			old->value_factor = old->distance + old->degree;
		}//if()

	}
	else if (old = is_closed(x, y)) {

		node->direct[cur_direct] = old;

		//� ��쿡�� ���� CloseNode�� �ִ� ����� degree�� �� ���� ��찡 �߻��� ���� �ִµ�
		//�� �� ������ �ٽ� ����      
		if (degree<old->degree) {
			old->prev_node = node;
			old->degree = degree;
			old->value_factor = old->distance + old->degree;
			make_sort(old);
		}//if()

		 //Ȯ���� ��� ���� �� OpenNode ����Ʈ�� �߰�
	}
	else {
		if ((child = (node_t*)calloc(1, sizeof(node_t))) == NULL)
			return;

		child->prev_node = node;
		child->degree = degree;
		child->distance = (x - dest_x)*(x - dest_x) + (y - dest_y)*(y - dest_y);
		child->value_factor = child->distance + child->degree;
		child->x = x;
		child->y = y;

		insert_node(child);

		node->direct[cur_direct] = child;

	}
}

char CPathManager::make_child(node_t * node, int dest_x, int dest_y)
{
	int x, y;
	char flag = 0;
	char checkis_available_grid[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

	x = node->x;
	y = node->y;

	//�̵� �������� ���� �Ǵ�.
	checkis_available_grid[DIRECTION_RIGHTDOWN] = is_available_grid(x, y + 1);
	checkis_available_grid[DIRECTION_DOWN] = is_available_grid(x, y + 1);
	checkis_available_grid[DIRECTION_LEFTDOWN] = is_available_grid(x - 1, y + 1);
	checkis_available_grid[DIRECTION_LEFT] = is_available_grid(x - 1, y);
	checkis_available_grid[DIRECTION_LEFTUP] = is_available_grid(x - 1, y - 1);
	checkis_available_grid[DIRECTION_UP] = is_available_grid(x, y - 1);
	checkis_available_grid[DIRECTION_RIGHTUP] = is_available_grid(x + 1, y - 1);
	checkis_available_grid[DIRECTION_RIGHT] = is_available_grid(x + 1, y);

	//�� �̵� ������ ��忡 ���� �ڽ� ��� ���� 
	if (checkis_available_grid[DIRECTION_LEFT]) {
		extend_child_node(node, x - 1, y, dest_x, dest_y, DIRECTION_LEFT);
		flag = 1;
	}//if()

	if (checkis_available_grid[DIRECTION_RIGHT]) {
		extend_child_node(node, x + 1, y, dest_x, dest_y, DIRECTION_RIGHT);
		flag = 1;
	}//if()

	if (checkis_available_grid[DIRECTION_UP]) {
		extend_child_node(node, x, y - 1, dest_x, dest_y, DIRECTION_UP);
		flag = 1;
	}//if()

	if (checkis_available_grid[DIRECTION_DOWN]) {
		extend_child_node(node, x, y + 1, dest_x, dest_y, DIRECTION_DOWN);
		flag = 1;
	}//if()

	if (checkis_available_grid[DIRECTION_RIGHTDOWN] && checkis_available_grid[DIRECTION_RIGHT] && checkis_available_grid[DIRECTION_DOWN]) {
		extend_child_node(node, x + 1, y + 1, dest_x, dest_y, DIRECTION_RIGHTDOWN);
		flag = 1;
	}//if()

	if (checkis_available_grid[DIRECTION_LEFTUP] && checkis_available_grid[DIRECTION_LEFT] && checkis_available_grid[DIRECTION_UP]) {
		extend_child_node(node, x - 1, y - 1, dest_x, dest_y, DIRECTION_LEFTUP);
		flag = 1;
	}//if()

	if (checkis_available_grid[DIRECTION_RIGHTUP] && checkis_available_grid[DIRECTION_RIGHT] && checkis_available_grid[DIRECTION_UP]) {
		extend_child_node(node, x + 1, y - 1, dest_x, dest_y, DIRECTION_RIGHTUP);
		flag = 1;
	}//if()

	if (checkis_available_grid[DIRECTION_LEFTDOWN] && checkis_available_grid[DIRECTION_LEFT] && checkis_available_grid[DIRECTION_DOWN]) {
		extend_child_node(node, x - 1, y + 1, dest_x, dest_y, DIRECTION_LEFTDOWN);
		flag = 1;
	}//if()

	return flag;

}



node_t* CPathManager::FindPath(POINT tSrc, POINT tDest)
{
	
	INTPOINT src = TILEMANAGER->GetIndex(tSrc);
	INTPOINT dest = TILEMANAGER->GetIndex(tDest);

		node_t* present, *best = NULL;
		int count = 0;

		//���� ��ġ ��� �߰� 
		present = (node_t*)calloc(1, sizeof(node_t));
		present->degree = 0;
		present->distance = (dest.x - src.x)*(dest.x - src.x) + (dest.y - src.y)*(dest.y - src.y);
		present->value_factor = present->distance;
		present->x = dest.x;
		present->y = dest.y;

		OPEN = present;

		while (count< FINDPATH_LIMIT) {

			if (OPEN == NULL)
				return best;

			best = OPEN;					   //�� �������� ���鼭 OpenNode�� �ĺ��κ��� Ž���� �켱 �õ��մϴ�. 
			OPEN = best->next_node;     //�׸��� �� ���� ��尡 OpenNode�� �ֻ��� �ĺ����� �����Ǹ� 
			best->next_node = CLOSED;  //���ݱ��� ����� ������ ��带 �̹��� Ž���� best���� ���������ν� 
									   //������� Ž����  ������ ���� �����ϰ� �˴ϴ�. 
			CLOSED = best;						//�� best���� �̹� �������� Ž�� �õ��ǹǷ� close���� ���� �Ǵ°���. 


			if (best == NULL)
				return NULL;

			//������ ����.
			if (best->x == src.x && best->y == src.y) return best;

			if (make_child(best, src.x, src.y) == 0 && count == 0)
				return NULL;

			count++;

		}

		return best;

	
}
