#include <bnch_swt/index.hpp>
#include <random>

struct pair {
	char val01{};
	char val02{};
};

template<typename value_type>
concept uns64_t = std::is_integral_v<value_type> && std::unsigned_integral<value_type>;

template<typename value_type>
concept sig64_t = std::is_integral_v<value_type> && std::signed_integral<value_type>;

template<typename typeName> struct int_tables {
	inline static constexpr char charTable00[]{ 0x30u, 0x31u, 0x32u, 0x33u, 0x34u, 0x35u, 0x36u, 0x37u, 0x38u, 0x39u };

	inline static constexpr char charTable01[]{ 0x30, 0x30, 0x30, 0x31, 0x30, 0x32, 0x30, 0x33, 0x30, 0x34, 0x30, 0x35, 0x30, 0x36, 0x30, 0x37, 0x30, 0x38, 0x30, 0x39, 0x31, 0x30,
		0x31, 0x31, 0x31, 0x32, 0x31, 0x33, 0x31, 0x34, 0x31, 0x35, 0x31, 0x36, 0x31, 0x37, 0x31, 0x38, 0x31, 0x39, 0x32, 0x30, 0x32, 0x31, 0x32, 0x32, 0x32, 0x33, 0x32, 0x34,
		0x32, 0x35, 0x32, 0x36, 0x32, 0x37, 0x32, 0x38, 0x32, 0x39, 0x33, 0x30, 0x33, 0x31, 0x33, 0x32, 0x33, 0x33, 0x33, 0x34, 0x33, 0x35, 0x33, 0x36, 0x33, 0x37, 0x33, 0x38,
		0x33, 0x39, 0x34, 0x30, 0x34, 0x31, 0x34, 0x32, 0x34, 0x33, 0x34, 0x34, 0x34, 0x35, 0x34, 0x36, 0x34, 0x37, 0x34, 0x38, 0x34, 0x39, 0x35, 0x30, 0x35, 0x31, 0x35, 0x32,
		0x35, 0x33, 0x35, 0x34, 0x35, 0x35, 0x35, 0x36, 0x35, 0x37, 0x35, 0x38, 0x35, 0x39, 0x36, 0x30, 0x36, 0x31, 0x36, 0x32, 0x36, 0x33, 0x36, 0x34, 0x36, 0x35, 0x36, 0x36,
		0x36, 0x37, 0x36, 0x38, 0x36, 0x39, 0x37, 0x30, 0x37, 0x31, 0x37, 0x32, 0x37, 0x33, 0x37, 0x34, 0x37, 0x35, 0x37, 0x36, 0x37, 0x37, 0x37, 0x38, 0x37, 0x39, 0x38, 0x30,
		0x38, 0x31, 0x38, 0x32, 0x38, 0x33, 0x38, 0x34, 0x38, 0x35, 0x38, 0x36, 0x38, 0x37, 0x38, 0x38, 0x38, 0x39, 0x39, 0x30, 0x39, 0x31, 0x39, 0x32, 0x39, 0x33, 0x39, 0x34,
		0x39, 0x35, 0x39, 0x36, 0x39, 0x37, 0x39, 0x38, 0x39, 0x39 };

	inline static constexpr uint16_t charTable02[]{ 0x3030, 0x3130, 0x3230, 0x3330, 0x3430, 0x3530, 0x3630, 0x3730, 0x3830, 0x3930, 0x3031, 0x3131, 0x3231, 0x3331, 0x3431, 0x3531,
		0x3631, 0x3731, 0x3831, 0x3931, 0x3032, 0x3132, 0x3232, 0x3332, 0x3432, 0x3532, 0x3632, 0x3732, 0x3832, 0x3932, 0x3033, 0x3133, 0x3233, 0x3333, 0x3433, 0x3533, 0x3633,
		0x3733, 0x3833, 0x3933, 0x3034, 0x3134, 0x3234, 0x3334, 0x3434, 0x3534, 0x3634, 0x3734, 0x3834, 0x3934, 0x3035, 0x3135, 0x3235, 0x3335, 0x3435, 0x3535, 0x3635, 0x3735,
		0x3835, 0x3935, 0x3036, 0x3136, 0x3236, 0x3336, 0x3436, 0x3536, 0x3636, 0x3736, 0x3836, 0x3936, 0x3037, 0x3137, 0x3237, 0x3337, 0x3437, 0x3537, 0x3637, 0x3737, 0x3837,
		0x3937, 0x3038, 0x3138, 0x3238, 0x3338, 0x3438, 0x3538, 0x3638, 0x3738, 0x3838, 0x3938, 0x3039, 0x3139, 0x3239, 0x3339, 0x3439, 0x3539, 0x3639, 0x3739, 0x3839, 0x3939 };

	inline static constexpr uint8_t decTrailingZeroTable[]{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 0 };

	inline static constexpr uint8_t digitCounts[]{ 19, 19, 19, 19, 18, 18, 18, 17, 17, 17, 16, 16, 16, 16, 15, 15, 15, 14, 14, 14, 13, 13, 13, 13, 12, 12, 12, 11, 11, 11, 10, 10,
		10, 10, 9, 9, 9, 8, 8, 8, 7, 7, 7, 7, 6, 6, 6, 5, 5, 5, 4, 4, 4, 4, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1 };

	inline static constexpr uint64_t digitCountThresholds[]{ 0ULL, 9ULL, 99ULL, 999ULL, 9999ULL, 99999ULL, 999999ULL, 9999999ULL, 99999999ULL, 999999999ULL, 9999999999ULL,
		99999999999ULL, 999999999999ULL, 9999999999999ULL, 99999999999999ULL, 999999999999999ULL, 9999999999999999ULL, 99999999999999999ULL, 999999999999999999ULL,
		9999999999999999999ULL };
};

BNCH_SWT_HOST static uint64_t fastDigitCount(const uint64_t inputValue) {
	const uint64_t originalDigitCount{ int_tables<void>::digitCounts[std::countl_zero(inputValue)] };
	return originalDigitCount + static_cast<uint64_t>(inputValue > int_tables<void>::digitCountThresholds[originalDigitCount]);
}

template<uint64_t divisor, uint64_t multiplier, uint32_t shift> struct multiply_and_shift {
	template<typename value_type> BNCH_SWT_HOST static uint64_t impl(value_type value) noexcept {
#if BNCH_SWT_COMPILER_CLANG
		return value / divisor;
#else
	#if defined(__SIZEOF_INT128__)
		const __int128_t product = static_cast<__int128_t>(value) * multiplier;
		return static_cast<uint64_t>(product >> shift);
	#elif defined(_M_ARM64) && !defined(__MINGW32__)
		value_type high_part{ __umulh(value, multiplier) };
		value = value * multiplier;
		if constexpr (shift < 64) {
		} else {
			return static_cast<uint64_t>(high_part >> (shift - 64ULL));
		}
		value_type values;
		values = __umulh(value, multiplier);
		value  = value * multiplier;
		return values == 0;
	#elif (defined(_WIN64) && !defined(__clang__))
		uint64_t high_part;
		const uint64_t low_part = _umul128(value, multiplier, &high_part);
		if constexpr (shift < 64) {
			return static_cast<uint64_t>((low_part >> shift) | (high_part << (64ULL - shift)));
		} else {
			return static_cast<uint64_t>(high_part >> (shift - 64ULL));
		}
	#else
		uint64_t high_part;
		const uint64_t low_part = mul128Generic(value, multiplier, &high_part);
		if constexpr (shift < 64) {
			return static_cast<uint64_t>((low_part >> shift) | (high_part << (64ULL - shift)));
		} else {
			return static_cast<uint64_t>(high_part >> (shift - 64ULL));
		}
	#endif
#endif
	}
};

