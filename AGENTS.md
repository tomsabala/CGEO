# AGENTS.md

Canonical agent context for CGEO: a computational-geometry library with a C++ core exposed to
Python through pybind11.

## Build and test

```bash
pip install -e ".[test]"     # builds cgeo._cgeo in place
pytest tests                 # tests/test_smoke.py + tests/convex_hull_test.py
```

C++ core on its own (produces `libcgeo_core.a` and a `_cgeo` extension module):

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```

There is **no** `run.sh`, no `runSetup.sh`, no `setup.py develop`, no `requirements.txt`, and no
vendored pybind11 submodule under `extern/`. Anything referring to those is stale. pybind11 comes
from pip (`build-system.requires`); CMake takes it from `find_package(pybind11 CONFIG)` and falls
back to `FetchContent` only when pip's copy is absent.

With a **non-editable** install, anything that puts the repository root on `sys.path` imports the
source directory `cgeo/`, which has no compiled `_cgeo`, and fails. So run `pytest tests`, never
`python -m pytest tests` (`-m` prepends the cwd). CI does the same, for the same reason. An
editable install (`pip install -e .`) builds `_cgeo` into the source tree and sidesteps it.

Standard C++ headers must be included explicitly in the translation unit that needs them. GCC 11
pulls `<functional>` in through `<algorithm>`; GCC 13+, Apple clang and MSVC do not, and a missing
include shows up only in CI.

## Layout

|Path|Contents|
|---|---|
|`src/2D/shapes_2D/`|Primitives: `Point2d`, `Line2d`, `Segment2d`, `Polygon`, `Circle2d`, `Triangle2d`|
|`src/2D/algorithms_2D/`|`ConvexHull2D`, `SegmentIntersection2D`, `Triangulation2D`, `SmallestEnclosingDisk`|
|`src/data_structures/`|`SegmentBalancedTree`, the AVL sweep-line status structure|
|`src/2D/2D_bindings.cpp`|The single `PYBIND11_MODULE`; exposes submodules `libShapes_2D` and `libAlgorithms_2D`|
|`cgeo/modules/`|Python wrappers, each holding a `cPoint` / `cSegment` / `cPolygon` / … handle|
|`cgeo/utilities/c_utilities/global_c_utils.py`|The public algorithm entry points|
|`cgeo/plots_2d/`|matplotlib helpers; the only code needing the `plot` extra|
|`examples/`|Demo scripts. Not tests, not installed, not run in CI|
|`tests/test_smoke.py`|The wheel gate. Standard library + `cgeo` only, because cibuildwheel runs it inside each wheel's environment|

Public algorithm surface: `grahamConvexHull`, `giftWrapConvexHull`, `segmentIntersection`,
`triangulate`, `enclosingDisc`.

## Invariants

- **Orientation predicate.** Every shape implements `oriePred()` with a `1e-8` epsilon, and convex
  hull, intersection and containment all ride on it. ROADMAP Phase 2.1 replaces it with Shewchuk's
  adaptive predicates — do not scatter new epsilon comparisons through the shapes in the meantime.
- **Ownership for bindings.** C++ shapes own their members **by value**. Never return a raw `T*`
  to a member from a bound method: pybind11's default `return_value_policy::automatic` takes
  ownership of the returned pointer, and the C++ destructor frees it too. That is exactly the
  double free `Circle2d` had (it stored `Point2d* c` and returned it from `getCenter()`); the fix
  was `Point2d c` by value plus `const Point2d& getCenter() const`.
- **Version** lives only in `pyproject.toml`. `setup.py` carries the extension definition and
  nothing else.

## Adding an algorithm

1. New `.cpp` / `.h` under `src/2D/algorithms_2D/` — picked up automatically by the
   `src/**/*.cpp` glob in `setup.py` and by the `GLOB_RECURSE` in `CMakeLists.txt`.
2. A `py::class_` block in `src/2D/2D_bindings.cpp`.
3. A thin function in `cgeo/utilities/c_utilities/global_c_utils.py`.
4. A case in `tests/test_smoke.py`, using only the standard library.

## Known broken — do not "fix" incidentally

- `giftWrapConvexHull` returns a 1-vertex polygon for most inputs
  (`[(0,0),(1,3),(4,4),(5,1)]` → `[[0,0]]`). Predates the current layout; ROADMAP Phase 2.
- `grahamConvexHull` emits the chain endpoints twice
  (`[(0,0),(4,0),(4,4),(0,4),(2,2)]` → `[[4,0],[0,0],[0,4],[0,4],[4,4],[4,0]]`). The hull vertex
  *set* is correct, which is why `tests/test_smoke.py` asserts on the set. ROADMAP Phase 2.
- `Segment2D()` with no arguments, and therefore `Segment2D.fromCSegment` and
  `Polygon.getEdges()`, raise `TypeError`: `Shapes2D::Segment2d` has no default constructor, so
  the binding exposes no zero-argument `__init__`. Breaks `examples/polygon.py`,
  `examples/segment_2d.py` and `examples/y_monotone_decomposision.py`.

The remaining examples (`convex_hull_2d`, `enclosing_disc_2d`, `point_2d`,
`segment_intersection_2d`, `triangulation_2d`) run clean under `MPLBACKEND=Agg`.

## Release

Tag `vX.Y.Z` → `.github/workflows/release.yml` builds an sdist plus wheels on five runners,
runs `tests/test_smoke.py` inside every wheel, and publishes to PyPI via trusted publishing
(OIDC, GitHub environment `pypi`, no API token).
