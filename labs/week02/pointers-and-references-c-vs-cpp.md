# Pointers and References: C vs. C++

**BS0013 Data Structures — Week 2 supplementary reference**  
Riga Business School, Riga Technical University

This guide connects the C pointer knowledge you may have encountered in Systems Programming or Harvard CS50 with the C++ pointers and references used in this course. C and C++ share much of their pointer syntax, but C++ adds references, different object-creation mechanisms, and standard-library abstractions for ownership.

The central question is: **When a program stores an address, what must be true before that address may be used safely?**

This is a comparison, not an instruction to replace C with C++ or to learn every memory-management technique immediately. Examples assume C11/C17 and C++20 unless a newer language version is explicitly mentioned. Code fragments are illustrative; include the appropriate headers and place statements inside a function when compiling them.

## 1. The common mental model

Both languages use pointers to store addresses of objects. A pointer is itself an object with a value; the object it points to is separate.

```cpp
int x = 10;
int* p = &x;
```

```text
p (pointer object)           x (integer object)
+------------------+         +----------+
| address of x     | ------> | 10       |
+------------------+         +----------+
```

- `x` is the integer object.
- `&x` produces its address.
- `p` stores that address.
- `*p` accesses the integer through the pointer.

The pointer does not contain a second copy of the integer. Copying an address is not the same as copying the object at that address.

## 2. Core syntax comparison

| Concept | C | C++ | Meaning |
|---|---|---|---|
| Declare an integer | `int x = 10;` | `int x = 10;` | Create an integer object. |
| Declare a pointer | `int *p;` | `int* p;` | Both declaration styles work in either language. |
| Obtain an address | `&x` | `&x` | Address-of operator. |
| Store an address | `p = &x;` | `p = &x;` | Make `p` point to `x`. |
| Dereference | `*p` | `*p` | Access the pointed-to object. |
| Modify through pointer | `*p = 42;` | `*p = 42;` | Modify the target, if the access is valid. |
| Null pointer | `NULL` | `nullptr` | Represent no pointed-to object. |
| Reference declaration | Not supported | `int& r = x;` | Bind a C++ reference to an object. |
| Pointer member access | `p->value` | `p->value` | Equivalent to `(*p).value`. |

**Declaration detail:** `int* p, q;` declares `p` as a pointer and `q` as an ordinary integer. The `*` belongs to the declarator, not to every name on the line. Prefer one declaration per line when learning pointers.

## 3. Address-of, dereference, and pointer copying

The syntax is nearly identical in C and C++.

### C

```c
#include <stdio.h>

int main(void)
{
    int x = 10;
    int *p = &x;
    *p = 25;
    printf("%d\n", x); /* 25 */
    return 0;
}
```

### C++

```cpp
#include <iostream>

int main()
{
    int x = 10;
    int* p = &x;
    *p = 25;
    std::cout << x << '\n'; // 25
}
```

The expression `p` evaluates to an address. The expression `*p` denotes the object at that address. Assigning to `*p` changes the pointed-to object, not the address stored in `p`.

### Pointer copying is not object copying

```cpp
int a = 10;
int b = 20;

int* p = &a;
int* q = p;

*q = 15;
p = &b;
*p = 27;
```

After execution:

| Expression | Result |
|---|---|
| `a` | `15` |
| `b` | `27` |
| `p` | Points to `b` |
| `q` | Still points to `a` |

Copying a pointer copies its address value. Reassigning one pointer does not change another pointer that previously held the same address. This behavior is the same in C and C++.

## 4. C++ references: the major language difference

Standard C does not have C++-style references. C programmers typically pass a pointer when a function must modify a caller's object.

### C: pass an address

```c
void increment(int *p)
{
    ++(*p);
}

/* In a caller: */
int x = 10;
increment(&x);
```

### C++: pass by reference

```cpp
void increment(int& value)
{
    ++value;
}

// In a caller:
int x = 10;
increment(x);
```

Both examples change `x` to `11`. C explicitly passes an address; C++ reference parameters allow ordinary object syntax at the call site.

A C++ reference is an alias-like way to access an existing object. It is not the same as a pointer variable, and the language does not require it to be implemented as a stored machine address.

```cpp
int x = 10;
int& r = x;

r = 30; // changes x
```

### Pointer vs. reference semantics

