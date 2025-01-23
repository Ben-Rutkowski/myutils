#### [My Utils](index.html) > [dcomp](dcomp.html) > FunctionWrapper

## FunctionWrapper

Parses and stores components of a function string.

###### Description

Is constructed using a description and function declaration string (*e.g.*, `int getCount(size_t offset);`) and parses it into *description*, *type*, *name*, and *args*.

---

#### Attributes

All attributes are strings.

- `description`: a short description of function
- `func_type`: return type
- `func_name`: function name
- `func_args`: list of arguments

#### \_\_init\_\_

Parses the description and function string.

> `def __init__(...)`

Breaks

**Arguments:**

- `func_tup`: tuple of (*description*, *function string*).

#### genMarkdownEntry

Creates an entry for the function.

> `def genMarkdownEntry(...)`

Each entry has a title, description, code declaration, and list of arguemnts.
