#include <mwe/mwe.hpp>

#include <omp.h>

namespace mwe {

int return_0() noexcept { return 0; }

uint64_t uses_omp() noexcept {
	uint64_t s = 0;
	#pragma omp parallel for reduction(+:s)
	for (uint64_t i = 0; i < 500000u; ++i) {
		for (uint64_t j = 0; j <= i; ++j) {
			s += i + j;
		}
	}
	return s;
}

uint64_t not_uses_omp() noexcept {
	uint64_t s = 0;
	for (uint64_t i = 0; i < 500000u; ++i) {
		for (uint64_t j = 0; j <= i; ++j) {
			s += i + j;
		}
	}
	return s;
}

}
