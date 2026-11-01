# CGEO Roadmap

Target: turn a four-algorithm 2D exercise into a geometry kernel people install, trust,
and can watch run in a browser.

The three outcomes a stranger can verify in under a minute, in priority order:

1. `pip install cgeo` works on every major platform, no compiler required.
2. An interactive WASM playground runs the *actual* C++ kernel in the browser.
3. Exact-predicate robustness, demonstrated against libraries that get it wrong.

---

## Phase 0 — Restore a working baseline

Nothing below matters until `main` compiles. Everything in this phase is mechanical.

### 0.1 Fix the build

`src/2D/algorithms_2D/SegmentIntersection2D.cpp` does not compile (gcc 11.4, `-std=c++17`):

```
:97:54  error: 'Point' was not declared in this scope
:97:76  error: template argument 1 is invalid
:97:1   error: no declaration matches 'findInteriorMap(int)'
:146:46 error: 'Segment' does not name a type
:152:46 error: 'Segment' was not declared in this scope
```

Commit `c927fa6` ("refactore code base…") removed the `Point` / `Segment` aliases from
`SegmentIntersection2D.h` but left the `.cpp` using them. The header now declares
`Shapes2D::Point2d`, `Shapes2D::Segment2d` and `EventMap::iterator`. Reconcile the `.cpp`
to the header — do not reintroduce the aliases.

**Done when:** `pip install .` succeeds from a clean venv on gcc and clang.

### 0.2 Fix packaging

- Add `pyproject.toml` with `[build-system] requires = ["setuptools>=61", "pybind11>=2.11"]`.
  Without it, `setup.py` line 8 imports `pybind11` before it can exist in an isolated build.
- Stop vendoring pybind11 via submodule for the build path; depend on the PyPI package.
  Keep the submodule only if the CMake path still needs it.
- Delete `py_src/` — it is tracked but contains **only** `.pyc` files. Dead since the
  rename to `cgeo/`.
- Untrack every `__pycache__/` and add it to `.gitignore`.
- Delete the 9 stale remote branches (`segments_intersection`, `py-module-build`,
  `setup-file-conf`, `cmakelist-configurations`, `cmake-single-platyform-testing`,
  `fixing-memory-leaks`, `add-license-1`, `code-simplifier`, …).

### 0.3 Fix CI

Both workflows are decorative:

- `cmake-single-platform.yml` passes `-CMAKE_PATH_IGNORE=…` and `cmake --build … --path-ignore …`.
  Neither is a CMake flag. The configure step cannot succeed.
- `wheel.yml` triggers on `push: branches: [master]`. The default branch is `main`, so it
  has never run on a push. It also uses `actions/upload-artifact@v3` and
  `download-artifact@v3`, both deprecated and now failing.
- No workflow runs `pytest`.

Replace with one `ci.yml`: build + `pytest tests/` on linux/macos/windows × Python
3.9–3.13, on `main` and PRs.

### 0.4 Release 0.2.0 with wheels

PyPI currently serves `cgeo 0.1.4` (2023-12-12), **sdist only**. It installs and then
fails on import:

```
ImportError: cannot import name 'Circle' from partially initialized module
cgeo.modules.circle (most likely due to a circular import)
```

`cgeo/utilities/__init__.py` eagerly imported `global_c_utils`, which imports
`cgeo.modules.circle`, which imports back into `cgeo.utilities`. HEAD already fixed this
(the file is now empty) — it was simply never released.

Set up `cibuildwheel` + PyPI trusted publishing on tag. Ship `cp39`–`cp313` wheels for
manylinux, macOS (x86_64 + arm64), and Windows.

**Done when:** `pip install cgeo && python -c "import cgeo"` works on a machine with no
compiler.

---

## Phase 1 — WASM playground

The highest-impact item in the repo. Ship the real kernel to the browser.

- Second build target: emscripten + `embind` over the same `src/` tree. No algorithm
  reimplemented in JavaScript.
- Static site (GitHub Pages) with a canvas per algorithm:
  - **Convex hull** — drag points, hull updates live; toggle Jarvis / Graham / divide &
    conquer and watch the different traversal orders.
  - **Segment intersection** — step the sweep line event by event. Render the event queue
    and the live `SegmentBalancedTree` as a tree, highlighting the rotation on each event.
    This is the one that lands: almost nobody visualizes the status structure.
  - **Triangulation** — y-monotone decomposition, then the diagonals, as separate steps.
  - **Smallest enclosing disk** — Welzl's recursion with the boundary set highlighted.
- Timeline scrubber, step/play controls, and permalinks encoding the input point set so a
  specific degenerate case can be shared.
- Link it from the README with an animated preview, replacing the static PNGs in
  `cgeo/plot_images/`.

