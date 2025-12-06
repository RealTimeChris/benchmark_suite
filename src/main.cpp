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

static constexpr uint64_t total_iteration_count{ 10 };
static constexpr uint64_t measured_iterations{ 10 };

template<typename value_type> struct test_struct_no_pause {
	BNCH_SWT_HOST static uint64_t impl([[maybe_unused]] value_type& values_01) {
		[[maybe_unused]] auto start = bnch_swt::clock_type::now();
		[[maybe_unused]] auto end	= bnch_swt::clock_type::now();
		while ((end - start).count() < 10000) {
			end = bnch_swt::clock_type::now();
		}
		values_01[0] += values_01[2];
		bnch_swt::do_not_optimize_away(values_01);
		return 200000ull;
	}
};

template<typename value_type> struct test_struct_pause {
	BNCH_SWT_HOST static uint64_t impl([[maybe_unused]] value_type& values_01) {
		[[maybe_unused]] auto start = bnch_swt::clock_type::now();
		[[maybe_unused]] auto end	= bnch_swt::clock_type::now();
		while ((end - start).count() < 10000) {
			end = bnch_swt::clock_type::now();
		}
		values_01[0] += values_01[2];
		bnch_swt::do_not_optimize_away(values_01);
		return 200000ull;
	}
};

int main() {
	using bench_type = bnch_swt::benchmark_stage<"test_stage", total_iteration_count, measured_iterations, bnch_swt::benchmark_types::cpu, false>;
	std::vector<double> doubles{};
	for (uint64_t x = 0; x < 1024; ++x) {
		doubles.emplace_back(bnch_swt::random_generator<double>::impl());
	}

	bench_type::run_benchmark<"no-yield-std::string", test_struct_no_pause<std::vector<double>>>(doubles);
	bench_type::run_benchmark<"yield-std::string", test_struct_pause<std::vector<double>>>(doubles);

	bench_type::print_results();
	return 0;
}
