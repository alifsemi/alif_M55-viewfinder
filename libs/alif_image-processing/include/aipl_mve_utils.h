/**
 * @file aipl_mve_utils.h
 */

#ifndef AIPL_MVE_UTILS_H
#define AIPL_MVE_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "aipl_config.h"
#if AIPL_USE_MVE
#include "arm_mve.h"

/*********************
 *      DEFINES
 *********************/
/**
 * Create 16 offset values
 *
 * @param N number of pixels
 * @param S pixel size
 */
#define AIPL_OFFSETS_U8(N, S)   (vmulq_n_u8(vidupq_n_u8(0, N), S))

#define AIPL_8_BYTE_OFFSETS_U8  AIPL_OFFSETS_U8(1, 8)
#define AIPL_4_BYTE_OFFSETS_U8  AIPL_OFFSETS_U8(1, 4)
#define AIPL_3_BYTE_OFFSETS_U8  AIPL_OFFSETS_U8(1, 3)
#define AIPL_2_BYTE_OFFSETS_U8  AIPL_OFFSETS_U8(1, 2)

/**
 * Create 8 offset values
 *
 * @param N number of pixels
 * @param S pixel size
 */
#define AIPL_OFFSETS_U16(N, S)  (vmulq_n_u16(vidupq_n_u16(0, N), S))

#define AIPL_8_BYTE_OFFSETS_U16 AIPL_OFFSETS_U16(1, 8)
#define AIPL_4_BYTE_OFFSETS_U16 AIPL_OFFSETS_U16(1, 4)
#define AIPL_3_BYTE_OFFSETS_U16 AIPL_OFFSETS_U16(1, 3)
#define AIPL_2_BYTE_OFFSETS_U16 AIPL_OFFSETS_U16(1, 2)

#define INLINE inline __attribute__((always_inline))

/**********************
 *      TYPEDEFS
 **********************/
typedef struct {
    uint16x8_t a;
    uint16x8_t r;
    uint16x8_t g;
    uint16x8_t b;
} aipl_mve_argb_x8_t;

typedef struct {
    uint8x16_t a;
    uint8x16_t r;
    uint8x16_t g;
    uint8x16_t b;
} aipl_mve_argb_x16_t;

typedef struct {
    uint32x4_t r;
    uint32x4_t g;
    uint32x4_t b;
} aipl_mve_rgb_x4_t;

typedef struct {
    uint16x8_t r;
    uint16x8_t g;
    uint16x8_t b;
} aipl_mve_rgb_x8_t;

typedef struct {
    uint8x16_t r;
    uint8x16_t g;
    uint8x16_t b;
} aipl_mve_rgb_x16_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/
/**
 * Get 8 even-numbered pixels from 16-pixel ARGB struct
 *
 * @param dst   8-pixel struct pointer
 * @param src   16-pixel struct pointer
 */
INLINE void aipl_mve_convert_argb_x16_to_x8_evn(aipl_mve_argb_x8_t* dst,
                                                const aipl_mve_argb_x16_t* src)
{
    dst->a = vmovlbq(src->a);
    dst->r = vmovlbq(src->r);
    dst->g = vmovlbq(src->g);
    dst->b = vmovlbq(src->b);
}

/**
 * Get 8 odd-numbered pixels from 16-pixel ARGB struct
 *
 * @param dst   8-pixel struct pointer
 * @param src   16-pixel struct pointer
 */
INLINE void aipl_mve_convert_argb_x16_to_x8_odd(aipl_mve_argb_x8_t* dst,
                                                const aipl_mve_argb_x16_t* src)
{
    dst->a = vmovltq(src->a);
    dst->r = vmovltq(src->r);
    dst->g = vmovltq(src->g);
    dst->b = vmovltq(src->b);
}

/**
 * Get 8 even-numbered pixels from 16-pixel RGB struct
 *
 * @param dst   8-pixel struct pointer
 * @param src   16-pixel struct pointer
 */
INLINE void aipl_mve_convert_rgb_x16_to_x8_evn(aipl_mve_rgb_x8_t* dst,
                                               const aipl_mve_rgb_x16_t* src)
{
    dst->r = vmovlbq(src->r);
    dst->g = vmovlbq(src->g);
    dst->b = vmovlbq(src->b);
}

/**
 * Get 8 odd-numbered pixels from 16-pixel RGB struct
 *
 * @param dst   8-pixel struct pointer
 * @param src   16-pixel struct pointer
 */
INLINE void aipl_mve_convert_rgb_x16_to_x8_odd(aipl_mve_rgb_x8_t* dst,
                                               const aipl_mve_rgb_x16_t* src)
{
    dst->r = vmovltq(src->r);
    dst->g = vmovltq(src->g);
    dst->b = vmovltq(src->b);
}

/**
 * Get 4 even-numbered pixels from 8-pixel RGB struct
 *
 * @param dst   4-pixel struct pointer
 * @param src   8-pixel struct pointer
 */
INLINE void aipl_mve_convert_rgb_x8_to_x4_evn(aipl_mve_rgb_x4_t* dst,
                                              const aipl_mve_rgb_x8_t* src)
{
    dst->r = vmovlbq(src->r);
    dst->g = vmovlbq(src->g);
    dst->b = vmovlbq(src->b);
}

/**
 * Get 4 odd-numbered pixels from 8-pixel RGB struct
 *
 * @param dst   4-pixel struct pointer
 * @param src   8-pixel struct pointer
 */
INLINE void aipl_mve_convert_rgb_x8_to_x4_odd(aipl_mve_rgb_x4_t* dst,
                                              const aipl_mve_rgb_x8_t* src)
{
    dst->r = vmovltq(src->r);
    dst->g = vmovltq(src->g);
    dst->b = vmovltq(src->b);
}

/**
 * Get 16-pixel struct from two 8-pixel ARGBs
 *
 * @param dst       16-pixel struct pointer
 * @param src_evn   8-pixel even struct pointer
 * @param src_odd   8-pixel odd struct pointer
 */
INLINE void aipl_mve_convert_2_argb_x8_to_x16(aipl_mve_argb_x16_t* dst,
                                              const aipl_mve_argb_x8_t* src_evn,
                                              const aipl_mve_argb_x8_t* src_odd)
{
    dst->a = vmovntq(vreinterpretq_u8(src_evn->a), src_odd->a);
    dst->r = vmovntq(vreinterpretq_u8(src_evn->r), src_odd->r);
    dst->g = vmovntq(vreinterpretq_u8(src_evn->g), src_odd->g);
    dst->b = vmovntq(vreinterpretq_u8(src_evn->b), src_odd->b);
}

/**
 * Get 8-pixel struct from two 4-pixel RGBs
 *
 * @param dst       8-pixel struct pointer
 * @param src_evn   4-pixel even struct pointer
 * @param src_odd   4-pixel odd struct pointer
 */
INLINE void aipl_mve_convert_2_rgb_x4_to_x8(aipl_mve_rgb_x8_t* dst,
                                            const aipl_mve_rgb_x4_t* src_evn,
                                            const aipl_mve_rgb_x4_t* src_odd)
{
    dst->r = vmovntq(vreinterpretq_u16(src_evn->r), src_odd->r);
    dst->g = vmovntq(vreinterpretq_u16(src_evn->g), src_odd->g);
    dst->b = vmovntq(vreinterpretq_u16(src_evn->b), src_odd->b);
}

/**
 * Get 16-pixel struct from two 8-pixel RGBs
 *
 * @param dst       16-pixel struct pointer
 * @param src_evn   8-pixel even struct pointer
 * @param src_odd   8-pixel odd struct pointer
 */
INLINE void aipl_mve_convert_2_rgb_x8_to_x16(aipl_mve_rgb_x16_t* dst,
                                             const aipl_mve_rgb_x8_t* src_evn,
                                             const aipl_mve_rgb_x8_t* src_odd)
{
    dst->r = vmovntq(vreinterpretq_u8(src_evn->r), src_odd->r);
    dst->g = vmovntq(vreinterpretq_u8(src_evn->g), src_odd->g);
    dst->b = vmovntq(vreinterpretq_u8(src_evn->b), src_odd->b);
}

/**
 * Load 8 ARGB8888 pixels with alpha channel
 *
 * @param dst   destination struct pointer
 * @param src   first source pixel pointer
 * @param pred  load predicate
 */
INLINE void aipl_mve_loada_argb8888_8px(aipl_mve_argb_x8_t* dst,
                                        const uint8_t* src,
                                        mve_pred16_t pred)
{
    dst->a = vldrbq_gather_offset_z(src + 3, AIPL_4_BYTE_OFFSETS_U16, pred);
    dst->r = vldrbq_gather_offset_z(src + 2, AIPL_4_BYTE_OFFSETS_U16, pred);
    dst->g = vldrbq_gather_offset_z(src + 1, AIPL_4_BYTE_OFFSETS_U16, pred);
    dst->b = vldrbq_gather_offset_z(src, AIPL_4_BYTE_OFFSETS_U16, pred);
}

/**
 * Load 16 ARGB8888 pixels with alpha channel
 *
 * @param dst   destination struct pointer
 * @param src   first source pixel pointer
 * @param pred  load predicate
 */
INLINE void aipl_mve_loada_argb8888_16px(aipl_mve_argb_x16_t* dst,
                                         const uint8_t* src,
                                         mve_pred16_t pred)
{
    dst->a = vldrbq_gather_offset_z(src + 3, AIPL_4_BYTE_OFFSETS_U8, pred);
    dst->r = vldrbq_gather_offset_z(src + 2, AIPL_4_BYTE_OFFSETS_U8, pred);
    dst->g = vldrbq_gather_offset_z(src + 1, AIPL_4_BYTE_OFFSETS_U8, pred);
    dst->b = vldrbq_gather_offset_z(src, AIPL_4_BYTE_OFFSETS_U8, pred);
}

/**
 * Load 8 ARGB8888 pixels with alpha channel
 * and custom offset between pixels
 *
 * @param dst       destination struct pointer
 * @param src       first source pixel pointer
 * @param offset    pixel offset
 * @param pred      load predicate
 */
