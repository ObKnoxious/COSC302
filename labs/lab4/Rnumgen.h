#ifndef __RNUMGEN_H__
#define __RNUMGEN_H__

#include <vector>
#include <functional>
#include <algorithm>
class rnumgen {
	public:
		rnumgen(int seedvalue, std::vector<int> &v);

		int rand() const;

	private:
		std::vector<float> F;	
};

#endif
