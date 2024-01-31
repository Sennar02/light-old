#ifndef LIGHT_BASE_DEFINE_HPP
#define LIGHT_BASE_DEFINE_HPP

#include <light/Base/depend.hpp>

namespace lgh
{
    using u8  = uint8_t;
    using u16 = uint16_t;
    using u32 = uint32_t;
    using u64 = uint64_t;
    using upt = uintptr_t;

    using i8  = int8_t;
    using i16 = int16_t;
    using i32 = int32_t;
    using i64 = int64_t;
    using ipt = intptr_t;

    using f32 = float_t;
    using f64 = double_t;

    static const u32 g_bits = 8u;

    template <class Item, class Fail>
    class Result;

    template <class Item>
    class Option;

    template <class Item, u32 Size>
    class Vector;

    template <class Type>
    using Vector2D = Vector<Type, 2>;

    using Vec2u = Vector2D<u32>;
    using Vec2i = Vector2D<i32>;
    using Vec2f = Vector2D<f32>;

    class String;

    static const u8  g_max_u8  = UINT8_MAX;
    static const u16 g_max_u16 = UINT16_MAX;
    static const u32 g_max_u32 = UINT32_MAX;
    static const u64 g_max_u64 = UINT64_MAX;
    static const upt g_max_upt = SIZE_MAX;

    static const u8  g_min_u8  = 0;
    static const u16 g_min_u16 = 0;
    static const u32 g_min_u32 = 0;
    static const u64 g_min_u64 = 0;
    static const upt g_min_upt = 0;

    static const i8  g_max_i8  = g_max_u8 / 2;
    static const i16 g_max_i16 = g_max_u16 / 2;
    static const i32 g_max_i32 = g_max_u32 / 2;
    static const i64 g_max_i64 = g_max_u64 / 2;
    static const ipt g_max_ipt = g_max_upt / 2;

    static const i8  g_min_i8  = -g_max_i8 - 1;
    static const i16 g_min_i16 = -g_max_i16 - 1;
    static const i32 g_min_i32 = -g_max_i32 - 1;
    static const i64 g_min_i64 = -g_max_i64 - 1;
    static const ipt g_min_ipt = -g_max_ipt - 1;

    static const f32 g_inf_f32 = INFINITY;
    static const f64 g_inf_f64 = INFINITY;

    static const f32 g_nan_f32 = NAN;
    static const f64 g_nan_f64 = NAN;

    static const u32 g_len_u8  = sizeof(u8);
    static const u32 g_len_u16 = sizeof(u16);
    static const u32 g_len_u32 = sizeof(u32);
    static const u32 g_len_u64 = sizeof(u64);
    static const u32 g_len_upt = sizeof(upt);

    static const u32 g_len_i8  = sizeof(i8);
    static const u32 g_len_i16 = sizeof(i16);
    static const u32 g_len_i32 = sizeof(i32);
    static const u32 g_len_i64 = sizeof(i64);
    static const u32 g_len_ipt = sizeof(ipt);

    static const u32 g_len_f32 = sizeof(f32);
    static const u32 g_len_f64 = sizeof(f64);
} // namespace lgh

// clang-format off
#define LGT_STRING(str) \
    lgh::String { str, sizeof(str) - 1u }
// clang-format on

#endif // LIGHT_BASE_DEFINE_HPP
