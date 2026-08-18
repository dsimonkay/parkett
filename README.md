# parkett

A toy electronic exchange. Limit order book, matching engine, trading bots and a live dashboard, written in modern C++ (C++23).

[![CI](https://github.com/dsimonkay/parkett/actions/workflows/ci.yaml/badge.svg)](https://github.com/dsimonkay/parkett/actions/workflows/ci.yaml)

## What it is

Parkett is a self-contained miniature exchange:

- an **exchange server** that accepts limit and market orders and matches them with price-time priority;
- **bots** that trade on it — built in, as native plugins (`.so`/`.dll`), or remotely over TCP;
- every state change is an **event**, written to a write-ahead log and deterministically replayable;
- a **live dashboard** showing candlestick charts, order book depth and a bot leaderboard, with manual trading against the bots.

It is a learning project, built milestone by milestone. Financial realism is deliberately out of scope: no fees, no auctions, no short selling.

**Status:** M0 complete: project skeleton, build system, tests and CI in place.

## Requirements

| | |
|---|---|
| Compiler | GCC 14+ or Clang 18+ (C++23) |
| Build | CMake ≥ 3.28, Ninja |
| Platform | Linux (primary target) |

Dependencies are fetched automatically by CMake via `FetchContent`; nothing needs to be installed by hand.

On Debian/Ubuntu:

```bash
sudo apt install g++-14 cmake ninja-build clang-format clang-tidy
```

## Building

Three presets are available: `debug`, `release` and `asan-ubsan` (AddressSanitizer + UndefinedBehaviorSanitizer).

```bash
cmake --preset debug          # configure
cmake --build --preset debug  # build
ctest --preset debug          # run tests
```

Binaries land in `build/<preset>/bin/`:

```bash
./build/debug/bin/exchanged
```

## Layout

```
parkett/
├── core/         # lib: domain types, order book, matching, events, serialization
├── exchanged/    # executable: the exchange server
└── .github/      # CI workflows
```

Planned components: `sim/` (simulation clock, built-in agents), `plugin-api/` (C ABI plugin contract), `bots/` (native and Rust plugins), `ui/` (ImGui/ImPlot dashboard), `replay/` (WAL replayer), `bench/`.

Architectural rules, enforced in review:

1. `core` knows nothing about threads, networking, UI or global state: pure deterministic logic.
2. Every state change is born as an event; the rest of the system consumes events only.
3. The UI draws and forwards intent; it holds no business logic.
4. The plugin boundary is a C ABI: no exception crosses it.

## Development

Code style is enforced by `clang-format` (Allman braces, 4-space indent, 100-column limit) and checked in CI:

```bash
git ls-files '*.cpp' '*.h' | xargs clang-format -i                    # format
git ls-files '*.cpp' '*.h' | xargs clang-format --dry-run --Werror    # check
```

Static analysis with `clang-tidy`, using the compile database generated in the build directory:

```bash
run-clang-tidy -p build/debug -quiet '/(core|exchanged)/(src|test)/'
```

Tests live next to the code they cover, in a `test/` subdirectory of each component, and are written with [Catch2](https://github.com/catchorg/Catch2).

## Roadmap

| | Milestone | Status |
|---|---|---|
| M0 | Project skeleton, CMake, CI, sanitizers | ✅ |
| M1 | Domain types — strong types, `std::expected`, formatters | |
| M2 | Order book and matching engine | |
| M3 | Events, binary serialization, WAL, deterministic replay | |
| M4 | Simulation clock and built-in trading agents | |
| M5 | ABI-stable plugin system (`dlopen`, C boundary) | |
| M6 | Concurrency — event bus, hand-written SPSC ring buffer | |
| M7 | TCP networking with C++20 coroutines | |
| M8 | Live dashboard (Dear ImGui + ImPlot) | |
| M9 | A trading bot written in Rust, over the same C plugin API | |
| M10 | Performance — benchmarking, profiling, targeted optimization | |
