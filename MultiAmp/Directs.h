#pragma once
class Direct{
public:
	static const size_t CNTROTATES = 9;

	Direct(size_t idx = 0){ i = idx; }
	Direct(int x, int y){ i = find(x, y); }

	size_t i = 0;
	const int vx[CNTROTATES] = {0, 0, 1, 1, 1, 0,-1,-1,-1};
	const int vy[CNTROTATES] = {0,-1,-1, 0, 1, 1, 1, 0,-1};

	void set(int x, int y){ i = find(x, y); }
	Direct rotate(int cnt_rotate){ i = (i + cnt_rotate + CNTROTATES * 256) % CNTROTATES; }
	Direct horiz(){ return Direct(find(vx[i], -vy[i])); }
	Direct vert(){ return Direct(find(-vx[i], vy[i])); }
	Direct slope(){ return Direct(find(vy[i], vx[i])); }
	Direct rise(){ return Direct(find(-vy[i], -vx[i])); }
private:
	size_t find(int x, int y){
		for(size_t j = 0; j < CNTROTATES; j++)
			if(vx[j] == x && vy[j] == y)
				return j;
		return CNTROTATES;
	};
};