template<typename value_type> BNCH_SWT_HOST static char* toChars1(char* buf, const value_type value) noexcept {
	buf[0] = int_tables<void>::charTable00[value];
	return buf + 1ULL;
}

template<typename value_type> BNCH_SWT_HOST static char* toChars2(char* buf, const value_type value) noexcept {
	std::memcpy(buf, int_tables<void>::charTable02 + value, 2ULL);
	return buf + 2ULL;
}

template<typename value_type> BNCH_SWT_HOST static char* toChars3(char* buf, const value_type value) noexcept {
	const uint32_t aa = (value * 5243u) >> 19ULL;
	buf[0]			  = int_tables<void>::charTable00[aa];
	std::memcpy(buf + 1ULL, int_tables<void>::charTable02 + (value - aa * 100u), 2ULL);
	return buf + 3ULL;
}

template<typename value_type> BNCH_SWT_HOST static char* toChars4(char* buf, const value_type value) noexcept {
	const uint32_t aa = (value * 5243u) >> 19ULL;
	std::memcpy(buf, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 2ULL, int_tables<void>::charTable02 + (value - aa * 100u), 2ULL);
	return buf + 4ULL;
}

template<typename value_type> BNCH_SWT_HOST static char* toChars5(char* buf, const value_type value) noexcept {
	uint32_t aa		  = static_cast<uint32_t>((value * 429497ULL) >> 32ULL);
	buf[0]			  = int_tables<void>::charTable00[aa];
	aa				  = value - aa * 10000u;
	const uint32_t bb = (aa * 5243u) >> 19ULL;
	std::memcpy(buf + 1ULL, int_tables<void>::charTable02 + bb, 2ULL);
	std::memcpy(buf + 3ULL, int_tables<void>::charTable02 + (aa - bb * 100u), 2ULL);
	return buf + 5ULL;
}

template<typename value_type> BNCH_SWT_HOST static char* toChars6(char* buf, const value_type value) noexcept {
	uint32_t aa = static_cast<uint32_t>((value * 429497ULL) >> 32ULL);
	std::memcpy(buf, int_tables<void>::charTable02 + aa, 2ULL);
	aa				  = value - aa * 10000u;
	const uint32_t bb = (aa * 5243u) >> 19ULL;
	std::memcpy(buf + 2ULL, int_tables<void>::charTable02 + bb, 2ULL);
	std::memcpy(buf + 4ULL, int_tables<void>::charTable02 + (aa - bb * 100u), 2ULL);
	return buf + 6ULL;
}