INLINE void aipl_mve_loada_argb8888_offset_8px(aipl_mve_argb_x8_t* dst,
                                               const uint8_t* src,
                                               uint8_t offset,
                                               mve_pred16_t pred)
{
    dst->a = vldrbq_gather_offset_z(src + 3, AIPL_OFFSETS_U16(offset, 4), pred);
    dst->r = vldrbq_gather_offset_z(src + 2, AIPL_OFFSETS_U16(offset, 4), pred);
    dst->g = vldrbq_gather_offset_z(src + 1, AIPL_OFFSETS_U16(offset, 4), pred);
    dst->b = vldrbq_gather_offset_z(src, AIPL_OFFSETS_U16(offset, 4), pred);
}

/**
 * Load 16 ARGB8888 pixels with alpha channel
 * and custom offsets between pixels
 *
 * @param dst       destination struct pointer
 * @param src       first source pixel pointer
 * @param offset    pixel offset
 * @param pred      load predicate
 */
INLINE void aipl_mve_loada_argb8888_offset_16px(aipl_mve_argb_x16_t* dst,
                                                const uint8_t* src,
                                                uint8_t offset,
                                                mve_pred16_t pred)
{
    dst->a = vldrbq_gather_offset_z(src + 3, AIPL_OFFSETS_U8(offset, 4), pred);
    dst->r = vldrbq_gather_offset_z(src + 2, AIPL_OFFSETS_U8(offset, 4), pred);
    dst->g = vldrbq_gather_offset_z(src + 1, AIPL_OFFSETS_U8(offset, 4), pred);
    dst->b = vldrbq_gather_offset_z(src, AIPL_OFFSETS_U8(offset, 4), pred);
}

/**
 * Load 16 ARGB4444 pixels with alpha channel
 *
 * @param dst   destination struct pointer
 * @param src   first source pixel pointer
 * @param pred  load predicate
 */
INLINE void aipl_mve_loada_argb4444_16px(aipl_mve_argb_x16_t* dst,
                                         const uint8_t* src,
                                         mve_pred16_t pred)
{
    uint8x16_t ar = vldrbq_gather_offset_z(src + 1, AIPL_2_BYTE_OFFSETS_U8, pred);
    uint8x16_t gb = vldrbq_gather_offset_z(src, AIPL_2_BYTE_OFFSETS_U8, pred);

    dst->a = vorrq(vandq(ar, vdupq_n_u8(0xf0)), vshrq(ar, 4));
    dst->r = vshlq_n(ar, 4);
    dst->g = vandq(gb, vdupq_n_u8(0xf0));
    dst->b = vshlq_n(gb, 4);
}

/**
 * Load 16 ARGB1555 pixels with alpha channel
 *
 * @param dst   destination struct pointer
 * @param src   first source pixel pointer
 * @param pred  load predicate
 */
INLINE void aipl_mve_loada_argb1555_16px(aipl_mve_argb_x16_t* dst,
                                         const uint8_t* src,
                                         mve_pred16_t pred)
{
    uint8x16_t upper = vldrbq_gather_offset_z(src + 1, AIPL_2_BYTE_OFFSETS_U8, pred);
    uint8x16_t lower = vldrbq_gather_offset_z(src, AIPL_2_BYTE_OFFSETS_U8, pred);

    dst->a = vmulq(vshrq(upper, 7), vdupq_n_u8(0xff));
    dst->r = vandq(vshlq_n(upper, 1), vdupq_n_u8(0xf0));
    dst->g = vorrq(vshlq_n(upper, 6), vshrq(vandq(lower, vdupq_n_u8(0xe0)), 2));
    dst->b = vshlq_n(lower, 3);
}

/**
 * Load 16 RGBA8888 pixels with alpha channel
 *
 * @param dst   destination struct pointer
 * @param src   first source pixel pointer
 * @param pred  load predicate
 */
INLINE void aipl_mve_loada_rgba8888_16px(aipl_mve_argb_x16_t* dst,
                                         const uint8_t* src,
                                         mve_pred16_t pred)
{
    dst->r = vldrbq_gather_offset_z(src + 3, AIPL_4_BYTE_OFFSETS_U8, pred);
    dst->g = vldrbq_gather_offset_z(src + 2, AIPL_4_BYTE_OFFSETS_U8, pred);
    dst->b = vldrbq_gather_offset_z(src + 1, AIPL_4_BYTE_OFFSETS_U8, pred);
    dst->a = vldrbq_gather_offset_z(src, AIPL_4_BYTE_OFFSETS_U8, pred);
}

/**
 * Load 16 RGBA4444 pixels with alpha channel
 *
 * @param dst   destination struct pointer
 * @param src   first source pixel pointer
 * @param pred  load predicate
 */
INLINE void aipl_mve_loada_rgba4444_16px(aipl_mve_argb_x16_t* dst,
                                         const uint8_t* src,
                                         mve_pred16_t pred)
{
    uint8x16_t rg = vldrbq_gather_offset_z(src + 1, AIPL_2_BYTE_OFFSETS_U8, pred);
    uint8x16_t ba = vldrbq_gather_offset_z(src, AIPL_2_BYTE_OFFSETS_U8, pred);

    dst->r = vandq(rg, vdupq_n_u8(0xf0));
    dst->g = vshlq_n(rg, 4);
    dst->b = vandq(ba, vdupq_n_u8(0xf0));
    dst->a = vorrq(vshlq_n(ba, 4), vandq(ba, vdupq_n_u8(0x0f)));
}

/**
 * Load 16 RGBA5551 pixels with alpha channel
 *
 * @param dst   destination struct pointer
 * @param src   first source pixel pointer
 * @param pred  load predicate
 */
INLINE void aipl_mve_loada_rgba5551_16px(aipl_mve_argb_x16_t* dst,
                                         const uint8_t* src,
                                         mve_pred16_t pred)
{
    uint8x16_t upper = vldrbq_gather_offset_z(src + 1, AIPL_2_BYTE_OFFSETS_U8, pred);
    uint8x16_t lower = vldrbq_gather_offset_z(src, AIPL_2_BYTE_OFFSETS_U8, pred);

    dst->r = vandq(upper, vdupq_n_u8(0xf8));
    dst->g = vorrq(vshlq_n(upper, 5), vshrq(vandq(lower, vdupq_n_u8(0xc0)), 3));
    dst->b = vshlq_n(vandq(lower, vdupq_n_u8(0x3e)), 2);
    dst->a = vmulq(vandq(lower, vdupq_n_u8(0x01)), vdupq_n_u8(0xff));
}

/**
 * Load 8 ARGB888 pixels without alpha channel
 *
 * @param dst   destination struct pointer
 * @param src   first source pixel pointer
 * @param pred  load predicate
 */
INLINE void aipl_mve_load_argb8888_8px(aipl_mve_rgb_x8_t* dst,
                                       const uint8_t* src,
                                       mve_pred16_t pred)
{
    const uint16x8_t pixel_offsets = vmulq_n_u16(vidupq_n_u16(0, 1), 4);

    dst->r = vldrbq_gather_offset_z(src + 2, AIPL_4_BYTE_OFFSETS_U16, pred);
    dst->g = vldrbq_gather_offset_z(src + 1, AIPL_4_BYTE_OFFSETS_U16, pred);
    dst->b = vldrbq_gather_offset_z(src, AIPL_4_BYTE_OFFSETS_U16, pred);
}

/**
 * Load 16 ARGB8888 pixels without alpha channel
 *
 * @param dst   destination struct pointer
 * @param src   first source pixel pointer
 * @param pred  load predicate
 */
INLINE void aipl_mve_load_argb8888_16px(aipl_mve_rgb_x16_t* dst,
                                        const uint8_t* src,
                                        mve_pred16_t pred)
{
    dst->r = vldrbq_gather_offset_z(src + 2, AIPL_4_BYTE_OFFSETS_U8, pred);
    dst->g = vldrbq_gather_offset_z(src + 1, AIPL_4_BYTE_OFFSETS_U8, pred);
    dst->b = vldrbq_gather_offset_z(src, AIPL_4_BYTE_OFFSETS_U8, pred);
}

/**
 * Load 8 ARGB8888 pixels without alpha channel
 * and with custom offsets between pixels
 *
 * @param dst       destination struct pointer
 * @param src       first source pixel pointer
 * @param offset    pixel offset
 * @param pred      load predicate
 */
INLINE void aipl_mve_load_argb8888_offset_8px(aipl_mve_rgb_x8_t* dst,
                                              const uint8_t* src,
                                              uint8_t offset,
                                              mve_pred16_t pred)
{
    dst->r = vldrbq_gather_offset_z(src + 2, AIPL_OFFSETS_U16(offset, 4), pred);
    dst->g = vldrbq_gather_offset_z(src + 1, AIPL_OFFSETS_U16(offset, 4), pred);
    dst->b = vldrbq_gather_offset_z(src, AIPL_OFFSETS_U16(offset, 4), pred);
}

/**
 * Load 16 ARGB8888 pixels without alpha channel
 * and with custom offsets between pixels
 *
 * @param dst       destination struct pointer
 * @param src       first source pixel pointer
 * @param offset    pixel offset
 * @param pred      load predicate
 */
INLINE void aipl_mve_load_argb8888_offset_16px(aipl_mve_rgb_x16_t* dst,
                                               const uint8_t* src,
                                               uint8_t offset,
                                               mve_pred16_t pred)
{
    dst->r = vldrbq_gather_offset_z(src + 2, AIPL_OFFSETS_U8(offset, 4), pred);
    dst->g = vldrbq_gather_offset_z(src + 1, AIPL_OFFSETS_U8(offset, 4), pred);
    dst->b = vldrbq_gather_offset_z(src, AIPL_OFFSETS_U8(offset, 4), pred);
}

/**
 * Load 16 ARGB4444 pixels without alpha channel
 *
 * @param dst   destination struct pointer
 * @param src   first source pixel pointer
 * @param pred  load predicate
 */
