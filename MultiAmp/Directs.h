#pragma once
class Direct{
public:
	static const size_t CNTROTATES = 9;

	Direct(size_t idx = 0){ i = idx; }
	Direct(int x, int y){ i = find(x, y); }
	Direct operator = (const Direct& other){ i = other.i; return *this; }
	Direct operator = (const size_t other){ i = other; return *this; }

	size_t i = 0;
	const int vx[CNTROTATES] = {0, 0, 1, 1, 1, 0,-1,-1,-1};
	const int vy[CNTROTATES] = {0,-1,-1, 0, 1, 1, 1, 0,-1};

	void set(int x, int y){ i = find(x, y); }
	Direct horiz(){ return find(vx[i], -vy[i]); }
	Direct vert(){ return find(-vx[i], vy[i]); }
	Direct slope(){ return find(vy[i], vx[i]); }
	Direct rise(){ return find(-vy[i], -vx[i]); }
private:
	size_t find(int x, int y){
		for(size_t j = 0; j < CNTROTATES; j++)
			if(vx[j] == x && vy[j] == y)
				return j;
		return CNTROTATES;
	};
};