template<typename value_type> BNCH_SWT_HOST static char* toChars7(char* buf, const value_type value) noexcept {
	uint32_t aabb = static_cast<uint32_t>((value * 109951163ULL) >> 40ULL);
	uint32_t aa	  = (aabb * 5243u) >> 19ULL;
	buf[0]		  = int_tables<void>::charTable00[aa];
	std::memcpy(buf + 1ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	aabb = value - aabb * 10000u;
	aa	 = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 3ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 5ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	return buf + 7ULL;
}

template<typename value_type> BNCH_SWT_HOST static char* toChars8(char* buf, const value_type value) noexcept {
	uint32_t aabb = static_cast<uint32_t>((value * 109951163ULL) >> 40ULL);
	uint32_t aa	  = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 2ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	aabb = value - aabb * 10000u;
	aa	 = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 4ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 6ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	return buf + 8ULL;
}

template<typename value_type> BNCH_SWT_HOST static char* toChars9(char* buf, const value_type value) noexcept {
	uint32_t high = static_cast<uint32_t>((value * 720575941ULL) >> 56ULL);
	buf[0]		  = int_tables<void>::charTable00[high];
	high		  = value - high * 100000000u;
	uint32_t aabb = static_cast<uint32_t>((high * 109951163ULL) >> 40ULL);
	uint32_t aa	  = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 1ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 3ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	aabb = high - aabb * 10000u;
	aa	 = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 5ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 7ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	return buf + 9ULL;
}

template<typename value_type> BNCH_SWT_HOST static char* toChars10(char* buf, const value_type value) noexcept {
	const uint32_t high = static_cast<uint32_t>((value * 1801439851ULL) >> 54ULL);
	const uint32_t low	= static_cast<uint32_t>(value - high * 10000000ULL);
	uint32_t aa			= (high * 5243u) >> 19ULL;
	buf[0]				= int_tables<void>::charTable00[aa];
	std::memcpy(buf + 1ULL, int_tables<void>::charTable02 + (high - aa * 100u), 2ULL);
	uint32_t aabb = static_cast<uint32_t>((low * 109951163ULL) >> 40ULL);
	aa			  = (aabb * 5243u) >> 19ULL;
	buf[3]		  = int_tables<void>::charTable00[aa];
	std::memcpy(buf + 4ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	aabb = low - aabb * 10000u;
	aa	 = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 6ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 8ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	return buf + 10;
}

template<typename value_type> BNCH_SWT_HOST static char* toChars11(char* buf, const value_type value) noexcept {
	const uint64_t high = multiply_and_shift<10000000ULL, 15474250491067253437ULL, 87>::impl(value);
	const uint32_t low	= static_cast<uint32_t>(value - high * 10000000ULL);
	uint32_t aa			= (high * 5243u) >> 19ULL;
	std::memcpy(buf, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 2ULL, int_tables<void>::charTable02 + (high - aa * 100u), 2ULL);
	uint32_t aabb = static_cast<uint32_t>((low * 109951163ULL) >> 40ULL);
	aa			  = (aabb * 5243u) >> 19ULL;
	buf[4]		  = int_tables<void>::charTable00[aa];
	std::memcpy(buf + 5ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	aabb = low - aabb * 10000u;
	aa	 = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 7ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 9ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	return buf + 11;
}

template<typename value_type> BNCH_SWT_HOST static char* toChars12(char* buf, const value_type value) noexcept {
	const uint64_t high = multiply_and_shift<100000000ULL, 6189700196426901375ULL, 89>::impl(value);
	const uint64_t low	= static_cast<uint64_t>(value - high * 100000000ULL);
	uint64_t aa			= (high * 5243u) >> 19ULL;
	std::memcpy(buf, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 2ULL, int_tables<void>::charTable02 + (high - aa * 100u), 2ULL);
	uint64_t aabb = static_cast<uint64_t>((low * 109951163ULL) >> 40ULL);
	aa			  = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 4ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 6ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	aabb = low - aabb * 10000u;
	aa	 = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 8ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 10ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	return buf + 12;
}

template<typename value_type> BNCH_SWT_HOST static char* toChars13(char* buf, const value_type value) noexcept {
	const uint64_t high = multiply_and_shift<100000000ULL, 6189700196426901375ULL, 89>::impl(value);
	const uint32_t low	= static_cast<uint32_t>(value - high * 100000000ULL);
	uint32_t aa			= static_cast<uint32_t>((high * 429497ULL) >> 32ULL);
	const uint32_t bbcc = high - aa * 10000u;
	const uint32_t bb	= (bbcc * 5243u) >> 19ULL;
	uint32_t cc			= bbcc - bb * 100u;
	buf[0]				= int_tables<void>::charTable00[aa];
	std::memcpy(buf + 1ULL, int_tables<void>::charTable02 + bb, 2ULL);
	std::memcpy(buf + 3ULL, int_tables<void>::charTable02 + cc, 2ULL);
	const uint32_t aabb = static_cast<uint32_t>((low * 109951163ULL) >> 40ULL);
	const uint32_t ccdd = low - aabb * 10000u;
	aa					= (aabb * 5243u) >> 19ULL;
	cc					= (ccdd * 5243u) >> 19ULL;
	std::memcpy(buf + 5ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 7ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	std::memcpy(buf + 9ULL, int_tables<void>::charTable02 + cc, 2ULL);
	std::memcpy(buf + 11ULL, int_tables<void>::charTable02 + (ccdd - cc * 100u), 2ULL);
	return buf + 13ULL;
}

template<typename value_type> BNCH_SWT_HOST static char* toChars14(char* buf, const value_type value) noexcept {
	const uint64_t high = multiply_and_shift<100000000ULL, 6189700196426901375ULL, 89>::impl(value);
	const uint32_t low	= static_cast<uint32_t>(value - high * 100000000ULL);
	uint32_t aa			= static_cast<uint32_t>((high * 429497ULL) >> 32ULL);
	const uint32_t bbcc = high - aa * 10000u;
	const uint32_t bb	= (bbcc * 5243u) >> 19ULL;
	uint32_t cc			= bbcc - bb * 100u;
	std::memcpy(buf, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 2ULL, int_tables<void>::charTable02 + bb, 2ULL);
	std::memcpy(buf + 4ULL, int_tables<void>::charTable02 + cc, 2ULL);
	const uint32_t aabb = static_cast<uint32_t>((low * 109951163ULL) >> 40ULL);
	const uint32_t ccdd = low - aabb * 10000u;
	aa					= (aabb * 5243u) >> 19ULL;
	cc					= (ccdd * 5243u) >> 19ULL;
	std::memcpy(buf + 6ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 8ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	std::memcpy(buf + 10ULL, int_tables<void>::charTable02 + cc, 2ULL);
	std::memcpy(buf + 12ULL, int_tables<void>::charTable02 + (ccdd - cc * 100u), 2ULL);
	return buf + 14ULL;
}

template<typename value_type> BNCH_SWT_HOST static char* toChars15(char* buf, const value_type value) noexcept {
	const uint64_t high = multiply_and_shift<100000000ULL, 6189700196426901375ULL, 89>::impl(value);
	const uint32_t low	= static_cast<uint32_t>(value - high * 100000000ULL);
	uint32_t aabb		= static_cast<uint32_t>((high * 109951163ULL) >> 40ULL);
	uint32_t ccdd		= static_cast<uint32_t>(high - aabb * 10000u);
	uint32_t aa			= (aabb * 5243u) >> 19ULL;
	uint32_t cc			= (ccdd * 5243u) >> 19ULL;
	const uint32_t bb	= aabb - aa * 100u;
	const uint32_t dd	= ccdd - cc * 100u;
	buf[0]				= int_tables<void>::charTable00[aa];
	std::memcpy(buf + 1ULL, int_tables<void>::charTable02 + bb, 2ULL);
	std::memcpy(buf + 3ULL, int_tables<void>::charTable02 + cc, 2ULL);
	std::memcpy(buf + 5ULL, int_tables<void>::charTable02 + dd, 2ULL);
	aabb = static_cast<uint32_t>((low * 109951163ULL) >> 40ULL);
	ccdd = low - aabb * 10000u;
	aa	 = (aabb * 5243u) >> 19ULL;
	cc	 = (ccdd * 5243u) >> 19ULL;
	std::memcpy(buf + 7ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 9ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	std::memcpy(buf + 11ULL, int_tables<void>::charTable02 + cc, 2ULL);
	std::memcpy(buf + 13ULL, int_tables<void>::charTable02 + (ccdd - cc * 100u), 2ULL);
	return buf + 15ULL;
}

template<typename value_type> BNCH_SWT_HOST static char* toChars16(char* buf, const value_type value) noexcept {
	const uint64_t high = multiply_and_shift<100000000ULL, 6189700196426901375ULL, 89>::impl(value);
	const uint32_t low	= static_cast<uint32_t>(value - high * 100000000ULL);
	uint32_t aabb		= static_cast<uint32_t>((high * 109951163ULL) >> 40ULL);
	uint32_t ccdd		= static_cast<uint32_t>(high - aabb * 10000u);
	uint32_t aa			= (aabb * 5243u) >> 19ULL;
	uint32_t cc			= (ccdd * 5243u) >> 19ULL;
	const uint32_t bb	= aabb - aa * 100u;
	const uint32_t dd	= ccdd - cc * 100u;
	std::memcpy(buf, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 2ULL, int_tables<void>::charTable02 + bb, 2ULL);
	std::memcpy(buf + 4ULL, int_tables<void>::charTable02 + cc, 2ULL);
	std::memcpy(buf + 6ULL, int_tables<void>::charTable02 + dd, 2ULL);
	aabb = static_cast<uint32_t>((low * 109951163ULL) >> 40ULL);
	ccdd = low - aabb * 10000u;
	aa	 = (aabb * 5243u) >> 19ULL;
	cc	 = (ccdd * 5243u) >> 19ULL;
	std::memcpy(buf + 8ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 10ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	std::memcpy(buf + 12ULL, int_tables<void>::charTable02 + cc, 2ULL);
	std::memcpy(buf + 14ULL, int_tables<void>::charTable02 + (ccdd - cc * 100u), 2ULL);
	return buf + 16ULL;
}

template<typename value_type> BNCH_SWT_HOST static char* toChars17(char* buf, const value_type value) noexcept {
	const uint64_t high	 = multiply_and_shift<100000000ULL, 6189700196426901375ULL, 89>::impl(value);
	const uint64_t low	 = value - high * 100000000ULL;
	const uint64_t high9 = (high * 720575941ULL) >> 56ULL;
	const uint64_t low9	 = high - high9 * 100000000ULL;
	buf[0]				 = int_tables<void>::charTable00[high9];
	uint64_t aabb		 = (low9 * 109951163ULL) >> 40ULL;
	uint64_t aa			 = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 1ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 3ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	aabb = low9 - aabb * 10000u;
	aa	 = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 5ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 7ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	aabb = (low * 109951163ULL) >> 40ULL;
	aa	 = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 9ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 11ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	aabb = low - aabb * 10000u;
	aa	 = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 13ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 15ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	return buf + 17;
}

template<typename value_type> BNCH_SWT_HOST static char* toChars18(char* buf, const value_type value) noexcept {
	const uint64_t high	  = multiply_and_shift<100000000ULL, 6189700196426901375ULL, 89>::impl(value);
	const uint64_t low	  = value - high * 100000000ULL;
	const uint64_t high10 = (high * 1801439851ULL) >> 54;
	const uint64_t low10  = high - high10 * 10000000ULL;
	uint64_t aa			  = (high10 * 5243u) >> 19ULL;
	buf[0]				  = int_tables<void>::charTable00[aa];
	std::memcpy(buf + 1ULL, int_tables<void>::charTable02 + (high10 - aa * 100u), 2ULL);
	uint64_t aabb = (low10 * 109951163ULL) >> 40ULL;
	aa			  = (aabb * 5243u) >> 19ULL;
	buf[3]		  = int_tables<void>::charTable00[aa];
	std::memcpy(buf + 4ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	aabb = low10 - aabb * 10000u;
	aa	 = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 6ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 8ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	aabb = (low * 109951163ULL) >> 40ULL;
	aa	 = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 10ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 12ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	aabb = low - aabb * 10000u;
	aa	 = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 14ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 16ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	return buf + 18;
}

template<typename value_type> BNCH_SWT_HOST static char* toChars19(char* buf, const value_type value) noexcept {
	const uint64_t high	  = multiply_and_shift<100000000ULL, 6189700196426901375ULL, 89>::impl(value);
	const uint64_t low	  = value - high * 100000000ULL;
	const uint64_t high11 = multiply_and_shift<10000000ULL, 15474250491067253437ULL, 87>::impl(high);
	const uint64_t low11  = high - high11 * 10000000ULL;
	uint64_t aa			  = (high11 * 5243u) >> 19ULL;
	std::memcpy(buf, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 2ULL, int_tables<void>::charTable02 + (high11 - aa * 100u), 2ULL);
	uint64_t aabb = (low11 * 109951163ULL) >> 40ULL;
	aa			  = (aabb * 5243u) >> 19ULL;
	buf[4]		  = int_tables<void>::charTable00[aa];
	std::memcpy(buf + 5ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	aabb = low11 - aabb * 10000u;
	aa	 = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 7ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 9ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	aabb = (low * 109951163ULL) >> 40ULL;
	aa	 = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 11ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 13ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	aabb = low - aabb * 10000u;
	aa	 = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 15ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 17ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	return buf + 19;
}

template<typename value_type> BNCH_SWT_HOST static char* toChars20(char* buf, const value_type value) noexcept {
	const uint64_t high	  = multiply_and_shift<100000000ULL, 6189700196426901375ULL, 89>::impl(value);
	const uint64_t low	  = value - high * 100000000ULL;
	const uint64_t high12 = multiply_and_shift<100000000ULL, 6189700196426901375ULL, 89>::impl(high);
	const uint64_t low12  = high - high12 * 100000000ULL;
	uint64_t aa			  = (high12 * 5243u) >> 19ULL;
	std::memcpy(buf, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 2ULL, int_tables<void>::charTable02 + (high12 - aa * 100u), 2ULL);
	uint64_t aabb = (low12 * 109951163ULL) >> 40ULL;
	aa			  = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 4ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 6ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	aabb = low12 - aabb * 10000u;
	aa	 = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 8ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 10ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	aabb = (low * 109951163ULL) >> 40ULL;
	aa	 = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 12ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 14ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	aabb = low - aabb * 10000u;
	aa	 = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 16ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 18ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	return buf + 20;
}

template<uns64_t value_type> BNCH_SWT_HOST char* toChars(char* buf, const value_type value) noexcept {
	switch (fastDigitCount(value)) {
		case 20: {
			return toChars20(buf, value);
		}
		case 19: {
			return toChars19(buf, value);
		}
		case 18: {
			return toChars18(buf, value);
		}
		case 17: {
			return toChars17(buf, value);
		}
		case 16: {
			return toChars16(buf, value);
		}
		case 15: {
			return toChars15(buf, value);
		}
		case 14: {
			return toChars14(buf, value);
		}
		case 13: {
			return toChars13(buf, value);
		}
		case 12: {
			return toChars12(buf, value);
		}
		case 11: {
			return toChars11(buf, value);
		}
		case 10: {
			return toChars10(buf, value);
		}
		case 9: {
			return toChars9(buf, static_cast<uint32_t>(value));
		}
		case 8: {
			return toChars8(buf, static_cast<uint32_t>(value));
		}
		case 7: {
			return toChars7(buf, static_cast<uint32_t>(value));
		}
		case 6: {
			return toChars6(buf, static_cast<uint32_t>(value));
		}
		case 5: {
			return toChars5(buf, static_cast<uint32_t>(value));
		}
		case 4: {
			return toChars4(buf, static_cast<uint32_t>(value));
		}
		case 3: {
			return toChars3(buf, static_cast<uint32_t>(value));
		}
		case 2: {
			return toChars2(buf, static_cast<uint32_t>(value));
		}
		default: {
			return toChars1(buf, static_cast<uint32_t>(value));
		}
	}
}

template<sig64_t value_type> BNCH_SWT_HOST static char* toChars(char* buf, const value_type value) noexcept {
	*buf = '-';
	return toChars(buf + (value < 0), static_cast<uint64_t>(value ^ (value >> 63ULL)) - (value >> 63ULL));
}

template<typename value_type> BNCH_SWT_HOST static char* toChars11Old(char* buf, const value_type value) noexcept {
	const uint64_t high = value / 10000000ULL;
	const uint32_t low	= static_cast<uint32_t>(value - high * 10000000ULL);
	uint32_t aa			= (high * 5243u) >> 19ULL;
	std::memcpy(buf, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 2ULL, int_tables<void>::charTable02 + (high - aa * 100u), 2ULL);
	uint32_t aabb = static_cast<uint32_t>((low * 109951163ULL) >> 40ULL);
	aa			  = (aabb * 5243u) >> 19ULL;
	buf[4]		  = int_tables<void>::charTable00[aa];
	std::memcpy(buf + 5ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	aabb = low - aabb * 10000u;
	aa	 = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 7ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 9ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	return buf + 11;
}

template<typename value_type> BNCH_SWT_HOST static char* toChars12Old(char* buf, const value_type value) noexcept {
	const uint64_t high = value / 100000000ULL;
	const uint64_t low	= static_cast<uint64_t>(value - high * 100000000ULL);
	uint64_t aa			= (high * 5243u) >> 19ULL;
	std::memcpy(buf, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 2ULL, int_tables<void>::charTable02 + (high - aa * 100u), 2ULL);
	uint64_t aabb = static_cast<uint64_t>((low * 109951163ULL) >> 40ULL);
	aa			  = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 4ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 6ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	aabb = low - aabb * 10000u;
	aa	 = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 8ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 10ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	return buf + 12;
}

template<typename value_type> BNCH_SWT_HOST static char* toChars13Old(char* buf, const value_type value) noexcept {
	const uint64_t high = value / 100000000ULL;
	const uint32_t low	= static_cast<uint32_t>(value - high * 100000000ULL);
	uint32_t aa			= static_cast<uint32_t>((high * 429497ULL) >> 32ULL);
	const uint32_t bbcc = high - aa * 10000u;
	const uint32_t bb	= (bbcc * 5243u) >> 19ULL;
	uint32_t cc			= bbcc - bb * 100u;
	buf[0]				= int_tables<void>::charTable00[aa];
	std::memcpy(buf + 1ULL, int_tables<void>::charTable02 + bb, 2ULL);
	std::memcpy(buf + 3ULL, int_tables<void>::charTable02 + cc, 2ULL);
	const uint32_t aabb = static_cast<uint32_t>((low * 109951163ULL) >> 40ULL);
	const uint32_t ccdd = low - aabb * 10000u;
	aa					= (aabb * 5243u) >> 19ULL;
	cc					= (ccdd * 5243u) >> 19ULL;
	std::memcpy(buf + 5ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 7ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	std::memcpy(buf + 9ULL, int_tables<void>::charTable02 + cc, 2ULL);
	std::memcpy(buf + 11ULL, int_tables<void>::charTable02 + (ccdd - cc * 100u), 2ULL);
	return buf + 13ULL;
}

template<typename value_type> BNCH_SWT_HOST static char* toChars14Old(char* buf, const value_type value) noexcept {
	const uint64_t high = value / 100000000ULL;
	const uint32_t low	= static_cast<uint32_t>(value - high * 100000000ULL);
	uint32_t aa			= static_cast<uint32_t>((high * 429497ULL) >> 32ULL);
	const uint32_t bbcc = high - aa * 10000u;
	const uint32_t bb	= (bbcc * 5243u) >> 19ULL;
	uint32_t cc			= bbcc - bb * 100u;
	std::memcpy(buf, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 2ULL, int_tables<void>::charTable02 + bb, 2ULL);
	std::memcpy(buf + 4ULL, int_tables<void>::charTable02 + cc, 2ULL);
	const uint32_t aabb = static_cast<uint32_t>((low * 109951163ULL) >> 40ULL);
	const uint32_t ccdd = low - aabb * 10000u;
	aa					= (aabb * 5243u) >> 19ULL;
	cc					= (ccdd * 5243u) >> 19ULL;
	std::memcpy(buf + 6ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 8ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	std::memcpy(buf + 10ULL, int_tables<void>::charTable02 + cc, 2ULL);
	std::memcpy(buf + 12ULL, int_tables<void>::charTable02 + (ccdd - cc * 100u), 2ULL);
	return buf + 14ULL;
}

template<typename value_type> BNCH_SWT_HOST static char* toChars15Old(char* buf, const value_type value) noexcept {
	const uint64_t high = value / 100000000ULL;
	const uint32_t low	= static_cast<uint32_t>(value - high * 100000000ULL);
	uint32_t aabb		= static_cast<uint32_t>((high * 109951163ULL) >> 40ULL);
	uint32_t ccdd		= static_cast<uint32_t>(high - aabb * 10000u);
	uint32_t aa			= (aabb * 5243u) >> 19ULL;
	uint32_t cc			= (ccdd * 5243u) >> 19ULL;
	const uint32_t bb	= aabb - aa * 100u;
	const uint32_t dd	= ccdd - cc * 100u;
	buf[0]				= int_tables<void>::charTable00[aa];
	std::memcpy(buf + 1ULL, int_tables<void>::charTable02 + bb, 2ULL);
	std::memcpy(buf + 3ULL, int_tables<void>::charTable02 + cc, 2ULL);
	std::memcpy(buf + 5ULL, int_tables<void>::charTable02 + dd, 2ULL);
	aabb = static_cast<uint32_t>((low * 109951163ULL) >> 40ULL);
	ccdd = low - aabb * 10000u;
	aa	 = (aabb * 5243u) >> 19ULL;
	cc	 = (ccdd * 5243u) >> 19ULL;
	std::memcpy(buf + 7ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 9ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	std::memcpy(buf + 11ULL, int_tables<void>::charTable02 + cc, 2ULL);
	std::memcpy(buf + 13ULL, int_tables<void>::charTable02 + (ccdd - cc * 100u), 2ULL);
	return buf + 15ULL;
}

template<typename value_type> BNCH_SWT_HOST static char* toChars16Old(char* buf, const value_type value) noexcept {
	const uint64_t high = value / 100000000ULL;
	const uint32_t low	= static_cast<uint32_t>(value - high * 100000000ULL);
	uint32_t aabb		= static_cast<uint32_t>((high * 109951163ULL) >> 40ULL);
	uint32_t ccdd		= static_cast<uint32_t>(high - aabb * 10000u);
	uint32_t aa			= (aabb * 5243u) >> 19ULL;
	uint32_t cc			= (ccdd * 5243u) >> 19ULL;
	const uint32_t bb	= aabb - aa * 100u;
	const uint32_t dd	= ccdd - cc * 100u;
	std::memcpy(buf, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 2ULL, int_tables<void>::charTable02 + bb, 2ULL);
	std::memcpy(buf + 4ULL, int_tables<void>::charTable02 + cc, 2ULL);
	std::memcpy(buf + 6ULL, int_tables<void>::charTable02 + dd, 2ULL);
	aabb = static_cast<uint32_t>((low * 109951163ULL) >> 40ULL);
	ccdd = low - aabb * 10000u;
	aa	 = (aabb * 5243u) >> 19ULL;
	cc	 = (ccdd * 5243u) >> 19ULL;
	std::memcpy(buf + 8ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 10ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	std::memcpy(buf + 12ULL, int_tables<void>::charTable02 + cc, 2ULL);
	std::memcpy(buf + 14ULL, int_tables<void>::charTable02 + (ccdd - cc * 100u), 2ULL);
	return buf + 16ULL;
}

template<typename value_type> BNCH_SWT_HOST static char* toChars17Old(char* buf, const value_type value) noexcept {
	const uint64_t high	 = value / 100000000ULL;
	const uint64_t low	 = value - high * 100000000ULL;
	const uint64_t high9 = (high * 720575941ULL) >> 56ULL;
	const uint64_t low9	 = high - high9 * 100000000ULL;
	buf[0]				 = int_tables<void>::charTable00[high9];
	uint64_t aabb		 = (low9 * 109951163ULL) >> 40ULL;
	uint64_t aa			 = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 1ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 3ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	aabb = low9 - aabb * 10000u;
	aa	 = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 5ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 7ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	aabb = (low * 109951163ULL) >> 40ULL;
	aa	 = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 9ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 11ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	aabb = low - aabb * 10000u;
	aa	 = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 13ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 15ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	return buf + 17;
}

template<typename value_type> BNCH_SWT_HOST static char* toChars18Old(char* buf, const value_type value) noexcept {
	const uint64_t high	  = value / 100000000ULL;
	const uint64_t low	  = value - high * 100000000ULL;
	const uint64_t high10 = (high * 1801439851ULL) >> 54;
	const uint64_t low10  = high - high10 * 10000000ULL;
	uint64_t aa			  = (high10 * 5243u) >> 19ULL;
	buf[0]				  = int_tables<void>::charTable00[aa];
	std::memcpy(buf + 1ULL, int_tables<void>::charTable02 + (high10 - aa * 100u), 2ULL);
	uint64_t aabb = (low10 * 109951163ULL) >> 40ULL;
	aa			  = (aabb * 5243u) >> 19ULL;
	buf[3]		  = int_tables<void>::charTable00[aa];
	std::memcpy(buf + 4ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	aabb = low10 - aabb * 10000u;
	aa	 = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 6ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 8ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	aabb = (low * 109951163ULL) >> 40ULL;
	aa	 = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 10ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 12ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	aabb = low - aabb * 10000u;
	aa	 = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 14ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 16ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	return buf + 18;
}

template<typename value_type> BNCH_SWT_HOST static char* toChars19Old(char* buf, const value_type value) noexcept {
	const uint64_t high	  = value / 100000000ULL;
	const uint64_t low	  = value - high * 100000000ULL;
	const uint64_t high11 = high / 10000000ULL;
	const uint64_t low11  = high - high11 * 10000000ULL;
	uint64_t aa			  = (high11 * 5243u) >> 19ULL;
	std::memcpy(buf, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 2ULL, int_tables<void>::charTable02 + (high11 - aa * 100u), 2ULL);
	uint64_t aabb = (low11 * 109951163ULL) >> 40ULL;
	aa			  = (aabb * 5243u) >> 19ULL;
	buf[4]		  = int_tables<void>::charTable00[aa];
	std::memcpy(buf + 5ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	aabb = low11 - aabb * 10000u;
	aa	 = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 7ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 9ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	aabb = (low * 109951163ULL) >> 40ULL;
	aa	 = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 11ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 13ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	aabb = low - aabb * 10000u;
	aa	 = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 15ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 17ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	return buf + 19;
}

template<typename value_type> BNCH_SWT_HOST static char* toChars20Old(char* buf, const value_type value) noexcept {
	const uint64_t high	  = value / 100000000ULL;
	const uint64_t low	  = value - high * 100000000ULL;
	const uint64_t high12 = high / 100000000ULL;
	const uint64_t low12  = high - high12 * 100000000ULL;
	uint64_t aa			  = (high12 * 5243u) >> 19ULL;
	std::memcpy(buf, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 2ULL, int_tables<void>::charTable02 + (high12 - aa * 100u), 2ULL);
	uint64_t aabb = (low12 * 109951163ULL) >> 40ULL;
	aa			  = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 4ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 6ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	aabb = low12 - aabb * 10000u;
	aa	 = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 8ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 10ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	aabb = (low * 109951163ULL) >> 40ULL;
	aa	 = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 12ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 14ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	aabb = low - aabb * 10000u;
	aa	 = (aabb * 5243u) >> 19ULL;
	std::memcpy(buf + 16ULL, int_tables<void>::charTable02 + aa, 2ULL);
	std::memcpy(buf + 18ULL, int_tables<void>::charTable02 + (aabb - aa * 100u), 2ULL);
	return buf + 20;
}

template<uns64_t value_type> BNCH_SWT_HOST char* toCharsOld(char* buf, const value_type value) noexcept {
	switch (fastDigitCount(value)) {
		case 20: {
			return toChars20Old(buf, value);
		}
		case 19: {
			return toChars19Old(buf, value);
		}
		case 18: {
			return toChars18Old(buf, value);
		}
		case 17: {
			return toChars17Old(buf, value);
		}
		case 16: {
			return toChars16Old(buf, value);
		}
		case 15: {
			return toChars15Old(buf, value);
		}
		case 14: {
			return toChars14Old(buf, value);
		}
		case 13: {
			return toChars13Old(buf, value);
		}
		case 12: {
			return toChars12Old(buf, value);
		}
		case 11: {
			return toChars11Old(buf, value);
		}
		case 10: {
			return toChars10(buf, value);
		}
		case 9: {
			return toChars9(buf, static_cast<uint32_t>(value));
		}
		case 8: {
			return toChars8(buf, static_cast<uint32_t>(value));
		}
		case 7: {
			return toChars7(buf, static_cast<uint32_t>(value));
		}
		case 6: {
			return toChars6(buf, static_cast<uint32_t>(value));
		}
		case 5: {
			return toChars5(buf, static_cast<uint32_t>(value));
		}
		case 4: {
			return toChars4(buf, static_cast<uint32_t>(value));
		}
		case 3: {
			return toChars3(buf, static_cast<uint32_t>(value));
		}
		case 2: {
			return toChars2(buf, static_cast<uint32_t>(value));
		}
		default: {
			return toChars1(buf, static_cast<uint32_t>(value));
		}
	}
}

template<sig64_t value_type> BNCH_SWT_HOST static char* toCharsOld(char* buf, const value_type value) noexcept {
	*buf = '-';
	return toCharsOld(buf + (value < 0), static_cast<uint64_t>(value ^ (value >> 63ULL)) - (value >> 63ULL));
}

constexpr char char_table[200] = { '0', '0', '0', '1', '0', '2', '0', '3', '0', '4', '0', '5', '0', '6', '0', '7', '0', '8', '0', '9', '1', '0', '1', '1', '1', '2', '1', '3', '1',
	'4', '1', '5', '1', '6', '1', '7', '1', '8', '1', '9', '2', '0', '2', '1', '2', '2', '2', '3', '2', '4', '2', '5', '2', '6', '2', '7', '2', '8', '2', '9', '3', '0', '3', '1',
	'3', '2', '3', '3', '3', '4', '3', '5', '3', '6', '3', '7', '3', '8', '3', '9', '4', '0', '4', '1', '4', '2', '4', '3', '4', '4', '4', '5', '4', '6', '4', '7', '4', '8', '4',
	'9', '5', '0', '5', '1', '5', '2', '5', '3', '5', '4', '5', '5', '5', '6', '5', '7', '5', '8', '5', '9', '6', '0', '6', '1', '6', '2', '6', '3', '6', '4', '6', '5', '6', '6',
	'6', '7', '6', '8', '6', '9', '7', '0', '7', '1', '7', '2', '7', '3', '7', '4', '7', '5', '7', '6', '7', '7', '7', '8', '7', '9', '8', '0', '8', '1', '8', '2', '8', '3', '8',
	'4', '8', '5', '8', '6', '8', '7', '8', '8', '8', '9', '9', '0', '9', '1', '9', '2', '9', '3', '9', '4', '9', '5', '9', '6', '9', '7', '9', '8', '9', '9' };

template<class T>
	requires std::same_as<std::remove_cvref_t<T>, uint32_t>
auto* to_chars(auto* buf, T val) noexcept {
	/* The maximum value of uint32_t is 4294967295 (10 digits), */
	/* these digits are named as 'aabbccddee' here.             */
	uint32_t aa, bb, cc, dd, ee, aabb, bbcc, ccdd, ddee, aabbcc;

	/* Leading zero count in the first pair.                    */
	uint32_t lz;

	/* Although most compilers may convert the "division by     */
	/* constant value" into "multiply and shift", manual        */
	/* conversion can still help some compilers generate        */
	/* fewer and better instructions.                           */

	if (val < 100) { /* 1-2 digits: aa */
		lz = val < 10;
		std::memcpy(buf, char_table + (val * 2 + lz), 2);
		buf -= lz;
		return buf + 2;
	} else if (val < 10000) { /* 3-4 digits: aabb */
		aa = (val * 5243) >> 19; /* (val / 100) */
		bb = val - aa * 100; /* (val % 100) */
		lz = aa < 10;
		std::memcpy(buf, char_table + (aa * 2 + lz), 2);
		buf -= lz;
		std::memcpy(&buf[2], char_table + (2 * bb), 2);

		return buf + 4;
	} else if (val < 1000000) { /* 5-6 digits: aabbcc */
		aa	 = uint32_t((uint64_t(val) * 429497) >> 32); /* (val / 10000) */
		bbcc = val - aa * 10000; /* (val % 10000) */
		bb	 = (bbcc * 5243) >> 19; /* (bbcc / 100) */
		cc	 = bbcc - bb * 100; /* (bbcc % 100) */
		lz	 = aa < 10;
		std::memcpy(buf, char_table + aa * 2 + lz, 2);
		buf -= lz;
		std::memcpy(buf + 2, char_table + bb * 2, 2);
		std::memcpy(buf + 4, char_table + cc * 2, 2);
		return buf + 6;
	} else if (val < 100000000) { /* 7~8 digits: aabbccdd */
		/* (val / 10000) */
		aabb = uint32_t((uint64_t(val) * 109951163) >> 40);
		ccdd = val - aabb * 10000; /* (val % 10000) */
		aa	 = (aabb * 5243) >> 19; /* (aabb / 100) */
		cc	 = (ccdd * 5243) >> 19; /* (ccdd / 100) */
		bb	 = aabb - aa * 100; /* (aabb % 100) */
		dd	 = ccdd - cc * 100; /* (ccdd % 100) */
		lz	 = aa < 10;
		std::memcpy(buf, char_table + aa * 2 + lz, 2);
		buf -= lz;
		std::memcpy(buf + 2, char_table + bb * 2, 2);
		std::memcpy(buf + 4, char_table + cc * 2, 2);
		std::memcpy(buf + 6, char_table + dd * 2, 2);
		return buf + 8;
	} else { /* 9~10 digits: aabbccddee */
		/* (val / 10000) */
		aabbcc = uint32_t((uint64_t(val) * 3518437209ul) >> 45);
		/* (aabbcc / 10000) */
		aa	 = uint32_t((uint64_t(aabbcc) * 429497) >> 32);
		ddee = val - aabbcc * 10000; /* (val % 10000) */
		bbcc = aabbcc - aa * 10000; /* (aabbcc % 10000) */
		bb	 = (bbcc * 5243) >> 19; /* (bbcc / 100) */
		dd	 = (ddee * 5243) >> 19; /* (ddee / 100) */
		cc	 = bbcc - bb * 100; /* (bbcc % 100) */
		ee	 = ddee - dd * 100; /* (ddee % 100) */
		lz	 = aa < 10;
		std::memcpy(buf, char_table + aa * 2 + lz, 2);
		buf -= lz;
		std::memcpy(buf + 2, char_table + bb * 2, 2);
		std::memcpy(buf + 4, char_table + cc * 2, 2);
		std::memcpy(buf + 6, char_table + dd * 2, 2);
		std::memcpy(buf + 8, char_table + ee * 2, 2);
		return buf + 10;
	}
}

template<class T>
	requires std::same_as<std::remove_cvref_t<T>, int32_t>
auto* to_chars(auto* buf, T x) noexcept {
	*buf = '-';
	// shifts are necessary to have the numeric_limits<int32_t>::min case
	return to_chars(buf + (x < 0), uint32_t(x ^ (x >> 31)) - (x >> 31));
}

template<class T>
	requires(std::same_as<std::remove_cvref_t<T>, uint32_t>)
BNCH_SWT_HOST auto* to_chars_u64_len_8(auto* buf, T val) noexcept {
	/* 8 digits: aabbccdd */
	const uint32_t aabb = uint32_t((uint64_t(val) * 109951163) >> 40); /* (val / 10000) */
	const uint32_t ccdd = val - aabb * 10000; /* (val % 10000) */
	const uint32_t aa	= (aabb * 5243) >> 19; /* (aabb / 100) */
	const uint32_t cc	= (ccdd * 5243) >> 19; /* (ccdd / 100) */
	const uint32_t bb	= aabb - aa * 100; /* (aabb % 100) */
	const uint32_t dd	= ccdd - cc * 100; /* (ccdd % 100) */
	std::memcpy(buf, char_table + aa * 2, 2);
	std::memcpy(buf + 2, char_table + bb * 2, 2);
	std::memcpy(buf + 4, char_table + cc * 2, 2);
	std::memcpy(buf + 6, char_table + dd * 2, 2);
	return buf + 8;
}

template<class T>
	requires(std::same_as<std::remove_cvref_t<T>, uint32_t>)
BNCH_SWT_HOST auto* to_chars_u64_len_4(auto* buf, T val) noexcept {
	/* 4 digits: aabb */
	const uint32_t aa = (val * 5243) >> 19; /* (val / 100) */
	const uint32_t bb = val - aa * 100; /* (val % 100) */
	std::memcpy(buf, char_table + aa * 2, 2);
	std::memcpy(buf + 2, char_table + bb * 2, 2);
	return buf + 4;
}

template<class T>
	requires(std::same_as<std::remove_cvref_t<T>, uint32_t>)
inline auto* to_chars_u64_len_1_8(auto* buf, T val) noexcept {
	uint32_t aa, bb, cc, dd, aabb, bbcc, ccdd, lz;

	if (val < 100) { /* 1-2 digits: aa */
		lz = val < 10;
		std::memcpy(buf, char_table + val * 2 + lz, 2);
		buf -= lz;
		return buf + 2;
	} else if (val < 10000) { /* 3-4 digits: aabb */
		aa = (val * 5243) >> 19; /* (val / 100) */
		bb = val - aa * 100; /* (val % 100) */
		lz = aa < 10;
		std::memcpy(buf, char_table + aa * 2 + lz, 2);
		buf -= lz;
		std::memcpy(buf + 2, char_table + bb * 2, 2);
		return buf + 4;
	} else if (val < 1000000) { /* 5-6 digits: aabbcc */
		aa	 = uint32_t((uint64_t(val) * 429497) >> 32); /* (val / 10000) */
		bbcc = val - aa * 10000; /* (val % 10000) */
		bb	 = (bbcc * 5243) >> 19; /* (bbcc / 100) */
		cc	 = bbcc - bb * 100; /* (bbcc % 100) */
		lz	 = aa < 10;
		std::memcpy(buf, char_table + aa * 2 + lz, 2);
		buf -= lz;
		std::memcpy(buf + 2, char_table + bb * 2, 2);
		std::memcpy(buf + 4, char_table + cc * 2, 2);
		return buf + 6;
	} else { /* 7-8 digits: aabbccdd */
		/* (val / 10000) */
		aabb = uint32_t((uint64_t(val) * 109951163) >> 40);
		ccdd = val - aabb * 10000; /* (val % 10000) */
		aa	 = (aabb * 5243) >> 19; /* (aabb / 100) */
		cc	 = (ccdd * 5243) >> 19; /* (ccdd / 100) */
		bb	 = aabb - aa * 100; /* (aabb % 100) */
		dd	 = ccdd - cc * 100; /* (ccdd % 100) */
		lz	 = aa < 10;
		std::memcpy(buf, char_table + aa * 2 + lz, 2);
		buf -= lz;
		std::memcpy(buf + 2, char_table + bb * 2, 2);
		std::memcpy(buf + 4, char_table + cc * 2, 2);
		std::memcpy(buf + 6, char_table + dd * 2, 2);
		return buf + 8;
	}
}

template<class T>
	requires(std::same_as<std::remove_cvref_t<T>, uint32_t>)
auto* to_chars_u64_len_5_8(auto* buf, T val) noexcept {
	if (val < 1000000) { /* 5-6 digits: aabbcc */
		const uint32_t aa	= uint32_t((uint64_t(val) * 429497) >> 32); /* (val / 10000) */
		const uint32_t bbcc = val - aa * 10000; /* (val % 10000) */
		const uint32_t bb	= (bbcc * 5243) >> 19; /* (bbcc / 100) */
		const uint32_t cc	= bbcc - bb * 100; /* (bbcc % 100) */
		const uint32_t lz	= aa < 10;
		std::memcpy(buf, char_table + aa * 2 + lz, 2);
		buf -= lz;
		std::memcpy(buf + 2, char_table + bb * 2, 2);
		std::memcpy(buf + 4, char_table + cc * 2, 2);
		return buf + 6;
	} else { /* 7-8 digits: aabbccdd */
		/* (val / 10000) */
		const uint32_t aabb = uint32_t((uint64_t(val) * 109951163) >> 40);
		const uint32_t ccdd = val - aabb * 10000; /* (val % 10000) */
		const uint32_t aa	= (aabb * 5243) >> 19; /* (aabb / 100) */
		const uint32_t cc	= (ccdd * 5243) >> 19; /* (ccdd / 100) */
		const uint32_t bb	= aabb - aa * 100; /* (aabb % 100) */
		const uint32_t dd	= ccdd - cc * 100; /* (ccdd % 100) */
		const uint32_t lz	= aa < 10;
		std::memcpy(buf, char_table + aa * 2 + lz, 2);
		buf -= lz;
		std::memcpy(buf + 2, char_table + bb * 2, 2);
		std::memcpy(buf + 4, char_table + cc * 2, 2);
		std::memcpy(buf + 6, char_table + dd * 2, 2);
		return buf + 8;
	}
}

template<class T>
	requires(std::same_as<std::remove_cvref_t<T>, uint64_t>)
auto* to_chars(auto* buf, T val) noexcept {
	if (val < 100000000) { /* 1-8 digits */
		buf = to_chars_u64_len_1_8(buf, uint32_t(val));
		return buf;
	} else if (val < 100000000ULL * 100000000ULL) { /* 9-16 digits */
		const uint64_t hgh = val / 100000000;
		const auto low	   = uint32_t(val - hgh * 100000000); /* (val % 100000000) */
		buf				   = to_chars_u64_len_1_8(buf, uint32_t(hgh));
		buf				   = to_chars_u64_len_8(buf, low);
		return buf;
	} else { /* 17-20 digits */
		const uint64_t tmp = val / 100000000;
		const auto low	   = uint32_t(val - tmp * 100000000); /* (val % 100000000) */
		const auto hgh	   = uint32_t(tmp / 10000);
		const auto mid	   = uint32_t(tmp - hgh * 10000); /* (tmp % 10000) */
		buf				   = to_chars_u64_len_5_8(buf, hgh);
		buf				   = to_chars_u64_len_4(buf, mid);
		buf				   = to_chars_u64_len_8(buf, low);
		return buf;
	}
}

template<class T>
	requires std::same_as<std::remove_cvref_t<T>, int64_t>
auto* to_chars(auto* buf, T x) noexcept {
	*buf = '-';
	// shifts are necessary to have the numeric_limits<int64_t>::min case
	return to_chars(buf + (x < 0), uint64_t(x ^ (x >> 63)) - (x >> 63));
}

uint64_t generateRandomIntegerByLength(uint64_t digitLength) {
	if (digitLength == 0) {
		throw std::invalid_argument("Digit length must be greater than 0.");
	}

	if (digitLength > 20) {
		throw std::invalid_argument("Digit length exceeds the limit for uint64_t (maximum 20 digits).");
	}

	std::string newString{};
	newString.resize(digitLength);
	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_int_distribution<uint16_t> dist01(1, 9);
	std::uniform_int_distribution<uint16_t> dist02(0, 9);
	newString[0] = static_cast<char>(dist01(gen)) + '0';
	for (uint64_t x = 1; x < digitLength; ++x) {
		newString[x] = static_cast<char>(dist02(gen)) + '0';
	}
	auto endIter = newString.data() + newString.size();
	uint64_t newValue{ std::strtoull(newString.data(), &endIter, 10) };
	return newValue;
}

template<typename value_type> std::vector<value_type> generateRandomIntegers(uint64_t count, uint64_t maxLength = 0, bool generateOnlyGivenLength = false) {
	std::random_device rd;
	std::mt19937_64 gen(rd());
	uint64_t maxLengthNew{ maxLength == 0 ? 20 : maxLength };
	std::uniform_int_distribution<value_type> lengthGen(1, maxLengthNew);

	std::vector<value_type> randomNumbers;
	for (uint64_t value = 0; value < count; ++value) {
		uint64_t newValue{};
		if (generateOnlyGivenLength) {
			newValue = generateRandomIntegerByLength(maxLengthNew);
		} else {
			newValue = generateRandomIntegerByLength(lengthGen(gen));
		}
		randomNumbers.push_back(newValue);
	}

	return randomNumbers;
}

static constexpr auto max_iterations{ 20 };
static constexpr auto measured_iterations{ max_iterations / 5 };

struct benchmark_glz_to_chars {
	BNCH_SWT_HOST static uint64_t impl(std::vector<std::vector<std::string>>& resultsTest, const std::vector<std::vector<uint64_t>>& randomIntegers, uint64_t count,
		uint64_t current_index) {
		uint64_t currentCount{};
		for (uint64_t x = 0; x < count; ++x) {
			to_chars(resultsTest[current_index][x].data(), randomIntegers[current_index][x]);
			currentCount += resultsTest[current_index][x].size();
		}
		return currentCount;
	}
};

struct benchmark_jsonifier_to_chars {
	BNCH_SWT_HOST static uint64_t impl(std::vector<std::vector<std::string>>& resultsTest, const std::vector<std::vector<uint64_t>>& randomIntegers, uint64_t count,
		uint64_t current_index) {
		uint64_t currentCount{};
		for (uint64_t x = 0; x < count; ++x) {
			toChars(resultsTest[current_index][x].data(), static_cast<uint64_t>(randomIntegers[current_index][x]));
			currentCount += resultsTest[current_index][x].size();
		}
		return currentCount;
	}
};

struct benchmark_std_to_chars {
	BNCH_SWT_HOST static uint64_t impl(std::vector<std::vector<std::string>>& resultsTest, const std::vector<std::vector<uint64_t>>& randomIntegers, uint64_t count, uint64_t current_index) {
		uint64_t currentCount{};
		for (uint64_t x = 0; x < count; ++x) {
			std::to_chars(resultsTest[current_index][x].data(), resultsTest[current_index][x].data() + resultsTest[current_index][x].size(),
				static_cast<uint64_t>(randomIntegers[current_index][x]));
			currentCount += resultsTest[current_index][x].size();
		}
		return currentCount;
	}
};

struct benchmark_jsonifier_to_chars_old {
	BNCH_SWT_HOST static uint64_t impl(std::vector<std::vector<std::string>>& resultsTest, const std::vector<std::vector<uint64_t>>& randomIntegers, uint64_t count,
		uint64_t current_index) {
		uint64_t currentCount{};
		for (uint64_t x = 0; x < count; ++x) {
			toCharsOld(resultsTest[current_index][x].data(), static_cast<uint64_t>(randomIntegers[current_index][x]));
			currentCount += resultsTest[current_index][x].size();
		}
		return currentCount;
	}
};

template<bnch_swt::string_literal stage_name, typename benchmark_type, bnch_swt::string_literal benchmark_name>
BNCH_SWT_HOST void run_and_validate(auto& resultsTest, const auto& resultsReal, const auto& randomIntegers, uint64_t count, uint64_t& current_index) {
	using benchmark = bnch_swt::benchmark_stage<stage_name, max_iterations, measured_iterations, bnch_swt::benchmark_types::cpu, true>;

	benchmark::template run_benchmark<benchmark_name, benchmark_type>(resultsTest, randomIntegers, count, current_index);

	for (uint64_t y = 0; y < count; ++y) {
		if (resultsReal[current_index][y] != resultsTest[current_index][y]) {
			std::cout << benchmark_name.operator std::string_view() << " failed to serialize an integer of value: " << resultsReal[current_index][y]
					  << ", instead it serialized: " << resultsTest[current_index][y] << std::endl;
		}
	}
}

template<uint64_t count, uint64_t length = 0, bool generateOnlyGivenLength = false, bnch_swt::string_literal name> inline void testFunction64() {
	std::vector<std::vector<uint64_t>> randomIntegers{};
	randomIntegers.resize(max_iterations);
	for (uint64_t x = 0; x < max_iterations; ++x) {
		randomIntegers[x] = generateRandomIntegers<uint64_t>(count, length, generateOnlyGivenLength);
	}
	std::vector<std::vector<std::string>> resultsReal{};	
	std::vector<std::vector<std::string>> resultsTest{};
	resultsReal.resize(max_iterations);
	resultsTest.resize(max_iterations);
	for (uint64_t x = 0; x < max_iterations; ++x) {
		resultsTest[x].resize(count);
		resultsReal[x].resize(count);

		for (uint64_t y = 0; y < count; ++y) {
			resultsReal[x][y] = std::to_string(randomIntegers[x][y]);
			resultsTest[x][y].resize(resultsReal[x][y].size());
		}
	}
	uint64_t currentIndex{};
	run_and_validate<name, benchmark_glz_to_chars, "glz::to_chars">(resultsTest, resultsReal, randomIntegers, count, currentIndex);
	currentIndex = 0;
	run_and_validate<name, benchmark_std_to_chars, "std::to_chars">(resultsTest, resultsReal, randomIntegers, count, currentIndex);
	currentIndex = 0;
	run_and_validate<name, benchmark_jsonifier_to_chars, "jsonifier::internal::toChars">(resultsTest, resultsReal, randomIntegers, count, currentIndex);
	currentIndex = 0;
	run_and_validate<name, benchmark_jsonifier_to_chars_old, "jsonifier::internal::toCharsOld">(resultsTest, resultsReal, randomIntegers, count, currentIndex);
	bnch_swt::benchmark_stage<name, max_iterations, measured_iterations, bnch_swt::benchmark_types::cpu, true>::print_results(true, true);
}

int main() {
	testFunction64<1000, 1, true, "uint64-test-1-100">();
	testFunction64<1000, 2, true, "uint64-test-2-100">();
	testFunction64<1000, 3, true, "uint64-test-3-100">();
	testFunction64<1000, 4, true, "uint64-test-4-100">();
	testFunction64<1000, 5, true, "uint64-test-5-100">();
	testFunction64<1000, 6, true, "uint64-test-6-100">();
	testFunction64<1000, 7, true, "uint64-test-7-100">();
	testFunction64<1000, 8, true, "uint64-test-8-100">();
	testFunction64<1000, 9, true, "uint64-test-9-100">();
	testFunction64<1000, 10, true, "uint64-test-10-100">();
	testFunction64<1000, 11, true, "uint64-test-11-100">();
	testFunction64<1000, 12, true, "uint64-test-12-100">();
	testFunction64<1000, 13, true, "uint64-test-13-100">();
	testFunction64<1000, 14, true, "uint64-test-14-100">();
	testFunction64<1000, 15, true, "uint64-test-15-100">();
	testFunction64<1000, 16, true, "uint64-test-16-100">();
	testFunction64<1000, 17, true, "uint64-test-17-100">();
	testFunction64<1000, 18, true, "uint64-test-18-100">();
	testFunction64<1000, 19, true, "uint64-test-19-100">();
	testFunction64<1000, 20, true, "uint64-test-20-100">();
	return 0;
}