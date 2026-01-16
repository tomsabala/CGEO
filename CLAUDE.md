# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

CGEO is a computational geometry library with C++ core implementations and Python bindings via pybind11. It provides high-performance geometric algorithms (convex hull, segment intersection, triangulation, smallest enclosing disk) and 2D shape primitives (Point, Segment, Polygon, Circle, Triangle).

## Build Commands

```bash
# Initialize pybind11 submodule (required before first build)
git submodule update --init

# Build for development (compiles C++ extension in-place)
python3 setup.py build_ext -bin
sudo python3 setup.py develop

# Full build with distribution package
./runSetup.sh

# Alternative CMake build (creates build/ directory)
./run.sh

# Run tests
pytest tests/
```

## Architecture

### C++ Core (`src/`)
- **`2D/shapes_2D/`**: Geometric primitives (Point2d, Segment2d, Polygon, Circle2d, Triangle2d, Line2d)
- **`2D/algorithms_2D/`**: Algorithms (ConvexHull2D, SegmentIntersection2D, Triangulation2D, SmallestEnclosingDisk)
- **`data_structures/`**: AVL-based SegmentBalancedTree for sweep-line algorithms
- **`2D/2D_bindings.cpp`**: pybind11 binding layer exposing `libShapes_2D` and `libAlgorithms_2D` submodules

### Python Package (`cgeo/`)
- **`modules/`**: Python wrapper classes (Point2D, Segment2D, Polygon, Circle, Triangle) that wrap C++ objects
- **`utilities/c_utilities/global_c_utils.py`**: Python API to invoke C++ algorithms
- **`plots_2d/`**: Visualization utilities using matplotlib

### Python Bindings
The C++ extension is built as `cgeo._cgeo` with two submodules:
- `_cgeo.libShapes_2D`: Shape classes (Point, Segment, Polygon, Circle, Triangle)
- `_cgeo.libAlgorithms_2D`: Algorithm classes (ConvexHull, SegmentIntersection2D, Triangulation2D, SmallestEnclosingDisk)

Python wrappers in `cgeo/modules/` provide a Pythonic interface over these C++ bindings.

## Key Patterns

**Orientation Predicate**: All shapes implement `oriePred()` for computing turn direction (left/right/collinear). This is fundamental to convex hull, intersection testing, and containment checks. Uses epsilon comparison (1e-8) for floating-point robustness.

**Sweep-line with Balanced Tree**: `SegmentIntersection2D` uses `SegmentBalancedTree` (AVL tree) for efficient segment ordering during sweep-line processing.

## Testing

Tests use pytest with Shapely as a validation oracle:
```bash
pytest tests/convex_hull_test.py  # Main test with property-based validation
```

Test data configuration is in `tests/polygon_size_tests.json`.
