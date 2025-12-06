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

template<typename value_type>
struct test_struct_no_pause {
	BNCH_SWT_HOST static uint64_t impl([[maybe_unused]] value_type& values_01) {
		[[maybe_unused]] auto start = bnch_swt::clock_type::now();
		[[maybe_unused]] auto end	= bnch_swt::clock_type::now();
		bnch_swt::do_not_optimize_away(values_01);
		return 200000ull;
	}
};

template<typename value_type> struct test_struct_pause {
	BNCH_SWT_HOST static uint64_t impl([[maybe_unused]] value_type& values_01) {
		[[maybe_unused]] auto start = bnch_swt::clock_type::now();
		[[maybe_unused]] auto end	= bnch_swt::clock_type::now();
		bnch_swt::do_not_optimize_away(values_01);
		return 200000ull;
	}
};

int main() {
	std::vector<double> doubles{};
	std::vector<float> floats{};
	std::vector<int64_t> int64_ts{};
	std::vector<uint64_t> uint64_ts{};
	std::vector<int32_t> int32_ts{};
	std::vector<uint32_t> uint32_ts{};
	std::vector<int16_t> int16_ts{};
	std::vector<uint16_t> uint16_ts{};
	std::vector<int8_t> int8_ts{};
	std::vector<uint8_t> uint8_ts{};
	std::vector<std::string> strings{};
	std::vector<bool> bools{};
	for (uint64_t x = 0; x < 1024; ++x) {
		doubles.emplace_back(bnch_swt::random_generator<double>::impl());
		floats.emplace_back(bnch_swt::random_generator<float>::impl());
		uint64_ts.emplace_back(bnch_swt::random_generator<uint64_t>::impl());
		int64_ts.emplace_back(bnch_swt::random_generator<int64_t>::impl());
		uint32_ts.emplace_back(bnch_swt::random_generator<uint32_t>::impl());
		int32_ts.emplace_back(bnch_swt::random_generator<int32_t>::impl());
		uint16_ts.emplace_back(bnch_swt::random_generator<uint16_t>::impl());
		int16_ts.emplace_back(bnch_swt::random_generator<int16_t>::impl());
		uint8_ts.emplace_back(bnch_swt::random_generator<uint8_t>::impl());
		int8_ts.emplace_back(bnch_swt::random_generator<int8_t>::impl());
		bools.emplace_back(bnch_swt::random_generator<bool>::impl());
		strings.emplace_back(bnch_swt::random_generator<std::string>::impl(24));
	}

	bnch_swt::benchmark_stage<"test_stage", total_iteration_count, measured_iterations>::run_benchmark<"no-yield-double", test_struct_no_pause<std::vector<double>>>(doubles);
	bnch_swt::benchmark_stage<"test_stage", total_iteration_count, measured_iterations>::run_benchmark<"yield-double", test_struct_pause<std::vector<double>>>(doubles);
	bnch_swt::benchmark_stage<"test_stage", total_iteration_count, measured_iterations>::run_benchmark<"no-yield-float", test_struct_no_pause<std::vector<float>>>(floats);
	bnch_swt::benchmark_stage<"test_stage", total_iteration_count, measured_iterations>::run_benchmark<"yield-float", test_struct_pause<std::vector<float>>>(floats);
	bnch_swt::benchmark_stage<"test_stage", total_iteration_count, measured_iterations>::run_benchmark<"no-yield-int64_t", test_struct_no_pause<std::vector<int64_t>>>(int64_ts);
	bnch_swt::benchmark_stage<"test_stage", total_iteration_count, measured_iterations>::run_benchmark<"yield-int64_t", test_struct_pause<std::vector<int64_t>>>(int64_ts);
	bnch_swt::benchmark_stage<"test_stage", total_iteration_count, measured_iterations>::run_benchmark<"no-yield-uint64_t", test_struct_no_pause<std::vector<uint64_t>>>(uint64_ts);
	bnch_swt::benchmark_stage<"test_stage", total_iteration_count, measured_iterations>::run_benchmark<"yield-uint64_t", test_struct_pause<std::vector<uint64_t>>>(uint64_ts);
	bnch_swt::benchmark_stage<"test_stage", total_iteration_count, measured_iterations>::run_benchmark<"no-yield-int32_t", test_struct_no_pause<std::vector<int32_t>>>(int32_ts);
	bnch_swt::benchmark_stage<"test_stage", total_iteration_count, measured_iterations>::run_benchmark<"yield-int32_t", test_struct_pause<std::vector<int32_t>>>(int32_ts);
	bnch_swt::benchmark_stage<"test_stage", total_iteration_count, measured_iterations>::run_benchmark<"no-yield-uint32_t", test_struct_no_pause<std::vector<uint32_t>>>(uint32_ts);
	bnch_swt::benchmark_stage<"test_stage", total_iteration_count, measured_iterations>::run_benchmark<"yield-uint32_t", test_struct_pause<std::vector<uint32_t>>>(uint32_ts);
	bnch_swt::benchmark_stage<"test_stage", total_iteration_count, measured_iterations>::run_benchmark<"no-yield-int16_t", test_struct_no_pause<std::vector<int16_t>>>(int16_ts);
	bnch_swt::benchmark_stage<"test_stage", total_iteration_count, measured_iterations>::run_benchmark<"yield-int16_t", test_struct_pause<std::vector<int16_t>>>(int16_ts);
	bnch_swt::benchmark_stage<"test_stage", total_iteration_count, measured_iterations>::run_benchmark<"no-yield-uint16_t", test_struct_no_pause<std::vector<uint16_t>>>(uint16_ts);
	bnch_swt::benchmark_stage<"test_stage", total_iteration_count, measured_iterations>::run_benchmark<"yield-uint16_t", test_struct_pause<std::vector<uint16_t>>>(uint16_ts);
	bnch_swt::benchmark_stage<"test_stage", total_iteration_count, measured_iterations>::run_benchmark<"no-yield-int8_t", test_struct_no_pause<std::vector<int8_t>>>(int8_ts);
	bnch_swt::benchmark_stage<"test_stage", total_iteration_count, measured_iterations>::run_benchmark<"yield-int8_t", test_struct_pause<std::vector<int8_t>>>(int8_ts);
	bnch_swt::benchmark_stage<"test_stage", total_iteration_count, measured_iterations>::run_benchmark<"no-yield-uint8_t", test_struct_no_pause<std::vector<uint8_t>>>(uint8_ts);
	bnch_swt::benchmark_stage<"test_stage", total_iteration_count, measured_iterations>::run_benchmark<"yield-uint8_t", test_struct_pause<std::vector<uint8_t>>>(uint8_ts);
	bnch_swt::benchmark_stage<"test_stage", total_iteration_count, measured_iterations>::run_benchmark<"no-yield-bool", test_struct_no_pause<std::vector<bool>>>(bools);
	bnch_swt::benchmark_stage<"test_stage", total_iteration_count, measured_iterations>::run_benchmark<"yield-bool", test_struct_pause<std::vector<bool>>>(bools);
	bnch_swt::benchmark_stage<"test_stage", total_iteration_count, measured_iterations>::run_benchmark<"no-yield-std::string", test_struct_no_pause<std::vector<std::string>>>(strings);
	bnch_swt::benchmark_stage<"test_stage", total_iteration_count, measured_iterations>::run_benchmark<"yield-std::string", test_struct_pause<std::vector<std::string>>>(strings);

	bnch_swt::benchmark_stage<"test_stage", total_iteration_count, measured_iterations>::print_results();
	return 0;
}

