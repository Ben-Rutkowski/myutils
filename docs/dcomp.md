#### [My Utils](index.html) > dcomp

## dcomp

Tool for creating documentation on C and C++ objects.

###### Description
Searches through a header file for documentation tags and creates markdown document. For each header input, the markdown output will have three sections:

- **Doc Path Template**: template for a path within documents (*e.g.*, `My Utils > dcomp`).
- **Table of Contents**: a bulletin list of links to each code object.
- **Object Docs**: a list of blank entries for each code object.

###### Usage
Tag code objects you want to document with a specified comment (*e.g.*, `/*:F:*/` for a function) before the declaration to mark it to be compiled. (These comments can be deleted after compilation for readability.) Call `dcomp` with the header file and an output markdown file. Users may add a short description after the tag (*e.g.* `/*:F: Short desctiption*/`) to be used in the Table of Contents and Object Docs.

- `-e` or `--entry`: prints only the entries.
- `-t` or `--table`: prints only the tables.
- `-l` or `--link`: formats the header path so output is child of the linked `.md` file.

---

## Structure

#### [DocFile](docfile.html)

A `DocFile` object is created from reading the source code. Every code object in the source file that has been tagged is extracted as a string and organized by type.