INLINE void aipl_mve_load_argb4444_16px(aipl_mve_rgb_x16_t* dst,
                                        const uint8_t* src,
                                        mve_pred16_t pred)
{
    uint8x16_t ar = vldrbq_gather_offset_z(src + 1, AIPL_2_BYTE_OFFSETS_U8, pred);
    uint8x16_t gb = vldrbq_gather_offset_z(src, AIPL_2_BYTE_OFFSETS_U8, pred);

    dst->r = vshlq_n(ar, 4);
    dst->g = vandq(gb, vdupq_n_u8(0xf0));
    dst->b = vshlq_n(gb, 4);
}

/**
 * Load 16 ARGB1555 pixels without alpha channel
 *
 * @param dst   destination struct pointer
 * @param src   first source pixel pointer
 * @param pred  load predicate
 */
INLINE void aipl_mve_load_argb1555_16px(aipl_mve_rgb_x16_t* dst,
                                        const uint8_t* src,
                                        mve_pred16_t pred)
{
    uint8x16_t upper = vldrbq_gather_offset_z(src + 1, AIPL_2_BYTE_OFFSETS_U8, pred);
    uint8x16_t lower = vldrbq_gather_offset_z(src, AIPL_2_BYTE_OFFSETS_U8, pred);

    dst->r = vandq(vshlq_n(upper, 1), vdupq_n_u8(0xf0));
    dst->g = vorrq(vshlq_n(upper, 6), vshrq(vandq(lower, vdupq_n_u8(0xe0)), 2));
    dst->b = vshlq_n(lower, 3);
}

/**
 * Load 16 ARGB4444 pixels without alpha channel
 * and with custom offsets between pixels
 *
 * @param dst       destination struct pointer
 * @param src       first source pixel pointer
 * @param offset    pixel offset
 * @param pred      load predicate
 */
INLINE void aipl_mve_load_argb4444_offset_16px(aipl_mve_rgb_x16_t* dst,
                                               const uint8_t* src,
                                               uint8_t offset,
                                               mve_pred16_t pred)
{
    uint8x16_t ar = vldrbq_gather_offset_z(src + 1, AIPL_OFFSETS_U8(offset, 2), pred);
    uint8x16_t gb = vldrbq_gather_offset_z(src, AIPL_OFFSETS_U8(offset, 2), pred);

    dst->r = vshlq_n(ar, 4);
    dst->g = vandq(gb, vdupq_n_u8(0xf0));
    dst->b = vshlq_n(gb, 4);
}

/**
 * Load 16 ARGB1555 pixels without alpha channel
 * and with custom offsets between pixels
 *
 * @param dst       destination struct pointer
 * @param src       first source pixel pointer
 * @param offset    pixel offset
 * @param pred      load predicate
 */
INLINE void aipl_mve_load_argb1555_offset_16px(aipl_mve_rgb_x16_t* dst,
                                               const uint8_t* src,
                                               uint8_t offset,
                                               mve_pred16_t pred)
{
    uint8x16_t upper = vldrbq_gather_offset_z(src + 1, AIPL_OFFSETS_U8(offset, 2), pred);
    uint8x16_t lower = vldrbq_gather_offset_z(src, AIPL_OFFSETS_U8(offset, 2), pred);

    dst->r = vandq(vshlq_n(upper, 1), vdupq_n_u8(0xf0));
    dst->g = vorrq(vshlq_n(upper, 6), vshrq(vandq(lower, vdupq_n_u8(0xe0)), 2));
    dst->b = vshlq_n(lower, 3);
}

/**
 * Load 16 RGBA8888 pixels without alpha channel
 *
 * @param dst   destination struct pointer
 * @param src   first source pixel pointer
 * @param pred  load predicate
 */
INLINE void aipl_mve_load_rgba8888_16px(aipl_mve_rgb_x16_t* dst,
                                        const uint8_t* src,
                                        mve_pred16_t pred)
{
    dst->r = vldrbq_gather_offset_z(src + 3, AIPL_4_BYTE_OFFSETS_U8, pred);
    dst->g = vldrbq_gather_offset_z(src + 2, AIPL_4_BYTE_OFFSETS_U8, pred);
    dst->b = vldrbq_gather_offset_z(src + 1, AIPL_4_BYTE_OFFSETS_U8, pred);
}

/**
 * Load 16 RGBA8888 pixels without alpha channel
 * and with custom offsets between pixels
 *
 * @param dst       destination struct pointer
 * @param src       first source pixel pointer
 * @param offset    pixel offset
 * @param pred      load predicate
 */
INLINE void aipl_mve_load_rgba8888_offset_16px(aipl_mve_rgb_x16_t* dst,
                                               const uint8_t* src,
                                               uint8_t offset,
                                               mve_pred16_t pred)
{
    dst->r = vldrbq_gather_offset_z(src + 3, AIPL_OFFSETS_U8(offset, 4), pred);
    dst->g = vldrbq_gather_offset_z(src + 2, AIPL_OFFSETS_U8(offset, 4), pred);
    dst->b = vldrbq_gather_offset_z(src + 1, AIPL_OFFSETS_U8(offset, 4), pred);
}

/**
 * Load 16 RGBA4444 pixels without alpha channel
 *
 * @param dst   destination struct pointer
 * @param src   first source pixel pointer
 * @param pred  load predicate
 */
INLINE void aipl_mve_load_rgba4444_16px(aipl_mve_rgb_x16_t* dst,
                                        const uint8_t* src,
                                        mve_pred16_t pred)
{
    uint8x16_t rg = vldrbq_gather_offset_z(src + 1, AIPL_2_BYTE_OFFSETS_U8, pred);
    uint8x16_t ba = vldrbq_gather_offset_z(src, AIPL_2_BYTE_OFFSETS_U8, pred);

    dst->r = vandq(rg, vdupq_n_u8(0xf0));
    dst->g = vshlq_n(rg, 4);
    dst->b = vandq(ba, vdupq_n_u8(0xf0));
}

/**
 * Load 16 RGBA4444 pixels without alpha channel
 * and with custom offsets between pixels
 *
 * @param dst       destination struct pointer
 * @param src       first source pixel pointer
 * @param offset    pixel offset
 * @param pred      load predicate
 */
INLINE void aipl_mve_load_rgba4444_offset_16px(aipl_mve_rgb_x16_t* dst,
                                               const uint8_t* src,
                                               uint8_t offset,
                                               mve_pred16_t pred)
{
    uint8x16_t rg = vldrbq_gather_offset_z(src + 1, AIPL_OFFSETS_U8(offset, 2), pred);
    uint8x16_t ba = vldrbq_gather_offset_z(src, AIPL_OFFSETS_U8(offset, 2), pred);

    dst->r = vandq(rg, vdupq_n_u8(0xf0));
    dst->g = vshlq_n(rg, 4);
    dst->b = vandq(ba, vdupq_n_u8(0xf0));
}

/**
 * Load 16 RGBA5551 pixels without alpha channel
 *
 * @param dst   destination struct pointer
 * @param src   first source pixel pointer
 * @param pred  load predicate
 */
INLINE void aipl_mve_load_rgba5551_16px(aipl_mve_rgb_x16_t* dst,
                                        const uint8_t* src,
                                        mve_pred16_t pred)
{
    uint8x16_t upper = vldrbq_gather_offset_z(src + 1, AIPL_2_BYTE_OFFSETS_U8, pred);
    uint8x16_t lower = vldrbq_gather_offset_z(src, AIPL_2_BYTE_OFFSETS_U8, pred);

    dst->r = vandq(upper, vdupq_n_u8(0xf8));
    dst->g = vorrq(vshlq_n(upper, 5), vshrq(vandq(lower, vdupq_n_u8(0xc0)), 3));
    dst->b = vshlq_n(vandq(lower, vdupq_n_u8(0x3e)), 2);
}


/**
 * Load 16 RGBA5551 pixels without alpha channel
 * and with custom offsets between pixels
 *
 * @param dst       destination struct pointer
 * @param src       first source pixel pointer
 * @param offset    pixel offset
 * @param pred      load predicate
 */
INLINE void aipl_mve_load_rgba5551_offset_16px(aipl_mve_rgb_x16_t* dst,
                                               const uint8_t* src,
                                               uint8_t offset,
                                               mve_pred16_t pred)
{
    uint8x16_t upper = vldrbq_gather_offset_z(src + 1, AIPL_OFFSETS_U8(offset, 2), pred);
    uint8x16_t lower = vldrbq_gather_offset_z(src, AIPL_OFFSETS_U8(offset, 2), pred);

    dst->r = vandq(upper, vdupq_n_u8(0xf8));
    dst->g = vorrq(vshlq_n(upper, 5), vshrq(vandq(lower, vdupq_n_u8(0xc0)), 3));
    dst->b = vshlq_n(vandq(lower, vdupq_n_u8(0x3e)), 2);
}


/**
 * Load 16 RGB888 pixels
 *
 * @param dst   destination struct pointer
 * @param src   first source pixel pointer
 * @param pred  load predicate
 */
INLINE void aipl_mve_load_rgb888_16px(aipl_mve_rgb_x16_t* dst,
                                      const uint8_t* src,
                                      mve_pred16_t pred)
{
    // NOTE: local viewfinder change (use RGB instead of BGR order)
    dst->r = vldrbq_gather_offset_z(src + 0, AIPL_3_BYTE_OFFSETS_U8, pred);
    dst->g = vldrbq_gather_offset_z(src + 1, AIPL_3_BYTE_OFFSETS_U8, pred);
    dst->b = vldrbq_gather_offset_z(src + 2, AIPL_3_BYTE_OFFSETS_U8, pred);
}

/**
 * Load 16 RGB888 pixels with custom offsets between pixels
 *
 * @param dst       destination struct pointer
 * @param src       first source pixel pointer
 * @param offset    pixel offset
 * @param pred      load predicate
 */
INLINE void aipl_mve_load_rgb888_offset_16px(aipl_mve_rgb_x16_t* dst,
                                             const uint8_t* src,
                                             uint8_t offset,
                                             mve_pred16_t pred)
{
    // NOTE: local viewfinder change (use RGB instead of BGR order)
    dst->r = vldrbq_gather_offset_z(src + 0, AIPL_OFFSETS_U8(offset, 3), pred);
    dst->g = vldrbq_gather_offset_z(src + 1, AIPL_OFFSETS_U8(offset, 3), pred);
    dst->b = vldrbq_gather_offset_z(src + 2, AIPL_OFFSETS_U8(offset, 3), pred);
}

