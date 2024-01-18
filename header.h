#include<iostream>
#include<fstream>
using namespace std;
class node
{
public:
	int data;
	node* next;
	node* prev;
	node* up;
	node* down;
	node(int d)
	{
		data = d;
		next = NULL;
		prev = NULL;
		up = NULL;
		down = NULL;
	}
};

//--------------------Task 1----------------------
class Transport_Layer_optimization
{
	node* metroHead, * busHead, * walkHead;
	int stops[3];
	int currentLocation;
public:
	Transport_Layer_optimization()
	{
		metroHead = NULL;
		busHead = NULL;
		walkHead = NULL;
	}
	void ReadFile(string location)
	{
		ifstream file(location);
		for (int sizes = 0; sizes < 3; sizes++)
		{
			file >> stops[sizes];
		}
		for (int metros = 0; metros < stops[0]; metros++)
		{
			file >> currentLocation;
			addNode(1, currentLocation);
		}
		for (int buses = 0; buses < stops[1]; buses++)
		{
			file >> currentLocation;
			addNode(2, currentLocation);
		}
		for (int walks = 0; walks < stops[2]; walks++)
		{
			file >> currentLocation;
			addNode(3, currentLocation);
		}
		connectNodes();
		file.close();
	}
	void display()
	{
		node* thisNode = metroHead;
		while (thisNode != NULL)
		{
			cout << thisNode->data << " ";
			thisNode = thisNode->next;
		}
		cout << endl;
		thisNode = busHead;
		while (thisNode != NULL)
		{
			cout << thisNode->data << " ";
			thisNode = thisNode->next;
		}
		cout << endl;
		thisNode = walkHead;
		while (thisNode != NULL)
		{
			cout << thisNode->data << " ";
			thisNode = thisNode->next;
		}
		cout << endl;
	}
	string GetPath(int a, int b)
	{
		int currentLayer;
		bool start = false, change = false, back = false, repeat = false;
		node* thisNode = metroHead;
		string result, extra;
		while (thisNode != NULL)
		{
			if (thisNode->data == a)
			{
				start = true;
				currentLayer = 1;
				break;
			}
			thisNode = thisNode->next;
		}
		if (!start)
		{
			thisNode = busHead;
			while (thisNode != NULL)
			{
				if (thisNode->data == a)
				{
					start = true;
					currentLayer = 2;
					break;
				}
				thisNode = thisNode->next;
			}
		}
		if (!start)
		{
			thisNode = walkHead;
			while (thisNode != NULL)
			{
				if (thisNode->data == a)
				{
					start = true;
					currentLayer = 3;
					break;
				}
				thisNode = thisNode->next;
			}
		}
		if (!start)
		{
			result = "Path doesn't exist\n";
			return result;
		}
		else
		{
			while (thisNode != NULL)
			{
				if (back)
				{
					repeat = false;
				}
				if (!repeat && extra != "")
				{
					if (thisNode->data + 48 == int(extra[4]))
					{
						int remove1 = result.length() - 1;
						int remove2 = extra.length() - 1;
						if (remove2 != -1)
						{
							result = result.substr(0, remove1 - remove2);
							extra = "";
						}
					}
					else
					{
						extra += " -> ";
						extra += to_string(thisNode->data);
						extra += "-";
						extra += to_string(currentLayer);
					}
				}
				if (repeat)
				{
					extra += " -> ";
					extra += to_string(thisNode->data);
					extra += "-";
					extra += to_string(currentLayer);
				}
				if (start)
				{
					start = false;
				}
				else
				{
					result += " -> ";
				}
				if (thisNode != NULL)
				{
					result += to_string(thisNode->data);
				}
				result += "-";
				result += to_string(currentLayer);
				if (thisNode->data == b)
				{
					break;
				}
				if (thisNode->up != NULL && change == false)
				{
					thisNode = thisNode->up;
					currentLayer--;
					back = false;
				}
				else if (thisNode->next != NULL && a < b || thisNode->prev != NULL && a > b)
				{
					if (a < b)
					{
						if (thisNode->data == thisNode->next->data - 1 && back == false)
						{
							if (thisNode->down != NULL)
							{
								repeat = true;
							}
							thisNode = thisNode->next;
							change = false;
						}
						else if (thisNode->down != NULL)
						{
							thisNode = thisNode->down;
							currentLayer++;
							change = true;
							back = false;
						}
						else
						{
							thisNode = thisNode->prev;
							back = true;
							change = false;
						}
					}
					else if (a > b)
					{
						if (thisNode->data == thisNode->prev->data + 1 && back == false)
						{
							if (thisNode->down != NULL)
							{
								repeat = true;
							}
							thisNode = thisNode->prev;
							change = false;
						}
						else if (thisNode->down != NULL)
						{
							thisNode = thisNode->down;
							currentLayer++;
							change = true;
							back = false;
						}
						else
						{
							thisNode = thisNode->next;
							back = true;
							change = false;
						}
					}
				}
				else
				{
					if (a < b)
					{
						if (thisNode->down != NULL)
						{
							thisNode = thisNode->down;
							currentLayer++;
							change = true;
							back = false;
						}
						else
						{
							thisNode = thisNode->prev;
							back = true;
						}
					}
					else if (a > b)
					{
						if (thisNode->down != NULL)
						{
							thisNode = thisNode->down;
							currentLayer++;
							change = true;
							back = false;
						}
						else
						{
							thisNode = thisNode->next;
							back = true;
						}
					}
				}
			}
		}
		return result;
	}
	void addNode(int layer, int Location_id)
	{
		bool middle = false;
		if (layer == 1)
		{
			node* thisNode = metroHead;
			node* thatNode = thisNode;
			while (thisNode != NULL)
			{
				if (thisNode->data > Location_id)
				{
					middle = true;
					break;
				}
				thatNode = thisNode;
				thisNode = thisNode->next;
			}
			if (middle)
			{
				node* temp = thisNode;
				thisNode = new node(Location_id);
				temp->prev = thisNode;
				thisNode->next = temp;
			}
			else
			{
				thisNode = new node(Location_id);
				thisNode->next = NULL;
			}
			thisNode->up = NULL;
			thisNode->down = NULL;
			if (thisNode != thatNode && thatNode != NULL)
			{
				thisNode->prev = thatNode;
				thatNode->next = thisNode;
			}
			if (metroHead == NULL)
			{
				thisNode->prev = NULL;
				metroHead = thisNode;
			}
		}
		else if (layer == 2)
		{
			node* thisNode = busHead;
			node* thatNode = thisNode;
			while (thisNode != NULL)
			{
				if (thisNode->data > Location_id)
				{
					middle = true;
					break;
				}
				thatNode = thisNode;
				thisNode = thisNode->next;
			}
			if (middle)
			{
				node* temp = thisNode;
				thisNode = new node(Location_id);
				temp->prev = thisNode;
				thisNode->next = temp;
			}
			else
			{
				thisNode = new node(Location_id);
				thisNode->next = NULL;
			}
			thisNode->up = NULL;
			thisNode->down = NULL;
			if (thisNode != thatNode && thatNode != NULL)
			{
				thisNode->prev = thatNode;
				thatNode->next = thisNode;
			}
			if (busHead == NULL)
			{
				thisNode->prev = NULL;
				busHead = thisNode;
			}
		}
		else if (layer == 3)
		{
			node* thisNode = walkHead;
			node* thatNode = thisNode;
			while (thisNode != NULL)
			{
				if (thisNode->data > Location_id)
				{
					middle = true;
					break;
				}
				thatNode = thisNode;
				thisNode = thisNode->next;
			}
			if (middle)
			{
				node* temp = thisNode;
				thisNode = new node(Location_id);
				temp->prev = thisNode;
				thisNode->next = temp;
			}
			else
			{
				thisNode = new node(Location_id);
				thisNode->next = NULL;
			}
			thisNode->up = NULL;
			thisNode->down = NULL;
			if (thisNode != thatNode && thatNode != NULL)
			{
				thisNode->prev = thatNode;
				thatNode->next = thisNode;
			}
			if (walkHead == NULL)
			{
				thisNode->prev = NULL;
				walkHead = thisNode;
			}
		}
	}
	void connectNodes()
	{
		node* thisMetro = metroHead, * thisBus = busHead, * thisWalk = walkHead;
		while (thisMetro != NULL && thisBus != NULL)
		{
			if (thisMetro->data == thisBus->data)
			{
				thisMetro->down = thisBus;
				thisBus->up = thisMetro;
				thisMetro = thisMetro->next;
				thisBus = thisBus->next;
			}
			else if (thisMetro->data > thisBus->data)
			{
				thisBus = thisBus->next;
			}
			else if (thisMetro->data < thisBus->data)
			{
				thisMetro = thisMetro->next;
			}
		}
		thisBus = busHead;
		while (thisBus != NULL && thisWalk != NULL)
		{
			if (thisBus->data == thisWalk->data)
			{
				thisBus->down = thisWalk;
				thisWalk->up = thisBus;
				thisBus = thisBus->next;
				thisWalk = thisWalk->next;
			}
			else if (thisBus->data > thisWalk->data)
			{
				thisWalk = thisWalk->next;
			}
			else if (thisBus->data < thisWalk->data)
			{
				thisBus = thisBus->next;
			}
		}
	}
	void DeleteNode(int layer, int Location_id)
	{
		node* thisNode, * thatNode;
		if (layer == 1)
		{
			thisNode = metroHead;
		}
		else if (layer == 2)
		{
			thisNode = busHead;
		}
		else
		{
			thisNode = walkHead;
		}
		while (thisNode != NULL)
		{
			if (thisNode->data == Location_id)
			{
				break;
			}
			thatNode = thisNode;
			thisNode = thisNode->next;
		}
		thatNode->next = thisNode->next;
		if (layer == 1)
		{
			node* temp = thisNode->down;
			thisNode->down = NULL;
			temp->up = NULL;
		}
		else if (layer == 2)
		{
			node* temp = thisNode->up;
			node* temp2 = thisNode->down;
			thisNode->up = NULL;
			thisNode->down = NULL;
			temp->down = NULL;
			temp2->up = NULL;
		}
		else
		{
			node* temp = thisNode->up;
			thisNode->up = NULL;
			temp->down = NULL;
		}
		delete thisNode;
	}
	~Transport_Layer_optimization()
	{
		delete metroHead;
		delete busHead;
		delete walkHead;
	}
};