| Property | C++ pointer | C++ reference |
|---|---|---|
| Declaration | `int* p = &x;` | `int& r = x;` |
| Access object | `*p` | `r` |
| Can be reassigned to another object? | Yes | No; assignment modifies the referent. |
| Can represent no object? | Yes, using `nullptr` | An ordinary valid reference must refer to an object. |
| Must be initialized when declared? | Not always, though initialization is strongly recommended | Yes, a reference must be initialized. |
| Can hold an independently copied address? | Yes | A reference is not a reseatable pointer variable. |
| Typical use | Optional access, traversal, links, explicit address manipulation | Required parameters and aliases |

A reference does not own an object or automatically extend its lifetime merely because it refers to it. A reference can become dangling. C++ has specific temporary-lifetime extension rules, but they do not make arbitrary references safe after their targets have been destroyed.

## 5. Function parameters and idiomatic usage

C++ offers several parameter-passing choices:

```cpp
void inspect(int value);          // copy
void modify(int& value);          // mutable reference
void read(const int& value);      // read-only reference
void optional(int* value);        // pointer, may be nullptr
```

| Intention | C idiom | C++ idiom |
|---|---|---|
| Pass a small value | `void f(int x)` | `void f(int x)` |
| Modify caller's integer | `void f(int *x)` | `void f(int& x)` |
| Read a large record without copying | `void f(const struct Record *r)` | `void f(const Record& r)` |
| Accept an optional object | Pointer, possibly `NULL` | Pointer, possibly `nullptr` |
| Traverse a linked structure | Pointer | Pointer |
| Return or store an address | Pointer | Pointer or an appropriate higher-level abstraction |

A C++ pointer parameter is not inherently wrong. Use it when nullability, reseating, or pointer-based representation is part of the interface. References are often clearer when a valid object is required. For small scalar values, passing by value is usually simplest.

For Week 2, raw pointers are useful because they make reachability and node links explicit. This does not imply that raw pointers are the default choice for every C++ function.

## 6. Null pointers and uninitialized pointers

A null pointer is a defined pointer state that does not identify an object. An uninitialized pointer has an indeterminate value and must not be used as though it contained a valid address.

### C

```c
#include <stddef.h>

int *p = NULL;

if (p != NULL) {
    /* Access through p only when the target is also known to be live. */
}
```

### C++

```cpp
int* p = nullptr;

if (p != nullptr) {
    // Access only when the target is also known to be live.
}
```

`nullptr` is the preferred C++ null pointer literal because it has a dedicated type and avoids ambiguities associated with integer null pointer constants. C23 also introduces `nullptr` and `nullptr_t`, but many introductory C courses and existing C codebases use `NULL`.

**Never assume that an uninitialized pointer is automatically null.**

```cpp
int* p;          // uninitialized local pointer
// *p = 10;      // invalid: no valid target has been established
```

Prefer explicit initialization:

```cpp
int* p = nullptr;
```

A non-null pointer is not necessarily valid. Null checks cannot establish whether an object is still alive.

## 7. Object lifetime: the same fundamental hazard

A pointer is safe to dereference only when it identifies an appropriate live object and the access is otherwise valid. Having an address is not sufficient.

```cpp
int* p = nullptr;

{
    int local = 42;
    p = &local;
    // p identifies a live object here.
}

// local's lifetime has ended.
// Do not dereference p or assume the old address remains usable.
```

The corresponding C program has the same lifetime problem:

```c
int *p = NULL;

{
    int local = 42;
    p = &local;
}

/* local is no longer alive. Do not dereference p. */
```

A dangling pointer is not necessarily equal to null. Its old address may still look plausible, but that does not make it valid. Language rules also restrict certain uses of pointer values after their target's lifetime ends; do not rely on inspecting or comparing such values as a validity test.

### Storage duration vs. lifetime

Objects with automatic storage duration are typically associated with block scope. Dynamically allocated objects remain alive until they are released through the appropriate mechanism. Static storage duration objects generally exist for the duration of the program.

"Stack" and "heap" are useful implementation-level terms, but the language rules are expressed in terms of storage duration, allocation, and object lifetime. Not every object is required to occupy a particular physical memory region.

### Returning the address of a local object

```cpp
int* bad_address()
{
    int local = 42;
    return &local; // unsafe: local's lifetime ends on return
}
```

The same error can be written in C. Returning a pointer does not extend the lifetime of the object it identifies. Returning a reference to such a local object is also unsafe.

## 8. Dynamic allocation: `malloc`/`free` vs. `new`/`delete`

C and C++ provide different conventional allocation mechanisms.

### C: `malloc` and `free`

