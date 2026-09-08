# Week 1 reflection

Write concise answers in your own words.

## 1. Source and executable

What is the difference between `src/hello.cpp` and `build/manual/hello` after compilation?

Answer: src/hello.cpp is what we write as code, what we understand and build/manual/hello is what computer understands and is able to execute

## 2. Compiler warnings

What is the purpose of `-Wall -Wextra -Wpedantic`?

Answer: They are meant for the compiler, so that it can possibly detect some issues - what is wrong wiyh our code

## 3. Value and reference parameters

What is the difference between these declarations?

```cpp
void f(std::vector<int> values);
void f(std::vector<int>& values);
```

Answer: Without & the fuction gets a copy and cannot change the vector while with & the function can change it

## 4. Const reference

Why can this parameter form be useful?

```cpp
void print(const std::vector<int>& values);
```

Answer: This allows us to not create a consuming copy of the vector as well as 'const' prevents accidental modification

## 5. Linux navigation

Which command shows the current working directory?

Answer:pwd

## 6. Git state

Which command shows modified files?

Answer: git status

