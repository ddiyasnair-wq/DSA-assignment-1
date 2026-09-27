# Q5 — Organisational Hierarchy: Analysis, Comparison & Conclusion

## a) Tree Structure Used

A **general (n-ary) tree** is the natural fit here — each node (department)
can have any number of children, unlike a binary tree. Each `TreeNode`
stores a name and an array of child pointers.

Hierarchy built:
```
CEO
├── HR
├── Finance
└── IT
    ├── Development
    │   ├── Frontend
    │   └── Backend
    └── Testing
```

**Level-order traversal output (BFS, from execution):**
```
CEO
HR Finance IT
Development Testing
Frontend Backend
```

**Tree height:** 4 (CEO → IT → Development → Frontend/Backend)

## b) Search Comparison Results (from execution)

| Search Key | Present in unsorted array at index | Linear Search comparisons | Binary Search comparisons |
|---|---|---|---|
| Testing | 5 | 6 | 4 |
| HR | 1 | 2 | 2 |
| Backend | 7 (last) | 8 | 3 |
| Sales (miss) | — | 8 | 4 |

(Binary Search requires the array to be sorted first: `Backend, CEO,
Development, Finance, Frontend, HR, IT, Testing`.)

## c) Analysis

**Tree height:** With only 8 departments the tree stays shallow (height 4),
so level-order traversal and any tree-based lookup remain cheap regardless
of representation.

**Traversal behaviour:** Level-order (BFS) traversal correctly reflects the
reporting structure level by level (CEO → direct reports → their reports),
which is exactly what "organisational reporting" needs — you can see who
reports to whom at each tier. A tree traversal is the right tool for
*displaying structure*; it is not meant for fast key lookup by name.

**Search comparisons — Linear vs Binary:**
- Linear Search comparisons grow with the position of the key in the
  unsorted list: best case 1 (first element), worst case n (last element
  or miss). Here `Backend` and the missing `Sales` both needed all 8
  comparisons.
- Binary Search comparisons stay close to ⌈log₂n⌉ regardless of where the
  key sits, once the array is sorted — at most 4 comparisons for 8
  elements, versus up to 8 for Linear Search.

**Time complexity:**

| Operation | Time Complexity | Space Complexity |
|---|---|---|
| Tree construction (n nodes) | O(n) | O(n) |
| Level-order traversal | O(n) | O(w) — w = max width of a level |
| Linear Search | O(n) worst/avg, O(1) best | O(1) |
| Binary Search | O(log n) worst/avg, O(1) best | O(1) (iterative) |
| Sorting the array once (qsort) | O(n log n) | O(log n) (typical quicksort) |

## Conclusion

The **tree structure** (n-ary tree with level-order traversal) is well
suited to *representing and displaying* the organisational hierarchy,
since it naturally captures parent-child reporting relationships and
scales to O(n) construction/traversal even as more departments are added.

For **department searching**, Binary Search clearly outperforms Linear
Search once the department list is sorted (O(log n) vs O(n)) — the
measured comparisons (up to 4 vs up to 8 for 8 departments) confirm the
theoretical gap, and the advantage widens further as the company grows.
The one cost is the O(n log n) sort needed up front and the requirement
to re-sort (or use an insertion-preserving sorted structure such as a
BST) whenever new departments are added.

**Overall recommendation:** keep the **tree** for organisational
reporting/visualisation, and maintain a **separate sorted array (or a
BST) of department names** for fast lookups. This combination is
suitable for both organisational reporting and efficient department
searching as the company scales — a pure unsorted linear-search list
would not scale well, while a bare tree alone is not optimized for
name-based lookup.