```c
#include <stdlib.h>

int main(void)
{
    int *p = malloc(sizeof *p);

    if (p == NULL) {
        return 1; /* Handle allocation failure. */
    }

    *p = 42;
    free(p);
    p = NULL;
    return 0;
}
```

`malloc` allocates a region of storage and returns `void*`. In C, this can be implicitly converted to another object-pointer type. `free` releases the allocation. `malloc` does not initialize an integer value for you.

### C++: `new` and `delete`

```cpp
#include <iostream>

int main()
{
    int* p = new int{42};
    std::cout << *p << '\n';

    delete p;
    p = nullptr;
}
```

A `new` expression allocates storage and initializes an object. A `delete` expression destroys the object and releases the associated storage. Ordinary throwing `new` reports allocation failure by throwing `std::bad_alloc`.

### Key differences

| Issue | C | C++ |
|---|---|---|
| Conventional allocation | `malloc` | `new` |
| Conventional release | `free` | `delete` |
| Allocation return type | `void*` | Typed pointer |
| Object initialization | Separate responsibility | Supported directly by `new` |
| Constructors/destructors | Not language features in C | Integrated with object creation/destruction |
| Failure in ordinary form | Null pointer | Exception |
| Preferred ordinary ownership style | Explicit allocation discipline | RAII and standard-library ownership types |

**Do not mix allocation families.** Storage obtained with `malloc` must be released with `free`; an object created with scalar `new` must be released with scalar `delete`. Arrays created with `new[]` require `delete[]`.

```cpp
int* values = new int[5]{};
delete[] values;
```

Using `free` on an object created with `new`, or `delete` on storage obtained with `malloc`, is undefined behavior.

## 9. Ownership is separate from having an address

Consider two pointers to one allocation:

```cpp
int* owner = new int{42};
int* observer = owner;

// Both pointers can access the live object here.

 delete owner;
owner = nullptr;

// observer must not be dereferenced: the object is gone.
```

Setting `owner` to `nullptr` changes only that pointer. It does not update `observer`, and it does not undo the deletion. In C, the same issue occurs with `malloc` and `free`. Neither language automatically tracks all raw pointers that refer to an allocation.

The **owner** is the part of the program responsible for ensuring that a resource is released exactly once. An **observer** may access the object only while it remains alive.

### Assignment to null does not release memory

```cpp
p = nullptr;
```

This only changes the pointer value. If `p` was the only way to reach a dynamically allocated object, that allocation may become unreachable and leak.

Likewise, clearing one pointer after deletion does not make other aliases safe. The correct repair is to design and enforce a clear ownership and lifetime policy, not merely to add null assignments.

## 10. C++ RAII and safer ownership idioms

Modern C++ generally avoids manually pairing `new` and `delete` in ordinary application code. Resource Acquisition Is Initialization (RAII) ties resource cleanup to an object's lifetime.

```cpp
#include <memory>

int main()
{
    auto p = std::make_unique<int>(42);
    *p = 43;

    // The owned integer is automatically released
    // when p's lifetime ends.
}
```

A `std::unique_ptr<int>` owns its dynamically allocated object and releases it automatically. This is different from a raw `int*`, which has no built-in ownership behavior.

For an ordinary sequence of integers, prefer:

```cpp
#include <vector>

std::vector<int> values{10, 20, 30};
```

rather than manually allocating an array merely to store application data. A `std::vector` owns and manages its element storage.

C programs can implement disciplined cleanup through explicit conventions and control flow, but C does not have C++ destructors or standard-library RAII ownership types.

**Week 2 scope:** Understand manual allocation and release so that lifetime errors are visible. Full ownership-class design, move semantics, and implementation of dynamic containers belong to later course topics.

## 11. Arrays and pointer arithmetic

C and C++ both support pointer arithmetic within appropriate array bounds.

```cpp
int values[3] = {10, 20, 30};
int* p = values;

// *p       is 10
// *(p + 1) is 20
// p[2]     is 30
```

In many expressions, an array is converted to a pointer to its first element. However, an array is not itself a pointer.

```cpp
sizeof(values) // size of the entire array
sizeof(p)      // size of the pointer object
```

The array-to-pointer conversion has exceptions, including when the array is the operand of `sizeof` or unary `&`. Both languages distinguish arrays from pointers, although some details of their type systems differ.

A pointer may be advanced within an array and one position past its end, but the one-past-the-end pointer must not be dereferenced.

### C++ alternative for ordinary sequences