/**
 * Load 16 RGB565 pixels
 *
 * @param dst   destination struct pointer
 * @param src   first source pixel pointer
 * @param pred  load predicate
 */
INLINE void aipl_mve_load_rgb565_16px(aipl_mve_rgb_x16_t* dst,
                                      const uint8_t* src,
                                      mve_pred16_t pred)
{
    uint8x16_t upper = vldrbq_gather_offset_z(src + 1, AIPL_2_BYTE_OFFSETS_U8, pred);
    uint8x16_t lower = vldrbq_gather_offset_z(src, AIPL_2_BYTE_OFFSETS_U8, pred);

    dst->r = vandq(upper, vdupq_n_u8(0xf8));
    dst->g = vorrq(vshlq_n(upper, 5), vshrq(vandq(lower, vdupq_n_u8(0xe0)), 3));
    dst->b = vshlq_n(lower, 3);
}

/**
 * Load 16 RGB565 pixels with custom offsets between pixels
 *
 * @param dst       destination struct pointer
 * @param src       first source pixel pointer
 * @param offset    pixel offset
 * @param pred      load predicate
 */
INLINE void aipl_mve_load_rgb565_offset_16px(aipl_mve_rgb_x16_t* dst,
                                             const uint8_t* src,
                                             uint8_t offset,
                                             mve_pred16_t pred)
{
    uint8x16_t upper = vldrbq_gather_offset_z(src + 1, AIPL_OFFSETS_U8(offset, 2), pred);
    uint8x16_t lower = vldrbq_gather_offset_z(src, AIPL_OFFSETS_U8(offset, 2), pred);

    dst->r = vandq(upper, vdupq_n_u8(0xf8));
    dst->g = vorrq(vshlq_n(upper, 5), vshrq(vandq(lower, vdupq_n_u8(0xe0)), 3));
    dst->b = vshlq_n(lower, 3);
}

/**
 * Store 16 ARGB8888 pixels without alpha channel
 *
 * @param dst   first destination pixel pointer
 * @param src   source struct pointer
 * @param pred  store predicate
 */
INLINE void aipl_mve_store_argb8888_16px(uint8_t* dst,
                                         const aipl_mve_rgb_x16_t* src,
                                         mve_pred16_t pred)
{
    vstrbq_scatter_offset_p(dst + 3, AIPL_4_BYTE_OFFSETS_U8, vdupq_n_u8(0xff), pred);
    vstrbq_scatter_offset_p(dst + 2, AIPL_4_BYTE_OFFSETS_U8, src->r, pred);
    vstrbq_scatter_offset_p(dst + 1, AIPL_4_BYTE_OFFSETS_U8, src->g, pred);
    vstrbq_scatter_offset_p(dst, AIPL_4_BYTE_OFFSETS_U8, src->b, pred);
}

/**
 * Store 16 ARGB8888 pixels without alpha channel
 * and custom offset between pixels
 *
 * @param dst       first destination pixel pointer
 * @param src       source struct pointer
 * @param offset    pixel offset
 * @param pred      store predicate
 */
INLINE void aipl_mve_store_argb8888_offset_16px(uint8_t* dst,
                                                const aipl_mve_rgb_x16_t* src,
                                                uint8_t offset,
                                                mve_pred16_t pred)
{
    vstrbq_scatter_offset_p(dst + 3, AIPL_OFFSETS_U8(offset, 4), vdupq_n_u8(0xff), pred);
    vstrbq_scatter_offset_p(dst + 2, AIPL_OFFSETS_U8(offset, 4), src->r, pred);
    vstrbq_scatter_offset_p(dst + 1, AIPL_OFFSETS_U8(offset, 4), src->g, pred);
    vstrbq_scatter_offset_p(dst, AIPL_OFFSETS_U8(offset, 4), src->b, pred);
}

/**
 * Store 16 ARGB4444 pixels without alpha channel
 *
 * @param dst   first destination pixel pointer
 * @param src   source struct pointer
 * @param pred  store predicate
 */
INLINE void aipl_mve_store_argb4444_16px(uint8_t* dst,
                                         const aipl_mve_rgb_x16_t* src,
                                         mve_pred16_t pred)
{
    uint8x16_t ar = vsriq(vdupq_n_u8(0xf0), src->r, 4);
    uint8x16_t gb = vsriq(src->g, src->b, 4);

    vstrbq_scatter_offset_p(dst + 1, AIPL_2_BYTE_OFFSETS_U8, ar, pred);
    vstrbq_scatter_offset_p(dst, AIPL_2_BYTE_OFFSETS_U8, gb, pred);
}

/**
 * Store 16 ARGB4444 pixels without alpha channel
 * and custom offset between pixels
 *
 * @param dst       first destination pixel pointer
 * @param src       source struct pointer
 * @param offset    pixel offset
 * @param pred      store predicate
 */
INLINE void aipl_mve_store_argb4444_offset_16px(uint8_t* dst,
                                                const aipl_mve_rgb_x16_t* src,
                                                uint8_t offset,
                                                mve_pred16_t pred)
{
    uint8x16_t ar = vsriq(vdupq_n_u8(0xf0), src->r, 4);
    uint8x16_t gb = vsriq(src->g, src->b, 4);

    vstrbq_scatter_offset_p(dst + 1, AIPL_OFFSETS_U8(offset, 2), ar, pred);
    vstrbq_scatter_offset_p(dst, AIPL_OFFSETS_U8(offset, 2), gb, pred);
}

/**
 * Store 16 ARGB1555 pixels without alpha channel
 *
 * @param dst   first destination pixel pointer
 * @param src   source struct pointer
 * @param pred  store predicate
 */
INLINE void aipl_mve_store_argb1555_16px(uint8_t* dst,
                                         const aipl_mve_rgb_x16_t* src,
                                         mve_pred16_t pred)
{
    uint8x16_t upper = vsriq(vdupq_n_u8(0x80), src->r, 1);
    upper = vsriq(upper, src->g, 6);
    uint8x16_t lower = vshlq_n(src->g, 2);
    lower = vsriq(lower, src->b, 3);

    vstrbq_scatter_offset_p(dst + 1, AIPL_2_BYTE_OFFSETS_U8, upper, pred);
    vstrbq_scatter_offset_p(dst, AIPL_2_BYTE_OFFSETS_U8, lower, pred);
}

/**
 * Store 16 ARGB1555 pixels without alpha channel
 * and custom offset between pixels
 *
 * @param dst       first destination pixel pointer
 * @param src       source struct pointer
 * @param offset    pixel offset
 * @param pred      store predicate
 */
INLINE void aipl_mve_store_argb1555_offset_16px(uint8_t* dst,
                                                const aipl_mve_rgb_x16_t* src,
                                                uint8_t offset,
                                                mve_pred16_t pred)
{
    uint8x16_t upper = vsriq(vdupq_n_u8(0x80), src->r, 1);
    upper = vsriq(upper, src->g, 6);
    uint8x16_t lower = vshlq_n(src->g, 2);
    lower = vsriq(lower, src->b, 3);

    vstrbq_scatter_offset_p(dst + 1, AIPL_OFFSETS_U8(offset, 2), upper, pred);
    vstrbq_scatter_offset_p(dst, AIPL_OFFSETS_U8(offset, 2), lower, pred);
}

/**
 * Store 16 RGBA8888 pixels without alpha channel
 *
 * @param dst   first destination pixel pointer
 * @param src   source struct pointer
 * @param pred  store predicate
 */
INLINE void aipl_mve_store_rgba8888_16px(uint8_t* dst,
                                         const aipl_mve_rgb_x16_t* src,
                                         mve_pred16_t pred)
{
    vstrbq_scatter_offset_p(dst + 3, AIPL_4_BYTE_OFFSETS_U8, src->r, pred);
    vstrbq_scatter_offset_p(dst + 2, AIPL_4_BYTE_OFFSETS_U8, src->g, pred);
    vstrbq_scatter_offset_p(dst + 1, AIPL_4_BYTE_OFFSETS_U8, src->b, pred);
    vstrbq_scatter_offset_p(dst, AIPL_4_BYTE_OFFSETS_U8, vdupq_n_u8(0xff), pred);
}

/**
 * Store 16 RGBA8888 pixels without alpha channel
 * and custom offset between pixels
 *
 * @param dst       first destination pixel pointer
 * @param src       source struct pointer
 * @param offset    pixel offset
 * @param pred      store predicate
 */
INLINE void aipl_mve_store_rgba8888_offset_16px(uint8_t* dst,
                                                const aipl_mve_rgb_x16_t* src,
                                                uint8_t offset,
                                                mve_pred16_t pred)
{
    vstrbq_scatter_offset_p(dst + 3, AIPL_OFFSETS_U8(offset, 4), src->r, pred);
    vstrbq_scatter_offset_p(dst + 2, AIPL_OFFSETS_U8(offset, 4), src->g, pred);
    vstrbq_scatter_offset_p(dst + 1, AIPL_OFFSETS_U8(offset, 4), src->b, pred);
    vstrbq_scatter_offset_p(dst, AIPL_OFFSETS_U8(offset, 4), vdupq_n_u8(0xff), pred);
}

/**
 * Store 16 RGBA4444 pixels without alpha channel
 *
 * @param dst   first destination pixel pointer
 * @param src   source struct pointer
 * @param pred  store predicate
 */
INLINE void aipl_mve_store_rgba4444_16px(uint8_t* dst,
                                         const aipl_mve_rgb_x16_t* src,
                                         mve_pred16_t pred)
{
    uint8x16_t rg = vsriq(src->r, src->g, 4);
    uint8x16_t ba = vsriq(src->b, vdupq_n_u8(0xff), 4);

    vstrbq_scatter_offset_p(dst + 1, AIPL_2_BYTE_OFFSETS_U8, rg, pred);
    vstrbq_scatter_offset_p(dst, AIPL_2_BYTE_OFFSETS_U8, ba, pred);
}

