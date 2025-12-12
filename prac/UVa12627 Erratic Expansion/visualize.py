#!/usr/bin/env python3
"""
Visualize the balloon expansion pattern for UVa 12627
R = Red balloon
B = Blue balloon
"""

def expand(grid):
    """Expand the grid by one hour"""
    n = len(grid)
    new_size = n * 2
    new_grid = [['' for _ in range(new_size)] for _ in range(new_size)]

    for i in range(n):
        for j in range(n):
            # Calculate new positions
            top_left = (2*i, 2*j)
            top_right = (2*i, 2*j + 1)
            bottom_left = (2*i + 1, 2*j)
            bottom_right = (2*i + 1, 2*j + 1)

            if grid[i][j] == 'R':  # Red balloon
                new_grid[top_left[0]][top_left[1]] = 'R'
                new_grid[top_right[0]][top_right[1]] = 'R'
                new_grid[bottom_left[0]][bottom_left[1]] = 'R'
                new_grid[bottom_right[0]][bottom_right[1]] = 'B'
            else:  # Blue balloon
                new_grid[top_left[0]][top_left[1]] = 'B'
                new_grid[top_right[0]][top_right[1]] = 'B'
                new_grid[bottom_left[0]][bottom_left[1]] = 'B'
                new_grid[bottom_right[0]][bottom_right[1]] = 'B'

    return new_grid

def count_red(grid):
    """Count total red balloons in the grid"""
    count = 0
    for row in grid:
        count += row.count('R')
    return count

def print_grid(grid, k):
    """Print the grid with nice formatting"""
    n = len(grid)
    print(f"\n{'='*60}")
    print(f"Hour {k}: Grid size {n}×{n}")
    print(f"Red balloons: {count_red(grid)}")
    print(f"{'='*60}")

    # For larger grids, show structure with dots
    if n <= 16:
        for i, row in enumerate(grid):
            line = ' '.join(row)
            print(f"{i+1:2d} | {line}")
        print()
    else:
        # For very large grids, just show the pattern
        print(f"Grid too large ({n}×{n}) to display fully")
        print("Showing top-left 16×16 portion:")
        for i in range(min(16, n)):
            line = ' '.join(grid[i][:16])
            print(f"{i+1:2d} | {line}")
        print(f"... (showing only {min(16, n)} of {n} rows)")
        print()

def count_red_in_rows(grid, a, b):
    """Count red balloons in rows [a, b] (1-indexed)"""
    count = 0
    for i in range(a-1, b):
        if i < len(grid):
            count += grid[i].count('R')
    return count

# Start with one red balloon
grid = [['R']]

print("UVa 12627 - Erratic Expansion Visualization")
print("=" * 60)

# Show progression from hour 0 to 10
for k in range(11):
    print_grid(grid, k)

    # Show some example queries for smaller grids
    if k <= 3:
        n = len(grid)
        # Query entire grid
        total = count_red_in_rows(grid, 1, n)
        print(f"Example: Rows [1, {n}] -> {total} red balloons")

        # Query partial range if grid is large enough
        if n >= 4:
            mid = n // 2
            partial = count_red_in_rows(grid, mid, n-1)
            print(f"Example: Rows [{mid}, {n-1}] -> {partial} red balloons")
        print()

    # Expand for next hour
    if k < 10:
        grid = expand(grid)

# Summary
print("\n" + "="*60)
print("SUMMARY: Red balloon count by hour")
print("="*60)
grid = [['R']]
for k in range(11):
    n = len(grid)
    red_count = count_red(grid)
    print(f"Hour {k:2d}: Grid {n:4d}×{n:4d}, Red balloons: {red_count}")
    if k < 10:
        grid = expand(grid)
