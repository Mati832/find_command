---

# find_command

A multithreaded file search tool implementing a subset of the Linux `find` command.

---

## Usage

```bash
./findClone [path] [-name pattern] [-type f|d] [-size [+|-|=]value] [-mtime [+|-|=]value] [-r] [-h]
```

---

## Arguments & Flags

### Path

* **`[path]`**
  Start point of the search. If empty, the current directory is used.

### Filters

* **`-name pattern`**
  Filters files/directories by name. Wildcard usage is supported
  *(e.g. `./findClone -name "*.txt"`)*

* **`-type f|d`**
  Filters for files or directories.

* **`-size [+|-|=]value`**
  Filters by file size using a prefix:

  * `+` greater than
  * `-` less than
  * `=` equal to

* **`-mtime [+|-|=]value`**
  Filters by last modification time using a prefix:

  * `+` older than
  * `-` newer than
  * `=` exactly

### Options

* **`-r`**
  Enables recursive search through subdirectories.

* **`-h`**
  Human-readable output. Prints additional information
  *(size, timestamp)* for the found files.

---

## Build Instructions

* **Compile**

  ```bash
  make
  ```

* **Execute Tests**

  ```bash
  make test
  ```

* **Clean**

  ```bash
  make clean
  ```

---

## AI Usage Disclosure

This project was developed with the support of AI tools. The following tasks were assisted by AI:

### Assisted Areas

* **Structure**
  Generated a first rough structure to provide an overview of how the structure could look like.

* **Build System**
  Generated the Makefile.

* **Testing**
  Generated some test cases.

* **Debugging**
  Provided assistance for resolving errors.

* **Documentation**
  Formatted the final README for better readability.

* **General Guidance**
  Answered technical questions regarding:

  * Implementation of stdin for path input
  * Unit testing strategies in C
  * Mechanics of function pointers for filter logic
  * Explanation of `errno` and Linux File API metadata (`stat` / `lstat`)

---
