#pragma once
class Sala
{
	bool _visited;
	int _type;
public:
	Sala();
	~Sala();
	void setVisited() { _visited = true; }
	bool getVisited() { return _visited; }
	void setType(int d);
	int getType() { return _type; }
};

