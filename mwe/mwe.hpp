#pragma once

#include <string>

namespace mwe {

std::string return_hello_world() noexcept;
std::string return_goodbye_world() noexcept;

int return_0() noexcept;

uint64_t uses_omp() noexcept;
uint64_t not_uses_omp() noexcept;

} // -- namespace tfm
