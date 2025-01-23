#### [My Utils](index.html) > [dcomp](dcomp.html) > DocFile

## DocFile

Parses and stores components from a single source file.

###### Description

Reads a file for tags and creates wrappers for each tagged code object. Scans line by line for tagged comments. When a tag is found, it extracts description and grabs a code object string starting on the following line. 

Each doc page has a path at the top. DocFiles can be linked to a selected doc source so that its path continues the path of the linked page. *E.g.*, A page has `My Utils > dcomp` as a path. If a DocFile is linked to that page, the resulting path is `My Utils > dcomp > Sub-Directory`.

###### Usage

Create a DocFile by passing in a source file. Can generate a *table* or *entry* using `genMarkdownTable` or `genMarkdownEntry`. A *page* contains a path, description template, table, and all code object entries. Generate a page using `genMarkdownPage`.

---

#### Attributes

All attributes are strings.

- `path`: path of doc page; is template if not linked.
- `lines`: the lines of source file
- `func_wrap`: wrappers for each tagged function

#### \_\_init\_\_

Reads a source file and parses it.

#### linkPath

Creates a path for this DocFile that continues the path of the linked doc source. Checks the relative path first, then checks `docs/`.

#### grabTag

Extracts the description from the tag at the given line index.

#### grabFunction

Extracts a function string at the given line index.