//--------------------Task 2----------------------
class Transport_Cost_Calculator
{
	node* metroHead, * busHead, * walkHead, * metroTail;
	int stops;
	int currentPrice;
public:
	Transport_Cost_Calculator()
	{
		metroHead = NULL;
		busHead = NULL;
		walkHead = NULL;
	}
	void ReadFile(string location)
	{
		ifstream file(location);
		file >> stops;
		for (int metros = 1; metros < stops; metros++)
		{
			file >> currentPrice;
			addNode(1, currentPrice);
		}
		for (int buses = 1; buses < stops; buses++)
		{
			file >> currentPrice;
			addNode(2, currentPrice);
		}
		for (int walks = 1; walks < stops; walks++)
		{
			file >> currentPrice;
			addNode(3, currentPrice);
		}
		connectNodes();
		file.close();
	}
	void addNode(int layer, int price)
	{
		node* thisNode, * thatNode = NULL;
		bool start = true;
		if (layer == 1)
		{
			thisNode = metroHead;
		}
		else if (layer == 2)
		{
			thisNode = busHead;
		}
		else
		{
			thisNode = walkHead;
		}
		while (thisNode != NULL)
		{
			thatNode = thisNode;
			thisNode = thisNode->next;
			start = false;
		}
		thisNode = new node(price);
		if (thisNode != thatNode && start == false)
		{
			thatNode->next = thisNode;
			thisNode->prev = thatNode;
		}
		else
		{
			if (layer == 1)
			{
				metroHead = thisNode;
			}
			else if (layer == 2)
			{
				busHead = thisNode;
			}
			else
			{
				walkHead = thisNode;
			}
		}
	}
	void connectNodes()
	{
		node* thisMetro = metroHead, * thisBus = busHead, * thisWalk = walkHead;
		while (thisMetro != NULL && thisBus != NULL)
		{
			thisMetro->down = thisBus;
			thisBus->up = thisMetro;
			thisMetro = thisMetro->next;
			thisBus = thisBus->next;
		}
		thisBus = busHead;
		while (thisBus != NULL && thisWalk != NULL)
		{
			thisBus->down = thisWalk;
			thisWalk->up = thisBus;
			thisBus = thisBus->next;
			thisWalk = thisWalk->next;
		}
	}
	int GetMinCost(int start, int end)
	{
		node* thisNode = metroHead;
		int location = start;
		int totalCost = 0, minCost = 0, totalMinCost = 1000000;
		int layer, newLayer, mid, midLayer;
		for (int startLayer = 1; startLayer <= 3; startLayer++)
		{
			if (start > end && start - end > 1)
			{
				mid = start - 1;
			}
			else if (start < end && end - start > 1)
			{
				mid = start + 1;
			}
			else
			{
				mid = start;
			}
			findStart(thisNode, totalCost, layer, startLayer, start, end, location);
			goToEnd(thisNode, location, end, totalCost, totalMinCost);
			while (mid != end)
			{
				findStart(thisNode, totalCost, layer, startLayer, start, end, location);
				calculateCost(thisNode, minCost, totalCost, totalMinCost, newLayer, layer, location, mid, end);
				moveLayers(thisNode, minCost, totalCost, layer);
				calculateCost(thisNode, minCost, totalCost, totalMinCost, newLayer, layer, location, end, end);
				if (totalMinCost > totalCost)
				{
					totalMinCost = totalCost;
				}
				if (mid > end)
				{
					mid--;
				}
				else
				{
					mid++;
				}
			}
		}
		return totalMinCost;
	}
	void findStart(node*& thisNode, int& totalCost, int& layer, int startLayer, int start, int end, int& location)
	{
		location = start;
		layer = startLayer;
		totalCost = 0;
		if (layer == 1)
		{
			thisNode = metroHead;
		}
		else if (layer == 2)
		{
			thisNode = metroHead->down;
		}
		else
		{
			thisNode = metroHead->down->down;
		}
		if (start < end)
		{
			for (int go = 1; go < start; go++)
			{
				thisNode = thisNode->next;
			}
		}
		else
		{
			for (int go = 1; go < end; go++)
			{
				thisNode = thisNode->next;
			}
		}
	}
	void calculateCost(node*& thisNode, int& minCost, int& totalCost, int& totalMinCost, int& newLayer, int& layer, int& location, int end, int realEnd)
	{
		bool change = false;
		while (location != end)
		{
			change = false;
			minCost = thisNode->data;
			newLayer = layer;
			if (layer == 1)
			{
				if (thisNode->down->data < minCost)
				{
					if (thisNode->next->next != NULL)
					{
						if (thisNode->down->data + thisNode->down->next->data + 5 < thisNode->data + thisNode->next->data && thisNode->down->data + thisNode->down->next->data + thisNode->down->next->data + 5 < thisNode->data + thisNode->next->data + thisNode->next->next->data)
						{
							node* temp = thisNode;
							thisNode = thisNode->down;
							goToEnd(thisNode, location, realEnd, totalCost + 5, totalMinCost);
							thisNode = temp;
							minCost = thisNode->down->data + 5;
							newLayer = 2;
						}
					}
					if (thisNode->down->data + 5 < minCost)
					{
						node* temp = thisNode;
						thisNode = thisNode->down;
						goToEnd(thisNode, location, realEnd, totalCost + 5, totalMinCost);
						thisNode = temp;
						minCost = thisNode->down->data + 5;
						newLayer = 2;
					}
				}
				if (thisNode->down->down->data < minCost)
				{
					if (thisNode->next->next != NULL)
					{
						if (thisNode->down->down->data + thisNode->down->down->next->data + 10 < thisNode->data + thisNode->next->data && thisNode->down->down->data + thisNode->down->down->next->data + thisNode->down->down->next->data + 10 < thisNode->data + thisNode->next->data + thisNode->next->next->data)
						{
							node* temp = thisNode;
							thisNode = thisNode->down->down;
							goToEnd(thisNode, location, realEnd, totalCost + 10, totalMinCost);
							thisNode = temp;
							minCost = thisNode->down->down->data + 10;
							newLayer = 3;
						}
					}
					else if (thisNode->down->down->data + 10 < minCost)
					{
						node* temp = thisNode;
						thisNode = thisNode->down->down;
						goToEnd(thisNode, location, realEnd, totalCost + 10, totalMinCost);
						thisNode = temp;
						minCost = thisNode->down->down->data + 10;
						newLayer = 3;
					}
				}
			}
			else if (layer == 2)
			{
				if (thisNode->down->data < minCost)
				{
					if (thisNode->next->next != NULL)
					{
						if (thisNode->down->data + thisNode->down->next->data + 5 < thisNode->data + thisNode->next->data && thisNode->down->data + thisNode->down->next->data + thisNode->down->next->data + 5 < thisNode->data + thisNode->next->data + thisNode->next->next->data)
						{
							node* temp = thisNode;
							thisNode = thisNode->down;
							goToEnd(thisNode, location, realEnd, totalCost + 5, totalMinCost);
							thisNode = temp;
							minCost = thisNode->down->data + 5;
							newLayer = 3;
						}
					}
					else if (thisNode->down->data + 5 < minCost)
					{
						node* temp = thisNode;
						thisNode = thisNode->down;
						goToEnd(thisNode, location, realEnd, totalCost + 5, totalMinCost);
						thisNode = temp;
						minCost = thisNode->down->data + 5;
						newLayer = 3;
					}
				}
				if (thisNode->up->data < minCost)
				{
					if (thisNode->next->next != NULL)
					{
						if (thisNode->up->data + thisNode->up->next->data + 5 < thisNode->data + thisNode->next->data && thisNode->up->data + thisNode->up->next->data + thisNode->up->next->data + 5 < thisNode->data + thisNode->next->data + thisNode->next->next->data)
						{
							node* temp = thisNode;
							thisNode = thisNode->up;
							goToEnd(thisNode, location, realEnd, totalCost + 5, totalMinCost);
							thisNode = temp;
							minCost = thisNode->up->data + 5;
							newLayer = 1;
						}
					}
					else if (thisNode->up->data + 5 < minCost)
					{
						node* temp = thisNode;
						thisNode = thisNode->up;
						goToEnd(thisNode, location, realEnd, totalCost + 5, totalMinCost);
						thisNode = temp;
						minCost = thisNode->up->data + 5;
						newLayer = 1;
					}
				}
			}
			else
			{
				if (thisNode->up->data < minCost)
				{
					if (thisNode->next->next != NULL)
					{
						if (thisNode->up->data + thisNode->up->next->data + 5 < thisNode->data + thisNode->next->data && thisNode->up->data + thisNode->up->next->data + thisNode->up->next->data + 5 < thisNode->data + thisNode->next->data + thisNode->next->next->data)
						{
							node* temp = thisNode;
							thisNode = thisNode->up;
							goToEnd(thisNode, location, realEnd, totalCost + 5, totalMinCost);
							thisNode = temp;
							minCost = thisNode->up->data + 5;
							newLayer = 2;
						}
					}
					else if (thisNode->up->data + 5 < minCost)
					{
						node* temp = thisNode;
						thisNode = thisNode->up;
						goToEnd(thisNode, location, realEnd, totalCost + 5, totalMinCost);
						thisNode = temp;
						minCost = thisNode->up->data + 5;
						newLayer = 2;
					}
				}
				if (thisNode->up->up->data < minCost)
				{
					if (thisNode->next->next != NULL)
					{
						if (thisNode->up->up->data + thisNode->up->up->next->data + 10 < thisNode->data + thisNode->next->data && thisNode->up->up->data + thisNode->up->up->next->data + thisNode->up->up->next->data + 10 < thisNode->data + thisNode->next->data + thisNode->next->next->data)
						{
							node* temp = thisNode;
							thisNode = thisNode->up->up;
							goToEnd(thisNode, location, realEnd, totalCost + 10, totalMinCost);
							thisNode = temp;
							minCost = thisNode->up->up->data + 10;
							newLayer = 1;
						}
					}
					else if (thisNode->up->up->data + 10 < minCost)
					{
						node* temp = thisNode;
						thisNode = thisNode->up->up;
						goToEnd(thisNode, location, realEnd, totalCost + 10, totalMinCost);
						thisNode = temp;
						minCost = thisNode->up->up->data + 10;
						newLayer = 1;
					}
				}
			}
			if (layer == 1)
			{
				if (newLayer == 2)
				{
					thisNode = thisNode->down;
				}
				else if (newLayer == 3)
				{
					thisNode = thisNode->down->down;
				}
			}
			else if (layer == 2)
			{
				if (newLayer == 1)
				{
					thisNode = thisNode->up;
				}
				else if (newLayer == 3)
				{
					thisNode = thisNode->down;
				}
			}
			else
			{
				if (newLayer == 1)
				{
					thisNode = thisNode->up->up;
				}
				else if (newLayer == 2)
				{
					thisNode = thisNode->up;
				}
			}
			layer = newLayer;
			totalCost += minCost;
			thisNode = thisNode->next;
			if (thisNode == NULL)
			{
				break;
			}
			if (location < end)
			{
				location++;
			}
			else if (location > end)
			{
				location--;
			}
		}
	}
	void moveLayers(node*& thisNode, int& minCost, int& totalCost, int& layer)
	{
		minCost = thisNode->data;
		if (layer == 1)
		{
			if (minCost > thisNode->down->data)
			{
				totalCost += 5;
				layer = 2;
				minCost = thisNode->down->data;
			}
			if (minCost > thisNode->down->down->data)
			{
				thisNode = thisNode->down->down;
				totalCost += 10;
				if (layer == 2)
				{
					totalCost -= 5;
				}
				layer = 3;
			}
			if (layer == 2)
			{
				thisNode = thisNode->down;
			}
		}
		else if (layer == 2)
		{
			if (minCost > thisNode->down->data)
			{
				totalCost += 5;
				layer = 3;
				minCost = thisNode->down->data;
			}
			if (minCost > thisNode->up->data)
			{
				thisNode = thisNode->up;
				totalCost += 5;
				if (layer == 3)
				{
					totalCost -= 5;
				}
				layer = 1;
			}
			if (layer == 3)
			{
				thisNode = thisNode->down;
			}
		}
		else
		{
			if (minCost > thisNode->up->data)
			{
				totalCost += 5;
				layer = 2;
				minCost = thisNode->up->data;
			}
			if (minCost > thisNode->up->up->data)
			{
				thisNode = thisNode->up->up;
				totalCost += 10;
				if (layer == 2)
				{
					totalCost -= 5;
				}
				layer = 1;
			}
			if (layer == 2)
			{
				thisNode = thisNode->up;
			}
		}
	}
	void goToEnd(node*& thisNode, int location, int end, int totalCost, int& totalMinCost)
	{
		while (location != end)
		{
			totalCost += thisNode->data;
			thisNode = thisNode->next;
			if (location < end)
			{
				location++;
			}
			else
			{
				location--;
			}
		}
		if (totalMinCost > totalCost)
		{
			totalMinCost = totalCost;
		}
	}
	~Transport_Cost_Calculator()
	{

	}
};