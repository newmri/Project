#pragma once

struct INTPOINT;

class CNode
{

	public CNaviNode pParent = null;

	//���� ��带 �־��� ����� ���빰�� ����

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