// Copyright 2021-present StarRocks, Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#pragma once

#include "unpack_def.h"

inline void extend_8u16u(const __m512i src, uint16_t* dst_ptr) {
    __m256i tmp = _mm512_extracti64x4_epi64(src, 0);
    __m512i result = _mm512_cvtepu8_epi16(tmp);
    _mm512_storeu_si512(dst_ptr, result);
    dst_ptr += 32;

    tmp = _mm512_extracti64x4_epi64(src, 1);
    result = _mm512_cvtepu8_epi16(tmp);
    _mm512_storeu_si512(dst_ptr, result);
    dst_ptr += 32;
}

inline void extend_8u32u_tail(const uint8_t* src_ptr, uint32_t num_values, uint8_t* dst_ptr) {
    __m128i srcmm;
    __m512i dstmm;

    __mmask16 tail_mask = OWN_BIT_MASK(num_values);
    srcmm = _mm_maskz_loadu_epi8(tail_mask, (const __m128i*)src_ptr);
    dstmm = _mm512_maskz_cvtepu8_epi32(tail_mask, srcmm);
    _mm512_mask_storeu_epi32(dst_ptr, tail_mask, dstmm);
}

inline void extend_8u32u(const __m512i src, uint32_t* dst_ptr) {
    __m128i tmp = _mm512_extracti32x4_epi32(src, 0);
    __m512i result = _mm512_cvtepu8_epi32(tmp);
    _mm512_storeu_si512(dst_ptr, result);
    dst_ptr += 16u;

    tmp = _mm512_extracti32x4_epi32(src, 1);
    result = _mm512_cvtepu8_epi32(tmp);
    _mm512_storeu_si512(dst_ptr, result);
    dst_ptr += 16u;

    tmp = _mm512_extracti32x4_epi32(src, 2);
    result = _mm512_cvtepu8_epi32(tmp);
    _mm512_storeu_si512(dst_ptr, result);
    dst_ptr += 16u;

    tmp = _mm512_extracti32x4_epi32(src, 3);
    result = _mm512_cvtepu8_epi32(tmp);
    _mm512_storeu_si512(dst_ptr, result);
    dst_ptr += 16u;
}

inline void extend_8u64u(const __m512i src, uint64_t* dst_ptr) {
    __m128i tmp = _mm512_extracti32x4_epi32(src, 0);
    __m512i presult = _mm512_cvtepu8_epi32(tmp);
    __m256i tmp1 = _mm512_extracti64x4_epi64(presult, 0);
    __m512i result = _mm512_cvtepu32_epi64(tmp1);
    _mm512_storeu_si512(dst_ptr, result);
    dst_ptr += 8u;
    tmp1 = _mm512_extracti64x4_epi64(presult, 1);
    result = _mm512_cvtepu32_epi64(tmp1);
    _mm512_storeu_si512(dst_ptr, result);
    dst_ptr += 8u;

    tmp = _mm512_extracti32x4_epi32(src, 1);
    presult = _mm512_cvtepu8_epi32(tmp);
    tmp1 = _mm512_extracti64x4_epi64(presult, 0);
    result = _mm512_cvtepu32_epi64(tmp1);
    _mm512_storeu_si512(dst_ptr, result);
    dst_ptr += 8u;
    tmp1 = _mm512_extracti64x4_epi64(presult, 1);
    result = _mm512_cvtepu32_epi64(tmp1);
    _mm512_storeu_si512(dst_ptr, result);
    dst_ptr += 8u;

    tmp = _mm512_extracti32x4_epi32(src, 2);
    presult = _mm512_cvtepu8_epi32(tmp);
    tmp1 = _mm512_extracti64x4_epi64(presult, 0);
    result = _mm512_cvtepu32_epi64(tmp1);
    _mm512_storeu_si512(dst_ptr, result);
    dst_ptr += 8u;
    tmp1 = _mm512_extracti64x4_epi64(presult, 1);
    result = _mm512_cvtepu32_epi64(tmp1);
    _mm512_storeu_si512(dst_ptr, result);
    dst_ptr += 8u;

    tmp = _mm512_extracti32x4_epi32(src, 3);
    presult = _mm512_cvtepu8_epi32(tmp);
    tmp1 = _mm512_extracti64x4_epi64(presult, 0);
    result = _mm512_cvtepu32_epi64(tmp1);
    _mm512_storeu_si512(dst_ptr, result);
    dst_ptr += 8u;
    tmp1 = _mm512_extracti64x4_epi64(presult, 1);
    result = _mm512_cvtepu32_epi64(tmp1);
    _mm512_storeu_si512(dst_ptr, result);
    dst_ptr += 8u;
}
