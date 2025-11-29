/*
	MIT License

	Copyright (c) 2024 RealTimeChris

	Permission is hereby granted, free of charge, to any person obtaining a copy of this
	software and associated documentation files (the "Software"), to deal in the Software
	without restriction, including without limitation the rights to use, copy, modify, merge,
	publish, distribute, sublicense, and/or sell copies of the Software, and to permit
	persons to whom the Software is furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all copies or
	substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
	INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
	PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
	FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
	OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
	DEALINGS IN THE SOFTWARE.
*/
/// https://github.com/RealTimeChris/benchmarksuite
#include <bnch_swt/index.hpp>

static constexpr uint64_t total_iterations{ 10 };
static constexpr uint64_t measured_iterations{ 10 };

template<typename value_type>
concept integral_types = std::is_integral_v<std::remove_cvref_t<value_type>>;

template<uint64_t shift, integral_types value_type> BNCH_SWT_HOST_DEVICE constexpr value_type operator<<(const value_type arg, std::integral_constant<uint64_t, shift>) noexcept {
	constexpr uint64_t shift_amount{ shift };
	return arg << shift_amount;
}

template<uint64_t shift, integral_types value_type> BNCH_SWT_HOST_DEVICE constexpr value_type& operator<<=(value_type& arg, std::integral_constant<uint64_t, shift>) noexcept {
	constexpr uint64_t shift_amount{ shift };
	return arg = arg << shift_amount;
}

template<uint64_t shift, integral_types value_type> BNCH_SWT_HOST_DEVICE constexpr value_type operator>>(const value_type arg, std::integral_constant<uint64_t, shift>) noexcept {
	constexpr uint64_t shift_amount{ shift };
	return arg >> shift_amount;
}

template<uint64_t shift, integral_types value_type> BNCH_SWT_HOST_DEVICE constexpr value_type& operator>>=(value_type& arg, std::integral_constant<uint64_t, shift>) noexcept {
	constexpr uint64_t shift_amount{ shift };
	return arg = arg >> shift_amount;
}

BNCH_SWT_NOINLINE void regular_shift() {
	uint64_t regular_shift{ static_cast<uint64_t>(rand()) };
	regular_shift = regular_shift << 32;
	bnch_swt::do_not_optimize_away(regular_shift);
}

BNCH_SWT_NOINLINE void constexpr_shift() {
	uint64_t regular_shift{ static_cast<uint64_t>(rand()) };
	regular_shift = regular_shift << std::integral_constant<uint64_t, 32>{};
	bnch_swt::do_not_optimize_away(regular_shift);
}

int main() {
	
	regular_shift();
	constexpr_shift();
	return 0;
}
