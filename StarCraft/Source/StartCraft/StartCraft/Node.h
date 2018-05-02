#pragma once

struct INTPOINT;

class CNode
{

	public CNaviNode pParent = null;

	//현재 노드를 주어진 노드의 내용물로 복사

	public void Copy(CNaviNode pNode)

	{

		x = pNode.x;

		y = pNode.y;

		dist = pNode.dist;

		depth = pNode.depth;

		pParent = pNode.pParent;

	}

private:
	INTPOINT pos;
	int dist;
	int depth;
};