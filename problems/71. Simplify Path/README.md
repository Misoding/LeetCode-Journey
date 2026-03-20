# Day 56: Simplify Path

- **Difficulty:** Medium
- **Topics:** String, Stack
- **LeetCode Link:** [Simplify Path](https://leetcode.com/problems/simplify-path/)
- **Author:** [Mihail Iazinschi](https://www.linkedin.com/in/mihail-iazinschi/)

---

## 📝 Problem Statement

Given a string `path`, which is an **absolute path** (starting with a slash `'/'`) to a file or directory in a Unix-style file system, convert it to the simplified **canonical path**.

In a Unix-style file system:
* A period `.` refers to the current directory.
* A double period `..` refers to the directory up a level.
* Any multiple consecutive slashes (i.e., `//`) are treated as a single slash `/`.

The canonical path should have the following format:
* The path starts with a single slash `/`.
* Any two directories are separated by a single slash `/`.
* The path does not end with a trailing `/`.
* The path only contains the directories on the path from the root directory to the target file or directory (i.e., no period `.` or double period `..`).

Return the simplified canonical path.

---

## 🏗️ Deep-Dive Implementation Strategy

The problem models an OS-level directory traversal system. This is inherently a LIFO (Last-In-First-Out) stack evaluation problem, where going "up a level" equates to popping the most recently entered directory.

### 1. Zero-Allocation Tokenization
Instead of using `std::stringstream` to split the path by `/` (which inherently requires allocating an array of strings), this implementation uses a sliding-window token extractor. 
* The pointer `i` scans forward until it hits a `/`, extracting the substring strictly between the delimiters.
* This operates directly on the raw string, minimizing heap allocations.

### 2. Double-Ended Queue (Deque) as a Stack
A `std::deque<string>` is the optimal data structure here.
* **Stack behavior (Push/Pop Back):** When encountering a directory name, we push it. When encountering `..`, we pop the last directory.
* **Queue behavior (Pop Front):** When the canonical path is ready, we must build it from root to leaf (left to right). A standard `std::stack` would force us to reverse the output, but a deque allows $O(1)$ front extraction.

### 3. Explicit Delimiter State Management
The algorithm explicitly pushes the `/` delimiter into the stack alongside the directory names.
* When evaluating `..`, the system pops *twice*: once to remove the trailing `/`, and once to remove the directory node itself.
* If the stack empties (e.g., trying to `cd ..` from root), the root delimiter `/` is preserved to maintain the absolute path invariant.

---

## 🔬 Formal Algorithmic Analysis

### 1. Mathematical Model

Let the input path be $P$. We parse $P$ into an ordered sequence of tokens $T = (t_1, t_2, \dots, t_k)$ where $t_i \in \{\text{dir}, \text{"."}, \text{".."}\}$.
The transition function over the stack state $S$ is defined as:

$$
S_{next} = \begin{cases} 
S \cup \{t_i\} & \text{if } t_i \text{ is a valid directory} \\
S \setminus \{\text{top}(S)\} & \text{if } t_i = \text{".."} \land S \neq \emptyset \\
S & \text{if } t_i = \text{".."} \land S = \emptyset \lor t_i = \text{"."}
\end{cases}
$$

The final canonical path is the concatenation of all elements remaining in $S$, prefixed and separated by `/`.

### 2. Time Complexity Analysis

The external `for` loop combined with the internal `while` loop behaves linearly. The index `i` is strictly incremented and never resets. The `substr()` extraction and string comparisons (`==`) operate on small disjoint fragments of length $L_j$, where $\sum L_j \le N$.
Extracting elements from the deque at the end is strictly proportional to the number of nodes saved.

$$
T(N) = \Theta(N)
$$

$$
T(N) \in O(N)
$$

### 3. Space Complexity Analysis

The auxiliary spatial allocation is consumed by the `std::deque` and the final string accumulator. In the worst-case scenario (e.g., `/a/b/c/d/`), there are no `..` commands, and the deque stores $O(N)$ characters parsed from the path.

$$
S_{aux}(N) = \Theta(N)
$$

$$
S_{aux}(N) \in O(N)
$$

---

## 💻 Implementation (C++)

```cpp
class Solution {
public:
    string simplifyPath(string path) {
        deque<string> pathSt;
        pathSt.push_back("/");
        for(int i = 0; i < path.length();i++) {
            string formedString = "";
            if(path[i] == '/') continue;
            if (!pathSt.empty() && pathSt.back() == "/") {
                int start = i;
                while(i < path.length() && path[i] != '/') i++;
                formedString = path.substr(start, i-start);
                if (formedString == ".."){
                    pathSt.pop_back();
                    if ((pathSt.empty())) {
                        pathSt.push_back("/");
                        continue;
                    }
                    pathSt.pop_back();
                    continue;
                }
                if(formedString == "."){
                    continue;
                }
                pathSt.push_back(formedString);
                pathSt.push_back("/");
            }
        }
       string resString = "";
       pathSt.pop_back();
        while(!(pathSt.empty())) {
            resString += pathSt.front();
            pathSt.pop_front();
        }
        if (resString == "") return "/";

        return resString;

    }
};
```

---

### 🔗 Connect
This problem is part of my daily algorithmic practice. You can find more about my professional journey on my [**LinkedIn Profile**](https://www.linkedin.com/in/mihail-iazinschi/).