#include <tfm/test_for_mac.hpp>

namespace tfm {

int return_0() noexcept { return 0; }

int uses_omp() noexcept {
	int s = 0;
	
	#pragma omp parallel for reduction(+:s)
	for (int i = 0; i < 10000; ++i) {
	}
	
	return s;
}

}