```cpp
#include <vector>
#include <iostream>

std::vector<int> values{10, 20, 30};

for (int value : values) {
    std::cout << value << '\n';
}
```

C++ containers retain their size and manage their own storage. Raw pointer arithmetic remains important for understanding low-level representations, but it is not the preferred default for every sequence-processing task.

## 12. Pointers to structures and member access

The member-access syntax is shared.

### C

```c
struct Node {
    int value;
    struct Node *next;
};

struct Node a = {10, NULL};
struct Node *p = &a;

/* p->value is 10. */
```

### C++

```cpp
struct Node {
    int value;
    Node* next;
};

Node a{10, nullptr};
Node* p = &a;

// p->value is 10.
```

In both languages, `p->value` is equivalent to `(*p).value`. The parentheses matter because member access has higher precedence than unary dereference. Writing `*p.value` would be parsed differently.

C requires `struct Node` in this declaration style unless a typedef or another suitable name is introduced. In C++, `Node` itself can normally be used as the type name after the structure declaration.

## 13. Linked nodes: the same representation idea

A linked node stores data and an address leading to the next node.

```cpp
struct Node {
    int value;
    Node* next;
};
```

For Week 2, we can use objects with automatic storage duration:

```cpp
Node c{30, nullptr};
Node b{20, &c};
Node a{10, &b};

Node* head = &a;
```

```text
head
  |
  v
+----+------+    +----+------+    +----+---------+
| 10 | next | -> | 20 | next | -> | 30 | nullptr |
+----+------+    +----+------+    +----+---------+
   a                 b                 c
```

The links describe reachability. They do not determine ownership or extend the lifetime of the nodes.

### C++ traversal

```cpp
#include <iostream>

void print_chain(const Node* head)
{
    const Node* current = head;

    while (current != nullptr) {
        std::cout << current->value << ' ';
        current = current->next;
    }
}
```

### Equivalent C traversal

```c
#include <stdio.h>

void print_chain(const struct Node *head)
{
    const struct Node *current = head;

    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
}
```

The structural invariant is that each link used during traversal must identify a live node of the expected type, and a finite null-terminated chain must eventually reach the null pointer.

### Rewiring does not destroy a node

```cpp
a.next = &c; // a -> c; b still exists
```

Node `b` is no longer reachable from `a`, but its lifetime has not ended. In this example, `b` is an automatic object, so changing a link does not destroy it. Later, when nodes are dynamically owned by a container, removing a link and releasing an owned node will be separate concerns that must be handled correctly.

For a chain of `n` nodes, a full traversal takes **Θ(n) time** and **Θ(1) auxiliary traversal space**. The storage occupied by the nodes themselves is not auxiliary traversal storage.

## 14. `const` with pointers and references

The basic idea of pointer constness is shared by C and C++.

```cpp
const int* p = &x;
```

`p` can be reassigned, but the integer cannot be modified through `p`.

```cpp
int* const p = &x;
```

`p` cannot be reassigned, but the integer can be modified through it.

```cpp
const int* const p = &x;
```

Neither reassignment of `p` nor modification of the integer through `p` is permitted.

### C++ const reference

```cpp
const int& r = x;
```

A const reference provides read-only access through that reference. It is commonly used for function parameters that should not modify their arguments.

Constness restricts operations through a particular access path. It does not necessarily mean that the underlying object is globally immutable.

## 15. `void*` and type safety

C commonly uses `void*` as a generic object-pointer type, particularly with allocation and generic library interfaces.

```c
void *raw = malloc(sizeof(int));
int *p = raw; // valid implicit conversion in C
```

C++ requires an explicit conversion from `void*` to a typed object pointer:

```cpp
#include <cstdlib>

void* raw = std::malloc(sizeof(int));
int* p = static_cast<int*>(raw);
// Use the allocation correctly, then std::free(raw).
```

These fragments illustrate the conversion rules, not a recommended C++ allocation style. In ordinary C++, typed allocations, templates, containers, and RAII abstractions are generally preferable.

A `void*` does not carry enough type information to dereference it directly as an integer. The program must establish the correct object type before typed access.

## 16. Strings: a familiar CS50 connection

C strings are conventionally represented as null-terminated character arrays and accessed through pointers.

```c
const char *message = "Hello";
printf("%s\n", message);
```

In introductory CS50 material, a `string` typedef may be introduced to simplify this representation. It is a course-level abstraction, not a built-in C string type. CS50's own string library and its current teaching materials should be consulted for the precise typedef used in a particular edition.

C++ still supports C-style strings:

