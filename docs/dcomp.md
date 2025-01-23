#### [My Utils](index.html) > dcomp

## dcomp

Tool for creating documentation on C and C++ objects.

###### Description
Searches through a header file for documentation tags and creates markdown document. For each header input, the markdown output will have three sections:

- **Doc Path**: path within documents (*e.g.*, `My Utils > dcomp`).
- **Table of Contents**: a bulletin list of links to each code object.
- **Object Entries**: a list of blank entries for each code object.

###### Usage
Tag code objects you want to document with a specified comment (*e.g.*, `/*:F:*/` for a function) one line before the declaration to mark it to be compiled. (These comments can be deleted after compilation for readability.) Call `dcomp` with the header file and an output markdown file. Users may add a short description after the tag (*e.g.* `/*:F: Short desctiption*/`) to be used in the Table of Contents and Object Entries.

Basic arugments are passed as file inputs to be created as DocFile objects. Options:

- `-e` or `--entry`: prints only the entries.
- `-t` or `--table`: prints only the tables.
- `-l` or `--link`: one argument; formats the header path so output is child of the linked `.md` file.

All file paths are relative to the current directory that called the script. Linked arguemnt paths will check the current directory and then check `docs/`.

---

## Structure

#### [DocFile](docfile.html)

A `DocFile` object is created from reading the source code. For each tagged object, stores a Wrapper object.

#### [FunctionWrapper](function_wrapper.html)

A parsed funciton object, contains *description*, *return type*, *name*, and *arguments*.
