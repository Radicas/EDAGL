#include <benchmark/benchmark.h>
#include <iostream>
#include <string>
#include <cstdint>

void int32Add() {
    int32_t n = 0x3f4d245d;
    int32_t m = 0x28937a93;
    int32_t rv = m + n;
}

static void BM_Int32Add(benchmark::State &state) {
    for (auto _: state) {
        int32Add();
    }
}

BENCHMARK(BM_Int32Add);

void int64Add() {
    int64_t n = 0x3d5a636348539873;
    int64_t m = 0x2a4d69922859af73;
    int64_t rv = m + n;
}

static void BM_Int64Add(benchmark::State &state) {
    for (auto _: state) {
        int64Add();
    }
}

BENCHMARK(BM_Int64Add);

void floatAdd() {
    float n = 123425.5643;
    float m = 7364577.8394;
    float rv = m + n;
}

static void BM_FloatAdd(benchmark::State &state) {
    for (auto _: state) {
        floatAdd();
    }
}

BENCHMARK(BM_FloatAdd);

void doubleAdd() {
    double n = 573829472843.83267;
    double m = 3485783438478343.438757;
    double rv = m + n;
}

static void BM_DoubleAdd(benchmark::State &state) {
    for (auto _: state) {
        doubleAdd();
    }
}

BENCHMARK(BM_DoubleAdd);

//////////////////////////////Add////////////////////////////////////////



BENCHMARK_MAIN();