```cpp
const char* message = "Hello";
```

but ordinary C++ code generally prefers:

```cpp
#include <string>

std::string message = "Hello";
```

`std::string` manages its storage and provides operations such as `.size()` and concatenation. A C-style string pointer does not, by itself, know the length of the string or own its storage.

## 17. Common errors in both languages

| Error | Example | Problem |
|---|---|---|
| Uninitialized pointer | `int* p; *p = 5;` | No valid target has been established. |
| Null dereference | `int* p = nullptr; *p = 5;` | No object is pointed to. |
| Use after lifetime | Use the address of a local object after its block ends | Target no longer exists. |
| Use after release | Dereference after `free` or `delete` | Allocation's lifetime has ended. |
| Double release | Release the same allocation twice | Undefined behavior. |
| Memory leak | Lose the only owning pointer | Allocation is no longer reachable for cleanup. |
| Out-of-bounds access | `p[10]` for a three-element array | Access outside valid bounds. |
| Wrong allocation family | `free(new int)` | Mismatched allocation and deallocation. |

The C column of these examples would use C syntax such as `NULL` where appropriate. The underlying hazards are shared. A pointer can be non-null and still invalid. Checking `p != nullptr` is therefore not a complete validity test; the program must also know that the target is alive and that the access is permitted.

## 18. Practical debugging with AddressSanitizer

Both C and C++ programs can be compiled with AddressSanitizer when supported by the compiler.

```bash
# C
gcc -g -O1 -fsanitize=address -fno-omit-frame-pointer program.c -o program

# C++
g++ -g -O1 -fsanitize=address -fno-omit-frame-pointer program.cpp -o program
```

AddressSanitizer can detect many memory errors, including heap use-after-free, out-of-bounds accesses, and double-free errors. It is a diagnostic tool, not a proof that a program is free of undefined behavior.

When examining a report, identify the invalid access, the allocation site, and the release site. The Week 2 lab provides dedicated sanitizer targets for this purpose:

```bash
cmake -S . -B build
cmake --build build --target use_after_free_asan
./build/use_after_free_asan

cmake --build build --target double_delete_asan
./build/double_delete_asan
```

Run these commands from `labs/week02/`. The unsafe targets are intentionally separate from the normal build. Do not add undefined behavior to your safe assignment solutions merely to observe an error.

## 19. What to carry forward from C into C++

Your C knowledge transfers directly to address-of, dereference, pointer copying, null checks, pointer-based traversal, and the need to respect object lifetime. The most important adjustments are learning C++ references, using `nullptr`, understanding the distinction between `new`/`delete` and `malloc`/`free`, and recognizing that modern C++ normally delegates ownership to standard-library types.

| Keep from C | Add or adjust in C++ |
|---|---|
| `&x`, `*p`, and `p->member` | References and const references |
| Explicit pointer state reasoning | Prefer `nullptr` for null pointers |
| Array bounds and pointer arithmetic | Prefer `std::vector` for ordinary sequences |
| Lifetime and cleanup discipline | RAII, `std::unique_ptr`, and automatic cleanup |
| Address-based linked representations | Separate non-owning links from ownership responsibility |
| Compiler and memory-error tools | Continue using GCC, GDB, and AddressSanitizer |

For this week, the central rule is:

> A pointer gives a program a way to reach an object. It does not guarantee that the object exists, is still alive, or may be accessed.

## Further reading

- [C++ reference: Pointers](https://en.cppreference.com/w/cpp/language/pointer)
- [C++ reference: References](https://en.cppreference.com/w/cpp/language/reference)
- [C++ reference: Object lifetime](https://en.cppreference.com/w/cpp/language/lifetime)
- [C++ reference: `new` expression](https://en.cppreference.com/w/cpp/language/new)
- [C++ reference: `std::unique_ptr`](https://en.cppreference.com/w/cpp/memory/unique_ptr)
- [C reference: Pointer declarations](https://en.cppreference.com/w/c/language/pointer)
- [C reference: Dynamic memory management](https://en.cppreference.com/w/c/memory)
- [Harvard CS50: Memory (2026)](https://cs50.harvard.edu/x/2026/weeks/4/)
- [BS0013 Week 2 assignment](assignment.md)

This guide is supplementary. The required Week 2 work remains the assignment's pointer traces, lifetime reasoning, safe allocation and release, sanitizer diagnosis, and linked-node traversal and rewiring. Ownership-class implementation, move semantics, and dynamic-container internals are not prerequisites for completing this week's lab.