/**
 * Store 16 RGBA4444 pixels without alpha channel
 * and custom offset between pixels
 *
 * @param dst       first destination pixel pointer
 * @param src       source struct pointer
 * @param offset    pixel offset
 * @param pred      store predicate
 */
INLINE void aipl_mve_store_rgba4444_offset_16px(uint8_t* dst,
                                                const aipl_mve_rgb_x16_t* src,
                                                uint8_t offset,
                                                mve_pred16_t pred)
{
    uint8x16_t rg = vsriq(src->r, src->g, 4);
    uint8x16_t ba = vsriq(src->b, vdupq_n_u8(0xff), 4);

    vstrbq_scatter_offset_p(dst + 1, AIPL_OFFSETS_U8(offset, 2), rg, pred);
    vstrbq_scatter_offset_p(dst, AIPL_OFFSETS_U8(offset, 2), ba, pred);
}

/**
 * Store 16 RGBA5551 pixels without alpha channel
 *
 * @param dst   first destination pixel pointer
 * @param src   source struct pointer
 * @param pred  store predicate
 */
INLINE void aipl_mve_store_rgba5551_16px(uint8_t* dst,
                                         const aipl_mve_rgb_x16_t* src,
                                         mve_pred16_t pred)
{
    uint8x16_t upper = vsriq(src->r, src->g, 5);
    uint8x16_t lower = vshlq_n(src->g, 3);
    lower = vsriq(lower, src->b, 2);
    lower = vorrq(lower, vdupq_n_u8(0x01));

    vstrbq_scatter_offset_p(dst + 1, AIPL_2_BYTE_OFFSETS_U8, upper, pred);
    vstrbq_scatter_offset_p(dst, AIPL_2_BYTE_OFFSETS_U8, lower, pred);
}

/**
 * Store 16 RGBA5551 pixels without alpha channel
 * and custom offset between pixels
 *
 * @param dst       first destination pixel pointer
 * @param src       source struct pointer
 * @param offset    pixel offset
 * @param pred      store predicate
 */
INLINE void aipl_mve_store_rgba5551_offset_16px(uint8_t* dst,
                                                const aipl_mve_rgb_x16_t* src,
                                                uint8_t offset,
                                                mve_pred16_t pred)
{
    uint8x16_t upper = vsriq(src->r, src->g, 5);
    uint8x16_t lower = vshlq_n(src->g, 3);
    lower = vsriq(lower, src->b, 2);
    lower = vorrq(lower, vdupq_n_u8(0x01));

    vstrbq_scatter_offset_p(dst + 1, AIPL_OFFSETS_U8(offset, 2), upper, pred);
    vstrbq_scatter_offset_p(dst, AIPL_OFFSETS_U8(offset, 2), lower, pred);
}

/**
 * Store 16 RGB888 pixels without alpha channel
 * and custom offset between pixels
 *
 * @param dst       first destination pixel pointer
 * @param src       source struct pointer
 * @param offset    pixel offset
 * @param pred      store predicate
 */
INLINE void aipl_mve_store_rgb888_offset_16px(uint8_t* dst,
                                              const aipl_mve_rgb_x16_t* src,
                                              uint8_t offset,
                                              mve_pred16_t pred)
{
    vstrbq_scatter_offset_p(dst + 2, AIPL_OFFSETS_U8(offset, 3), src->r, pred);
    vstrbq_scatter_offset_p(dst + 1, AIPL_OFFSETS_U8(offset, 3), src->g, pred);
    vstrbq_scatter_offset_p(dst, AIPL_OFFSETS_U8(offset, 3), src->b, pred);
}

/**
 * Store 16 RGB565 pixels without alpha channel
 * and custom offset between pixels
 *
 * @param dst       first destination pixel pointer
 * @param src       source struct pointer
 * @param offset    pixel offset
 * @param pred      store predicate
 */
INLINE void aipl_mve_store_rgb565_offset_16px(uint8_t* dst,
                                              const aipl_mve_rgb_x16_t* src,
                                              uint8_t offset,
                                              mve_pred16_t pred)
{
    uint8x16_t upper = vsriq(src->r, src->g, 5);
    uint8x16_t lower = vshlq_n(src->g, 3);
    lower = vsriq(lower, src->b, 3);

    vstrbq_scatter_offset_p(dst + 1, AIPL_OFFSETS_U8(offset, 2), upper, pred);
    vstrbq_scatter_offset_p(dst, AIPL_OFFSETS_U8(offset, 2), lower, pred);
}

/**
 * Store 8 ARGB8888 pixels with alpha channel
 *
 * @param dst   first destination pixel pointer
 * @param src   source struct pointer
 * @param pred  store predicate
 */
INLINE void aipl_mve_storea_argb8888_8px(uint8_t* dst,
                                         const aipl_mve_argb_x8_t* src,
                                         mve_pred16_t pred)
{
    vstrbq_scatter_offset_p(dst + 3, AIPL_4_BYTE_OFFSETS_U16, src->a, pred);
    vstrbq_scatter_offset_p(dst + 2, AIPL_4_BYTE_OFFSETS_U16, src->r, pred);
    vstrbq_scatter_offset_p(dst + 1, AIPL_4_BYTE_OFFSETS_U16, src->g, pred);
    vstrbq_scatter_offset_p(dst, AIPL_4_BYTE_OFFSETS_U16, src->b, pred);
}

/**
 * Store 16 ARGB8888 pixels with alpha channel
 *
 * @param dst   first destination pixel pointer
 * @param src   source struct pointer
 * @param pred  store predicate
 */
INLINE void aipl_mve_storea_argb8888_16px(uint8_t* dst,
                                          const aipl_mve_argb_x16_t* src,
                                          mve_pred16_t pred)
{
    vstrbq_scatter_offset_p(dst + 3, AIPL_4_BYTE_OFFSETS_U8, src->a, pred);
    vstrbq_scatter_offset_p(dst + 2, AIPL_4_BYTE_OFFSETS_U8, src->r, pred);
    vstrbq_scatter_offset_p(dst + 1, AIPL_4_BYTE_OFFSETS_U8, src->g, pred);
    vstrbq_scatter_offset_p(dst, AIPL_4_BYTE_OFFSETS_U8, src->b, pred);
}

/**
 * Store 8 ARGB4444 pixels with alpha channel
 *
 * @param dst   first destination pixel pointer
 * @param src   source struct pointer
 * @param pred  store predicate
 */
INLINE void aipl_mve_storea_argb4444_8px(uint16_t* dst,
                                         const aipl_mve_argb_x8_t* src,
                                         mve_pred16_t pred)
{
    uint8x16_t ar = vreinterpretq_u8(src->a);
    ar = vsriq(ar, vreinterpretq_u8(src->r), 4);
    uint8x16_t gb = vreinterpretq_u8(src->g);
    gb = vsriq(gb, vreinterpretq_u8(src->b), 4);
    uint16x8_t pix = vreinterpretq_u16(vmovntq(gb, vreinterpretq_u16(ar)));

    vst1q_p(dst, pix, pred);
}

/**
 * Store 16 ARGB4444 pixels with alpha channel
 *
 * @param dst   first destination pixel pointer
 * @param src   source struct pointer
 * @param pred  store predicate
 */
INLINE void aipl_mve_storea_argb4444_16px(uint8_t* dst,
                                          const aipl_mve_argb_x16_t* src,
                                          mve_pred16_t pred)
{
    uint8x16_t ar = vsriq(src->a, src->r, 4);
    uint8x16_t gb = vsriq(src->g, src->b, 4);

    vstrbq_scatter_offset_p(dst + 1, AIPL_2_BYTE_OFFSETS_U8, ar, pred);
    vstrbq_scatter_offset_p(dst, AIPL_2_BYTE_OFFSETS_U8, gb, pred);
}

/**
 * Store 16 ARGB1555 pixels with alpha channel
 *
 * @param dst   first destination pixel pointer
 * @param src   source struct pointer
 * @param pred  store predicate
 */
INLINE void aipl_mve_storea_argb1555_16px(uint8_t* dst,
                                          const aipl_mve_argb_x16_t* src,
                                          mve_pred16_t pred)
{
    uint8x16_t upper = vsriq(src->a, src->r, 1);
    upper = vsriq(upper, src->g, 6);
    uint8x16_t lower = vshlq_n(src->g, 2);
    lower = vsriq(lower, src->b, 3);

    vstrbq_scatter_offset_p(dst + 1, AIPL_2_BYTE_OFFSETS_U8, upper, pred);
    vstrbq_scatter_offset_p(dst, AIPL_2_BYTE_OFFSETS_U8, lower, pred);
}

/**
 * Store 16 RGBA8888 pixels with alpha channel
 *
 * @param dst   first destination pixel pointer
 * @param src   source struct pointer
 * @param pred  store predicate
 */
INLINE void aipl_mve_storea_rgba8888_16px(uint8_t* dst,
                                          const aipl_mve_argb_x16_t* src,
                                          mve_pred16_t pred)
{
    vstrbq_scatter_offset_p(dst + 3, AIPL_4_BYTE_OFFSETS_U8, src->r, pred);
    vstrbq_scatter_offset_p(dst + 2, AIPL_4_BYTE_OFFSETS_U8, src->g, pred);
    vstrbq_scatter_offset_p(dst + 1, AIPL_4_BYTE_OFFSETS_U8, src->b, pred);
    vstrbq_scatter_offset_p(dst, AIPL_4_BYTE_OFFSETS_U8, src->a, pred);
}

/**
 * Store 16 RGBA4444 pixels with alpha channel
 *
 * @param dst   first destination pixel pointer
 * @param src   source struct pointer
 * @param pred  store predicate
 */
INLINE void aipl_mve_storea_rgba4444_16px(uint8_t* dst,
                                          const aipl_mve_argb_x16_t* src,
                                          mve_pred16_t pred)
{
    uint8x16_t rg = vsriq(src->r, src->g, 4);
    uint8x16_t ba = vsriq(src->b, src->a, 4);

    vstrbq_scatter_offset_p(dst + 1, AIPL_2_BYTE_OFFSETS_U8, rg, pred);
    vstrbq_scatter_offset_p(dst, AIPL_2_BYTE_OFFSETS_U8, ba, pred);
}