**Done when:** a stranger clicks a link and sees a sweep line running within 3 seconds.

---

## Phase 2 — Exact predicates and the robustness story

The part that cannot be faked, and the reason to trust the library.

### 2.1 Adaptive-precision arithmetic

Every shape's `oriePred()` compares against `1e-8`. That is wrong for near-degenerate
input — it reports collinear for points that are not, and the error compounds through the
hull and sweep-line algorithms.

Implement Shewchuk's adaptive-precision `orient2d` and `incircle`:

- Static floating-point filter first — the common case stays as fast as it is now.
- Exact expansion arithmetic only on filter failure.
- Benchmark to prove the fast path did not regress.

### 2.2 Differential fuzzing

`tests/` already uses Shapely as an oracle. Turn that into a weapon.

- Hypothesis strategies that generate **deliberately degenerate** input: collinear triples,
  duplicate and near-duplicate points, points separated by 1 ULP, cocircular quadruples,
  near-tangent circles, self-touching polygons, zero-length segments.
- Cross-check CGEO against Shapely, CGAL, and `scipy.spatial` on every generated case.
- Property assertions independent of any oracle: hull output is convex and contains every
  input point; triangulation triangles are interior-disjoint and partition the polygon;
  reported intersections lie on both segments.
- Two hull defects are already known and measured; they are the first regression targets,
  not a rediscovery exercise:
  - `giftWrapConvexHull` returns a 1-vertex polygon for most inputs (e.g.
    `[(0,0),(1,3),(4,4),(5,1)]` → `[[0,0]]`). Present at `0f39701`, so it predates the
    `c927fa6` refactor.
  - `grahamConvexHull` emits chain endpoints twice (`[(0,0),(4,0),(4,4),(0,4),(2,2)]` →
    `[[4,0],[0,0],[0,4],[0,4],[4,4],[4,0]]`). The existing Shapely area-difference assertion
    cannot catch it.
- Run the fuzzer nightly in CI with a persistent corpus; minimize and commit every failure
  as a regression case.

### 2.3 Report what you find upstream

Run it long enough and one of GEOS / Shapely / CGAL will be wrong on some input. File the
issues. Link them from the README.

*"Found and reported N robustness bugs in production geometry libraries via differential
fuzzing"* is the strongest sentence either of these projects can earn, because strangers
verified it.

### 2.4 Degeneracy gallery

A README table rendering degenerate inputs side by side: epsilon-based output (a "convex"
hull that visibly is not convex, a triangulation with overlapping triangles) against
CGEO's exact output. Generated as SVG by a script, regenerated in CI, committed.

---

## Phase 3 — Breadth

With the fuzzing oracle from Phase 2, correctness cost per new algorithm is near zero.
This is where the implementation budget goes.

- 2D Delaunay triangulation + Voronoi diagram (`incircle` from 2.1 is the predicate).
- Polygon boolean ops — union, intersection, difference (Vatti or Greiner–Hormann).
- Minkowski sum and polygon offsetting.
- 3D convex hull (quickhull) — `src/3D/` currently has `Point3d` and `Face3d` and nothing
  that uses them.
- BVH / spatial index for broad-phase queries.
- Line segment arrangement (generalizes the existing sweep line).

Every item ships with: exact predicates, Hypothesis differential tests, a WASM
visualization, and a benchmark entry.

---

## Phase 4 — Performance, measured

- `pytest-benchmark` suite comparing against Shapely/GEOS and `scipy.spatial` per
  algorithm, across input sizes and distributions (uniform, clustered, degenerate).
- Continuous benchmarking in CI — a PR that regresses a hot path fails.
- Published results table in the README with the exact hardware and reproduction command.

Honest framing: GEOS is mature and broadly beating it is unlikely. Pick a workload where
the design wins (e.g. many-segment sweep with a balanced status tree) and claim only that.

---

## Phase 5 — Become MLMP's geometry backend

MLMP hand-rolls segment intersection on naked doubles at
`mlmp/src/state/kinematic_chain.h:243`, cited to a Stack Overflow answer, inside its
collision checker — i.e. in the hottest loop of a motion planner.

Expose a C++ consumer API (header + static lib, not just the Python extension) and make
MLMP link it. A demanding real-time consumer is the only thing that makes a geometry API
good, and it closes the loop: planner benchmark regressions become kernel test cases.

See `MLMP/ROADMAP.md` Phase 2.

---

## Non-goals

- LLM/chatbot features. A geometry kernel is a tool; wrapping it in a chat interface adds
  nothing and reads as padding.
- Reimplementing CGAL. Pick depth on robustness and visualization, not feature parity.
- Keeping the matplotlib PNG gallery once the WASM playground exists.
