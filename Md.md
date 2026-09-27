# Version History — Assumptions, Edge Cases & Bugs

## Assumptions

* History is **linear**; branching/merging is not supported.
* `cursor` represents the index of the **currently active state**.
* `Ctrl+Z` is represented by calling `undo()`.
* Adding a new state after `undo()` deletes all states ahead of the cursor.
* `maxHistory` represents the maximum number of states stored.
* When the limit is exceeded, the **oldest state is removed**.
* States are currently represented only by `int`.
* History exists only in memory; there is no disk persistence.

## Possible Edge Cases

### 1. Undo at the oldest state

```text
[10, 20, 30]
 ^
cursor
```

Calling `undo()` should do nothing and return `false`.

### 2. Undo with no states

```text
history = []
cursor = -1
```

Calling `undo()` should safely return `false`.

### 3. New state after undo

```text
[10, 20, 30, 40, 50]
         ^
       cursor
```

Adding `35` produces:

```text
[10, 20, 30, 35]
                  ^
```

States `40` and `50` are discarded.

### 4. History limit = 1

Only the latest state can be retained:

```text
[10]

push(20)

[20]
```

### 5. Invalid history size

`maxHistory <= 0` is currently not explicitly handled and should be validated.

## Possible Bugs / Improvements

### 1. `maxHistory <= 0`

Currently, a value such as:

```cpp
VersionHistory vh(0);
```

can cause incorrect cursor/history behavior.

**Fix:** Reject zero or negative capacity in the constructor.

### 2. `currentState()` on empty history

Currently it returns:

```text
-1
```

This is intentional to represent "no current state", but this behavior should be documented or replaced with a safer API later.

### 3. `vector::erase()`

Removing the first element:

```cpp
history.erase(history.begin());
```

takes **O(n)** time because the remaining elements must be shifted.

This is acceptable for the current simple implementation, but can later be replaced with a **deque/ring buffer** for efficient bounded history.

### 4. Full state storage

Currently every state is stored completely:

```text
10 → 20 → 30 → 40 → 50
```

No actual **diff/delta representation** is implemented yet.

A future version can store:

```text
Initial State
    ↓
 Diff 1
    ↓
 Diff 2
    ↓
 Diff 3
```

to reduce storage requirements for large application states.

## Current Scope

The current implementation intentionally supports only:

```text
pushState()
undo()
currentState()
printHistory()
```

No redo, branching, persistence, compression, or distributed version control features are implemented.