/**
 * Store 16 RGBA5551 pixels with alpha channel
 *
 * @param dst   first destination pixel pointer
 * @param src   source struct pointer
 * @param pred  store predicate
 */
INLINE void aipl_mve_storea_rgba5551_16px(uint8_t* dst,
                                          const aipl_mve_argb_x16_t* src,
                                          mve_pred16_t pred)
{
    uint8x16_t upper = vsriq(src->r, src->g, 5);
    uint8x16_t lower = vshlq_n(src->g, 3);
    lower = vsriq(lower, src->b, 2);
    lower = vsriq(lower, src->a, 7);

    vstrbq_scatter_offset_p(dst + 1, AIPL_2_BYTE_OFFSETS_U8, upper, pred);
    vstrbq_scatter_offset_p(dst, AIPL_2_BYTE_OFFSETS_U8, lower, pred);
}

/**
 * Store 16 RGB888 pixels from ARGB struct
 *
 * @param dst   first destination pixel pointer
 * @param src   source struct pointer
 * @param pred  store predicate
 */
INLINE void aipl_mve_storea_rgb888_16px(uint8_t* dst,
                                        const aipl_mve_argb_x16_t* src,
                                        mve_pred16_t pred)
{
    vstrbq_scatter_offset_p(dst + 2, AIPL_3_BYTE_OFFSETS_U8, src->r, pred);
    vstrbq_scatter_offset_p(dst + 1, AIPL_3_BYTE_OFFSETS_U8, src->g, pred);
    vstrbq_scatter_offset_p(dst, AIPL_3_BYTE_OFFSETS_U8, src->b, pred);
}

/**
 * Store 16 RGB888 pixels from RGB struct
 *
 * @param dst   first destination pixel pointer
 * @param src   source struct pointer
 * @param pred  store predicate
 */
INLINE void aipl_mve_store_rgb888_16px(uint8_t* dst,
                                       const aipl_mve_rgb_x16_t* src,
                                       mve_pred16_t pred)
{
    vstrbq_scatter_offset_p(dst + 2, AIPL_3_BYTE_OFFSETS_U8, src->r, pred);
    vstrbq_scatter_offset_p(dst + 1, AIPL_3_BYTE_OFFSETS_U8, src->g, pred);
    vstrbq_scatter_offset_p(dst, AIPL_3_BYTE_OFFSETS_U8, src->b, pred);
}

/**
 * Store 16 RGB565 pixels from ARGB struct
 *
 * @param dst   first destination pixel pointer
 * @param src   source struct pointer
 * @param pred  store predicate
 */
INLINE void aipl_mve_storea_rgb565_16px(uint8_t* dst,
                                         const aipl_mve_argb_x16_t* src,
                                         mve_pred16_t pred)
{
    uint8x16_t upper = vsriq(src->r, src->g, 5);
    uint8x16_t lower = vshlq_n(src->g, 3);
    lower = vsriq(lower, src->b, 3);

    vstrbq_scatter_offset_p(dst + 1, AIPL_2_BYTE_OFFSETS_U8, upper, pred);
    vstrbq_scatter_offset_p(dst, AIPL_2_BYTE_OFFSETS_U8, lower, pred);
}

/**
 * Store 16 RGB565 pixels from RGB struct
 *
 * @param dst   first destination pixel pointer
 * @param src   source struct pointer
 * @param pred  store predicate
 */
INLINE void aipl_mve_store_rgb565_16px(uint8_t* dst,
                                       const aipl_mve_rgb_x16_t* src,
                                       mve_pred16_t pred)
{
    uint8x16_t upper = vsriq(src->r, src->g, 5);
    uint8x16_t lower = vshlq_n(src->g, 3);
    lower = vsriq(lower, src->b, 3);

    vstrbq_scatter_offset_p(dst + 1, AIPL_2_BYTE_OFFSETS_U8, upper, pred);
    vstrbq_scatter_offset_p(dst, AIPL_2_BYTE_OFFSETS_U8, lower, pred);
}

/**
 * Store 8 ALPHA8 pixels
 *
 * @param dst   first destination pixel pointer
 * @param src   source struct pointer
 * @param pred  store predicate
 */
INLINE void aipl_mve_store_alpha8_8px(uint8_t* dst,
                                      const uint16x8_t* src,
                                      mve_pred16_t pred)
{
    uint16x8_t out = vreinterpretq_u16(vqmovnbq(vdupq_n_u8(0), *src));
    vstrbq_p(dst, out, pred);
}

/**
 * Store 16 ALPHA8 pixels
 *
 * @param dst   first destination pixel pointer
 * @param src   source struct pointer
 * @param pred  store predicate
 */
INLINE void aipl_mve_store_alpha8_16px(uint8_t* dst,
                                       const uint8x16_t* src,
                                       mve_pred16_t pred)
{
    vst1q_p(dst, *src, pred);
}

/**
 * Calculate Y channel for 8 pixels from ARGB struct
 *
 * @param y     Y channel struct pointer
 * @param pix   pixels struct pointer
 */
INLINE void aipl_mve_calculate_y_argb_x8(uint16x8_t* y,
                                         const aipl_mve_argb_x8_t* pix)
{
    *y = vmulq(pix->r, 66);
    *y = vmlaq(*y, pix->g, 129);
    *y = vmlaq(*y, pix->b, 25);

    *y = vshrq(vaddq(*y, 128), 8);
    *y = vaddq(*y, 16);
}

/**
 * Calculate Y channel for 8 pixels from RGB struct
 *
 * @param y     Y channel struct pointer
 * @param pix   pixels struct pointer
 */
INLINE void aipl_mve_calculate_y_rgb_x8(uint16x8_t* y,
                                        const aipl_mve_rgb_x8_t* pix)
{
    *y = vmulq(pix->r, 66);
    *y = vmlaq(*y, pix->g, 129);
    *y = vmlaq(*y, pix->b, 25);

    *y = vshrq(vaddq(*y, 128), 8);
    *y = vaddq(*y, 16);
}

/**
 * Calculate Y channel for 16 pixels from ARGB struct
 *
 * @param y     Y channel struct pointer
 * @param pix   pixels struct pointer
 */
INLINE void aipl_mve_calculate_y_argb_x16(uint8x16_t* y,
                                          const aipl_mve_argb_x16_t* pix)
{
    aipl_mve_argb_x8_t pix_t;
    aipl_mve_argb_x8_t pix_b;
    aipl_mve_convert_argb_x16_to_x8_odd(&pix_t, pix);
    aipl_mve_convert_argb_x16_to_x8_evn(&pix_b, pix);

    uint16x8_t y_t;
    uint16x8_t y_b;
    aipl_mve_calculate_y_argb_x8(&y_t, &pix_t);
    aipl_mve_calculate_y_argb_x8(&y_b, &pix_b);

    *y = vmovntq(vreinterpretq_u8(y_b), y_t);
}

/**
 * Calculate Y channel for 16 pixels from RGB struct
 *
 * @param y     Y channel struct pointer
 * @param pix   pixels struct pointer
 */
INLINE void aipl_mve_calculate_y_rgb_x16(uint8x16_t* y,
                                         const aipl_mve_rgb_x16_t* pix)
{
    aipl_mve_rgb_x8_t pix_t;
    aipl_mve_rgb_x8_t pix_b;
    aipl_mve_convert_rgb_x16_to_x8_odd(&pix_t, pix);
    aipl_mve_convert_rgb_x16_to_x8_evn(&pix_b, pix);

    uint16x8_t y_t;
    uint16x8_t y_b;
    aipl_mve_calculate_y_rgb_x8(&y_t, &pix_t);
    aipl_mve_calculate_y_rgb_x8(&y_b, &pix_b);

    *y = vmovntq(vreinterpretq_u8(y_b), y_t);
}

/**
 * Calculate U channel for 8 pixels from ARGB struct
 *
 * @param u     U channel struct pointer
 * @param pix   pixels struct pointer
 */
INLINE void aipl_mve_calculate_u_argb_x8(uint16x8_t* u,
                                         const aipl_mve_argb_x8_t* pix)
{
    *u = vmulq(pix->r, -38);
    *u = vmlaq(*u, pix->g, -74);
    *u = vmlaq(*u, pix->b, 112);

    *u = vshrq(vaddq(*u, 128), 8);
    *u = vaddq(*u, 128);
}

/**
 * Calculate U channel for 8 pixels from RGB struct
 *
 * @param u     U channel struct pointer
 * @param pix   pixels struct pointer
 */
INLINE void aipl_mve_calculate_u_rgb_x8(uint16x8_t* u,
                                        const aipl_mve_rgb_x8_t* pix)
{
    *u = vmulq(pix->r, -38);
    *u = vmlaq(*u, pix->g, -74);
    *u = vmlaq(*u, pix->b, 112);

    *u = vshrq(vaddq(*u, 128), 8);
    *u = vaddq(*u, 128);
}

/**
 * Calculate U channel for 16 pixels from ARGB struct
 *
 * @param u     U channel struct pointer
 * @param pix   pixels struct pointer
 */
INLINE void aipl_mve_calculate_u_argb_x16(uint8x16_t* u,
                                          const aipl_mve_argb_x16_t* pix)
{
    aipl_mve_argb_x8_t pix_t;
    aipl_mve_argb_x8_t pix_b;
    aipl_mve_convert_argb_x16_to_x8_odd(&pix_t, pix);
    aipl_mve_convert_argb_x16_to_x8_evn(&pix_b, pix);

    uint16x8_t u_t;
    uint16x8_t u_b;
    aipl_mve_calculate_u_argb_x8(&u_t, &pix_t);
    aipl_mve_calculate_u_argb_x8(&u_b, &pix_b);

    *u = vmovntq(vreinterpretq_u8(u_b), u_t);
}

/**
 * Calculate U channel for 16 pixels from RGB struct
 *
 * @param u     U channel struct pointer
 * @param pix   pixels struct pointer
 */
INLINE void aipl_mve_calculate_u_rgb_x16(uint8x16_t* u,
                                          const aipl_mve_rgb_x16_t* pix)
{
    aipl_mve_rgb_x8_t pix_t;
    aipl_mve_rgb_x8_t pix_b;
    aipl_mve_convert_rgb_x16_to_x8_odd(&pix_t, pix);
    aipl_mve_convert_rgb_x16_to_x8_evn(&pix_b, pix);

    uint16x8_t u_t;
    uint16x8_t u_b;
    aipl_mve_calculate_u_rgb_x8(&u_t, &pix_t);
    aipl_mve_calculate_u_rgb_x8(&u_b, &pix_b);

    *u = vmovntq(vreinterpretq_u8(u_b), u_t);
}

/**
 * Calculate V channel for 8 pixels from ARGB struct
 *
 * @param v     V channel struct pointer
 * @param pix   pixels struct pointer
 */
INLINE void aipl_mve_calculate_v_argb_x8(uint16x8_t* v,
                                         const aipl_mve_argb_x8_t* pix)
{
    *v = vmulq(pix->r, 112);
    *v = vmlaq(*v, pix->g, -94);
    *v = vmlaq(*v, pix->b, -18);

    *v = vshrq(vaddq(*v, 128), 8);
    *v = vaddq(*v, 128);
}

/**
 * Calculate V channel for 8 pixels from RGB struct
 *
 * @param v     V channel struct pointer
 * @param pix   pixels struct pointer
 */
INLINE void aipl_mve_calculate_v_rgb_x8(uint16x8_t* v,
                                        const aipl_mve_rgb_x8_t* pix)
{
    *v = vmulq(pix->r, 112);
    *v = vmlaq(*v, pix->g, -94);
    *v = vmlaq(*v, pix->b, -18);

    *v = vshrq(vaddq(*v, 128), 8);
    *v = vaddq(*v, 128);
}

/**
 * Calculate V channel for 16 pixels from ARGB struct
 *
 * @param v     V channel struct pointer
 * @param pix   pixels struct pointer
 */
INLINE void aipl_mve_calculate_v_argb_x16(uint8x16_t* v,
                                          const aipl_mve_argb_x16_t* pix)
{
    aipl_mve_argb_x8_t pix_t;
    aipl_mve_argb_x8_t pix_b;
    aipl_mve_convert_argb_x16_to_x8_odd(&pix_t, pix);
    aipl_mve_convert_argb_x16_to_x8_evn(&pix_b, pix);

    uint16x8_t v_t;
    uint16x8_t v_b;
    aipl_mve_calculate_v_argb_x8(&v_t, &pix_t);
    aipl_mve_calculate_v_argb_x8(&v_b, &pix_b);

    *v = vmovntq(vreinterpretq_u8(v_b), v_t);
}

/**
 * Calculate V channel for 16 pixels from RGB struct
 *
 * @param v     V channel struct pointer
 * @param pix   pixels struct pointer
 */
INLINE void aipl_mve_calculate_v_rgb_x16(uint8x16_t* v,
                                         const aipl_mve_rgb_x16_t* pix)
{
    aipl_mve_rgb_x8_t pix_t;
    aipl_mve_rgb_x8_t pix_b;
    aipl_mve_convert_rgb_x16_to_x8_odd(&pix_t, pix);
    aipl_mve_convert_rgb_x16_to_x8_evn(&pix_b, pix);

    uint16x8_t v_t;
    uint16x8_t v_b;
    aipl_mve_calculate_v_rgb_x8(&v_t, &pix_t);
    aipl_mve_calculate_v_rgb_x8(&v_b, &pix_b);

    *v = vmovntq(vreinterpretq_u8(v_b), v_t);
}

/**
 * Convert 4 Y, U and V channel values to R, G and B channels
 *
 * @param r     R channel destination pointer
 * @param g     G channel destination pointer
 * @param b     B channel destination pointer
 * @param y     Y channel values pointer
 * @param u     U channel values pointer
 * @param v     V channel values pointer
 */
INLINE void aipl_mve_convert_yuv_to_rgb_channels_x4(uint32x4_t* r,
                                                    uint32x4_t* g,
                                                    uint32x4_t* b,
                                                    const uint32x4_t* y,
                                                    const uint32x4_t* u,
                                                    const uint32x4_t* v)
{
    int32x4_t c = vsubq(vreinterpretq_s32(*y), 16);
    int32x4_t d = vsubq(vreinterpretq_s32(*u), 128);
    int32x4_t e = vsubq(vreinterpretq_s32(*v), 128);

    int32x4_t r_i = vmulq(c, 298);
    int32x4_t g_i = vmlaq(r_i, d, -100);
    int32x4_t b_i = vmlaq(r_i, d, 516);

    r_i = vmlaq(r_i, e, 409);
    r_i = vshrq(vaddq(r_i, 128), 8);

    g_i = vmlaq(g_i, e, -208);
    g_i = vshrq(vaddq(g_i, 128), 8);

    b_i = vshrq(vaddq(b_i, 128), 8);

    *r = vreinterpretq_u32(vqmovunbq((vdupq_n_u16(0)), r_i));
    *g = vreinterpretq_u32(vqmovunbq((vdupq_n_u16(0)), g_i));
    *b = vreinterpretq_u32(vqmovunbq((vdupq_n_u16(0)), b_i));
}

/**
 * Convert 4 Y, U and V channel values to RGB pixels
 *
 * @param pix   RGB struct pointer
 * @param y     Y channel values pointer
 * @param u     U channel values pointer
 * @param v     V channel values pointer
 */
INLINE void aipl_mve_convert_yuv_to_rgb_x4(aipl_mve_rgb_x4_t* pix,
                                           const uint32x4_t* y,
                                           const uint32x4_t* u,
                                           const uint32x4_t* v)
{
    aipl_mve_convert_yuv_to_rgb_channels_x4(&pix->r, &pix->g, &pix->b,
                                            y, u , v);
}

/**
 * Convert 8 Y, U and V channel values to RGB pixels
 *
 * @param pix   RGB struct pointer
 * @param y     Y channel values pointer
 * @param u     U channel values pointer
 * @param v     V channel values pointer
 */
INLINE void aipl_mve_convert_yuv_to_rgb_x8(aipl_mve_rgb_x8_t* pix,
                                           const uint16x8_t* y,
                                           const uint16x8_t* u,
                                           const uint16x8_t* v)
{
    uint32x4_t y_t = vmovltq(*y);
    uint32x4_t y_b = vmovlbq(*y);
    uint32x4_t u_t = vmovltq(*u);
    uint32x4_t u_b = vmovlbq(*u);
    uint32x4_t v_t = vmovltq(*v);
    uint32x4_t v_b = vmovlbq(*v);

    aipl_mve_rgb_x4_t pix_t;
    aipl_mve_rgb_x4_t pix_b;
    aipl_mve_convert_yuv_to_rgb_x4(&pix_t, &y_t, &u_t, &v_t);
    aipl_mve_convert_yuv_to_rgb_x4(&pix_b, &y_b, &u_b, &v_b);

    aipl_mve_convert_2_rgb_x4_to_x8(pix, &pix_b, &pix_t);
}

/**
 * Convert 16 Y, U and V channel values to RGB pixels
 *
 * @param pix   RGB struct pointer
 * @param y     Y channel values pointer
 * @param u     U channel values pointer
 * @param v     V channel values pointer
 */
INLINE void aipl_mve_convert_yuv_to_rgb_x16(aipl_mve_rgb_x16_t* pix,
                                            const uint8x16_t* y,
                                            const uint8x16_t* u,
                                            const uint8x16_t* v)
{
    uint16x8_t y_t = vmovltq(*y);
    uint16x8_t y_b = vmovlbq(*y);
    uint16x8_t u_t = vmovltq(*u);
    uint16x8_t u_b = vmovlbq(*u);
    uint16x8_t v_t = vmovltq(*v);
    uint16x8_t v_b = vmovlbq(*v);

    aipl_mve_rgb_x8_t pix_t;
    aipl_mve_rgb_x8_t pix_b;
    aipl_mve_convert_yuv_to_rgb_x8(&pix_t, &y_t, &u_t, &v_t);
    aipl_mve_convert_yuv_to_rgb_x8(&pix_b, &y_b, &u_b, &v_b);

    aipl_mve_convert_2_rgb_x8_to_x16(pix, &pix_b, &pix_t);
}

/**
 * Convert 16 alpha channel values to RGB pixels
 *
 * @param pix   RGB struct pointer
 * @param alpha Y channel values pointer
 */
INLINE void aipl_mve_convert_alpha_to_rgb_x16(aipl_mve_rgb_x16_t* pix,
                                              const uint8x16_t* alpha)
{
    pix->r = *alpha;
    pix->g = *alpha;
    pix->b = *alpha;
}

/**
 * Peform color correction on 8 sets of R, G and B channels
 *
 * @param r     R channel vector pointer
 * @param g     G channel vector pointer
 * @param b     B channel vector pointer
 * @param ccm   color correcion matrix
 */
INLINE void aipl_mve_color_correction_rgb_channels_x8(uint16x8_t* r,
                                                      uint16x8_t* g,
                                                      uint16x8_t* b,
                                                      const float* ccm)
{
    float16x8_t r_f = vcvtq(*r);
    float16x8_t g_f = vcvtq(*g);
    float16x8_t b_f = vcvtq(*b);

    float16x8_t r_mac = vmulq(r_f, ccm[0]);
    r_mac = vfmaq(r_mac, g_f, ccm[1]);
    r_mac = vfmaq(r_mac, b_f, ccm[2]);

    uint16x8_t r_out = vcvtq_u16_f16(r_mac);
    *r = vreinterpretq_u16(vqmovnbq(vdupq_n_u8(0), r_out));

    float16x8_t g_mac = vmulq(r_f, ccm[3]);
    g_mac = vfmaq(g_mac, g_f, ccm[4]);
    g_mac = vfmaq(g_mac, b_f, ccm[5]);

    uint16x8_t g_out = vcvtq_u16_f16(g_mac);
    *g = vreinterpretq_u16(vqmovnbq(vdupq_n_u8(0), g_out));

    float16x8_t b_mac = vmulq(r_f, ccm[6]);
    b_mac = vfmaq(b_mac, g_f, ccm[7]);
    b_mac = vfmaq(b_mac, b_f, ccm[8]);

    uint16x8_t b_out = vcvtq_u16_f16(b_mac);
    *b = vreinterpretq_u16(vqmovnbq(vdupq_n_u8(0), b_out));
}

/**
 * Perform color correction on 8 ARGB pixels
 *
 * @param pix   pixels struct pointer
 * @param ccm   color correction matrix
 */
INLINE void aipl_mve_color_correction_argb_x8(aipl_mve_argb_x8_t* pix,
                                              const float* ccm)
{
    aipl_mve_color_correction_rgb_channels_x8(&pix->r, &pix->g, &pix->b, ccm);
}

/**
 * Perform color correction on 16 ARGB pixels
 *
 * @param pix   pixels struct pointer
 * @param ccm   color correction matrix
 */
INLINE void aipl_mve_color_correction_argb_x16(aipl_mve_argb_x16_t* pix,
                                                const float* ccm)
{
    aipl_mve_argb_x8_t pix_t;
    aipl_mve_argb_x8_t pix_b;
    aipl_mve_convert_argb_x16_to_x8_odd(&pix_t, pix);
    aipl_mve_convert_argb_x16_to_x8_evn(&pix_b, pix);

    aipl_mve_color_correction_argb_x8(&pix_t, ccm);
    aipl_mve_color_correction_argb_x8(&pix_b, ccm);

    aipl_mve_convert_2_argb_x8_to_x16(pix, &pix_b, &pix_t);
}

/**
 * Perform color correction on 8 RGB pixels
 *
 * @param pix   pixels struct pointer
 * @param ccm   color correction matrix
 */
INLINE void aipl_mve_color_correction_rgb_x8(aipl_mve_rgb_x8_t* pix,
                                             const float* ccm)
{
    aipl_mve_color_correction_rgb_channels_x8(&pix->r, &pix->g, &pix->b, ccm);
}

/**
 * Perform color correction on 16 RGB pixels
 *
 * @param pix   pixels struct pointer
 * @param ccm   color correction matrix
 */
INLINE void aipl_mve_color_correction_rgb_x16(aipl_mve_rgb_x16_t* pix,
                                              const float* ccm)
{
    aipl_mve_rgb_x8_t pix_t;
    aipl_mve_rgb_x8_t pix_b;
    aipl_mve_convert_rgb_x16_to_x8_odd(&pix_t, pix);
    aipl_mve_convert_rgb_x16_to_x8_evn(&pix_b, pix);

    aipl_mve_color_correction_rgb_x8(&pix_t, ccm);
    aipl_mve_color_correction_rgb_x8(&pix_b, ccm);

    aipl_mve_convert_2_rgb_x8_to_x16(pix, &pix_b, &pix_t);
}

/**
 * Perform white balance on on 8 sets of R, G and B channels
 *
 * @param r     R channel vector pointer
 * @param g     G channel vector pointer
 * @param b     B channel vector pointer
 * @param ar    red channel multiplier
 * @param ag    green channel multiplier
 * @param ab    blue channel multiplier
 */
INLINE void aipl_mve_white_balance_rgb_channels_x8(uint16x8_t* r,
                                                   uint16x8_t* g,
                                                   uint16x8_t* b,
                                                   float ar, float ag, float ab)
{
    float16x8_t r_f = vcvtq(*r);
    float16x8_t g_f = vcvtq(*g);
    float16x8_t b_f = vcvtq(*b);

    float16x8_t r_mul = vmulq(r_f, ar);

    uint16x8_t r_out = vcvtq_u16_f16(r_mul);
    *r = vreinterpretq_u16(vqmovnbq(vdupq_n_u8(0), r_out));

    float16x8_t g_mul = vmulq(g_f, ag);

    uint16x8_t g_out = vcvtq_u16_f16(g_mul);
    *g = vreinterpretq_u16(vqmovnbq(vdupq_n_u8(0), g_out));

    float16x8_t b_mul = vmulq(b_f, ab);

    uint16x8_t b_out = vcvtq_u16_f16(b_mul);
    *b = vreinterpretq_u16(vqmovnbq(vdupq_n_u8(0), b_out));
}

/**
 * Perform white balance on 8 ARGB pixels
 *
 * @param pix   pixels struct pointer
 * @param ar    red channel multiplier
 * @param ag    green channel multiplier
 * @param ab    blue channel multiplier
 */
INLINE void aipl_mve_white_balance_argb_x8(aipl_mve_argb_x8_t* pix,
                                           float ar, float ag, float ab)
{
    aipl_mve_white_balance_rgb_channels_x8(&pix->r, &pix->g, &pix->b,
                                           ar, ag, ab);
}

/**
 * Perform white balance on 16 ARGB pixels
 *
 * @param pix   pixels struct pointer
 * @param ar    red channel multiplier
 * @param ag    green channel multiplier
 * @param ab    blue channel multiplier
 */
INLINE void aipl_mve_white_balance_argb_x16(aipl_mve_argb_x16_t* pix,
                                            float ar, float ag, float ab)
{
    aipl_mve_argb_x8_t pix_t;
    aipl_mve_argb_x8_t pix_b;
    aipl_mve_convert_argb_x16_to_x8_odd(&pix_t, pix);
    aipl_mve_convert_argb_x16_to_x8_evn(&pix_b, pix);

    aipl_mve_white_balance_argb_x8(&pix_t, ar, ag, ab);
    aipl_mve_white_balance_argb_x8(&pix_b, ar, ag, ab);

    aipl_mve_convert_2_argb_x8_to_x16(pix, &pix_b, &pix_t);

}

/**
 * Perform white balance on 8 RGB pixels
 *
 * @param pix   pixels struct pointer
 * @param ar    red channel multiplier
 * @param ag    green channel multiplier
 * @param ab    blue channel multiplier
 */
INLINE void aipl_mve_white_balance_rgb_x8(aipl_mve_rgb_x8_t* pix,
                                          float ar, float ag, float ab)
{
    aipl_mve_white_balance_rgb_channels_x8(&pix->r, &pix->g, &pix->b,
                                           ar, ag, ab);
}

/**
 * Perform white balance on 16 RGB pixels
 *
 * @param pix   pixels struct pointer
 * @param ar    red channel multiplier
 * @param ag    green channel multiplier
 * @param ab    blue channel multiplier
 */
INLINE void aipl_mve_white_balance_rgb_x16(aipl_mve_rgb_x16_t* pix,
                                           float ar, float ag, float ab)
{
    aipl_mve_rgb_x8_t pix_t;
    aipl_mve_rgb_x8_t pix_b;
    aipl_mve_convert_rgb_x16_to_x8_odd(&pix_t, pix);
    aipl_mve_convert_rgb_x16_to_x8_evn(&pix_b, pix);

    aipl_mve_white_balance_rgb_x8(&pix_t, ar, ag, ab);
    aipl_mve_white_balance_rgb_x8(&pix_b, ar, ag, ab);

    aipl_mve_convert_2_rgb_x8_to_x16(pix, &pix_b, &pix_t);
}

/**
 * Perform gamma correction on on 8 sets of R, G and B channels
 *
 * @param r     R channel vector pointer
 * @param g     G channel vector pointer
 * @param b     B channel vector pointer
 * @param lut   gamma lookup table
 */
INLINE void aipl_mve_lut_transform_rgb_channels_x8(uint16x8_t* r,
                                                   uint16x8_t* g,
                                                   uint16x8_t* b,
                                                   uint8_t* lut)
{
    *r = vldrbq_gather_offset(lut, *r);
    *g = vldrbq_gather_offset(lut, *g);
    *b = vldrbq_gather_offset(lut, *b);
}

/**
 * Perform gamma correction on 16 sets of R, G and B channels
 *
 * @param r     R channel vector pointer
 * @param g     G channel vector pointer
 * @param b     B channel vector pointer
 * @param lut   gamma lookup table
 */
INLINE void aipl_mve_lut_transform_rgb_channels_x16(uint8x16_t* r,
                                                    uint8x16_t* g,
                                                    uint8x16_t* b,
                                                    uint8_t* lut)
{
    *r = vldrbq_gather_offset(lut, *r);
    *g = vldrbq_gather_offset(lut, *g);
    *b = vldrbq_gather_offset(lut, *b);
}

/**
 * Perform gamma correction on 8 ARGB pixels
 *
 * @param pix   pixels struct pointer
 * @param lut   gamma lookup table
 */
INLINE void aipl_mve_lut_transform_argb_x8(aipl_mve_argb_x8_t* pix,
                                           uint8_t* lut)
{
    aipl_mve_lut_transform_rgb_channels_x8(&pix->r, &pix->g, &pix->b, lut);
}

/**
 * Perform gamma correction on 16 ARGB pixels
 *
 * @param pix   pixels struct pointer
 * @param lut   gamma lookup table
 */
INLINE void aipl_mve_lut_transform_argb_x16(aipl_mve_argb_x16_t* pix,
                                            uint8_t* lut)
{
    aipl_mve_lut_transform_rgb_channels_x16(&pix->r, &pix->g, &pix->b, lut);
}

/**
 * Perform gamma correction on 8 RGB pixels
 *
 * @param pix   pixels struct pointer
 * @param lut   gamma lookup table
 */
INLINE void aipl_mve_lut_transform_rgb_x8(aipl_mve_rgb_x8_t* pix,
                                          uint8_t* lut)
{
    aipl_mve_lut_transform_rgb_channels_x8(&pix->r, &pix->g, &pix->b, lut);
}

/**
 * Perform gamma correction on 16 RGB pixels
 *
 * @param pix   pixels struct pointer
 * @param lut   gamma lookup table
 */
INLINE void aipl_mve_lut_transform_rgb_x16(aipl_mve_rgb_x16_t* pix,
                                           uint8_t* lut)
{
    aipl_mve_lut_transform_rgb_channels_x16(&pix->r, &pix->g, &pix->b, lut);
}

/**********************
 *      MACROS
 **********************/

#endif /*AIPL_USE_MVE*/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*AIPL_MVE_UTILS_H*/
